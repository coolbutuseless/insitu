

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

