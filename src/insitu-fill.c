



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
SEXP ins_fill_(SEXP x_, SEXP value_) {
  
  double value = asReal(value_);
  double *x = REAL(x_);
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ = value;
    *x++ = value;
    *x++ = value;
    *x++ = value;
  }
  for (; i< length(x_); i++) {
    *x++ = value;
  }
  
  return x_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fill a vector in-place with runif values using R's runif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_runif_(SEXP x_, SEXP min_, SEXP max_) {
  
  if (!random64_has_been_initialised) {
    random64_has_been_initialised = 1;
    random64_set_seed();
  }
  
  
  double min = asReal(min_);
  double max = asReal(max_);
  runif_random64_(REAL(x_), length(x_), min, max);
  
  return x_;
}


