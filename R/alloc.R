
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Allocate a new numeric vector 
#'
#' These functions are like \code{numeric()} except the contents of the vector
#' are not initialized.
#' 
#' \describe{
#'   \item{\code{alloc_n}}{Allocates a numeric vector which can hold 'n' values}
#'   \item{\code{alloc_along}}{Allocates a numeric vector which can hold the same number of values as the given vector}
#' }
#' 
#' @param n length of new numeric vector
#' @param x vector used as template. New vector will be the same length as this vector
#' @return new numeric vector of the required length. Note: This vector 
#'         is \emph{not} initialized to zero.
#' @examples
#' x <- alloc_n(10)
#' br_fill_seq(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_n <- function(n) {
  .Call(alloc_n_, n)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname alloc_n
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_along <- function(x) {
  .Call(alloc_along_, x)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fill with zeros
#' 
#' @inheritParams br_fmadd
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' x <- as.numeric(1:10)
#' br_zero(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_zero <- function(x) {
  invisible(.Call(br_zero_, x))
}

