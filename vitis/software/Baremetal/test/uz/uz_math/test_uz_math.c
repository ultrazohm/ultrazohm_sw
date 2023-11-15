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

void test_uz_math_mean(void)

{

    float input_data[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    uz_array_float_t array = {
        .length = UZ_ARRAY_SIZE(input_data),
        .data = input_data};
    float mean = uz_math_mean(array);

    TEST_ASSERT_EQUAL_FLOAT(3.5f, mean);
}

void test_uz_math_mean_second_pair_of_values(void)
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

void test_uz_math_variance(void)
{
    // Wiki example
    // https://en.wikipedia.org/wiki/Standard_deviation#Sample_standard_deviation

    float input_data[8] = {2.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 7.0f, 9.0f};
    uz_array_float_t array = {
        .length = UZ_ARRAY_SIZE(input_data),
        .data = input_data};
    float variance = uz_math_variance(array);

    TEST_ASSERT_EQUAL_FLOAT(4.0f, variance);
}

void test_uz_math_standard_deviation(void)

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

#endif // TEST