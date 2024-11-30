
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
SEXP br_copy_(SEXP x_, SEXP y_, SEXP n_, SEXP xi_, SEXP yi_) {
  
  int xi = asInteger(xi_);
  int yi = asInteger(yi_);
  int n  = isNull(n_) ? length(x_) : asInteger(n_);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Account for negative indices
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (xi < 0) {
    xi += length(x_);
  } else {
    --xi; // From R to C indexing
  }
  
  if (yi < 0) {
    yi += length(y_);
  } else {
    --yi; // From R to C indexing
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Sanity Check
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (xi < 0 || yi < 0 || xi >= length(x_) || yi >= length(y_)) {
    error("br_copy() index out of range:  x: %i/%.0f  y: %i/%.0f", 
          asInteger(xi_), (double)length(x_), asInteger(yi_), (double)length(y_));
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Copy
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (length(y_) == 1) {
    // Scalar y
    if (xi + n > length(x_)) {
      error("br_copy() end of copy exceeds size:");
    }
    
    double y = asReal(y_);
    double *x = REAL(x_);
    for (int i = 0; i < n; i++) {
      x[xi + i] = y;
    }
  } else {
    // Vector 'y'
    if (xi + n > length(x_) || yi + n > length(y_)) {
      error("br_copy() end of copy exceeds size:");
    }
    
    memcpy(REAL(x_) + xi, REAL(y_) + yi, (size_t)n * sizeof(double));
  }
  
  
  return x_;
}


#define UNROLL 4

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// "copy_if()" with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_copy_if_vxy_(SEXP x_, SEXP y_, SEXP lgl_) {

  double *x   = REAL(x_);
  double *y   = REAL(y_);
  double *lgl = REAL(lgl_);

  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x = *lgl++ != 0 ? *y : *x; ++x; ++y;
    *x = *lgl++ != 0 ? *y : *x; ++x; ++y;
    *x = *lgl++ != 0 ? *y : *x; ++x; ++y;
    *x = *lgl++ != 0 ? *y : *x; ++x; ++y;
  }
  for (; i< length(x_); i++) {
    *x = *lgl++ != 0 ? *y : *x; ++x; ++y;
  }

  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// "copy_if()" with scalar y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_copy_if_sy_(SEXP x_, SEXP y_, SEXP lgl_) {

  double *x   = REAL(x_);
  double  y   = asReal(y_);
  double *lgl = REAL(lgl_);

  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x = *lgl++ != 0 ? y : *x; ++x;
    *x = *lgl++ != 0 ? y : *x; ++x;
    *x = *lgl++ != 0 ? y : *x; ++x;
    *x = *lgl++ != 0 ? y : *x; ++x;
  }
  for (; i< length(x_); i++) {
    *x = *lgl++ != 0 ? y : *x; ++x;
  }

  return x_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_copy_if_(SEXP x_, SEXP y_, SEXP lgl_) {

  R_xlen_t lx   = length(x_);
  R_xlen_t ly   = length(y_);
  R_xlen_t llgl = length(lgl_);

  if (lx == ly && lx == llgl) {
    return br_copy_if_vxy_(x_, y_, lgl_);
  } else if (ly == 1 && lx == llgl) {
    return br_copy_if_sy_(x_, y_, lgl_);
  }

  error("br_add(): Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);
}


