

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Shuffle a vector in place
#'
#' Uses fisher-yates.
#'
#' The \emph{fast} variant of this function uses a xoshiro256++ PRNG which is
#' much faster than sourcing randomness from R's random number generator.
#'
#' @inheritParams br_fmadd
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' set.seed(1)
#' set_seed_lehmer()
#' x <- as.numeric(1:10)
#' br_shuffle(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_shuffle <- function(x) {
  invisible(.Call(br_shuffle_, x))
}
