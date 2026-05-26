#ifdef TEST

#include "unity.h"
#include "uz_prng_pcg.h"
#include "uz_array.h"
#include "export_array.h"
#include "uz_math.h"

#define NUMBER_OF_CALLS 5000


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_prng_pcg_init(void)
{
    uz_prng_pcg_init(0U);
}

void test_uz_prng_pcg_uint32(void)
{
    uz_prng_pcg_t *pcg = uz_prng_pcg_init(0U);
    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_pcg_get_uniform_uint32(pcg);
    }
    float mean = uz_math_mean_uint32_t(random_array);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, mean/(float)UINT32_MAX );
    char filepath[] = "../../../docs/source/software/library/uz_prng/uz_prng_pcg/uz_prng_pcg_uint32.csv";
    export_array_uint32(random_array, filepath);
}

void test_uz_prng_pcg_equal_two_instances(void)
{
    uint32_t seed = 168221U;
    uz_prng_pcg_t *pcg = uz_prng_pcg_init(seed);
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
        random_array.data[i] = uz_prng_pcg_get_uniform_uint32(pcg);
    }

    uz_prng_pcg_t *pcg2 = uz_prng_pcg_init(seed);

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array_2.data[i] = uz_prng_pcg_get_uniform_uint32(pcg2);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_2, NUMBER_OF_CALLS);
}

void test_uz_prng_pcg_equal_after_reset(void)
{
    uint32_t seed = 168221U;
    uz_prng_pcg_t *pcg = uz_prng_pcg_init(seed);
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
        random_array.data[i] = uz_prng_pcg_get_uniform_uint32(pcg);
    }

    uz_prng_pcg_reset(pcg, seed);

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array_2.data[i] = uz_prng_pcg_get_uniform_uint32(pcg);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_2, NUMBER_OF_CALLS);
}

#endif // TEST
