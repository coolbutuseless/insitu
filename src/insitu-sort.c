

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// qsort() helper functions for 'int' vectors
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int int_cmpfunc_inc (const void * a, const void * b) {
  const int *aa = a;
  const int *bb = b;
  return (*aa > *bb) - (*aa < *bb);
}

int int_cmpfunc_dec (const void * a, const void * b) {
  const int *aa = a;
  const int *bb = b;
  return (*aa < *bb) - (*aa > *bb);
}




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
SEXP insitu_sort_(SEXP x_, SEXP decreasing_) {

  if (ALTREP(x_)) {
    error("insitu: ALTREP objects are not supported");
  }

  switch(TYPEOF(x_)) {
  case INTSXP: {
    qsort(INTEGER(x_), (size_t)length(x_), sizeof(int), asLogical(decreasing_) ? int_cmpfunc_dec : int_cmpfunc_inc);
  } break;
  case REALSXP: {
    qsort(REAL(x_), (size_t)length(x_), sizeof(double), asLogical(decreasing_) ? dbl_cmpfunc_dec : dbl_cmpfunc_inc);
  } break;
  default:
    error("insitu_sort(): type not supported");
  }


  return x_;
}
