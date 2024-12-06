% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/alloc.R
\name{br_zero}
\alias{br_zero}
\title{Fill with zeros}
\usage{
br_zero(x)
}
\arguments{
\item{x}{numeric vector. This vector will be modified by-reference to 
contain the result of the calculation}
}
\value{
\code{x} argument is modified by-reference and returned invisibly
}
\description{
Fill with zeros
}
\examples{
x <- as.numeric(1:10)
br_zero(x)
x
}
