% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/transform-3d.R
\name{tf3_add_translate}
\alias{tf3_add_translate}
\title{Add translation to a transformation matrix}
\usage{
tf3_add_translate(mat, x = 0, y = 0, z = 0)
}
\arguments{
\item{mat}{4x4 transformation matrix}

\item{x, y, z}{translation}
}
\value{
None. \code{mat} modified by reference and returned invisibly
}
\description{
Add translation to a transformation matrix
}
\examples{
tf <- tf3_new()
tf3_add_translate(tf, 1, 2, 3)
tf
}
