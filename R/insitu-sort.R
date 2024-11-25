

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Sort a vector of real values in-situ
#'
#' @param x vector of real values
#' @param decreasing order. default FALSE
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ins_sort <- function(x, decreasing = FALSE) {
  invisible(.Call(ins_sort_, x, decreasing))
}


