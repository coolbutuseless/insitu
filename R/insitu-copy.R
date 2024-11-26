

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


if (FALSE) {
  x <- as.numeric(1:10)
  y <- as.numeric(11:20)
  
  ins_copy(x, y)
  x
}

