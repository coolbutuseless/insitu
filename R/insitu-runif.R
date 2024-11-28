

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Write random values into a vector in-situ. Uses xoshiro256++ for RNG
#'
#' @param x vector of real, integer values
#' @param lower,upper limits of random numbers generated
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ins_runif <- function(x, lower, upper) {
  invisible(.Call(ins_runif_, x, lower, upper))
}
