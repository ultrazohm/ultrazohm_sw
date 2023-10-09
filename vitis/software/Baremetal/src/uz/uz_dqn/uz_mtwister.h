#ifndef UZ_MTWISTER_H
#define UZ_MTWISTER_H

#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdint.h>


typedef struct uz_mtwister_t uz_mtwister_t;

enum mtwister_rng_type
{
    mtwister_uniform_distribution,
    mtwister_normal_distribution
};

struct uz_mtwister_config{
    uint32_t seed;
    enum mtwister_rng_type distribution;
    float mean;
    float std;
};

uz_mtwister_t *uz_mtwister_init(struct uz_mtwister_config cfg);
void uz_mtwister_set_mean(uz_mtwister_t *self, float mean);
void uz_mtwister_set_standard_deviation(uz_mtwister_t *self,float standard_deviation);

float uz_mtwister_random_float_uniform(uz_mtwister_t *self);
uint32_t uz_mtwister_generate_random_uint32(uz_mtwister_t *self, uint32_t max);

void uz_mtwister_generate_random_uint32_array(uz_mtwister_t *self, uint32_t *array, uint32_t size, float max_val);


uint32_t uz_mtwister_generate_random_zero_or_one_uint32(uz_mtwister_t *self);
uint32_t uz_mtwister_generate_random_zero_to_max_uint32(uz_mtwister_t *self, uint32_t max);


    float uz_generate_random_number(uz_mtwister_t *self);
float uz_random_box_mueller(uz_mtwister_t *self, float mean, float std);
    void polar_box_muller(float *retval, uint32_t range);
#endif // UZ_DQN_H