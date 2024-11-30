

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Initialise the state of this package's Lehmer RNG
#'
#' @param seed initeger seed value
#' @return None.
#' @examples
#' set_seed_lehmer(1)
#' x <- alloc_n(10)
#' br_runif(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_seed_lehmer <- function(seed) {
  set.seed(1)
  invisible(.Call(set_seed_random64_))
}
