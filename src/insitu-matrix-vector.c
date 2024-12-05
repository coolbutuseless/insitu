
#define R_NO_REMAP
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
                     SEXP alpha_, SEXP beta_, SEXP ta_) {
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isMatrix(A_)) {
    Rf_error("br_mat_mat_mul_(): A must be a matrix");
  }
  
  bool ta = Rf_asLogical(ta_);
  
  int M = Rf_nrows(A_);
  int N = Rf_ncols(A_);
  
  if (M == 0 || N == 0) {
    Rf_error("Dimensions of zero are not supported");
  }
  
  if (!ta && ((Rf_length(x_) != N || Rf_length(y_) != M))) {
    Rf_error("x, y are non-conformable with 'A'");
  } 
  
  if (ta && (Rf_length(x_) != M || Rf_length(y_) != N)) {
    Rf_error("x, y are non-conformable with 't(A)'");
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *A = REAL(A_);
  double *x = REAL(x_);
  double *y = REAL(y_);
  double alpha = Rf_asReal(alpha_);
  double beta  = Rf_asReal(beta_);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Transposition?
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = ta ? "T" : "N"; 
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
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_vec_mul_asq_(SEXP A_, SEXP x_, SEXP alpha_, SEXP ta_) {
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isMatrix(A_)) {
    Rf_error("br_mat_mat_mul_(): A must be a matrix");
  }
  
  int M = Rf_nrows(A_);
  int N = Rf_ncols(A_);
  
  if (M == 0 || N == 0) {
    Rf_error("Dimensions of zero are not supported");
  }
  
  if (M != N) {
    Rf_error("'A' matrix must be square");
  }
  
  if (Rf_length(x_) != N) {
    Rf_error("x, is non-conformable with 'A'");
  } 
  
  double *y = malloc(N * sizeof(double));
  if (y == NULL) {
    Rf_error("'y' allocation failed");
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *A = REAL(A_);
  double *x = REAL(x_);
  double alpha = Rf_asReal(alpha_);
  double beta  = 0;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Transposition?
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = Rf_asLogical(ta_) ? "T" : "N"; 
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
  
  memcpy(x, y, N * sizeof(double));
  free(y);
  return(x_);
}

