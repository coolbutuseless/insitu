

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_plus_vxy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ += *y++;
    *x++ += *y++;
    *x++ += *y++;
    *x++ += *y++;
  }
  for (; i< length(x_); i++) {
    *x++ += *y++;
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with scalar y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_plus_sy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double  y = REAL(y_)[0];
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ += y;
    *x++ += y;
    *x++ += y;
    *x++ += y;
  }
  for (; i< length(x_); i++) {
    *x++ += y;
  }
  
  return x_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_plus_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_plus_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_plus_sy_(x_, y_);
  }
  
  error("ins_plus(): Lengths not compatible: x = %li, y = %li", lx, ly);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// subtraction with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_minus_vxy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ -= *y++;
    *x++ -= *y++;
    *x++ -= *y++;
    *x++ -= *y++;
  }
  for (; i< length(x_); i++) {
    *x++ -= *y++;
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// subtraction with scalar y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_minus_sy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double  y = REAL(y_)[0];
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ -= y;
    *x++ -= y;
    *x++ -= y;
    *x++ -= y;
  }
  for (; i< length(x_); i++) {
    *x++ -= y;
  }
  
  return x_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_minus_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_minus_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_minus_sy_(x_, y_);
  }
  
  error("ins_minus(): Lengths not compatible: x = %li, y = %li", lx, ly);
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// multiplication with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_mult_vxy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ *= *y++;
    *x++ *= *y++;
    *x++ *= *y++;
    *x++ *= *y++;
  }
  for (; i< length(x_); i++) {
    *x++ *= *y++;
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// multiplication with scalar y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_mult_sy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double  y = REAL(y_)[0];
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ *= y;
    *x++ *= y;
    *x++ *= y;
    *x++ *= y;
  }
  for (; i< length(x_); i++) {
    *x++ *= y;
  }
  
  return x_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_mult_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_mult_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_mult_sy_(x_, y_);
  }
  
  error("ins_mult(): Lengths not compatible: x = %li, y = %li", lx, ly);
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// division with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_divide_vxy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ /= *y++;
    *x++ /= *y++;
    *x++ /= *y++;
    *x++ /= *y++;
  }
  for (; i< length(x_); i++) {
    *x++ /= *y++;
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// division with scalar y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_divide_sy_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);
  double  y = REAL(y_)[0];
  
#define UNROLL 4
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x++ /= y;
    *x++ /= y;
    *x++ /= y;
    *x++ /= y;
  }
  for (; i< length(x_); i++) {
    *x++ /= y;
  }
  
  return x_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_divide_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_divide_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_divide_sy_(x_, y_);
  }
  
  error("ins_divide(): Lengths not compatible: x = %li, y = %li", lx, ly);
}

