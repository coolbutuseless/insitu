
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils-logical-to-idx.h"
#define UNROLL 4 


// #define OP_ADD_VV(OFF)   x[i + (OFF)] + y[i + (OFF)]
// #define OP_ADD_VS(OFF)   x[i + (OFF)] + y[0]
// 
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// // C calculation
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// int br_add_manual(double *x, double *y, int xlen, int ylen, int *idx, int idx_len) {
//   if (ylen == 1) {
//     /* op(vector, scalar) */
//     if (idx == NULL) {
//       /* op(vector, scalar) full */
//       int i = 0;
//       for (; i < xlen - (UNROLL - 1); i += UNROLL) {
//         x[i + 0] = OP_ADD_VS(0);
//         x[i + 1] = OP_ADD_VS(1);
//         x[i + 2] = OP_ADD_VS(2);
//         x[i + 3] = OP_ADD_VS(3);
//       }
//       for (; i < xlen; ++i) {
//         x[i + 0] = OP_ADD_VS(0);
//       }
//     } else {
//       /* op(vector, scalar) by idx */
//       for (int j = 0; j < idx_len; ++j) {
//         int i = idx[j];
//         x[i + 0] = OP_ADD_VS(0);
//       }
//     }
//   } else if (xlen == ylen) {
//     /* op(vector, vector) */
//     if (idx == NULL) {
//       /* op(vector, vector) full */
//       int i = 0;
//       for (; i < xlen - (UNROLL - 1); i += UNROLL) {
//         x[i + 0] = OP_ADD_VV(0);
//         x[i + 1] = OP_ADD_VV(1);
//         x[i + 2] = OP_ADD_VV(2);
//         x[i + 3] = OP_ADD_VV(3);
//       }
//       for (; i < xlen; ++i) {
//         x[i + 0] = OP_ADD_VV(0);
//       }
//     } else {
//       /* op(vector, vector) byidx */
//       for (int j = 0; j < idx_len; ++j) {
//         int i = idx[j];
//         x[i] = OP_ADD_VV(0);
//       }
//     }
//   } else {
//     Rf_warning("br_add(): 1245 error x/y non-conformable %i/%i", xlen, ylen);
//     return 1;
//   }
//   
//   return 0;
// }




