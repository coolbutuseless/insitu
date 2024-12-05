
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "random64.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Accessor for 2D matrix by row (r) and column (c)   [0 indexed]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define I(r, c) ((c) * 4 + (r))


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assert that SEXP is a 4x4 numeric matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static inline void assert_mat44(SEXP mat_) {
  
  if (Rf_isMatrix(mat_) && Rf_isReal(mat_) && Rf_nrows(mat_) == 4 && Rf_ncols(mat_) == 4) {
    return;
  }
  
  Rf_error("Argument is not a 4x4 numeric matrix");
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reset a transformation matrix back to the identity
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_reset_(SEXP mat_) {
  
  assert_mat44(mat_);
  double *mat = REAL(mat_);
  memset(mat, 0, 16 * sizeof(double));
  
  mat[I(0, 0)] = 1;
  mat[I(1, 1)] = 1;
  mat[I(2, 2)] = 1;
  mat[I(3, 3)] = 1;
  
  return mat_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reset a transformation matrix back to the identity
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_add_translation_(SEXP mat_, SEXP x_, SEXP y_, SEXP z_) {
  
  assert_mat44(mat_);
  double *mat = REAL(mat_);
  
  mat[I(0, 3)] += Rf_asReal(x_);
  mat[I(1, 3)] += Rf_asReal(y_);
  mat[I(2, 3)] += Rf_asReal(z_);
  
  return mat_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reset a transformation matrix back to the identity
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_add_scale_(SEXP mat_, SEXP x_, SEXP y_, SEXP z_) {
  
  assert_mat44(mat_);
  double *mat = REAL(mat_);
  
  mat[I(0, 0)] *= Rf_asReal(x_);
  mat[I(1, 1)] *= Rf_asReal(y_);
  mat[I(2, 2)] *= Rf_asReal(z_);
  
  return mat_;
}

