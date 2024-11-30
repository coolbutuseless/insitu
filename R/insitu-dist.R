

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Distance calculation
#' 
#' @param x1,y1,z1,x2,y2,z2 numeric vectors all the same length
#' @return \code{x1} modified in-place and returned invisibly
#' @examples
#' N <- 10
#' x1 <- rep(1, N)
#' y1 <- runif(N)
#' z1 <- runif(N)
#' x2 <- runif(N)
#' y2 <- runif(N)
#' z2 <- runif(N)
#' br_dist2(x1, y1, x2, y2)
#' x1
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_dist2 <- function(x1, y1, x2, y2) {
  invisible(.Call(br_dist2_, x1, y1, x2, y2))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_dist2
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_dist3 <- function(x1, y1, z1, x2, y2, z2) {
  invisible(.Call(br_dist3_, x1, y1, z2, x2, y2, z2))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Hypotenuse length calculation (distance from origin)
#' 
#' @param x,y,z numeric vectors all the same length
#' @return \code{x1} modified in-place and returned invisibly
#' @examples
#' # Distance from origin in 3D
#' N <- 10
#' x <- rep(1, N)
#' y <- runif(N)
#' br_hypot2(x, y)
#' x
#'
#' # Distance from origin in 2D
#' x <- rep(1, N)
#' z <- runif(N)
#' br_hypot3(x, y, z)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_hypot <- function(x, y) {
  invisible(.Call(br_hypot2_, x, y))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_hypot
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_hypot2 <- br_hypot


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_hypot
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_hypot3 <- function(x, y, z) {
  invisible(.Call(br_hypot3_, x, y, z))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Normalise vectors to length 1
#' 
#' These functions will normalise the (x, y) or (x, y, z) coordinates so that
#' the represented vector quantity has a length of 1.   All arguments will 
#' be modified in place.
#' 
#' @param x,y,z numeric vectors all the same length
#' @return None. \code{x, y and z} modified in-place.
#' @examples
#' N <- 10
#' x <- runif(N)
#' y <- runif(N)
#' br_normalise2(x, y)
#' x
#' y
#' sqrt(x^2 + y^2)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_normalise2 <- function(x, y) {
  .Call(br_normalise2_, x, y)
  invisible()
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_normalise2
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_normalise3 <- function(x, y, z) {
  .Call(br_normalise3_, x, y, z)
  invisible()
}

