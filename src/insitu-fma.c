
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UNROLL 4

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FMA with scalar 'a'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fma_sa_(SEXP x_, SEXP a_, SEXP b_, double fa, double fb) {
  
  double *x = REAL(x_);
  double  a = Rf_asReal(a_) * fa;
  double *b = REAL(b_);
  
  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    x[i + 0] = fma(x[i + 0], a, fb * b[i + 0]);
    x[i + 1] = fma(x[i + 1], a, fb * b[i + 1]);
    x[i + 2] = fma(x[i + 2], a, fb * b[i + 2]);
    x[i + 3] = fma(x[i + 3], a, fb * b[i + 3]);
  }
  for (; i< Rf_length(x_); ++i) {
    x[i + 0] = fma(x[i + 0], a, fb * b[i + 0]);
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FMA with scalar 'b'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fma_sb_(SEXP x_, SEXP a_, SEXP b_, double fa, double fb) {
  
  double *x = REAL(x_);
  double *a = REAL(a_);
  double  b = Rf_asReal(b_) * fb;
  
  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    x[i + 0] = fma(fa * x[i + 0], a[i + 0], b);
    x[i + 1] = fma(fa * x[i + 1], a[i + 1], b);
    x[i + 2] = fma(fa * x[i + 2], a[i + 2], b);
    x[i + 3] = fma(fa * x[i + 3], a[i + 3], b);
  }
  for (; i< Rf_length(x_); ++i) {
    x[i + 0] = fma(fa * x[i + 0], a[i + 0], b);
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FMA with scalar 'a' & 'b'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fma_sab_(SEXP x_, SEXP a_, SEXP b_, double fa, double fb) {
  
  double *x = REAL(x_);
  double  a = Rf_asReal(a_) * fa;
  double  b = Rf_asReal(b_) * fb;
  
  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    x[i + 0] = fma(x[i + 0], a, b);
    x[i + 1] = fma(x[i + 1], a, b);
    x[i + 2] = fma(x[i + 2], a, b);
    x[i + 3] = fma(x[i + 3], a, b);
  }
  for (; i< Rf_length(x_); ++i) {
    x[i + 0] = fma(x[i + 0], a, b);
  }
  
  return x_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FMA with vector x,a,b
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fma_vxab_(SEXP x_, SEXP a_, SEXP b_, double fa, double fb) {
  
  double *x = REAL(x_);
  double *a = REAL(a_);
  double *b = REAL(b_);
  
  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    x[i + 0] = fma(fa * x[i + 0], a[i + 0], fb * b[i + 0]);
    x[i + 1] = fma(fa * x[i + 1], a[i + 1], fb * b[i + 1]);
    x[i + 2] = fma(fa * x[i + 2], a[i + 2], fb * b[i + 2]);
    x[i + 3] = fma(fa * x[i + 3], a[i + 3], fb * b[i + 3]);
  }
  for (; i< Rf_length(x_); ++i) {
    x[i + 0] = fma(fa * x[i + 0], a[i + 0], fb * b[i + 0]);
  }
  
  return x_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// fmadd  0
// fmsub  1
// fnmadd 2
// fnmsub 3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_fma_(SEXP op_, SEXP x_, SEXP a_, SEXP b_) {
  
  int op = Rf_asInteger(op_);
  double fa = 1;
  double fb = 1;
  
  switch(op) {
  case 0: // fmadd
    break;
  case 1: // fmsub
    fb = -1;
    break;
  case 2: // fnmadd
    fa = -1;
    break;
  case 3: // fnmsub
    fa = -1;
    fb = -1;
    break;
  default:
    Rf_error("br_fma_(): 'op' %d out of bounds [0, 3]", op);
  }
  
  R_xlen_t lx = Rf_length(x_);
  R_xlen_t la = Rf_length(a_);
  R_xlen_t lb = Rf_length(b_);
  
  if (lx == la && lx == lb) {
    return fma_vxab_(x_, a_, b_, fa, fb);
  } else if (lx == la && lb == 1) {
    return fma_sb_(x_, a_, b_, fa, fb);
  } else if (lx == lb && la == 1) {
    return fma_sa_(x_, a_, b_, fa, fb);
  } else if (la == 1 && lb == 1) {
    return fma_sab_(x_, a_, b_, fa, fb);
  }
  
  Rf_error("br_fma_(): Lengths not compatible: x = %.0f, a = %.0f, b = %.0f", (double)lx, (double)la, (double)lb);
}


