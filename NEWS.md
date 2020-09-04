

# insitu 0.1.3

* Feature: Using xoshirto256++ on windows, and the faster lehmer64() elsewhere.
    * the actual RNGs are about the same speed, but uint128_t support means
    we can use the much faster method for random integers on an interval
    https://lemire.me/blog/2019/06/06/nearly-divisionless-random-integer-generation-on-various-systems/
* re-introduces `insitu_shuffle_fast()`

# insitu 0.1.2

* Bug fix: using xoshiro256++ as the RNG as it does not rely on uint128_t and 
  pakcage now builds on windows.
* Vignette: References vignette to illustrate behaviour difference between copy-on-modify
  and modification in-situ

# insitu 0.1.0

* Initial release
