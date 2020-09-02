
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand-lehmer64.h"



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


SEXP insitu_shuffle_fast_(SEXP x_)  {

  if (ALTREP(x_)) {
    error("insitu: ALTREP objects are not supported");
  }

  lehmer64_set_seed();


  switch(TYPEOF(x_)) {
  case INTSXP: {
    int n = length(x_);
    int *x = INTEGER(x_);
    for (int i = n-1; i > 0; i--)  {
      int j = (int)nearlydivisionless(i + 1);
      int tmp = x[i];
      x[i] = x[j];
      x[j] = tmp;
    }
  } break;
  case REALSXP: {
    int n = length(x_);
    double *x = REAL(x_);
    for (int i = n-1; i > 0; i--)  {
      int j = (int)nearlydivisionless(i + 1);
      double tmp = x[i];
      x[i] = x[j];
      x[j] = tmp;
    }
  } break;
  case STRSXP: {
    int n = length(x_);
    for (int i = n-1; i > 0; i--)  {
      int j = (int)nearlydivisionless(i + 1);
      SEXP tmp = STRING_ELT(x_, i);
      SET_STRING_ELT(x_, i, STRING_ELT(x_, j));
      SET_STRING_ELT(x_, j, tmp);
    }
  } break;
  default: {
    error("insitu_shuffle_fast(): type not handled");
  }
  }

  return x_;
}


//for (int i = 0; i < length(value_); ++i) {
//  SET_STRING_ELT(x_, n + i, STRING_ELT(value_, i));
//}









