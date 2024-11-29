
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Allocate a new numeric vector 
#'
#' These functions are like \code{numeric()} except the contents of the vector
#' are not initialized
#' 
#' @param n length of new vector
#' @param x new vector will be the same length as this vector
#' @return new vector of the required length
#' @examples
#' alloc_n(10)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_n <- function(n) {
  .Call(alloc_n_, n)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname alloc_n
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_for <- function(x) {
  .Call(alloc_for_, x)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fill with zeros
#' @param x vector
#' @return modified vector. invisibly
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ins_zero <- function(x) {
  invisible(.Call(ins_zero_, x))
}


if (FALSE) {
  
  N <- 100000
  bench::mark(
    alloc_n(N),
    numeric(N),
    check = TRUE
  )
  
}



