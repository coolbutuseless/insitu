
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// * abs, sign, sqrt, floor, ceiling, trunc, round, signif
// * exp, log, expm1, log1p, cos, sin, tan, cospi, sinpi, tanpi, acos, asin, atan
// * cosh, sinh, tanh, acosh, asinh, atanh
// * lgamma, gamma, digamma, trigamma
// * cumsum, cumprod, cummax, cummin

#define UNROLL 4

// SEXP br_sqrt_(SEXP x_) {
//   double *x = REAL(x_);
//     
//     int i = 0;
//     for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
//       *x = sqrt(*x); ++x;
//       *x = sqrt(*x); ++x;
//       *x = sqrt(*x); ++x;
//       *x = sqrt(*x); ++x;
//     }
//     for (; i< Rf_length(x_); ++i) {
//       *x = sqrt(*x); ++x;
//     }
//   
//   return x_;
// }


#define INSUNARYOP(nm, unaryop)                                      \
SEXP br_##nm##_where_(SEXP x_, SEXP where_) {                                  \
                                                                               \
  if (Rf_length(x_) != Rf_length(where_)) {                                    \
    Rf_error("'x' and 'where' must be the same length");                       \
  }                                                                            \
  double *x = REAL(x_);                                                        \
  double *where = REAL(where_);                                                \
  int i = 0;                                                            \
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {                      \
    if (*where++ != 0) *x = unaryop; ++x;                                      \
    if (*where++ != 0) *x = unaryop; ++x;                                      \
    if (*where++ != 0) *x = unaryop; ++x;                                      \
    if (*where++ != 0) *x = unaryop; ++x;                                      \
  }                                                                            \
  for (; i< Rf_length(x_); ++i) {                                              \
    if (*where++ != 0) *x = unaryop; ++x;                                      \
  }                                                                            \
                                                                               \
  return x_;                                                                   \
}                                                                              \
                                                                               \
SEXP br_##nm##_(SEXP x_, SEXP where_) {                                        \
  if (!Rf_isNull(where_)) {                                                    \
    return br_##nm##_where_(x_, where_);                                       \
  }                                                                            \
  double *x = REAL(x_);                                                        \
                                                                               \
  int i = 0;                                                            \
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


INSUNARYOP(abs  ,  fabs(*x))
INSUNARYOP(sqrt ,  sqrt(*x))
INSUNARYOP(floor, floor(*x))
INSUNARYOP(ceil ,  ceil(*x))
INSUNARYOP(trunc, trunc(*x))
INSUNARYOP(exp  ,   exp(*x))
INSUNARYOP(log  ,   log(*x))
INSUNARYOP(log2 ,  log2(*x))
INSUNARYOP(log10, log10(*x))
INSUNARYOP(cos  ,   cos(*x))
INSUNARYOP(sin  ,   sin(*x))
INSUNARYOP(tan  ,   tan(*x))
INSUNARYOP(not  , (double)(*x == 0))
INSUNARYOP(expm1, expm1(*x))
INSUNARYOP(log1p, log1p(*x))
INSUNARYOP(acos ,  acos(*x))
INSUNARYOP(asin ,  asin(*x))
INSUNARYOP(atan ,  atan(*x))
INSUNARYOP(acosh, acosh(*x))
INSUNARYOP(asinh, asinh(*x))
INSUNARYOP(atanh, atanh(*x))
INSUNARYOP(cosh ,  cosh(*x))
INSUNARYOP(sinh ,  sinh(*x))
INSUNARYOP(tanh ,  tanh(*x))
INSUNARYOP(sign ,  (double)( (*x > 0) - (*x < 0) ))
INSUNARYOP(cospi,   cos(*x * M_PI))
INSUNARYOP(sinpi,   sin(*x * M_PI))
INSUNARYOP(tanpi,   tan(*x * M_PI))
INSUNARYOP(is_na, (double)isnan(*x))

  
  
  
  
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
  

