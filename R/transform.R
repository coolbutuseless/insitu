

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
#' tf <- matrix(1, 4, 4)
#' tf_reset(tf)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_reset <- function(mat) {
  invisible(
    .Call(tf_reset_, mat)
  )
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Apply a 3D transform to a matrix of coordinates
#'
#' @param mat matrix with at least 4 columns reprsenting (x, y, z) and d
#' @param tf 4x4 transformation matrix
#' @return None. \code{mat} is modified by reference and returned invisibly
#' @examples
#' tf <- tf_create()
#' tf <- tf_add_translate(tf, 1, 2, 3)
#' mat <- cbind(
#'   x = as.numeric(1:6),
#'   y = as.numeric(1:6),
#'   z = as.numeric(1:6),
#'   d = 1
#' )
#' tf
#' mat
#' 
#' tf_apply(mat, tf)
#' mat
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf_apply <- function(mat, tf) {
  invisible(
    .Call(br_mat_mat_mul_bsq_, mat, tf, alpha = 1, tb = TRUE)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add translation to a transformation matrix
#' 
#' @inheritParams tf_reset
#' @param x,y,z translation
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- tf_create()
#' tf_add_translate(tf, 1, 2, 3)
#' tf
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
#' tf <- tf_create()
#' tf_add_scale(tf, 1, 2, 3)
#' tf
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
#' tf <- tf_create()
#' tf_add_rotate_x(tf, pi/6)
#' tf
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

