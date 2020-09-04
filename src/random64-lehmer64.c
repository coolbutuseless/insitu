
#ifndef _WIN32

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
__uint128_t g_lehmer64_state;

int random64_has_been_initialised = 0;

uint64_t lehmer64() {
  g_lehmer64_state *= 0xda942042e4dd58b5;
  return g_lehmer64_state >> 64;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Random-numbers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void random64_set_seed() {

  //Rprintf("Seeding lehmer64\n");

  GetRNGstate();
  // Seed lehmer64's seed using 4 calls to R's built-in RNG
  g_lehmer64_state = unif_rand() * INT_MAX +
    ((__uint128_t)(unif_rand() * INT_MAX) << 32) +
    ((__uint128_t)(unif_rand() * INT_MAX) << 64) +
    ((__uint128_t)(unif_rand() * INT_MAX) << 96);

  PutRNGstate();

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// https://lemire.me/blog/2019/06/06/nearly-divisionless-random-integer-generation-on-various-systems/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint64_t random_integer_on_interval ( uint64_t s ) {
  uint64_t x = lehmer64 () ;
  __uint128_t m = ( __uint128_t ) x * ( __uint128_t ) s;
  uint64_t l = ( uint64_t ) m;
  if (l < s) {
    uint64_t t = -s % s;
    while (l < t) {
      x = lehmer64 () ;
      m = ( __uint128_t ) x * ( __uint128_t ) s;
      l = ( uint64_t ) m;
    }
  }
  return m >> 64;
}




void runif_random64_(double *x, int n, double dmin, double dmax) {

  double drange = dmax - dmin;

  for (int i = 0; i < n; ++i) {
    g_lehmer64_state *= 0xda942042e4dd58b5;
    uint64_t result = g_lehmer64_state >> 64;
    *x++ = (result >> 11) * 0x1.0p-53 * drange + dmin;
  }

}


#endif

