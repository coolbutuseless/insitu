

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
int *lgl_to_idx(SEXP lgl_, int *len, int *status) {

  *status = 0;
  int *idx = NULL;
  *len = 0;
  
  if (TYPEOF(lgl_) == INTSXP || TYPEOF(lgl_) == LGLSXP) {
    int *ptr = INTEGER(lgl_);
    for (int i = 0; i < Rf_length(lgl_); ++i) {
      *len += ptr[i] != 0;
    } 
    idx = malloc(*len * sizeof(int));
    if (idx == NULL) {
      *status = 1;
      Rf_warning("lgl_to_idx_(): Couldn't allocate 'idx' (Loc: 1)");
      return NULL;
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
      *status = 1;
      Rf_warning("lgl_to_idx_(): Couldn't allocate 'idx' (Loc: 2)");
      return NULL;
    }
    int *pidx = idx;
    for (int i = 0; i < Rf_length(lgl_); ++i) {
      if (ptr[i] != 0) {
        *pidx++ = i;
      }
    } 
  } else {
    *status = 1;
    idx = NULL;
    Rf_warning("lgl_to_idx_(): Index type not understood");
  }
  
  
  return idx;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert an R index to a C index. 
// Check for outliers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int *ridx_to_idx(SEXP idx_, int ref_len, int *status) {
  
  int *idx = malloc(Rf_length(idx_) * sizeof(int));
  if (idx == NULL) {
    Rf_error("ridx_to_idx_(): Could not allocate 'idx'");
  }
  
  if (TYPEOF(idx_) == INTSXP) {
    int *ptr = INTEGER(idx_);
    for (int i = 0; i < Rf_length(idx_); ++i) {
      int val = ptr[i];
      if (val < 1 || val > ref_len) {
        *status = 1;
        Rf_warning("ridx_to_idx_(): Index out-of-bounds [1, %i]: %i (Loc: 1)", ref_len, val);
        free(idx);
        return NULL;
      } else {
        idx[i] = val - 1;
      }
    }
  } else if (TYPEOF(idx_) == REALSXP) {
    double *ptr = REAL(idx_);
    for (int i = 0; i < Rf_length(idx_); ++i) {
      int val = (int)round(ptr[i]);
      if (val < 1 || val > ref_len) {
        *status = 1;
        Rf_warning("ridx_to_idx_(): Index out-of-bounds [1, %i]: %i (Loc: 2)", ref_len, val);
        free(idx);
        return NULL;
      } else {
        idx[i] = val - 1;
      }
    }
  } else {
    *status = 1;
    Rf_warning("ridx_to_idx_(): Index type not understood");
    free(idx);
  }
  
  return idx;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert 'idx' or 'where' to an integer index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int *location_to_idx(SEXP idx_, SEXP where_, int *idx_len, int ref_len, int *status) {
  int *idx = NULL;
  *status = 0;
  
  if (!Rf_isNull(idx_)) {
    idx = ridx_to_idx(idx_, ref_len, status);
    *idx_len = idx==NULL ? 0 : Rf_length(idx_);
  } else if (!Rf_isNull(where_)) {
    if (Rf_length(where_) != ref_len) {
      *status = 1;
      Rf_warning("location_to_idx_() length(where) = %i does not match ref length %i", Rf_length(where_), ref_len);
    } else {
      idx = lgl_to_idx(where_, idx_len, status);
    }
  }
  
  return idx;
}












