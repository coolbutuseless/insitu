
<!-- README.md is generated from README.Rmd. Please edit that file -->

# insitu

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
![](https://img.shields.io/badge/api-unstable-orange.svg)
[![R-CMD-check](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

`insitu` provides some functions for operating on numeric vectors
*by-reference* i.e.  without allocating a new vector. (*in situ* is
Latin for “in place”).

Modifying vectors by-reference is often faster than R’s regular
*copy-on-modify* operation because of reduced memory allocation. A
reduction in memory allocation has a corresponding benefit in that the
number of garbage collection operations is also reduced.

## What’s in the box

- `{insitu}` includes most of the standard math operations seen in R.
- Functions have a `br_` prefix - standing for “**b**y **r**eference”.
- The first argument to a function will be overwritten with the result.
- Each R function returns the modified vector invisibly
  - the result does not to be assigned back into this variable.
  - the result should not be assigned into a different variable.

| Function | Description |
|----|----|
| `alloc_n()`, `alloc_along()` | Create new vectors **without** zero-ing contents. Faster than `numeric()` |
| `br_zero()` | fill vector with zeros |
| `br_fmadd()`, `br_fmsub()`, `br_fnmadd()`, `br_fnmsub()` | Fused multiply add (and variants) |
| `br_runif(x, lower = 0, upper = 1)` | Fill vector with uniform random numbers |
| `br_rev(x)` | Reverse vector |
| `br_shuffle(x)` | Shuffle the elements of a vector |
| `br_sort(x)` | Sort the elements of a vector |
| `br_copy(x, y, n, xi, yi)` | copy ‘n’ elements from ‘y’ into ‘x’ starting at ‘xi’ and ‘yi’ |
| `br_fill_seq(x, from, to, step)` | Fill vector with a sequence |
| `br_copy_if(x, y, lgl)` | copy ‘y’ into ‘x’ where `lgl != 0` |
| `br_abs()`, `br_sqrt()`,`br_floor()`,`br_ceil()`, `br_trunc()`, `br_round()`, `br_exp()`, `br_log()`, `br_cos()`, `br_sin()`, `br_tan()`, `br_not()`, `br_expm1()`, `br_log1p()`, `br_acos()`,`br_asin()`, `br_atan()`,`br_acosh()`,`br_asinh()`,`br_atanh()`,`br_cosh()`, `br_sinh()`,`br_tanh()`, `br_sign()`, `br_cospi()`, `br_sinpi()`, `br_tanpi()`, `br_cumsum()`, `br_cumprod()`, `br_cummax()`, `br_cummin()`, `br_log2()`, `br_log10()`, `br_is_na()` | Standard single argument math operations |
| `br_add()`, `br_sub()`, `br_mul()`, `br_div()`, `br_eq()`, `br_ne()`, `br_lt()`, `br_le()`, `br_gt()`, `br_ge()`, `br_and()`, `br_or()`, `br_rem()`, `br_idiv()`, `br_max()`, `br_min()`, `br_mat_hypot()` | Standard two-argument math operations |

| Matrix functions | Description |
|----|----|
| `alloc_matrix(nrow, ncol)` | Allocate a matrix of the given size, but do not initialise |
| `alloc_mat_mat_mul(A, B)` | Allocate a matrix to hold the result of `A * B`, but do not initialise matrix, or perform the calculation |
| `br_mat_mat_mul(C, A, B)` | Multiply two matrices `C <- A %*% B + C` (C must be pre-allocated) |
| `br_mat_mat_mul_bsq(A, B)` | Multiply two matrices `A <- A %*% B` (When `B` is a square matrix) |
| `br_mat_vec_mul(y, A, x)` | `y <- A %*% x` Matrix-Vector multiplication (using a pre-allocated output matrix) |
| `br_mat_vec_mul_asq(A, x)` | `x <- A %*% x` Matrix-Vector multiplication when `A` is a square matrix |
| `br_mat_normalise2(mat)`, `br_mat_normalise3(mat)` | normalise coordinates |
| `br_mat_hypot2(d, mat)` `br_mat_hypot3(d, mat)` | distance from point to origin |
| `br_mat_dist2(d, mat1, mat2)`, `br_mat_dist3(d, mat1, mat2)` | distance between points |
| `br_mat_transpose(mat)` | matrix transpose |

#### RNG

`{insitu}` uses a custom random-number generator called
[lehmer](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/).

This RNG is fast, but it may have slightly different properties compared
to R’s built-in random number generator.

## Installation

You can install from [GitHub](https://github.com/coolbutuseless/insitu)
with:

``` r
# install.packages('remotes')
remotes::install_github('coolbutuseless/insitu')
```

## Operations *by-reference*

*By-reference* operations on vectors can be performed using the `br_*()`
functions in this package.

``` r
x <- as.numeric(1:10)
y <- as.numeric(1:10)
br_add(x, y) # overwrite 'x' with 'x + y'
br_sqrt(x)   # overwrite 'x' with 'sqrt(x)'
x
```

    #>  [1] 1.414214 2.000000 2.449490 2.828427 3.162278 3.464102 3.741657 4.000000
    #>  [9] 4.242641 4.472136

Using `with()` and the `by_reference` helper, it is also possible to
write operations in more idiomatic R

``` r
x <- as.numeric(1:10)
y <- as.numeric(1:10)
with(by_reference, {
  x + y
  sqrt(x)
})
x
```

    #>  [1] 1.414214 2.000000 2.449490 2.828427 3.162278 3.464102 3.741657 4.000000
    #>  [9] 4.242641 4.472136

It is possible to include the extra assignment operator, but this is
redundant.

``` r
x <- as.numeric(1:10)
y <- as.numeric(1:10)
with(by_reference, {
  x <- x + y
  x <- sqrt(x)
})
x
```

    #>  [1] 1.414214 2.000000 2.449490 2.828427 3.162278 3.464102 3.741657 4.000000
    #>  [9] 4.242641 4.472136

## Example: Convolution

This example calculates the convolution of two numeric vectors. It is an
example taken from a presentation [“Byte Code Compiler Recent Work on R
Runtime”](https://www.r-project.org/dsc/2017/slides/tomas_bc.pdf) by
Tomas Kalibera with Luke Tierney Jan Vitek.

The initial `conv_nested()` function is an example of how badly R can
behave with a for-loop and element-by-element access.

When a basic vectorisation is applied (`conv_vec()`) performance is
expected to increase.

A third version of the function (`conv_vec_byref()`) replaces the code
with functions from `{insitu}`.

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Convolution with nested for loops
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
conv_nested <- function(x,y) {
  nx <- length(x)
  ny <- length(y)
  z <- numeric(nx + ny - 1)
  for(i in seq(length = nx)) {
    xi <- x[[i]]
    for(j in seq(length = ny)) {
      ij <- i + j - 1
      z[[ij]] <- z[[ij]] + xi * y[[j]]
    }
  }
  z
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Vectorised base R solution
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
conv_vec <- function(x,y) {
  nx <- length(x)
  ny <- length(y)
  sy <- seq_along(y) - 1L
  z <- numeric(nx + ny - 1)
  for(i in seq(length = nx)) {
    ij <- i + sy
    z <- replace(z, ij, z[ij] + x[[i]] * y)
  }
  z
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Vectorised solution with by-reference routines
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
conv_vec_byref <- function(x,y) {
  nx <- length(x)
  ny <- length(y)
  sy <- seq_along(y) - 1L
  z  <- numeric(nx + ny - 1)
  ty <- alloc_along(y) # allocate temporary working space
  tz <- alloc_along(y) # allocate temp working space
  for(i in seq(length = nx)) {
    br_copy(ty, y)                         # ty <- y
    br_copy(tz, z, n = ny, xi = 1, yi = i) # tz <- z[i + seq(ny) - 1L]
    br_fmadd(ty, x[[i]], tz)               # ty <- ty * x[[i]] + tz
    br_copy(z, ty, n = ny, xi = i)         # z[i + seq(ny) - 1L] <- tv
  }
  z
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Convolve using base R 'convolve()' which uses FFT
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
conv_fft <- function(x, y) {
  convolve(x, rev(y), type = "o")
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Benchmark
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set.seed(1)
N <- 1000
x <- runif(N)
y <- runif(N)
bm <- bench::mark(
  conv_nested(x, y),
  conv_vec(x, y),
  conv_fft(x, y),
  conv_vec_byref(x, y)
)[, 1:5] 

knitr::kable(bm)
```

| expression           |     min |  median |   itr/sec | mem_alloc |
|:---------------------|--------:|--------:|----------:|----------:|
| conv_nested(x, y)    | 61.06ms | 61.47ms |  16.25189 |    88.5KB |
| conv_vec(x, y)       | 10.09ms |    11ms |  91.21590 |    34.6MB |
| conv_fft(x, y)       |   3.6ms |  3.68ms | 270.32186 |     380KB |
| conv_vec_byref(x, y) |  2.87ms |  2.97ms | 321.81867 |   115.9KB |

## Matrix-matrix multiplication

By-reference matrix multiplication still uses R’s linked BLAS functions,
and requires pre-allocation of the output matrix (or vector).

Use the helper function `alloc_mat_mat_mul()` to allocate a matrix to
fit the result of the given multiplication (but this matrix can be
created however you want).

Note that `br_mat_mat_mul()` exposes the full interface to the BLAS
function
[dgemm()](https://www.math.utah.edu/software/lapack/lapack-blas/dgemm.html).
`dgemm()` allows any matrix of the form `C = alpha * A * B + beta * C`
to be calculated (include options to transpose `A` or `B`)

``` r
# Two matrices to multiply
k <- 500
set.seed(1)
A <- matrix(runif(2 * k * k), 2*k, k)
B <- matrix(runif(2 * k * k),   k, 2 * k)  

# Pre-allocate the output location
C <- alloc_mat_mat_mul(A, B)

bench::mark(
  br_mat_mat_mul(C, A, B), # Overwriting 'C' with result.
  A %*% B,                 # Compare to base R
  check = FALSE
)
```

    #> # A tibble: 2 × 6
    #>   expression                   min   median `itr/sec` mem_alloc `gc/sec`
    #>   <bch:expr>              <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
    #> 1 br_mat_mat_mul(C, A, B)    149ms    149ms      6.68    7.87KB     0   
    #> 2 A %*% B                    150ms    150ms      6.65    7.63MB     2.22

Note in the above benchmark that `br_mat_ma_mul()` only allocates
several **kilobytes** of R memory, while `A %*% B` allocates several
**megabytes**.

## Matrix-Matrix multipliction when `B` is a square matrix

If `B` is square, then the result of `A %*% B` is the same size as `A`.

`br_mat_mat_mul_bsq()` is a specialised method for this case.

``` r
# Two matrices to multiply
k <- 500
set.seed(1)
A <- matrix(runif(2 * k * k), 2 * k, 1 * k)
B <- matrix(runif(1 * k * k), 1 * k, 1 * k)  # B is square

bench::mark(
  br_mat_mat_mul_bsq(A, B), # Overwriting 'A' with result.
  A %*% B,                 # Compare to base R
  check = FALSE
)
```

    #> # A tibble: 2 × 6
    #>   expression                    min   median `itr/sec` mem_alloc `gc/sec`
    #>   <bch:expr>               <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
    #> 1 br_mat_mat_mul_bsq(A, B)   73.9ms   75.3ms      13.3    4.86KB     0   
    #> 2 A %*% B                    74.6ms   74.9ms      13.4    3.81MB     2.23
