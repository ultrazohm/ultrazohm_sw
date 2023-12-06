#ifdef TEST

#include "unity.h"

#include "uz_prng.h"
#include "uz_array.h"
#include "export_array.h"

#include "uz_prng_squares.h"
#include "uz_prng_halton.h"

#include "uz_prng_pcg.h"

#include "uz_prng_mtwister.h"
#include "mt19937.h"

#include "uz_prng_pcg.h"

#include "uz_prng_xoshiro.h"
#include "splitmix64.h"
#include "xoshiro128plusplus.h"

#include "uz_math.h"

#include <string.h>

#define NUMBER_OF_CALLS 5000

void setUp(void)
{
}

void tearDown(void)
{
}

void export_helper(uz_array_float_t export_array, uint32_t seed_index, char generator_type[]);

void test_uz_prng_equal_direct_usage_of_squares(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(0U);
    uz_prng_t *squares_by_prng = uz_prng_init(uz_prng_generator_squares, uz_prng_float_scale_fp_multiply, 0U);

    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    uint32_t random_number_fcn_pointer[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array_fcn_pointer = {
        .data = random_number_fcn_pointer,
        .length = UZ_ARRAY_SIZE(random_number_fcn_pointer)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_squares_get_uniform_uint32(squares);
        random_array_fcn_pointer.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(squares_by_prng);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_fcn_pointer, NUMBER_OF_CALLS);
}

void test_uz_prng_equal_direct_usage_of_mtwister(void)
{
    uz_prng_mtwister_t *mtwister = uz_prng_mtwister_init(0U);
    uz_prng_t *mtwister_by_prng = uz_prng_init(uz_prng_generator_mtwister, uz_prng_float_scale_fp_multiply, 0U);

    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    uint32_t random_number_fcn_pointer[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array_fcn_pointer = {
        .data = random_number_fcn_pointer,
        .length = UZ_ARRAY_SIZE(random_number_fcn_pointer)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_mtwister_get_uniform_uint32(mtwister);
        random_array_fcn_pointer.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(mtwister_by_prng);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_fcn_pointer, NUMBER_OF_CALLS);
}

void test_uz_prng_equal_direct_usage_of_pcg(void)
{
    uz_prng_pcg_t *pcg = uz_prng_pcg_init(0U);
    uz_prng_t *pcg_by_prng = uz_prng_init(uz_prng_generator_pcg, uz_prng_float_scale_fp_multiply, 0U);

    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    uint32_t random_number_fcn_pointer[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array_fcn_pointer = {
        .data = random_number_fcn_pointer,
        .length = UZ_ARRAY_SIZE(random_number_fcn_pointer)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_pcg_get_uniform_uint32(pcg);
        random_array_fcn_pointer.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(pcg_by_prng);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_fcn_pointer, NUMBER_OF_CALLS);
}

void test_uz_prng_equal_direct_usage_of_xoshiro(void)
{
    uz_prng_xoshiro_t *xoshiro = uz_prng_xoshiro_init(0U);
    uz_prng_t *xoshiro_by_prng = uz_prng_init(uz_prng_generator_xoshiro, uz_prng_float_scale_fp_multiply, 0U);

    uint32_t random_number[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    uint32_t random_number_fcn_pointer[NUMBER_OF_CALLS];
    uz_array_uint32_t random_array_fcn_pointer = {
        .data = random_number_fcn_pointer,
        .length = UZ_ARRAY_SIZE(random_number_fcn_pointer)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_xoshiro_get_uniform_uint32(xoshiro);
        random_array_fcn_pointer.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(xoshiro_by_prng);
    }
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number, random_number_fcn_pointer, NUMBER_OF_CALLS);
}

void test_uz_prng_equal_direct_usage_of_halton(void)
{
    uz_prng_halton_t *halton = uz_prng_halton_init(7U);
    uz_prng_t *halton_by_prng = uz_prng_init(uz_prng_generator_halton, uz_prng_float_scale_fp_multiply, 7U);

    float random_number[NUMBER_OF_CALLS];
    uz_array_float_t random_array = {
        .data = random_number,
        .length = UZ_ARRAY_SIZE(random_number)};

    float random_number_fcn_pointer[NUMBER_OF_CALLS];
    uz_array_float_t random_array_fcn_pointer = {
        .data = random_number_fcn_pointer,
        .length = UZ_ARRAY_SIZE(random_number_fcn_pointer)};

    for (uint32_t i = 0; i < random_array.length; i++)
    {
        random_array.data[i] = uz_prng_halton_get_uniform_float(halton);
        random_array_fcn_pointer.data[i] = uz_prng_get_uniform_float_zero_to_one(halton_by_prng);
    }
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(random_number, random_number_fcn_pointer, NUMBER_OF_CALLS);
}

#define NUMBER_OF_SEEDS 10

void test_uz_prng_export_many_seeds(void)
{

    uint64_t halton_seed[NUMBER_OF_SEEDS] = {13, 17, 19, 23, 29, 31, 37, 41, 43, 47};                                 // 6. to 15. prime number
    uint64_t xoshiro_seed[NUMBER_OF_SEEDS] = {0, 59994356, 96162775, 58988824, 66869139, 20, 17, 23605, 50, 258116};  // arbitrary numbers with large and small seeds
    uint64_t pcg_seed[NUMBER_OF_SEEDS] = {0, 59994356, 96162775, 58988824, 66869139, 20, 17, 23605, 50, 258116};      // arbitrary numbers with large and small seeds
    uint64_t mtwister_seed[NUMBER_OF_SEEDS] = {0, 59994356, 96162775, 58988824, 66869139, 20, 17, 23605, 50, 258116}; // arbitrary numbers with large and small seeds
    uint64_t squares_seed[NUMBER_OF_SEEDS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};                                          // take key's from list
    uz_prng_t *halton = uz_prng_init(uz_prng_generator_halton, uz_prng_float_scale_fp_multiply, 7U);
    uz_prng_t *xoshiro = uz_prng_init(uz_prng_generator_xoshiro, uz_prng_float_scale_fp_multiply, 0U);
    uz_prng_t *pcg = uz_prng_init(uz_prng_generator_pcg, uz_prng_float_scale_fp_multiply, 0U);
    uz_prng_t *mtwister = uz_prng_init(uz_prng_generator_mtwister, uz_prng_float_scale_fp_multiply, 0U);
    uz_prng_t *squares = uz_prng_init(uz_prng_generator_squares, uz_prng_float_scale_fp_multiply, 0U);

    float halton_output[NUMBER_OF_CALLS];
    uz_array_float_t halton_array = {
        .data = halton_output,
        .length = UZ_ARRAY_SIZE(halton_output)};

    float xoshiro_output[NUMBER_OF_CALLS];
    uz_array_float_t xoshiro_array = {
        .data = xoshiro_output,
        .length = UZ_ARRAY_SIZE(xoshiro_output)};

    float pcg_output[NUMBER_OF_CALLS];
    uz_array_float_t pcg_array = {
        .data = pcg_output,
        .length = UZ_ARRAY_SIZE(pcg_output)};

    float mtwister_output[NUMBER_OF_CALLS];
    uz_array_float_t mtwister_array = {
        .data = mtwister_output,
        .length = UZ_ARRAY_SIZE(mtwister_output)};

    float squares_output[NUMBER_OF_CALLS];
    uz_array_float_t squares_array = {
        .data = squares_output,
        .length = UZ_ARRAY_SIZE(squares_output)};

    for (uint32_t seed_index = 0; seed_index < NUMBER_OF_SEEDS; seed_index++)
    {

        uz_prng_reset(halton, halton_seed[seed_index]);
        uz_prng_reset(mtwister, mtwister_seed[seed_index]);
        uz_prng_reset(pcg, pcg_seed[seed_index]);
        uz_prng_reset(xoshiro, xoshiro_seed[seed_index]);
        uz_prng_reset(squares, squares_seed[seed_index]);

        for (uint32_t i = 0; i < squares_array.length; i++)
        {
            halton_array.data[i] = uz_prng_get_uniform_float_zero_to_one(halton);
            squares_array.data[i] = uz_prng_get_uniform_float_zero_to_one(squares);
            pcg_array.data[i] = uz_prng_get_uniform_float_zero_to_one(pcg);
            xoshiro_array.data[i] = uz_prng_get_uniform_float_zero_to_one(xoshiro);
            mtwister_array.data[i] = uz_prng_get_uniform_float_zero_to_one(mtwister);
        }
        float mean_halton = uz_math_mean(halton_array);
        float mean_squares = uz_math_mean(squares_array);
        float mean_mtwister = uz_math_mean(mtwister_array);
        float mean_pcg = uz_math_mean(pcg_array);
        float mean_xoshiro = uz_math_mean(xoshiro_array);

        TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, mean_halton);
        TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, mean_squares);
        TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, mean_mtwister);
        TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, mean_pcg);
        TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, mean_xoshiro);
        export_helper(halton_array, seed_index, "halton");
        export_helper(pcg_array, seed_index, "pcg");
        export_helper(mtwister_array, seed_index, "mtwister");
        export_helper(squares_array, seed_index, "squares");
        export_helper(xoshiro_array, seed_index, "xoshiro");
    }
}

void export_helper(uz_array_float_t export_array, uint32_t seed_index, char generator_type[])
{

    char str[1000]={0};
    char str2[1000]={0};
    sprintf(str2, "_seed_index_%d.csv", seed_index);
    strcat(str, generator_type);
    strcat(str, str2);

    char absolute_path[1000] = "test/uz/uz_prng/";
    strcat(absolute_path,str );
    export_array_float(export_array, absolute_path);
}

#endif // TEST
