
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Unary
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP br_unary_(SEXP op_, SEXP x_, SEXP idx_, SEXP where_, SEXP cols_);
extern SEXP br_cumulative_(SEXP op_, SEXP x_);
extern SEXP br_round_(SEXP x_, SEXP digits_);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Binary
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP xbr_binary_(SEXP op_, SEXP x_, SEXP y_, SEXP idx_, SEXP where_, SEXP cols_);



extern SEXP set_seed_random64_(void);


extern SEXP br_mat_hypot2_(SEXP d_, SEXP mat_);
extern SEXP br_mat_hypot3_(SEXP d_, SEXP mat_);

extern SEXP br_mat_dist2_(SEXP d_, SEXP mat1_, SEXP mat2_);
extern SEXP br_mat_dist3_(SEXP d_, SEXP mat1_, SEXP mat2_);

extern SEXP br_normalise2_(SEXP mat_);
extern SEXP br_normalise3_(SEXP mat_);


extern SEXP alloc_matrix_(SEXP nrow_, SEXP ncol_);

extern SEXP br_mat_vec_mul_(SEXP y_, SEXP A_, SEXP x_, 
                            SEXP alpha_, SEXP beta_, SEXP ta_);
extern SEXP br_mat_vec_mul_asq_(SEXP A_, SEXP x_, SEXP alpha_, SEXP ta_);  
  
extern SEXP br_mat_mat_mul_full_(SEXP C_, SEXP A_, SEXP B_, 
                                 SEXP alpha_, SEXP beta_, 
                                 SEXP ta_, SEXP tb_);
extern SEXP br_mat_mat_mul_bsq_(SEXP A_, SEXP B_, SEXP alpha_, SEXP tb_);

extern SEXP br_mat_transpose_(SEXP mat_);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Transforms
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP tf_reset_(SEXP mat_);
extern SEXP tf_add_translate_(SEXP mat_, SEXP x_, SEXP y_, SEXP z_);
extern SEXP tf_add_scale_    (SEXP mat_, SEXP x_, SEXP y_, SEXP z_);
extern SEXP tf_add_rotate_x_ (SEXP mat_, SEXP theta_);
extern SEXP tf_add_rotate_y_ (SEXP mat_, SEXP theta_);
extern SEXP tf_add_rotate_z_ (SEXP mat_, SEXP theta_);




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
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Unary
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"br_unary_"     , (DL_FUNC) &br_unary_     , 5},
  {"br_cumulative_", (DL_FUNC) &br_cumulative_, 2},
  {"br_round_"     , (DL_FUNC) &br_round_     , 2},
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Binary
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"xbr_binary_"  , (DL_FUNC) &xbr_binary_  , 6},
  
  
  
  

  {"set_seed_random64_"     , (DL_FUNC) &set_seed_random64_     , 0},
  
  {"br_mat_hypot2_", (DL_FUNC) &br_mat_hypot2_, 2},
  {"br_mat_hypot3_", (DL_FUNC) &br_mat_hypot3_, 2},
  
  {"br_mat_dist2_", (DL_FUNC) &br_mat_dist2_, 3},
  {"br_mat_dist3_", (DL_FUNC) &br_mat_dist3_, 3},
  
  {"br_normalise2_", (DL_FUNC) &br_normalise2_, 1},
  {"br_normalise3_", (DL_FUNC) &br_normalise3_, 1},
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Matrix
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"alloc_matrix_"       , (DL_FUNC) &alloc_matrix_       , 2},
  {"br_mat_vec_mul_"     , (DL_FUNC) &br_mat_vec_mul_     , 6},
  {"br_mat_vec_mul_asq_" , (DL_FUNC) &br_mat_vec_mul_asq_ , 4},
  {"br_mat_mat_mul_full_", (DL_FUNC) &br_mat_mat_mul_full_, 7},
  {"br_mat_mat_mul_bsq_" , (DL_FUNC) &br_mat_mat_mul_bsq_ , 4},
  
  {"br_mat_transpose_", (DL_FUNC) &br_mat_transpose_, 1},
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Transforms
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"tf_reset_", (DL_FUNC) &tf_reset_, 1},
  {"tf_add_translate_", (DL_FUNC) &tf_add_translate_, 4},
  {"tf_add_scale_"    , (DL_FUNC) &tf_add_scale_    , 4},
  {"tf_add_rotate_x_" , (DL_FUNC) &tf_add_rotate_x_ , 2},
  {"tf_add_rotate_y_" , (DL_FUNC) &tf_add_rotate_y_ , 2},
  {"tf_add_rotate_z_" , (DL_FUNC) &tf_add_rotate_z_ , 2},
  
  
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



