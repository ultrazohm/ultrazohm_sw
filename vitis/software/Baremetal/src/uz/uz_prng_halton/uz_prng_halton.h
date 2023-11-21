#ifndef UZ_PRNG_HALTON_H
#define UZ_PRNG_HALTON_H

#include <stdint.h>
#include "../uz_array/uz_array.h"

typedef struct uz_prng_halton_t uz_prng_halton_t;

uz_prng_halton_t *uz_prng_halton_init(uint32_t base);
float uz_prng_halton_get_uniform_float(uz_prng_halton_t *self);
void uz_prng_halton_get_uniform_float_2d(uz_prng_halton_t *self, float *x, float *y);

#endif // UZ_PRNG_HALTON_H
