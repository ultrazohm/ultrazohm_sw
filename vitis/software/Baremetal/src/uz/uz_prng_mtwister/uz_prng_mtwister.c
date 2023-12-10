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
#include "../uz_global_configuration.h"
#if UZ_PRNG_MTWISTER_MAX_INSTANCES > 0U

#include <math.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng_mtwister.h"
#include "mt19937.h"

struct uz_prng_mtwister_t
{
    bool is_ready;
    struct _ORG_STATE state;
};

static uint32_t instance_counterrand = 0U;
static uz_prng_mtwister_t instancesrand[UZ_MTWISTER_MAX_INSTANCES] = {0};
static uz_prng_mtwister_t *uz_prng_mtwister_allocation(void);

static uz_prng_mtwister_t *uz_prng_mtwister_allocation(void)
{
    uz_assert(instance_counterrand < UZ_MTWISTER_MAX_INSTANCES);
    uz_prng_mtwister_t *self = &instancesrand[instance_counterrand];
    uz_assert_false(self->is_ready);
    instance_counterrand++;
    self->is_ready = true;
    return (self);
}

uz_prng_mtwister_t *uz_prng_mtwister_init(uint32_t random_seed)
{
    uz_prng_mtwister_t *self = uz_prng_mtwister_allocation();
    uz_prng_mtwister_reset(self, random_seed);
    return (self);
}

void uz_prng_mtwister_reset(uz_prng_mtwister_t *self, uint32_t random_seed)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    _sgenrand_dc(&self->state, random_seed);
}

uint32_t uz_prng_mtwister_get_uniform_uint32(uz_prng_mtwister_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return _genrand_dc(&self->state);
}

#endif // UZ_MTWISTER_H