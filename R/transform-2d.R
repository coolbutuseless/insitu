

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Create identity transform for 2-D
#' 
#' @return 3x3 identity matrix
#' @examples
#' tf2_new()
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf2_new <- function() {
  diag(3)
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Reset a 2-D transformation matrix back to the identity matrix
#' 
#' @param mat 3x3 transformation matrix
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- matrix(1, 3, 3)
#' tf2_reset(tf)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf2_reset <- function(mat) {
  invisible(
    .Call(tf2_reset_, mat)
  )
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Apply a 2-D affine transform to a matrix or data.frame of coordinates
#'
#' @param x matrix or data.frame.  If a matrix, the first two columns must be 
#'        x,y coordinates.  If a data.frame, must contain columns 'x' and 'y'.
#'        Other columns will not be affected.
#' @param tf 3x3 transformation matrix
#' @return None. \code{mat} is modified by reference and returned invisibly
#' @examples
#' # Transform a matrix
#' tf <- tf2_new()
#' tf <- tf2_add_translate(tf, 1, 10)
#' x <- cbind(
#'   x = as.numeric(1:6),
#'   y = as.numeric(1:6),
#'   other = 999
#' )
#' tf
#' x
#' 
#' tf2_apply(x, tf)
#' x
#' 
#' # Transform a data.frame
#' x <- data.frame(
#'   other = 'hello',
#'   x = as.numeric(1:6),
#'   y = as.numeric(1:6)
#' )
#' tf2_apply(x, tf)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf2_apply <- function(x, tf) {
  invisible(
    .Call(tf_apply_, x, tf)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add translation to a transformation matrix
#' 
#' @inheritParams tf2_reset
#' @param x,y translation
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- tf2_new()
#' tf2_add_translate(tf, 1, 2)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf2_add_translate <- function(mat, x = 0, y = 0) {
  invisible(
    .Call(tf2_add_translate_, mat, x, y)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add scaling to a transformation matrix
#' 
#' @inheritParams tf2_reset
#' @param x,y scaling
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- tf2_new()
#' tf2_add_scale(tf, 1, 2)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf2_add_scale <- function(mat, x = 1, y = x) {
  invisible(
    .Call(tf2_add_scale_, mat, x, y)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Add rotation to a transformation matrix
#' 
#' @inheritParams tf2_reset
#' @param theta rotation angle (radians)
#' @return None. \code{mat} modified by reference and returned invisibly
#' @examples
#' tf <- tf2_new()
#' tf2_add_rotate(tf, pi/6)
#' tf
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tf2_add_rotate <- function(mat, theta) {
  invisible(
    .Call(tf2_add_rotate_, mat, theta)
  )
}




if (FALSE) {
  
  set.seed(1)
  N <- 100
  x <- runif(N, 0.5, 1)
  y <- runif(N, 0.5, 1)
  mat0 <- cbind(x, y, 1)  
  mat <- duplicate(mat0)
  
  par(mai = c(0.1, 0.1, 0.1, 0.1))
  plot(1, xlim = c(-1.15, 1.15), ylim = c(-1.15, 1.15), asp = 1, axes = T, ann = T)
  points(mat0, pch = 19)
  
  tf <- tf2_new() |> 
    tf2_add_translate(-0.75, -0.75) |>
    tf2_add_rotate(180 * pi / 180) |>
    tf2_add_translate(0.75, 0.75)
  
  br_copy(mat, mat0)
  tf2_apply(mat, tf)
  
  points(mat, pch = 19, cex = 0.5, col = 'red')
  
}
















