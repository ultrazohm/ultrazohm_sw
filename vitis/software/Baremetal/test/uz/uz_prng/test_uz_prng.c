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

void export_helper_float(uz_array_float_t export_array, uint32_t seed_index, char generator_type[]);
void export_helper_uint32(uz_array_uint32_t export_array, uint32_t seed_index, char generator_type[]);

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
        export_helper_float(halton_array, seed_index, "halton");
        export_helper_float(pcg_array, seed_index, "pcg");
        export_helper_float(mtwister_array, seed_index, "mtwister");
        export_helper_float(squares_array, seed_index, "squares");
        export_helper_float(xoshiro_array, seed_index, "xoshiro");
    }
}

void test_uz_prng_export_many_seeds_biased_uint1000(void)
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

    uint32_t halton_output[NUMBER_OF_CALLS];
    uz_array_uint32_t halton_array = {
        .data = halton_output,
        .length = UZ_ARRAY_SIZE(halton_output)};

    uint32_t xoshiro_output[NUMBER_OF_CALLS];
    uz_array_uint32_t xoshiro_array = {
        .data = xoshiro_output,
        .length = UZ_ARRAY_SIZE(xoshiro_output)};

    uint32_t pcg_output[NUMBER_OF_CALLS];
    uz_array_uint32_t pcg_array = {
        .data = pcg_output,
        .length = UZ_ARRAY_SIZE(pcg_output)};

    uint32_t mtwister_output[NUMBER_OF_CALLS];
    uz_array_uint32_t mtwister_array = {
        .data = mtwister_output,
        .length = UZ_ARRAY_SIZE(mtwister_output)};

    uint32_t squares_output[NUMBER_OF_CALLS];
    uz_array_uint32_t squares_array = {
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
            halton_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_int_mult(halton, 9U);
            squares_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_int_mult(squares, 9U);
            pcg_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_int_mult(pcg, 9U);
            xoshiro_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_int_mult(xoshiro, 9U);
            mtwister_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_int_mult(mtwister, 9U);
        }
        export_helper_uint32(halton_array, seed_index, "halton_biased1000");
        export_helper_uint32(pcg_array, seed_index, "pcg_biased1000");
        export_helper_uint32(mtwister_array, seed_index, "mtwister_biased1000");
        export_helper_uint32(squares_array, seed_index, "squares_biased1000");
        export_helper_uint32(xoshiro_array, seed_index, "xoshiro_biased1000");
    }
}

void test_uz_prng_export_many_seeds_unbiased_uint1000(void)
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

    uint32_t halton_output[NUMBER_OF_CALLS];
    uz_array_uint32_t halton_array = {
        .data = halton_output,
        .length = UZ_ARRAY_SIZE(halton_output)};

    uint32_t xoshiro_output[NUMBER_OF_CALLS];
    uz_array_uint32_t xoshiro_array = {
        .data = xoshiro_output,
        .length = UZ_ARRAY_SIZE(xoshiro_output)};

    uint32_t pcg_output[NUMBER_OF_CALLS];
    uz_array_uint32_t pcg_array = {
        .data = pcg_output,
        .length = UZ_ARRAY_SIZE(pcg_output)};

    uint32_t mtwister_output[NUMBER_OF_CALLS];
    uz_array_uint32_t mtwister_array = {
        .data = mtwister_output,
        .length = UZ_ARRAY_SIZE(mtwister_output)};

    uint32_t squares_output[NUMBER_OF_CALLS];
    uz_array_uint32_t squares_array = {
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
            halton_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(halton, 9U);
            squares_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(squares, 9U);
            pcg_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(pcg, 9U);
            xoshiro_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(xoshiro, 9U);
            mtwister_array.data[i] = uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(mtwister, 9U);
        }
        export_helper_uint32(halton_array, seed_index, "halton_unbiased1000");
        export_helper_uint32(pcg_array, seed_index, "pcg_unbiased1000");
        export_helper_uint32(mtwister_array, seed_index, "mtwister_unbiased1000");
        export_helper_uint32(squares_array, seed_index, "squares_unbiased1000");
        export_helper_uint32(xoshiro_array, seed_index, "xoshiro_unbiased1000");
    }
}

void test_uz_prng_normal_distribution_mean_5(void)
{
    uz_prng_t *squares = uz_prng_init(uz_prng_generator_squares, uz_prng_float_scale_fp_multiply, 0U);

    float expected_mean = 5.0f;
    float expected_std = 3.0f;

    float squares_output[NUMBER_OF_CALLS];
    uz_array_float_t squares_array = {
        .data = squares_output,
        .length = UZ_ARRAY_SIZE(squares_output)};

    for (uint32_t i = 0; i < squares_array.length; i++)
    {
        squares_array.data[i] = uz_prng_get_normal_float(squares, expected_mean, expected_std);
    }
    float mean = uz_math_mean(squares_array);
    float std = uz_math_standard_deviation(squares_array);
    TEST_ASSERT_FLOAT_WITHIN(0.1, expected_mean, mean);
    TEST_ASSERT_FLOAT_WITHIN(0.1, expected_std, std);
}

