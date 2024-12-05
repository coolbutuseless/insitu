

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
  
  asize <- ifelse(ta, ncol(A), nrow(A))
  bsize <- ifelse(tb, nrow(B), ncol(B))
  
  alloc_matrix(asize, bsize)
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Matrix-matrix multiplication
#' 
#' This function exposes the general matrix multiplication operation from R's
#' included BLAS.  \code{C = alpha * A * B + beta * C}
#' 
#' @param C Matrix which will be modified by-reference
#' @param A,B Primary multiplication matrices
#' @param alpha Scaling factor for \code{A * B}. Default: 1.0
#' @param beta Scaling factor for \code{C}. Default: 0.0
#' @param ta,tb Should matrix be transposed? Default: FALSE
#' @return C is modified by-reference and returned invisibly
#' @examples
#' A <- matrix(as.numeric(1:32), 8, 4)
#' B <- matrix(as.numeric(1:24), 4, 6)  
#' C <- alloc_mat_mat_mul(A, B)
#' 
#' br_mat_mat_mul(C, A, B) # By reference. Overwriting 'C'
#' C
#' 
#' A %*% B  # Compare to base R
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_mat_mul <- function(C, A, B, alpha = 1, beta = 0, ta = FALSE, tb = FALSE) {
  invisible(
    .Call(br_mat_mat_mul_full_, C, A, B, alpha, beta, ta, tb)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Matrix-vector multiplication
#' 
#' This function exposes the general matrix-vector multiplication operation from R's
#' included BLAS.  \code{y = alpha * A * x + beta * y}
#' 
#' @param y Vector which will be modified by-reference
#' @param A Matrix
#' @param x vector
#' @param alpha Scaling factor for \code{A * x}. Default: 1.0
#' @param beta Scaling factor for \code{y}. Default: 0.0
#' @return y is modified by-reference and returned invisibly
#' @examples
#' A <- matrix(1, 3, 5)
#' x <- rep(1, 5)
#' y <- rep(0, 3)
#' 
#' # Calculate. By-reference. Overwriting 'y'
#' br_mat_vec_mul(y, A, x)
#' y
#' 
#' # Compare to R's method
#' A %*% x
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_vec_mul <- function(y, A, x, alpha = 1, beta = 0) {
  invisible(
    .Call(br_mat_vec_mul_, y, A, x, alpha, beta)
  )
}

