
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Allocate a new numeric vector 
#'
#' These functions are like \code{numeric()} except the contents of the vector
#' are not initialized.
#' 
#' \describe{
#'   \item{\code{alloc_n}}{Allocates a numeric vector which can hold 'n' values}
#'   \item{\code{alloc_along}}{Allocates a numeric vector which can hold the same number of values as the given vector}
#' }
#' 
#' @param n length of new numeric vector
#' @param x vector used as template. New vector will be the same length as this vector
#' @return new numeric vector of the required length. Note: This vector 
#'         is \emph{not} initialized to zero.
#' @examples
#' x <- alloc_n(10)
#' br_fill_seq(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_n <- function(n) {
  .Call(alloc_n_, n)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname alloc_n
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_along <- function(x) {
  .Call(alloc_along_, x)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fill with zeros
#' 
#' @inheritParams br_fmadd
#' 
#' @return \code{x} argument is modified by-reference and returned invisibly
#' @examples
#' x <- as.numeric(1:10)
#' br_zero(x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_zero <- function(x) {
  invisible(.Call(br_zero_, x))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Allocate empty matrix of the given dimensions.
#' 
#' The values are in the matrix are \emph{not} initialised to zero.
#' 
#' @param nrow,ncol dimensions
#' @return Matrix of the requested dimensions. Values are \emph{not} initialised.
#' @examples
#' m <- alloc_matrix(nrow = 3, ncol = 2)
#' is.matrix(m)
#' dim(m)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_matrix <- function(nrow, ncol) {
  .Call(alloc_matrix_, nrow, ncol)
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Allocate empty matrix for the result of the matrix multiplication \code{A * B}
#' 
#' @inheritParams br_mat_mat_mul
#' @return Uninitialized matrix of the correct size to hold the result 
#' @examples
#' A <- matrix(1, 2, 4)
#' B <- matrix(1, 4, 7)
#' C <- alloc_mat_mat_mul(A, B)
#' is.matrix(C)
#' dim(C)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_mat_mat_mul <- function(A, B, ta = FALSE, tb = FALSE) {
  
  rows <- ifelse(ta, ncol(A), nrow(A))
  cols <- ifelse(tb, nrow(B), ncol(B))
  
  alloc_matrix(rows, cols)
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Allocate empty vector for the result of the matrix-vector multiplication \code{A * x}
#' 
#' @inheritParams br_mat_vec_mul
#' @return Uninitialized vector of the correct size to hold the result of \code{A * x}
#' @examples
#' A <- matrix(1, 2, 4)
#' x <- matrix(1, 4, 1)
#' y <- alloc_mat_vec_mul(A, x)
#' dim(y)
#' br_mat_vec_mul(y, A, x)
#' y
#' # Compare to base R
#' A %*% x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_mat_vec_mul <- function(A, x) {
  alloc_matrix(nrow = nrow(A), ncol = 1)
}

