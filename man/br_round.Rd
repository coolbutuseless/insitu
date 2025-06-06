% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/insitu-ops-unary.R
\name{br_round}
\alias{br_round}
\title{Round}
\usage{
br_round(x, digits)
}
\arguments{
\item{x}{numeric vector. This vector will be modified by-reference to 
contain the result of the calculation}

\item{digits}{number of decimal places}
}
\value{
\code{x} modified by reference and returned invisibly
}
\description{
Round
}
\examples{
x <- c(1.234, 5.6789)
br_round(x, 2)
x
}
