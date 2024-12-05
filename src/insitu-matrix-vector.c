
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
                     SEXP alpha_, SEXP beta_) {
  
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
  
  if ((Rf_length(x_) != N || Rf_length(y_) != M)) {
    Rf_error("x, y lengths must match ncols(A)");
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

