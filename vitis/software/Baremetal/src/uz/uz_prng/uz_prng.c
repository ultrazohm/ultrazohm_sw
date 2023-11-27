

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
#if UZ_PRNG_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_prng.h"
#include "../uz_prng_squares/uz_prng_squares.h"
#include "../uz_prng_halton/uz_prng_halton.h"
#include "../uz_prng_mtwister/uz_prng_mtwister.h"
#include "../uz_prng_pcg/uz_prng_pcg.h"
#include "../uz_prng_xoshiro/uz_prng_xoshiro.h"

struct uz_prng_t
{
    bool is_ready;
    void *generator; // This points to an instance of uz_prng_squares/pca/etc. -> since these have different types, this is a pointer to void*
    enum uz_prng_generator generator_type;
    enum uz_prng_float_scale_method float_scale_method;
};

static uint32_t instance_counter = 0U;
static uz_prng_t instances[UZ_PRNG_MAX_INSTANCES] = {0};

static float uz_prng_scale_to_float_zero_to_one_divide(uint32_t random_number);
static float uz_prng_scale_to_float_zero_to_one_multiply(uint32_t random_number);
static float uz_prng_scale_to_float_zero_to_one_shift_multiply(uint32_t random_number);

static uz_prng_t *uz_prng_allocation(void);

static uz_prng_t *uz_prng_allocation(void)
{
    uz_assert(instance_counter < UZ_PRNG_MAX_INSTANCES);
    uz_prng_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_prng_t *uz_prng_init(enum uz_prng_generator generator, enum uz_prng_float_scale_method scale_method, uint64_t seed)
{
    uz_prng_t *self = uz_prng_allocation();
    self->generator_type = generator;
    self->float_scale_method = scale_method;
    switch (self->generator_type)
    {
    case uz_prng_generator_squares:
        self->generator = uz_prng_squares_init(seed);
        break;
    case uz_prng_generator_mtwister:
        uz_assert(seed <= UINT32_MAX); // Seed of init is always 64 since some generators require 64bit seed. Seed must fit uint32_t
        self->generator = uz_prng_mtwister_init((uint32_t)seed);
        break;
    case uz_prng_generator_halton:
        uz_assert(seed <= UINT32_MAX); // Seed of init is always 64 since some generators require 64bit seed. Seed must fit uint32_t
        self->generator = uz_prng_halton_init((uint32_t)seed);
        break;
    case uz_prng_generator_pcg:
        self->generator = uz_prng_pcg_init(seed);
        break;
    case uz_prng_generator_xoshiro:
        self->generator = uz_prng_xoshiro_init(seed);
        break;
    default:
        uz_assert(0); // No valid choice for generator type
        break;
    }

    return (self);
}

uint32_t uz_prng_get_uniform_uint32_zero_to_uint32_max(uz_prng_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uint32_t random_number = 0U;
    switch (self->generator_type)
    {
    case uz_prng_generator_squares:
        random_number = uz_prng_squares_get_uniform_uint32(self->generator);
        break;
    case uz_prng_generator_mtwister:
        random_number = uz_prng_mtwister_get_uniform_uint32(self->generator);
        break;
    case uz_prng_generator_halton:
        random_number = (uint32_t)((uz_prng_halton_get_uniform_float(self->generator) * (float)UINT32_MAX));
        break;
    case uz_prng_generator_pcg:
        random_number = uz_prng_pcg_get_uniform_uint32(self->generator);
        break;
    case uz_prng_generator_xoshiro:
        random_number = uz_prng_xoshiro_get_uniform_uint32(self->generator);
        break;
    default:
        uz_assert(0); // No valid choice for generator type
        break;
    }
    return random_number;
}

float uz_prng_get_uniform_float_zero_to_one(uz_prng_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float random_number = 0.0f;
    uint32_t random_uint = 0U;

    if (self->generator_type == uz_prng_generator_halton)
    {
        random_number = uz_prng_halton_get_uniform_float(self->generator);
    }
    else
    {
        random_uint = uz_prng_squares_get_uniform_uint32(self->generator);
        switch (self->float_scale_method)
        {
        case uz_prng_float_scale_fp_multiply:
            random_number = uz_prng_scale_to_float_zero_to_one_multiply(random_uint);
            break;
        case uz_prng_float_scale_fp_divide:
            random_number = uz_prng_scale_to_float_zero_to_one_divide(random_uint);
            break;
        case uz_prng_float_scale_fp_shift_multiply:
            random_number = uz_prng_scale_to_float_zero_to_one_shift_multiply(random_uint);
            break;
        default:
            uz_assert(0);
            break;
        }
    }
    return random_number;
}

bool uz_prng_get_uniform_bool(uz_prng_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    bool random_value = false;
    uint32_t determine_half = uz_prng_get_uniform_uint32_zero_to_uint32_max(self);
    if (determine_half > (UINT32_MAX / 2U))
    { // Might introduce bias?
        random_value = true;
    }
    return random_value;
}

float uz_prng_get_uniform_float_min_to_max(uz_prng_t *self, float min, float max)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Generate values in the open interval (a,b)
    // r = a + (b - a)*random_zero_to_one
    uz_assert(min > max);
    return (min + (max - min) * uz_prng_get_uniform_float_zero_to_one(self));
}

