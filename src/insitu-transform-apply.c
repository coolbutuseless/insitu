
#define R_NO_REMAP
#define USE_FC_LEN_T

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils-data-frame.h"


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



SEXP tf_df_apply_(SEXP A_, SEXP B_);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Special case:
//  - B is square
//  - C is not specified by the user
//  - Result is written back into A
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_apply_(SEXP A0_, SEXP B_) {

  if (Rf_inherits(A0_, "data.frame")) {
    return tf_df_apply_(A0_, B_);
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions are conformable
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isMatrix(A0_) || !Rf_isMatrix(B_)) {
    Rf_error("tf_apply_(): A & B must be matrices");
  }
  
  if (Rf_nrows(B_) != Rf_ncols(B_)) {
    Rf_error("tf_apply_(): 'B' must be a square matrix");
  }  
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // 2d or 3d?
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  int dim = Rf_nrows(B_) - 1;
  if (dim != 2 && dim != 3) {
    Rf_error("tf_apply_(): Only 2D/3D currently supported (%i)", dim);
  }
  
  if (Rf_ncols(A0_) < dim) {
    Rf_error("Need at least 2 columns for 2D transform, and 3 Columns for 3D transform");
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Pack data.frame into a matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  int Arows = Rf_nrows(A0_);
  int Acols = dim + 1; // coordinates + 'd'

  double *A = malloc(Arows * Acols * sizeof(double));
  if (A == NULL) Rf_error("tf_apply_(): Could not allocate 'A'");
  
  // Copy the coordinates we weree given
  memcpy(A, REAL(A0_), dim * Arows * sizeof(double));
  
  // Set the homogenous coordinate 'w' to '1'
  for (int i = 0; i < Arows; ++i) {
    A[dim * Arows + i] = 1;
  }
  
  // for (int row = 0; row < Arows; ++row) {
  //   Rprintf("A[%i] ", row);
  //   for (int col = 0; col < Acols; ++col) {
  //     Rprintf("%.1f ", A[col * Arows + row]);
  //   }
  //   Rprintf("\n");
  // }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Prep for call
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  bool ta = false;
  bool tb = true;
  
  int ka = ta ? Arows        : Acols;
  int kb = tb ? Rf_ncols(B_) : Rf_nrows(B_);
  
  if (ka != kb) {
    Rf_error("tf_apply_(): A, B are non-conformable");
  }
  
  int Crows = ta ? Acols        : Arows;
  int Ccols = tb ? Rf_nrows(B_) : Rf_ncols(B_);
  
  size_t Csize = (size_t)Crows * (size_t)Ccols * sizeof(double);
  double *C = malloc(Csize);
  if (C == NULL) {
    Rf_error("tf_apply_(): Failed to allocate 'C'");
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Setup arguments to dgemm()
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = ta ? "T" : "N"; 
  char *B_op = tb ? "T" : "N"; 
  
  // A = M * k
  // B = k * N
  int M = ta ? Acols        : Arows;
  int N = tb ? Rf_nrows(B_) : Rf_ncols(B_);
  int k = ta ? Arows        : Acols;
  
  int LDA = ta ? k : M;
  int LDB = tb ? N : k;
  int LDC = M;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *B = REAL(B_);
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
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Copy results in 'C' directly into A0.
  // Ignore the homogenous coordinate
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  memcpy(REAL(A0_), C, Arows * dim * sizeof(double));
  free(C);
  return(A0_);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Special case:
//  - A is a data.frame with (x,y) or (x,y,z) columns
//  - B is square
//  - C is not specified by the user
//  - Result is written back into A
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP tf_df_apply_(SEXP df_, SEXP B_) {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Confirm dimensions are conformable
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isMatrix(B_)) {
    Rf_error("tf_df_apply_(): B must be a matrix");
  }
  
  if (Rf_nrows(B_) != Rf_ncols(B_)) {
    Rf_error("tf_df_apply_(): 'B' must be a square matrix");
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // 2d or 3d?
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  int dim = Rf_nrows(B_) - 1;
  if (dim != 2 && dim != 3) {
    Rf_error("tf_df_apply_(): Only 2D/3D currently supported (%i)", dim);
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Pack data.frame into a matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_inherits(df_, "data.frame")) {
    Rf_error("tf_df_apply_(): 'A' must be a data.frame or matrix");
  }
  int Arows = Rf_length(VECTOR_ELT(df_, 0));
  int Acols = dim + 1; // coordinates + 'd'
  
  SEXP x_ = get_df_col_or_error(df_, "x");
  SEXP y_ = get_df_col_or_error(df_, "y");
  SEXP z_ = R_NilValue;
  if (dim == 3) {
    z_ = get_df_col_or_error(df_, "z");
  }
  
  double *A = malloc(Arows * Acols * sizeof(double));
  if (A == NULL) Rf_error("tf_df_apply_(): Could not allocate 'A'");
  memcpy(A + 0 * Arows, REAL(x_), Arows * sizeof(double));
  memcpy(A + 1 * Arows, REAL(y_), Arows * sizeof(double));
  if (dim == 3) {
    memcpy(A + 2 * Arows, REAL(z_), Arows * sizeof(double));
  }

  
  for (int i = 0; i < Arows; ++i) {
    A[dim * Arows + i] = 1;
  }
  
  // for (int row = 0; row < Arows; ++row) {
  //   Rprintf("A[%i] ", row);
  //   for (int col = 0; col < Acols; ++col) {
  //     Rprintf("%.1f ", A[col * Arows + row]);
  //   }
  //   Rprintf("\n");
  // }
  
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Process
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  bool ta = false;
  bool tb = true;
  
  int ka = ta ? Arows        : Acols;
  int kb = tb ? Rf_ncols(B_) : Rf_nrows(B_);
  
  if (ka != kb) {
    Rf_error("tf_df_apply_(): A, B are non-conformable");
  }
  
  int Crows = ta ? Acols        : Arows;
  int Ccols = tb ? Rf_nrows(B_) : Rf_ncols(B_);
  
  size_t Csize = (size_t)Crows * (size_t)Ccols * sizeof(double);
  double *C = malloc(Csize);
  if (C == NULL) {
    Rf_error("tf_df_apply_(): Failed to allocate 'C'");
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Setup arguments to dgemm()
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *A_op = ta ? "T" : "N"; 
  char *B_op = tb ? "T" : "N"; 
  
  // A = M * k
  // B = k * N
  int M = ta ? Acols        : Arows;
  int N = tb ? Rf_nrows(B_) : Rf_ncols(B_);
  int k = ta ? Arows        : Acols;
  
  int LDA = ta ? k : M;
  int LDB = tb ? N : k;
  int LDC = M;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get pointers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  double *B = REAL(B_);
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
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Copy results in 'C' directly into the 'df_' columns
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  memcpy(REAL(x_), C + 0 * Crows, Crows * sizeof(double));
  memcpy(REAL(y_), C + 1 * Crows, Crows * sizeof(double));
  if (dim == 3) {
    memcpy(REAL(z_), C + 2 * Crows, Crows * sizeof(double));
  }
  
  
  free(C);
  free(A);
  return(df_);
}











