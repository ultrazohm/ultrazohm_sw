#include "uz_prng_pcg.h"
/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2023 Tobias Schindler
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/
/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For additional information about the PCG random number generation scheme,
 * including its license and other licensing options, visit
 *
 *       http://www.pcg-random.org
 */

/*
 * This code is derived from the full C implementation, which is in turn
 * derived from the canonical C++ PCG implementation. The C++ version
 * has many additional features and is preferable if you can use C++ in
 * your project.
 */

#include "../uz_global_configuration.h"
#if UZ_PRNG_PCG_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng_pcg.h"

// From original code
typedef struct pcg_state_setseq_64 pcg32_random_t;

struct pcg_state_setseq_64
{                   // Internals are *Private*.
    uint64_t state; // RNG state.  All values are possible.
    uint64_t inc;   // Controls which RNG sequence (stream) is
                    // selected. Must *always* be odd.
};

struct uz_prng_pcg_t
{
    bool is_ready;
    struct pcg_state_setseq_64 pcg_state;
};

static uint32_t instance_counter = 0U;
static uz_prng_pcg_t instances[UZ_PRNG_PCG_MAX_INSTANCES] = {0};

static uz_prng_pcg_t *uz_prng_pcg_allocation(void);
// Original functions from https://github.com/imneme/pcg-c-basic/blob/master/pcg_basic.c
static void pcg32_srandom_r(pcg32_random_t *rng, uint64_t initstate, uint64_t initseq);
static uint32_t pcg32_random_r(pcg32_random_t *rng);

static uz_prng_pcg_t *uz_prng_pcg_allocation(void)
{
    uz_assert(instance_counter < UZ_PRNG_PCG_MAX_INSTANCES);
    uz_prng_pcg_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prng_pcg_t *uz_prng_pcg_init(uint64_t seed)
{
    uz_prng_pcg_t *self = uz_prng_pcg_allocation();
    pcg32_srandom_r(&self->pcg_state, seed, 54U); // Sequence randomly set to 54 since this is done in https://github.com/imneme/pcg-c-basic/blob/master/pcg32-demo.c
    return (self);
}

uint32_t uz_prng_pcg_get_uniform_uint32(uz_prng_pcg_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return pcg32_random_r(&self->pcg_state);
}

void pcg32_srandom_r(pcg32_random_t *rng, uint64_t initstate, uint64_t initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
}

uint32_t pcg32_random_r(pcg32_random_t *rng)
{
    uint64_t oldstate = rng->state;
    rng->state = (oldstate * 6364136223846793005ULL) + rng->inc;
    uint32_t xorshifted =  (uint32_t)(((oldstate >> 18u) ^ oldstate) >> 27u);
    uint32_t rot = (uint32_t)(oldstate >> 59u);
    return (uint32_t)(xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

#endif