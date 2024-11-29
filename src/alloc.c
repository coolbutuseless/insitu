
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


SEXP alloc_n_(SEXP n_) {
  return allocVector(REALSXP, asInteger(n_));
}

SEXP alloc_for_(SEXP x_) {
  return allocVector(REALSXP, length(x_));
}

SEXP ins_zero_(SEXP x_) {
  double *x = REAL(x_);
  memset(x, 0, (size_t)length(x_) * sizeof(double));
  return x_;
}
