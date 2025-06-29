

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Copy all or part of one vector into another
#' 
#' @inheritParams br_fmadd
#' @param y Either scalar numeric value or numeric vector of the same 
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
#' Replace elements of one vector with another
#' 
#' This is similar to \code{br_copy()} except that \code{xi} and \code{yi}
#' are vectors of indices into \code{x} and \code{y}, respectively.
#' 
#' @inheritParams br_fmadd
#' @param y A numeric vector
#' @param xi destination indices in \code{x} for the replacement operation
#' @param yi source indices in \code{y} for the replacement. If NULL (the default),
#'        then values are taken sequentially from \code{y}
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' # sequential y indices assumed if 'yi' is NULL (the default)
#' #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' x <- c(1, 2, 3, 4, 5)
#' y <- c(99, 98)
#' xi <- c(1L, 3L)
#' 
#' br_replace(x, xi, y)
#' x
#' 
#' 
#' #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' # explicit y
#' #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' x <- c(1, 2, 3, 4, 5)
#' y <- c(99, 98, 97, 96)
#' xi <- c(1L, 3L)
#' yi <- c(4L, 3L)
#' 
#' br_replace(x, xi, y, yi)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_replace <- function(x, xi, y, yi = NULL) {
  invisible(.Call(br_replace_, x, y, xi, yi))
}


