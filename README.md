
<!-- README.md is generated from README.Rmd. Please edit that file -->

# insitu

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
![](https://img.shields.io/badge/api-unstable-orange.svg)
[![R-CMD-check](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

`insitu` provides some functions for operating on numeric vectors
*in-place* i.e.  without allocating a new vector.

Modifying vectors in-place is often faster than R’s regular
*copy-on-modify* operation because of reduced memory allocation. A
reduction in memory allocation has a corresponding benefit in that the
number of garbage collection operations is also reduced.

## What’s in the box

- `insitu` includes most of the standard math operations seen in R.
- Functions have a `ins_` prefix.
- The first argument to a function will be overwritten with the result.
- Each R function returns the modified vector invisibly - the result
  does not need to be assigned into a variable.

| insitu | description |
|----|----|
| `alloc_n()`, `alloc_for()` | Create new vectors **without** zero-ing contents. Faster than `numeric()` |
| `ins_zero()` | fill vector with zeros |
| fmadd, fmsub, fnmadd, fnmsub | Fused multiply add |
| ins_runif(x, lower, upper) | Fill vector with uniform random numbers |
| ins_reverse(x) | Reverse vector |
| ins_shuffle(x) | Shuffle the elements of a vector |
| ins_sort(x) | Sort the elements of a vector |
| ins_copy(x, y, n, xi, yi, n) | copy ‘n’ elements from ‘y’ into ‘x’ starting at ‘xi’ and ‘yi’ |
| ins_copy_if(x, y, lgl) | copy ‘y’ into ‘x’ where `lgl != 0` |
| `ins_abs()`, `ins_sqrt()`,`ins_floor()`,`ins_ceil()`, `ins_trunc()`, `ins_round()`, `ins_exp()`, `ins_log()`, `ins_cos()`, `ins_sin()`, `ins_tan()`, `ins_not()`, `ins_expm1()`, `ins_log1p()`, `ins_acos()`,`ins_asin()`, `ins_atan()`,`ins_acosh()`,`ins_asinh()`,`ins_atanh()`,`ins_cosh()`, `ins_sinh()`,`ins_tanh()`, `ins_sign()`, `ins_cospi()`, `ins_sinpi()`, `ins_tanpi()`, `ins_cumsum()`, `ins_cumprod()`, `ins_cummax()`, `ins_cummin()`, `ins_log2()`, `ins_log10()`, `ins_is_na()` | Standard single argument math operations |
| `ins_add()`, `ins_sub()`, `ins_mul()`, `ins_div()`, `ins_eq()`, `ins_ne()`, `ins_lt()`, `ins_le()`, `ins_gt()`, `ins_ge()`, `ins_and()`, `ins_or()`, `ins_rem()`, `ins_idiv()`, `ins_max()`, `ins_min()`, `ins_hypot()` | Standard two-argument math operations |

#### RNG

`insitu` uses a custom random-number generator called
[lehmer](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/).

This RNG is fast, but it may have slightly different properties compared
to R’s built-in random number generator.

#### ALTREP utils

- `is_altrep(x)` tests whether an object is an ALTREP
- `is_mutable(x)` tests whether an object is mutable by checking its
  reference count
- `get_refcnt(x)` returns the reference count for the object

## Installation

You can install from [GitHub](https://github.com/coolbutuseless/insitu)
with:

``` r
# install.packages('remotes')
remotes::install_github('coolbutuseless/insitu')
```

## In-situ arithmetic

In-situ operations on vectors can be performed using the `ins_*()`
functions in this package.

``` r
x <- as.numeric(1:10)
y <- as.numeric(1:10)
ins_add(x, y) # overwrite 'x' with 'x + y'
x
```

    #>  [1]  2  4  6  8 10 12 14 16 18 20

Using the `insitu` helper, it is also possible to write operations in
more idiomatic R

``` r
x <- as.numeric(1:10)
y <- as.numeric(1:10)
with(insitu, {
  x + y
  sqrt(x)
})
x
```

    #>  [1] 1.414214 2.000000 2.449490 2.828427 3.162278 3.464102 3.741657 4.000000
    #>  [9] 4.242641 4.472136

It is possible to include the extra assigment operator, but this is
redundant.

``` r
x <- as.numeric(1:10)
y <- as.numeric(1:10)
with(insitu, {
  x <- x + y
  x <- sqrt(x)
})
x
```

    #>  [1] 1.414214 2.000000 2.449490 2.828427 3.162278 3.464102 3.741657 4.000000
    #>  [9] 4.242641 4.472136

## Example

This example calculates the convolution of two numeric vectors. It is an
example taken from a presentation [“Byte Code Compiler Recent Work on R
Runtime”](https://www.r-project.org/dsc/2017/slides/tomas_bc.pdf) by
Tomas Kalibera with Luke Tierney Jan Vitek.

The initial `conv_nested()` function is an example of how badly R
behaves with a for-loop and element-by-element access.

When a basic vectorisation is applied (`conv_vec()`) performance is
expected to increase.

Using in-place operations (`conv_vec_insitu()`) replaces the code with
functions from `{insitu}`.

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
# Vectorised solution with in-situ operations
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
conv_vec_insitu <- function(x,y) {
  nx <- length(x)
  ny <- length(y)
  sy <- seq_along(y) - 1L
  z <- numeric(nx + ny - 1)
  ty <- duplicate(y)
  tz <- duplicate(y)
  for(i in seq(length = nx)) {
    ins_copy(ty, y)
    ins_copy(tz, z, n = ny, xi = 1, yi = i)
    fmadd(ty, x[[i]], tz)
    ins_copy(z, ty, n = ny, xi = i)
  }
  z
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
  conv_vec_insitu(x, y)
)[, 1:5] 

knitr::kable(bm)
```

| expression            |      min |   median |    itr/sec | mem_alloc |
|:----------------------|---------:|---------:|-----------:|----------:|
| conv_nested(x, y)     | 103.59ms | 103.74ms |   9.636456 |    88.6KB |
| conv_vec(x, y)        |  10.55ms |  10.93ms |  84.786892 |    34.6MB |
| conv_vec_insitu(x, y) |   7.42ms |   7.52ms | 122.263238 |   118.2KB |

## Sort

`ins_sort()` is analogous to `sort()` but sorts values in the current
vector rather than creating a new one.

``` r
x <- as.numeric(sample(10))
x
```

    #>  [1]  3  2  6  4  5  7  1  9  8 10

``` r
ins_sort(x)
x
```

    #>  [1]  1  2  3  4  5  6  7  8  9 10

## Shuffle

`ins_shuffle()` is analogous to `sample()` but shuffles values in the
current vector rather than creating a new one.

``` r
set.seed(1)
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
ins_shuffle(x)
x
```

    #>  [1] 7 3 1 2 8 5 4 6 9 0

## Reverse

`ins_reverse()` is analogous to `rev()` but reverses values in the
current vector rather than creating a new one.

``` r
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
ins_reverse(x)
x
```

    #>  [1] 9 8 7 6 5 4 3 2 1 0

## Fill with random

`ins_runif()` is analogous to `runif()` but generates values in the
current vector rather than creating a new one.

``` r
set.seed(1)
x <- numeric(10)
ins_runif(x, 10, 15)
x
```

    #>  [1] 12.71450 14.52799 14.93769 13.86312 10.52249 11.69022 12.32248 10.53172
    #>  [9] 12.79174 12.46911

## Fused multiply add (FMA)

- `fmadd(x, a, b)` in-situ `x * a + b`
- `fmsub(x, a, b)` in-situ `x * a - b`
- `fnmadd(x, a, b)` in-situ `-x * a + b`
- `fnmsub(x, a, b)` in-situ `-x * a - b`

``` r
x <- as.numeric(1:10)
a <- 2
b <- as.numeric(1:10)
fmadd(x, a, b)
x
```

    #>  [1]  3  6  9 12 15 18 21 24 27 30

## Related Software

- [data.table](https://cran.r-project.org/package=data.table) performs a
  lot of operations in-situ (i.e. “by reference”)
