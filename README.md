
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
| insitu\_sort(x)                            | Sort the elements of a vector                                          | Yes     | Yes  |           |
|                                            |                                                                        |         |      |           |

#### Fast Variants

The `_fast` versions of some functions use their own random-number
generator rather than the one supplied in R. This generator is
[xoshiro256++](http://prng.di.unimi.it/). It is very fast, but has
different properties from R’s built in random number generator. Use with
caution.

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
| replace(x, idx, ins)       |  1.241861 |  1.233105 |  1.000000 |        NaN |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  1.311755 |        NaN |
| replace(x, idx, ins)       |  2.040300 |  2.276765 |  1.000000 |   2.446429 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  2.460077 |   1.000000 |
| replace(x, idx, ins)       |  5.338397 |  7.134181 |  1.000000 |   2.494071 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  6.750720 |   1.000000 |
| replace(x, idx, ins)       | 15.452247 | 26.413083 |  1.000000 |   2.499401 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 25.646324 |   1.000000 |
| replace(x, idx, ins)       | 19.619739 | 33.642784 |  1.000000 |   2.499940 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 30.651642 |   1.000000 |
| replace(x, idx, ins)       | 19.402404 | 18.190081 |  1.000000 |   2.499994 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 17.813360 |   1.000000 |

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
| replace(x, idx, ins)       |   1.29µs |   1.59µs | 546007.5980 |         0B |
| insitu\_replace(x, 1, ins) |   1.07µs |   1.27µs | 699029.4479 |         0B |
| replace(x, idx, ins)       |   2.13µs |   2.62µs | 297293.8467 |     1.07KB |
| insitu\_replace(x, 1, ins) |   1.06µs |   1.22µs | 681761.0951 |       448B |
| replace(x, idx, ins)       |    6.3µs |   7.78µs | 110956.3977 |     9.86KB |
| insitu\_replace(x, 1, ins) |    1.2µs |   1.43µs | 576792.5439 |     3.95KB |
| replace(x, idx, ins)       |  44.24µs |  87.97µs |  10798.0014 |    97.75KB |
| insitu\_replace(x, 1, ins) |   2.94µs |   3.37µs | 262770.7713 |    39.11KB |
| replace(x, idx, ins)       | 426.07µs | 825.45µs |   1182.7554 |   976.66KB |
| insitu\_replace(x, 1, ins) |  21.68µs |  25.06µs |  33944.6554 |   390.67KB |
| replace(x, idx, ins)       |   4.94ms |   5.53ms |    164.1017 |     9.54MB |
| insitu\_replace(x, 1, ins) | 247.25µs | 322.64µs |   2378.8128 |     3.81MB |

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
| replace(x, idx, ins) | 1.418259 | 1.434664 | 1.000000 |        NaN |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.524706 |        NaN |
| replace(x, idx, ins) | 1.583133 | 1.936554 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 2.170449 |        NaN |
| replace(x, idx, ins) | 1.054626 | 1.202658 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.272733 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.756241 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.229603 | 1.000000 | 1.751837 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.600853 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.102361 | 1.000000 | 1.537459 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.000000 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.092076 | 1.040353 | 1.112988 |        NaN |

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
| replace(x, idx, ins) |    1.3µs |   1.55µs | 550433.2834 |         0B |
| insitu\_fill(x, ins) |    945ns |    1.1µs | 786129.7150 |         0B |
| replace(x, idx, ins) |   1.92µs |   2.35µs | 333706.1717 |     1.27KB |
| insitu\_fill(x, ins) |   1.26µs |   1.42µs | 617234.3035 |         0B |
| replace(x, idx, ins) |   4.46µs |   7.22µs | 131239.2460 |    11.81KB |
| insitu\_fill(x, ins) |   4.49µs |   4.74µs | 198650.4758 |         0B |
| replace(x, idx, ins) |  29.47µs |  70.36µs |  13303.6225 |   117.28KB |
| insitu\_fill(x, ins) |  36.62µs |   39.8µs |  23890.7319 |         0B |
| replace(x, idx, ins) |  309.7µs | 651.62µs |   1525.3561 |     1.15MB |
| insitu\_fill(x, ins) | 330.21µs | 392.95µs |   2480.4136 |         0B |
| replace(x, idx, ins) |   3.29ms |   4.01ms |    208.9375 |    11.44MB |
| insitu\_fill(x, ins) |   3.56ms |   4.03ms |    239.2026 |         0B |

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
| sort(x)         | 41.278671 | 43.203405 |  1.000000 |        NaN |
| insitu\_sort(x) |  1.000000 |  1.000000 | 42.303925 |        NaN |
| sort(x)         | 25.698803 | 26.551185 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 | 25.076374 |        NaN |
| sort(x)         |  6.526590 |  7.414666 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  7.613729 |        NaN |
| sort(x)         |  1.733806 |  2.618806 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  2.725311 |        NaN |
| sort(x)         |  1.129045 |  1.755064 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.776082 |        NaN |
| sort(x)         |  1.079406 |  1.450852 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.472845 |        NaN |

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
| sort(x)         |  39.51µs |  46.84µs |  19478.4944 |         0B |
| insitu\_sort(x) |    954ns |   1.16µs | 733700.8515 |         0B |
| sort(x)         |  40.27µs |  49.11µs |  18295.3131 |     1.27KB |
| insitu\_sort(x) |   1.55µs |    1.8µs | 483616.6163 |         0B |
| sort(x)         |  43.66µs |  54.94µs |  16291.7566 |    11.81KB |
| insitu\_sort(x) |   7.11µs |   7.84µs | 123944.3259 |         0B |
| sort(x)         | 109.58µs | 173.75µs |   5333.7207 |   117.28KB |
| insitu\_sort(x) |  60.35µs |  67.76µs |  14507.3767 |         0B |
| sort(x)         | 688.35µs |   1.21ms |    792.5908 |     1.15MB |
| insitu\_sort(x) | 592.11µs | 672.98µs |   1477.7928 |         0B |
| sort(x)         |   6.62ms |   9.78ms |    101.3818 |    11.44MB |
| insitu\_sort(x) |   6.33ms |   6.75ms |    144.2143 |         0B |

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
      check    = FALSE,
      relative = TRUE
    )
  }
)

