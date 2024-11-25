
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP is_altrep_(SEXP x_);
extern SEXP is_mutable_(SEXP x_);
extern SEXP get_refcnt_(SEXP x_);
extern SEXP duplicate_(SEXP x_);

extern SEXP insitu_replace_(SEXP x_, SEXP n_, SEXP value_);
extern SEXP insitu_sort_(SEXP x_, SEXP decreasing_);
extern SEXP insitu_shuffle_fast_(SEXP x_);
extern SEXP insitu_reverse_(SEXP x_);
extern SEXP insitu_fill_(SEXP x_, SEXP value_);
extern SEXP insitu_fill_runif_fast_(SEXP x_, SEXP min_, SEXP max_);


extern SEXP fmadd_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fmsub_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fnmadd_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fnmsub_(SEXP a_, SEXP b_, SEXP c_);

extern SEXP ins_plus_  (SEXP x_, SEXP y_);
extern SEXP ins_minus_ (SEXP x_, SEXP y_);
extern SEXP ins_mult_  (SEXP x_, SEXP y_);
extern SEXP ins_divide_(SEXP x_, SEXP y_);

extern SEXP set_seed_random64_(void);

static const R_CallMethodDef CEntries[] = {

  {"is_altrep_"             , (DL_FUNC) &is_altrep_             , 1},
  {"is_mutable_"            , (DL_FUNC) &is_mutable_            , 1},
  {"get_refcnt_"            , (DL_FUNC) &get_refcnt_            , 1},
  {"duplicate_"             , (DL_FUNC) &duplicate_             , 1},

  {"insitu_replace_"        , (DL_FUNC) &insitu_replace_        , 3},
  {"insitu_sort_"           , (DL_FUNC) &insitu_sort_           , 2},
  {"insitu_shuffle_fast_"   , (DL_FUNC) &insitu_shuffle_fast_   , 1},
  {"insitu_reverse_"        , (DL_FUNC) &insitu_reverse_        , 1},
  {"insitu_fill_"           , (DL_FUNC) &insitu_fill_           , 2},
  {"insitu_fill_runif_fast_", (DL_FUNC) &insitu_fill_runif_fast_, 3},
  
  {"fmadd_" , (DL_FUNC) &fmadd_ , 3},
  {"fmsub_" , (DL_FUNC) &fmsub_ , 3},
  {"fnmadd_", (DL_FUNC) &fnmadd_, 3},
  {"fnmsub_", (DL_FUNC) &fnmsub_, 3},
  
  
  {"ins_plus_"  , (DL_FUNC) &ins_plus_  , 2},
  {"ins_minus_" , (DL_FUNC) &ins_minus_ , 2},
  {"ins_mult_"  , (DL_FUNC) &ins_mult_  , 2},
  {"ins_divide_", (DL_FUNC) &ins_divide_, 2},

  {"set_seed_random64_"     , (DL_FUNC) &set_seed_random64_     , 0},
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



