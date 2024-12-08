
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




#define INSUNARYOP(nm, unaryop)                                        \
SEXP br_##nm##_where_(SEXP x_, int *idx, int idx_len) {                \
                                                                       \
  double *x = REAL(x_);                                                \
                                                                       \
  for (int j = 0; j < idx_len; ++j) {                                  \
    int i = idx[j];                                                    \
    x[i] = unaryop(0);                                                 \
  }                                                                    \
                                                                       \
  return x_;                                                           \
}                                                                      \
                                                                       \
                                                                       \
SEXP br_##nm##_(SEXP x_, SEXP idx_, SEXP where_) {                     \
                                                                       \
  if (!Rf_isNull(where_)) {                                            \
    int idx_len = 0;                                                   \
    int *idx = lgl_to_idx(where_, &idx_len);                           \
    SEXP res_ = br_##nm##_where_(x_, idx, idx_len);                    \
    free(idx);                                                         \
    return res_;                                                       \
  }                                                                    \
                                                                       \
  if (!Rf_isNull(idx_)) {                                              \
    int *idx = ridx_to_idx(idx_, Rf_length(x_));                       \
    SEXP res_ = br_##nm##_where_(x_, idx, Rf_length(idx_));            \
    free(idx);                                                         \
    return res_;                                                       \
  }                                                                    \
                                                                       \
  double *x = REAL(x_);                                                \
                                                                       \
  int i = 0;                                                           \
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {              \
    x[i + 0] = unaryop(0);                                             \
    x[i + 1] = unaryop(1);                                             \
    x[i + 2] = unaryop(2);                                             \
    x[i + 3] = unaryop(3);                                             \
  }                                                                    \
  for (; i< Rf_length(x_); ++i) {                                      \
    x[i] = unaryop(0);                                                 \
  }                                                                    \
                                                                       \
  return x_;                                                           \
}           


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


INSUNARYOP(abs  ,  OP_ABS)
INSUNARYOP(sqrt ,  OP_SQRT)
INSUNARYOP(floor,  OP_FLOOR)
INSUNARYOP(ceil ,  OP_CEIL)
INSUNARYOP(trunc,  OP_TRUNC)
INSUNARYOP(exp  ,  OP_EXP)
INSUNARYOP(log  ,  OP_LOG)
INSUNARYOP(log2 ,  OP_LOG2)
INSUNARYOP(log10,  OP_LOG10)
INSUNARYOP(cos  ,  OP_ABS)
INSUNARYOP(sin  ,  OP_SIN)
INSUNARYOP(tan  ,  OP_TAN)
INSUNARYOP(not  ,  OP_NOT)
INSUNARYOP(expm1,  OP_EXPM1)
INSUNARYOP(log1p,  OP_LOG1P)
INSUNARYOP(acos ,  OP_ACOS)
INSUNARYOP(asin ,  OP_ASIN)
INSUNARYOP(atan ,  OP_ATAN)
INSUNARYOP(acosh,  OP_ACOSH)
INSUNARYOP(asinh,  OP_ASINH)
INSUNARYOP(atanh,  OP_ATANH)
INSUNARYOP(cosh ,  OP_COSH)
INSUNARYOP(sinh ,  OP_SINH)
INSUNARYOP(tanh ,  OP_TANH)
INSUNARYOP(sign ,  OP_SIGN)
INSUNARYOP(cospi,  OP_COSPI)
INSUNARYOP(sinpi,  OP_SINPI)
INSUNARYOP(tanpi,  OP_TANPI)
INSUNARYOP(is_na,  OP_IS_NA)

  
  
  
  
  // INSITU Cumulative Op
#define INSCUMOP(nm, unaryop)                                                    \
  SEXP br_##nm##_(SEXP x_) {                                                     \
    double *x = REAL(x_);                                                        \
                                                                                 \
    int i = 1;                                                                   \
    for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {                      \
      *x = unaryop; ++x;                                                         \
      *x = unaryop; ++x;                                                         \
      *x = unaryop; ++x;                                                         \
      *x = unaryop; ++x;                                                         \
    }                                                                            \
    for (; i< Rf_length(x_); ++i) {                                              \
      *x = unaryop; ++x;                                                         \
    }                                                                            \
                                                                                 \
    return x_;                                                                   \
  }           

INSCUMOP(cumsum ,  *x + *(x - 1))
INSCUMOP(cumprod,  *x * *(x - 1))
INSCUMOP(cummax ,  *x > *(x - 1) ? *x : *(x - 1))
INSCUMOP(cummin ,  *x < *(x - 1) ? *x : *(x - 1))
  