res_rel %>%
  select(expression, min, median, `itr/sec`, mem_alloc) %>%
  knitr::kable()
```

| expression         |      min |   median |  itr/sec | mem\_alloc |
| :----------------- | -------: | -------: | -------: | ---------: |
| sample(x)          | 6.894231 | 7.064299 | 1.000000 |        Inf |
| insitu\_shuffle(x) | 1.000000 | 1.000000 | 7.316364 |        NaN |
| sample(x)          | 5.347292 | 5.880952 | 1.000000 |        Inf |
| insitu\_shuffle(x) | 1.000000 | 1.000000 | 5.662780 |        NaN |
| sample(x)          | 3.544081 | 3.496057 | 1.000000 |        Inf |
| insitu\_shuffle(x) | 1.000000 | 1.000000 | 3.522028 |        NaN |
| sample(x)          | 3.791260 | 3.955682 | 1.000000 |        Inf |
| insitu\_shuffle(x) | 1.000000 | 1.000000 | 4.040656 |        NaN |
| sample(x)          | 4.400853 | 4.313949 | 1.000000 |        Inf |
| insitu\_shuffle(x) | 1.000000 | 1.000000 | 4.176216 |        NaN |
| sample(x)          | 3.947524 | 3.666679 | 1.000000 |        Inf |
| insitu\_shuffle(x) | 1.000000 | 1.000000 | 3.453054 |        NaN |

``` r

