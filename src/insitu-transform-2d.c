
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
// BLAS matrix multiply
// TODO: just roll a simple nested loop and benchmark.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat33_mul(double *A, double *B) {
  
  double C[9];
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Setup arguments to dgemm()
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = "N"; 
  char *B_op = "N"; 
  
  // A = M * k
  // B = k * N
  int M = 3;
  int N = 3;
  int k = 3;
  
  int LDA = 3;
  int LDB = 3;
  int LDC = 3;
  
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

  memcpy(B, C, 9 * sizeof(double));
}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Accessor for 2D matrix by row (r) and column (c)   [0 indexed]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define I(r, c) ((c) * 3 + (r))


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assert that SEXP is a 4x4 numeric matrix
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static inline void assert_mat33(SEXP mat_) {
  
  if (Rf_isMatrix(mat_) && Rf_isReal(mat_) && Rf_nrows(mat_) == 3 && Rf_ncols(mat_) == 3) {
    return;
  }
  
  Rf_error("assert_mat33(): Argument is not a 4x4 numeric matrix");
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reset a transformation matrix back to the identity
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf2_reset_(SEXP mat_) {
  
  assert_mat33(mat_);
  double *mat = REAL(mat_);
  memset(mat, 0, 9 * sizeof(double));
  
  mat[I(0, 0)] = 1;
  mat[I(1, 1)] = 1;
  mat[I(2, 2)] = 1;
  
  return mat_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Add translation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf2_add_translate_(SEXP mat_, SEXP x_, SEXP y_) {
  
  static double t[9]  = { 1, 0, 0, 
                          0, 1, 0,
                          0, 0, 1 };
  assert_mat33(mat_);
  
  // setup transformation matrix
  t[I(0, 2)] = Rf_asReal(x_);
  t[I(1, 2)] = Rf_asReal(y_);
  
  
  // do the multiplication
  double *mat = REAL(mat_);
  mat33_mul(t, mat);
  
  
  return mat_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Add scaling
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf2_add_scale_(SEXP mat_, SEXP x_, SEXP y_) {
  
  static double t[9]  = { 1, 0, 0, 
                          0, 1, 0,
                          0, 0, 1 };
  assert_mat33(mat_);
  
  // setup transformation matrix
  t[I(0, 0)] = Rf_asReal(x_);
  t[I(1, 1)] = Rf_asReal(y_);
  
  // do the multiplication
  double *mat = REAL(mat_);
  mat33_mul(t, mat);
  
  
  return mat_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Add a rotation around the z axis
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf2_add_rotate_(SEXP mat_, SEXP theta_) {
  
  static double t[9]  = { 1, 0, 0, 
                          0, 1, 0,
                          0, 0, 1 };
  assert_mat33(mat_);
  
  // setup transformation matrix
  double theta = Rf_asReal(theta_);
  t[I(0, 0)] =  cos(theta);
  t[I(0, 1)] = -sin(theta);
  t[I(1, 0)] =  sin(theta);
  t[I(1, 1)] =  cos(theta);
  
  // do the multiplication
  double *mat = REAL(mat_);
  mat33_mul(t, mat);
  
  
  return mat_;
}








