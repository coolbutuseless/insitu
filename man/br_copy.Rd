% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/insitu-copy.R
\name{br_copy}
\alias{br_copy}
\title{Copy all or part of one vector into another}
\usage{
br_copy(x, y, n = NULL, xi = 1L, yi = 1L)
}
\arguments{
\item{x}{numeric vector. This vector will be modified by-reference to 
contain the result of the calculation}

\item{y}{Either scalar numeric value or numeric vector of the same 
length as \code{x}.}

\item{n}{number of elements to copy. Default: NULL. This default requires
\code{x} and \code{y} to be the same length, and simply copies the full vector
\code{y} into \code{x}.}

\item{xi, yi}{starting indices for the copy operation within the two vectors. 
Default: 1 i.e. the first element}
}
\value{
\code{x} argument is modified by-reference and returned invisibly
}
\description{
Copy all or part of one vector into another
}
\examples{
# x, y are the same length. copy all of 'y' into 'x'
x <- as.numeric(1:10)
y <- as.numeric(10:1)
br_copy(x, y)
x

# copy the last 3 elements of 'y' into the first 3 elements of x
x <- as.numeric(1:10)
y <- as.numeric(10:1)
br_copy(x, y, n = 3, xi = 1, yi = 8)
x

# copy a scalar value into the last 3 elements of x
x <- as.numeric(1:10)
br_copy(x, y = 99, n = 3, xi = -3)
x

}
