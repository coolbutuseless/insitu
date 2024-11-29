
# insitu 0.1.3.9006

* [9006] `ins_copy_if()`
* [9006] `ins_is_na()`
* [9006] `ins_copy()` replaces old `ins_copy()`, `ins_copy_from()`, 
         `ins_replace()` and `ins_fill()`
* [9005] Including `insitu` helper for use with `with()`
* [9004] Use math.h fma() instead of rolling my own
* [9004] nearly full complement of unary and binary math ops
* [9003] add `ins_copy()`
* [9002] Use prefix `ins_`
* [9002] Remove benchmarks from readme
* [9002] Remove xoshiro. Use lehmer64 on all platforms. Needs testing 
         on windows.
* [9001] Add fused multiply add (and variants)
* [9001] Add in-place addition, subtration, division and multiplication
* [9001] Remove use of R's `runif()`
* [9001] Remove support for integer vectors and character vectors
* [9001] switch from `pryr::address()` to `rlang::obj_address()`
* [9000] Update package infrastructure

# insitu 0.1.3

* Feature: Using xoshirto256++ on windows, and the faster lehmer64() elsewhere.
    * the actual RNGs are about the same speed, but uint128_t support means
    we can use the much faster method for random integers on an interval
    https://lemire.me/blog/2019/06/06/nearly-divisionless-random-integer-generation-on-various-systems/
* re-introduces `ins_shuffle()`

# insitu 0.1.2

* Bug fix: using xoshiro256++ as the RNG as it does not rely on uint128_t and 
  pakcage now builds on windows.
* Vignette: References vignette to illustrate behaviour difference between copy-on-modify
  and modification in-situ

# insitu 0.1.0

* Initial release
