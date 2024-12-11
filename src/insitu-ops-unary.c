
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils-logical-to-idx.h"

// * abs, sign, sqrt, floor, ceiling, trunc, round, signif
// * exp, log, expm1, log1p, cos, sin, tan, cospi, sinpi, tanpi, acos, asin, atan
// * cosh, sinh, tanh, acosh, asinh, atanh
// * lgamma, gamma, digamma, trigamma
// * cumsum, cumprod, cummax, cummin

#define UNROLL 4


// #define OP_SQRT(offset)   sqrt(x[i + (offset)])
// 
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// //
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void ybr_sqrt_byidx(double *x, int *idx, int idx_len) {
// 
//   for (int j = 0; j < idx_len; ++j) {
//     int i = idx[j];
//     x[i] = OP_SQRT(0);
//   }
// }
// 
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// //
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void ybr_sqrt_full(double *x, int len) {
// 
//   int i = 0;
//   for (; i < len - (UNROLL - 1); i += UNROLL) {
//     x[i + 0] = OP_SQRT(0);
//     x[i + 1] = OP_SQRT(1);
//     x[i + 2] = OP_SQRT(2);
//     x[i + 3] = OP_SQRT(3);
//   }
//   for (; i < len; ++i) {
//     x[i] = OP_SQRT(0);
//   }
// }
// 


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a function that performs the unary operation by index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOPBYIDX(nm, unaryop)                                         \
static inline void br_##nm##_byidx(double *x, int *idx, int idx_len) {   \
                                                                          \
  for (int j = 0; j < idx_len; ++j) {                                     \
    int i = idx[j];                                                       \
    x[i] = unaryop(0);                                                    \
  }                                                                       \
                                                                          \
}                                                                         \


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a unary func that performs the operation over 'len' values
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOPFULL(nm, unaryop)                                  \
static inline void br_##nm##_full(double *x, int len) {          \
  int i = 0;                                                      \
  for (; i < len - (UNROLL - 1); i += UNROLL) {                   \
    x[i + 0] = unaryop(0);                                        \
    x[i + 1] = unaryop(1);                                        \
    x[i + 2] = unaryop(2);                                        \
    x[i + 3] = unaryop(3);                                        \
  }                                                               \
  for (; i< len; ++i) {                                           \
    x[i] = unaryop(0);                                            \
  }                                                               \
}                                                                 \


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO: Create a set of unary funcs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOP(nm, unaryop)       \
UNARYOPBYIDX(nm, unaryop)          \
UNARYOPFULL(nm, unaryop)           \


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Define core of each unary operation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OP_ABS(offset)    fabs(x[i + (offset)])
#define OP_SQRT(offset)   sqrt(x[i + (offset)])
#define OP_FLOOR(offset) floor(x[i + (offset)])
#define OP_CEIL(offset)   ceil(x[i + (offset)])
#define OP_TRUNC(offset) trunc(x[i + (offset)])
#define OP_EXP(offset)     exp(x[i + (offset)])
#define OP_LOG(offset)     log(x[i + (offset)])
#define OP_LOG2(offset)   log2(x[i + (offset)])
#define OP_LOG10(offset) log10(x[i + (offset)])
#define OP_COS(offset)     cos(x[i + (offset)])
#define OP_SIN(offset)     sin(x[i + (offset)])
#define OP_TAN(offset)     tan(x[i + (offset)])
#define OP_NOT(offset)   (double)(x[i + (offset)] == 0)
#define OP_EXPM1(offset) expm1(x[i + (offset)])
#define OP_LOG1P(offset) log1p(x[i + (offset)])
#define OP_ACOS(offset)   acos(x[i + (offset)])
#define OP_ASIN(offset)   asin(x[i + (offset)])
#define OP_ATAN(offset)   atan(x[i + (offset)])
#define OP_ACOSH(offset) acosh(x[i + (offset)])
#define OP_ASINH(offset) asinh(x[i + (offset)])
#define OP_ATANH(offset) atanh(x[i + (offset)])
#define OP_COSH(offset)   cosh(x[i + (offset)])
#define OP_SINH(offset)   sinh(x[i + (offset)])
#define OP_TANH(offset)   tanh(x[i + (offset)])
#define OP_SIGN(offset)  (double)( (x[i + (offset)] > 0) - (x[i + (offset)] < 0)) 
#define OP_COSPI(offset)   cos(x[i + (offset)] * M_PI)
#define OP_SINPI(offset)   sin(x[i + (offset)] * M_PI)
#define OP_TANPI(offset)   tan(x[i + (offset)] * M_PI)
#define OP_IS_NA(offset) (double)isnan(x[i + (offset)])
#define OP_ZERO(offset)  0.0
#define OP_POW2(offset)  x[i + (offset)] * x[i + (offset)]


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Create unary functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UNARYOP(abs  ,  OP_ABS)
UNARYOP(sqrt ,  OP_SQRT)
UNARYOP(floor,  OP_FLOOR)
UNARYOP(ceil ,  OP_CEIL)
UNARYOP(trunc,  OP_TRUNC)
UNARYOP(exp  ,  OP_EXP)
UNARYOP(log  ,  OP_LOG)
UNARYOP(log2 ,  OP_LOG2)
UNARYOP(log10,  OP_LOG10)
UNARYOP(cos  ,  OP_ABS)
UNARYOP(sin  ,  OP_SIN)
UNARYOP(tan  ,  OP_TAN)
UNARYOP(not  ,  OP_NOT)
UNARYOP(expm1,  OP_EXPM1)
UNARYOP(log1p,  OP_LOG1P)
UNARYOP(acos ,  OP_ACOS)
UNARYOP(asin ,  OP_ASIN)
UNARYOP(atan ,  OP_ATAN)
UNARYOP(acosh,  OP_ACOSH)
UNARYOP(asinh,  OP_ASINH)
UNARYOP(atanh,  OP_ATANH)
UNARYOP(cosh ,  OP_COSH)
UNARYOP(sinh ,  OP_SINH)
UNARYOP(tanh ,  OP_TANH)
UNARYOP(sign ,  OP_SIGN)
UNARYOP(cospi,  OP_COSPI)
UNARYOP(sinpi,  OP_SINPI)
UNARYOP(tanpi,  OP_TANPI)
UNARYOP(is_na,  OP_IS_NA)
UNARYOP(zero ,  OP_ZERO)
UNARYOP(pow2 ,  OP_ZERO)


  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Array of unary functions performed by index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define NUNARYOPS 31

