

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
ybr_sqrt  <- function(x, idx = NULL, where = NULL, cols = NULL) { invisible(.Call(ybr_sqrt_ , x, idx, where, cols)) }

