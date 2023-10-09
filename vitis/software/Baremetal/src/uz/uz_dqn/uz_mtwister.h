#ifndef UZ_MTWISTER_H
#define UZ_MTWISTER_H

#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdint.h>


typedef struct uz_mtwister_t uz_mtwister_t;


uz_mtwister_t *uz_mtwister_init(uint32_t random_seed);


float uz_mtwister_random_float_uniform(uz_mtwister_t *self);
uint32_t uz_mtwister_generate_random_uint32(uz_mtwister_t *self, uint32_t max);

void uz_mtwister_generate_random_uint32_array(uz_mtwister_t *self, uint32_t *array, uint32_t size, float max_val);

uint32_t uz_mtwister_generate_random_zero_or_one_uint32(uz_mtwister_t *self);
uint32_t uz_mtwister_generate_random_zero_to_max_uint32(uz_mtwister_t *self, uint32_t max);

float uz_mtwister_random_float_normal(uz_mtwister_t *self, float mean, float std);

#endif // UZ_DQN_H