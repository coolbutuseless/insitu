
#define R_NO_REMAP
#define USE_FC_LEN_T

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


#include <R_ext/BLAS.h>
#ifndef FCONE
# define FCONE
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat44_mul(double *A, double *B) {
  
  double C[16];
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Setup arguments to dgemm()
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = "N"; 
  char *B_op = "N"; 
  
  // A = M * k
  // B = k * N
  int M = 4;
  int N = 4;
  int k = 4;
  
  int LDA = 4;
  int LDB = 4;
  int LDC = 4;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double alpha = 1;
  double beta  = 0;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Call
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  F77_CALL(dgemm)(
      A_op,
      B_op,
      &M,
      &N,
      &k,
      &alpha,
      A,
      &LDA,
      B,
      &LDB,
      &beta,
      C,
      &LDC FCONE FCONE
  );

  memcpy(A, C, 16 * sizeof(double));
}





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
// Add translation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_add_translate_(SEXP mat_, SEXP x_, SEXP y_, SEXP z_) {
  
  assert_mat44(mat_);
  double *mat = REAL(mat_);
  
  mat[I(0, 3)] += Rf_asReal(x_);
  mat[I(1, 3)] += Rf_asReal(y_);
  mat[I(2, 3)] += Rf_asReal(z_);
  
  return mat_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Add scaling
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_add_scale_(SEXP mat_, SEXP x_, SEXP y_, SEXP z_) {
  
  assert_mat44(mat_);
  double *mat = REAL(mat_);
  
  mat[I(0, 0)] *= Rf_asReal(x_);
  mat[I(1, 1)] *= Rf_asReal(y_);
  mat[I(2, 2)] *= Rf_asReal(z_);
  
  return mat_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Add a rotation around the z axis
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_add_rotate_z_(SEXP mat_, SEXP theta_) {
  
  static double r[16];
  assert_mat44(mat_);

  // setup rotation matrix
  double theta = Rf_asReal(theta_);
  memset(r, 0, 16 * sizeof(double));
  r[I(0, 0)] =  cos(theta);
  r[I(0, 1)] = -sin(theta);
  r[I(1, 0)] =  sin(theta);
  r[I(1, 1)] =  cos(theta);
  r[I(2, 2)] = 1;
  r[I(3, 3)] = 1;
  
  // do the multiplication
  double *mat = REAL(mat_);
  
  mat44_mul(mat, r);
  
  return mat_;
}








