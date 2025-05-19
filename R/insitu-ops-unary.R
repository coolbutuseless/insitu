

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Math operations taking only a single input vector
#' 
#' @inheritParams br_fmadd
#' @param where logical vector stored as floating point values. 0 = FALSE, 
#'        all non-zero values treated as TRUE. Default: NULL.
#'        This value indicates if the operation should be performed for the 
#'        corresponding element in \code{x}.
#' @param idx vector of indices
#' @param cols which matrix columns should this apply to?  Argument only valid
#'        if \code{x} is a matrix
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' # By-reference \code{abs()}
#' x <- c(-1, 0, 1)
#' br_abs(x)
#' x
#' 
#' # Conditional application of sqrt()
#' x <- as.numeric(-5:5)
#' t <- duplicate(x)     # will use this to hold a numeric logical vector
#' br_gt(t, 0)           # where is the value > 0
#' br_sqrt(x, where = t) # only sqrt(x) where x > 0
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_abs   <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 0L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_sqrt  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 1L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_floor <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 2L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_ceil  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 3L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_trunc <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 4L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_exp   <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 5L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_log   <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 6L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_log2  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 7L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_log10 <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 8L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_cos   <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 9L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_sin   <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 10L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_tan   <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 11L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_not   <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 12L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_expm1 <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 13L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_log1p <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 14L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_acos  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 15L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_asin  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 16L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_atan  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 17L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_acosh <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 18L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_asinh <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 19L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_atanh <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 20L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_cosh  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 21L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_sinh  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 22L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_tanh  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 23L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_cospi  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 24L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_sinpi  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 25L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_tanpi  <- function(x, idx = NULL, where = NULL, cols = NULL) {  
  invisible(.Call(br_op_unary_, 26L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_sign   <- function(x, idx = NULL, where = NULL, cols = NULL) { 
  invisible(.Call(br_op_unary_, 27L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_is_na <- function(x, idx = NULL, where = NULL, cols = NULL) { 
  invisible(.Call(br_op_unary_, 28L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_zero <- function(x, idx = NULL, where = NULL, cols = NULL) { 
  invisible(.Call(br_op_unary_, 29L, x, idx, where, cols)) 
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_abs
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_pow2 <- function(x, idx = NULL, where = NULL, cols = NULL) { 
  invisible(.Call(br_op_unary_, 30L, x, idx, where, cols)) 
}






#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Not exported
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_unary <- function(op, x, idx = NULL, where = NULL, cols = NULL) { 
  invisible(.Call(br_op_unary_, op, x, idx, where, cols)) 
}





#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Round
#' @inheritParams br_abs
#' @param digits number of decimal places
#' @return \code{x} modified by reference and returned invisibly
#' @examples
#' x <- c(1.234, 5.6789)
#' br_round(x, 2)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_round <- function(x, digits) { invisible(.Call(br_op_unary_round_, x, digits)) }



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fast Round
#'
#' This rounding is about 10x faster than the standard rounding function.  It 
#' uses properties of the bit precision of IEEE-754 floating point numbers to
#' perform the founding with a simple add/subtract operation
#' 
#' @inheritParams br_abs
#' @param digits number of decimal places
#' @return \code{x} modified by reference and returned invisibly
#' @examples
#' x <- c(1.234, 5.6789)
#' br_round(x, 2)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_round_fast <- function(x, digits) { invisible(.Call(br_op_unary_round_fast_, x, digits)) }





if (FALSE) {
  
  x <- c(NA, 1)
  br_is_na(x)
  br_eq(x, 1)
  x
  
}

