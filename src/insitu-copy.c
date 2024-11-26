
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



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assignment to a vector in-place.
// Copy a segment out of 'y' starting at 'yi' into vector 'x' at 'xi'
// Copy 'n' elements
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_copy_from_(SEXP x_, SEXP y_, SEXP xi_, SEXP yi_, SEXP n_) {
  
  int xi = asInteger(xi_) - 1;
  int yi = asInteger(yi_) - 1;
  int n  = asInteger(n_);
  
  if (xi < 0 || yi < 0 || xi >= length(x_) || yi >= length(y_)) {
    error("ins_copy_from() index out of range:  x: %i/%.0f  y: %i/%.0f", 
          asInteger(xi_), (double)length(x_), asInteger(yi_), (double)length(y_));
  }
  
  // Rprintf("ins_copy_from: %i, %i => n = %i\n", xi, yi, n);
  
  if (xi + n > length(x_) || yi + n > length(y_)) {
    error("ins_copy_from() end of copy exceeds size:");
  }
  
  memcpy(REAL(x_) + xi, REAL(y_) + yi, (size_t)n * sizeof(double));
  
  return x_;
}
