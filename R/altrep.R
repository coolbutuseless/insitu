

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Is this an ALTREP object?
#'
#' @param x object
#'
#' @return logical
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
is_altrep <- function(x) {
  .Call(is_altrep_, x)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Duplicate an R object
#'
#' @param x Any R object
#'
#' @return duplicate of the given object
#' @examples
#' x <- c(1, 2, 3)
#' y <- duplicate(x)
#' y
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
duplicate <- function(x) {
  .Call(duplicate_, x)
}
