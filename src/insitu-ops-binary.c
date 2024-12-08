
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
SEXP br_add_vxy_(SEXP x_, SEXP y_) {

  double *x = REAL(x_);
  double *y = REAL(y_);

  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    *x += *y; ++x; ++y;
    *x += *y; ++x; ++y;
    *x += *y; ++x; ++y;
    *x += *y; ++x; ++y;
  }
  for (; i< Rf_length(x_); ++i) {
    *x += *y; ++x; ++y;
  }

  return x_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with scalar y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_add_sy_(SEXP x_, SEXP y_) {

  double *x = REAL(x_);
  double  y = REAL(y_)[0];

  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    *x += y; ++x;
    *x += y; ++x;
    *x += y; ++x;
    *x += y; ++x;
  }
  for (; i< Rf_length(x_); ++i) {
    *x += y; ++x;
  }

  return x_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with vector x,y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_add_vxy_where_(SEXP x_, SEXP y_, SEXP where_) {
  
  if (Rf_length(where_) != Rf_length(x_)) {
    Rf_error("'where' must be the same length as 'x'.  %.0f != %.0f", 
             (double)Rf_length(where_), (double)Rf_length(x_));
  }
  
  double *x = REAL(x_);
  double *y = REAL(y_);
  double *where = REAL(where_);
  
  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    if (*where++ != 0) *x += *y; ++x; ++y;
    if (*where++ != 0) *x += *y; ++x; ++y;
    if (*where++ != 0) *x += *y; ++x; ++y;
    if (*where++ != 0) *x += *y; ++x; ++y;
  }
  for (; i< Rf_length(x_); ++i) {
    if (*where++ != 0) *x += *y; ++x; ++y;
  }
  
  return x_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// addition with scalar y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_add_sy_where_(SEXP x_, SEXP y_, SEXP where_) {
  
  if (Rf_length(where_) != Rf_length(x_)) {
    Rf_error("'where' must be the same length as 'x'.  %.0f != %.0f", 
             (double)Rf_length(where_), (double)Rf_length(x_));
  }
  
  double *x = REAL(x_);
  double  y = REAL(y_)[0];
  double *where = REAL(where_);
  
  int i = 0;
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {
    if (*where++) *x += y; ++x;
    if (*where++) *x += y; ++x;
    if (*where++) *x += y; ++x;
    if (*where++) *x += y; ++x;
  }
  for (; i< Rf_length(x_); ++i) {
    if (*where++) *x += y; ++x;
  }
  
  return x_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_add_(SEXP x_, SEXP y_, SEXP where_) {

  R_xlen_t lx = Rf_length(x_);
  R_xlen_t ly = Rf_length(y_);

  if (lx == ly) {
    if (Rf_isNull(where_)) {
      return br_add_vxy_(x_, y_);
    } else {
      return br_add_vxy_where_(x_, y_, where_);
    }
  } else if (ly == 1) {
    if (Rf_isNull(where_)) {
      return br_add_sy_(x_, y_);
    } else {
      return br_add_sy_where_(x_, y_, where_);
    }
  }

  Rf_error("br_add(): Lengths not compatible: x = %.0f, y = %.0f", (double)lx, (double)ly);
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//  MEGA MACRO
//  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define INSBINOP(nm, vectorop, scalarop)                                      \
SEXP br_##nm##_vxy_(SEXP x_, SEXP y_) {                                       \
                                                                              \
  double *x = REAL(x_);                                                       \
  double *y = REAL(y_);                                                       \
                                                                              \
  int i = 0;                                                                  \
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {                     \
    vectorop; ++x; ++y;                                                       \
    vectorop; ++x; ++y;                                                       \
    vectorop; ++x; ++y;                                                       \
    vectorop; ++x; ++y;                                                       \
  }                                                                           \
  for (; i< Rf_length(x_); ++i) {                                             \
    vectorop; ++x; ++y;                                                       \
  }                                                                           \
                                                                              \
  return x_;                                                                  \
}                                                                             \
                                                                              \
                                                                              \
SEXP br_##nm##_sy_(SEXP x_, SEXP y_) {                                        \
                                                                              \
  double *x = REAL(x_);                                                       \
  double  y = Rf_asReal(y_);                                                  \
                                                                              \
                                                                              \
  int i = 0;                                                                  \
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {                     \
    scalarop; ++x;                                                            \
    scalarop; ++x;                                                            \
    scalarop; ++x;                                                            \
    scalarop; ++x;                                                            \
  }                                                                           \
  for (; i< Rf_length(x_); ++i) {                                             \
    scalarop; ++x;                                                            \
  }                                                                           \
                                                                              \
  return x_;                                                                  \
}                                                                             \
                                                                              \
                                                                              \
                                                                              \
