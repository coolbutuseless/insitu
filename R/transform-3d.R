

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Create identity transform
#' 
#' @return 4x4 identity matrix
#' @examples
#' tf3_new()
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_new <- function() {
  diag(4)
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Reset a transformation matrix back to the identity matrix
#' @param mat 4x4 transformation matrix
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- matrix(1, 4, 4)
#' tf3_reset(tf)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_reset <- function(mat) {
  invisible(
    .Call(tf3_reset_, mat)
  )
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Apply a 3D affine transform to a matrix or data.frame of coordinates
#'
#' @param x matrix or data.frame.  If a matrix, the first two columns must be 
#'        x,y coordinates.  If a data.frame, must contain columns 'x' and 'y'.
#'        Other columns will not be affected.
#' @param tf 4x4 transformation matrix
#' @return None. \code{mat} is modified by reference and returned invisibly
#' @examples
#' # Transform a matrix
#' tf <- tf3_new()
#' tf <- tf3_add_translate(tf, 1, 10, 100)
#' x <- cbind(
#'   x = as.numeric(1:6),
#'   y = as.numeric(1:6),
#'   z = as.numeric(1:6),
#'   other = 999
#' )
#' tf
#' x
#' 
#' tf3_apply(x, tf)
#' x
#' 
#' # Transform a data.frame
#' x <- data.frame(
#'   other = 'hello',
#'   x = as.numeric(1:6),
#'   y = as.numeric(1:6),
#'   z = as.numeric(1:6)
#' )
#' tf3_apply(x, tf)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_apply <- function(x, tf) {
  invisible(
    .Call(tf_apply_, x, tf)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add translation to a transformation matrix
#' 
#' @inheritParams tf3_reset
#' @param x,y,z translation
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- tf3_new()
#' tf3_add_translate(tf, 1, 2, 3)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_add_translate <- function(mat, x = 0, y = 0, z = 0) {
  invisible(
    .Call(tf3_add_translate_, mat, x, y, z)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add scaling to a transformation matrix
#' 
#' @inheritParams tf3_reset
#' @param x,y,z scaling
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- tf3_new()
#' tf3_add_scale(tf, 1, 2, 3)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_add_scale <- function(mat, x = 1, y = x, z = x) {
  invisible(
    .Call(tf3_add_scale_, mat, x, y, z)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add rotation to a transformation matrix
#' 
#' @inheritParams tf3_reset
#' @param theta rotation angle (radians)
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- tf3_new()
#' tf3_add_rotate_x(tf, pi/6)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_add_rotate_x <- function(mat, theta) {
  invisible(
    .Call(tf3_add_rotate_x_, mat, theta)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname tf3_add_rotate_x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_add_rotate_y <- function(mat, theta) {
  invisible(
    .Call(tf3_add_rotate_y_, mat, theta)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname tf3_add_rotate_x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf3_add_rotate_z <- function(mat, theta) {
  invisible(
    .Call(tf3_add_rotate_z_, mat, theta)
  )
}

