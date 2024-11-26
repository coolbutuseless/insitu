

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Copy
#' 
#' @param x,y numeric vectors of the same length
#' @return modified x invisibly
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ins_copy <- function(x, y) {
  invisible(.Call(ins_copy_, x, y))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Copy segment
#' 
#' @param x,y numeric vectors
#' @param xi,yi starting indices
#' @param n number of elements to copy
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ins_copy_from <- function(x, y, xi, yi, n) {
  invisible(.Call(ins_copy_from_, x, y, xi, yi, n))
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
  ins_copy_from(x, y, 1, 1, 11)
  x
  
  
}

