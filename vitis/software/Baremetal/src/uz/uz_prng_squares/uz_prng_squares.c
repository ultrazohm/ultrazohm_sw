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

// Default keys are taken from the paper authors code at https://squaresrng.wixsite.com/rand
uint64_t default_keys[30] = {
    0xc8e4fd154ce32f6d,
    0xfcbd6e154bf53ed9,
    0xea6342c76bf95d47,
    0xfb9e125878fa6cb3,
    0xa1ed294ba7fe8b31,
    0xcf29ba8dc5f1a98d,
    0x815a7d4ed4e3b7f9,
    0x163acbf213f5d867,
    0x674e2d1542f9e6d3,
    0xebc9672872ecf651,
    0xec13a6976ecf14ad,
    0x42c86e3a9de3542b,
    0x5489de2cbce65297,
    0x49bc37fdcad971f3,
    0xd5b4213fe7db8f61,
    0xbf785e3215ac7ebd,
    0x46be329546e1ad3b,
    0x8b7ef19654e3dca7,
    0x1d7683c983d7eb15,
    0x3724b1c872d9fa81,
    0x2af73db87fab18ed,
    0xa185f4cbadcf285b,
    0x53d684c1fbd246c7,
    0x35fda1821cd68735,
    0xfd3791543bd985a1,
    0x7f59c4b657cb941f,
    0x19f3e5b765cea27b,
    0xf6235eca95b2c1e7,
    0x9d827c5ba2b3df45,
    0x8a149e2dc2a6feb1};

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

uz_prng_squares_t *uz_prng_squares_init(uint64_t key)
{
    uz_prng_squares_t *self = uz_prng_squares_allocation();

    if (key < 30U)
    {
        self->key = default_keys[key];
    }
    else
    {
        self->key = key;
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
    x = (((x * x) + z) >> 32U);
    return (uint32_t)x;
}



#endif