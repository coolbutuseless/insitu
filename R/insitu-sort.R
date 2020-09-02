

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Sort a vector of real values in-situ
#'
#' @param x vector of real values
#' @param decreasing order. default FALSE
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu_sort <- function(x, decreasing = FALSE) {
  invisible(.Call(insitu_sort_, x, decreasing))
}


