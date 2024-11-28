


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Copy segment
#' 
#' @param x,y numeric vectors
#' @param xi,yi starting indices
#' @param n number of elements to copy
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

