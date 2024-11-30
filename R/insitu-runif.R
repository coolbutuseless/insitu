

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fill a vector with uniform random values
#' 
#' Random numbers are generated using a Lehmer RNG (also known as Park-Miller RNG).
#' Note: The standard R RNG is only used to seed the Lehmer RNG - which means
#' that \code{set.seed()} can be used for generating repeatable streams.
#'
#' @inheritParams br_fmadd
#' @param lower,upper limits of random numbers generated. Default: 0, 1
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#'
#' @examples
#' set_seed_lehmer(1)
#' x <- alloc_n(10)
#' br_runif(x)
#' x
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_runif <- function(x, lower = 0, upper = 1) {
  invisible(.Call(br_runif_, x, lower, upper))
}
