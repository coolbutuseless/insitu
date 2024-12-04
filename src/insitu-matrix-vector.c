
#define USE_FC_LEN_T

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <R_ext/BLAS.h>

#ifndef FCONE
# define FCONE
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_vec_mul_(SEXP y_, SEXP A_, SEXP x_, 
                     SEXP alpha_, SEXP beta_) {
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!isMatrix(A_)) {
    error("br_mat_mat_mul_(): A must be a matrix");
  }
  
  int M = Rf_nrows(A_);
  int N = Rf_ncols(A_);
  
  if (M == 0 || N == 0) {
    error("Dimensions of zero are not supported");
  }
  
  if ((length(x_) != N || length(y_) != M)) {
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
  char *A_op = "N"; 
  int LDA  = M;
  int INCX = 1;
  int INCY = 1;
  
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



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Mat-vec multiplicatin when A is square. 
// This means that 'x' input is the same size as the output and will 
// therefore be overwritten to contain the result
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_vec_mul_asq_(SEXP A_, SEXP x_, SEXP alpha_) {
  
  static double *y = NULL;
  static int ysize = -1;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!isMatrix(A_)) {
    error("br_mat_mat_mul_(): A, B & C must all be matrices");
  }
  
  // A = M * k
  // B = k * N
  int M = Rf_nrows(A_);
  int N = Rf_ncols(A_);
  
  if (M == 0 || N == 0) {
    error("Dimensions of zero are not supported");
  }
  
  if (M != N) {
    error("'A' must be a square matrix");
  }
  
  if (length(x_) != N) {
    error("Dimensions of A and x non-conformal");
  }
  
  int ysize_desired = M;
  if (y == NULL) {
    y = malloc((size_t)M * sizeof(double));
  } else if (ysize_desired > ysize) {
    y = realloc(y, (size_t)M * sizeof(double));
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *A = REAL(A_);
  double *x = REAL(x_);
  double alpha = asReal(alpha_);
  double beta  = 0;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Transposition?
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = "N"; // Default: Not transposed
  int LDA  = M;
  int INCX = 1;
  int INCY = 1;
  
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
  
  memcpy(REAL(x_), y, (size_t)M * sizeof(double));
  return(x_);
}

