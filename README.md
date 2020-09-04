
<!-- README.md is generated from README.Rmd. Please edit that file -->

# insitu

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg) [![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![R build
status](https://github.com/coolbutuseless/insitu/workflows/R-CMD-check/badge.svg)](https://github.com/coolbutuseless/insitu/actions)
<!-- badges: end -->

`insitu` provides some functions for modifying vectors *in-situ* (in
place) without allocating a new vector.

This is an experimental package I wrote to try and figure out just how
fast things could be in R.

**Warning**: Modifying vectors in-situ can be fast, but doing so
violates some very strong norms within R internals.

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
    and assign new values into it. The speed saved by switching to
    in-situ modification will only possibly be useful if this operations
    is performed many, many times.

In the words of Luke Tierney in his User2020 keynote:

    You should never modify something without duplicating it.

This package ignores this advice. Beware.

## What’s in the box

| insitu                                     | description                                                            | integer | real | character |
| ------------------------------------------ | ---------------------------------------------------------------------- | ------- | ---- | --------- |
| insitu\_fill(x, value)                     | Fill vector with the given value                                       | Yes     | Yes  | Yes       |
| insitu\_fill\_runif(x, lower, upper)       | Fill vector with uniform random numbers                                | Yes     | Yes  |           |
| insitu\_fill\_runif\_fast(x, lower, upper) | Fill vector with uniform random numbers                                | Yes     | Yes  |           |
| insitu\_replace(x, pos, values)            | Replace values in x with given values starting from the given position | Yes     | Yes  | Yes       |
| insitu\_reverse(x)                         | Reverse vector                                                         | Yes     | Yes  | Yes       |
| insitu\_shuffle(x)                         | Shuffle the elements of a vector                                       | Yes     | Yes  | Yes       |
| insitu\_shuffle\_fast(x)                   | Shuffle the elements of a vector                                       | Yes     | Yes  | Yes       |
| insitu\_sort(x)                            | Sort the elements of a vector                                          | Yes     | Yes  |           |
|                                            |                                                                        |         |      |           |

#### Fast Variants

The `_fast` versions of some functions use their own random-number
generator rather than the one supplied in R.

  - On **windows** this RNG is [xoshiro256++](http://prng.di.unimi.it/).
    This does not require a `uint128_t` and compiles cleanly on the
    GitHub CI test server.
  - On **other platforms** this RNG is
    [lehmer](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/).
    Use of `uint128_t` on these platforms allows for faster generation
    of random integers on an interval.

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
x <- integer(10)
insitu_replace(x, 6, 1:5)
x
#>  [1] 0 0 0 0 0 1 2 3 4 5
```

<details>

<summary> Click to show/hide benchmark code & results </summary>

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

| expression                 |       min |    median |   itr/sec | mem\_alloc |
| :------------------------- | --------: | --------: | --------: | ---------: |
| replace(x, idx, ins)       |  1.217532 |  1.283092 |  1.000000 |        NaN |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  1.359811 |        NaN |
| replace(x, idx, ins)       |  2.083425 |  2.253825 |  1.000000 |   2.446429 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  2.370239 |   1.000000 |
| replace(x, idx, ins)       |  5.787535 |  7.500000 |  1.000000 |   2.494071 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  6.743343 |   1.000000 |
| replace(x, idx, ins)       | 16.649657 | 27.820027 |  1.000000 |   2.499401 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 27.274348 |   1.000000 |
| replace(x, idx, ins)       | 19.727567 | 33.679490 |  1.000000 |   2.499940 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 30.717399 |   1.000000 |
| replace(x, idx, ins)       | 15.334376 | 15.639572 |  1.000000 |   2.499994 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 15.656790 |   1.000000 |

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

| expression                 |      min |   median |    itr/sec | mem\_alloc |
| :------------------------- | -------: | -------: | ---------: | ---------: |
| replace(x, idx, ins)       |   1.12µs |   1.33µs | 611727.951 |         0B |
| insitu\_replace(x, 1, ins) |    937ns |    1.1µs | 477641.124 |         0B |
| replace(x, idx, ins)       |    1.9µs |   2.69µs | 307445.661 |     1.07KB |
| insitu\_replace(x, 1, ins) |    941ns |   1.13µs | 753573.249 |       448B |
| replace(x, idx, ins)       |   6.01µs |   7.53µs | 112163.194 |     9.86KB |
| insitu\_replace(x, 1, ins) |   1.04µs |   1.17µs | 800177.319 |     3.95KB |
| replace(x, idx, ins)       |  43.59µs |  82.21µs |  11660.335 |    97.75KB |
| insitu\_replace(x, 1, ins) |   2.61µs |   2.86µs | 327490.165 |    39.11KB |
| replace(x, idx, ins)       |  426.3µs | 742.61µs |   1398.942 |   976.66KB |
| insitu\_replace(x, 1, ins) |  21.38µs |  24.61µs |  38271.914 |   390.67KB |
| replace(x, idx, ins)       |   4.81ms |   5.19ms |    171.654 |     9.54MB |
| insitu\_replace(x, 1, ins) | 245.99µs | 302.02µs |   3091.613 |     3.81MB |

</details>

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" />

## In-situ fill

`insitu_fill()` is analogous to `replace()` but assigns the value into
the current vector rather than creating a new one.

``` r
x <- integer(10)
insitu_fill(x, 3L)
x
#>  [1] 3 3 3 3 3 3 3 3 3 3
```

<details>

<summary> Click to show/hide benchmark code & results </summary>

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

| expression           |      min |   median |  itr/sec | mem\_alloc |
| :------------------- | -------: | -------: | -------: | ---------: |
| replace(x, idx, ins) | 1.415816 | 1.481982 | 1.000000 |        NaN |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.531529 |        NaN |
| replace(x, idx, ins) | 1.448276 | 1.904298 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 2.028849 |        NaN |
| replace(x, idx, ins) | 1.036633 | 1.233400 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.282310 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.720537 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.239861 | 1.000000 | 1.713877 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.621770 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.219529 | 1.000000 | 1.544982 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.000000 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.107120 | 1.073682 | 1.036929 |        NaN |

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

| expression           |      min |   median |     itr/sec | mem\_alloc |
| :------------------- | -------: | -------: | ----------: | ---------: |
| replace(x, idx, ins) |    1.1µs |   1.28µs | 693348.0378 |         0B |
| insitu\_fill(x, ins) |    786ns |    890ns | 952000.7855 |         0B |
| replace(x, idx, ins) |   1.71µs |   2.05µs | 379655.6795 |     1.27KB |
| insitu\_fill(x, ins) |   1.11µs |   1.23µs | 713224.4847 |         0B |
| replace(x, idx, ins) |   4.33µs |   5.57µs | 163766.2173 |    11.81KB |
| insitu\_fill(x, ins) |   4.32µs |   4.52µs | 211244.2392 |         0B |
| replace(x, idx, ins) |  29.95µs |  66.63µs |  14303.7164 |   117.28KB |
| insitu\_fill(x, ins) |   33.9µs |  38.87µs |  24816.6239 |         0B |
| replace(x, idx, ins) | 284.87µs | 611.74µs |   1657.6368 |     1.15MB |
| insitu\_fill(x, ins) | 339.49µs | 378.57µs |   2575.4550 |         0B |
| replace(x, idx, ins) |    3.1ms |   3.73ms |    227.7902 |    11.44MB |
| insitu\_fill(x, ins) |   3.52ms |   3.85ms |    258.0574 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-7-1.png" width="100%" />

## In-situ sort

`insitu_sort()` is analogous to `sort()` but sorts values in the current
vector rather than creating a new one.

``` r
x <- sample(10)
insitu_sort(x)
x
#>  [1]  1  2  3  4  5  6  7  8  9 10
```

<details>

<summary> Click to show/hide benchmark code & results </summary>

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

| expression      |       min |    median |   itr/sec | mem\_alloc |
| :-------------- | --------: | --------: | --------: | ---------: |
| sort(x)         | 50.502681 | 53.010601 |  1.000000 |        NaN |
| insitu\_sort(x) |  1.000000 |  1.000000 | 51.538136 |        NaN |
| sort(x)         | 28.685212 | 29.955708 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 | 29.943166 |        NaN |
| sort(x)         |  6.588520 |  7.442051 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  7.423738 |        NaN |
| sort(x)         |  1.860792 |  2.590592 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  2.574593 |        NaN |
| sort(x)         |  1.050158 |  1.689087 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.683392 |        NaN |
| sort(x)         |  1.064161 |  1.291230 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.290399 |        NaN |

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

| expression      |      min |   median |      itr/sec | mem\_alloc |
| :-------------- | -------: | -------: | -----------: | ---------: |
| sort(x)         |  38.51µs |  45.22µs |   20749.4972 |         0B |
| insitu\_sort(x) |    739ns |    847ns | 1089466.0777 |         0B |
| sort(x)         |  39.44µs |  45.99µs |   20195.0811 |     1.27KB |
| insitu\_sort(x) |   1.37µs |   1.49µs |  613317.4899 |         0B |
| sort(x)         |  45.48µs |  52.46µs |   17910.1957 |    11.81KB |
| insitu\_sort(x) |   6.72µs |   7.22µs |  130958.4490 |         0B |
| sort(x)         | 110.91µs | 162.29µs |    5834.9493 |   117.28KB |
| insitu\_sort(x) |  60.25µs |  62.48µs |   15252.4789 |         0B |
| sort(x)         |  667.8µs |    1.1ms |     904.3444 |     1.15MB |
| insitu\_sort(x) | 591.76µs | 635.42µs |    1533.4030 |         0B |
| sort(x)         |   6.42ms |   8.47ms |     117.3836 |    11.44MB |
| insitu\_sort(x) |   5.94ms |   6.38ms |     155.1841 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-10-1.png" width="100%" />

## In-situ Shuffle

`insitu_shuffle()` is analogous to `sample()` but shuffles values in the
current vector rather than creating a new one.

``` r
set.seed(1)
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
insitu_shuffle(x)
x
#>  [1] 0 9 6 8 7 1 5 4 3 2
```

<details>

<summary> Click to show/hide benchmark code & results </summary>

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
      insitu_shuffle(x),
      insitu_shuffle_fast(x),
      check    = FALSE,
      relative = TRUE
    )
  }
)
#> Seeding lehmer64

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression               |       min |    median |   itr/sec | mem\_alloc |
| :----------------------- | --------: | --------: | --------: | ---------: |
| sample(x)                |  9.193220 | 10.392581 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  1.049153 |  1.132921 |  9.382435 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 10.573142 |        Inf |
| sample(x)                |  9.809001 | 11.123752 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  1.745335 |  1.817365 |  5.775404 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 10.645766 |        NaN |
| sample(x)                | 10.478358 | 10.913153 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  2.829087 |  2.922156 |  3.783572 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 10.820391 |        NaN |
| sample(x)                | 12.184464 | 14.246721 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  3.316114 |  3.333020 |  4.183835 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 13.935488 |        NaN |
| sample(x)                | 14.229428 | 15.783412 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  3.251185 |  3.525782 |  4.477019 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 15.208066 |        NaN |
| sample(x)                | 11.027614 | 10.708094 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  2.890044 |  3.065046 |  3.432175 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 |  9.301588 |        NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- runif(N)
    
    bench::mark(
      sample(x),
      insitu_shuffle(x),
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

| expression               |      min |   median |      itr/sec | mem\_alloc |
| :----------------------- | -------: | -------: | -----------: | ---------: |
| sample(x)                |   5.48µs |   6.88µs | 1.348616e+05 |     2.49KB |
| insitu\_shuffle(x)       |    631ns |    785ns | 1.182062e+06 |         0B |
| insitu\_shuffle\_fast(x) |    559ns |    669ns | 1.408376e+06 |         0B |
| sample(x)                |   8.91µs |  10.89µs | 8.767858e+04 |      4.2KB |
| insitu\_shuffle(x)       |   1.57µs |   1.79µs | 5.032382e+05 |         0B |
| insitu\_shuffle\_fast(x) |    891ns |   1.03µs | 8.843011e+05 |         0B |
| sample(x)                |  42.51µs |  46.45µs | 2.104219e+04 |    18.27KB |
| insitu\_shuffle(x)       |  11.45µs |  12.75µs | 7.509729e+04 |         0B |
| insitu\_shuffle\_fast(x) |   4.06µs |   4.36µs | 2.159665e+05 |         0B |
| sample(x)                | 419.59µs |  500.4µs | 1.960734e+03 |   158.89KB |
| insitu\_shuffle(x)       | 112.13µs | 118.25µs | 8.074340e+03 |         0B |
| insitu\_shuffle\_fast(x) |  33.87µs |   35.5µs | 2.723874e+04 |         0B |
| sample(x)                |   5.32ms |   6.01ms | 1.647716e+02 |     1.53MB |
| insitu\_shuffle(x)       |   1.21ms |   1.35ms | 7.238361e+02 |         0B |
| insitu\_shuffle\_fast(x) | 374.55µs | 391.36µs | 2.394888e+03 |         0B |
| sample(x)                |  68.64ms |  85.39ms | 1.197933e+01 |    15.26MB |
| insitu\_shuffle(x)       |  17.58ms |  21.57ms | 4.546286e+01 |         0B |
| insitu\_shuffle\_fast(x) |   5.97ms |   6.85ms | 1.308094e+02 |         0B |

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

<summary> Click to show/hide benchmark code & results </summary>

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

| expression         |      min |    median |   itr/sec | mem\_alloc |
| :----------------- | -------: | --------: | --------: | ---------: |
| rev(x)             | 4.304813 |  8.217852 |  1.000000 |        NaN |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  6.582061 |        NaN |
| rev(x)             | 5.240864 |  5.361042 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  4.253824 |        NaN |
| rev(x)             | 5.628082 |  7.263003 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  9.126051 |        NaN |
| rev(x)             | 7.009137 | 17.303129 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 17.877336 |        NaN |
| rev(x)             | 6.713473 | 16.408472 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 15.417446 |        NaN |
| rev(x)             | 6.435010 |  6.272768 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  6.267219 |        NaN |

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

| expression         |      min |   median |      itr/sec | mem\_alloc |
| :----------------- | -------: | -------: | -----------: | ---------: |
| rev(x)             |   2.43µs |   3.48µs |  220822.7066 |         0B |
| insitu\_reverse(x) |    545ns |    648ns | 1062980.4162 |         0B |
| rev(x)             |   2.82µs |   3.57µs |  216317.7100 |     1.27KB |
| insitu\_reverse(x) |    582ns |    682ns | 1078189.6708 |         0B |
| rev(x)             |   5.11µs |   7.22µs |  110170.5413 |    11.81KB |
| insitu\_reverse(x) |    922ns |   1.06µs |  849957.6549 |         0B |
| rev(x)             |  27.44µs |  83.95µs |   10952.0487 |   117.28KB |
| insitu\_reverse(x) |   4.31µs |   4.65µs |  200742.3695 |         0B |
| rev(x)             | 254.99µs | 748.59µs |    1318.0543 |     1.15MB |
| insitu\_reverse(x) |  39.25µs |  42.78µs |   22000.0058 |         0B |
| rev(x)             |   2.82ms |   3.67ms |     241.8555 |    11.44MB |
| insitu\_reverse(x) | 440.09µs | 535.94µs |    1793.8181 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-16-1.png" width="100%" />

## In-situ fill with random

`insitu_fill_runif()` is analogous to `runif()` but generates values in
the current vector rather than creating a new one.

``` r
set.seed(1)
x <- integer(10)
insitu_fill_runif(x, 10, 15)
x
#>  [1] 11 12 13 15 11 15 15 13 13 10
```

<details>

<summary> Click to show/hide benchmark code & results </summary>

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
      insitu_fill_runif(x, 0, 1),
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

| expression                         |       min |    median |   itr/sec | mem\_alloc |
| :--------------------------------- | --------: | --------: | --------: | ---------: |
| runif(x)                           |  2.431055 |  2.810204 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  1.130939 |  1.187755 |  2.414153 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 |  2.797715 |        Inf |
| runif(x)                           |  4.522255 |  4.772608 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  1.794263 |  1.802458 |  2.557143 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 |  4.702723 |        NaN |
| runif(x)                           | 12.631287 | 12.387146 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  4.366155 |  4.318669 |  2.889374 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 12.153330 |        NaN |
| runif(x)                           | 18.564671 | 21.181191 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  6.265620 |  6.335787 |  3.293511 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 20.873973 |        NaN |
| runif(x)                           | 20.715696 | 22.392503 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  6.681642 |  7.021151 |  3.168436 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 21.634243 |        NaN |
| runif(x)                           | 20.804400 | 21.284098 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  6.815076 |  6.950413 |  3.055635 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 20.934121 |        NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- numeric(N)
    
    bench::mark(
      runif(x),
      insitu_fill_runif(x, 0, 1),
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

| expression                         |      min |   median |      itr/sec | mem\_alloc |
| :--------------------------------- | -------: | -------: | -----------: | ---------: |
| runif(x)                           |   2.07µs |   2.65µs | 348849.69112 |     2.49KB |
| insitu\_fill\_runif(x, 0, 1)       |    973ns |   1.15µs | 759041.16665 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |    869ns |   1.04µs | 858964.25090 |         0B |
| runif(x)                           |   4.56µs |   5.37µs | 171428.26291 |     3.32KB |
| insitu\_fill\_runif(x, 0, 1)       |   1.67µs |   1.89µs | 474304.39333 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   1.04µs |   1.15µs | 787779.71546 |         0B |
| runif(x)                           |   28.8µs |  31.39µs |  30222.99118 |    10.35KB |
| insitu\_fill\_runif(x, 0, 1)       |   9.95µs |  11.13µs |  87147.73303 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   2.38µs |   2.66µs | 349568.26161 |         0B |
| runif(x)                           | 283.55µs | 333.75µs |   2912.99011 |    80.66KB |
| insitu\_fill\_runif(x, 0, 1)       |  95.73µs | 102.36µs |   9416.19991 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |  15.23µs |  16.34µs |  58074.35586 |         0B |
| runif(x)                           |   2.79ms |   3.24ms |    306.02533 |   783.79KB |
| insitu\_fill\_runif(x, 0, 1)       |  947.1µs |   1.06ms |    934.38810 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) | 141.72µs |  147.4µs |   6464.12331 |         0B |
| runif(x)                           |  28.33ms |  32.82ms |     31.65978 |     7.63MB |
| insitu\_fill\_runif(x, 0, 1)       |   9.56ms |  10.61ms |     95.09627 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   1.42ms |   1.53ms |    635.31162 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-19-1.png" width="100%" />

## Related Software

  - [data.table](https://cran.r-project.org/package=data.table) performs
    a lot of operations in-situ (which data.table calls “by reference”)

## Acknowledgements

  - R Core for developing and maintaining the language.
  - CRAN maintainers, for patiently shepherding packages onto CRAN and
    maintaining the repository
