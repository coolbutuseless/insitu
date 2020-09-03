


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "rand-xoshiro256p.h"

/* This is xoshiro256+ 1.0, our best and fastest generator for floating-point
 numbers. We suggest to use its upper bits for floating-point
 generation, as it is slightly faster than xoshiro256++/xoshiro256**. It
 passes all tests we are aware of except for the lowest three bits,
 which might fail linearity tests (and just those), so if low linear
 complexity is not considered an issue (as it is usually the case) it
 can be used to generate 64-bit outputs, too.

 We suggest to use a sign test to extract a random Boolean value, and
 right shifts to extract subsets of bits.

 The state must be seeded so that it is not everywhere zero. If you have
 a 64-bit seed, we suggest to seed a splitmix64 generator and use its
 output to fill s. */


static inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PRNG State
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static uint64_t xoshiro256p_state[4];


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Original PRNG
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint64_t next_xoshiro256p(void) {
  const uint64_t result = rotl(xoshiro256p_state[0] + xoshiro256p_state[3], 23) + xoshiro256p_state[0];

  const uint64_t t = xoshiro256p_state[1] << 17;

  xoshiro256p_state[2] ^= xoshiro256p_state[0];
  xoshiro256p_state[3] ^= xoshiro256p_state[1];
  xoshiro256p_state[1] ^= xoshiro256p_state[2];
  xoshiro256p_state[0] ^= xoshiro256p_state[3];

  xoshiro256p_state[2] ^= t;

  xoshiro256p_state[3] = rotl(xoshiro256p_state[3], 45);

  return result;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Random-numbers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void xoshiro256p_set_seed() {

  GetRNGstate();
  // Seed RNG using calls to R's built-in RNG
  xoshiro256p_state[0] = unif_rand() * INT_MAX + ((uint64_t)(unif_rand() * INT_MAX) << 32);
  xoshiro256p_state[1] = unif_rand() * INT_MAX + ((uint64_t)(unif_rand() * INT_MAX) << 32);
  xoshiro256p_state[2] = unif_rand() * INT_MAX + ((uint64_t)(unif_rand() * INT_MAX) << 32);
  xoshiro256p_state[3] = unif_rand() * INT_MAX + ((uint64_t)(unif_rand() * INT_MAX) << 32);

  PutRNGstate();

}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// https://lemire.me/blog/2019/06/06/nearly-divisionless-random-integer-generation-on-various-systems/
// Java method: https://arxiv.org/pdf/1805.10941.pdf
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint64_t  random_integer_on_interval_java(uint64_t s) {
  uint64_t x = next_xoshiro256p();
  uint64_t r = x % s;

  while(x - r > UINT64_MAX - s + 1) {
    x = next_xoshiro256p();
    r = x % s;
  }
  return r;
}














