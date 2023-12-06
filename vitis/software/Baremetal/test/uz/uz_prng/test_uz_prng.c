#ifdef TEST

#include "unity.h"

#include "uz_prng.h"
#include "uz_array.h"
#include "export_array.h"

#include "uz_prng_squares.h"
#include "uz_prng_squares.h"
#include "uz_prng_halton.h"

#include "uz_prng_pcg.h"
#include "mt19937.h"

#include "uz_prng_pcg.h"

#include "uz_prng_xoshiro.h"
#include "splitmix64.h"
#include "xoshiro128plusplus.h"

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
    float mean = (float)uz_math_mean_uint32_t(random_array);
    // TEST_ASSERT_EQUAL_FLOAT(2147483648.0f,mean);
}

void test_uz_prng_test_function_pointer(void)
{
    uz_prng_squares_t *squares = uz_prng_squares_init(0U);
    uz_prng_t *squares_by_prng = uz_prng_init(uz_prng_generator_squares, uz_prng_float_scale_fp_multiply,0U);

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
    TEST_ASSERT_EQUAL_UINT32_ARRAY(random_number,random_number_fcn_pointer,NUMBER_OF_CALLS);
}



#endif // TEST
