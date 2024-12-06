

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Create identity transform
#' 
#' @return 4x4 identity matrix
#' @examples
#' tf_create()
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_create <- function() {
  diag(4)
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Reset a transformation matrix back to the identity matrix
#' @param mat 4x4 transformation matrix
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' mat <- matrix(1, 4, 4)
#' tf_reset(mat)
#' mat
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_reset <- function(mat) {
  invisible(
    .Call(tf_reset_, mat)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add translation to a transformation matrix
#' 
#' @inheritParams tf_reset
#' @param x,y,z translation
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' mat <- tf_create()
#' tf_add_translate(mat, 1, 2, 3)
#' mat
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_add_translate <- function(mat, x = 0, y = 0, z = 0) {
  invisible(
    .Call(tf_add_translate_, mat, x, y, z)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add scaling to a transformation matrix
#' 
#' @inheritParams tf_reset
#' @param x,y,z scaling
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' mat <- tf_create()
#' tf_add_scale(mat, 1, 2, 3)
#' mat
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_add_scale <- function(mat, x = 1, y = x, z = x) {
  invisible(
    .Call(tf_add_scale_, mat, x, y, z)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add rotation to a transformation matrix
#' 
#' @inheritParams tf_reset
#' @param theta rotation angle (radians)
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' mat <- tf_create()
#' tf_add_rotate_z(mat, pi/6)
#' mat
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_add_rotate_x <- function(mat, theta) {
  invisible(
    .Call(tf_add_rotate_x_, mat, theta)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname tf_add_rotate_x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_add_rotate_y <- function(mat, theta) {
  invisible(
    .Call(tf_add_rotate_y_, mat, theta)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname tf_add_rotate_x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_add_rotate_z <- function(mat, theta) {
  invisible(
    .Call(tf_add_rotate_z_, mat, theta)
  )
}




# tf_rotate_x
# tf_rotate_u
# tf_rotate_z
# tf_rotate(mat, theta, x, y, z)
# tf_rotate_about(mat, theta, x, y, z, x0, y0, z0)
# tf_shear

if (FALSE) {
  
  N <- 50
  set.seed(1)
  x <- runif(N)
  y <- runif(N)
  z <- runif(N)
  d <- rep(1, N)
  
  mat <- cbind(x, y, z, d)
  # mat
  
  plot(mat[, 1:2], xlim = c(-1, 1), ylim = c(-1, 1), asp = 1)

  tf <- tf_create() |>
    # tf_add_scale(0.5) |>
    # tf_add_translate(y = 1) |>
    tf_add_translate(x = -0.5, y = -0.5) |>
    tf_add_rotate_z(pi) |>
    tf_add_translate(x = 0.5, y = 0.5) |>
    identity()
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



if (FALSE) {
  
  library(grid)
  
  x11(type = 'dbcairo', antialias = 'none')
  dev.control(displaylist = 'inhibit')  
  
  
  dev.flush()
  dev.flush()
  N <- 21
  N3 <- N^3
  set.seed(1)
  x <- runif(N3, -1, 1)
  y <- runif(N3, -1, 1)
  z <- runif(N3, -1, 1)
  d <- rep(1, nrow(df))
  mat0 <- cbind(x, y, z, d)
  mat  <- duplicate(mat0)
  
  plot(1, xlim = c(-1.15, 1.15), ylim = c(-1.15, 1.15), asp = 1, axes = F, ann = F)
  
  cols <- rainbow(N)
  
  # Transform
  tf <- tf_create() 
  
  gc(full = TRUE)
  
  for (t in 1:1000) {
    
    tf |>
      tf_reset() |>
      tf_add_rotate_x( t / 100) |>
      tf_add_rotate_y( t /  77 + pi / 3) |>
      tf_add_rotate_z(-t /  50 + pi / 6)
    
    br_copy(mat, mat0)
    br_mat_mat_mul_bsq(mat, tf)
    
    # dev.hold()
    # grid.rect(gp = gpar(fill = 'white'))
    # points(mat, pch = 19, cex = 0.5, col = cols)
    # dev.flush()
  }
  
  gc(full = TRUE)
  
  
}




















