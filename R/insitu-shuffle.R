

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Shuffle a vector in place
#'
#' Uses fisher-yates.
#'
#' The \emph{fast} variant of this function uses a xoshiro256++ PRNG which is
#' much faster than sourcing randomness from R's random number generator.
#'
#' @param x vector of values
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ins_shuffle <- function(x) {
  invisible(.Call(ins_shuffle_, x))
}
