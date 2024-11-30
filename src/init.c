
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP is_altrep_(SEXP x_);
extern SEXP is_mutable_(SEXP x_);
extern SEXP get_refcnt_(SEXP x_);
extern SEXP duplicate_(SEXP x_);

extern SEXP alloc_n_  (SEXP n_);
extern SEXP alloc_along_(SEXP x_);
extern SEXP br_zero_ (SEXP x_);

extern SEXP br_sort_(SEXP x_, SEXP decreasing_);
extern SEXP br_shuffle_(SEXP x_);
extern SEXP br_rev_(SEXP x_);
extern SEXP br_runif_(SEXP x_, SEXP min_, SEXP max_);

extern SEXP br_copy_(SEXP x_, SEXP y_, SEXP n_, SEXP xi_, SEXP yi_);
extern SEXP br_copy_if_(SEXP x_, SEXP y_, SEXP lgl_);

extern SEXP br_fill_seq_(SEXP x_, SEXP from_, SEXP to_, SEXP step_);

extern SEXP fmadd_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fmsub_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fnmadd_(SEXP a_, SEXP b_, SEXP c_);
extern SEXP fnmsub_(SEXP a_, SEXP b_, SEXP c_);

extern SEXP br_abs_  (SEXP x_);
extern SEXP br_sqrt_ (SEXP x_);
extern SEXP br_floor_(SEXP x_);
extern SEXP br_ceil_ (SEXP x_);
extern SEXP br_trunc_(SEXP x_);
extern SEXP br_exp_  (SEXP x_);
extern SEXP br_log_  (SEXP x_);
extern SEXP br_cos_  (SEXP x_);
extern SEXP br_sin_  (SEXP x_);
extern SEXP br_tan_  (SEXP x_);
extern SEXP br_not_  (SEXP x_);
extern SEXP br_expm1_(SEXP x_);
extern SEXP br_log1p_(SEXP x_);
extern SEXP br_acos_ (SEXP x_);
extern SEXP br_asin_ (SEXP x_);
extern SEXP br_atan_ (SEXP x_);
extern SEXP br_acosh_(SEXP x_);
extern SEXP br_asinh_(SEXP x_);
extern SEXP br_atanh_(SEXP x_);
extern SEXP br_cosh_ (SEXP x_);
extern SEXP br_sinh_ (SEXP x_);
extern SEXP br_tanh_ (SEXP x_);
extern SEXP br_cospi_(SEXP x_);
extern SEXP br_sinpi_(SEXP x_);
extern SEXP br_tanpi_(SEXP x_);
extern SEXP br_sign_ (SEXP x_);
extern SEXP br_log2_ (SEXP x_);
extern SEXP br_log10_(SEXP x_);

extern SEXP br_cumsum_ (SEXP x_);
extern SEXP br_cumprod_(SEXP x_);
extern SEXP br_cummax_ (SEXP x_);
extern SEXP br_cummin_ (SEXP x_);

extern SEXP br_is_na_  (SEXP x_);
extern SEXP br_round_(SEXP x_, SEXP digits_);


extern SEXP br_add_  (SEXP x_, SEXP y_);
extern SEXP br_sub_  (SEXP x_, SEXP y_);
extern SEXP br_mul_  (SEXP x_, SEXP y_);
extern SEXP br_div_  (SEXP x_, SEXP y_);
extern SEXP br_pow_  (SEXP x_, SEXP y_);
extern SEXP br_eq_   (SEXP x_, SEXP y_);
extern SEXP br_ne_   (SEXP x_, SEXP y_);
extern SEXP br_lt_   (SEXP x_, SEXP y_);
extern SEXP br_le_   (SEXP x_, SEXP y_);
extern SEXP br_gt_   (SEXP x_, SEXP y_);
extern SEXP br_ge_   (SEXP x_, SEXP y_);
extern SEXP br_and_  (SEXP x_, SEXP y_);
extern SEXP br_or_   (SEXP x_, SEXP y_);
extern SEXP br_rem_  (SEXP x_, SEXP y_);
extern SEXP br_idiv_ (SEXP x_, SEXP y_);
extern SEXP br_max_  (SEXP x_, SEXP y_);
extern SEXP br_min_  (SEXP x_, SEXP y_);
extern SEXP br_hypot2_(SEXP x_, SEXP y_);
extern SEXP br_hypot3_(SEXP x_, SEXP y_, SEXP z_);

extern SEXP set_seed_random64_(void);

extern SEXP br_dist2_(SEXP x1_, SEXP y1_, SEXP x2_, SEXP y2_);
extern SEXP br_dist3_(SEXP x1_, SEXP y1_, SEXP z1_, SEXP x2_, SEXP y2_, SEXP z2_);

extern SEXP br_normalise2_(SEXP x_, SEXP y_);
extern SEXP br_normalise3_(SEXP x_, SEXP y_, SEXP z_);

