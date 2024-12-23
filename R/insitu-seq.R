

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fill vector with a numeric sequence
#' 
#' @inheritParams br_fmadd
#' @param from starting value in sequence. Default: 1
#' @param to ending value in sequence. Default: NULL.  If NULL, then 
#'        \code{to = length(x) + from - 1}
#' @param step step size. This value is ignored if \code{to} is set.
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' # fill 1:10
#' x <- alloc_n(10)
#' br_seq(x)
#' x
#' 
#' 
#' # fill from 1 to 100
#' x <- alloc_n(10)
#' br_seq(x, from = 1, to = 100)
#' x
#' 
#' # fill from 0 in steps of 2.5
#' x <- alloc_n(10)
#' br_seq(x, from = 0, step = 0.25)
#' x
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_seq <- function(x, from = 1, to = NULL, step = NULL) {
  invisible(.Call(br_seq_, x, from, to, step))
}

