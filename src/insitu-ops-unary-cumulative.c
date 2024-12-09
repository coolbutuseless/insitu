
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
  

