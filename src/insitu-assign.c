



#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assignment to a vector in-place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP insitu_replace_(SEXP x_, SEXP n_, SEXP value_) {

  if (ALTREP(x_)) {
    error("insitu: ALTREP objects are not supported");
  }

  int n = isReal(n_) ? (int)asReal(n_) : asInteger(n_);
  n--;

  if (n < 0 || n + length(value_) > length(x_)) {
    error("insitu_replace(): out of bounds");
  }

  if (TYPEOF(x_) != TYPEOF(value_)) {
    error("insitu_replace(): Type mismatch");
  }

  switch(TYPEOF(x_)) {
  case INTSXP: case LGLSXP: {
    memcpy(INTEGER(x_) + n, INTEGER(value_), length(value_) * sizeof(int));
  } break;
  case REALSXP: {
    memcpy(REAL(x_) + n, REAL(value_), length(value_) * sizeof(double));
  } break;
  case STRSXP: {
    for (int i = 0; i < length(value_); ++i) {
      SET_STRING_ELT(x_, n + i, STRING_ELT(value_, i));
    }
  } break;
  default: {
    error("insitu_replace(): type not supported");
  }
  }

  return x_;
}



