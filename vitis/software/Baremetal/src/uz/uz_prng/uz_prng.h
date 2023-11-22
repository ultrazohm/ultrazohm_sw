#ifndef UZ_PRNG_H
#define UZ_PRNG_H

#include <stdint.h>
#include <stdbool.h>

typedef struct uz_prng_t uz_prng_t;

enum uz_prng_generator
{
    uz_prng_generator_squares,
    uz_prng_generator_mtwister,
    uz_prng_generator_pcg,
    uz_prng_generator_xoshiro,
    uz_prng_generator_halton,
};

uz_prng_t *uz_prng_init(enum uz_prng_generator generator, uint64_t seed);

uint32_t uz_prng_get_uniform_uint32_zero_to_uint32_max(uz_prng_t *self);
uint32_t uz_prng_get_uniform_uint32_zero_to_max(uz_prng_t *self, uint32_t max_range);
uint32_t uz_prng_get_uniform_uint32_zero_to_max_unbiased(uz_prng_t *self, uint32_t range);

bool uz_prng_get_uniform_bool(uz_prng_t *self);

float uz_prng_get_uniform_float_zero_to_one(uz_prng_t *self);
float uz_prng_get_uniform_float_min_to_max(uz_prng_t *self, float min, float max);

#endif // UZ_PRNG_H
