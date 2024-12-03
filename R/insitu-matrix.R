

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
#' @param A,B matrices to be multiplied
#' @return Uninitialized matrix of the correct size to hold the result 
#' @examples
#' A <- matrix(1, 2, 4)
#' B <- matrix(1, 4, 7)
#' C <- alloc_matrix_mul(A, B)
#' is.matrix(C)
#' dim(C)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alloc_matrix_mul <- function(A, B) {
  .Call(alloc_matrix_mul_, A, B)
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Matrix-matrix multiply
#' 
#' This function exposes the general matrix multiplication operation from R's
#' included BLAS.  \code{C = alpha * A * B + beta * C}
#' 
#' @param C Matrix which will be modified by-reference
#' @param A,B Primary multiplication matrices
#' @param alpha Scaling factor for \code{A * B}. Default: 1.0
#' @param beta Scaling factor for \code{C}. Default: 0.0
#' @param A_transpose,B_transpose Should matrix be transposed? Default: FALSE
#' @return C is modified by-reference and returned invisibly
#' @examples
#' A <- matrix(1, 8, 4)
#' B <- matrix(2, 4, 4)  
#' C <- matrix(1, nrow(A), ncol(B))
#' 
#' br_mul_mat_mat(C, A, B) # By reference. Overwriting 'C'
#' C
#' 
#' A %*% B  # Compare to base R
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mul_mat_mat <- function(C, A, B, alpha = 1, beta = 0, A_transpose = FALSE, B_transpose = FALSE) {
  invisible(
    .Call(br_mul_mat_mat_full_, C, A, B, alpha, beta, A_transpose, B_transpose)
  )
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Matrix-vector multiply
#' 
#' This function exposes the general matrix-vector multiplication operation from R's
#' included BLAS.  \code{y = alpha * A * x + beta * y}
#' 
#' @param y Vector which will be modified by-reference
#' @param A Matrix
#' @param x vector
#' @param alpha Scaling factor for \code{A * x}. Default: 1.0
#' @param beta Scaling factor for \code{y}. Default: 0.0
#' @param A_transpose Should matrix be transposed? Default: FALSE
#' @return y is modified by-reference and returned invisibly
#' @examples
#' A <- matrix(1, 3, 5)
#' x <- rep(1, 5)
#' y <- rep(0, 3)
#' 
#' # Calculate. By-reference. Overwriting 'y'
#' br_mul_mat_vec(y, A, x)
#' y
#' 
#' # Compare to R's method
#' A %*% x
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mul_mat_vec <- function(y, A, x, alpha = 1, beta = 0, A_transpose = FALSE) {
  invisible(
    .Call(br_mul_mat_vec_, y, A, x, alpha, beta, A_transpose)
  )
}



if (FALSE) {
  
  k <- 100
  A <- matrix(runif(k * k), k, k)
  B <- matrix(runif(k * k), k, k)
  C <- alloc_matrix_mul(A, B)
  
  
  bench::mark(
    A %*% B,
    br_mul_mat_mat_slim(A, B),
    br_mul_mat_mat(C, A, B),
    check = FALSE
  )
  
  
}