void (*unaryfunc_byidx[NUNARYOPS]) (double *x, int *idx, int idx_len) = {
  br_abs_byidx  , //  0
  br_sqrt_byidx , //  1
  br_floor_byidx, //  2
  br_ceil_byidx , //  3
  br_trunc_byidx, //  4
  br_exp_byidx  , //  5
  br_log_byidx  , //  6
  br_log2_byidx , //  7
  br_log10_byidx, //  8
  br_cos_byidx  , //  9
  br_sin_byidx  , // 10
  br_tan_byidx  , // 11
  br_not_byidx  , // 12
  br_expm1_byidx, // 13
  br_log1p_byidx, // 14
  br_acos_byidx , // 15
  br_asin_byidx , // 16
  br_atan_byidx , // 17
  br_acosh_byidx, // 18
  br_asinh_byidx, // 19
  br_atanh_byidx, // 20
  br_cosh_byidx , // 21
  br_sinh_byidx , // 22
  br_tanh_byidx , // 23
  br_sign_byidx , // 24
  br_cospi_byidx, // 25
  br_sinpi_byidx, // 26
  br_tanpi_byidx, // 27
  br_is_na_byidx, // 28
  br_zero_byidx , // 29
  br_pow2_byidx   // 30
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Array of unary functions over full vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void (*unaryfunc_full[NUNARYOPS]) (double *x, int len) = {
  br_abs_full  ,  //  0
  br_sqrt_full ,  //  1
  br_floor_full,  //  2
  br_ceil_full ,  //  3
  br_trunc_full,  //  4
  br_exp_full  ,  //  5
  br_log_full  ,  //  6
  br_log2_full ,  //  7
  br_log10_full,  //  8
  br_cos_full  ,  //  9
  br_sin_full  ,  // 10
  br_tan_full  ,  // 11
  br_not_full  ,  // 12
  br_expm1_full,  // 13
  br_log1p_full,  // 14
  br_acos_full ,  // 15
  br_asin_full ,  // 16
  br_atan_full ,  // 17
  br_acosh_full,  // 18
  br_asinh_full,  // 19
  br_atanh_full,  // 20
  br_cosh_full ,  // 21
  br_sinh_full ,  // 22
  br_tanh_full ,  // 23
  br_sign_full ,  // 24
  br_cospi_full,  // 25
  br_sinpi_full,  // 26
  br_tanpi_full,  // 27
  br_is_na_full,  // 28
  br_zero_full ,  // 29
  br_pow2_full    // 30
};

char *opnames[NUNARYOPS] = {
  "abs"  ,
  "sqrt" ,
  "floor",
  "ceil" ,
  "trunc",
  "exp"  ,
  "log"  ,
  "log2" ,
  "log10",
  "cos"  ,
  "sin"  ,
  "tan"  ,
  "not"  ,
  "expm1",
  "log1p",
  "acos" ,
  "asin" ,
  "atan" ,
  "acosh",
  "asinh",
  "atanh",
  "cosh" ,
  "sinh" ,
  "tanh" ,
  "sign" ,
  "cospi",
  "sinpi",
  "tanpi",
  "is_na",
  "zero" ,
  "pow2"
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Main R dispatch for unary ops
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_op_unary_(SEXP op_, SEXP x_, SEXP idx_, SEXP where_, SEXP cols_) {
  
  int op = Rf_asInteger(op_);
  if (op < 0 || op >= NUNARYOPS) {
    Rf_error(
      "[br_op_unary_('%s') Loc:1] 'op' out of range [0, %i]", 
      opnames[op], NUNARYOPS - 1
    );
  }
  
  void (*unary_byidx) (double *x, int *idx, int idx_len) = unaryfunc_byidx[op];
  void (*unary_full ) (double *x, int len)               = unaryfunc_full [op];
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Basic case. Matrix and vector both treated like matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isNull(idx_) && Rf_isNull(where_) && Rf_isNull(cols_)) {
    unary_full(REAL(x_), (int)Rf_length(x_));
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // If 'cols' specified, must be a matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isNull(cols_)) {
    if (!Rf_isMatrix(x_)) {
      Rf_error("[br_op_unary_('%s') Loc:2] Specified 'cols' but 'x' is not a matrix", opnames[op]);
    }
    int status = 0;
    int *cols = ridx_to_idx(cols_, Rf_ncols(x_), &status);
    if (status != 0) {
      Rf_error("[br_op_unary_('%s') Loc:3] ridx_to_idx() failed.", opnames[op]);
    }
    if (!Rf_isNull(idx_)) {
      int status = 0;
      int *idx = ridx_to_idx(idx_, Rf_nrows(x_), &status);
      if (status != 0) {
        free(cols);
        Rf_error("[br_op_unary_('%s') Loc:4] ridx_to_idx() failed.", opnames[op]);
      }
      for (int i = 0; i < Rf_length(cols_); ++i) {
        unary_byidx(REAL(x_) + cols[i] * Rf_nrows(x_), idx, Rf_length(idx_));
      }
      free(idx);
    } else if (!Rf_isNull(where_)) {
      int idx_len = 0;
      int status = 0;
      int *idx = lgl_to_idx(where_, &idx_len, &status);
      if (status != 0) {
        Rf_error("[br_op_unary_('%s') Loc:5] lgl_to_idx() failed.", opnames[op]);
      }
      for (int i = 0; i < Rf_length(cols_); ++i) {
        unary_byidx(REAL(x_) + cols[i] * Rf_nrows(x_), idx, idx_len);
      }
      free(idx);
    } else {
      // no 'idx' or 'where' .  Apply to full column
      for (int i = 0; i < Rf_length(cols_); ++i) {
        unary_full(REAL(x_) + cols[i] * Rf_nrows(x_), Rf_nrows(x_));
      }
    }
    
    free(cols);
    return x_;
  }
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Matrix where 'cols' has not been set. 
  // Just deal with 'where' and 'idx' and apply to all columns
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isMatrix(x_)) {
    if (!Rf_isNull(idx_)) {
      int status = 0;
      int *idx = ridx_to_idx(idx_, Rf_nrows(x_), &status);
      if (status != 0) {
        Rf_error("[br_op_unary_('%s') Loc:6] ridx_to_idx() failed.", opnames[op]);
      }
      for (int col = 0; col < Rf_ncols(x_); ++col) {
        unary_byidx(REAL(x_) + col * Rf_nrows(x_), idx, Rf_length(idx_));
      }
      // int *idx = ridx_to_idx(idx_, Rf_length(x_), &status);
      // if (status != 0) {
      //   Rf_error("[br_op_unary_('%s') Loc:6a] ridx_to_idx() failed.", opnames[op]);
      // }
      // unary_byidx(REAL(x_), idx, Rf_length(idx_));
      // free(idx);
    } else if (!Rf_isNull(where_)) {
      if (Rf_length(where_) == Rf_nrows(x_)) {
        // Apply 'where' column-wise
        int idx_len = 0;
        int status = 0;
        int *idx = lgl_to_idx(where_, &idx_len, &status);
        if (status != 0) {
          Rf_error("[br_op_unary_('%s') Loc:7] lgl_to_idx() failed.", opnames[op]);
        }
        for (int col = 0; col < Rf_ncols(x_); ++col) {
          unary_byidx(REAL(x_) + col * Rf_nrows(x_), idx, idx_len);
        }
        free(idx);
      } else if (Rf_length(where_) == Rf_length(x_)) {
        // Treat 'where' as global
        int idx_len = 0;
        int status = 0;
        int *idx = lgl_to_idx(where_, &idx_len, &status);
        if (status != 0) {
          Rf_error("[br_op_unary_('%s') Loc:8] lgl_to_idx() failed.", opnames[op]);
        }
        unary_byidx(REAL(x_), idx, idx_len);
        free(idx);
      } else {
        Rf_error(
          "[br_op_unary_('%s') Loc:9] Length mismatch: len(where) [%.0f] != len(x) [%.0f] or nrow(x) [%i]", 
          opnames[op], 
                 (double)Rf_length(where_), (double)Rf_length(x_),
                 Rf_nrows(x_)
        );
      }
    } else {
      Rf_error("[br_op_unary_('%s') Loc:10] " "Sanity check failed", opnames[op]);
    }
    
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // If here, 'x' will only be treated as vector with either 'idx' or 'where' set
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isNull(idx_)) {
    int status = 0;
    int *idx = ridx_to_idx(idx_, Rf_length(x_), &status);
    if (status != 0) {
      Rf_error("[br_op_unary_('%s') Loc:11] ridx_to_idx() failed.", opnames[op]);
    }
    unary_byidx(REAL(x_), idx, Rf_length(idx_));
    free(idx);
    return x_;
  } else if (!Rf_isNull(where_)) {
    if (Rf_length(where_) == Rf_length(x_)) {
      int idx_len = 0;
      int status = 0;
      int *idx = lgl_to_idx(where_, &idx_len, &status);
      if (status != 0) {
        Rf_error("[br_op_unary_('%s') Loc:12] lgl_to_idx() failed.", opnames[op]);
      }
      unary_byidx(REAL(x_), idx, idx_len);
      free(idx);
      return x_;
    } else {
      Rf_error(
        "[br_op_unary_('%s') Loc:13] Length mismatch: len(where) [%.0f] != len(x) [%.0f] ", 
        opnames[op], (double)Rf_length(where_), (double)Rf_length(x_)
      );
    }
  } else {
    Rf_error("[br_op_unary_('%s') Loc:14] Sanity check failed", opnames[op]);
  }
  
  
  Rf_error("[br_op_unary_('%s') Loc:15] Sanity check failed", opnames[op]);
}




