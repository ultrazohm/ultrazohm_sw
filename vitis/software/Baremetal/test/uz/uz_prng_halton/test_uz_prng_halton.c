#ifdef TEST

#include "unity.h"
#include <stdint.h>
#include "uz_prng_halton.h"
#include "uz_array.h"
#include "export_array.h"


void setUp(void)
{
}

void tearDown(void)
{
}
#define NUMBER_OF_CALLS 5000

void test_uz_prng_halton_float(void)
{
    uz_prng_halton_t *halton = uz_prng_halton_init(7U);
    float random_number[NUMBER_OF_CALLS];
    uz_array_float_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_halton_get_uniform_float(halton);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_halton/uz_prng_halton_float.csv";
    export_array_float(random_array, filepath);
}

void test_uz_prng_halton_uint32(void)
{
    uz_prng_halton_t *halton = uz_prng_halton_init(7U);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = (uint32_t)(uz_prng_halton_get_uniform_float(halton) * (float)UINT32_MAX);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_halton/uz_prng_halton_uint32.csv";
    export_array_uint32(random_array, filepath);
}

void test_uz_prng_halton_2d_float(void)
{
    uz_prng_halton_t *halton = uz_prng_halton_init(7U);
    float x[NUMBER_OF_CALLS];
    float y[NUMBER_OF_CALLS];
    uz_array_float_t random_array_x = {
        .data = x,
        .length = UZ_ARRAY_SIZE(x)};
    uz_array_float_t random_array_y = {
        .data = y,
        .length = UZ_ARRAY_SIZE(y)};

    for (uint32_t i = 0; i < random_array_x.length; i++)
    {
        uz_prng_halton_get_uniform_float_2d(halton, &random_array_x.data[i], &random_array_y.data[i]);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_halton/uz_prng_halton_2d_float_x.csv";
    export_array_float(random_array_x, filepath);
    char filepath2[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_halton/uz_prng_halton_2d_float_y.csv";
    export_array_float(random_array_y, filepath2);
}

#endif // TEST
