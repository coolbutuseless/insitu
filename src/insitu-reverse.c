

#define R_NO_REMAP


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reverse a vector in place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_rev_(SEXP x_) {
  
  int i = Rf_length(x_) - 1;
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
  
  return x_;
}


