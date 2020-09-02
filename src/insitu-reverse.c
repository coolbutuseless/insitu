



#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reverse a vector in place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP insitu_reverse_(SEXP x_) {

  if (ALTREP(x_)) {
    error("insitu: ALTREP objects are not supported");
  }

  switch(TYPEOF(x_)) {
  case INTSXP: case LGLSXP: {
    int i = length(x_) - 1;
    int j = 0;
    int *x = INTEGER(x_);
    while(i > j)
    {
      int temp = x[i];
      x[i] = x[j];
      x[j] = temp;
      i--;
      j++;
    }
  } break;
  case REALSXP: {
    int i = length(x_) - 1;
    int j = 0;
    double *x = REAL(x_);
    while(i > j)
    {
      double temp = x[i];
      x[i] = x[j];
      x[j] = temp;
      i--;
      j++;
    }
  } break;
  case STRSXP: {
    int i = length(x_) - 1;
    int j = 0;
    while(i > j)
    {
      SEXP tmp = STRING_ELT(x_, i);
      SET_STRING_ELT(x_, i, STRING_ELT(x_, j));
      SET_STRING_ELT(x_, j, tmp);
      i--;
      j++;
    }
  } break;
  default: {
    error("insitu_reverse(): type not supported");
  }
  }

  return x_;
}


