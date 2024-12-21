

#define R_NO_REMAP


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reverse a vector in place
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP br_roll_(SEXP x_, SEXP dist_) {
  
  // Sanity check input length
  int len  = (int)Rf_length(x_);
  if (len == 0) Rf_error("Zero-length vector not supported");
  
  // roll distance wraps around
  int dist = Rf_asInteger(dist_);
  dist = dist % len;
  if (dist < 0) dist += len;
  
  // If roll distance is a multiple of vector length, just return vector
  if (dist == 0) {
    return x_;
  }
  
  double *src = REAL(x_);
  
  double *tmp = malloc(dist * sizeof(double));
  if (tmp == NULL) Rf_error("br_roll_(): Failed to allocate 'tmp'");
  
  // Copy bytes at end into temporary storage
  memcpy(tmp, src + len - dist, dist * sizeof(double));
  
  // Roll values format
  memmove(src + dist, src, (len - dist) * sizeof(double));
  
  // Copy temp storage back into the start of 'x'
  memcpy(src, tmp, dist * sizeof(double));
  
  free(tmp);
  return x_;
}


