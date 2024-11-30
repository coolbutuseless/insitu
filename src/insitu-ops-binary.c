

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UNROLL 4 

// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// // addition with vector x,y
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SEXP br_add_vxy_(SEXP x_, SEXP y_) {
//   
//   double *x = REAL(x_);
//   double *y = REAL(y_);
//   
// #define UNROLL 4
//   int i = 0;
//   for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
//     *x++ += *y++;
//     *x++ += *y++;
//     *x++ += *y++;
//     *x++ += *y++;
//   }
//   for (; i< length(x_); i++) {
//     *x++ += *y++;
//   }
//   
//   return x_;
// }
// 
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// // addition with scalar y
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SEXP br_add_sy_(SEXP x_, SEXP y_) {
//   
//   double *x = REAL(x_);
//   double  y = REAL(y_)[0];
//   
// #define UNROLL 4
//   int i = 0;
//   for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {
//     *x++ += y;
//     *x++ += y;
//     *x++ += y;
//     *x++ += y;
//   }
//   for (; i< length(x_); i++) {
//     *x++ += y;
//   }
//   
//   return x_;
// }
// 
// 
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// // 
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SEXP br_add_(SEXP x_, SEXP y_) {
//   
//   R_xlen_t lx = length(x_);
//   R_xlen_t ly = length(y_);
//   
//   if (lx == ly) {
//     return br_add_vxy_(x_, y_);
//   } else if (ly == 1) {
//     return br_add_sy_(x_, y_);
//   }
//   
//   error("br_add(): Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);
// }



// INSBINOP(add, *x++ += *y++, *x++ += y)

#define INSBINOP(nm, vectorop, scalarop)                                         \
SEXP br_##nm##_vxy_(SEXP x_, SEXP y_) {                                         \
                                                                                 \
  double *x = REAL(x_);                                                          \
  double *y = REAL(y_);                                                          \
                                                                                 \
  int i = 0;                                                                     \
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {                           \
    vectorop; ++x;                                                               \
    vectorop; ++x;                                                               \
    vectorop; ++x;                                                               \
    vectorop; ++x;                                                               \
  }                                                                              \
  for (; i< length(x_); i++) {                                                   \
    vectorop; ++x;                                                               \
  }                                                                              \
                                                                                 \
  return x_;                                                                     \
}                                                                                \
                                                                                 \
                                                                                 \
SEXP br_##nm##_sy_(SEXP x_, SEXP y_) {                                          \
                                                                                 \
  double *x = REAL(x_);                                                          \
  double  y = asReal(y_);                                                        \
                                                                                 \
                                                                                 \
  int i = 0;                                                                     \
  for (; i < length(x_) - (UNROLL - 1); i += UNROLL) {                           \
    scalarop; ++x;                                                               \
    scalarop; ++x;                                                               \
    scalarop; ++x;                                                               \
    scalarop; ++x;                                                               \
  }                                                                              \
  for (; i< length(x_); i++) {                                                   \
    scalarop; ++x;                                                               \
  }                                                                              \
                                                                                 \
  return x_;                                                                     \
}                                                                                \
                                                                                 \
                                                                                 \
SEXP br_##nm##_(SEXP x_, SEXP y_) {                                             \
                                                                                 \
  R_xlen_t lx = length(x_);                                                      \
  R_xlen_t ly = length(y_);                                                      \
                                                                                 \
  if (lx == ly) {                                                                \
    return br_##nm##_vxy_(x_, y_);                                              \
  } else if (ly == 1) {                                                          \
    return br_##nm##_sy_(x_, y_);                                               \
  }                                                                              \
                                                                                 \
  error("Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);   \
}


// * Group: Ops
// * "+", "-", "*", "/", "^", "%%", "%/%"
// * "&", "|", "!"
// * "==", "!=", "<", "<=", ">=", ">"


INSBINOP(add, *x += *y++, *x += y)
INSBINOP(sub, *x -= *y++, *x -= y)
INSBINOP(mul, *x *= *y++, *x *= y)
INSBINOP(div, *x /= *y++, *x /= y)
INSBINOP(pow, *x = pow(*x, *y++), *x = pow(*x,  y))
INSBINOP(eq , *x = (double)(*x == *y++), *x = (double)(*x == y))
INSBINOP(ne , *x = (double)(*x != *y++), *x = (double)(*x != y))
INSBINOP(lt , *x = (double)(*x <  *y++), *x = (double)(*x <  y))
INSBINOP(le , *x = (double)(*x <= *y++), *x = (double)(*x <= y))
INSBINOP(gt , *x = (double)(*x >  *y++), *x = (double)(*x >  y))
INSBINOP(ge , *x = (double)(*x >= *y++), *x = (double)(*x >= y))
  
INSBINOP(and, *x = (double)((*x != 0) && (*y++ != 0)), *x = (double)((*x != 0) && (y != 0)))
INSBINOP(or , *x = (double)((*x != 0) || (*y++ != 0)), *x = (double)((*x != 0) || (y != 0)))
  
INSBINOP(rem , *x = remainder(*x, *y++), *x = remainder(*x, y))
INSBINOP(idiv, *x = floor(*x / *y++)   , *x = floor(*x / y))
  
INSBINOP(max, *x = *x > *y++ ? *x : *(y - 1), *x = *x > y ? *x : y)
INSBINOP(min, *x = *x < *y++ ? *x : *(y - 1), *x = *x < y ? *x : y)
  
INSBINOP(hypot2, *x = hypot(*x, *y++), *x = hypot(*x, y))
  

