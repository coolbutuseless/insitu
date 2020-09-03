
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
generator rather than the one supplied in R. This generator is
[lehmer64](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/).
It is very fast, but has different properties from R’s built in random
number generator. Use with caution.

#### ALTREP utils

  - `is_altrep(x)` tests whether an object is an ALTREP
  - `is_mutable(x)` tests whether an object is mutable in-place by
    checking its reference count
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
| replace(x, idx, ins)       |  1.196573 |  1.172176 |  1.000000 |        NaN |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  1.269699 |        NaN |
| replace(x, idx, ins)       |  2.067353 |  2.124646 |  1.000000 |   2.446429 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  2.414546 |   1.000000 |
| replace(x, idx, ins)       |  4.812500 |  6.597468 |  1.000000 |   2.494071 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  6.335685 |   1.000000 |
| replace(x, idx, ins)       | 14.899316 | 25.762939 |  1.000000 |   2.499401 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 26.161848 |   1.000000 |
| replace(x, idx, ins)       | 19.484796 | 32.479221 |  1.000000 |   2.499940 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 30.132984 |   1.000000 |
| replace(x, idx, ins)       | 19.922236 | 18.236982 |  1.000000 |   2.499994 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 17.722262 |   1.000000 |

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

| expression                 |      min |   median |     itr/sec | mem\_alloc |
| :------------------------- | -------: | -------: | ----------: | ---------: |
| replace(x, idx, ins)       |    1.4µs |   1.66µs | 499763.6125 |         0B |
| insitu\_replace(x, 1, ins) |   1.11µs |   1.41µs | 513883.7531 |         0B |
| replace(x, idx, ins)       |   2.21µs |   2.91µs | 278613.6649 |     1.07KB |
| insitu\_replace(x, 1, ins) |   1.06µs |   1.45µs | 606769.3872 |       448B |
| replace(x, idx, ins)       |   6.25µs |    7.9µs | 108973.9122 |     9.86KB |
| insitu\_replace(x, 1, ins) |   1.38µs |    1.6µs | 549490.7656 |     3.95KB |
| replace(x, idx, ins)       |   44.8µs |  87.84µs |  10798.7962 |    97.75KB |
| insitu\_replace(x, 1, ins) |   2.98µs |   3.47µs | 264614.5698 |    39.11KB |
| replace(x, idx, ins)       | 429.45µs | 810.51µs |   1236.4251 |   976.66KB |
| insitu\_replace(x, 1, ins) |  21.99µs |  25.37µs |  33703.2323 |   390.67KB |
| replace(x, idx, ins)       |   5.03ms |   5.57ms |    153.1147 |     9.54MB |
| insitu\_replace(x, 1, ins) | 247.41µs | 322.88µs |   2448.9522 |     3.81MB |

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
| replace(x, idx, ins) | 1.294597 | 1.283034 | 1.000000 |        NaN |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.184036 |        NaN |
| replace(x, idx, ins) | 1.453295 | 1.638786 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.727016 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.086737 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.039746 | 1.000000 | 1.217489 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.582475 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.322781 | 1.000000 | 1.637680 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.492545 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.350085 | 1.000000 | 1.445815 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.000000 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.166219 | 1.032048 | 1.097336 |        NaN |

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
| replace(x, idx, ins) |   1.21µs |   1.69µs | 492051.7639 |         0B |
| insitu\_fill(x, ins) |   1.01µs |   1.22µs | 704502.1931 |         0B |
| replace(x, idx, ins) |   1.96µs |   2.37µs | 315831.5886 |     1.27KB |
| insitu\_fill(x, ins) |   1.28µs |   1.59µs | 511827.6193 |         0B |
| replace(x, idx, ins) |   4.73µs |   7.51µs | 118794.0405 |    11.81KB |
| insitu\_fill(x, ins) |   4.91µs |   5.33µs | 173484.4944 |         0B |
| replace(x, idx, ins) |   29.9µs |  71.49µs |  12992.4226 |   117.28KB |
| insitu\_fill(x, ins) |  40.83µs |  44.12µs |  21557.2898 |         0B |
| replace(x, idx, ins) | 275.54µs | 653.23µs |   1536.4061 |     1.15MB |
| insitu\_fill(x, ins) | 370.32µs | 424.86µs |   2326.9036 |         0B |
| replace(x, idx, ins) |   3.32ms |   4.06ms |    201.3681 |    11.44MB |
| insitu\_fill(x, ins) |   3.82ms |   4.36ms |    225.7616 |         0B |

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
| sort(x)         | 36.688074 | 37.221236 |  1.000000 |        NaN |
| insitu\_sort(x) |  1.000000 |  1.000000 | 38.695174 |        NaN |
| sort(x)         | 23.880363 | 24.584972 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 | 23.866136 |        NaN |
| sort(x)         |  6.409326 |  7.047000 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  7.917572 |        NaN |
| sort(x)         |  2.016700 |  2.526580 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  2.653967 |        NaN |
| sort(x)         |  1.100797 |  1.805110 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.817177 |        NaN |
| sort(x)         |  1.014717 |  1.492425 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.415460 |        NaN |

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

