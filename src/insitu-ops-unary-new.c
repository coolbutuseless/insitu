
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
        Rf_error("Length mismatch: len(where) [%.0f] != len(x) [%.0f] or nrow(x) [%i]",
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
      Rf_error("Length mismatch: len(where) [%.0f] != len(x) [%.0f] ",
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
#define UNARYOPBYIDX(nm, unaryop)                                         \
static inline void br_##nm##_byidx(double *x, int *idx, int idx_len) {   \
                                                                          \
  for (int j = 0; j < idx_len; ++j) {                                     \
    int i = idx[j];                                                       \
    x[i] = unaryop(0);                                                    \
  }                                                                       \
                                                                          \
}                                                                         \


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a unary func that performs the operation over 'len' values
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOPFULL(nm, unaryop)                                  \
static inline void br_##nm##_full(double *x, int len) {          \
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
}                                                                 \


#define UNARYOPFUNC(nm, unaryop)                                                      \
SEXP br_##nm##_(SEXP x_, SEXP idx_, SEXP where_, SEXP cols_) {                       \
                                                                                      \
  /* Basic case. Matrix and vector both treated like matrix */                        \
  if (Rf_isNull(idx_) && Rf_isNull(where_) && Rf_isNull(cols_)) {                     \
    br_##nm##_full(REAL(x_), (int)Rf_length(x_));                                    \
    return x_;                                                                        \
  }                                                                                   \
                                                                                      \
  /* If 'cols' specified, must be a matrix */                                         \
  if (!Rf_isNull(cols_)) {                                                            \
    if (!Rf_isMatrix(x_)) Rf_error("Specified 'cols' by 'x' is not a matrix");        \
    int *cols = ridx_to_idx(cols_, Rf_ncols(x_));                                     \
    if (!Rf_isNull(idx_)) {                                                           \
      int *idx = ridx_to_idx(idx_, Rf_nrows(x_));                                     \
      for (int i = 0; i < Rf_length(cols_); ++i) {                                    \
        br_##nm##_byidx(REAL(x_) + cols[i] * Rf_nrows(x_), idx, Rf_length(idx_));    \
      }                                                                               \
      free(idx);                                                                      \
    } else if (!Rf_isNull(where_)) {                                                  \
      int idx_len = 0;                                                                \
      int *idx = lgl_to_idx(where_, &idx_len);                                        \
      for (int i = 0; i < Rf_length(cols_); ++i) {                                    \
        br_##nm##_byidx(REAL(x_) + cols[i] * Rf_nrows(x_), idx, idx_len);            \
      }                                                                               \
      free(idx);                                                                      \
    } else {                                                                          \
      for (int i = 0; i < Rf_length(cols_); ++i) {                                    \
        br_##nm##_full(REAL(x_) + cols[i] * Rf_nrows(x_), Rf_nrows(x_));             \
      }                                                                               \
    }                                                                                 \
                                                                                      \
    free(cols);                                                                       \
    return x_;                                                                        \
  }                                                                                   \
                                                                                      \
                                                                                      \
  /* Matrix where 'cols' has not been set. Just deal with 'where' and 'idx'           \
   and apply to all columns */                                                        \
  if (Rf_isMatrix(x_)) {                                                              \
    if (!Rf_isNull(idx_)) {                                                           \
      int *idx = ridx_to_idx(idx_, Rf_nrows(x_));                                     \
      for (int col = 0; col < Rf_ncols(x_); ++col) {                                  \
        br_##nm##_byidx(REAL(x_) + col * Rf_nrows(x_), idx, Rf_length(idx_));        \
      }                                                                               \
      free(idx);                                                                      \
    } else if (!Rf_isNull(where_)) {                                                  \
      if (Rf_length(where_) == Rf_nrows(x_)) {                                        \
        /* Apply 'where' column-wise */                                               \
        int idx_len = 0;                                                              \
        int *idx = lgl_to_idx(where_, &idx_len);                                      \
        for (int col = 0; col < Rf_ncols(x_); ++col) {                                \
          br_##nm##_byidx(REAL(x_) + col * Rf_nrows(x_), idx, idx_len);              \
        }                                                                             \
        free(idx);                                                                    \
      } else if (Rf_length(where_) == Rf_length(x_)) {                                \
        /* Treat 'where' as global */                                                 \
        int idx_len = 0;                                                              \
        int *idx = lgl_to_idx(where_, &idx_len);                                      \
        br_##nm##_byidx(REAL(x_), idx, idx_len);                                     \
        free(idx);                                                                    \
      } else {                                                                        \
        Rf_error("Length mismatch: len(where) [%.0f] != len(x) [%.0f] or nrow(x) [%i]",\
                 (double)Rf_length(where_), (double)Rf_length(x_),                    \
                 Rf_nrows(x_));                                                       \
      }                                                                               \
    } else {                                                                          \
      Rf_error("Error. Code 8876. Should never happen!");                             \
    }                                                                                 \
                                                                                      \
    return x_;                                                                        \
  }                                                                                   \
                                                                                      \
  /* If here, 'x' will only be treated as vector with either 'idx' or 'where' set */  \
  if (!Rf_isNull(idx_)) {                                                             \
    int *idx = ridx_to_idx(idx_, Rf_length(x_));                                      \
    br_##nm##_byidx(REAL(x_), idx, Rf_length(idx_));                                 \
    free(idx);                                                                        \
    return x_;                                                                        \
  } else if (!Rf_isNull(where_)) {                                                    \
    if (Rf_length(where_) == Rf_length(x_)) {                                         \
      int idx_len = 0;                                                                \
      int *idx = lgl_to_idx(where_, &idx_len);                                        \
      br_##nm##_byidx(REAL(x_), idx, idx_len);                                       \
      free(idx);                                                                      \
      return x_;                                                                      \
    } else {                                                                          \
      Rf_error("Length mismatch: len(where) [%.0f] != len(x) [%.0f] ",                 \
               (double)Rf_length(where_), (double)Rf_length(x_));                     \
    }                                                                                 \
  } else {                                                                            \
    Rf_error("Error. Code 8877. Should never happen!");                               \
  }                                                                                   \
                                                                                      \
                                                                                      \
  Rf_error("Error. Code 8878. Should never happen!");                                 \
}    


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a set of unary funcs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOP(nm, unaryop)       \
UNARYOPBYIDX(nm, unaryop)          \
UNARYOPFULL(nm, unaryop)           \
UNARYOPFUNC(nm, unaryop)