uint32_t uz_prng_get_uniform_uint32_zero_to_range(uz_prng_t *self, uint32_t range)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uint32_t bounded = uz_prng_get_uniform_uint32_zero_to_range_int_mult(self, range);
    return bounded;
}

// Functions that scale uint32_t to float [0,1)

static float uz_prng_scale_to_float_zero_to_one_divide(uint32_t random_number)
{
    // Paper author code of squares (https://arxiv.org/pdf/2004.06278.pdf) uses double and no cast to scale
    // unclear why this works in the example code provided
    // works with cast as it forces floating point division.
    // Additionally, paper scales by 4294967296 instead of 0xffffffffU (which is uint32_t max).
    float random_float = (float)(random_number) / (float)UINT32_MAX;
    return random_float;
}

static float uz_prng_scale_to_float_zero_to_one_multiply(uint32_t random_number)
{
    // 0x1.0p-32 is a floating point constant for 2-32 that converts a integer value in the range [0..UINT32_MAX)
    // into a float in the unit interval;
    return ((float)0x1.0p-32) * (float)random_number;
}

static float uz_prng_scale_to_float_zero_to_one_shift_multiply(uint32_t random_number)
{
    // https://prng.di.unimi.it/ section generating uniform doubles in the unit interval, adapted to single precision
    return (((random_number >> 8U) * (float)0x1.0p-24));
}

// Functions that scale float 0..uint32_max to [0,max_range), see https://www.pcg-random.org/posts/bounded-rands.html
/*
 * A C++ implementation methods and benchmarks for random numbers in a range
 * (32-bit version)
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Melissa E. O'Neill
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

uint32_t uz_prng_get_uniform_uint32_zero_to_range_unbiased(uz_prng_t *self, uint32_t range)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // This is USE_DEBIASED_INT_MULT of https://github.com/imneme/bounded-rands/blob/3d71f53c975b1e5b29f2f3b05a74e26dab9c3d84/bounded32.cpp#L236
    uint32_t t = (-range) % range;
    uint32_t l = 0U;
    uint64_t m = 0U;
    do
    {
        uint32_t x = uz_prng_get_uniform_uint32_zero_to_uint32_max(self);
        m = (uint64_t)(x) * (uint64_t)(range);
        l = (uint32_t)(m);
    } while (l < t);
    return (uint32_t)(m >> 32U);
}

uint32_t uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(uz_prng_t *self, uint32_t range)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // This is USE_DEBIASED_INT_MULT_TOPT_MOPT of https://github.com/imneme/bounded-rands/blob/3d71f53c975b1e5b29f2f3b05a74e26dab9c3d84/bounded32.cpp#L290
    uint32_t x = uz_prng_get_uniform_uint32_zero_to_uint32_max(self);
    uint64_t m = (uint64_t)(x) * (uint64_t)(range);
    uint32_t l = (uint32_t)(m);
    if (l < range)
    {
        uint32_t t = -range;
        if (t >= range)
        {
            t -= range;
            if (t >= range)
            {
                t %= range;
            }
        }
        while (l < t)
        {
            x = uz_prng_get_uniform_uint32_zero_to_uint32_max(self);
            m = (uint64_t)(x) * (uint64_t)(range);
            l = (uint32_t)(m);
        }
    }
    return (uint32_t)(m >> 32);
}

uint32_t uz_prng_get_uniform_uint32_zero_to_range_float_mult(uz_prng_t *self, uint32_t range)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // This is USE_BIASED_FP_MULT_SCALE of https://github.com/imneme/bounded-rands/blob/3d71f53c975b1e5b29f2f3b05a74e26dab9c3d84/bounded32.cpp#L63
    uint32_t unbound_rng = uz_prng_get_uniform_uint32_zero_to_uint32_max(self);
    float zero_to_one_one = ((float)0x1.0p-32) * (float)unbound_rng;
    return (uint32_t)((float)range * zero_to_one_one);
}

uint32_t uz_prng_get_uniform_uint32_zero_to_range_int_mult(uz_prng_t *self, uint32_t range)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uint32_t unbound_rng = uz_prng_get_uniform_uint32_zero_to_uint32_max(self);
    // This is USE_BIASED_INT_MULT of https://github.com/imneme/bounded-rands/blob/3d71f53c975b1e5b29f2f3b05a74e26dab9c3d84/bounded32.cpp#L228
    uint64_t m = (uint64_t)(unbound_rng) * (uint64_t)(range);
    return (uint32_t)(m >> 32);
}

#endif