| expression      |      min |   median |     itr/sec | mem\_alloc |
| :-------------- | -------: | -------: | ----------: | ---------: |
| sort(x)         |  39.75µs |  47.38µs |  18680.1080 |         0B |
| insitu\_sort(x) |    913ns |   1.32µs | 609800.6083 |         0B |
| sort(x)         |  41.57µs |  48.59µs |  17957.1350 |     1.27KB |
| insitu\_sort(x) |   1.68µs |   2.03µs | 404762.2060 |         0B |
| sort(x)         |  47.59µs |  56.24µs |  15206.6809 |    11.81KB |
| insitu\_sort(x) |   7.17µs |   8.04µs | 119283.6715 |         0B |
| sort(x)         | 111.09µs |  174.1µs |   5179.8989 |   117.28KB |
| insitu\_sort(x) |  60.58µs |  68.73µs |  14102.0267 |         0B |
| sort(x)         | 653.51µs |   1.21ms |    795.1924 |     1.15MB |
| insitu\_sort(x) | 592.32µs | 677.57µs |   1442.6479 |         0B |
| sort(x)         |   6.91ms |   9.83ms |    100.1024 |    11.44MB |
| insitu\_sort(x) |   6.31ms |   6.94ms |    140.1463 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-10-1.png" width="100%" />

## In-situ Shuffle

`insitu_shuffle()` is analogous to `sample()` but shuffles values in the
current vector rather than creating a new one.

