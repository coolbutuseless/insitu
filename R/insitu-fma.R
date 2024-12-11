

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fused multiply add
#' 
#' Performs a compound calculation equivalent to \code{x <- x * a + b} using
#' the best precision from the math library.
#' 
#' \describe{
#'   \item{\code{br_fmadd()}}{Equivalent to: \code{x <- x * a + b}}
#'   \item{\code{br_fmsub()}}{Equivalent to: \code{x <- x * a - b}}
#'   \item{\code{br_fnmadd()}}{Equivalent to: \code{x <- -x * a + b}}
#'   \item{\code{br_fnmsub()}}{Equivalent to: \code{x <- -x * a - b}}
#' }
#' 
#' @param x numeric vector. This vector will be modified by-reference to 
#'        contain the result of the calculation
#' @param a,b Either scalar numeric values or numeric vectors of the same 
#'       length as \code{x}.
#'       
#' @return \code{x} argument is modified by-reference and returned invisibly
#' 
#' @examples
#' x <- c(1, 2, 3)
#' a <- c(2, 3, 4)
#' b <- c(10, 10, 10)
#' br_fmadd(x, a, b)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_fmadd <- function(x, a, b) {
  invisible(.Call(br_fma_, 0L, x, a, b))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_fmadd
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_fmsub <- function(x, a, b) {
  invisible(.Call(br_fma_, 1L, x, a, b))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_fmadd
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_fnmadd <- function(x, a, b) {
  invisible(.Call(br_fma_, 2L, x, a, b))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_fmadd
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_fnmsub <- function(x, a, b) {
  invisible(.Call(br_fma_, 3L, x, a, b))
}



if (FALSE) {
  
  N <- 1000000
  x <- seq_len(N) / N
  a <- rep(2, N)
  b <- rep(3, N)
  
  bench::mark(
    x * a + b,
    br_fmadd(x, a, b),
    check = TRUE
  ) -> zz
  zz[, 1:5]
  plot(zz)

  x <- 1  
  fma(x, 2, 3)
  x
}