#define OP_ABS(offset)    fabs(x[i + (offset)])
#define OP_SQRT(offset)   sqrt(x[i + (offset)])
#define OP_FLOOR(offset) floor(x[i + (offset)])
#define OP_CEIL(offset)   ceil(x[i + (offset)])
#define OP_TRUNC(offset) trunc(x[i + (offset)])
#define OP_EXP(offset)     exp(x[i + (offset)])
#define OP_LOG(offset)     log(x[i + (offset)])
#define OP_LOG2(offset)   log2(x[i + (offset)])
#define OP_LOG10(offset) log10(x[i + (offset)])
#define OP_COS(offset)     cos(x[i + (offset)])
#define OP_SIN(offset)     sin(x[i + (offset)])
#define OP_TAN(offset)     tan(x[i + (offset)])
#define OP_NOT(offset)   (double)(x[i + (offset)] == 0)
#define OP_EXPM1(offset) expm1(x[i + (offset)])
#define OP_LOG1P(offset) log1p(x[i + (offset)])
#define OP_ACOS(offset)   acos(x[i + (offset)])
#define OP_ASIN(offset)   asin(x[i + (offset)])
#define OP_ATAN(offset)   atan(x[i + (offset)])
#define OP_ACOSH(offset) acosh(x[i + (offset)])
#define OP_ASINH(offset) asinh(x[i + (offset)])
#define OP_ATANH(offset) atanh(x[i + (offset)])
#define OP_COSH(offset)   cosh(x[i + (offset)])
#define OP_SINH(offset)   sinh(x[i + (offset)])
#define OP_TANH(offset)   tanh(x[i + (offset)])
#define OP_SIGN(offset)  (double)( (x[i + (offset)] > 0) - (x[i + (offset)] < 0)) 
#define OP_COSPI(offset)   cos(x[i + (offset)] * M_PI)
#define OP_SINPI(offset)   sin(x[i + (offset)] * M_PI)
#define OP_TANPI(offset)   tan(x[i + (offset)] * M_PI)
#define OP_IS_NA(offset) (double)isnan(x[i + (offset)])


UNARYOP(abs  ,  OP_ABS)
UNARYOP(sqrt ,  OP_SQRT)
UNARYOP(floor,  OP_FLOOR)
UNARYOP(ceil ,  OP_CEIL)
UNARYOP(trunc,  OP_TRUNC)
UNARYOP(exp  ,  OP_EXP)
UNARYOP(log  ,  OP_LOG)
UNARYOP(log2 ,  OP_LOG2)
UNARYOP(log10,  OP_LOG10)
UNARYOP(cos  ,  OP_ABS)
UNARYOP(sin  ,  OP_SIN)
UNARYOP(tan  ,  OP_TAN)
UNARYOP(not  ,  OP_NOT)
UNARYOP(expm1,  OP_EXPM1)
UNARYOP(log1p,  OP_LOG1P)
UNARYOP(acos ,  OP_ACOS)
UNARYOP(asin ,  OP_ASIN)
UNARYOP(atan ,  OP_ATAN)
UNARYOP(acosh,  OP_ACOSH)
UNARYOP(asinh,  OP_ASINH)
UNARYOP(atanh,  OP_ATANH)
UNARYOP(cosh ,  OP_COSH)
UNARYOP(sinh ,  OP_SINH)
UNARYOP(tanh ,  OP_TANH)
UNARYOP(sign ,  OP_SIGN)
UNARYOP(cospi,  OP_COSPI)
UNARYOP(sinpi,  OP_SINPI)
UNARYOP(tanpi,  OP_TANPI)
UNARYOP(is_na,  OP_IS_NA)






