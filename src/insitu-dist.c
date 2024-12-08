
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define UNROLL 4

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_dist2_(SEXP d_, SEXP mat1_, SEXP mat2_) {
  
  int nrow = Rf_nrows(mat1_);
  if (nrow != Rf_nrows(mat2_)) {
    Rf_error("br_mat_dist2_(): mat1 and mat2 must have the same number of rows. %i != %i", nrow, Rf_nrows(mat2_));
  }
  
  if (Rf_length(d_) != nrow) {
    Rf_error("br_mat_dist2_(): 'd' must have a length to match nrow(mat1).  %i != %i", (int)Rf_length(d_), nrow);
  }
  
  if (Rf_ncols(mat1_) < 2 || Rf_ncols(mat2_) < 2) {
    Rf_error("br_mat_dist2_(): Must be at least 2 columns in each matrix");
  }
  
  double *x1 = REAL(mat1_);
  double *y1 = x1 + nrow;
  double *x2 = REAL(mat2_);
  double *y2 = x2 + nrow;
  double *d = REAL(d_);
  
  int i = 0;
  for (; i < nrow - (UNROLL - 1); i += UNROLL) {
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
  }
  for (; i < nrow; ++i) {
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
  }
  
  return d_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_dist3_(SEXP d_, SEXP mat1_, SEXP mat2_) {
  
  int nrow = Rf_nrows(mat1_);
  if (nrow != Rf_nrows(mat2_)) {
    Rf_error("br_mat_dist3_(): mat1 and mat2 must have the same number of rows. %i != %i", nrow, Rf_nrows(mat2_));
  }
  
  if (Rf_length(d_) != nrow) {
    Rf_error("br_mat_dist3_(): 'd' must have a length to match nrow(mat1).  %i != %i", (int)Rf_length(d_), nrow);
  }

  if (Rf_ncols(mat1_) < 3 || Rf_ncols(mat2_) < 3) {
    Rf_error("br_mat_dist3_(): Must be at least 3 columns in each matrix");
  }
  
  double *x1 = REAL(mat1_);
  double *y1 = x1 + nrow;
  double *z1 = y1 + nrow;
  double *x2 = REAL(mat2_);
  double *y2 = x2 + nrow;
  double *z2 = y2 + nrow;
  double *d = REAL(d_);
  
  int i = 0;
  for (; i < nrow - (UNROLL - 1); i += UNROLL) {
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
  }
  for (; i < nrow; ++i) {
    *d++ = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
  }
  
  return d_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Length of (x, y, z) 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_hypot2_(SEXP d_, SEXP mat_) {
  
  
  if (!Rf_isMatrix(mat_)) {
    Rf_error("br_mat_hypot2_(): input must be a 2D matrix");
  }
  
  int nrow = Rf_nrows(mat_);
  int ncol = Rf_ncols(mat_);
  if (ncol < 2) {
    Rf_error("br_mat_hypot2_(): input must have at least 2 columns");
  }
  
  if (Rf_length(d_) != nrow) {
    Rf_error("br_mat_hypot2_(): length(d) != nrow(mat)");
  }
  
  double *x = REAL(mat_);
  double *y = x + nrow;
  double *d = REAL(d_);
  
  int i = 0;
  for (; i < nrow - (UNROLL - 1); i += UNROLL) {
    *d++ = hypot(*x++, *y++);  
    *d++ = hypot(*x++, *y++);  
    *d++ = hypot(*x++, *y++);  
    *d++ = hypot(*x++, *y++);  
  }
  for (; i < nrow; ++i) {
    *d++ = hypot(*x++, *y++);  
  }
  
  return d_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Length of (x, y, z) 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_hypot3_(SEXP d_, SEXP mat_) {
  
  
  if (!Rf_isMatrix(mat_)) {
    Rf_error("br_mat_hypot3_(): input must be a 2D matrix");
  }
  
  int nrow = Rf_nrows(mat_);
  int ncol = Rf_ncols(mat_);
  if (ncol < 3) {
    Rf_error("br_mat_hypot3_(): input must have at least 3 columns");
  }
  
  if (Rf_length(d_) != nrow) {
    Rf_error("br_mat_hypot3_(): length(d) != nrow(mat)");
  }
  
  double *x = REAL(mat_);
  double *y = x + nrow;
  double *z = y + nrow;
  double *d = REAL(d_);
  
  int i = 0;
  for (; i < nrow - (UNROLL - 1); i += UNROLL) {
    *d++ = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
    *d++ = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
    *d++ = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
    *d++ = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
  }
  for (; i < nrow; ++i) {
    *d++ = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
  }
  
  return d_;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Normalise
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_normalise2_(SEXP mat_) {
  
  if (!Rf_isMatrix(mat_)) {
    Rf_error("br_normalise2_(): input must be a 2D matrix");
  }
  
  int nrow = Rf_nrows(mat_);
  int ncol = Rf_ncols(mat_);
  if (ncol < 2) {
    Rf_error("br_normalise2_(): input must have at least 2 columns");
  }
  
  double *x = REAL(mat_);
  double *y = x + nrow;
  
  for (int i = 0; i < nrow; ++i) {
    double len = hypot(*x, *y); 
    *x /= len;
    *y /= len;
    ++x; ++y; 
  }
  
  return mat_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Normalise
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_normalise3_(SEXP mat_) {
  
  if (!Rf_isMatrix(mat_)) {
    Rf_error("br_normalise3_(): input must be a 2D matrix");
  }
  
  int nrow = Rf_nrows(mat_);
  int ncol = Rf_ncols(mat_);
  if (ncol < 3) {
    Rf_error("br_normalise3_(): input must have at least 3 columns");
  }
  
  double *x = REAL(mat_);
  double *y = x + nrow;
  double *z = y + nrow;
  
  for (int i = 0; i < nrow; ++i) {
    double len = sqrt(*x * *x + *y * *y + *z * *z); 
    *x /= len;
    *y /= len;
    *z /= len;
    ++x; ++y; ++z; 
  }
  
  return mat_;
}

















