

#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// qsort() helper functions for 'dbl' vectors
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int dbl_cmpfunc_inc (const void * a, const void * b) {
  const double *aa = a;
  const double *bb = b;
  return (*aa > *bb) - (*aa < *bb);
}

int dbl_cmpfunc_dec (const void * a, const void * b) {
  const double *aa = a;
  const double *bb = b;
  return (*aa < *bb) - (*aa > *bb);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sort a numeric/integer vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_sort_(SEXP x_, SEXP decreasing_) {

  qsort(REAL(x_), (size_t)Rf_length(x_), sizeof(double), Rf_asLogical(decreasing_) ? dbl_cmpfunc_dec : dbl_cmpfunc_inc);

  return x_;
}
