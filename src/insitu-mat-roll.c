

#define R_NO_REMAP


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void roll_vec(double *src, int len, int dist) {

  double *tmp = malloc(dist * sizeof(double));
  if (tmp == NULL) Rf_error("br_mat_roll_()/roll_vec(): Failed to allocate 'tmp'");
  
  // Copy bytes at end into temporary storage
  memcpy(tmp, src + len - dist, dist * sizeof(double));
  
  // Roll values format
  memmove(src + dist, src, (len - dist) * sizeof(double));
  
  // Copy temp storage back into the start of 'x'
  memcpy(src, tmp, dist * sizeof(double));
  
  free(tmp);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reverse a vector in place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_mat_roll_(SEXP x_, SEXP rows_, SEXP cols_) {
  
  // Sanity check input length
  int len  = (int)Rf_length(x_);
  if (len == 0) Rf_error("br_mat_roll_(): Zero-length matrix not supported");
  
  // roll distance wraps around
  int nrows = Rf_nrows(x_);
  int ncols = Rf_ncols(x_);
  
  int rows = Rf_asInteger(rows_);
  int cols = Rf_asInteger(cols_);
  rows = rows % nrows;
  cols = cols % ncols;
  
  if (rows < 0) rows += nrows;
  if (cols < 0) cols += ncols;

  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Roll columns
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (cols > 0) {
    int dist = cols * nrows;
    double *src = REAL(x_);
    
    double *tmp = malloc(dist * sizeof(double));
    if (tmp == NULL) Rf_error("br_mat_roll_(): Failed to allocate 'tmp'");
    
    // Copy bytes at end into temporary storage
    memcpy(tmp, src + len - dist, dist * sizeof(double));
    
    // Roll values format
    memmove(src + dist, src, (len - dist) * sizeof(double));
    
    // Copy temp storage back into the start of 'x'
    memcpy(src, tmp, dist * sizeof(double));
    
    free(tmp);
  }
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Roll rows
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (rows > 0) {
    double *src = REAL(x_);
    for (int col = 0; col < ncols; ++col) {
      roll_vec(src + col * nrows, nrows, rows);
    }
  }
  
  return x_;
}











