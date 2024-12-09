

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Math operations taking only a single input vector
#' 
#' @inheritParams br_fmadd
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
br_cumsum  <- function(x) { invisible(.Call(br_cumulative_, 0L, x)) }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_cumsum
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_cumprod <- function(x) { invisible(.Call(br_cumulative_, 1L, x)) }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_cumsum
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_cummax  <- function(x) { invisible(.Call(br_cumulative_, 2L, x)) }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_cumsum
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_cummin  <- function(x) { invisible(.Call(br_cumulative_, 3L, x)) }



if (FALSE) {
  
  x <- c(NA, 1)
  br_is_na(x)
  br_eq(x, 1)
  x
  
}

