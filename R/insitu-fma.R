

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' In-situ Fused multiply add
#' 
#' \code{x = x * a + b}
#' 
#' @param x,a,b vectors of the same length
#' @return \code{x} modified in-place and retuned invisibly
#' @examples
#' x <- c(1, 2, 3)
#' a <- c(2, 3, 4)
#' b <- c(10, 10, 10)
#' fmadd(x, a, b)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fmadd <- function(x, a, b) {
  invisible(.Call(fmadd_, x, a, b))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname fmadd
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fmsub <- function(x, a, b) {
  invisible(.Call(fmsub_, x, a, b))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname fmadd
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fnmadd <- function(x, a, b) {
  invisible(.Call(fnmadd_, x, a, b))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname fmadd
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fnmsub <- function(x, a, b) {
  invisible(.Call(fnmsub_, x, a, b))
}



if (FALSE) {
  
  N <- 1000000
  x <- seq_len(N) / N
  a <- rep(2, N)
  b <- rep(3, N)
  
  bench::mark(
    x * a + b,
    fmadd(x, a, b),
    check = TRUE
  ) -> zz
  zz
  plot(zz)

  x <- 1  
  fma(x, 2, 3)
  x
}

