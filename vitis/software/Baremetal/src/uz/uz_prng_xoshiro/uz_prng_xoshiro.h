#ifndef UZ_PRNG_XOSHIRO_H
#define UZ_PRNG_XOSHIRO_H

#include <stdint.h>

typedef struct uz_prng_xoshiro_t uz_prng_xoshiro_t;

uz_prng_xoshiro_t *uz_prng_xoshiro_init(uint64_t seed);
uint32_t uz_prng_xoshiro_get_uniform_uint32(uz_prng_xoshiro_t *self);

#endif // UZ_PRNG_XOSHIRO_H
