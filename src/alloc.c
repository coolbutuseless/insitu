
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


SEXP alloc_n_(SEXP n_) {
  return Rf_allocVector(REALSXP, Rf_asInteger(n_));
}

SEXP alloc_along_(SEXP x_) {
  return Rf_allocVector(REALSXP, Rf_length(x_));
}

SEXP br_zero_(SEXP x_) {
  double *x = REAL(x_);
  memset(x, 0, (size_t)Rf_length(x_) * sizeof(double));
  return x_;
}
