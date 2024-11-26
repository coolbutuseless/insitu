

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

// SEXP ins_sqrt_(SEXP x_) {
//   double *x = REAL(x_);
//     
//     int i = 0;
//     for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
//       *x = sqrt(*x); x++;
//       *x = sqrt(*x); x++;
//       *x = sqrt(*x); x++;
//       *x = sqrt(*x); x++;
//     }
//     for (; i< length(x_); i++) {
//       *x = sqrt(*x); x++;
//     }
//   
//   return x_;
// }


#define INSMATHOP(nm, cfun)                                        \
SEXP ins_##nm##_(SEXP x_) {                                        \
  double *x = REAL(x_);                                            \
                                                                   \
  int i = 0;                                                       \
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {             \
    *x = cfun(*x); x++;                                            \
    *x = cfun(*x); x++;                                            \
    *x = cfun(*x); x++;                                            \
    *x = cfun(*x); x++;                                            \
  }                                                                \
  for (; i< length(x_); i++) {                                     \
    *x = cfun(*x); x++;                                            \
  }                                                                \
                                                                   \
  return x_;                                                       \
}                                                              


INSMATHOP(abs  , fabs)
INSMATHOP(sqrt , sqrt)
INSMATHOP(floor, floor)
INSMATHOP(ceil , ceil)
INSMATHOP(trunc, trunc)
INSMATHOP(round, round)
INSMATHOP(exp  , exp)
INSMATHOP(log  , log)
INSMATHOP(cos  , cos)
INSMATHOP(sin  , sin)
INSMATHOP(tan  , tan)
