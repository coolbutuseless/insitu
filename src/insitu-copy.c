
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "random64.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assignment to a vector in-place.
// Copy a segment out of 'y' starting at 'yi' into vector 'x' at 'xi'
// Copy 'n' elements
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_copy_(SEXP x_, SEXP y_, SEXP n_, SEXP xi_, SEXP yi_) {
  
  int xi = asInteger(xi_) - 1;
  int yi = asInteger(yi_) - 1;
  int n  = isNull(n_) ? length(x_) : asInteger(n_);
  
  if (xi < 0 || yi < 0 || xi >= length(x_) || yi >= length(y_)) {
    error("ins_copy() index out of range:  x: %i/%.0f  y: %i/%.0f", 
          asInteger(xi_), (double)length(x_), asInteger(yi_), (double)length(y_));
  }
  
  
  if (length(y_) == 1) {
    // Scalar y
    double y = asReal(y_);
    double *x = REAL(x_);
    for (int i = 0; i < n; i++) {
      x[xi + i] = y;
    }
  } else {
    // Vector 'y'
    if (xi + n > length(x_) || yi + n > length(y_)) {
      error("ins_copy() end of copy exceeds size:");
    }
    
    memcpy(REAL(x_) + xi, REAL(y_) + yi, (size_t)n * sizeof(double));
  }
  
  
  return x_;
}
