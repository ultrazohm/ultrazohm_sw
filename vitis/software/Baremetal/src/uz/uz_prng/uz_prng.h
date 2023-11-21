#ifndef UZ_PRNG_H
#define UZ_PRNG_H

#include <stdint.h>

float uz_prng_get_uniform_float_zero_to_one(uint32_t random_number);

uint32_t uz_prng_bounded_rand_multiply_bias(uint32_t unbound_rng, uint32_t range);

#endif // UZ_PRNG_H
