

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_add_vxy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_add_sy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_add_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_add_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_add_sy_(x_, y_);
  }
  
  error("ins_add(): Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// subtraction with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_sub_vxy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_sub_sy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_sub_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_sub_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_sub_sy_(x_, y_);
  }
  
  error("ins_sub(): Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// multiplication with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_mul_vxy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_mul_sy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_mul_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_mul_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_mul_sy_(x_, y_);
  }
  
  error("ins_mul(): Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// division with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP ins_div_vxy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_div_sy_(SEXP x_, SEXP y_) {
  
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
SEXP ins_div_(SEXP x_, SEXP y_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t ly = length(y_);
  
  if (lx == ly) {
    return ins_div_vxy_(x_, y_);
  } else if (ly == 1) {
    return ins_div_sy_(x_, y_);
  }
  
  error("ins_div(): Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);
}

