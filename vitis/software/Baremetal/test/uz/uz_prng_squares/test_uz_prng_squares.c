#ifdef TEST

#include "unity.h"

#include "uz_prng_squares.h"
#include "export_array.h"
#include "uz_array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#define NUMBER_OF_CALLS 1000

void test_uz_prng_squares_uint32(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init();
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array={
        .data=random_number,
        .length=UZ_ARRAY_SIZE(random_number)
    };

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_uint32(squares);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_squares/uz_prng_squares_uint32.csv";
    export_array_uint32(random_array, filepath);
}

void test_uz_prng_squares_float(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init();
    float random_number[NUMBER_OF_CALLS]={0};
    uz_array_float_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};
    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_float_zero_to_one(squares);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_squares/uz_prng_squares_float.csv";
    export_array_float(random_array, filepath);
}

#endif // TEST
