/* An implementation of the MT19937 Algorithm for the Mersenne Twister
 * by Evan Sultanik.  Based upon the pseudocode in: M. Matsumoto and
 * T. Nishimura, "Mersenne Twister: A 623-dimensionally
 * equidistributed uniform pseudorandom number generator," ACM
 * Transactions on Modeling and Computer Simulation Vol. 8, No. 1,
 * January pp.3-30 1998.
 *
 * http://www.sultanik.com/Mersenne_twister
 * https://github.com/ESultanik/mtwister/tree/master
 */
#include "../uz_global_configuration.h"
#if UZ_MTWISTER_MAX_INSTANCES > 0U

#define STATE_VECTOR_LENGTH 624
#define STATE_VECTOR_M 397 /* changes to STATE_VECTOR_LENGTH also require changes to this */

#define UPPER_MASK 0x80000000
#define LOWER_MASK 0x7fffffff
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#include "uz_mtwister.h"
#include <math.h>

struct uz_mtwister_t
{
  bool is_ready;
  uint32_t seed;
  uint64_t mt[STATE_VECTOR_LENGTH];
  int index;
  uint64_t mag[2U];
  float box_mueller_cache;
};

static uint64_t genRandLong(uz_mtwister_t *self);
static double genRand(uz_mtwister_t *rand);
static float genRand_float(uz_mtwister_t *rand);

static uint32_t instance_counterrand = 0U;
static uz_mtwister_t instancesrand[UZ_MTWISTER_MAX_INSTANCES] = {0};
static uz_mtwister_t *uz_mtwister_allocation(void);

static uz_mtwister_t *uz_mtwister_allocation(void)
{
  uz_assert(instance_counterrand < UZ_MTWISTER_MAX_INSTANCES);
  uz_mtwister_t *self = &instancesrand[instance_counterrand];
  uz_assert_false(self->is_ready);
  instance_counterrand++;
  self->is_ready = true;
  return (self);
}

inline static void m_seedRand(uz_mtwister_t *self, unsigned long seed);

// Function to initialize a random_number instance with a given config
uz_mtwister_t *uz_mtwister_init(uint32_t random_seed)
{
  uz_mtwister_t *self = uz_mtwister_allocation();
  self->seed = random_seed;
  m_seedRand(self, self->seed);
  self->mag[0] = 0x0;
  self->mag[1] = 0x9908b0df; /* self->mag[x] = x * 0x9908b0df for x = 0,1 */
  self->box_mueller_cache=0.0f;
   return (self);
}

inline static void m_seedRand(uz_mtwister_t *self, unsigned long seed)
{
  /* set initial seeds to mt[STATE_VECTOR_LENGTH] using the generator
   * from Line 25 of Table 1 in: Donald Knuth, "The Art of Computer
   * Programming," Vol. 2 (2nd Ed.) pp.102.
   */
  self->mt[0] = seed & 0xffffffff;
  for (self->index = 1; self->index < STATE_VECTOR_LENGTH; self->index++)
  {
    self->mt[self->index] = (6069 * self->mt[self->index - 1]) & 0xffffffff;
  }
}


/**
 * Generates a pseudo-randomly generated long.
 */
static uint64_t genRandLong(uz_mtwister_t *self)
{
  uint64_t y=0;
  if (self->index >= STATE_VECTOR_LENGTH || self->index < 0)
  {
    /* generate STATE_VECTOR_LENGTH words at a time */
    int32_t kk=0;
    if (self->index >= STATE_VECTOR_LENGTH + 1 || self->index < 0)
    {
      m_seedRand(self, 4357);
    }
    for (kk = 0; kk < STATE_VECTOR_LENGTH - STATE_VECTOR_M; kk++)
    {
      y = (self->mt[kk] & UPPER_MASK) | (self->mt[kk + 1] & LOWER_MASK);
      self->mt[kk] = self->mt[kk + STATE_VECTOR_M] ^ (y >> 1) ^ self->mag[y & 0x1];
    }
    for (; kk < STATE_VECTOR_LENGTH - 1; kk++)
    {
      y = (self->mt[kk] & UPPER_MASK) | (self->mt[kk + 1] & LOWER_MASK);
      self->mt[kk] = self->mt[kk + (STATE_VECTOR_M - STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ self->mag[y & 0x1];
    }
    y = (self->mt[STATE_VECTOR_LENGTH - 1] & UPPER_MASK) | (self->mt[0] & LOWER_MASK);
    self->mt[STATE_VECTOR_LENGTH - 1] = self->mt[STATE_VECTOR_M - 1] ^ (y >> 1) ^ self->mag[y & 0x1];
    self->index = 0;
  }
  y = self->mt[self->index++];
  y ^= (y >> 11);
  y ^= (y << 7) & TEMPERING_MASK_B;
  y ^= (y << 15) & TEMPERING_MASK_C;
  y ^= (y >> 18);
  return y;
}

static double genRand(uz_mtwister_t *rand)
{
  return ((double)genRandLong(rand) / (uint64_t)0xffffffff);
}

static float genRand_float(uz_mtwister_t *rand)
{
  return ((float)genRandLong(rand) / (float)0xffffffff);
}

float uz_mtwister_random_float_uniform(uz_mtwister_t *self)
{
  return ((float)genRandLong(self) / (float)0xffffffff);
}

uint32_t uz_mtwister_generate_random_zero_or_one_uint32(uz_mtwister_t *self)
{
  uz_assert_not_NULL(self);
  uint32_t y = (uint32_t)(genRand_float(self) * (2.0f));
  return y;
}

uint32_t uz_mtwister_generate_random_zero_to_max_uint32(uz_mtwister_t *self, uint32_t max)
{
  uint32_t y = (uint32_t)(genRand_float(self) * (float)(max + 1));
  return y;
}

uint32_t uz_mtwister_generate_random_uint32(uz_mtwister_t *self, uint32_t max)
{
  uz_assert_not_NULL(self);
  return uz_mtwister_generate_random_zero_to_max_uint32(self, max);
}

void uz_mtwister_generate_random_uint32_array(uz_mtwister_t *self, uint32_t *array, uint32_t size, float max_val)
{
  uz_assert_not_NULL(self);
  uz_assert_not_NULL(array);
  for (uint32_t i = 0; i < size; i++)
  {
    array[i] = uz_mtwister_generate_random_zero_to_max_uint32(self, (uint32_t)max_val);
  }
}

float uz_mtwister_random_float_normal(uz_mtwister_t *self, float mean, float std)
{
  float x=0.0f;
  float y=0.0f;
  float r=0.0f;
  float res=0.0f;

  if (self->box_mueller_cache == 0.0f)
  {
    do
    {
      x = (2.0f * genRand_float(self)) - 1.0f;
      y = (2.0f * genRand_float(self)) - 1.0f;
      r = x * x + y * y;
    } while (r == 0.0f || r > 1.0f);

    float d = sqrtf(-2.0f * logf(r) / r);
    float n1 = x * d;
    float n2 = y * d;
    res = n1 * std + mean;
    self->box_mueller_cache = n2;
  }
  else
  {
    res = self->box_mueller_cache * std + mean;
    self->box_mueller_cache = 0.0f;
  }
  return res;
}

#endif // UZ_MTWISTER_H