#define BINARYOP(nm, op_vv, op_vs)                                                    \
int br_##nm##_(double *x, double *y, int xlen, int ylen, int *idx, int idx_len) {   \
  if (ylen == 1) {                                                                    \
    /* op(vector, scalar) */                                                          \
    if (idx == NULL) {                                                                \
      /* op(vector, scalar) full */                                                   \
      int i = 0;                                                                      \
      for (; i < xlen - (UNROLL - 1); i += UNROLL) {                                  \
        x[i + 0] = op_vs(0);                                                          \
        x[i + 1] = op_vs(1);                                                          \
        x[i + 2] = op_vs(2);                                                          \
        x[i + 3] = op_vs(3);                                                          \
      }                                                                               \
      for (; i < xlen; ++i) {                                                         \
        x[i + 0] = op_vs(0);                                                          \
      }                                                                               \
    } else {                                                                          \
      /* op(vector, scalar) by idx */                                                 \
      for (int j = 0; j < idx_len; ++j) {                                             \
        int i = idx[j];                                                               \
        x[i + 0] = op_vs(0);                                                          \
      }                                                                               \
    }                                                                                 \
  } else if (xlen == ylen) {                                                          \
    /* op(vector, vector) */                                                          \
    if (idx == NULL) {                                                                \
      /* op(vector, vector) full */                                                   \
      int i = 0;                                                                      \
      for (; i < xlen - (UNROLL - 1); i += UNROLL) {                                  \
        x[i + 0] = op_vv(0);                                                          \
        x[i + 1] = op_vv(1);                                                          \
        x[i + 2] = op_vv(2);                                                          \
        x[i + 3] = op_vv(3);                                                          \
      }                                                                               \
      for (; i < xlen; ++i) {                                                         \
        x[i + 0] = op_vv(0);                                                          \
      }                                                                               \
    } else {                                                                          \
      /* op(vector, vector) byidx */                                                  \
      for (int j = 0; j < idx_len; ++j) {                                             \
        int i = idx[j];                                                               \
        x[i] = op_vv(0);                                                              \
      }                                                                               \
    }                                                                                 \
  } else {                                                                            \
    Rf_warning("br_" #nm "_(): x/y non-conformable %i/%i", xlen, ylen);          \
    return 1;                                                                         \
  }                                                                                   \
                                                                                      \
  return 0;                                                                           \
}

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define OP_ADD_VV(OFF)   x[i + (OFF)] + y[i + (OFF)]
#define OP_ADD_VS(OFF)   x[i + (OFF)] + y[0]
#define OP_SUB_VV(OFF)   x[i + (OFF)] - y[i + (OFF)]
#define OP_SUB_VS(OFF)   x[i + (OFF)] - y[0]
#define OP_MUL_VV(OFF)   x[i + (OFF)] * y[i + (OFF)]
#define OP_MUL_VS(OFF)   x[i + (OFF)] * y[0]
#define OP_DIV_VV(OFF)   x[i + (OFF)] / y[i + (OFF)]
#define OP_DIV_VS(OFF)   x[i + (OFF)] / y[0]
#define OP_POW_VV(OFF)   pow(x[i + (OFF)], y[i + (OFF)])
#define OP_POW_VS(OFF)   pow(x[i + (OFF)], y[0])
#define OP_EQ_VV(OFF)   (double)(x[i + (OFF)] == y[i + (OFF)])
#define OP_EQ_VS(OFF)   (double)(x[i + (OFF)] == y[0])
#define OP_NE_VV(OFF)   (double)(x[i + (OFF)] != y[i + (OFF)])
#define OP_NE_VS(OFF)   (double)(x[i + (OFF)] != y[0])
#define OP_LT_VV(OFF)   (double)(x[i + (OFF)] <  y[i + (OFF)])
#define OP_LT_VS(OFF)   (double)(x[i + (OFF)] <  y[0])
#define OP_LE_VV(OFF)   (double)(x[i + (OFF)] <= y[i + (OFF)])
#define OP_LE_VS(OFF)   (double)(x[i + (OFF)] <= y[0])
#define OP_GT_VV(OFF)   (double)(x[i + (OFF)] >  y[i + (OFF)])
#define OP_GT_VS(OFF)   (double)(x[i + (OFF)] >  y[0])
#define OP_GE_VV(OFF)   (double)(x[i + (OFF)] >= y[i + (OFF)])
#define OP_GE_VS(OFF)   (double)(x[i + (OFF)] >= y[0])
#define OP_AND_VV(OFF)  (double)( (x[i + (OFF)] != 0) && (y[i + (OFF)] != 0) )
#define OP_AND_VS(OFF)  (double)( (x[i + (OFF)] != 0) && (y[0]         != 0) )
#define OP_OR_VV(OFF)   (double)( (x[i + (OFF)] != 0) || (y[i + (OFF)] != 0) )
#define OP_OR_VS(OFF)   (double)( (x[i + (OFF)] != 0) || (y[0]         != 0) )
#define OP_REM_VV(OFF)   remainder(x[i + (OFF)], y[i + (OFF)])
#define OP_REM_VS(OFF)   remainder(x[i + (OFF)], y[0])
#define OP_IDIV_VV(OFF)   floor(x[i + (OFF)] / y[i + (OFF)])
#define OP_IDIV_VS(OFF)   floor(x[i + (OFF)] / y[0])
#define OP_MAX_VV(OFF)    MAX(x[i + (OFF)], y[i + (OFF)])
#define OP_MAX_VS(OFF)    MAX(x[i + (OFF)], y[0])
#define OP_MIN_VV(OFF)    MIN(x[i + (OFF)], y[i + (OFF)])
#define OP_MIN_VS(OFF)    MIN(x[i + (OFF)], y[0])
#define OP_ASSIGN_VV(OFF)  y[i + (OFF)]
#define OP_ASSIGN_VS(OFF)  y[0]
#define OP_SUMSQ_VV(OFF)   x[i + (OFF)] * x[i + (OFF)]  + y[i + (OFF)] * y[i + (OFF)]
#define OP_SUMSQ_VS(OFF)   x[i + (OFF)] * x[i + (OFF)]  + y[0] * y[0]
#define OP_DIFFSQ_VV(OFF)  x[i + (OFF)] * x[i + (OFF)]  - y[i + (OFF)] * y[i + (OFF)]
#define OP_DIFFSQ_VS(OFF)  x[i + (OFF)] * x[i + (OFF)]  - y[0] * y[0]


