#include "uz_prng.h"
#include "../uz_HAL.h"

#define SCALE_TO_FLOAT 0xffffffffU // 4294967296 in the code example of the paper author

float uz_prng_get_uniform_float_zero_to_one(uint32_t random_number)
{
    float random_float = (float)(random_number) / (float)SCALE_TO_FLOAT; // Paper author code uses double and no cast to scale - unclear why this works in the example code provided -> works obv. with cast as it forces floating point division. Additionally, paper scales by 4294967296 instead of 0xffffffffU (which is uint32_t max). Not clear either.
    return random_float;
}