

#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fetch a data.frame column by name or else return NULL
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP get_df_col_or_NULL(SEXP df_, const char *str) {
  SEXP col   = R_NilValue;
  SEXP names = Rf_getAttrib(df_, R_NamesSymbol);
  
  for (int i = 0; i < Rf_length(df_); i++) {
    if(strcmp(CHAR(STRING_ELT(names, i)), str) == 0) {
      col = VECTOR_ELT(df_, i);
      break;
    }
  }
  return col;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fetch a data.frame column by name otherwise raise error
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP get_df_col_or_error(SEXP df_, const char *str) {
  SEXP col = get_df_col_or_NULL(df_, str);
  
  if (Rf_isNull(col)) {
    Rf_error("Expected data.frame to have column '%s'", str);
  }
  
  return col;
}