BINARYOP(add   , OP_ADD_VV    , OP_ADD_VS    )
BINARYOP(sub   , OP_SUB_VV    , OP_SUB_VS    )
BINARYOP(mul   , OP_MUL_VV    , OP_MUL_VS    )
BINARYOP(div   , OP_DIV_VV    , OP_DIV_VS    )
BINARYOP(pow   , OP_POW_VV    , OP_POW_VS    )
BINARYOP(eq    , OP_EQ_VV     , OP_EQ_VS     )
BINARYOP(ne    , OP_NE_VV     , OP_NE_VS     )
BINARYOP(lt    , OP_LT_VV     , OP_LT_VS     )
BINARYOP(le    , OP_LE_VV     , OP_LE_VS     )
BINARYOP(gt    , OP_GT_VV     , OP_GT_VS     )
BINARYOP(ge    , OP_GE_VV     , OP_GE_VS     )
BINARYOP(and   , OP_AND_VV    , OP_AND_VS    )
BINARYOP(or    , OP_OR_VV     , OP_OR_VS     )
BINARYOP(rem   , OP_REM_VV    , OP_REM_VS    )
BINARYOP(idiv  , OP_IDIV_VV   , OP_IDIV_VS   )
BINARYOP(max   , OP_MAX_VV    , OP_MAX_VS    )
BINARYOP(min   , OP_MIN_VV    , OP_MIN_VS    )
BINARYOP(assign, OP_ASSIGN_VV , OP_ASSIGN_VS )
BINARYOP(sumsq , OP_SUMSQ_VV  , OP_SUMSQ_VS  )
BINARYOP(diffsq, OP_DIFFSQ_VV , OP_DIFFSQ_VS )

#define NBINARYOPS 20

int (*binaryfunc[NBINARYOPS]) (double *x, double *y, int xlen, int ylen, int *idx, int idx_len) = {
  br_add_   , //  0 
  br_sub_   , //  1
  br_mul_   , //  2
  br_div_   , //  3
  br_pow_   , //  4
  br_eq_    , //  5
  br_ne_    , //  6
  br_lt_    , //  7
  br_le_    , //  8
  br_gt_    , //  9
  br_ge_    , // 10
  br_and_   , // 11
  br_or_    , // 12
  br_rem_   , // 13
  br_idiv_  , // 14
  br_max_   , // 15
  br_min_   , // 16
  br_assign_, // 17
  br_sumsq_ , // 18
  br_diffsq_  // 19
};

