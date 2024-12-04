
#define R_NO_REMAP

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
  
  double from = Rf_asReal(from_);
  
  if (Rf_length(x_) == 0) {
    return(x_);
  } 
  
  if (Rf_length(x_) == 1) {
    x[0] = from;
    return(x_);
  }
  
  if (Rf_isNull(to_) && Rf_isNull(step_)) {
    for (int i = 0; i < Rf_length(x_); i++) {
      x[i] = from + (double)i;
    }
  } else if (!Rf_isNull(to_)) { 
    double to = Rf_asReal(to_);
    double step = (to - from) / (double)(Rf_length(x_) - 1);
    for (int i = 0; i < Rf_length(x_); i++) {
      x[i] = from + (double)(i * step);
    }
    // Ensure the final value is exactly what the user requested.
    x[Rf_length(x_) - 1] = to;
  } else if (!Rf_isNull(step_)) {
    double step = Rf_asReal(step_);
    for (int i = 0; i < Rf_length(x_); i++) {
      x[i] = from + (double)(i * step);
    }
  } else {
    Rf_error("br_fill_seq_() One of 'to' and 'step' must be non-NULL");
  }
  
  
  return x_;
}

