
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "random64.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Assignment to a vector in-place.
// Using (possibly) non-sequential elements from y
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_replace_(SEXP x_, SEXP y_, SEXP xi_, SEXP yi_) {
  
  if (Rf_isNull(yi_) || Rf_length(yi_) == 0) {
    // do all the y values in sequence
    if (Rf_length(xi_) > Rf_length(y_)) {
      Rf_error("br_replace_() Error mismatch in length of 'xi' (%i) and 'y' (%i)",
               Rf_length(xi_), Rf_length(y_));
    }
      
    int nx = Rf_length(x_);
    // int ny = Rf_length(y_);
    
    for (int i = 0; i < Rf_length(xi_); i++) {
      int idx = INTEGER(xi_)[i];
      if (idx < 1 || idx > nx) {
        Rf_error("br_replace_(): xi[%i] = %i is out of range [1, %i]", i, idx, nx);
      }
      REAL(x_)[idx - 1] = REAL(y_)[i];
    }
        
  } else if (Rf_length(xi_) == Rf_length(yi_)) {
    
    SEXP xii = PROTECT(Rf_coerceVector(xi_, INTSXP));
    SEXP yii = PROTECT(Rf_coerceVector(yi_, INTSXP));
    
    int nx = Rf_length(x_);
    int ny = Rf_length(y_);
    
    for (int i = 0; i < Rf_length(xi_); i++) {
      int xi = INTEGER(xii)[i];
      int yi = INTEGER(yii)[i];
      if (xi < 1 || xi > nx) {
        Rf_error("br_replace_(): xi[%i] = %i is out of range [0, %i]", i, xi, nx);
      }
      if (yi < 1 || yi > nx) {
        Rf_error("br_replace_(): yi[%i] = %i is out of range [0, %i]", i, yi, ny);
      }
      REAL(x_)[xi - 1] = REAL(y_)[yi - 1];
    }
    
    UNPROTECT(2);
  } else {
    Rf_error("br_replace_() Error mismatch in length of 'xi' (%i) and 'yi' (%i)",
             Rf_length(xi_), Rf_length(yi_));
  }
  
  return x_;
}





