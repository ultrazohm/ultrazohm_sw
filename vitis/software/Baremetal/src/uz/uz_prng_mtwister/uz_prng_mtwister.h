#ifndef UZ_PRNG_MTWISTER_H
#define UZ_PRNG_MTWISTER_H

#include <stdint.h>

typedef struct uz_prng_mtwister_t uz_prng_mtwister_t;

uz_prng_mtwister_t *uz_prng_mtwister_init(uint32_t random_seed);
uint32_t uz_prng_mtwister_get_uniform_uint32(uz_prng_mtwister_t *self);

#endif // UZ_PRNG_MTWISTER_H