static const R_CallMethodDef CEntries[] = {

  {"is_altrep_"  , (DL_FUNC) &is_altrep_   , 1},
  {"is_mutable_" , (DL_FUNC) &is_mutable_  , 1},
  {"get_refcnt_" , (DL_FUNC) &get_refcnt_  , 1},
  {"duplicate_"  , (DL_FUNC) &duplicate_   , 1},
  
  {"alloc_n_"    , (DL_FUNC) &alloc_n_     , 1},
  {"alloc_along_"  , (DL_FUNC) &alloc_along_   , 1},
  {"br_zero_"   , (DL_FUNC) &br_zero_    , 1},

  {"br_sort_"   , (DL_FUNC) &br_sort_    , 2},
  {"br_shuffle_", (DL_FUNC) &br_shuffle_ , 1},
  {"br_rev_", (DL_FUNC) &br_rev_ , 1},
  {"br_runif_"  , (DL_FUNC) &br_runif_   , 3},
  
  {"br_copy_"    , (DL_FUNC) &br_copy_    , 5},
  {"br_copy_if_" , (DL_FUNC) &br_copy_if_ , 3},
  
  {"br_fill_seq_", (DL_FUNC) &br_fill_seq_, 4},
  
  {"fmadd_" , (DL_FUNC) &fmadd_ , 3},
  {"fmsub_" , (DL_FUNC) &fmsub_ , 3},
  {"fnmadd_", (DL_FUNC) &fnmadd_, 3},
  {"fnmsub_", (DL_FUNC) &fnmsub_, 3},
  
  {"br_abs_"  , (DL_FUNC) &br_abs_  , 1},
  {"br_sqrt_" , (DL_FUNC) &br_sqrt_ , 1},
  {"br_floor_", (DL_FUNC) &br_floor_, 1},
  {"br_ceil_" , (DL_FUNC) &br_ceil_ , 1},
  {"br_trunc_", (DL_FUNC) &br_trunc_, 1},
  {"br_exp_"  , (DL_FUNC) &br_exp_  , 1},
  {"br_log_"  , (DL_FUNC) &br_log_  , 1},
  {"br_cos_"  , (DL_FUNC) &br_cos_  , 1},
  {"br_sin_"  , (DL_FUNC) &br_sin_  , 1},
  {"br_tan_"  , (DL_FUNC) &br_tan_  , 1},
  {"br_not_"  , (DL_FUNC) &br_not_  , 1},
  {"br_expm1_", (DL_FUNC) &br_expm1_, 1},
  {"br_log1p_", (DL_FUNC) &br_log1p_, 1},
  {"br_acos_" , (DL_FUNC) &br_acos_ , 1},
  {"br_asin_" , (DL_FUNC) &br_asin_ , 1},
  {"br_atan_" , (DL_FUNC) &br_atan_ , 1},
  {"br_acosh_", (DL_FUNC) &br_acosh_, 1},
  {"br_asinh_", (DL_FUNC) &br_asinh_, 1},
  {"br_atanh_", (DL_FUNC) &br_atanh_, 1},
  {"br_cosh_" , (DL_FUNC) &br_cosh_ , 1},
  {"br_sinh_" , (DL_FUNC) &br_sinh_ , 1},
  {"br_tanh_" , (DL_FUNC) &br_tanh_ , 1},
  {"br_cospi_", (DL_FUNC) &br_cospi_, 1},
  {"br_sinpi_", (DL_FUNC) &br_sinpi_, 1},
  {"br_tanpi_", (DL_FUNC) &br_tanpi_, 1},
  {"br_sign_" , (DL_FUNC) &br_sign_ , 1},
  {"br_log2_" , (DL_FUNC) &br_log2_ , 1},
  {"br_log10_", (DL_FUNC) &br_log10_, 1},
  
  {"br_cumsum_"  , (DL_FUNC) &br_cumsum_  , 1},
  {"br_cumprod_" , (DL_FUNC) &br_cumprod_ , 1},
  {"br_cummax_"  , (DL_FUNC) &br_cummax_  , 1},
  {"br_cummin_"  , (DL_FUNC) &br_cummin_  , 1},
  
  {"br_is_na_"  , (DL_FUNC) &br_is_na_  , 1},
  {"br_round_", (DL_FUNC) &br_round_, 2},
  
  
  {"br_add_"  , (DL_FUNC) &br_add_  , 2},
  {"br_sub_"  , (DL_FUNC) &br_sub_  , 2},
  {"br_mul_"  , (DL_FUNC) &br_mul_  , 2},
  {"br_div_"  , (DL_FUNC) &br_div_  , 2},
  {"br_pow_"  , (DL_FUNC) &br_pow_  , 2},
  {"br_eq_"   , (DL_FUNC) &br_eq_   , 2},
  {"br_ne_"   , (DL_FUNC) &br_ne_   , 2},
  {"br_lt_"   , (DL_FUNC) &br_lt_   , 2},
  {"br_le_"   , (DL_FUNC) &br_le_   , 2},
  {"br_gt_"   , (DL_FUNC) &br_gt_   , 2},
  {"br_ge_"   , (DL_FUNC) &br_ge_   , 2},
  {"br_and_"  , (DL_FUNC) &br_and_  , 2},
  {"br_or_"   , (DL_FUNC) &br_or_   , 2},
  {"br_rem_"  , (DL_FUNC) &br_rem_  , 2},
  {"br_idiv_" , (DL_FUNC) &br_idiv_ , 2},
  {"br_max_"  , (DL_FUNC) &br_max_  , 2},
  {"br_min_"  , (DL_FUNC) &br_min_  , 2},
  {"br_hypot2_", (DL_FUNC) &br_hypot2_, 2},
  {"br_hypot3_", (DL_FUNC) &br_hypot3_, 3},

  {"set_seed_random64_"     , (DL_FUNC) &set_seed_random64_     , 0},
  
  {"br_dist2_", (DL_FUNC) &br_dist2_, 4},
  {"br_dist3_", (DL_FUNC) &br_dist3_, 6},
  
  {"br_normalise2_", (DL_FUNC) &br_normalise2_, 2},
  {"br_normalise3_", (DL_FUNC) &br_normalise3_, 3},
  
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



