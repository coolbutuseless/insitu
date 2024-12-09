
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



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a unary func that performs the operation over 'len' values
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define CUMULATIVEOPFULL(nm, unaryop)                                  \
static inline void br_##nm##_full(double *x, int len) {                \
  int i = 1;                                                           \
  for (; i < len - (UNROLL - 1); i += UNROLL) {                        \
    x[i + 0] = unaryop(0);                                             \
    x[i + 1] = unaryop(1);                                             \
    x[i + 2] = unaryop(2);                                             \
    x[i + 3] = unaryop(3);                                             \
  }                                                                    \
  for (; i< len; ++i) {                                                \
    x[i] = unaryop(0);                                                 \
  }                                                                    \
}                                                                      \

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Dispatch function for cumulative op
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define CUMULATIVEOPFUNC(nm, unaryop)                                                    \
SEXP br_##nm##_(SEXP x_) {                                                               \
                                                                                         \
  br_##nm##_full(REAL(x_), (int)Rf_length(x_));                                          \
                                                                                         \
  return x_;                                                                             \
}           

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create 'full' cumulative op as well as dispatch FUNC
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define CUMULATIVEOP(nm, unaryop)                              \
CUMULATIVEOPFULL(nm, unaryop)                                  \
CUMULATIVEOPFUNC(nm, unaryop)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Define the operations on each element (starting from element 1)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OP_CUMSUM(offset)  x[i + (offset)] + x[i + (offset) - 1]
#define OP_CUMPROD(offset) x[i + (offset)] * x[i + (offset) - 1]
#define OP_CUMMAX(offset)  x[i + (offset)] > x[i + (offset) - 1] ? x[i + (offset)] : x[i + (offset) - 1];
#define OP_CUMMIN(offset)  x[i + (offset)] < x[i + (offset) - 1] ? x[i + (offset)] : x[i + (offset) - 1];

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Create the functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CUMULATIVEOP(cumsum ,  OP_CUMSUM)
CUMULATIVEOP(cumprod,  OP_CUMPROD)
CUMULATIVEOP(cummax ,  OP_CUMMAX)
CUMULATIVEOP(cummin ,  OP_CUMMIN)

