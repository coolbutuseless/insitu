
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
| ins_plus, ins_minus, ins_mult, ins_divide | inplace `+=`, `-=`, `*=`, `/=` |
| insitu_fill(x, value) | Fill vector with the given value |
| insitu_fill_runif_fast(x, lower, upper) | Fill vector with uniform random numbers |
| insitu_replace(x, pos, values) | Replace values in x with given values starting from the given position |
| insitu_reverse(x) | Reverse vector |
| insitu_shuffle_fast(x) | Shuffle the elements of a vector |
| insitu_sort(x) | Sort the elements of a vector |

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
# install.package('remotes')
remotes::install_github('coolbutuseless/insitu')
```

## Future possibilities

- In-place radix sort - instead of using `qsort()`
- `cummin`, `cummax` etc
- `negate`
- `diff`

## In-situ Replacement

`insitu_replace()` is analogous to `replace()` but replaces values in
the current vector rather than creating a new one.

``` r
x <- numeric(10)
insitu_replace(x, 6, c(1, 2, 3, 4, 5))
x
#>  [1] 0 0 0 0 0 1 2 3 4 5
```

<details>

<summary>

Click to show/hide benchmark code & results
</summary>

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Assign values into a vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
N = c(1e1, 1e2, 1e3, 1e4, 1e5, 1e6)

res_rel <- bench::press(
  N = N,
  {
    x <- numeric(N)
    x[1] <- x[1]
    idx <- seq(1, N/2)
    ins <- as.numeric(idx)
    
    bench::mark(
      replace(x, idx, ins),
      insitu_replace(x, 1, ins),
      check    = TRUE,
      relative = TRUE
    )
  }
)

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression                |       min |    median |   itr/sec | mem_alloc |
|:--------------------------|----------:|----------:|----------:|----------:|
| replace(x, idx, ins)      |  1.428535 |  1.333307 |  1.000000 |       NaN |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 |  1.616663 |       NaN |
| replace(x, idx, ins)      |  2.833363 |  2.111089 |  1.000000 |  2.446429 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 |  2.395028 |  1.000000 |
| replace(x, idx, ins)      |  9.571646 |  7.800312 |  1.000000 |  2.494071 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 |  7.892244 |  1.000000 |
| replace(x, idx, ins)      | 33.353258 | 35.999626 |  1.000000 |  2.499401 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 | 29.547247 |  1.000000 |
| replace(x, idx, ins)      | 36.281070 | 43.272415 |  1.000000 |  2.499940 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 | 42.301594 |  1.000000 |
| replace(x, idx, ins)      | 40.923029 | 43.196644 |  1.000000 |  2.499994 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 | 42.521166 |  1.000000 |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- numeric(N)
    x[1] <- x[1]
    idx <- seq(1, N/2)
    ins <- as.numeric(idx)
    
    bench::mark(
      replace(x, idx, ins),
      insitu_replace(x, 1, ins),
      check    = TRUE,
      relative = FALSE
    )
  }
)

res_abs %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression                |      min |   median |      itr/sec | mem_alloc |
|:--------------------------|---------:|---------:|-------------:|----------:|
| replace(x, idx, ins)      |    410ns |    492ns | 1871770.0175 |        0B |
| insitu_replace(x, 1, ins) | 287.01ns | 369.01ns | 2538065.4354 |        0B |
| replace(x, idx, ins)      | 697.01ns | 779.01ns | 1096037.7841 |    1.07KB |
| insitu_replace(x, 1, ins) | 287.01ns | 369.01ns | 2594188.4337 |      448B |
| replace(x, idx, ins)      |   2.75µs |   3.16µs |  291340.7332 |    9.86KB |
| insitu_replace(x, 1, ins) |    328ns |    410ns | 2345469.1478 |    3.95KB |
| replace(x, idx, ins)      |  23.37µs |  27.27µs |   35925.5482 |   97.75KB |
| insitu_replace(x, 1, ins) | 656.01ns | 779.01ns | 1204892.1191 |   39.11KB |
| replace(x, idx, ins)      | 227.92µs | 269.12µs |    3721.2297 |  976.66KB |
| insitu_replace(x, 1, ins) |   6.27µs |    6.4µs |  151909.0733 |  390.67KB |
| replace(x, idx, ins)      |   2.47ms |   2.72ms |     367.5307 |    9.54MB |
| insitu_replace(x, 1, ins) |  61.54µs |   62.2µs |   15640.6309 |    3.81MB |

</details>

    #> Warning: The `trans` argument of `continuous_scale()` is deprecated as of ggplot2 3.5.0.
    #> ℹ Please use the `transform` argument instead.
    #> This warning is displayed once every 8 hours.
    #> Call `lifecycle::last_lifecycle_warnings()` to see where this warning was
    #> generated.

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" />

## In-situ fill

`insitu_fill()` is analogous to `replace()` but assigns the value into
the current vector rather than creating a new one.

``` r
x <- numeric(10)
insitu_fill(x, 3)
x
#>  [1] 3 3 3 3 3 3 3 3 3 3
```

<details>

<summary>

Click to show/hide benchmark code & results
</summary>

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Assign values into a vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# N = c(1e1, 1e2, 1e3, 1e4, 1e5, 1e6)

res_rel <- bench::press(
  N = N,
  {
    x <- numeric(N)
    idx <- 1:N
    ins <- 99
    
    bench::mark(
      replace(x, idx, ins),
      insitu_fill(x, ins),
      check    = TRUE,
      relative = TRUE
    )
  }
)

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression           |      min |   median |  itr/sec | mem_alloc |
|:---------------------|---------:|---------:|---------:|----------:|
| replace(x, idx, ins) | 2.250044 | 1.571414 | 1.000000 |       NaN |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 1.584508 |       NaN |
| replace(x, idx, ins) | 2.666667 | 2.250044 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 2.608900 |       NaN |
| replace(x, idx, ins) | 4.533280 | 4.277703 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 4.137790 |       NaN |
| replace(x, idx, ins) | 5.185182 | 4.735279 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 5.189450 |       NaN |
| replace(x, idx, ins) | 5.299417 | 4.812930 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 5.149312 |       NaN |
| replace(x, idx, ins) | 5.365785 | 4.946204 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 5.083808 |       NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- numeric(N)
    idx <- 1:N
    ins <- 99
    
    bench::mark(
      replace(x, idx, ins),
      insitu_fill(x, ins),
      check    = TRUE,
      relative = FALSE
    )
  }
)

res_abs %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression           |      min |   median |      itr/sec | mem_alloc |
|:---------------------|---------:|---------:|-------------:|----------:|
| replace(x, idx, ins) |    410ns | 451.01ns | 1883783.6481 |        0B |
| insitu_fill(x, ins)  | 164.01ns | 287.01ns | 3127725.3387 |        0B |
| replace(x, idx, ins) |    656ns | 738.01ns | 1095550.4906 |    1.27KB |
| insitu_fill(x, ins)  |    246ns |    328ns | 2413351.9452 |        0B |
| replace(x, idx, ins) |   2.75µs |   3.16µs |  287233.7418 |   11.81KB |
| insitu_fill(x, ins)  | 615.01ns |    738ns | 1307389.9271 |        0B |
| replace(x, idx, ins) |  22.92µs |  26.28µs |   37105.8687 |  117.28KB |
| insitu_fill(x, ins)  |   4.39µs |   5.62µs |  188353.7580 |        0B |
| replace(x, idx, ins) | 224.43µs | 258.05µs |    3840.6118 |    1.15MB |
| insitu_fill(x, ins)  |  42.31µs |  55.55µs |   19923.9802 |        0B |
| replace(x, idx, ins) |   2.32ms |   2.56ms |     387.2738 |   11.44MB |
| insitu_fill(x, ins)  | 421.56µs |  506.8µs |    1997.2658 |        0B |

</details>

<img src="man/figures/README-unnamed-chunk-7-1.png" width="100%" />

## In-situ sort

`insitu_sort()` is analogous to `sort()` but sorts values in the current
vector rather than creating a new one.

``` r
x <- as.numeric(sample(10))
x
#>  [1]  9  3  8  1  4  7 10  6  5  2
insitu_sort(x)
x
#>  [1]  1  2  3  4  5  6  7  8  9 10
```

<details>

<summary>

Click to show/hide benchmark code & results
</summary>

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Assign values into a vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# N = c(1e1, 1e2, 1e3, 1e4, 1e5, 1e6)

res_rel <- bench::press(
  N = N,
  {
    x <- runif(N)

    bench::mark(
      sort(x),
      insitu_sort(x),
      check    = TRUE,
      relative = TRUE
    )
  }
)

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression     |       min |    median |   itr/sec | mem_alloc |
|:---------------|----------:|----------:|----------:|----------:|
| sort(x)        | 46.666667 | 42.998885 |  1.000000 |       NaN |
| insitu_sort(x) |  1.000000 |  1.000000 | 39.471476 |       NaN |
| sort(x)        | 22.230479 | 20.533090 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 | 20.151969 |       NaN |
| sort(x)        |  4.569624 |  4.865826 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  4.925618 |       NaN |
| sort(x)        |  1.365123 |  1.570667 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  1.571351 |       NaN |
| sort(x)        |  1.004250 |  1.221638 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  1.195088 |       NaN |
| sort(x)        |  1.067237 |  1.179757 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  1.178598 |       NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- runif(N)
    
    bench::mark(
      sort(x),
      insitu_sort(x),
      check    = TRUE,
      relative = FALSE
    )
  }
)

res_abs %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression     |      min |   median |      itr/sec | mem_alloc |
|:---------------|---------:|---------:|-------------:|----------:|
| sort(x)        |  11.48µs |  12.38µs |   75486.4190 |        0B |
| insitu_sort(x) | 205.01ns | 287.01ns | 3027031.9863 |        0B |
| sort(x)        |  11.77µs |  12.75µs |   74546.7917 |    1.27KB |
| insitu_sort(x) |    492ns | 615.01ns | 1516043.7737 |        0B |
| sort(x)        |   14.8µs |  15.99µs |   57867.1290 |   11.81KB |
| insitu_sort(x) |   3.24µs |   3.36µs |  292041.4553 |        0B |
| sort(x)        |  41.08µs |  50.06µs |   19986.8857 |  117.28KB |
| insitu_sort(x) |  30.09µs |  30.79µs |   31680.5508 |        0B |
| sort(x)        | 300.61µs | 370.78µs |    2713.6385 |    1.15MB |
| insitu_sort(x) | 299.05µs | 303.93µs |    3254.1475 |        0B |
| sort(x)        |   3.07ms |   3.67ms |     275.5080 |   11.44MB |
| insitu_sort(x) |   3.02ms |   3.09ms |     322.1431 |        0B |

</details>

<img src="man/figures/README-unnamed-chunk-10-1.png" width="100%" />

## In-situ Shuffle

`insitu_shuffle()` is analogous to `sample()` but shuffles values in the
current vector rather than creating a new one.

``` r
set.seed(1)
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
insitu_shuffle_fast(x)
x
#>  [1] 7 3 1 2 8 5 4 6 9 0
```

<details>

<summary>

Click to show/hide benchmark code & results
</summary>

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Assign values into a vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# N = c(1e1, 1e2, 1e3, 1e4, 1e5, 1e6)

res_rel <- bench::press(
  N = N,
  {
    x <- runif(N)

    bench::mark(
      sample(x),
      insitu_shuffle_fast(x),
      check    = FALSE,
      relative = TRUE
    )
  }
)

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression             |       min |   median |  itr/sec | mem_alloc |
|:-----------------------|----------:|---------:|---------:|----------:|
| sample(x)              | 16.667653 | 9.500592 | 1.000000 |       NaN |
| insitu_shuffle_fast(x) |  1.000000 | 1.000000 | 9.694632 |       NaN |
| sample(x)              |  7.500000 | 8.357130 | 1.000000 |       Inf |
| insitu_shuffle_fast(x) |  1.000000 | 1.000000 | 8.704380 |       NaN |
| sample(x)              |  6.101134 | 6.836955 | 1.000000 |       Inf |
| insitu_shuffle_fast(x) |  1.000000 | 1.000000 | 6.884471 |       NaN |
| sample(x)              |  6.797911 | 7.330633 | 1.000000 |       Inf |
| insitu_shuffle_fast(x) |  1.000000 | 1.000000 | 7.195001 |       NaN |
| sample(x)              |  7.616043 | 7.807329 | 1.000000 |       Inf |
| insitu_shuffle_fast(x) |  1.000000 | 1.000000 | 7.753422 |       NaN |
| sample(x)              |  7.853553 | 7.846756 | 1.000000 |       Inf |
| insitu_shuffle_fast(x) |  1.000000 | 1.000000 | 7.836728 |       NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- runif(N)
    
    bench::mark(
      sample(x),
      insitu_shuffle_fast(x),
      check    = FALSE,
      relative = FALSE
    )
  }
)

res_abs %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression             |      min |   median |      itr/sec | mem_alloc |
|:-----------------------|---------:|---------:|-------------:|----------:|
| sample(x)              |   2.09µs |   2.38µs | 3.896126e+05 |        0B |
| insitu_shuffle_fast(x) |    164ns |    246ns | 3.732492e+06 |        0B |
| sample(x)              |   3.69µs |   4.76µs | 1.964800e+05 |    1.71KB |
| insitu_shuffle_fast(x) | 451.01ns |    574ns | 1.669584e+06 |        0B |
| sample(x)              |  22.06µs |  25.71µs | 3.760291e+04 |   15.77KB |
| insitu_shuffle_fast(x) |   3.61µs |   3.77µs | 2.588602e+05 |        0B |
| sample(x)              | 239.65µs | 258.05µs | 3.846824e+03 |   156.4KB |
| insitu_shuffle_fast(x) |  35.26µs |  35.47µs | 2.745652e+04 |        0B |
| sample(x)              |   2.71ms |   2.88ms | 3.458594e+02 |    1.53MB |
| insitu_shuffle_fast(x) | 358.87µs | 364.41µs | 2.711422e+03 |        0B |
| sample(x)              |  28.54ms |  30.12ms | 3.314929e+01 |   15.26MB |
| insitu_shuffle_fast(x) |   3.64ms |    3.8ms | 2.630279e+02 |        0B |

</details>

<img src="man/figures/README-unnamed-chunk-13-1.png" width="100%" />

## In-situ Reverse

`insitu_reverse()` is analogous to `rev()` but reverses values in the
current vector rather than creating a new one.

``` r
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
insitu_reverse(x)
x
#>  [1] 9 8 7 6 5 4 3 2 1 0
```

<details>

<summary>

Click to show/hide benchmark code & results
</summary>

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Assign values into a vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# N = c(1e1, 1e2, 1e3, 1e4, 1e5, 1e6)

res_rel <- bench::press(
  N = N,
  {
    x <- runif(N)

    bench::mark(
      rev(x),
      insitu_reverse(x),
      check    = TRUE,
      relative = TRUE
    )
  }
)

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression        |       min |    median |   itr/sec | mem_alloc |
|:------------------|----------:|----------:|----------:|----------:|
| rev(x)            |  4.500089 |  4.199886 |  1.000000 |       NaN |
| insitu_reverse(x) |  1.000000 |  1.000000 |  4.198024 |       NaN |
| rev(x)            |  6.000089 |  5.599801 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 |  5.409955 |       NaN |
| rev(x)            |  9.428383 |  8.500018 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 |  9.225505 |       NaN |
| rev(x)            | 10.021235 | 13.319905 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 | 12.862238 |       NaN |
| rev(x)            |  8.985833 | 11.780882 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 | 11.373771 |       NaN |
| rev(x)            |  9.844783 | 10.911528 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 | 10.849040 |       NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- runif(N)
    
    bench::mark(
      rev(x),
      insitu_reverse(x),
      check    = TRUE,
      relative = FALSE
    )
  }
)

res_abs %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression        |      min |   median |      itr/sec | mem_alloc |
|:------------------|---------:|---------:|-------------:|----------:|
| rev(x)            | 778.98ns | 860.99ns | 1095662.7661 |        0B |
| insitu_reverse(x) |    164ns | 205.01ns | 4216426.9105 |        0B |
| rev(x)            |    984ns |   1.11µs |  731783.2221 |    1.27KB |
| insitu_reverse(x) |    164ns |    246ns | 3692762.8211 |        0B |
| rev(x)            |   2.75µs |   3.57µs |  269879.9669 |   11.81KB |
| insitu_reverse(x) | 287.01ns |    410ns | 2394680.4242 |        0B |
| rev(x)            |  19.31µs |  24.97µs |   39929.1794 |  117.28KB |
| insitu_reverse(x) |   1.93µs |   2.09µs |  461192.4385 |        0B |
| rev(x)            | 182.41µs | 239.56µs |    4242.6981 |    1.15MB |
| insitu_reverse(x) |  19.19µs |  20.46µs |   48229.7067 |        0B |
| rev(x)            |   1.84ms |   2.38ms |     428.1889 |   11.44MB |
| insitu_reverse(x) |  221.6µs | 225.17µs |    4126.2496 |        0B |

</details>

<img src="man/figures/README-unnamed-chunk-16-1.png" width="100%" />

## In-situ fill with random

`insitu_fill_runif()` is analogous to `runif()` but generates values in
the current vector rather than creating a new one.

``` r
set.seed(1)
x <- numeric(10)
insitu_fill_runif_fast(x, 10, 15)
x
#>  [1] 14.45509 12.79015 10.98593 13.68036 10.52347 11.07634 12.15119 12.89595
#>  [9] 13.94301 10.44809
```

<details>

<summary>

Click to show/hide benchmark code & results
</summary>

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Assign values into a vector
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# N = c(1e1, 1e2, 1e3, 1e4, 1e5, 1e6)

res_rel <- bench::press(
  N = N,
  {
    x <- numeric(N)

    bench::mark(
      runif(x),
      insitu_fill_runif_fast(x, 0, 1),
      check    = FALSE,
      relative = TRUE
    )
  }
)

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression                      |      min |   median |  itr/sec | mem_alloc |
|:--------------------------------|---------:|---------:|---------:|----------:|
| runif(x)                        | 1.500030 | 1.249989 | 1.000000 |       NaN |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 1.327602 |       NaN |
| runif(x)                        | 2.124928 | 1.999964 | 1.000000 |       Inf |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 2.123765 |       NaN |
| runif(x)                        | 3.500000 | 3.599982 | 1.000000 |       Inf |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 3.671257 |       NaN |
| runif(x)                        | 3.985454 | 4.243722 | 1.000000 |       Inf |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 4.223335 |       NaN |
| runif(x)                        | 4.024057 | 4.425373 | 1.000000 |       Inf |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 4.395818 |       NaN |
| runif(x)                        | 4.089551 | 4.542190 | 1.000000 |       Inf |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 4.535665 |       NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- numeric(N)
    
    bench::mark(
      runif(x),
      insitu_fill_runif_fast(x, 0, 1),
      check    = FALSE,
      relative = FALSE
    )
  }
)

res_abs %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression                      |      min |   median |      itr/sec | mem_alloc |
|:--------------------------------|---------:|---------:|-------------:|----------:|
| runif(x)                        | 368.99ns | 410.01ns | 2132783.1072 |        0B |
| insitu_fill_runif_fast(x, 0, 1) | 286.99ns | 328.01ns | 2692176.0149 |        0B |
| runif(x)                        |    738ns | 820.01ns |  964804.8275 |      848B |
| insitu_fill_runif_fast(x, 0, 1) |    328ns | 410.01ns | 2080727.6057 |        0B |
| runif(x)                        |   4.59µs |   5.12µs |  184441.4610 |    7.86KB |
| insitu_fill_runif_fast(x, 0, 1) |   1.31µs |   1.44µs |  675928.1429 |        0B |
| runif(x)                        |  44.61µs |  49.77µs |   19832.8049 |   78.17KB |
| insitu_fill_runif_fast(x, 0, 1) |  11.28µs |  11.44µs |   85324.9133 |        0B |
| runif(x)                        | 445.59µs |  497.7µs |    2004.2724 |   781.3KB |
| insitu_fill_runif_fast(x, 0, 1) | 105.98µs | 112.63µs |    8773.8117 |        0B |
| runif(x)                        |   4.75ms |   5.05ms |     197.1284 |    7.63MB |
| insitu_fill_runif_fast(x, 0, 1) |   1.11ms |   1.13ms |     882.9950 |        0B |

</details>

<img src="man/figures/README-unnamed-chunk-19-1.png" width="100%" />

## Related Software

- [data.table](https://cran.r-project.org/package=data.table) performs a
  lot of operations in-situ (i.e. “by reference”)
