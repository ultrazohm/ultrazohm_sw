#ifndef UZ_PRNG_SQUARES_H
#define UZ_PRNG_SQUARES_H

#include <stdint.h>

typedef struct uz_prng_squares_t uz_prng_squares_t;

uz_prng_squares_t *uz_prng_squares_init(uint64_t seed);
uint32_t uz_prng_squares_get_uniform_uint32(uz_prng_squares_t *self);
float uz_prng_squares_get_uniform_float_zero_to_one(uz_prng_squares_t *self);

#endif // UZ_PRNG_SQUARES_H
