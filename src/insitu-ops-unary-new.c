
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

// #define OP_SQRT(offset) sqrt(x[i + (offset)])
// 
// SEXP br_sqrt_where_(SEXP x_, int *idx, int idx_len) {
//   double *x = REAL(x_);
//   
//   for (int j = 0; j < idx_len; ++j) {
//     int i = idx[j];
//     x[i] = OP_SQRT(0);
//   }
// 
//   return x_;
// }
// 
// 
// SEXP br_sqrt_(SEXP x_, SEXP where_) {
//   if (!Rf_isNull(where_)) {         
//     int idx_len = 0;
//     int *idx = lgl_to_idx(where_, &idx_len);
//     SEXP res_ = br_sqrt_where_(x_, idx, idx_len);
//     free(idx);
//     return res_;
//   }                                      
//   
//   double *x = REAL(x_);
//   
//   int i = 0;
//   for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
//     x[i + 0] = OP_SQRT(0);
//     x[i + 1] = OP_SQRT(1);
//     x[i + 2] = OP_SQRT(2);
//     x[i + 3] = OP_SQRT(3);
//   }
//   for (; i< Rf_length(x_); ++i) {
//     x[i] = sqrt(x[i]);
//   }
//   
//   return x_;
// }



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


#define OP_SQRT(offset)   sqrt(x[i + (offset)])



UNARYOP(sqrtx ,  OP_SQRT)






