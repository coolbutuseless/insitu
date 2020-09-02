

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Write values into a vector in-situ
#'
#' @param x vector of real, integer or character values
#' @param idx index at which to start writing
#' @param values values to insert. must be same type as \code{x}
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
insitu_replace <- function(x, idx, values) {
  invisible(.Call(insitu_replace_, x, idx, values))
}


