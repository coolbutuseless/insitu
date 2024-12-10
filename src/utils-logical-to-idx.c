

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
  } else {
    Rf_error("Index type not understood");
  }
  
  
  return idx;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert an R index to a C index. 
// Check for outliers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int *ridx_to_idx(SEXP idx_, int ref_len) {
  
  int *idx = malloc(Rf_length(idx_) * sizeof(int));
  if (idx == NULL) {
    Rf_error("ridx_to_idx(): Could not allocate 'idx'");
  }
  
  if (TYPEOF(idx_) == INTSXP) {
    int *ptr = INTEGER(idx_);
    for (int i = 0; i < Rf_length(idx_); ++i) {
      int val = ptr[i];
      if (val < 1 || val > ref_len) {
        free(idx);
        Rf_error("Index out-of-bounds [1, %i]: %i", ref_len, val);
      }
      idx[i] = val - 1;
    }
  } else if (TYPEOF(idx_) == REALSXP) {
    double *ptr = REAL(idx_);
    for (int i = 0; i < Rf_length(idx_); ++i) {
      int val = (int)round(ptr[i]);
      if (val < 1 || val > ref_len) {
        free(idx);
        Rf_error("Index out-of-bounds [1, %i]: %i", ref_len, val);
      }
      idx[i] = val - 1;
    }
  } else {
    free(idx);
    Rf_error("index type not understood");
  }
  
  return idx;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert 'idx' or 'where' to an integer index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int *location_to_idx(SEXP idx_, SEXP where_, int *idx_len, int ref_len) {
  int *idx = NULL;
  
  if (!Rf_isNull(idx_)) {
    idx = ridx_to_idx(idx_, ref_len);
    *idx_len = Rf_length(idx_);
  } else if (!Rf_isNull(where_)) {
    if (Rf_length(where_) != ref_len) {
      Rf_error("'where' (%i) does not match ref length [%i]", Rf_length(where_), ref_len);
    }
    idx = lgl_to_idx(where_, idx_len);
  }
  
  return idx;
}












