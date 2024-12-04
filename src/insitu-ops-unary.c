

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
//       *x = sqrt(*x); x++;
//       *x = sqrt(*x); x++;
//       *x = sqrt(*x); x++;
//       *x = sqrt(*x); x++;
//     }
//     for (; i< Rf_length(x_); i++) {
//       *x = sqrt(*x); x++;
//     }
//   
//   return x_;
// }


#define INSUNARYOP(nm, unaryop, startidx)                      \
SEXP br_##nm##_(SEXP x_) {                                    \
  double *x = REAL(x_);                                        \
                                                               \
  int i = startidx;                                            \
  x += startidx;                                               \
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {         \
    *x = unaryop; x++;                                         \
    *x = unaryop; x++;                                         \
    *x = unaryop; x++;                                         \
    *x = unaryop; x++;                                         \
  }                                                            \
  for (; i< Rf_length(x_); i++) {                                 \
    *x = unaryop; x++;                                         \
  }                                                            \
                                                               \
  return x_;                                                   \
}                                                              

#define R_NO_REMAP

INSUNARYOP(abs  ,  fabs(*x), 0)
INSUNARYOP(sqrt ,  sqrt(*x), 0)
INSUNARYOP(floor, floor(*x), 0)
INSUNARYOP(ceil ,  ceil(*x), 0)
INSUNARYOP(trunc, trunc(*x), 0)
// INSUNARYOP(round, round(*x), 0)
INSUNARYOP(exp  ,   exp(*x), 0)
INSUNARYOP(log  ,   log(*x), 0)
INSUNARYOP(cos  ,   cos(*x), 0)
INSUNARYOP(sin  ,   sin(*x), 0)
INSUNARYOP(tan  ,   tan(*x), 0)
INSUNARYOP(not  , (double)(*x == 0), 0)
INSUNARYOP(expm1, expm1(*x), 0)
INSUNARYOP(log1p, log1p(*x), 0)
INSUNARYOP(acos ,  acos(*x), 0)
INSUNARYOP(asin ,  asin(*x), 0)
INSUNARYOP(atan ,  atan(*x), 0)
INSUNARYOP(acosh, acosh(*x), 0)
INSUNARYOP(asinh, asinh(*x), 0)
INSUNARYOP(atanh, atanh(*x), 0)
INSUNARYOP(cosh ,  cosh(*x), 0)
INSUNARYOP(sinh ,  sinh(*x), 0)
INSUNARYOP(tanh ,  tanh(*x), 0)
INSUNARYOP(sign ,  (double)( (*x > 0) - (*x < 0) ), 0)
INSUNARYOP(cospi,   cos(*x * M_PI), 0)
INSUNARYOP(sinpi,   sin(*x * M_PI), 0)
INSUNARYOP(tanpi,   tan(*x * M_PI), 0)


INSUNARYOP(cumsum ,  *x + *(x - 1), 1)
INSUNARYOP(cumprod,  *x * *(x - 1), 1)
INSUNARYOP(cummax ,  *x > *(x - 1) ? *x : *(x - 1), 1)
INSUNARYOP(cummin ,  *x < *(x - 1) ? *x : *(x - 1), 1)
  
INSUNARYOP(log2 ,   log2(*x), 0)
INSUNARYOP(log10,   log10(*x), 0)

INSUNARYOP(is_na, (double)isnan(*x), 0)

