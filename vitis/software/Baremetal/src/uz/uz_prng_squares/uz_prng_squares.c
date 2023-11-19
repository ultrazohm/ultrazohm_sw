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
#include "uz_prng_squares.h"

#include "../uz_global_configuration.h"
#if UZ_PRNG_SQUARES_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng_squares.h"

uint64_t default_keys[30] = {
#include "uz_prng_squares_keys.h"
};

struct uz_prng_squares_t
{
    bool is_ready;
    uint64_t key;
    uint64_t counter;
};

static uint32_t instance_counter = 0U;
static uz_prng_squares_t instances[UZ_PRNG_SQUARES_MAX_INSTANCES] = {0};

static uint32_t uz_prng_squares32_uniform_uint32(uint64_t ctr, uint64_t key);

static uz_prng_squares_t *uz_prng_squares_allocation(void);

static uz_prng_squares_t *uz_prng_squares_allocation(void)
{
    uz_assert(instance_counter < UZ_PRNG_SQUARES_MAX_INSTANCES);
    uz_prng_squares_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prng_squares_t *uz_prng_squares_init(uint64_t seed)
{
    uz_prng_squares_t *self = uz_prng_squares_allocation();

    if (seed < 30U)
    {
        self->key = default_keys[seed];
    }
    else
    {
        self->key = seed;
    }

    self->counter = 0U;
    return (self);
}

void uz_prng_squares_reset_counter(uz_prng_squares_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->counter = 0U;
}

uint32_t uz_prng_squares_get_uniform_uint32(uz_prng_squares_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->counter++;
    uint32_t random_value = uz_prng_squares32_uniform_uint32(self->counter, self->key);
    return random_value;
}

static uint32_t uz_prng_squares32_uniform_uint32(uint64_t ctr, uint64_t key)
{
    uint64_t y = ctr * key;
    uint64_t x = ctr * key;
    uint64_t z = y + key;
    // Calculations and bit shifting according to paper https://arxiv.org/pdf/2004.06278.pdf
    // Code adjusted to fit coding rules as good as possible, bitshift and bitwise operations are required.
    x = (x * x) + y;
    x = (x >> 32U) | (x << 32U);
    x = (x * x) + z;
    x = (x >> 32U) | (x << 32U);
    x = (x * x) + y;
    x = (x >> 32U) | (x << 32U);
    x = ((x * x + z) >> 32U);
    return (uint32_t)x;
}

#endif