/* An implementation of the MT19937 Algorithm for the Mersenne Twister
 * by Evan Sultanik.  Based upon the pseudocode in: M. Matsumoto and
 * T. Nishimura, "Mersenne Twister: A 623-dimensionally
 * equidistributed uniform pseudorandom number generator," ACM
 * Transactions on Modeling and Computer Simulation Vol. 8, No. 1,
 * January pp.3-30 1998.
 *
 * http://www.sultanik.com/Mersenne_twister
 */
#include "../uz_global_configuration.h"
#if UZ_DQN_RAND_MAX_INSTANCES > 0U

#define UPPER_MASK		0x80000000
#define LOWER_MASK		0x7fffffff
#define TEMPERING_MASK_B	0x9d2c5680
#define TEMPERING_MASK_C	0xefc60000
#include "uz_mtwister.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static uint32_t instance_counterrand = 0U;
static uz_mtwister_t instancesrand[UZ_DQN_RAND_MAX_INSTANCES] = {0};
static uz_mtwister_t* uz_mtwister_allocation(void);

static uz_mtwister_t* uz_mtwister_allocation(void){
    uz_assert(instance_counterrand < UZ_DQN_RAND_MAX_INSTANCES);
    uz_mtwister_t* self = &instancesrand[instance_counterrand];
    uz_assert_false(self->is_ready);
    instance_counterrand++;
    self->is_ready = true;
    return (self);
}

// Function to initialize a random_number instance with a given config
uz_mtwister_t *init_mtwister(struct uz_mtwister_config cfg) {
    uz_mtwister_t *self = uz_mtwister_allocation();
    self->seed = cfg.seed;
    self->seedRand = seedRand(self->seed);
    self->distribution = cfg.distribution;
    self->mean = 0.0f;
    self->std = 0.5f;
    self->limit = 1;
    return (self);
}


float uz_generate_random_number(uz_mtwister_t *self){
  uz_assert_not_NULL(self);
  float randomsample = 0.0f;
  switch (self->distribution)
  {
  case uniform_distribution:
    randomsample = genRand_float(&self->seedRand);
    break;
  case normal_distribution:
    randomsample = uz_random_box_mueller(&self->seedRand,self->mean,self->std);
    break;
  default:
    break;
  }
  return randomsample;
}

inline static void m_seedRand(MTRand* rand, unsigned long seed) {
  /* set initial seeds to mt[STATE_VECTOR_LENGTH] using the generator
   * from Line 25 of Table 1 in: Donald Knuth, "The Art of Computer
   * Programming," Vol. 2 (2nd Ed.) pp.102.
   */
  rand->mt[0] = seed & 0xffffffff;
  for(rand->index=1; rand->index<STATE_VECTOR_LENGTH; rand->index++) {
    rand->mt[rand->index] = (6069 * rand->mt[rand->index-1]) & 0xffffffff;
  }
}

/**
* Creates a new random number generator from a given seed.
*/
MTRand seedRand(unsigned long seed) {
  MTRand rand;
  m_seedRand(&rand, seed);
  return rand;
}

/**
 * Generates a pseudo-randomly generated long.
 */
unsigned long genRandLong(MTRand* rand) {

  unsigned long y;
  static unsigned long mag[2] = {0x0, 0x9908b0df}; /* mag[x] = x * 0x9908b0df for x = 0,1 */
  if(rand->index >= STATE_VECTOR_LENGTH || rand->index < 0) {
    /* generate STATE_VECTOR_LENGTH words at a time */
    int kk;
    if(rand->index >= STATE_VECTOR_LENGTH+1 || rand->index < 0) {
      m_seedRand(rand, 4357);
    }
    for(kk=0; kk<STATE_VECTOR_LENGTH-STATE_VECTOR_M; kk++) {
      y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
      rand->mt[kk] = rand->mt[kk+STATE_VECTOR_M] ^ (y >> 1) ^ mag[y & 0x1];
    }
    for(; kk<STATE_VECTOR_LENGTH-1; kk++) {
      y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
      rand->mt[kk] = rand->mt[kk+(STATE_VECTOR_M-STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ mag[y & 0x1];
    }
    y = (rand->mt[STATE_VECTOR_LENGTH-1] & UPPER_MASK) | (rand->mt[0] & LOWER_MASK);
    rand->mt[STATE_VECTOR_LENGTH-1] = rand->mt[STATE_VECTOR_M-1] ^ (y >> 1) ^ mag[y & 0x1];
    rand->index = 0;
  }
  y = rand->mt[rand->index++];
  y ^= (y >> 11);
  y ^= (y << 7) & TEMPERING_MASK_B;
  y ^= (y << 15) & TEMPERING_MASK_C;
  y ^= (y >> 18);
  return y;
}

double genRand(MTRand* rand) {
  return((double)genRandLong(rand) / (unsigned long)0xffffffff);
}
float genRand_float(MTRand* rand) {
return((float)genRandLong(rand) / (float)0xffffffff);
}

uint32_t genRand_zero_one(MTRand* rand) {
  uint32_t y = (uint32_t) (genRand_float(rand)*(2.0f));
return y;
}

uint32_t genRand_uint32_t(MTRand* rand, uint32_t max) {
  uint32_t y = (uint32_t) (genRand_float(rand)*(float)(max+1));
return y;
}

void genRand_uint32_t_array(uint32_t *array, MTRand* rand, uint32_t size, float min_val, float max_val)
{
uz_assert_not_NULL(array);
uz_assert(min_val<max_val);
for (uint32_t i = 0; i < size; i++) {
    //array[i] = random_number((int)min_val,(int)max_val); test mit rand funktioniert auch nicht!s
    array[i] = genRand_uint32_t(rand, (uint32_t)max_val);
    //array[i] = (uint32_t) (min_val + (genRand_float(rand)*(max_val - min_val + 1)));
}  
}

float uz_random_box_mueller(MTRand* seed,float mean, float std){
    static float cached = 0.0f;
    float x, y, r, res;

    if (cached == 0.0f) {
        do {
            x = (2.0f * genRand_float(seed)) - 1.0f;
            y = (2.0f * genRand_float(seed)) - 1.0f;
            r = x * x + y * y;
        } while (r == 0.0f || r > 1.0f);

        float d = sqrtf(-2.0f * logf(r) / r);
        float n1 = x * d;
        float n2 = y * d;
        res = n1 * std + mean;
        cached = n2;
    }
    else {
        res = cached * std + mean;
        cached = 0.0f;
    }
return res;
}

void export_histogram(float *array,uint32_t size){

FILE* file1 = fopen("test/uz/uz_dqn/matlab/randboxmueller.csv", "w");
if (file1 != NULL)
{
for (u_int32_t i = 0; i < size; i++) {
        fprintf(file1, "%d,%.4f\n", i, (double)array[i]);
}
}
}

uint32_t random_number(int min_num, int max_num)
    {
        int result = 0, low_num = 0, hi_num = 0;

        if (min_num < max_num)
        {
            low_num = min_num;
            hi_num = max_num + 1; // include max_num in output
        } else {
            low_num = max_num + 1; // include max_num in output
            hi_num = min_num;
        }

        srand(time(NULL));
        result = (rand() % (hi_num - low_num)) + low_num;
        uint32_t randnumb = (uint32_t)result;
        return randnumb;
    }
#endif // UZ_MTWISTER_H