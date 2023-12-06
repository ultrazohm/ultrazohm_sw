#include "uz_prng_xoshiro.h"

#include "../uz_global_configuration.h"
#if UZ_PRNG_XOSHIRO_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng_xoshiro.h"
#include "splitmix64.h"
#include "xoshiro128plusplus.h"

struct uz_prng_xoshiro_t
{
    bool is_ready;
    uint32_t state[4];
};

static uint32_t instance_counter = 0U;
static uz_prng_xoshiro_t instances[UZ_PRNG_XOSHIRO_MAX_INSTANCES] = {0};

static uz_prng_xoshiro_t *uz_prng_xoshiro_allocation(void);

static uz_prng_xoshiro_t *uz_prng_xoshiro_allocation(void)
{
    uz_assert(instance_counter < UZ_PRNG_XOSHIRO_MAX_INSTANCES);
    uz_prng_xoshiro_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prng_xoshiro_t *uz_prng_xoshiro_init(uint64_t seed)
{
    uz_prng_xoshiro_t *self = uz_prng_xoshiro_allocation();
    uz_prng_xoshiro_reset(self, seed);
        return (self);
    }

void uz_prng_xoshiro_reset(uz_prng_xoshiro_t* self, uint64_t seed){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uint64_t state_0 = splitmix64_get_random_uint64(seed);    // Shuffles the given seed as recommended by xoshiro128++ authors
    uint64_t state_1 = splitmix64_get_random_uint64(state_0); // Shuffles the given seed as recommended by xoshiro128++ authors
    uint64_t state_2 = splitmix64_get_random_uint64(state_1); // Shuffles the given seed as recommended by xoshiro128++ authors
    uint64_t state_3 = splitmix64_get_random_uint64(state_2); // Shuffles the given seed as recommended by xoshiro128++ authors

    self->state[1] = (uint32_t)state_0;
    self->state[1] = (uint32_t)state_1;
    self->state[2] = (uint32_t)state_2;
    self->state[3] = (uint32_t)state_3;
}

uint32_t uz_prng_xoshiro_get_uniform_uint32(uz_prng_xoshiro_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
   return xoshiro128plusplus_get_uint32(self->state);
}

#endif