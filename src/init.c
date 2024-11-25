
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP is_altrep_(SEXP x_);
extern SEXP is_mutable_(SEXP x_);
extern SEXP get_refcnt_(SEXP x_);
extern SEXP duplicate_(SEXP x_);

extern SEXP ins_replace_(SEXP x_, SEXP n_, SEXP value_);
extern SEXP ins_sort_(SEXP x_, SEXP decreasing_);
extern SEXP ins_shuffle_(SEXP x_);
extern SEXP ins_reverse_(SEXP x_);
extern SEXP ins_fill_(SEXP x_, SEXP value_);
extern SEXP ins_runif_(SEXP x_, SEXP min_, SEXP max_);


extern SEXP fmadd_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fmsub_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fnmadd_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fnmsub_(SEXP a_, SEXP b_, SEXP c_);

extern SEXP ins_add_  (SEXP x_, SEXP y_);
extern SEXP ins_sub_ (SEXP x_, SEXP y_);
extern SEXP ins_mul_  (SEXP x_, SEXP y_);
extern SEXP ins_div_(SEXP x_, SEXP y_);

extern SEXP set_seed_random64_(void);

static const R_CallMethodDef CEntries[] = {

  {"is_altrep_"             , (DL_FUNC) &is_altrep_             , 1},
  {"is_mutable_"            , (DL_FUNC) &is_mutable_            , 1},
  {"get_refcnt_"            , (DL_FUNC) &get_refcnt_            , 1},
  {"duplicate_"             , (DL_FUNC) &duplicate_             , 1},

  {"ins_replace_"        , (DL_FUNC) &ins_replace_        , 3},
  {"ins_sort_"           , (DL_FUNC) &ins_sort_           , 2},
  {"ins_shuffle_"   , (DL_FUNC) &ins_shuffle_   , 1},
  {"ins_reverse_"        , (DL_FUNC) &ins_reverse_        , 1},
  {"ins_fill_"           , (DL_FUNC) &ins_fill_           , 2},
  {"ins_runif_", (DL_FUNC) &ins_runif_, 3},
  
  {"fmadd_" , (DL_FUNC) &fmadd_ , 3},
  {"fmsub_" , (DL_FUNC) &fmsub_ , 3},
  {"fnmadd_", (DL_FUNC) &fnmadd_, 3},
  {"fnmsub_", (DL_FUNC) &fnmsub_, 3},
  
  
  {"ins_add_"  , (DL_FUNC) &ins_add_  , 2},
  {"ins_sub_" , (DL_FUNC) &ins_sub_ , 2},
  {"ins_mul_"  , (DL_FUNC) &ins_mul_  , 2},
  {"ins_div_", (DL_FUNC) &ins_div_, 2},

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