void test_uz_prng_normal_distribution(void)
{

    float expected_mean = 0.0f;
    float expected_std = 1.0f;

    uz_prng_t *squares = uz_prng_init(uz_prng_generator_squares, uz_prng_float_scale_fp_multiply, 0U);

    float squares_output[NUMBER_OF_CALLS];
    uz_array_float_t squares_array = {
        .data = squares_output,
        .length = UZ_ARRAY_SIZE(squares_output)};

    for (uint32_t i = 0; i < squares_array.length; i++)
    {
        squares_array.data[i] = uz_prng_get_normal_float(squares, expected_mean, expected_std);
    }
    float mean = uz_math_mean(squares_array);
    float std = uz_math_standard_deviation(squares_array);
    TEST_ASSERT_FLOAT_WITHIN(0.1, expected_mean, mean);
    TEST_ASSERT_FLOAT_WITHIN(0.1, expected_std, std);
}

void test_uz_prng_normal_distribution_plot(void)
{

    float expected_mean = 0.0f;
    float expected_std = 1.0f;

    uz_prng_t *squares = uz_prng_init(uz_prng_generator_squares, uz_prng_float_scale_fp_multiply, 0U);

    float squares_output[NUMBER_OF_CALLS];
    uz_array_float_t squares_array = {
        .data = squares_output,
        .length = UZ_ARRAY_SIZE(squares_output)};

    for (uint32_t i = 0; i < squares_array.length; i++)
    {
        squares_array.data[i] = uz_prng_get_normal_float(squares, expected_mean, expected_std);
    }
    char filepath_1[] = "test/uz/uz_prng/uz_prng_normal_distribution_1.csv";
    export_array_float(squares_array, filepath_1);

    uz_prng_reset(squares, 1U);
    for (uint32_t i = 0; i < squares_array.length; i++)
    {
        squares_array.data[i] = uz_prng_get_normal_float(squares, expected_mean, expected_std);
    }
    char filepath_2[] = "test/uz/uz_prng/uz_prng_normal_distribution_2.csv";
    export_array_float(squares_array, filepath_2);

    uz_prng_reset(squares, 2U);
    for (uint32_t i = 0; i < squares_array.length; i++)
    {
        squares_array.data[i] = uz_prng_get_normal_float(squares, expected_mean, expected_std);
    }
    char filepath_3[] = "test/uz/uz_prng/uz_prng_normal_distribution_3.csv";
    export_array_float(squares_array, filepath_3);
}

void test_uz_prng_squares_equal_after_reset(void)
{
    uint64_t seed=0U;
    uz_prng_t *prng = uz_prng_init(uz_prng_generator_squares, uz_prng_float_scale_fp_multiply, seed);

    uint32_t first_run[NUMBER_OF_CALLS];
    uz_array_uint32_t first_run_array = {
        .data = first_run,
        .length = UZ_ARRAY_SIZE(first_run)};

    uint32_t second_run[NUMBER_OF_CALLS];
    uz_array_uint32_t second_run_array = {
        .data = second_run,
        .length = UZ_ARRAY_SIZE(second_run)};

    uint32_t third_run[NUMBER_OF_CALLS];
    uz_array_uint32_t third_run_array = {
        .data = third_run,
        .length = UZ_ARRAY_SIZE(third_run)};

    for (uint32_t i = 0; i < first_run_array.length; i++)
    {
        first_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng,seed);
    for (uint32_t i = 0; i < second_run_array.length; i++)
    {
        second_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < third_run_array.length; i++)
    {
        third_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, second_run, NUMBER_OF_CALLS);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, third_run, NUMBER_OF_CALLS);
}

void test_uz_prng_twister_equal_after_reset(void)
{
    uint64_t seed = 0U;
    uz_prng_t *prng = uz_prng_init(uz_prng_generator_mtwister, uz_prng_float_scale_fp_multiply, seed);

    uint32_t first_run[NUMBER_OF_CALLS];
    uz_array_uint32_t first_run_array = {
        .data = first_run,
        .length = UZ_ARRAY_SIZE(first_run)};

    uint32_t second_run[NUMBER_OF_CALLS];
    uz_array_uint32_t second_run_array = {
        .data = second_run,
        .length = UZ_ARRAY_SIZE(second_run)};

    uint32_t third_run[NUMBER_OF_CALLS];
    uz_array_uint32_t third_run_array = {
        .data = third_run,
        .length = UZ_ARRAY_SIZE(third_run)};

    for (uint32_t i = 0; i < first_run_array.length; i++)
    {
        first_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < second_run_array.length; i++)
    {
        second_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < third_run_array.length; i++)
    {
        third_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, second_run, NUMBER_OF_CALLS);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, third_run, NUMBER_OF_CALLS);
}