``` r
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
insitu_shuffle(x)
x
#>  [1] 7 0 3 5 4 1 8 6 2 9
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

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression               |       min |    median |   itr/sec | mem\_alloc |
| :----------------------- | --------: | --------: | --------: | ---------: |
| sample(x)                |  6.259382 |  6.661726 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  1.000000 |  1.000000 |  8.848097 |        NaN |
| insitu\_shuffle\_fast(x) |  2.137969 |  2.118134 |  4.050106 |        Inf |
| sample(x)                |  5.027027 |  5.681964 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  1.000000 |  1.000000 |  5.661318 |        NaN |
| insitu\_shuffle\_fast(x) |  1.194054 |  1.201010 |  4.731081 |        Inf |
| sample(x)                |  7.989859 |  7.604354 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  2.262911 |  2.168541 |  3.517602 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 |  7.369995 |        Inf |
| sample(x)                | 11.629346 | 13.003945 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  3.165762 |  3.235819 |  4.139560 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 12.961142 |        Inf |
| sample(x)                | 14.737991 | 15.555305 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  3.289309 |  3.539353 |  3.932282 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 14.582776 |        Inf |
| sample(x)                | 12.965562 | 10.378325 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  2.893763 |  2.520475 |  3.880060 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 |  9.736874 |        Inf |

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
| sample(x)                |   5.85µs |   7.32µs | 112421.62112 |     2.49KB |
| insitu\_shuffle(x)       |    907ns |   1.15µs | 765712.37753 |         0B |
| insitu\_shuffle\_fast(x) |   1.95µs |   2.49µs | 298574.52156 |     2.49KB |
| sample(x)                |   9.28µs |  11.39µs |  77254.12133 |      4.2KB |
| insitu\_shuffle(x)       |   1.87µs |   2.29µs | 373351.40143 |         0B |
| insitu\_shuffle\_fast(x) |   2.26µs |   2.83µs | 315730.52471 |     2.49KB |
| sample(x)                |  42.69µs |  47.48µs |  19213.32502 |    18.27KB |
| insitu\_shuffle(x)       |  11.83µs |  13.77µs |  66976.90278 |         0B |
| insitu\_shuffle\_fast(x) |   5.43µs |    6.3µs | 145422.79031 |     2.49KB |
| sample(x)                | 415.44µs | 507.87µs |   1841.52711 |   158.89KB |
| insitu\_shuffle(x)       | 112.62µs | 128.21µs |   7629.90942 |         0B |
| insitu\_shuffle\_fast(x) |   35.4µs |  40.94µs |  22687.22319 |     2.49KB |
| sample(x)                |    5.5ms |    7.6ms |    132.22042 |     1.53MB |
| insitu\_shuffle(x)       |   1.26ms |   1.59ms |    595.08847 |         0B |
| insitu\_shuffle\_fast(x) | 382.71µs | 435.46µs |   2125.17540 |     2.49KB |
| sample(x)                |  82.24ms |     87ms |     11.46565 |    15.26MB |
| insitu\_shuffle(x)       |  18.98ms |  23.38ms |     41.66396 |         0B |
| insitu\_shuffle\_fast(x) |   6.29ms |   7.91ms |    117.64934 |     2.49KB |

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
| rev(x)             | 3.576020 |  4.069719 |  1.000000 |        NaN |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  4.449041 |        NaN |
| rev(x)             | 3.843678 |  4.472789 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  4.742882 |        NaN |
| rev(x)             | 4.912664 |  5.399563 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  5.621031 |        NaN |
| rev(x)             | 5.742399 | 15.978815 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 15.474308 |        NaN |
| rev(x)             | 5.937002 | 19.903847 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 18.451631 |        NaN |
| rev(x)             | 6.414645 |  6.462813 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  6.767398 |        NaN |

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

| expression         |      min |   median |     itr/sec | mem\_alloc |
| :----------------- | -------: | -------: | ----------: | ---------: |
| rev(x)             |   2.89µs |   3.81µs | 211295.2926 |         0B |
| insitu\_reverse(x) |    757ns |    989ns | 793828.7726 |         0B |
| rev(x)             |   3.19µs |   4.26µs | 174660.5541 |     1.27KB |
| insitu\_reverse(x) |    766ns |      1µs | 819534.9571 |         0B |
| rev(x)             |    5.7µs |   7.32µs | 108322.3970 |    11.81KB |
| insitu\_reverse(x) |   1.13µs |    1.4µs | 569731.4864 |         0B |
| rev(x)             |  26.57µs |  88.73µs |   9677.0156 |   117.28KB |
| insitu\_reverse(x) |   4.82µs |   5.47µs | 160942.8703 |         0B |
| rev(x)             | 245.06µs | 899.01µs |   1011.6112 |     1.15MB |
| insitu\_reverse(x) |   39.6µs |  45.39µs |  19656.7879 |         0B |
| rev(x)             |   3.08ms |   4.08ms |    197.7598 |    11.44MB |
| insitu\_reverse(x) | 439.96µs |  578.6µs |   1508.0490 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-16-1.png" width="100%" />

## In-situ fill with random

`insitu_fill_runif()` is analogous to `runif()` but generates values in
the current vector rather than creating a new one.

``` r
x <- integer(10)
insitu_fill_runif(x, 10, 15)
x
#>  [1] 11 15 14 10 14 12 12 14 13 13
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
| runif(x)                           |  2.217512 |  2.129139 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  1.000000 |  1.000000 |  2.248070 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  2.043318 |  1.848344 |  1.215003 |        Inf |
| runif(x)                           |  2.638207 |  2.540683 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  1.000000 |  1.000000 |  2.622694 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.185699 |  1.284148 |  1.940192 |        Inf |
| runif(x)                           |  7.687628 |  7.233287 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  2.804415 |  2.814008 |  2.160172 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 |  6.395486 |        Inf |
| runif(x)                           | 16.937764 | 18.316994 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  5.732299 |  5.791610 |  2.997671 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 17.840202 |        Inf |
| runif(x)                           | 19.780708 | 21.423552 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  6.614378 |  6.775963 |  3.073381 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 20.705291 |        Inf |
| runif(x)                           | 21.513446 | 20.998086 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  7.261796 |  6.853383 |  3.024274 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 20.671712 |        Inf |

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
| runif(x)                           |   2.36µs |   3.05µs | 292462.98375 |     2.49KB |
| insitu\_fill\_runif(x, 0, 1)       |   1.28µs |   1.48µs | 613275.36448 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   2.23µs |    2.8µs | 337753.42221 |     2.49KB |
| runif(x)                           |   4.89µs |   5.82µs | 149451.57361 |     3.32KB |
| insitu\_fill\_runif(x, 0, 1)       |   2.05µs |   2.31µs | 391793.93905 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   2.33µs |   2.88µs | 322692.43165 |     2.49KB |
| runif(x)                           |  29.15µs |  32.52µs |  28605.67413 |    10.35KB |
| insitu\_fill\_runif(x, 0, 1)       |  10.54µs |  11.74µs |  79427.81157 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   3.76µs |   4.63µs | 188473.01298 |     2.49KB |
| runif(x)                           |  283.5µs | 351.07µs |   2781.31751 |    80.66KB |
| insitu\_fill\_runif(x, 0, 1)       |  95.98µs | 105.38µs |   9029.35038 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |  16.85µs |  18.11µs |  51579.87000 |     2.49KB |
| runif(x)                           |   2.73ms |   3.41ms |    291.10757 |   783.79KB |
| insitu\_fill\_runif(x, 0, 1)       |  974.6µs |   1.09ms |    889.84381 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) | 147.99µs | 155.81µs |   6088.42809 |     2.49KB |
| runif(x)                           |  30.29ms |  33.39ms |     29.73056 |     7.63MB |
| insitu\_fill\_runif(x, 0, 1)       |  10.21ms |  10.96ms |     89.33462 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   1.43ms |   1.61ms |    599.67207 |     2.49KB |

</details>

<img src="man/figures/README-unnamed-chunk-19-1.png" width="100%" />

## Related Software

  - [data.table](https://cran.r-project.org/package=data.table) performs
    a lot of operations in-situ (which data.table calls “by reference”)

## Acknowledgements

  - R Core for developing and maintaining the language.
  - CRAN maintainers, for patiently shepherding packages onto CRAN and
    maintaining the repository
