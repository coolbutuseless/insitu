
#define R_NO_REMAP
#define USE_FC_LEN_T

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdbool.h>
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
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_mat_mul_full_(SEXP C_, SEXP A_, SEXP B_, 
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

