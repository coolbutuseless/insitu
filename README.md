
<!-- README.md is generated from README.Rmd. Please edit that file -->

# insitu

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
[![R-CMD-check](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/coolbutuseless/insitu/actions/workflows/R-CMD-check.yaml)
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
  and assign new values into it. The speed saved by switching to in-situ
  modification will only possibly be useful if this operations is
  performed many, many times.

In the words of Luke Tierney in his User2020 keynote:

    You should never modify something without duplicating it.

This package ignores this advice. Beware.

## What’s in the box

| insitu | description | integer | real | character |
|----|----|----|----|----|
| insitu_fill(x, value) | Fill vector with the given value | Yes | Yes | Yes |
| insitu_fill_runif(x, lower, upper) | Fill vector with uniform random numbers | Yes | Yes |  |
| insitu_fill_runif_fast(x, lower, upper) | Fill vector with uniform random numbers | Yes | Yes |  |
| insitu_replace(x, pos, values) | Replace values in x with given values starting from the given position | Yes | Yes | Yes |
| insitu_reverse(x) | Reverse vector | Yes | Yes | Yes |
| insitu_shuffle(x) | Shuffle the elements of a vector | Yes | Yes | Yes |
| insitu_shuffle_fast(x) | Shuffle the elements of a vector | Yes | Yes | Yes |
| insitu_sort(x) | Sort the elements of a vector | Yes | Yes |  |
|  |  |  |  |  |

#### Fast Variants

The `_fast` versions of some functions use their own random-number
generator rather than the one supplied in R.

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
x <- integer(10)
insitu_replace(x, 6, 1:5)
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
| replace(x, idx, ins)      |  1.428535 |  1.333346 |  1.000000 |       NaN |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 |  1.429349 |       NaN |
| replace(x, idx, ins)      |  2.285707 |  2.111089 |  1.000000 |  2.446429 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 |  2.297614 |  1.000000 |
| replace(x, idx, ins)      |  8.374978 |  7.700018 |  1.000000 |  2.494071 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 |  7.576151 |  1.000000 |
| replace(x, idx, ins)      | 35.311706 | 36.683859 |  1.000000 |  2.499401 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 | 32.760344 |  1.000000 |
| replace(x, idx, ins)      | 36.189483 | 40.698049 |  1.000000 |  2.499940 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 | 37.906871 |  1.000000 |
| replace(x, idx, ins)      | 37.648467 | 43.369127 |  1.000000 |  2.499994 |
| insitu_replace(x, 1, ins) |  1.000000 |  1.000000 | 41.569032 |  1.000000 |

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
| replace(x, idx, ins)      |    410ns | 492.01ns | 1848253.0154 |        0B |
| insitu_replace(x, 1, ins) | 246.01ns | 369.01ns | 2152198.2002 |        0B |
| replace(x, idx, ins)      | 696.99ns | 779.01ns | 1087525.9090 |    1.07KB |
| insitu_replace(x, 1, ins) | 246.01ns | 369.01ns | 2531716.3806 |      448B |
| replace(x, idx, ins)      |   2.75µs |   3.24µs |  280760.8600 |    9.86KB |
| insitu_replace(x, 1, ins) |    328ns | 410.01ns | 2228238.3120 |    3.95KB |
| replace(x, idx, ins)      |  23.41µs |  27.27µs |   34425.5371 |   97.75KB |
| insitu_replace(x, 1, ins) | 696.99ns | 779.01ns | 1228592.8401 |   39.11KB |
| replace(x, idx, ins)      |  227.3µs | 270.11µs |    3682.3209 |  976.66KB |
| insitu_replace(x, 1, ins) |   6.31µs |    6.4µs |  151309.2391 |  390.67KB |
| replace(x, idx, ins)      |   2.54ms |   2.69ms |     372.1388 |    9.54MB |
| insitu_replace(x, 1, ins) |  61.58µs |  62.16µs |   15534.2653 |    3.81MB |

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
x <- integer(10)
insitu_fill(x, 3L)
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
| replace(x, idx, ins) | 1.499970 | 1.714192 | 1.000000 |       NaN |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 1.634498 |       NaN |
| replace(x, idx, ins) | 1.777743 | 1.636370 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 1.871725 |       NaN |
| replace(x, idx, ins) | 1.456526 | 1.583333 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 1.749103 |       NaN |
| replace(x, idx, ins) | 1.348558 | 1.491687 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 1.498297 |       NaN |
| replace(x, idx, ins) | 1.290216 | 1.427333 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 1.410597 |       NaN |
| replace(x, idx, ins) | 1.252552 | 1.434858 | 1.000000 |       Inf |
| insitu_fill(x, ins)  | 1.000000 | 1.000000 | 1.429511 |       NaN |

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
| replace(x, idx, ins) |    410ns |    492ns | 1969563.7470 |        0B |
| insitu_fill(x, ins)  | 205.01ns | 287.01ns | 3155974.7038 |        0B |
| replace(x, idx, ins) |    656ns | 738.01ns | 1105102.2659 |    1.27KB |
| insitu_fill(x, ins)  |    328ns | 451.01ns | 2066399.3722 |        0B |
| replace(x, idx, ins) |   2.75µs |   3.12µs |  290552.1135 |   11.81KB |
| insitu_fill(x, ins)  |   1.89µs |   1.97µs |  492835.9767 |        0B |
| replace(x, idx, ins) |  22.84µs |  27.22µs |   35336.0034 |  117.28KB |
| insitu_fill(x, ins)  |  17.06µs |  17.34µs |   55187.6435 |        0B |
| replace(x, idx, ins) | 223.98µs | 270.72µs |    3656.4643 |    1.15MB |
| insitu_fill(x, ins)  | 177.53µs | 186.43µs |    5275.3371 |        0B |
| replace(x, idx, ins) |   2.52ms |   2.73ms |     363.0268 |   11.44MB |
| insitu_fill(x, ins)  |   1.82ms |    1.9ms |     521.4078 |        0B |

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
| sort(x)        | 55.797984 | 37.312511 |  1.000000 |       NaN |
| insitu_sort(x) |  1.000000 |  1.000000 | 35.500509 |       NaN |
| sort(x)        | 22.230452 | 20.666422 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 | 20.113415 |       NaN |
| sort(x)        |  4.544291 |  4.746978 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  4.884280 |       NaN |
| sort(x)        |  1.364627 |  1.649471 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  1.606509 |       NaN |
| sort(x)        |  1.009737 |  1.234818 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  1.208397 |       NaN |
| sort(x)        |  1.059204 |  1.220954 |  1.000000 |       Inf |
| insitu_sort(x) |  1.000000 |  1.000000 |  1.209129 |       NaN |

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
| sort(x)        |  11.56µs |  12.51µs |   75447.9521 |        0B |
| insitu_sort(x) | 205.01ns | 287.01ns | 2997162.6282 |        0B |
| sort(x)        |  11.81µs |  12.96µs |   73107.3657 |    1.27KB |
| insitu_sort(x) | 533.01ns | 615.01ns | 1502872.9309 |        0B |
| sort(x)        |  14.68µs |  15.95µs |   59707.9840 |   11.81KB |
| insitu_sort(x) |   3.24µs |    3.4µs |  281119.9790 |        0B |
| sort(x)        |  41.16µs |  50.92µs |   19266.3655 |  117.28KB |
| insitu_sort(x) |  30.14µs |  30.87µs |   31309.6087 |        0B |
| sort(x)        | 300.69µs | 376.63µs |    2661.2252 |    1.15MB |
| insitu_sort(x) | 298.97µs | 309.35µs |    3174.0371 |        0B |
| sort(x)        |   2.96ms |   3.74ms |     268.3219 |   11.44MB |
| insitu_sort(x) |   3.04ms |   3.13ms |     316.8744 |        0B |

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

| expression             |       min |    median |   itr/sec | mem_alloc |
|:-----------------------|----------:|----------:|----------:|----------:|
| sample(x)              | 13.000000 | 10.166696 |  1.000000 |       NaN |
| insitu_shuffle(x)      |  1.000000 |  1.000059 |  9.497897 |       NaN |
| insitu_shuffle_fast(x) |  1.000000 |  1.000000 | 10.688885 |       Inf |
| sample(x)              |  7.666667 |  8.571429 |  1.000000 |       Inf |
| insitu_shuffle(x)      |  1.000000 |  1.071441 |  7.211200 |       NaN |
| insitu_shuffle_fast(x) |  1.000000 |  1.000000 |  8.425420 |       NaN |
| sample(x)              |  6.571424 |  7.010868 |  1.000000 |       Inf |
| insitu_shuffle(x)      |  1.000000 |  1.043478 |  6.788954 |       NaN |
| insitu_shuffle_fast(x) |  1.059522 |  1.000000 |  6.898005 |       NaN |
| sample(x)              |  7.067552 |  7.568210 |  1.000000 |       Inf |
| insitu_shuffle(x)      |  1.000000 |  1.000000 |  7.400929 |       NaN |
| insitu_shuffle_fast(x) |  1.038601 |  1.028470 |  7.164622 |       NaN |
| sample(x)              |  7.927667 |  8.146069 |  1.000000 |       Inf |
| insitu_shuffle(x)      |  1.000000 |  1.000000 |  7.989710 |       NaN |
| insitu_shuffle_fast(x) |  1.036344 |  1.024535 |  7.899420 |       NaN |
| sample(x)              |  8.513607 |  8.334998 |  1.000000 |       Inf |
| insitu_shuffle(x)      |  1.000000 |  1.113752 |  7.408285 |       NaN |
| insitu_shuffle_fast(x) |  1.000383 |  1.000000 |  8.341736 |       NaN |

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

| expression             |      min |   median |      itr/sec | mem_alloc |
|:-----------------------|---------:|---------:|-------------:|----------:|
| sample(x)              |   2.09µs |   2.38µs | 3.915130e+05 |        0B |
| insitu_shuffle(x)      |    164ns | 246.01ns | 3.693770e+06 |        0B |
| insitu_shuffle_fast(x) |    164ns |    246ns | 4.110824e+06 |        0B |
| sample(x)              |   3.73µs |    4.8µs | 1.962182e+05 |    1.71KB |
| insitu_shuffle(x)      |    492ns | 615.01ns | 1.447280e+06 |        0B |
| insitu_shuffle_fast(x) | 451.01ns | 574.01ns | 1.678223e+06 |        0B |
| sample(x)              |   22.1µs |  25.71µs | 3.757693e+04 |   15.77KB |
| insitu_shuffle(x)      |   3.44µs |   3.94µs | 2.508289e+05 |        0B |
| insitu_shuffle_fast(x) |   3.65µs |   3.77µs | 2.550739e+05 |        0B |
| sample(x)              |  238.5µs |  262.4µs | 3.743312e+03 |   156.4KB |
| insitu_shuffle(x)      |  34.03µs |  34.65µs | 2.751845e+04 |        0B |
| insitu_shuffle_fast(x) |   35.3µs |  35.55µs | 2.707207e+04 |        0B |
| sample(x)              |   2.71ms |   2.89ms | 3.429788e+02 |    1.53MB |
| insitu_shuffle(x)      |  347.6µs | 358.67µs | 2.716908e+03 |        0B |
| insitu_shuffle_fast(x) | 358.83µs | 366.89µs | 2.676099e+03 |        0B |
| sample(x)              |  30.31ms |  31.84ms | 3.143281e+01 |   15.26MB |
| insitu_shuffle(x)      |   3.63ms |   4.28ms | 2.299212e+02 |        0B |
| insitu_shuffle_fast(x) |   3.65ms |   3.85ms | 2.579891e+02 |        0B |

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
| rev(x)            |  4.749956 |  4.399844 |  1.000000 |       NaN |
| insitu_reverse(x) |  1.000000 |  1.000000 |  4.292632 |       NaN |
| rev(x)            |  5.750044 |  4.666667 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 |  5.154166 |       NaN |
| rev(x)            |  8.374978 |  8.300018 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 |  8.542689 |       NaN |
| rev(x)            | 10.042591 | 13.666711 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 | 13.190408 |       NaN |
| rev(x)            |  9.010117 | 11.740379 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 | 11.288647 |       NaN |
| rev(x)            | 10.094735 | 11.349331 |  1.000000 |       Inf |
| insitu_reverse(x) |  1.000000 |  1.000000 | 11.156176 |       NaN |

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
| rev(x)            |    738ns | 861.01ns | 1086648.8815 |        0B |
| insitu_reverse(x) |    164ns | 205.01ns | 4346415.3802 |        0B |
| rev(x)            |    984ns |   1.15µs |  758242.9216 |    1.27KB |
| insitu_reverse(x) |    164ns | 205.01ns | 4152819.8291 |        0B |
| rev(x)            |   2.71µs |   3.65µs |  266007.8319 |   11.81KB |
| insitu_reverse(x) |    328ns |    410ns | 2431225.7872 |        0B |
| rev(x)            |  19.31µs |  27.76µs |   35825.8642 |  117.28KB |
| insitu_reverse(x) |   1.93µs |   2.09µs |  466817.0161 |        0B |
| rev(x)            | 182.61µs | 238.95µs |    4167.2199 |    1.15MB |
| insitu_reverse(x) |  20.09µs |  20.95µs |   46985.6204 |        0B |
| rev(x)            |   2.03ms |   2.41ms |     414.3907 |   11.44MB |
| insitu_reverse(x) | 222.22µs | 226.05µs |    4367.0878 |        0B |

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

| expression                      |      min |   median |  itr/sec | mem_alloc |
|:--------------------------------|---------:|---------:|---------:|----------:|
| runif(x)                        | 1.333333 | 1.249989 | 1.000000 |       NaN |
| insitu_fill_runif(x, 0, 1)      | 1.166696 | 1.124972 | 1.227076 |       NaN |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 1.401092 |       Inf |
| runif(x)                        | 2.249900 | 2.099943 | 1.000000 |       Inf |
| insitu_fill_runif(x, 0, 1)      | 1.999911 | 1.799936 | 1.278401 |       NaN |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 2.250320 |       NaN |
| runif(x)                        | 3.500000 | 3.657124 | 1.000000 |       Inf |
| insitu_fill_runif(x, 0, 1)      | 3.343755 | 3.371411 | 1.136509 |       NaN |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 3.731777 |       NaN |
| runif(x)                        | 3.981819 | 4.403569 | 1.000000 |       Inf |
| insitu_fill_runif(x, 0, 1)      | 3.865455 | 3.832142 | 1.131517 |       NaN |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 4.373772 |       NaN |
| runif(x)                        | 4.029607 | 4.483448 | 1.000000 |       Inf |
| insitu_fill_runif(x, 0, 1)      | 3.883049 | 3.961622 | 1.122150 |       NaN |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 4.408948 |       NaN |
| runif(x)                        | 4.365594 | 4.543865 | 1.000000 |       Inf |
| insitu_fill_runif(x, 0, 1)      | 3.959523 | 3.963309 | 1.142957 |       NaN |
| insitu_fill_runif_fast(x, 0, 1) | 1.000000 | 1.000000 | 4.526006 |       NaN |

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

| expression                      |      min |   median |      itr/sec | mem_alloc |
|:--------------------------------|---------:|---------:|-------------:|----------:|
| runif(x)                        | 287.01ns | 410.01ns | 2140193.6068 |        0B |
| insitu_fill_runif(x, 0, 1)      | 287.01ns | 369.01ns | 2465410.0546 |        0B |
| insitu_fill_runif_fast(x, 0, 1) |    246ns | 328.01ns | 2556902.8985 |        0B |
| runif(x)                        |    738ns | 861.01ns |  954938.0724 |      848B |
| insitu_fill_runif(x, 0, 1)      |    656ns |    738ns | 1158247.6454 |        0B |
| insitu_fill_runif_fast(x, 0, 1) |    328ns | 410.01ns | 2072013.9209 |        0B |
| runif(x)                        |   4.59µs |   5.17µs |  180842.5131 |    7.86KB |
| insitu_fill_runif(x, 0, 1)      |   4.39µs |   4.84µs |  206832.5143 |        0B |
| insitu_fill_runif_fast(x, 0, 1) |   1.31µs |   1.44µs |  668361.7853 |        0B |
| runif(x)                        |  44.94µs |  51.09µs |   19341.6114 |   78.17KB |
| insitu_fill_runif(x, 0, 1)      |  43.54µs |  43.99µs |   22263.7024 |        0B |
| insitu_fill_runif_fast(x, 0, 1) |  11.28µs |  11.48µs |   85157.8757 |        0B |
| runif(x)                        | 442.84µs | 496.92µs |    1995.5829 |   781.3KB |
| insitu_fill_runif(x, 0, 1)      | 431.89µs | 443.64µs |    2231.1179 |        0B |
| insitu_fill_runif_fast(x, 0, 1) | 110.78µs | 112.71µs |    8663.0863 |        0B |
| runif(x)                        |   4.91ms |   5.09ms |     195.9572 |    7.63MB |
| insitu_fill_runif(x, 0, 1)      |   4.39ms |   4.51ms |     220.7408 |        0B |
| insitu_fill_runif_fast(x, 0, 1) |   1.11ms |   1.14ms |     866.2841 |        0B |

</details>

<img src="man/figures/README-unnamed-chunk-19-1.png" width="100%" />

## Related Software

- [data.table](https://cran.r-project.org/package=data.table) performs a
  lot of operations in-situ (i.e. “by reference”)
