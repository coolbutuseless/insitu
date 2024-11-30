

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Sort a vector of real values in-situ
#'
#' @inheritParams br_fmadd
#' @param decreasing Logical. Sort values in decreasing order? default FALSE
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' set.seed(1)
#' x <- sample(as.numeric(1:10))
#' br_sort(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_sort <- function(x, decreasing = FALSE) {
  invisible(.Call(br_sort_, x, decreasing))
}
