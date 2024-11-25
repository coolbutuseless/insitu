
<!-- README.md is generated from README.Rmd. Please edit that file -->

# insitu

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
[![R-CMD-check](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

`insitu` provides some functions for modifying numeric vectors *in-situ*
(in place a.k.a. by reference) without allocating a new vector.

**Warning**: Unless you are very confident on who has references to your
data, do not use this package for in-place modification.

See the “References” vignette for an example of the differences in how
references behave under copy-on-modify and in-situ modification:
`vignette('references', package = 'insitu')`

## Modifying vectors in-place

**Pros** of modifying in-situ

- Often faster as there is reduced memory allocation (and also reduced
  pressure on the garbage collector)
- Often faster as there is no copying from the original vector into a
  new vector
- By using C, we can override the *copy-on-modify* semantics usually
  used in R (regardless of how many references exist to the given
  object)

**Cons** of modifying in-situ

- Normal R *copy-on-modify* behaviour is not followed - this will be a
  point of confusion as essentially everything in R uses
  *copy-on-modify* and not modification in-place.
- Copying and allocating vectors is already very fast. It only takes a
  few *microseconds* to allocate memory for a vector of 1000 elements
  and assign new values into it. The speed saved by switching to in-situ
  modification will only possibly be useful if this operations is
  performed many, many times.

## Ops

- Group: Math
  - abs, sign, sqrt, floor, ceiling, trunc, round, signif
  - exp, log, expm1, log1p, cos, sin, tan, cospi, sinpi, tanpi, acos,
    asin, atan
  - cosh, sinh, tanh, acosh, asinh, atanh
  - lgamma, gamma, digamma, trigamma
  - cumsum, cumprod, cummax, cummin
- Group: Ops
  - “+”, “-”, “\*“,”/“,”^“,”%%“,”%/%”
  - “&”, “\|”, “!”
  - “==”, “!=”, “\<”, “\<=”, “\>=”, “\>”
- Other
  - Sort
  - fill with uniform random
  - Fused multiply add:
    - fmadd `x * a + b`
    - fnmadd `-x * a + b`
    - fmsub `x * a - b`
    - fnmsub `-x * a - b`

## What’s in the box

| insitu | description |
|----|----|
| fmadd, fmsub, fnmadd, fnmsub | Fused multiply add |
| ins_add, ins_sub, ins_mul, ins_div | inplace `+=`, `-=`, `*=`, `/=` |
| ins_fill(x, value) | Fill vector with the given value |
| ins_runif(x, lower, upper) | Fill vector with uniform random numbers |
| ins_replace(x, pos, values) | Replace values in x with given values starting from the given position |
| ins_reverse(x) | Reverse vector |
| ins_shuffle(x) | Shuffle the elements of a vector |
| ins_sort(x) | Sort the elements of a vector |

#### Fast Variants

A custom random-number generator rather than the one supplied in R.

- On **windows** this RNG is [xoshiro256++](http://prng.di.unimi.it/).
  This does not require a `uint128_t` and compiles cleanly on the GitHub
  CI test server.
- On **other platforms** this RNG is
  [lehmer](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/).
  Use of `uint128_t` on these platforms allows for faster generation of
  random integers on an interval.

Both of these RNGs are very fast, but have different properties to R’s
built in random number generator. Use with caution.

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

## Replace

`ins_replace()` is analogous to `replace()` but replaces values in the
current vector rather than creating a new one.

``` r
x <- numeric(10)
ins_replace(x, 6, c(1, 2, 3, 4, 5))
x
#>  [1] 0 0 0 0 0 1 2 3 4 5
```

## Fill

`ins_fill()` is analogous to `replace()` but assigns the value into the
current vector rather than creating a new one.

``` r
x <- numeric(10)
ins_fill(x, 3)
x
#>  [1] 3 3 3 3 3 3 3 3 3 3
```

## Sort

`ins_sort()` is analogous to `sort()` but sorts values in the current
vector rather than creating a new one.

``` r
x <- as.numeric(sample(10))
x
#>  [1]  8  5  7  2  4  6  1 10  9  3
ins_sort(x)
x
#>  [1]  1  2  3  4  5  6  7  8  9 10
```

## Shuffle

`ins_shuffle()` is analogous to `sample()` but shuffles values in the
current vector rather than creating a new one.

``` r
set.seed(1)
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
ins_shuffle(x)
x
#>  [1] 7 3 1 2 8 5 4 6 9 0
```

## Reverse

`ins_reverse()` is analogous to `rev()` but reverses values in the
current vector rather than creating a new one.

``` r
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
ins_reverse(x)
x
#>  [1] 9 8 7 6 5 4 3 2 1 0
```

## Fill with random

`ins_runif()` is analogous to `runif()` but generates values in the
current vector rather than creating a new one.

``` r
set.seed(1)
x <- numeric(10)
ins_runif(x, 10, 15)
x
#>  [1] 12.71450 14.52799 14.93769 13.86312 10.52249 11.69022 12.32248 10.53172
#>  [9] 12.79174 12.46911
```

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
#>  [1]  3  6  9 12 15 18 21 24 27 30
```

## Related Software

- [data.table](https://cran.r-project.org/package=data.table) performs a
  lot of operations in-situ (i.e. “by reference”)
