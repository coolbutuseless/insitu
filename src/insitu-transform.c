
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
SEXP mat44_mul_(SEXP C_, SEXP A_, SEXP B_, 
                SEXP alpha_, SEXP beta_, 
                SEXP ta_, SEXP tb_) {
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions are conformable
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isMatrix(A_) || !Rf_isMatrix(B_) || !Rf_isMatrix(C_)) {
    Rf_error("br_mat_mat_mul_(): A, B & C must all be matrices");
  }
  
  bool ta = Rf_asLogical(ta_);
  bool tb = Rf_asLogical(tb_);
  
  int ka = ta ? Rf_nrows(A_) : Rf_ncols(A_);
  int kb = tb ? Rf_ncols(B_) : Rf_nrows(B_);
  
  if (ka != kb) {
    Rf_error("A, B are non-conformable");
  }
  
  int asize = ta ? Rf_ncols(A_) : Rf_nrows(A_);
  int bsize = tb ? Rf_nrows(B_) : Rf_ncols(B_);
  
  if (Rf_nrows(C_) != asize || Rf_ncols(C_) != bsize) {
    Rf_error("C not dimensioned for holding A * B");
  }  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Setup arguments to dgemm()
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = ta ? "T" : "N"; 
  char *B_op = tb ? "T" : "N"; 
  
  // A = M * k
  // B = k * N
  int M = ta ? Rf_ncols(A_) : Rf_nrows(A_);
  int N = tb ? Rf_nrows(B_) : Rf_ncols(B_);
  int k = ta ? Rf_nrows(A_) : Rf_ncols(A_);
  
  int LDA = ta ? k : M;
  int LDB = tb ? N : k;
  int LDC = M;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *A = REAL(A_);
  double *B = REAL(B_);
  double *C = REAL(C_);
  double alpha = Rf_asReal(alpha_);
  double beta  = Rf_asReal(beta_);
  
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
  
  return(C_);
}


void mat44_mul(double *A, double *B) {
  
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








