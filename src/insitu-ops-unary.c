
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
// MACRO: Create a unary func that performs the operation over 'len' values
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UNARYOP(nm, unaryop)                                                        \
static inline void br_##nm##_(double *x, int len, int *idx, int idx_len) {          \
  if (idx != NULL) {                                                                \
    for (int j = 0; j < idx_len; ++j) {                                             \
      int i = idx[j];                                                               \
      x[i] = unaryop(0);                                                            \
    }                                                                               \
  } else {                                                                          \
    int i = 0;                                                                      \
    for (; i < len - (UNROLL - 1); i += UNROLL) {                                   \
      x[i + 0] = unaryop(0);                                                        \
      x[i + 1] = unaryop(1);                                                        \
      x[i + 2] = unaryop(2);                                                        \
      x[i + 3] = unaryop(3);                                                        \
    }                                                                               \
    for (; i< len; ++i) {                                                           \
      x[i] = unaryop(0);                                                            \
    }                                                                               \
  }                                                                                 \
}                                                                 



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
#define OP_POW2(offset)  (x[i + (offset)] * x[i + (offset)])


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
UNARYOP(pow2 ,  OP_POW2)


  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Array of unary functions performed by index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define NUNARYOPS 31

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Array of unary functions over full vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void (*unaryfunc[NUNARYOPS]) (double *x, int len, int *idx, int idx_len) = {
  br_abs_  ,  //  0
  br_sqrt_ ,  //  1
  br_floor_,  //  2
  br_ceil_ ,  //  3
  br_trunc_,  //  4
  br_exp_  ,  //  5
  br_log_  ,  //  6
  br_log2_ ,  //  7
  br_log10_,  //  8
  br_cos_  ,  //  9
  br_sin_  ,  // 10
  br_tan_  ,  // 11
  br_not_  ,  // 12
  br_expm1_,  // 13
  br_log1p_,  // 14
  br_acos_ ,  // 15
  br_asin_ ,  // 16
  br_atan_ ,  // 17
  br_acosh_,  // 18
  br_asinh_,  // 19
  br_atanh_,  // 20
  br_cosh_ ,  // 21
  br_sinh_ ,  // 22
  br_tanh_ ,  // 23
  br_sign_ ,  // 24
  br_cospi_,  // 25
  br_sinpi_,  // 26
  br_tanpi_,  // 27
  br_is_na_,  // 28
  br_zero_ ,  // 29
  br_pow2_    // 30
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
  
  void (*unfunc) (double *x, int len, int *idx, int idx_len) = unaryfunc[op];
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Basic case. Matrix and vector both treated like matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isNull(idx_) && Rf_isNull(where_) && Rf_isNull(cols_)) {
    unfunc(REAL(x_), (int)Rf_length(x_), NULL, 0);
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // When 'x' is just a vector
  // or a matrix where 
  //    - 'cols' is not set
  //    - and  length(where) != nrows(x)
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isMatrix(x_) || (Rf_isNull(cols_) && Rf_length(where_) != Rf_nrows(x_))) {
    if (!Rf_isNull(cols_)) {
      Rf_warning("br_op_unary_('%s'): 'cols' is set, but 'x' is not a matrix. Ignoring 'cols'", opnames[op]);
    }
    
    int status = 0;
    int idx_len = 0;
    int *idx = location_to_idx(idx_, where_, &idx_len, Rf_length(x_), &status);
    if (status != 0) {
      Rf_error(
        "[br_op_unary_('%s') Loc:2] location_to_idx() failed",
        opnames[op]
      );
    }
    unfunc(REAL(x_), Rf_length(x_), idx, idx_len);
    free(idx);
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // When 'x' is a Matrix and 
  //   - 'cols' is NOT set.
  //   - and length(where) == length(rows)
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isNull(cols_) && Rf_length(where_) == Rf_nrows(x_)) {
    int status = 0;
    int idx_len = 0;
    int *idx = location_to_idx(idx_, where_, &idx_len, Rf_nrows(x_), &status);
    if (status != 0) {
      Rf_error(
        "[br_op_unary_('%s') Loc:3] location_to_idx() failed",
        opnames[op]
      );
    }
    for (int col = 0; col < Rf_ncols(x_); ++col) {
      unfunc(REAL(x_) + col * Rf_nrows(x_), Rf_nrows(x_), idx, idx_len);
    }
    free(idx);
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // 'cols' is set.
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isNull(cols_)) {
    int status = 0;
    int idx_len = 0;
    int *idx = location_to_idx(idx_, where_, &idx_len, Rf_nrows(x_), &status);
    if (status != 0) {
      Rf_error(
        "[br_op_unary_('%s') Loc:4] location_to_idx() failed",
        opnames[op]
      );
    }
    
    int *cols = NULL;
    int cols_len = 0;
    if (Rf_asLogical(cols_) == NA_LOGICAL) {
      // Perform over all columns
      cols = malloc(Rf_ncols(x_) * sizeof(int));
      if (cols == NULL) {
        Rf_error(
          "[br_op_unary_('%s') Loc:5] Failed to allocate 'cols'",
          opnames[op]
        );
      }
      for (int i = 0; i < Rf_ncols(x_); ++i) {
        cols[i] = i;
      }
      cols_len = Rf_ncols(x_);
    } else {
      // Perform over selected cols
      int status = 0;
      cols = ridx_to_idx(cols_, Rf_ncols(x_), &status);
      if (status != 0) {
        Rf_error(
          "[br_op_unary_('%s') Loc:6] ridx_to_idx() failed",
          opnames[op]
        );
      }
      if (cols == NULL) {
        Rf_error(
          "[br_op_unary_('%s') Loc:7] No columns specified? ridx_to_idx() failed",
          opnames[op]
        );
      }
      cols_len = Rf_length(cols_);
    }
    
    
    for (int i = 0; i < cols_len; ++i) {
      int col = cols[i];
      unfunc(REAL(x_) + col * Rf_nrows(x_), Rf_nrows(x_), idx, idx_len);
    }
    free(cols);
    free(idx);
    return x_;
  }
  
  Rf_error("[br_op_unary_('%s') Loc:99] Sanity check failed. No processing optino found", opnames[op]);
}





















