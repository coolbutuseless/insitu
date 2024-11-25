
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "random64.h"


SEXP insitu_shuffle_fast_(SEXP x_)  {
  
  if (!random64_has_been_initialised) {
    random64_has_been_initialised = 1;
    random64_set_seed();
  }
  
  
  int n = length(x_);
  double *x = REAL(x_);
  for (int i = n-1; i > 0; i--)  {
    int j = (int)random_integer_on_interval((uint64_t)i + 1);
    double tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
  }
  
  return x_;
}

