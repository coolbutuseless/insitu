
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern SEXP is_altrep_(SEXP x_);
extern SEXP is_mutable_(SEXP x_);
extern SEXP get_refcnt_(SEXP x_);
extern SEXP duplicate_(SEXP x_);

extern SEXP alloc_n_  (SEXP n_);
extern SEXP alloc_along_(SEXP x_);

extern SEXP br_sort_(SEXP x_, SEXP decreasing_);
extern SEXP br_shuffle_(SEXP x_);
extern SEXP br_rev_(SEXP x_);
extern SEXP br_runif_(SEXP x_, SEXP min_, SEXP max_);

extern SEXP br_copy_(SEXP x_, SEXP y_, SEXP n_, SEXP xi_, SEXP yi_);

extern SEXP br_fill_seq_(SEXP x_, SEXP from_, SEXP to_, SEXP step_);

extern SEXP br_fma_(SEXP op_, SEXP x_, SEXP a_, SEXP b_);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Unary
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP br_op_unary_(SEXP op_, SEXP x_, SEXP idx_, SEXP where_, SEXP cols_);
extern SEXP br_op_unary_cumulative_(SEXP op_, SEXP x_);
extern SEXP br_op_unary_round_(SEXP x_, SEXP digits_);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Binary
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP br_op_binary_(SEXP op_, SEXP x_, SEXP y_, SEXP idx_, SEXP where_, SEXP cols_);



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
// Transforms 3-D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP tf3_reset_(SEXP mat_);
extern SEXP tf3_add_translate_(SEXP mat_, SEXP x_, SEXP y_, SEXP z_);
extern SEXP tf3_add_scale_    (SEXP mat_, SEXP x_, SEXP y_, SEXP z_);
extern SEXP tf3_add_rotate_x_ (SEXP mat_, SEXP theta_);
extern SEXP tf3_add_rotate_y_ (SEXP mat_, SEXP theta_);
extern SEXP tf3_add_rotate_z_ (SEXP mat_, SEXP theta_);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Transforms 2-D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP tf2_reset_(SEXP mat_);
extern SEXP tf2_add_translate_(SEXP mat_, SEXP x_, SEXP y_);
extern SEXP tf2_add_scale_    (SEXP mat_, SEXP x_, SEXP y_);
extern SEXP tf2_add_rotate_   (SEXP mat_, SEXP theta_);




static const R_CallMethodDef CEntries[] = {

  {"is_altrep_"  , (DL_FUNC) &is_altrep_   , 1},
  {"is_mutable_" , (DL_FUNC) &is_mutable_  , 1},
  {"get_refcnt_" , (DL_FUNC) &get_refcnt_  , 1},
  {"duplicate_"  , (DL_FUNC) &duplicate_   , 1},
  
  {"alloc_n_"    , (DL_FUNC) &alloc_n_     , 1},
  {"alloc_along_"  , (DL_FUNC) &alloc_along_   , 1},

  {"br_sort_"   , (DL_FUNC) &br_sort_    , 2},
  {"br_shuffle_", (DL_FUNC) &br_shuffle_ , 1},
  {"br_rev_", (DL_FUNC) &br_rev_ , 1},
  {"br_runif_"  , (DL_FUNC) &br_runif_   , 3},
  
  {"br_copy_"    , (DL_FUNC) &br_copy_    , 5},
  
  {"br_fill_seq_", (DL_FUNC) &br_fill_seq_, 4},
  
  {"br_fma_", (DL_FUNC) &br_fma_, 4},
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Unary
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"br_op_unary_"     , (DL_FUNC) &br_op_unary_     , 5},
  {"br_op_unary_cumulative_", (DL_FUNC) &br_op_unary_cumulative_, 2},
  {"br_op_unary_round_"     , (DL_FUNC) &br_op_unary_round_     , 2},
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Binary
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"br_op_binary_"  , (DL_FUNC) &br_op_binary_  , 6},
  
  
  
  

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
  // Transforms 3-D
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"tf3_reset_"        , (DL_FUNC) &tf3_reset_        , 1},
  {"tf3_add_translate_", (DL_FUNC) &tf3_add_translate_, 4},
  {"tf3_add_scale_"    , (DL_FUNC) &tf3_add_scale_    , 4},
  {"tf3_add_rotate_x_" , (DL_FUNC) &tf3_add_rotate_x_ , 2},
  {"tf3_add_rotate_y_" , (DL_FUNC) &tf3_add_rotate_y_ , 2},
  {"tf3_add_rotate_z_" , (DL_FUNC) &tf3_add_rotate_z_ , 2},
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Transforms 2-D
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {"tf2_reset_"        , (DL_FUNC) &tf2_reset_        , 1},
  {"tf2_add_translate_", (DL_FUNC) &tf2_add_translate_, 3},
  {"tf2_add_scale_"    , (DL_FUNC) &tf2_add_scale_    , 3},
  {"tf2_add_rotate_"   , (DL_FUNC) &tf2_add_rotate_   , 2},
  
  
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



