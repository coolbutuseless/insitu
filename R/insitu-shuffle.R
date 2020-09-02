

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Shuffle a vector in place
#'
#' Uses fisher-yates.
#'
#' The \emph{fast} variant of this function uses a lehmer64 PRNG which is
#' much faster than sourcing randomness from R's random number generator.
#'
#' @param x vector of values
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu_shuffle <- function(x) {
  invisible(.Call(insitu_shuffle_, x))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname insitu_shuffle
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu_shuffle_fast <- function(x) {
  invisible(.Call(insitu_shuffle_fast_, x))
}


