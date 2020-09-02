
<!-- README.md is generated from README.Rmd. Please edit that file -->

# insitu

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg) [![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
<!-- badges: end -->

`insitu` provides some functions for modifying vectors *in-situ* (in
place) without allocating a new vector.

This is an experimental package I wrote to try and figure out just how
fast things could be in R.

**Warning**: Modifying vectors in-situ can be fast, but doing so
violates some very strong norms within R internals.

**Warning**: Unless you are very confident on who has references to your
data, do not use this package for in-place modification.

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
| replace(x, idx, ins)       |  1.302997 |  1.387215 |  1.000000 |        NaN |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  1.357949 |        NaN |
| replace(x, idx, ins)       |  2.310120 |  2.705283 |  1.000000 |   2.446429 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  2.877832 |   1.000000 |
| replace(x, idx, ins)       |  6.449000 |  8.495833 |  1.000000 |   2.494071 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 |  7.700718 |   1.000000 |
| replace(x, idx, ins)       | 17.644418 | 28.445678 |  1.000000 |   2.499401 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 27.662998 |   1.000000 |
| replace(x, idx, ins)       | 19.721418 | 32.784572 |  1.000000 |   2.499940 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 29.986347 |   1.000000 |
| replace(x, idx, ins)       | 19.432021 | 19.106933 |  1.000000 |   2.499994 |
| insitu\_replace(x, 1, ins) |  1.000000 |  1.000000 | 18.630879 |   1.000000 |

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
| replace(x, idx, ins)       |   1.21µs |   1.45µs | 551213.4632 |         0B |
| insitu\_replace(x, 1, ins) |    891ns |   1.02µs | 768342.2989 |         0B |
| replace(x, idx, ins)       |   2.12µs |   2.81µs | 317363.0733 |     1.07KB |
| insitu\_replace(x, 1, ins) |    883ns |   1.08µs | 821907.5845 |       448B |
| replace(x, idx, ins)       |   6.42µs |   7.95µs | 113197.7402 |     9.86KB |
| insitu\_replace(x, 1, ins) |    983ns |   1.16µs | 784843.6022 |     3.95KB |
| replace(x, idx, ins)       |  45.14µs |  82.42µs |  11629.3552 |    97.75KB |
| insitu\_replace(x, 1, ins) |   2.57µs |   2.96µs | 321871.8936 |    39.11KB |
| replace(x, idx, ins)       | 438.99µs | 755.94µs |   1348.6334 |   976.66KB |
| insitu\_replace(x, 1, ins) |  21.57µs |  24.66µs |  36745.5278 |   390.67KB |
| replace(x, idx, ins)       |   4.66ms |   5.28ms |    170.3594 |     9.54MB |
| insitu\_replace(x, 1, ins) | 243.65µs | 304.14µs |   2721.7207 |     3.81MB |

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
| replace(x, idx, ins) | 1.555556 | 1.593407 | 1.000000 |        NaN |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.608675 |        NaN |
| replace(x, idx, ins) | 1.691689 | 2.061961 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 2.170192 |        NaN |
| replace(x, idx, ins) | 1.077857 | 1.443381 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.000000 | 1.000000 | 1.511917 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.642973 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.354472 | 1.000000 | 1.636545 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.511576 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.358697 | 1.000000 | 1.425511 |        NaN |
| replace(x, idx, ins) | 1.000000 | 1.000000 | 1.000000 |        Inf |
| insitu\_fill(x, ins) | 1.176413 | 1.085845 | 1.052741 |        NaN |

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
| replace(x, idx, ins) |   1.19µs |   1.48µs | 593754.7330 |         0B |
| insitu\_fill(x, ins) |    774ns |    904ns | 908984.2262 |         0B |
| replace(x, idx, ins) |   1.85µs |   2.26µs | 348583.5741 |     1.27KB |
| insitu\_fill(x, ins) |   1.09µs |   1.19µs | 725064.9436 |         0B |
| replace(x, idx, ins) |      5µs |   8.59µs | 112466.4568 |    11.81KB |
| insitu\_fill(x, ins) |   4.59µs |   4.84µs | 194763.1120 |         0B |
| replace(x, idx, ins) |  30.01µs |  71.63µs |  13598.1736 |   117.28KB |
| insitu\_fill(x, ins) |  39.33µs |  42.43µs |  22639.4674 |         0B |
| replace(x, idx, ins) | 277.53µs | 638.61µs |   1593.3701 |     1.15MB |
| insitu\_fill(x, ins) | 384.94µs | 422.75µs |   2339.6249 |         0B |
| replace(x, idx, ins) |   3.21ms |   4.05ms |    211.0911 |    11.44MB |
| insitu\_fill(x, ins) |   3.86ms |   4.27ms |    228.7315 |         0B |

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
| sort(x)         | 52.375669 | 51.569845 |  1.000000 |        NaN |
| insitu\_sort(x) |  1.000000 |  1.000000 | 48.016888 |        NaN |
| sort(x)         | 28.817784 | 31.153745 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 | 31.460311 |        NaN |
| sort(x)         |  6.884891 |  7.492354 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  7.754858 |        NaN |
| sort(x)         |  1.727628 |  2.494858 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  2.558111 |        NaN |
| sort(x)         |  1.117249 |  1.738403 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.719464 |        NaN |
| sort(x)         |  1.117325 |  1.343009 |  1.000000 |        Inf |
| insitu\_sort(x) |  1.000000 |  1.000000 |  1.388850 |        NaN |

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
| sort(x)         |  39.63µs |  46.91µs |   19806.7686 |         0B |
| insitu\_sort(x) |    748ns |    850ns | 1064044.5193 |         0B |
| sort(x)         |  40.94µs |  48.47µs |   19058.6766 |     1.27KB |
| insitu\_sort(x) |   1.38µs |   1.56µs |  571674.7843 |         0B |
| sort(x)         |  46.69µs |  55.89µs |   16308.6713 |    11.81KB |
| insitu\_sort(x) |   6.74µs |   7.37µs |  128428.6682 |         0B |
| sort(x)         | 107.52µs | 165.38µs |    5714.8534 |   117.28KB |
| insitu\_sort(x) |  60.13µs |  64.45µs |   14909.5477 |         0B |
| sort(x)         | 646.06µs |   1.12ms |     894.5138 |     1.15MB |
| insitu\_sort(x) | 591.86µs | 663.91µs |    1507.6809 |         0B |
| sort(x)         |    6.5ms |   9.65ms |     107.0368 |    11.44MB |
| insitu\_sort(x) |   6.03ms |   6.54ms |     150.7618 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-10-1.png" width="100%" />

## In-situ Shuffle

`insitu_shuffle()` is analogous to `sample()` but shuffles values in the
current vector rather than creating a new one.

``` r
x <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
insitu_shuffle(x)
x
#>  [1] 4 0 1 2 7 6 9 3 8 5
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
| sample(x)                |  9.438792 |  9.432432 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  1.000000 |  1.000000 |  9.605972 |        NaN |
| insitu\_shuffle\_fast(x) |  3.109698 |  3.315315 |  3.034864 |        Inf |
| sample(x)                |  5.906785 |  6.642070 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  1.000000 |  1.000000 |  6.274882 |        NaN |
| insitu\_shuffle\_fast(x) |  1.464173 |  1.568282 |  4.146698 |        Inf |
| sample(x)                |  7.841510 |  7.252259 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  2.145723 |  2.006280 |  3.665144 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 |  6.881756 |        Inf |
| sample(x)                | 11.458289 | 13.128064 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  3.117985 |  3.335542 |  4.019841 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 12.717101 |        Inf |
| sample(x)                | 14.389791 | 15.522464 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  3.225662 |  3.408825 |  4.454372 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 15.051390 |        Inf |
| sample(x)                | 11.274217 | 11.086651 |  1.000000 |        Inf |
| insitu\_shuffle(x)       |  3.023171 |  3.270823 |  3.425963 |        NaN |
| insitu\_shuffle\_fast(x) |  1.000000 |  1.000000 | 10.718112 |        Inf |

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
| sample(x)                |    5.9µs |   7.33µs | 1.247657e+05 |     2.49KB |
| insitu\_shuffle(x)       |    628ns |    772ns | 1.193500e+06 |         0B |
| insitu\_shuffle\_fast(x) |   2.06µs |   2.56µs | 3.661504e+05 |     2.49KB |
| sample(x)                |   9.34µs |  11.65µs | 8.034879e+04 |      4.2KB |
| insitu\_shuffle(x)       |   1.61µs |   1.82µs | 4.976809e+05 |         0B |
| insitu\_shuffle\_fast(x) |   2.33µs |   2.98µs | 3.136920e+05 |     2.49KB |
| sample(x)                |  43.04µs |  47.54µs | 2.012544e+04 |    18.27KB |
| insitu\_shuffle(x)       |   11.6µs |  13.15µs | 7.359866e+04 |         0B |
| insitu\_shuffle\_fast(x) |   5.39µs |   6.46µs | 1.468926e+05 |     2.49KB |
| sample(x)                | 415.03µs |  494.9µs | 1.971563e+03 |   158.89KB |
| insitu\_shuffle(x)       |  112.2µs | 117.94µs | 8.035624e+03 |         0B |
| insitu\_shuffle\_fast(x) |  35.84µs |  37.43µs | 2.542841e+04 |     2.49KB |
| sample(x)                |   5.39ms |   6.08ms | 1.622922e+02 |     1.53MB |
| insitu\_shuffle(x)       |   1.21ms |   1.39ms | 7.107337e+02 |         0B |
| insitu\_shuffle\_fast(x) | 376.38µs | 392.08µs | 2.400462e+03 |     2.49KB |
| sample(x)                |  74.59ms |  81.04ms | 1.246314e+01 |    15.26MB |
| insitu\_shuffle(x)       |   17.5ms |  22.15ms | 4.523996e+01 |         0B |
| insitu\_shuffle\_fast(x) |   5.89ms |   6.88ms | 1.324154e+02 |     2.49KB |

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
| rev(x)             | 4.546817 |  5.441786 |  1.000000 |        NaN |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  5.746810 |        NaN |
| rev(x)             | 5.437931 |  5.945559 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  6.009411 |        NaN |
| rev(x)             | 6.438889 |  7.304478 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  8.297369 |        NaN |
| rev(x)             | 6.207009 | 15.968661 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 15.573545 |        NaN |
| rev(x)             | 7.128077 | 15.639549 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 | 14.690525 |        NaN |
| rev(x)             | 6.677842 |  6.377821 |  1.000000 |        Inf |
| insitu\_reverse(x) | 1.000000 |  1.000000 |  6.726696 |        NaN |

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
| rev(x)             |   2.33µs |    3.1µs |  296472.2734 |         0B |
| insitu\_reverse(x) |    535ns |    619ns | 1313615.9552 |         0B |
| rev(x)             |    2.9µs |   3.56µs |  232783.5769 |     1.27KB |
| insitu\_reverse(x) |    561ns |    650ns | 1265597.0576 |         0B |
| rev(x)             |   5.49µs |   7.61µs |  108282.5752 |    11.81KB |
| insitu\_reverse(x) |    893ns |      1µs |  953884.2764 |         0B |
| rev(x)             |  25.37µs |  78.67µs |   11915.5589 |   117.28KB |
| insitu\_reverse(x) |   4.28µs |   4.88µs |  189989.4664 |         0B |
| rev(x)             | 290.61µs | 706.11µs |    1332.5326 |     1.15MB |
| insitu\_reverse(x) |  39.33µs |  43.56µs |   21314.1226 |         0B |
| rev(x)             |   2.78ms |   3.62ms |     250.8282 |    11.44MB |
| insitu\_reverse(x) | 423.81µs | 521.47µs |    1592.7781 |         0B |

</details>

<img src="man/figures/README-unnamed-chunk-16-1.png" width="100%" />

## In-situ fill with random

`insitu_fill_runif()` is analogous to `runif()` but generates values in
the current vector rather than creating a new one.

``` r
x <- integer(10)
insitu_fill_runif(x, 10, 15)
x
#>  [1] 14 14 15 13 11 13 10 11 15 11
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
| runif(x)                           |  2.411950 |  2.795353 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  1.000000 |  1.000000 |  2.881447 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  2.375262 |  2.583557 |  1.205771 |        Inf |
| runif(x)                           |  2.866546 |  3.023120 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  1.000000 |  1.000000 |  2.919731 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.471618 |  1.633130 |  1.915442 |        Inf |
| runif(x)                           |  7.695180 |  6.320777 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  2.626059 |  2.217592 |  2.924314 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 |  5.746306 |        Inf |
| runif(x)                           | 16.568695 | 18.312150 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  5.678310 |  5.628338 |  3.221401 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 17.719036 |        Inf |
| runif(x)                           | 19.209331 | 22.178474 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  6.563929 |  7.047838 |  3.146685 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 21.237926 |        Inf |
| runif(x)                           | 19.994537 | 21.009341 |  1.000000 |        Inf |
| insitu\_fill\_runif(x, 0, 1)       |  6.863185 |  6.820089 |  3.032724 |        NaN |
| insitu\_fill\_runif\_fast(x, 0, 1) |  1.000000 |  1.000000 | 20.028337 |        Inf |

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
| runif(x)                           |   2.26µs |   3.03µs | 292748.04253 |     2.49KB |
| insitu\_fill\_runif(x, 0, 1)       |    922ns |   1.11µs | 770454.19098 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |    2.3µs |      3µs | 313720.19944 |     2.49KB |
| runif(x)                           |   4.93µs |   5.95µs | 154647.92489 |     3.32KB |
| insitu\_fill\_runif(x, 0, 1)       |   1.75µs |   1.98µs | 451649.31461 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |    2.4µs |   3.27µs | 282441.21964 |     2.49KB |
| runif(x)                           |  29.06µs |  31.39µs |  30222.71158 |    10.35KB |
| insitu\_fill\_runif(x, 0, 1)       |   9.89µs |  11.08µs |  86854.45717 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   3.83µs |   4.75µs | 191081.92380 |     2.49KB |
| runif(x)                           | 283.03µs | 335.79µs |   2922.72605 |    80.66KB |
| insitu\_fill\_runif(x, 0, 1)       |  95.35µs | 104.27µs |   9380.60556 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |  16.88µs |  18.12µs |  52709.37660 |     2.49KB |
| runif(x)                           |   2.85ms |   3.28ms |    303.83416 |   783.79KB |
| insitu\_fill\_runif(x, 0, 1)       | 943.39µs |   1.05ms |    948.90970 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) | 143.67µs | 149.91µs |   6370.92457 |     2.49KB |
| runif(x)                           |  28.85ms |  32.76ms |     31.23215 |     7.63MB |
| insitu\_fill\_runif(x, 0, 1)       |   9.82ms |  10.77ms |     93.35466 |         0B |
| insitu\_fill\_runif\_fast(x, 0, 1) |   1.43ms |   1.55ms |    611.64633 |     2.49KB |

</details>

<img src="man/figures/README-unnamed-chunk-19-1.png" width="100%" />

## Related Software

  - [data.table](https://cran.r-project.org/package=data.table) performs
    a lot of operations in-situ (which data.table calls “by reference”)

## Acknowledgements

  - R Core for developing and maintaining the language.
  - CRAN maintainers, for patiently shepherding packages onto CRAN and
    maintaining the repository
