
#define USE_FC_LEN_T

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// #ifdef USE_NEW_ACCELERATE
// # define ACCELERATE_NEW_LAPACK
// // avoid conflicts over COMPLEX
// # define USE_NON_APPLE_STANDARD_DATATYPES 0
// # include <Accelerate/Accelerate.h>
// # define FCONE
// # pragma clang diagnostic ignored "-Wincompatible-pointer-types"
// #else
// #include <R_ext/BLAS.h>
// #endif

#include <R_ext/BLAS.h>

#ifndef FCONE
# define FCONE
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Alloc matrix of a given size
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP alloc_matrix_(SEXP nrow_, SEXP ncol_) {
  return allocMatrix(REALSXP, asInteger(nrow_), asInteger(ncol_));
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Alloc matrix for the result 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP alloc_matrix_mul_(SEXP A_, SEXP B_) {
  
  if (!isMatrix(A_) || !isMatrix(B_)) {
    error("Both A and B must be matrices");
  }
  
  int nrow = Rf_nrows(A_);
  int ncol = Rf_ncols(B_);
  
  if (nrow == 0 || ncol == 0 || 
      Rf_ncols(A_) == 0 || Rf_nrows(B_) == 0) {
    error("Dimension = 0 is not supported");
  }
  
  return allocMatrix(REALSXP, nrow, ncol);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mul_mat_mat_(SEXP C_, SEXP A_, SEXP B_, 
                     SEXP alpha_, SEXP beta_, 
                     SEXP A_transpose_, SEXP B_transpose_) {
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!isMatrix(A_) || !isMatrix(B_) || !isMatrix(C_)) {
    error("br_mul_mat_mat_(): A, B & C must all be matrices");
  }
  
  // A = M * k
  // B = k * N
  int M = Rf_nrows(A_);
  int N = Rf_ncols(B_);
  int k = Rf_ncols(A_);

  if (Rf_nrows(B_) != k) {
    error("A, B are non-conformable");
  }
  
  if (M == 0 || N == 0 || k == 0) {
    error("Dimensions of zero are not supported");
  }
    
  if (Rf_nrows(C_) != M || Rf_ncols(C_) != N) {
    error("C not dimensioned for holding A * B");
  }  
    
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *A = REAL(A_);
  double *B = REAL(B_);
  double *C = REAL(C_);
  double alpha = asReal(alpha_);
  double beta  = asReal(beta_);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Transposition?
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = "N"; // Default: Not transposed
  char *B_op = "N"; // Default: Not transposed
  int LDA = M;
  int LDB = k;
  int LDC = M;
  
  if (asLogical(A_transpose_)) {
    warning("transponse not tested");
    A_op = "T";
    LDA = k;
  }


  if (asLogical(B_transpose_)) {
    warning("transponse not tested");
    B_op = "T";
    LDB = N;
  }
  
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



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mul_mat_vec_(SEXP y_, SEXP A_, SEXP x_, 
                     SEXP alpha_, SEXP beta_, 
                     SEXP A_transpose_) {
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!isMatrix(A_)) {
    error("br_mul_mat_mat_(): A, B & C must all be matrices");
  }
  
  // A = M * k
  // B = k * N
  int M = Rf_nrows(A_);
  int N = Rf_ncols(A_);
  
  if (M == 0 || N == 0) {
    error("Dimensions of zero are not supported");
  }
  
  if (length(x_) != N || length(y_) != M) {
    error("x, y lengths must match ncols(A)");
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *A = REAL(A_);
  double *x = REAL(x_);
  double *y = REAL(y_);
  double alpha = asReal(alpha_);
  double beta  = asReal(beta_);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Transposition?
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = "N"; // Default: Not transposed
  int LDA  = M;
  int INCX = 1;
  int INCY = 1;
  
  if (asLogical(A_transpose_)) {
    warning("transponse not tested");
    A_op = "T";
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Call
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  F77_CALL(dgemv)(
      A_op,
      &M,
      &N,
      &alpha,
      A,
      &LDA,
      x,
      &INCX,
      &beta,
      y,
      &INCY FCONE
  );
  
  return(y_);
}

