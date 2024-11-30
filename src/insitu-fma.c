

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
  double  a = asReal(a_) * fa;
  double *b = REAL(b_);
  
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x = fma(*x, a, fb * *b++); x++;
    *x = fma(*x, a, fb * *b++); x++;
    *x = fma(*x, a, fb * *b++); x++;
    *x = fma(*x, a, fb * *b++); x++;
  }
  for (; i< length(x_); i++) {
    *x = fma(*x, a, fb * *b++); x++;
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FMA with scalar 'b'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fma_sb_(SEXP x_, SEXP a_, SEXP b_, double fa, double fb) {
  
  double *x = REAL(x_);
  double *a = REAL(a_);
  double  b = asReal(b_) * fb;
  
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x = fma(fa * *x, *a++, b); x++;
    *x = fma(fa * *x, *a++, b); x++;
    *x = fma(fa * *x, *a++, b); x++;
    *x = fma(fa * *x, *a++, b); x++;
  }
  for (; i< length(x_); i++) {
    *x = fma(fa * *x, *a++, b); x++;
  }
  
  return x_;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FMA with scalar 'b'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fma_sab_(SEXP x_, SEXP a_, SEXP b_, double fa, double fb) {
  
  double *x = REAL(x_);
  double  a = asReal(a_) * fa;
  double  b = asReal(b_) * fb;
  
  int i = 0;
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x = fma(*x, a, b); x++;
    *x = fma(*x, a, b); x++;
    *x = fma(*x, a, b); x++;
    *x = fma(*x, a, b); x++;
  }
  for (; i< length(x_); i++) {
    *x = fma(*x, a, b); x++;
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
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
    *x = fma(fa * *x, *a++, fb * *b++); x++;
    *x = fma(fa * *x, *a++, fb * *b++); x++;
    *x = fma(fa * *x, *a++, fb * *b++); x++;
    *x = fma(fa * *x, *a++, fb * *b++); x++;
  }
  for (; i< length(x_); i++) {
    *x = fma(fa * *x, *a++, fb * *b++); x++;
  }
  
  return x_;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fmadd_(SEXP x_, SEXP a_, SEXP b_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t la = length(a_);
  R_xlen_t lb = length(b_);
  
  if (lx == la && lx == lb) {
    return fma_vxab_(x_, a_, b_, 1, 1);
  } else if (lx == la && lb == 1) {
    return fma_sb_(x_, a_, b_, 1, 1);
  } else if (lx == lb && la == 1) {
    return fma_sa_(x_, a_, b_, 1, 1);
  } else if (la == 1 && lb == 1) {
    return fma_sab_(x_, a_, b_, 1, 1);
  }
  
  error("br_fmadd(): Lengths not compatible: x = %.0f, a = %.0f, b = %.0f", (double)lx, (double)la, (double)lb);
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fmsub_(SEXP x_, SEXP a_, SEXP b_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t la = length(a_);
  R_xlen_t lb = length(b_);
  
  if (lx == la && lx == lb) {
    return fma_vxab_(x_, a_, b_, 1, -1);
  } else if (lx == la && lb == 1) {
    return fma_sb_(x_, a_, b_, 1, -1);
  } else if (lx == lb && la == 1) {
    return fma_sa_(x_, a_, b_, 1, -1);
  } else if (la == 1 && lb == 1) {
    return fma_sab_(x_, a_, b_, 1, -1);
  }
  
  error("br_fmsub(): Lengths not compatible: x = %.0f, a = %.0f, b = %.0f", (double)lx, (double)la, (double)lb);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fnmadd_(SEXP x_, SEXP a_, SEXP b_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t la = length(a_);
  R_xlen_t lb = length(b_);
  
  if (lx == la && lx == lb) {
    return fma_vxab_(x_, a_, b_, -1, 1);
  } else if (lx == la && lb == 1) {
    return fma_sb_(x_, a_, b_, -1, 1);
  } else if (lx == lb && la == 1) {
    return fma_sa_(x_, a_, b_, -1, 1);
  } else if (la == 1 && lb == 1) {
    return fma_sab_(x_, a_, b_, -1, 1);
  }
  
  error("br_fnmadd(): Lengths not compatible: x = %.0f, a = %.0f, b = %.0f", (double)lx, (double)la, (double)lb);
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP fnmsub_(SEXP x_, SEXP a_, SEXP b_) {
  
  R_xlen_t lx = length(x_);
  R_xlen_t la = length(a_);
  R_xlen_t lb = length(b_);
  
  if (lx == la && lx == lb) {
    return fma_vxab_(x_, a_, b_, -1, -1);
  } else if (lx == la && lb == 1) {
    return fma_sb_(x_, a_, b_, -1, -1);
  } else if (lx == lb && la == 1) {
    return fma_sa_(x_, a_, b_, -1, -1);
  } else if (la == 1 && lb == 1) {
    return fma_sab_(x_, a_, b_, -1, -1);
  }
  
  error("br_fnmsub(): Lengths not compatible: x = %.0f, a = %.0f, b = %.0f", (double)lx, (double)la, (double)lb);
}
