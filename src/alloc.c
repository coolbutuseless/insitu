
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Allong 'n' numeric elements
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP alloc_n_(SEXP n_) {
  return Rf_allocVector(REALSXP, Rf_asInteger(n_));
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Alloc numeric vector/matrix from a given template object.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP alloc_along_(SEXP x_) {
  SEXP res_ = PROTECT(Rf_allocVector(REALSXP, Rf_length(x_)));
  
  // Copy dims if 'x' is a matrix or array
  if (Rf_isArray(x_)) {
    SEXP dim_ = PROTECT(Rf_getAttrib(x_, R_DimSymbol));
    Rf_setAttrib(res_, R_DimSymbol, dim_);
    UNPROTECT(1);
  }
  
  UNPROTECT(1);
  return res_;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Alloc matrix of a given size
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP alloc_matrix_(SEXP nrow_, SEXP ncol_) {
  return Rf_allocMatrix(REALSXP, Rf_asInteger(nrow_), Rf_asInteger(ncol_));
}
