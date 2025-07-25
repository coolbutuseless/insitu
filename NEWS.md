
# insitu 0.1.3.9023

* [9023] Add `br_replace()`  2025-06-29
* [9022] fix some build errors
* [9021] Add `br_round_fast()` which is 10x faster than `br_round()`
* [9020] Expose `is_altrep()`, `is_mutable()` and `get_refcnt()`
* [9019] `tf2_apply()` and `tf3_apply()` now work on data.frames.
* [9018] get/set rows/cols from matrices
* [9017] add `br_roll()` and `br_mat_roll()`. Game-of-life example.
* [9017] Added 2D transforms
* [9016] `br_copy_if()` replaced with binaryop `br_assign()`
* [9016] `br_zero()` refactored to become a standard unaryop
* [9015] Global dispatch for unary/binary ops using array of func pointers
* [9014] Support for matrix arg to unary ops
* [9013] `where` and `idx` for conditional unary ops. Initial attempt at
         conditional binary ops
* [9012] 'where' conditional for unary ops
* [9011]3D transformation matrices
* [9010] Reintroduce specialised methods for `asq` and `bsq` in matrix multiplication
* [9009] Add `br_mat_transpose()`
* [9009] Add `R_NO_REMAP`
* [9009] Refactor & add tests for matrix operations.
* [9008] Add mat-mat and mat-vec multiplication.
* [9007] changed function prefix from `ins_` to `br_`
* [9007] changed helper from `insitu` to `by_reference`
* [9007] `br_mat_dist2()`, `br_mat_dist3()`, `br_mat_hypot2()`, `br_mat_hypot3()`
* [9006] `br_copy_if()`
* [9006] `br_is_na()`
* [9006] `br_copy()` replaces old `br_copy()`, `br_copy_from()`, 
         `br_replace()` and `br_fill()`
* [9005] Including `insitu` helper for use with `with()`
* [9004] Use math.h fma() instead of rolling my own
* [9004] nearly full complement of unary and binary math ops
* [9003] add `br_copy()`
* [9002] Use prefix `br_`
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
* re-introduces `br_shuffle()`

# insitu 0.1.2

* Bug fix: using xoshiro256++ as the RNG as it does not rely on uint128_t and 
  pakcage now builds on windows.
* Vignette: References vignette to illustrate behaviour difference between copy-on-modify
  and modification *by-reference*

# insitu 0.1.0

* Initial release
