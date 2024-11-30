

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


SEXP br_round_(SEXP x_, SEXP digits_) {
  double *x = REAL(x_);
  int digits = asInteger(digits_);
  
  static char buf[1024];
  
  for (int i = 0; i < length(x_); i++) {
    snprintf(buf, 1023, "%.*f", digits, x[i]);
    x[i] = atof(buf);
  }

  return x_;
}

