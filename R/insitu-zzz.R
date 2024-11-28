
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' List of all insitu functions
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu <- list(
  
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # Unary ops
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  `abs`     = ins_abs     , 
  `sqrt`    = ins_sqrt    , 
  `floor`   = ins_floor   , 
  `ceiling` = ins_ceil    , 
  `trunc`   = ins_trunc   , 
  `round`   = ins_round   , 
  `exp`     = ins_exp     , 
  `log`     = ins_log     , 
  `cos`     = ins_cos     , 
  `sin`     = ins_sin     , 
  `tan`     = ins_tan     , 
  `!`       = ins_not     , 
  `expm1`   = ins_expm1   , 
  `log1p`   = ins_log1p   , 
  `acos`    = ins_acos    , 
  `asin`    = ins_asin    , 
  `atan`    = ins_atan    , 
  `acosh`   = ins_acosh   , 
  `asinh`   = ins_asinh   , 
  `atanh`   = ins_atanh   , 
  `cosh`    = ins_cosh    , 
  `sinh`    = ins_sinh    , 
  `tanh`    = ins_tanh    , 
  `cospi`   = ins_cospi   , 
  `sinpi`   = ins_sinpi   , 
  `tanpi`   = ins_tanpi   , 
  `sign`    = ins_sign    , 
  `log2`    = ins_log2    , 
  `log10`   = ins_log10   , 
  `cumsum`  = ins_cumsum  ,
  `cumprod` = ins_cumprod ,
  `cummax`  = ins_cummax  ,
  `cummin`  = ins_cummin  ,
  
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # Binary ops
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  `+`     = ins_add,
  `-`     = ins_sub,
  `*`     = ins_mul,
  `/`     = ins_div,
  `^`     = ins_pow,
  `==`    = ins_eq,
  `!=`    = ins_ne,
  `<`     = ins_lt,
  `<=`    = ins_le,
  `>`     = ins_gt,
  `>=`    = ins_ge,
  `&&`    = ins_and,
  `||`    = ins_or,
  `%%`    = ins_rem,
  `&`     = ins_and,
  `|`     = ins_or,
  `%`     = ins_rem,
  `%/%`   = ins_idiv,
  `max`   = ins_max,
  `min`   = ins_min,
  `hypot` = ins_hypot
)


if (FALSE) {
  
  x <- as.numeric(10:1)
  y <- as.numeric(1:10)
  
  x
  y
  
  with(insitu, {
    !(x > y)
  })
  
  x
  
}