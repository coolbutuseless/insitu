
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
SEXP br_dist2_(SEXP x1_, SEXP y1_, SEXP x2_, SEXP y2_) {
  
  int n = (int)Rf_length(x1_);
  if (Rf_length(y1_) != n || Rf_length(x2_) !=n || Rf_length(y2_) != n) {
    Rf_error("br_dist2_(): All inputs must be the same length");
  }
  
  double *x1 = REAL(x1_);
  double *y1 = REAL(y1_);
  double *x2 = REAL(x2_);
  double *y2 = REAL(y2_);

  int i = 0;
  for (; i < n - (UNROLL - 1); i += UNROLL) {
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
  }
  for (; i < n; i++) {
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1)); ++x1; ++y1; ++x2; ++y2;
  }

  return x1_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_dist3_(SEXP x1_, SEXP y1_, SEXP z1_, SEXP x2_, SEXP y2_, SEXP z2_) {
  
  int n = (int)Rf_length(x1_);
  if (Rf_length(y1_) != n || Rf_length(z1_) != n ||
      Rf_length(x2_) != n || Rf_length(y2_) != n || Rf_length(z2_) != n) {
    Rf_error("br_dist3_(): All inputs must be the same length");
  }
  
  double *x1 = REAL(x1_);
  double *y1 = REAL(y1_);
  double *z1 = REAL(z1_);
  double *x2 = REAL(x2_);
  double *y2 = REAL(y2_);
  double *z2 = REAL(z2_);
  
  int i = 0;
  for (; i < n - (UNROLL - 1); i += UNROLL) {
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
  }
  for (; i < n; i++) {
    *x1 = sqrt((*x2 - *x1) * (*x2 - *x1) + (*y2 - *y1) * (*y2 - *y1) + (*z2 - *z1) * (*z2 - *z1)); ++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
  }
  
  return x1_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_hypot3_(SEXP x_, SEXP y_, SEXP z_) {
  
  int n = (int)Rf_length(x_);
  if (Rf_length(y_) != n || Rf_length(z_) != n) {
    Rf_error("br_hypot3_(): All inputs must be the same length");
  }
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  double *z = REAL(z_);
  
  int i = 0;
  for (; i < n - (UNROLL - 1); i += UNROLL) {
    *x = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
    *x = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
    *x = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
    *x = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
  }
  for (; i < n; i++) {
    *x = sqrt(*x * *x + *y * *y + *z * *z); ++x; ++y; ++z; 
  }
  
  return x_;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Normalise
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_normalise2_(SEXP x_, SEXP y_) {
  
  int n = (int)Rf_length(x_);
  if (Rf_length(y_) != n) {
    Rf_error("br_normalise2_(): All inputs must be the same length");
  }
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  
  for (int i = 0; i < Rf_length(x_); i++) {
    double len = hypot(*x, *y); 
    *x /= len;
    *y /= len;
    ++x; ++y; 
  }
  
  return x_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Normalise
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_normalise3_(SEXP x_, SEXP y_, SEXP z_) {
  
  int n = (int)Rf_length(x_);
  if (Rf_length(y_) != n || Rf_length(z_) != n) {
    Rf_error("br_normalise3_(): All inputs must be the same length");
  }
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  double *z = REAL(z_);
  
  for (int i = 0; i < Rf_length(x_); i++) {
    double len = sqrt(*x * *x + *y * *y + *z * *z); 
    *x /= len;
    *y /= len;
    *z /= len;
    ++x; ++y; ++z; 
  }
  
  return x_;
}

















