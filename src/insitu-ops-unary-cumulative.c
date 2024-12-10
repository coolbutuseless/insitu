
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
#define CUMULATIVEOP(nm, unaryop)                                      \
void br_##nm##_full(double *x, int len) {                              \
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Array of functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void (*cumulativefunc[4]) (double *x, int len) = {
  br_cumsum_full, br_cumprod_full, br_cummax_full, br_cummin_full
};
  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Global dispatch for cumulative ops
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_op_unary_cumulative_(SEXP op_, SEXP x_) {

  int op = Rf_asInteger(op_);
  if (op < 0 || op > 3) Rf_error("'op' out of range [0, 3]");
  
  void (*func) (double *x, int len) = cumulativefunc[op];

  func(REAL(x_), (int)Rf_length(x_));
  
  return x_;
}


