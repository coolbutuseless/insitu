

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Roll a vector
#' 
#' @inheritParams br_abs
#' @param dist Distance to roll. Can be postive or negative
#' @return None. \code{x} modified in-place and returned invisibly
#' @examples
#' x <- c(1, 2, 3, 4, 5)
#' br_roll(x, 2)
#' x
#' br_roll(x, -2)
#' x 
#' br_roll(x, -3)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_roll <- function(x, dist) {
  invisible(
    .Call(br_roll_, x, dist)
  )
}
