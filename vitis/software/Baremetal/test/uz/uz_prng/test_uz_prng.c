#ifdef TEST

#include "unity.h"

#include "uz_prng.h"
#include "uz_array.h"
#include "export_array.h"
#include "uz_prng_squares.h"
#include "uz_math.h"

#define NUMBER_OF_CALLS 5000

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_prng_test_mean(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(1U);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_uint32(squares);
    }
    float mean = uz_math_mean_uint32_t(random_array);
    // TEST_ASSERT_EQUAL_FLOAT(2147483648.0f,mean);
}

void test_uz_prng_float(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(2U);
    float random_number[NUMBER_OF_CALLS] = {0};
    uz_array_float_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};
    for (uint32_t i = 0; i < random_array.length; i++)
    {
        uint32_t random_value = uz_prng_squares_get_uniform_uint32(squares);
        random_array.data[i] = uz_prng_get_uniform_float_zero_to_one(random_value);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_squares/uz_prng_squares_float.csv";
    export_array_float(random_array, filepath);
    float mean_sampled = uz_math_mean(random_array);
    float mean = 0.5f;
    // TEST_ASSERT_FLOAT_WITHIN(0.001f, mean, mean_sampled);
}

void test_uz_prng_bounded_uint32_biased(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(2U);
    uint32_t random_number[NUMBER_OF_CALLS] = {0};
    uint32_t random_number_unbounded[NUMBER_OF_CALLS] = {0};
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    uz_array_uint32_t random_array_unbounded = {
        .data = random_number_unbounded,
        .length = UZ_ARRAY_SIZE(random_number_unbounded)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array_unbounded.data[i] = uz_prng_squares_get_uniform_uint32(squares);
        random_array.data[i] = uz_prng_bounded_rand_multiply_bias(random_array_unbounded.data[i], 52U);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_bounded_bias.csv";
    char filepath_1[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_unbounded_bias.csv";
    export_array_uint32(random_array, filepath);
    export_array_uint32(random_array_unbounded, filepath_1);
}

void test_uz_prng_bounded_uint32_unbiased(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(2U);
    uint32_t random_number[NUMBER_OF_CALLS] = {0};
    uint32_t random_number_unbounded[NUMBER_OF_CALLS] = {0};
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_bounded_rand_unbiased(squares, 52U);
    }
    char filepath[] = "../../../docs/source/mpsoc/software_framework/uz_prng/uz_prng_bounded_unbias.csv";
    export_array_uint32(random_array, filepath);
}

#endif // TEST