/* Vector x,y & conditional */                                                \
SEXP br_##nm##_vxy_where_(SEXP x_, SEXP y_, SEXP where_) {                    \
                                                                              \
  if (Rf_length(where_) != Rf_length(x_)) {                                   \
    Rf_error("'where' must be the same length as 'x'.  %.0f != %.0f",         \
             (double)Rf_length(where_), (double)Rf_length(x_));               \
  }                                                                           \
                                                                              \
  double *x = REAL(x_);                                                       \
  double *y = REAL(y_);                                                       \
  double *where = REAL(where_);                                               \
                                                                              \
  int i = 0;                                                                  \
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {                     \
    if (*where++ != 0) vectorop; ++x; ++y;                                    \
    if (*where++ != 0) vectorop; ++x; ++y;                                    \
    if (*where++ != 0) vectorop; ++x; ++y;                                    \
    if (*where++ != 0) vectorop; ++x; ++y;                                    \
  }                                                                           \
  for (; i< Rf_length(x_); ++i) {                                             \
    if (*where++ != 0) vectorop; ++x; ++y;                                    \
  }                                                                           \
                                                                              \
  return x_;                                                                  \
}                                                                             \
                                                                              \
                                                                              \
                                                                              \
/*  scalar y & conditional */                                                 \
SEXP br_##nm##_sy_where_(SEXP x_, SEXP y_, SEXP where_) {                     \
                                                                              \
  if (Rf_length(where_) != Rf_length(x_)) {                                   \
    Rf_error("'where' must be the same length as 'x'.  %.0f != %.0f",         \
             (double)Rf_length(where_), (double)Rf_length(x_));               \
  }                                                                           \
                                                                              \
  double *x = REAL(x_);                                                       \
  double  y = REAL(y_)[0];                                                    \
  double *where = REAL(where_);                                               \
                                                                              \
  int i = 0;                                                                  \
  for (; i < Rf_length(x_) - (UNROLL - 1); i += UNROLL) {                     \
    if (*where++) scalarop; ++x;                                              \
    if (*where++) scalarop; ++x;                                              \
    if (*where++) scalarop; ++x;                                              \
    if (*where++) scalarop; ++x;                                              \
  }                                                                           \
  for (; i< Rf_length(x_); ++i) {                                             \
    if (*where++) scalarop; ++x;                                              \
  }                                                                           \
                                                                              \
  return x_;                                                                  \
}                                                                             \
                                                                              \
/* Dispatch */                                                                \
SEXP br_##nm##_(SEXP x_, SEXP y_, SEXP where_) {                              \
                                                                              \
  R_xlen_t lx = Rf_length(x_);                                                \
  R_xlen_t ly = Rf_length(y_);                                                \
                                                                              \
  if (lx == ly) {                                                             \
    if (Rf_isNull(where_)) {                                                  \
      return br_##nm##_vxy_(x_, y_);                                          \
    } else {                                                                  \
      return br_##nm##_vxy_where_(x_, y_, where_);                            \
    }                                                                         \
  } else if (ly == 1) {                                                       \
    if (Rf_isNull(where_)) {                                                  \
      return br_##nm##_sy_(x_, y_);                                           \
    } else {                                                                  \
      return br_##nm##_sy_where_(x_, y_, where_);                             \
    }                                                                         \
  }                                                                           \
                                                                              \
  Rf_error("Lengths not compatible: x = %.0f, y = %.0f",                      \
           (double)lx, (double)ly);                                           \
}                                                                                    


// * Group: Ops
// * "+", "-", "*", "/", "^", "%%", "%/%"
// * "&", "|", "!"
// * "==", "!=", "<", "<=", ">=", ">"


// INSBINOP(add, *x += *y++, *x += y)
INSBINOP(sub, *x -= *y, *x -= y)
INSBINOP(mul, *x *= *y, *x *= y)
INSBINOP(div, *x /= *y, *x /= y)
INSBINOP(pow, *x = pow(*x, *y), *x = pow(*x,  y))
INSBINOP(eq , *x = (double)(*x == *y), *x = (double)(*x == y))
INSBINOP(ne , *x = (double)(*x != *y), *x = (double)(*x != y))
INSBINOP(lt , *x = (double)(*x <  *y), *x = (double)(*x <  y))
INSBINOP(le , *x = (double)(*x <= *y), *x = (double)(*x <= y))
INSBINOP(gt , *x = (double)(*x >  *y), *x = (double)(*x >  y))
INSBINOP(ge , *x = (double)(*x >= *y), *x = (double)(*x >= y))

INSBINOP(and, *x = (double)((*x != 0) && (*y != 0)), *x = (double)((*x != 0) && (y != 0)))
INSBINOP(or , *x = (double)((*x != 0) || (*y != 0)), *x = (double)((*x != 0) || (y != 0)))

INSBINOP(rem , *x = remainder(*x, *y), *x = remainder(*x, y))
INSBINOP(idiv, *x = floor(*x / *y)   , *x = floor(*x / y))

INSBINOP(max, *x = *x > *y ? *x : *y, *x = *x > y ? *x : y)
INSBINOP(min, *x = *x < *y ? *x : *y, *x = *x < y ? *x : y)


