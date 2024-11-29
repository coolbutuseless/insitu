


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Copy all or part of one vector into another
#' 
#' @param x destination vector.  Will be modified in-place
#' @param y source. Can be scalar of vector of values
#' @param xi,yi starting indices within the two vectors. Default: 1 i.e. the first element
#' @param n number of elements to copy. Default: NULL. This default requires
#'        \code{x} and \code{y} to be the same length, and simply copies the full vector
#'        \code{y} into \code{y}.
#' 
#' @return x modified in-place
#' @examples
#' # x, y are the same length. copy all of 'y' into 'x'
#' x <- as.numeric(1:10)
#' y <- as.numeric(10:1)
#' ins_copy(x, y)
#' x
#' 
#' # copy the last 3 elements of 'y' into the first 3 elements of x
#' x <- as.numeric(1:10)
#' y <- as.numeric(10:1)
#' ins_copy(x, y, n = 3, xi = 1, yi = 8)
#' x
#' 
#' # copy a scalar value into the last 5 elements of x
#' x <- as.numeric(1:10)
#' ins_copy(x, y = 99, n = 5, xi = 6)
#' x
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ins_copy <- function(x, y, n = NULL, xi = 1L, yi = 1L) {
  invisible(.Call(ins_copy_, x, y, n, xi, yi))
}





if (FALSE) {
  x <- as.numeric( 1:10)
  y <- as.numeric(11:20)
  
  ins_copy(x, y)
  x
  
  
  
  
  x <- as.numeric( 1:10)
  y <- as.numeric(11:20)
  x
  y
  ins_copy(x, y, n = 11, xi = 1, yi = 1)
  x
  
  
}

