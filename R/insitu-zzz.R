
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' List of all functions
#' 
#' @examples
#' x <- as.numeric(1:10)
#' with(by_reference, {x + 1; x * 2})
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
by_reference <- list(
  
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # Unary ops
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  `abs`     = br_abs     , 
  `sqrt`    = br_sqrt    , 
  `floor`   = br_floor   , 
  `ceiling` = br_ceil    , 
  `trunc`   = br_trunc   , 
  `round`   = br_round   , 
  `exp`     = br_exp     , 
  `log`     = br_log     , 
  `cos`     = br_cos     , 
  `sin`     = br_sin     , 
  `tan`     = br_tan     , 
  `!`       = br_not     , 
  `expm1`   = br_expm1   , 
  `log1p`   = br_log1p   , 
  `acos`    = br_acos    , 
  `asin`    = br_asin    , 
  `atan`    = br_atan    , 
  `acosh`   = br_acosh   , 
  `asinh`   = br_asinh   , 
  `atanh`   = br_atanh   , 
  `cosh`    = br_cosh    , 
  `sinh`    = br_sinh    , 
  `tanh`    = br_tanh    , 
  `cospi`   = br_cospi   , 
  `sinpi`   = br_sinpi   , 
  `tanpi`   = br_tanpi   , 
  `sign`    = br_sign    , 
  `log2`    = br_log2    , 
  `log10`   = br_log10   , 
  `cumsum`  = br_cumsum  ,
  `cumprod` = br_cumprod ,
  `cummax`  = br_cummax  ,
  `cummin`  = br_cummin  ,
  `is.na`   = br_is_na   ,
  
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # Binary ops
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  `+`     = br_add,
  `-`     = br_sub,
  `*`     = br_mul,
  `/`     = br_div,
  `^`     = br_pow,
  `==`    = br_eq,
  `!=`    = br_ne,
  `<`     = br_lt,
  `<=`    = br_le,
  `>`     = br_gt,
  `>=`    = br_ge,
  `&&`    = br_and,
  `||`    = br_or,
  `%%`    = br_rem,
  `&`     = br_and,
  `|`     = br_or,
  `%`     = br_rem,
  `%/%`   = br_idiv,
  `max`   = br_max,
  `min`   = br_min,
  `hypot` = br_hypot2,
  `hypot2`= br_hypot2,
  
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # Other ops
  #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  `rev`     = br_rev,
  `sort`    = br_sort,
  `shuffle` = br_shuffle,
  fmadd     = br_fmadd,
  fmsub     = br_fmsub,
  fnmadd    = br_fnmadd,
  fnmsub    = br_fnmsub,
  `hypot3`  = br_hypot3,
  dist2     = br_dist2,
  dist3     = br_dist3
)


