
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "random64.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assignment to a vector in-place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_copy_(SEXP x_, SEXP y_) {
  
  if (length(x_) != length(y_)) {
    error("ins_copy_() length mismatch x=%.0f, y = %.0f", (double)length(x_), (double)length(y_));
  }
  
  memcpy(REAL(x_), REAL(y_), (size_t)length(x_) * sizeof(double));
  
  return x_;
}

