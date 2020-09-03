
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand-xoshiro256p.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fisher-Yates shuffling using R's RNG for randomness
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP insitu_shuffle_(SEXP x_)  {

  if (ALTREP(x_)) {
    error("insitu: ALTREP objects are not supported");
  }

  switch(TYPEOF(x_)) {
  case INTSXP: {
    int n = length(x_);
    int *x = INTEGER(x_);
    for (int i = n-1; i > 0; i--)  {
      int j = (int)round(unif_rand() * i);
      int tmp = x[i];
      x[i] = x[j];
      x[j] = tmp;
    }
  } break;
  case REALSXP: {
    int n = length(x_);
    double *x = REAL(x_);
    for (int i = n-1; i > 0; i--)  {
      int j = (int)round(unif_rand() * i);
      double tmp = x[i];
      x[i] = x[j];
      x[j] = tmp;
    }
  } break;
  case STRSXP: {
    int n = length(x_);
    for (int i = n-1; i > 0; i--)  {
      int j = (int)round(unif_rand() * i);
      SEXP tmp = STRING_ELT(x_, i);
      SET_STRING_ELT(x_, i, STRING_ELT(x_, j));
      SET_STRING_ELT(x_, j, tmp);
    }
  } break;
  default: {
    error("insitu_shuffle(): type not handled");
  }
  }


  return x_;
}









