
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP is_altrep_();
extern SEXP is_mutable_();
extern SEXP get_refcnt_();
extern SEXP duplicate_();

extern SEXP insitu_replace_();
extern SEXP insitu_sort_();
extern SEXP insitu_shuffle_();
extern SEXP insitu_shuffle_fast_();
extern SEXP insitu_reverse_();
extern SEXP insitu_fill_();
extern SEXP insitu_fill_runif_();
extern SEXP insitu_fill_runif_fast_();

static const R_CallMethodDef CEntries[] = {

  {"is_altrep_"             , (DL_FUNC) &is_altrep_             , 1},
  {"is_mutable_"            , (DL_FUNC) &is_mutable_            , 1},
  {"get_refcnt_"            , (DL_FUNC) &get_refcnt_            , 1},
  {"duplicate_"             , (DL_FUNC) &duplicate_             , 1},

  {"insitu_replace_"        , (DL_FUNC) &insitu_replace_        , 3},
  {"insitu_sort_"           , (DL_FUNC) &insitu_sort_           , 2},
  {"insitu_shuffle_"        , (DL_FUNC) &insitu_shuffle_        , 1},
  {"insitu_shuffle_fast_"   , (DL_FUNC) &insitu_shuffle_fast_   , 1},
  {"insitu_reverse_"        , (DL_FUNC) &insitu_reverse_        , 1},
  {"insitu_fill_"           , (DL_FUNC) &insitu_fill_           , 2},
  {"insitu_fill_runif_"     , (DL_FUNC) &insitu_fill_runif_     , 3},
  {"insitu_fill_runif_fast_", (DL_FUNC) &insitu_fill_runif_fast_, 3},
  {NULL , NULL, 0}
};


void R_init_insitu(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
}



