
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// malloc/free the temporary storage 
// This way R does not have to GC it.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_transpose_(SEXP mat_) {
  
  if (!Rf_isMatrix(mat_)) {
    Rf_error("br_mat_transpose_(): must be a matrix");
  }
  
  int rows = Rf_nrows(mat_);
  int cols = Rf_ncols(mat_);
  
  double *tmp = malloc((size_t)rows * (size_t)cols * sizeof(double));
  if (tmp == NULL) {
    Rf_error("Could not allocate 'tmp'");
  }
  
  R_xlen_t len = Rf_xlength(mat_);
  R_xlen_t i, j;
  R_xlen_t l_1 = len - 1;
  double *mat = REAL(mat_);
  for (i = 0, j = 0; i < len; i++, j += rows) {
    if (j > l_1) j -= l_1;
    tmp[i] = mat[j];
  }
  
  SEXP dims_ = PROTECT(Rf_getAttrib(mat_, R_DimSymbol));
  INTEGER(dims_)[0] = cols;
  INTEGER(dims_)[1] = rows;
  UNPROTECT(1);
  
  memcpy(mat, tmp, (size_t)rows * (size_t)cols * sizeof(double));
  free(tmp);
  return mat_;  
}


