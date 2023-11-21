#include "uz_prng.h"
#include "../uz_HAL.h"
#include <stdint.h>

#define SCALE_TO_FLOAT 0xffffffffU // 4294967296 in the code example of the paper author

float uz_prng_get_uniform_float_zero_to_one(uint32_t random_number)
{
    float random_float = (float)(random_number) / (float)SCALE_TO_FLOAT; // Paper author code uses double and no cast to scale - unclear why this works in the example code provided -> works obv. with cast as it forces floating point division. Additionally, paper scales by 4294967296 instead of 0xffffffffU (which is uint32_t max). Not clear either.
    return random_float;
}

float uz_prng_get_uniform_float_zero_to_one_multi(uint32_t random_number)
{
    // (Note that 0x1.0p-32 is a binary floating point constant for 2-32 that we use to convert a random integer value in the range [0..232) into a double in the unit interval;
    return ((float)0x1.0p-32) * random_number;
}

// https://www.pcg-random.org/posts/bounded-rands.html
uint32_t uz_prng_bounded_rand_multiply_bias(uint32_t unbound_rng, uint32_t range)
{
    float zeroone = ((float)0x1.0p-32) * unbound_rng;
    return range * zeroone;
}

uint32_t uz_prng_bounded_rand(uint32_t unbound_rng, uint32_t range)
{
    uint64_t m = (uint64_t)(unbound_rng) * (uint64_t)(range);
    return m >> 32;
}

