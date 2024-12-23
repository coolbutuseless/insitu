

#define R_NO_REMAP


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_col_get_(SEXP mat_, SEXP i_, SEXP vec_) {
  
  int rows = Rf_nrows(mat_);
  int cols = Rf_ncols(mat_);
  int i    = Rf_asInteger(i_) - 1; // Convert to C 0-indexing
  
  if (Rf_length(vec_) != rows) {
    Rf_error("'vec' length does not match number of matrix rows. %i != %i", 
             Rf_length(vec_), rows);
  }
  
  if (i < 0 || i >= cols) {
    Rf_error("'i' out of range [0, %i]", cols);
  }
  
  double *mat = REAL(mat_);
  double *vec = REAL(vec_);
  
  memcpy(vec, mat + i * rows, rows * sizeof(double));
  
  return vec_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_col_set_(SEXP mat_, SEXP i_, SEXP vec_) {
  
  int rows = Rf_nrows(mat_);
  int cols = Rf_ncols(mat_);
  int i    = Rf_asInteger(i_) - 1; // Convert to C 0-indexing
  
  if (i < 0 || i >= cols) {
    Rf_error("'i' out of range [0, %i]", cols);
  }
  
  if (Rf_length(vec_) == 1) {
    double *mat = REAL(mat_);
    double val = Rf_asReal(vec_);
    for (int row = 0; row < rows; ++row) {
      mat[i * rows + row] = val;
    }
  } else if (Rf_length(vec_) == rows) {
    double *mat = REAL(mat_);
    double *vec = REAL(vec_);
    memcpy(mat + i * rows, vec, rows * sizeof(double));
  } else {
    Rf_error("'vec' length does not match number of matrix rows. %i != %i", 
             Rf_length(vec_), rows);
  }
  
  
  return mat_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_row_get_(SEXP mat_, SEXP i_, SEXP vec_) {
  
  int rows = Rf_nrows(mat_);
  int cols = Rf_ncols(mat_);
  int i    = Rf_asInteger(i_) - 1; // Convert to C 0-indexing
  
  if (Rf_length(vec_) != cols) {
    Rf_error("'vec' length does not match number of matrix cols. %i != %i", 
             Rf_length(vec_), cols);
  }
  
  if (i < 0 || i >= rows) {
    Rf_error("'i' out of range [0, %i]", rows);
  }
  
  double *mat = REAL(mat_);
  double *vec = REAL(vec_);
  
  for (int col = 0; col < cols; ++col) {
    vec[col] = mat[i + col * rows];
  }
  
  return vec_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_row_set_(SEXP mat_, SEXP i_, SEXP vec_) {
  
  int rows = Rf_nrows(mat_);
  int cols = Rf_ncols(mat_);
  int i    = Rf_asInteger(i_) - 1; // Convert to C 0-indexing
  
  if (i < 0 || i >= rows) {
    Rf_error("'i' out of range [0, %i]", rows);
  }
  
  if (Rf_length(vec_) == 1) {
    double *mat = REAL(mat_);
    double val = Rf_asReal(vec_);
    
    for (int col = 0; col < cols; ++col) {
      mat[i + col * rows] = val;
    }
  } else if (Rf_length(vec_) == cols) {
    double *mat = REAL(mat_);
    double *vec = REAL(vec_);
    
    for (int col = 0; col < cols; ++col) {
      mat[i + col * rows] = vec[col];
    }
  } else {
    Rf_error("'vec' length does not match number of matrix cols. %i != %i", 
             Rf_length(vec_), cols);
  }
  
  return mat_;
}


