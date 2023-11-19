#ifndef UZ_PRNG_PCG_H
#define UZ_PRNG_PCG_H

#include <stdint.h>

typedef struct uz_prng_pcg_t uz_prng_pcg_t;

uz_prng_pcg_t *uz_prng_pcg_init(uint64_t seed);
uint32_t uz_prng_pcg_get_uniform_uint32(uz_prng_pcg_t *self);

#endif // UZ_PRNG_PCG_H
