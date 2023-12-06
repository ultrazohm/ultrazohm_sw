#ifdef TEST

#include "unity.h"

#include "uz_prng_squares.h"
#include "export_array.h"
#include "uz_array.h"
#include "uz_math.h"

void setUp(void)
{
}

void tearDown(void)
{
}

#define NUMBER_OF_CALLS 5000

void test_uz_prng_squares_uint32(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(0U);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array={
        .data=random_number,
        .length=UZ_ARRAY_SIZE(random_number)
    };

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_uint32(squares);
    }
    float mean = uz_math_mean_uint32_t(random_array);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, mean / (float)UINT32_MAX);
    char filepath[] = "test/uz/uz_prng_squares/uz_prng_squares_uint32.csv";
    export_array_uint32(random_array, filepath);
}

void test_uz_prng_squares_equal_two_instances(void)
{
    uint32_t seed = 0U;
    uz_prng_squares_t *squares = uz_prng_squares_init(seed);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    uint32_t random_number_2[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array_2 = {
        .data = random_number_2,
        .length = UZ_ARRAY_SIZE(random_number_2)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_uint32(squares);
    }

    uz_prng_squares_t *squares2 = uz_prng_squares_init(seed);

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array_2.data[i] = uz_prng_squares_get_uniform_uint32(squares2);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_2, NUMBER_OF_CALLS);
}

void test_uz_prng_squares_equal_after_reset(void)
{
    uint32_t seed = 0U;
    uz_prng_squares_t *squares = uz_prng_squares_init(seed);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    uint32_t random_number_2[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array_2 = {
        .data = random_number_2,
        .length = UZ_ARRAY_SIZE(random_number_2)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_uint32(squares);
    }

    uz_prng_squares_reset(squares, seed);

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array_2.data[i] = uz_prng_squares_get_uniform_uint32(squares);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_2, NUMBER_OF_CALLS);
}

#endif // TEST
