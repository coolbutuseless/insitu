
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


SEXP br_round_(SEXP x_, SEXP digits_) {
  double *x = REAL(x_);
  int digits = Rf_asInteger(digits_);
  
  static char buf[1024];
  
  for (int i = 0; i < Rf_length(x_); ++i) {
    snprintf(buf, 1023, "%.*f", digits, x[i]);
    x[i] = atof(buf);
  }

  return x_;
}

