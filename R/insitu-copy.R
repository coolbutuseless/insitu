

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Copy all or part of one vector into another
#' 
#' @inheritParams br_fmadd
#' @param y Either scalar numeric values or numeric vectors of the same 
#'       length as \code{x}.
#' @param n number of elements to copy. Default: NULL. This default requires
#'        \code{x} and \code{y} to be the same length, and simply copies the full vector
#'        \code{y} into \code{x}.
#' @param xi,yi starting indices for the copy operation within the two vectors. 
#'        Default: 1 i.e. the first element
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' # x, y are the same length. copy all of 'y' into 'x'
#' x <- as.numeric(1:10)
#' y <- as.numeric(10:1)
#' br_copy(x, y)
#' x
#' 
#' # copy the last 3 elements of 'y' into the first 3 elements of x
#' x <- as.numeric(1:10)
#' y <- as.numeric(10:1)
#' br_copy(x, y, n = 3, xi = 1, yi = 8)
#' x
#' 
#' # copy a scalar value into the last 3 elements of x
#' x <- as.numeric(1:10)
#' br_copy(x, y = 99, n = 3, xi = -3)
#' x
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_copy <- function(x, y, n = NULL, xi = 1L, yi = 1L) {
  invisible(.Call(br_copy_, x, y, n, xi, yi))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Copy all or part of one vector into another
#' 
#' @inheritParams br_copy
#' @param where numeric vector the same length as \code{x} containing logical
#'        values where 0 indicates false, and all non-zero values
#'        indicate true
#'        
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' x <- c(-1, 0, 1)
#' 
#' # Where is x < 0?
#' xneg <- duplicate(x)
#' br_lt(xneg, 0) #  xneg <- (xneg < 0)
#' xneg
#' 
#' br_copy_if(x, -99, xneg)
#' x
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_copy_if <- function(x, y, where) {
  invisible(.Call(br_copy_if_, x, y, where))
}

