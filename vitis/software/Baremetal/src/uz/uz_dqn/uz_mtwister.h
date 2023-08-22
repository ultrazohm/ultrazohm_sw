#ifndef UZ_MTWISTER_H
#define UZ_MTWISTER_H

#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>

#define STATE_VECTOR_LENGTH 624
#define STATE_VECTOR_M      397 /* changes to STATE_VECTOR_LENGTH also require changes to this */

typedef struct uz_random_number_t uz_random_number_t;

typedef struct tagMTRand {
  unsigned long mt[STATE_VECTOR_LENGTH];
  int index;
} MTRand;

MTRand seedRand(unsigned long seed);
unsigned long genRandLong(MTRand* rand);
double genRand(MTRand* rand);
float genRand_float(MTRand* rand);
// Enum to define random number generator types
enum rng_type{
    Mersenne_Twister,
    multiFibonacci
};

struct uz_random_number_config{
    uint32_t seed;
    enum rng_type gen;
};
uz_random_number_t *init_random_number(struct uz_random_number_config cfg);
float uz_random_box_mueller(MTRand* seed,float mean, float std);
void polar_box_muller(float *retval, uint32_t range);
void export_histogram(float *array,uint32_t size);
#endif // UZ_DQN_H