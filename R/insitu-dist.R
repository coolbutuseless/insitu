

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Distance calculation
#' 
#' @param d pre-allocated vector to hold the result
#' @param mat1,mat2 matrices holding (x, y) or (x, y, z) coordinates
#' @return None. Argument \code{d} modified in-place and returned invisibly
#' @examples
#' N <- 10
#' x1 <- rep(1, N)
#' y1 <- runif(N)
#' z1 <- runif(N)
#' x2 <- runif(N)
#' y2 <- runif(N)
#' z2 <- runif(N)
#' mat1 <- cbind(x1, y1, z1)
#' mat2 <- cbind(x2, y2, z2)
#' d <- alloc_n(N)
#' br_mat_dist2(d, mat1, mat2)
#' d
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_dist2 <- function(d, mat1, mat2) {
  invisible(.Call(br_mat_dist2_, d, mat1, mat2))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_mat_dist2
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_dist3 <- function(d, mat1, mat2) {
  invisible(.Call(br_mat_dist3_, d, mat1, mat2))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Hypotenuse length calculation (distance from origin)
#' 
#' @param d pre-allocated numeric vector with length matching \code{nrow(mat)}
#' @param mat numeric matrix 
#' @return None. Argument \code{d} modified in-place and returned invisibly.
#' @examples
#' # Distance from origin in 3D
#' N <- 10
#' x <- rep(1, N)
#' y <- runif(N)
#' z <- runif(N)
#' mat <- cbind(x, y, z)
#' d1 <- alloc_n(N)
#' br_mat_hypot3(d1, mat)
#' d1
#' 
#' # Compare to base R
#' d2 <- sqrt(x * x + y * y + z * z)
#' all.equal(d1, d2)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_hypot2 <- function(d, mat) {
  invisible(.Call(br_mat_hypot2_, d, mat))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_mat_hypot2
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_hypot3 <- function(d, mat) {
  invisible(.Call(br_mat_hypot3_, d, mat))
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Normalise matrix of (x,y) coordinates to length 1
#' 
#' These functions will normalise matrices of (x, y) or (x, y, z) coordinates so that
#' the represented vector quantity have a length of 1.   
#' 
#' @param mat numeric matrix 
#' @return Input matrix modified in-place and returned invisibly.
#' @examples
#' N <- 10
#' x <- runif(N)
#' y <- runif(N)
#' mat <- cbind(x, y)
#' br_mat_normalise2(mat)
#' # Lengths should now be 1.
#' sqrt(mat[,1]^2 + mat[,2]^2)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_normalise2 <- function(mat) {
  invisible(.Call(br_normalise2_, mat))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname br_mat_normalise2
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_normalise3 <- function(mat) {
  invisible(.Call(br_normalise3_, mat))
}

