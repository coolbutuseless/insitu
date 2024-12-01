% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/insitu-matrix.R
\name{br_mul_mat_vec}
\alias{br_mul_mat_vec}
\title{Matrix-vector multiply}
\usage{
br_mul_mat_vec(y, A, x, alpha = 1, beta = 0, A_transpose = FALSE)
}
\arguments{
\item{y}{Vector which will be modified by-reference}

\item{A}{Matrix}

\item{x}{vector}

\item{alpha}{Scaling factor for \code{A * x}. Default: 1.0}

\item{beta}{Scaling factor for \code{y}. Default: 0.0}

\item{A_transpose}{Should matrix be transposed? Default: FALSE}
}
\value{
y is modified by-reference and returned invisibly
}
\description{
This function exposes the general matrix-vector multiplication operation from R's
included BLAS.  \code{y = alpha * A * x + beta * y}
}
\examples{
A <- matrix(1, 3, 5)
x <- rep(1, 5)
y <- rep(0, 3)

# Calculate. By-reference. Overwriting 'y'
br_mul_mat_vec(y, A, x)
y

# Compare to R's method
A \%*\% x

}