void test_uz_prng_pcg_equal_after_reset(void)
{
    uint64_t seed = 0U;
    uz_prng_t *prng = uz_prng_init(uz_prng_generator_pcg, uz_prng_float_scale_fp_multiply, seed);

    uint32_t first_run[NUMBER_OF_CALLS];
    uz_array_uint32_t first_run_array = {
        .data = first_run,
        .length = UZ_ARRAY_SIZE(first_run)};

    uint32_t second_run[NUMBER_OF_CALLS];
    uz_array_uint32_t second_run_array = {
        .data = second_run,
        .length = UZ_ARRAY_SIZE(second_run)};

    uint32_t third_run[NUMBER_OF_CALLS];
    uz_array_uint32_t third_run_array = {
        .data = third_run,
        .length = UZ_ARRAY_SIZE(third_run)};

    for (uint32_t i = 0; i < first_run_array.length; i++)
    {
        first_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < second_run_array.length; i++)
    {
        second_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < third_run_array.length; i++)
    {
        third_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, second_run, NUMBER_OF_CALLS);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, third_run, NUMBER_OF_CALLS);
}

void test_uz_prng_halton_equal_after_reset(void)
{
    uint64_t seed = 7U;
    uz_prng_t *prng = uz_prng_init(uz_prng_generator_mtwister, uz_prng_float_scale_fp_multiply, seed);

    uint32_t first_run[NUMBER_OF_CALLS];
    uz_array_uint32_t first_run_array = {
        .data = first_run,
        .length = UZ_ARRAY_SIZE(first_run)};

    uint32_t second_run[NUMBER_OF_CALLS];
    uz_array_uint32_t second_run_array = {
        .data = second_run,
        .length = UZ_ARRAY_SIZE(second_run)};

    uint32_t third_run[NUMBER_OF_CALLS];
    uz_array_uint32_t third_run_array = {
        .data = third_run,
        .length = UZ_ARRAY_SIZE(third_run)};

    for (uint32_t i = 0; i < first_run_array.length; i++)
    {
        first_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < second_run_array.length; i++)
    {
        second_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < third_run_array.length; i++)
    {
        third_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, second_run, NUMBER_OF_CALLS);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, third_run, NUMBER_OF_CALLS);
}

void test_uz_prng_xoshiro_equal_after_reset(void)
{
    uint64_t seed = 5642U;
    uz_prng_t *prng = uz_prng_init(uz_prng_generator_xoshiro, uz_prng_float_scale_fp_multiply, seed);

    uint32_t first_run[NUMBER_OF_CALLS];
    uz_array_uint32_t first_run_array = {
        .data = first_run,
        .length = UZ_ARRAY_SIZE(first_run)};

    uint32_t second_run[NUMBER_OF_CALLS];
    uz_array_uint32_t second_run_array = {
        .data = second_run,
        .length = UZ_ARRAY_SIZE(second_run)};

    uint32_t third_run[NUMBER_OF_CALLS];
    uz_array_uint32_t third_run_array = {
        .data = third_run,
        .length = UZ_ARRAY_SIZE(third_run)};

    for (uint32_t i = 0; i < first_run_array.length; i++)
    {
        first_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < second_run_array.length; i++)
    {
        second_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }
    uz_prng_reset(prng, seed);
    for (uint32_t i = 0; i < third_run_array.length; i++)
    {
        third_run_array.data[i] = uz_prng_get_uniform_uint32_zero_to_uint32_max(prng);
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, second_run, NUMBER_OF_CALLS);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(first_run, third_run, NUMBER_OF_CALLS);
}


void export_helper_float(uz_array_float_t export_array, uint32_t seed_index, char generator_type[])
{

    char str[1000] = {0};
    char str2[1000] = {0};
    sprintf(str2, "_seed_index_%d.csv", seed_index);
    strcat(str, generator_type);
    strcat(str, str2);

    char absolute_path[1000] = "test/uz/uz_prng/";
    strcat(absolute_path, str);
    export_array_float(export_array, absolute_path);
}

void export_helper_uint32(uz_array_uint32_t export_array, uint32_t seed_index, char generator_type[])
{

    char str[1000] = {0};
    char str2[1000] = {0};
    sprintf(str2, "_seed_index_%d.csv", seed_index);
    strcat(str, generator_type);
    strcat(str, str2);

    char absolute_path[1000] = "test/uz/uz_prng/";
    strcat(absolute_path, str);
    export_array_uint32(export_array, absolute_path);
}
#endif // TEST
