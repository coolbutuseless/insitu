
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


static double fact[24] = {
  1.0,
  10.0,
  100.0,
  1000.0,
  10000.0,
  100000.0,
  1000000.0,
  10000000.0,
  100000000.0,
  1000000000.0,
  10000000000.0,
  100000000000.0,
  1000000000000.0,
  10000000000000.0,
  100000000000000.0,
  1000000000000000.0,
  10000000000000000.0,
  100000000000000000.0,
  1000000000000000000.0,
  10000000000000000000.0,
  100000000000000000000.0,
  1000000000000000000000.0,
  10000000000000000000000.0,
  100000000000000000000000.0 
};

static double invfact[24] = {
  1.0,
  0.1,
  0.01,
  0.001,
  0.0001,
  0.00001,
  0.000001,
  0.0000001,
  0.00000001,
  0.000000001,
  0.0000000001,
  0.00000000001,
  0.000000000001,
  0.0000000000001,
  0.00000000000001,
  0.000000000000001,
  0.0000000000000001,
  0.00000000000000001,
  0.000000000000000001,
  0.0000000000000000001,
  0.00000000000000000001,
  0.000000000000000000001,
  0.0000000000000000000001,
  0.00000000000000000000001  
};


double fast_round(double x) {
  double sweet = 6755399441055744.0;  // 2^51 + 2^52
  return x + sweet - sweet;
}

/*
 * Check for special values which are impossible for ALP to encode
 * because they cannot be cast to int64 without an undefined behaviour
 */

// From ALP source
#define ENCODING_UPPER_LIMIT   9223372036854774784
#define ENCODING_LOWER_LIMIT  -9223372036854774784

bool is_impossible_to_encode(double n) {
  return 
  !isfinite(n) || 
    isnan(n) || 
    n > ENCODING_UPPER_LIMIT || 
    n < ENCODING_LOWER_LIMIT ||
    (n == 0.0 && signbit(n)); //! Verification for -0.0
}


SEXP br_op_unary_round_fast_(SEXP x_, SEXP digits_) {
  R_xlen_t len = Rf_xlength(x_);
  
  int digits = Rf_asInteger(digits_);
  if (digits < 0 || digits > 23) {
    Rf_error("'digits' argument out of range [0, 24]");
  }
  
  double f1 = fact[digits];
  double f2 = invfact[digits];
  
  double sweet = 6755399441055744.0;  // 2^51 + 2^52
  double *x = REAL(x_);
  for (R_xlen_t i = 0; i < len; i++) {
    if (is_impossible_to_encode(x[i])) {
      Rf_error("br_op_unary_round_fast(): Value not castable to int64: %f", x[i]);
    }
    x[i] = ((x[i] * f1) + sweet - sweet) * f2;
  }
  
  return x_;
}





SEXP br_op_unary_round_fast_unchecked_(SEXP x_, SEXP digits_) {
  R_xlen_t len = Rf_xlength(x_);
  
  int digits = Rf_asInteger(digits_);
  if (digits < 0 || digits > 23) {
    Rf_error("'digits' argument out of range [0, 24]");
  }
  
  double f1 = fact[digits];
  double f2 = invfact[digits];
  
  double sweet = 6755399441055744.0;  // 2^51 + 2^52
  double *x = REAL(x_);
  for (R_xlen_t i = 0; i < len; i++) {
    x[i] = ((x[i] * f1) + sweet - sweet) * f2;
  }
  
  return x_;
}






SEXP br_op_unary_round_(SEXP x_, SEXP digits_) {
  double *x = REAL(x_);
  
  int digits = Rf_asInteger(digits_);
  if (digits < 0 || digits > 23) {
    Rf_error("'digits' argument out of range [0, 24]");
  }
  
  double f1 = fact[digits];
  double f2 = invfact[digits];
  
  for (R_xlen_t i = 0; i < Rf_xlength(x_); ++i) {
    x[i] = round(x[i] * f1) * f2;
  }

  return x_;
}

