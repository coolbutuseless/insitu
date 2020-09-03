



#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rand-lehmer64.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assignment to a vector in-place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP insitu_fill_(SEXP x_, SEXP value_) {

  if (ALTREP(x_)) {
    error("insitu: ALTREP objects are not supported");
  }

  switch(TYPEOF(x_)) {
  case INTSXP: case LGLSXP: {
    int value = INTEGER(value_)[0];
    int *x = INTEGER(x_);
    for (int i = 0; i < length(x_); ++i) {
      x[i] = value;
    }
  } break;
  case REALSXP: {
    double value = REAL(value_)[0];
    double *x = REAL(x_);
    for (int i = 0; i < length(x_); ++i) {
      x[i] = value;
    }
  } break;
  case STRSXP: {
    SEXP value = STRING_ELT(value_, 0);
    for (int i = 0; i < length(x_); ++i) {
      SET_STRING_ELT(x_, i, value);
    }
  } break;
  default: {
    error("insitu_fill(): type not supported");
  }
  }

  return x_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fill a vector in-place with runif values using R's runif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP insitu_fill_runif_(SEXP x_, SEXP min_, SEXP max_) {

  switch(TYPEOF(x_)) {
  case INTSXP: case LGLSXP: {
    const int min   = isInteger(min_) ? INTEGER(min_)[0] : (int)round(REAL(min_)[0]);
    const int max   = isInteger(max_) ? INTEGER(max_)[0] : (int)round(REAL(max_)[0]);
    const int range = max - min + 1;
    int *x = INTEGER(x_);
    for (int i = 0; i < length(x_); ++i) {
      x[i] = (int)(unif_rand() * range + min);
    }
  } break;
  case REALSXP: {
    const double min   = isReal(min_) ? REAL(min_)[0] : (double)INTEGER(min_)[0];
    const double max   = isReal(max_) ? REAL(max_)[0] : (double)INTEGER(max_)[0];
    const double range = max - min;
    double *x = REAL(x_);
    for (int i = 0; i < length(x_); ++i) {
      x[i] = unif_rand() * range + min;
    }
  } break;
  default: {
    error("insitu_fill_runif(): type not supported");
  }
  }

  return x_;
}


void runif_lehmer64_(double *x, int n, double dmin, double dmax) {

  double drange = dmax - dmin;

  for (int i = 0; i < n; ++i) {
    g_lehmer64_state *= 0xda942042e4dd58b5;

    uint64_t result = g_lehmer64_state >> 64;
    *x++ = (result >> 11) * 0x1.0p-53 * drange + dmin;
  }

}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fill a vector in-place with runif values using R's runif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP insitu_fill_runif_fast_(SEXP x_, SEXP min_, SEXP max_) {

  lehmer64_set_seed();

  switch(TYPEOF(x_)) {
  case INTSXP: case LGLSXP: {
    const int min   = isInteger(min_) ? INTEGER(min_)[0] : (int)round(REAL(min_)[0]);
    const int max   = isInteger(max_) ? INTEGER(max_)[0] : (int)round(REAL(max_)[0]);
    int *x = INTEGER(x_);
    for (int i = 0; i < length(x_); ++i) {
      x[i] = nearlydivisionless(max) + min + 1;
    }
  } break;
  case REALSXP: {
    const double min   = isReal(min_) ? REAL(min_)[0] : (double)INTEGER(min_)[0];
    const double max   = isReal(max_) ? REAL(max_)[0] : (double)INTEGER(max_)[0];
    runif_lehmer64_(REAL(x_), length(x_), min, max);
  } break;
  default: {
    error("insitu_fill_runif_runif(): type not supported");
  }
  }

  return x_;
}


