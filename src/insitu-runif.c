
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "random64.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fill a vector in-place with runif values using R's runif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_runif_(SEXP x_, SEXP min_, SEXP max_) {
  
  if (!random64_has_been_initialised) {
    random64_has_been_initialised = 1;
    random64_set_seed();
  }
  
  
  double min = Rf_asReal(min_);
  double max = Rf_asReal(max_);
  runif_random64_(REAL(x_), Rf_length(x_), min, max);
  
  return x_;
}


