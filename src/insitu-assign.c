



#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assignment to a vector in-place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_replace_(SEXP x_, SEXP n_, SEXP value_) {
  
  int n = asInteger(n_) - 1;
  
  if (n < 0 || n + length(value_) > length(x_)) {
    error("ins_replace(): out of bounds");
  }
  
  memcpy(REAL(x_) + n, REAL(value_), (size_t)length(value_) * sizeof(double));
  
  return x_;
}



