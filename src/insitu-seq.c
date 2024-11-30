
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "random64.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fill the vector with a sequence
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_fill_seq_(SEXP x_, SEXP from_, SEXP to_, SEXP step_) {
  
  double *x = REAL(x_);
  
  double from = asReal(from_);
  
  if (length(x_) == 0) {
    return(x_);
  } 
  
  if (length(x_) == 1) {
    x[0] = from;
    return(x_);
  }
  
  if (isNull(to_) && isNull(step_)) {
    for (int i = 0; i < length(x_); i++) {
      x[i] = from + (double)i;
    }
  } else if (!isNull(to_)) { 
    double to = asReal(to_);
    double step = (to - from) / (double)(length(x_) - 1);
    for (int i = 0; i < length(x_); i++) {
      x[i] = from + (double)(i * step);
    }
    // Ensure the final value is exactly what the user requested.
    x[length(x_) - 1] = to;
  } else if (!isNull(step_)) {
    double step = asReal(step_);
    for (int i = 0; i < length(x_); i++) {
      x[i] = from + (double)(i * step);
    }
  } else {
    error("br_fill_seq_() One of 'to' and 'step' must be non-NULL");
  }
  
  
  return x_;
}

