

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Reverse a vector in place
#'
#' @inheritParams br_fmadd
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' x <- as.numeric(1:10)
#' br_rev(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_rev <- function(x) {
  invisible(.Call(br_rev_, x))
}

