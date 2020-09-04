

#include <stdint.h>

extern int random64_has_been_initialised;
void random64_set_seed();
uint64_t random64(void);
uint64_t  random_integer_on_interval(uint64_t s);
void runif_random64_(double *x, int n, double dmin, double dmax);
