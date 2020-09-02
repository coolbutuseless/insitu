

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Write value into a vector in-situ
#'
#' @param x vector of real, integer or character values
#' @param value value to fill with vector. must be same type as \code{x}
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu_fill <- function(x, value) {
  invisible(.Call(insitu_fill_, x, value))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Write random values into a vector in-situ
#'
#' @param x vector of real, integer values
#' @param lower,upper limits of random numbers generated
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu_fill_runif <- function(x, lower, upper) {
  invisible(.Call(insitu_fill_runif_, x, lower, upper))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Write random values into a vector in-situ. Uses lehmer64 for RNG
#'
#' @param x vector of real, integer values
#' @param lower,upper limits of random numbers generated
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu_fill_runif_fast <- function(x, lower, upper) {
  invisible(.Call(insitu_fill_runif_fast_, x, lower, upper))
}
