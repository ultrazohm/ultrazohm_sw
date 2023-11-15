#ifdef TEST

#include "unity.h"

#include "uz_math.h"
#include "uz_array.h"

void setUp(void)

{
}

void tearDown(void)

{
}

void test_uz_math_mean_float(void)
{
    float input_data[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    uz_array_float_t array = {
        .length = UZ_ARRAY_SIZE(input_data),
        .data = input_data};
    float mean = uz_math_mean(array);

    TEST_ASSERT_EQUAL_FLOAT(3.5f, mean);
}

void test_uz_math_mean_second_pair_of_values_float(void)
{
    // Wiki example
    // https://en.wikipedia.org/wiki/Standard_deviation#Sample_standard_deviation

    float input_data[8] = {2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f};
    uz_array_float_t array = {
        .length = UZ_ARRAY_SIZE(input_data),
        .data = input_data};

    float mean = uz_math_mean(array);

    TEST_ASSERT_EQUAL_FLOAT(5.0f, mean);
}

void test_uz_math_variance_float(void)
{
    // Wiki example
    // https://en.wikipedia.org/wiki/Standard_deviation#Sample_standard_deviation

    float input_data[8] = {2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f};
    uz_array_float_t array = {
        .length = UZ_ARRAY_SIZE(input_data),
        .data = input_data};
    float variance = uz_math_variance_uncorrected(array);

    TEST_ASSERT_EQUAL_FLOAT(4.0f, variance);
}

void test_uz_math_standard_deviation_float(void)
{
    // Wiki example
    // https://en.wikipedia.org/wiki/Standard_deviation#Sample_standard_deviation
    float input_data[8] = {2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f};
    uz_array_float_t array = {
        .length = UZ_ARRAY_SIZE(input_data),
        .data = input_data};
    float variance = uz_math_standard_deviation(array);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, variance);
}

void test_uz_math_mean_uint32(void)
{
    uint32_t input_data[6] = {1, 2, 3, 4, 5, 6};
    uz_array_uint32_t array = {
        .length = UZ_ARRAY_SIZE(input_data),
        .data = input_data};
    float mean = uz_math_mean_uint32_t(array);

    TEST_ASSERT_EQUAL_FLOAT(3.5f, mean);
}

#endif // TEST