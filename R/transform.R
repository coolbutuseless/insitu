
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add a translation transformation to a given matrix
#' 
#' @param mat 4x4 transformation matrix
#' @param x,y,z translation
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' mat <- identity(4)
#' tf_translate(mat, 1, 2 3)
#' mat
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_translate <- function(mat, x = 0, y = 0, z = 0) {
  mat[1, 4] <- mat[1, 4] + x
  mat[2, 4] <- mat[2, 4] + y
  mat[3, 4] <- mat[3, 4] + z
  
  mat
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add a scale transformation to a given matrix
#' 
#' @param mat 4x4 transformation matrix
#' @param x,y,z translation
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' mat <- identity(4)
#' tf_translate(mat, 1, 2 3)
#' mat
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_scale <- function(mat, x = 1, y = x, z = x) {
  mat[1, 1] <- mat[1, 1] * x
  mat[2, 2] <- mat[2, 2] * y
  mat[3, 3] <- mat[3, 3] * z
  
  mat
}


# tf_rotate_x
# tf_rotate_u
# tf_rotate_z
# tf_rotate(mat, theta, x, y, z)
# tf_rotate_about(mat, theta, x, y, z, x0, y0, z0)
# tf_shear

if (FALSE) {
  
  N <- 5000
  x <- runif(N)
  y <- runif(N)
  z <- runif(N)
  d <- rep(1, N)
  
  mat <- cbind(x, y, z, d)
  # mat
  
  plot(mat[, 1:2], xlim = c(-1, 3), ylim = c(-1, 3))

  tf <- diag(4) |>
    tf_scale(0.5) |>
    tf_translate(y = 1)
  tf

  if (FALSE) {
    bench::mark(
      mat %*% t(tf),
      br_mat_mat_mul_bsq(mat, tf, tb = TRUE),
      check = FALSE
    )
  }
  
    
  m2 <- mat %*% t(tf)
  br_mat_mat_mul_bsq(mat, tf, tb = TRUE)
  mat
  
  points(mat[, 1:2], col = 'red')
    
}