char *binary_names[NBINARYOPS] = {
  "add"   ,
  "sub"   ,
  "mul"   ,
  "div"   ,
  "pow"   ,
  "eq"    ,
  "ne"    ,
  "lt"    ,
  "le"    ,
  "gt"    ,
  "ge"    ,
  "and"   ,
  "or"    ,
  "rem"   ,
  "idiv"  ,
  "max"   ,
  "min"   ,
  "assign",
  "sumsq" ,
  "diffsq"
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_op_binary_(SEXP op_, SEXP x_, SEXP y_, SEXP idx_, SEXP where_, SEXP cols_) {
  
  int xlen = (int)Rf_length(x_);
  int ylen = (int)Rf_length(y_);

  int op = Rf_asInteger(op_);
  if (op < 0 || op >= NBINARYOPS) {
    Rf_error(
      "[br_op_binary_('%s') Loc:1] 'op' %d out of range [0, %i]", 
      binary_names[op], op, NBINARYOPS - 1
    );
  }
  int (*binfunc) (double *x, double *y, int xlen, int ylen, int *idx, int idx_len) = 
    binaryfunc[op];
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // 'x' is a vector, or a matrix where it can just be treated like a vector
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!Rf_isMatrix(x_) || (Rf_isNull(cols_) && ylen != Rf_nrows(x_))) {
    // Treat x_ as a vector. Ignore cols
    if (!Rf_isNull(cols_)) {
      Rf_warning("br_op_binary_(%s): 'cols' is set, but 'x' is not a matrix. Ignoring 'cols'", binary_names[op]);
    }
    int idx_len = 0;
    int status = 0;
    int *idx = location_to_idx(idx_, where_, &idx_len, xlen, &status);
    if (status != 0) {
      Rf_error(
        "[br_op_binary_('%s') Loc:2] location_to_idx() failed",
        binary_names[op]
      );
    }
    int res = binfunc(REAL(x_), REAL(y_), xlen, ylen, idx, idx_len);
    free(idx);
    if (res != 0) {
      Rf_error(
        "[br_op_binary_('%s') Loc:3] Calculation failed",
        binary_names[op]
      );
    }
    return x_;
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // 'x' is a matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isNull(cols_) && ylen == Rf_nrows(x_)) {
    // No cols specified, but 'y' is sized for "by column" 
    int idx_len = 0;
    int status = 0;
    int *idx = location_to_idx(idx_, where_, &idx_len, Rf_nrows(x_), &status);
    if (status != 0) {
      Rf_error(
        "[br_op_binary_('%s') Loc:4] location_to_idx() failed",
        binary_names[op]
      );
    }
    int res = 0;
    
    for (int col = 0; col < Rf_ncols(x_); ++col) {
      res = binfunc(REAL(x_) + col * Rf_nrows(x_), REAL(y_), 
                    Rf_nrows(x_), ylen, 
                    idx, idx_len);
      if (res != 0) {
        free(idx);
        Rf_error(
          "[br_op_binary_('%s') Loc:5] Matrix-vector broadcast failed at column: %i",
          binary_names[op], col
        );
      }
    }
    free(idx);
    return x_;
  } 
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // All cases for a matrix with cols==NULL should be handled before here.
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (Rf_isNull(cols_)) {
    Rf_error(
      "[br_op_binary_('%s') Loc:6] Sanity check failed",
      binary_names[op]
    );
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // User is asking for "by all columns" operation
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  int *cols = NULL;
  int cols_len = 0;
  
  if (Rf_asLogical(cols_) == NA_LOGICAL) {
    // Perform over all columns
    cols = malloc(Rf_ncols(x_) * sizeof(int));
    if (cols == NULL) {
      Rf_error(
        "[br_op_binary_('%s') Loc:7] Failed to allocate 'cols'",
        binary_names[op]
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
        "[br_op_binary_('%s') Loc:8] ridx_to_idx() failed",
        binary_names[op]
      );
    }
    if (cols == NULL) {
      Rf_error(
        "[br_op_binary_('%s') Loc:9] No columns specified? ridx_to_idx() failed",
        binary_names[op]
      );
    }
    cols_len = Rf_length(cols_);
  }
  
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // 'cols' has been specified by user
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
  int idx_len = 0;
  int status = 0;
  
  int *idx = location_to_idx(idx_, where_, &idx_len, Rf_nrows(x_), &status);
  if (status != 0) {
    free(cols);
    Rf_error(
      "[br_op_binary_('%s') Loc:10] location_to_idx() failed",
      binary_names[op]
    );
  }
  
  int res = 0;
  
  if (ylen == xlen) {
    // Treat y_ as a matrix of the same dimensions
    for (int i = 0; i < cols_len; i++) {
      int col = cols[i];
      res += binfunc(REAL(x_) + col * Rf_nrows(x_), 
                        REAL(y_) + col * Rf_nrows(x_), 
                        Rf_nrows(x_), Rf_nrows(x_), 
                        idx, idx_len);
    }
  } else {
    for (int i = 0; i < cols_len; i++) {
      int col = cols[i];
      res += binfunc(REAL(x_) + col * Rf_nrows(x_), REAL(y_), 
                        Rf_nrows(x_), ylen, 
                        idx, idx_len);
    }
  }
  
  free(idx);
  free(cols);
  
  if (res != 0) {
    Rf_error(
      "[br_op_binary_('%s') Loc:11] Matrix operation failed",
      binary_names[op]
    );
  }
  
  return x_;
}





















