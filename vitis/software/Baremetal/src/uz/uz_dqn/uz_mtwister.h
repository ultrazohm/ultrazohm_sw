#ifndef UZ_MTWISTER_H
#define UZ_MTWISTER_H

#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>

#define STATE_VECTOR_LENGTH 624
#define STATE_VECTOR_M      397 /* changes to STATE_VECTOR_LENGTH also require changes to this */

typedef struct uz_mtwister_t uz_mtwister_t;
typedef struct tagMTRand {
  unsigned long mt[STATE_VECTOR_LENGTH];
  int index;
} MTRand;
// Enum to define random number generator types
enum rng_type{
    uniform_distribution,
    normal_distribution
};
struct uz_mtwister_t{
    bool is_ready;
    uint32_t seed;
    MTRand seedRand;
    int limit; // if needed
    float mean;
    float std;
    enum rng_type distribution;
};


MTRand seedRand(unsigned long seed);
unsigned long genRandLong(MTRand* rand);
double genRand(MTRand* rand);
float genRand_float(MTRand* rand);
uint32_t genRand_zero_one(MTRand* rand);
uint32_t genRand_uint32_t(MTRand* rand, uint32_t max) ;
void genRand_uint32_t_array(uint32_t *array, MTRand* rand, uint32_t size, float min_val, float max_val);

struct uz_mtwister_config{
    uint32_t seed;
    enum rng_type distribution;
};
uz_mtwister_t *init_mtwister(struct uz_mtwister_config cfg);
float uz_generate_random_number(uz_mtwister_t *self);
float uz_random_box_mueller(MTRand* seed,float mean, float std);
void polar_box_muller(float *retval, uint32_t range);
void export_histogram(float *array,uint32_t size);
#endif // UZ_DQN_H