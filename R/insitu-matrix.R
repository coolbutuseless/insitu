

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
#' @param ta Should matrix 'A' be transposed? Default: FALSE
#' @param tb Should matrix 'B' be transposed? Default: FALSE
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
#' Matrix-matrix multiplication when B is a square matrix
#' 
#' This function exposes the general matrix multiplication operation from R's
#' included BLAS.  \code{A = alpha * A * B}
#' 
#' @inheritParams br_mat_mat_mul
#' @return C is modified by-reference and returned invisibly
#' @examples
#' A <- matrix(as.numeric(1:32), 8, 4)
#' B <- matrix(as.numeric(1:16), 4, 4)  
#' A %*% B  # Compare to base R
#' 
#' br_mat_mat_mul_bsq(A, B) # By reference. Overwriting 'A'
#' A
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_mat_mul_bsq <- function(A, B, alpha = 1, tb = FALSE) {
  invisible(
    .Call(br_mat_mat_mul_bsq_, A, B, alpha, tb)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Matrix-vector multiplication
#' 
#' This function exposes the general matrix-vector multiplication operation from R's
#' included BLAS.  \code{y = alpha * A * x + beta * y}
#' 
#' @param ta Should matrix 'A' be transposed? Default: FALSE
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
br_mat_vec_mul <- function(y, A, x, alpha = 1, beta = 0, ta = FALSE) {
  invisible(
    .Call(br_mat_vec_mul_, y, A, x, alpha, beta, ta)
  )
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Matrix-vector multiplication when A is square
#' 
#' This function exposes the general matrix-vector multiplication operation from R's
#' included BLAS.  \code{x = alpha * A * x}
#' 
#' @inheritParams br_mat_vec_mul
#' @return None. x is modified by-reference and returned invisibly
#' @examples
#' A <- matrix(1, 3, 3)
#' x <- rep(1, 3)
#' 
#' # Compare to R's method
#' A %*% x
#' 
#' # Calculate. By-reference. Overwriting 'x'
#' br_mat_vec_mul_asq(A, x)
#' x
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_vec_mul_asq <- function(A, x, alpha = 1, ta = FALSE) {
  invisible(
    .Call(br_mat_vec_mul_asq_, A, x, alpha, ta)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Transpose matrix
#' 
#' @param mat matrix
#' @return None. Matrix is modified by-reference and returned invisibly
#' @examples
#' m <- matrix(as.numeric(1:6), 2, 3)
#' m
#' br_mat_transpose(m)
#' m
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_transpose <- function(mat) {
  invisible(
    .Call(br_mat_transpose_, mat)
  )
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Roll elements of a matrix
#' 
#' @param mat matrix
#' @param rows,cols Number of rows and columns to roll
#' @return None. Matrix is modified by-reference and returned invisibly
#' @examples
#' m <- matrix(as.numeric(1:6), 2, 3)
#' m
#' br_mat_roll(m, rows = 3)
#' m
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
br_mat_roll <- function(mat, rows = 0, cols = 0) {
  invisible(
    .Call(br_mat_roll_, mat, rows, cols)
  )
}


