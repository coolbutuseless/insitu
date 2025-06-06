% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/insitu-ops-unary-cumulative.R
\name{br_cumsum}
\alias{br_cumsum}
\alias{br_cumprod}
\alias{br_cummax}
\alias{br_cummin}
\title{Math operations taking only a single input vector}
\usage{
br_cumsum(x)

br_cumprod(x)

br_cummax(x)

br_cummin(x)
}
\arguments{
\item{x}{numeric vector. This vector will be modified by-reference to 
contain the result of the calculation}
}
\value{
\code{x} argument is modified by-reference and returned invisibly
}
\description{
Math operations taking only a single input vector
}
\examples{
# By-reference \code{abs()}
x <- c(-1, 0, 1)
br_abs(x)
x

# Conditional application of sqrt()
x <- as.numeric(-5:5)
t <- duplicate(x)     # will use this to hold a numeric logical vector
br_gt(t, 0)           # where is the value > 0
br_sqrt(x, where = t) # only sqrt(x) where x > 0
x
}
