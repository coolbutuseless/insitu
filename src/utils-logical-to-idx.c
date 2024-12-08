

#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert a logical to an integer vector.
//
// @param lgl_ R vector. Logical, Integer and REAL accepted
// @param *len Value returned to user. Number of indicies
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int *lgl_to_idx(SEXP lgl_, int *len) {

  int *idx = NULL;
  *len = 0;
  
  if (TYPEOF(lgl_) == INTSXP || TYPEOF(lgl_) == LGLSXP) {
    int *ptr = INTEGER(lgl_);
    for (int i = 0; i < Rf_length(lgl_); ++i) {
      *len += ptr[i] != 0;
    } 
    idx = malloc(*len * sizeof(int));
    if (idx == NULL) {
      Rf_error("lgl_to_idx(): Couldn't allocate 'idx'");
    }
    int *pidx = idx;
    for (int i = 0; i < Rf_length(lgl_); ++i) {
      if (ptr[i] != 0) {
        *pidx++ = i;
      }
    } 
  } else if (TYPEOF(lgl_) == REALSXP) {
    double *ptr = REAL(lgl_);
    for (int i = 0; i < Rf_length(lgl_); ++i) {
      *len += ptr[i] != 0;
    } 
    idx = malloc(*len * sizeof(int));
    if (idx == NULL) {
      Rf_error("lgl_to_idx(): Couldn't allocate 'idx'");
    }
    int *pidx = idx;
    for (int i = 0; i < Rf_length(lgl_); ++i) {
      if (ptr[i] != 0) {
        *pidx++ = i;
      }
    } 
  }
  
  
  return idx;
}