res_abs <- bench::press(
  N = N,
  {
    x <- runif(N)
    
    bench::mark(
      sample(x),
      insitu_shuffle(x),
      check    = FALSE,
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
| sample(x)          |   5.98µs |   7.19µs | 124827.2530 |     2.49KB |
| insitu\_shuffle(x) |    794ns |    976ns | 946183.9866 |         0B |
| sample(x)          |   9.55µs |  11.86µs |  74778.1284 |      4.2KB |
| insitu\_shuffle(x) |   1.82µs |   2.12µs | 429224.4327 |         0B |
| sample(x)          |  42.57µs |  46.61µs |  20370.7246 |    18.27KB |
| insitu\_shuffle(x) |  11.85µs |  13.67µs |  68856.2140 |         0B |
| sample(x)          | 412.91µs | 505.66µs |   1893.3209 |   158.89KB |
| insitu\_shuffle(x) | 112.38µs | 127.59µs |   7711.6986 |         0B |
| sample(x)          |   5.34ms |   6.25ms |    158.2409 |     1.53MB |
| insitu\_shuffle(x) |   1.25ms |   1.44ms |    659.7863 |         0B |
| sample(x)          |  72.06ms |  77.33ms |     12.0217 |    15.26MB |
| insitu\_shuffle(x) |  18.02ms |  22.72ms |     42.6206 |         0B |

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
| rev(x)             | 4.039941 |  4.593596 |  1.000000 |        NaN |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  4.867159 |        NaN |
| rev(x)             | 4.493225 |  5.113663 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  5.168320 |        NaN |
| rev(x)             | 5.188818 |  6.103535 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  6.598503 |        NaN |
| rev(x)             | 5.774873 | 16.068639 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 16.203002 |        NaN |
| rev(x)             | 6.724603 | 17.457932 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 17.238845 |        NaN |
| rev(x)             | 7.152706 |  7.128707 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  7.833366 |        NaN |

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
| rev(x)             |   2.67µs |   3.51µs |  258742.0867 |         0B |
| insitu\_reverse(x) |    686ns |    825ns |  979483.0583 |         0B |
| rev(x)             |    3.1µs |   3.92µs |  205716.4316 |     1.27KB |
| insitu\_reverse(x) |    719ns |    862ns | 1045618.6652 |         0B |
| rev(x)             |   5.36µs |   7.21µs |  113599.0774 |    11.81KB |
| insitu\_reverse(x) |   1.07µs |   1.19µs |  765417.6909 |         0B |
| rev(x)             |  29.75µs |   85.3µs |   10855.9289 |   117.28KB |
| insitu\_reverse(x) |    4.6µs |   5.18µs |  185400.7858 |         0B |
| rev(x)             | 259.89µs |  783.1µs |    1224.2031 |     1.15MB |
| insitu\_reverse(x) |  39.51µs |  45.13µs |   20544.7953 |         0B |
| rev(x)             |   2.95ms |   3.73ms |     223.9566 |    11.44MB |
| insitu\_reverse(x) | 444.07µs | 595.25µs |    1409.2116 |         0B |

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

| expression                         |      min |   median |  itr/sec | mem\_alloc |
| :--------------------------------- | -------: | -------: | -------: | ---------: |
| runif(x)                           | 1.870017 | 2.008148 | 1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       | 1.000000 | 1.000000 | 2.048875 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) | 1.787695 | 1.936296 | 1.215929 |        Inf |
| runif(x)                           | 2.442684 | 2.409111 | 1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       | 1.000000 | 1.000000 | 2.318678 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) | 1.277338 | 1.372098 | 1.670423 |        Inf |
| runif(x)                           | 5.231884 | 4.928995 | 1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       | 1.844746 | 1.735290 | 2.831551 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) | 1.000000 | 1.000000 | 4.722702 |        Inf |
| runif(x)                           | 8.132951 | 9.077627 | 1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       | 2.749339 | 2.805251 | 3.237286 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) | 1.000000 | 1.000000 | 8.850086 |        Inf |
| runif(x)                           | 8.265000 | 9.116339 | 1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       | 2.813682 | 2.853143 | 3.150033 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) | 1.000000 | 1.000000 | 9.017577 |        Inf |
| runif(x)                           | 8.683844 | 8.902556 | 1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       | 2.906579 | 2.897405 | 3.015936 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) | 1.000000 | 1.000000 | 8.616409 |        Inf |

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
| runif(x)                           |   2.15µs |   2.64µs | 332633.90432 |     2.49KB |
| insitu\_fill\_runif(x, 0, 1)       |   1.16µs |   1.43µs | 594461.29803 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   2.03µs |   2.65µs | 347844.47682 |     2.49KB |
| runif(x)                           |   4.66µs |   5.42µs | 171388.46748 |     3.32KB |
| insitu\_fill\_runif(x, 0, 1)       |   1.93µs |   2.29µs | 372149.17391 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   2.42µs |   3.02µs | 305247.59400 |     2.49KB |
| runif(x)                           |  28.84µs |     32µs |  29063.97655 |    10.35KB |
| insitu\_fill\_runif(x, 0, 1)       |  10.16µs |  11.43µs |  83540.17602 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   5.56µs |   6.77µs | 131305.03980 |     2.49KB |
| runif(x)                           | 287.35µs | 349.97µs |   2813.90250 |    80.66KB |
| insitu\_fill\_runif(x, 0, 1)       |  95.88µs | 108.98µs |   9076.22115 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |  35.97µs |  38.31µs |  24486.54854 |     2.49KB |
| runif(x)                           |   2.87ms |   3.37ms |    295.66992 |   783.79KB |
| insitu\_fill\_runif(x, 0, 1)       | 976.13µs |   1.08ms |    911.68201 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) | 336.77µs | 369.54µs |   2650.25203 |     2.49KB |
| runif(x)                           |  30.13ms |  32.68ms |     30.75942 |     7.63MB |
| insitu\_fill\_runif(x, 0, 1)       |  10.05ms |  10.95ms |     90.51580 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   3.35ms |   3.69ms |    264.26280 |     2.49KB |

</details>

<img src="man/figures/README-unnamed-chunk-19-1.png" width="100%" />

## Related Software

  - [data.table](https://cran.r-project.org/package=data.table) performs
    a lot of operations in-situ (which data.table calls “by reference”)

## Acknowledgements

  - R Core for developing and maintaining the language.
  - CRAN maintainers, for patiently shepherding packages onto CRAN and
    maintaining the repository
