
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils-logical-to-idx.h"

// * abs, sign, sqrt, floor, ceiling, trunc, round, signif
// * exp, log, expm1, log1p, cos, sin, tan, cospi, sinpi, tanpi, acos, asin, atan
// * cosh, sinh, tanh, acosh, asinh, atanh
// * lgamma, gamma, digamma, trigamma
// * cumsum, cumprod, cummax, cummin

#define UNROLL 4
#define OP_SQRT(offset)   sqrt(x[i + (offset)])

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static inline void ybr_sqrt_byidx(double *x, int *idx, int idx_len) {

  for (int j = 0; j < idx_len; ++j) {
    int i = idx[j];
    x[i] = OP_SQRT(0);
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static inline void ybr_sqrt_full(double *x, int len) {

  int i = 0;
  for (; i < len - (UNROLL - 1); i += UNROLL) {
    x[i + 0] = OP_SQRT(0);
    x[i + 1] = OP_SQRT(1);
    x[i + 2] = OP_SQRT(2);
    x[i + 3] = OP_SQRT(3);
  }
  for (; i < len; ++i) {
    x[i] = OP_SQRT(0);
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Main R interface to 'sqrt()'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ybr_sqrt_(SEXP x_, SEXP idx_, SEXP where_, SEXP cols_) {                       
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Basic case. Matrix and vector both treated like matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isNull(idx_) && Rf_isNull(where_) && Rf_isNull(cols_)) {
    ybr_sqrt_full(REAL(x_), (int)Rf_length(x_));
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // If 'cols' specified, must be a matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isNull(cols_)) {
    if (!Rf_isMatrix(x_)) Rf_error("Specified 'cols' by 'x' is not a matrix");
    int *cols = ridx_to_idx(cols_, Rf_ncols(x_));
    if (!Rf_isNull(idx_)) {
      int *idx = ridx_to_idx(idx_, Rf_nrows(x_));
      for (int i = 0; i < Rf_length(cols_); ++i) {
        ybr_sqrt_byidx(REAL(x_) + cols[i] * Rf_nrows(x_), idx, Rf_length(idx_));
      }
      free(idx);
    } else if (!Rf_isNull(where_)) {
      int idx_len = 0;
      int *idx = lgl_to_idx(where_, &idx_len);
      for (int i = 0; i < Rf_length(cols_); ++i) {
        ybr_sqrt_byidx(REAL(x_) + cols[i] * Rf_nrows(x_), idx, idx_len);
      }
      free(idx);
    } else {
      for (int i = 0; i < Rf_length(cols_); ++i) {
        ybr_sqrt_full(REAL(x_) + cols[i] * Rf_nrows(x_), Rf_nrows(x_));
      }
    }
    
    free(cols);
    return x_;
  }
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Matrix where 'cols' has not been set. Just deal with 'where' and 'idx'
  // and apply to all columns
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isMatrix(x_)) {
    if (!Rf_isNull(idx_)) {
      int *idx = ridx_to_idx(idx_, Rf_nrows(x_));
      for (int col = 0; col < Rf_ncols(x_); ++col) {
        ybr_sqrt_byidx(REAL(x_) + col * Rf_nrows(x_), idx, Rf_length(idx_));
      }
      free(idx);
    } else if (!Rf_isNull(where_)) {
      if (Rf_length(where_) == Rf_nrows(x_)) {
        // Apply 'where' column-wise
        int idx_len = 0;
        int *idx = lgl_to_idx(where_, &idx_len);
        for (int col = 0; col < Rf_ncols(x_); ++col) {
          ybr_sqrt_byidx(REAL(x_) + col * Rf_nrows(x_), idx, idx_len);
        }
        free(idx);
      } else if (Rf_length(where_) == Rf_length(x_)) {
        // Treat 'where' as global
        int idx_len = 0;
        int *idx = lgl_to_idx(where_, &idx_len);
        ybr_sqrt_byidx(REAL(x_), idx, idx_len);
        free(idx);
      } else {
        Rf_error("Length mismach: len(where) [%.0f] != len(x) [%.0f] or nrow(x) [%i]",
                (double)Rf_length(where_), (double)Rf_length(x_), 
                Rf_nrows(x_));
      }
    } else {
      Rf_error("Error. Code 8876. Should never happen!");
    }
    
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // If here, 'x' will only be treated as vector with either 'idx' or 'where' set
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isNull(idx_)) {
    int *idx = ridx_to_idx(idx_, Rf_length(x_));
    ybr_sqrt_byidx(REAL(x_), idx, Rf_length(idx_));
    free(idx);
    return x_;
  } else if (!Rf_isNull(where_)) {
    if (Rf_length(where_) == Rf_length(x_)) {
      int idx_len = 0;
      int *idx = lgl_to_idx(where_, &idx_len);
      ybr_sqrt_byidx(REAL(x_), idx, idx_len);
      free(idx);
      return x_;
    } else {
      Rf_error("Length mismach: len(where) [%.0f] != len(x) [%.0f] ",
               (double)Rf_length(where_), (double)Rf_length(x_));
    }
  } else {
    Rf_error("Error. Code 8877. Should never happen!");
  }
  
  
  Rf_error("Error. Code 8878. Should never happen!");
}           



















//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a function that performs the unary operation by index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOPBYIDX(nm, unaryop)                                 \
void xbr_##nm##_byidx_(double *x, int *idx, int idx_len) {        \
                                                                  \
  for (int j = 0; j < idx_len; ++j) {                             \
    int i = idx[j];                                               \
    x[i] = unaryop(0);                                            \
  }                                                               \
                                                                  \
}                                                                 \


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a unary func that performs the operation over 'len' values
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOPFULL(nm, unaryop)                                  \
void xbr_##nm##_full_(double *x, int len) {                       \
  int i = 0;                                                      \
  for (; i < len - (UNROLL - 1); i += UNROLL) {                   \
    x[i + 0] = unaryop(0);                                        \
    x[i + 1] = unaryop(1);                                        \
    x[i + 2] = unaryop(2);                                        \
    x[i + 3] = unaryop(3);                                        \
  }                                                               \
  for (; i< len; ++i) {                                           \
    x[i] = unaryop(0);                                            \
  }                                                               \
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a set of unary funcs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOP(nm, unaryop)                                     \
UNARYOPBYIDX(nm, unaryop)                                        \
UNARYOPFULL(nm, unaryop) 





UNARYOP(xsqrt ,  OP_SQRT)






