

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "random64.h"


SEXP set_seed_random64_(void) {
  random64_set_seed();
  return R_NilValue;
}

