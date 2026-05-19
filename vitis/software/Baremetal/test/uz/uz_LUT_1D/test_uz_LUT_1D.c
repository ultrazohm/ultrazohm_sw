#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_LUT_1D.h"
#include <math.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_LUT_1D_Successfull_Init(void)
{
    float breakpoints5[5] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    float data5[5] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f};
    uz_array_float_t breakpoints_array5 = {.length = UZ_ARRAY_SIZE(breakpoints5), .data = breakpoints5};
    uz_array_float_t data_array5 = {.length = UZ_ARRAY_SIZE(data5), .data = data5};
    uz_LUT_1D_t* instance = uz_LUT_1D_init(&breakpoints_array5, &data_array5);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_LUT_1D_Assert_Breakpoints_Null(void)
{
    float data5[5] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f};
    uz_array_float_t data_array5 = {.length = UZ_ARRAY_SIZE(data5), .data = data5};
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(NULL, &data_array5));
}

void test_uz_LUT_1D_Assert_Data_Null(void)
{
    float breakpoints5[5] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    uz_array_float_t breakpoints_array5 = {.length = UZ_ARRAY_SIZE(breakpoints5), .data = breakpoints5};
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(&breakpoints_array5, NULL));
}

void test_uz_LUT_1D_Assert_Breakpoints_not_increasing(void)
{
    float breakpoints[5] = {0.0f, 2.0f, 1.0f, 3.0f, 4.0f};
    float data[5]        = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f};
     uz_array_float_t breakpoints_array = {.length = UZ_ARRAY_SIZE(breakpoints), .data = breakpoints};
     uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(&breakpoints_array, &data_array));
}

void test_uz_LUT_1D_Successfull_array_length_mismatch(void)
{
    float breakpoints5[5] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    float data20[20] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f, 34.0f, 36.0f, 38.0f};
    uz_array_float_t breakpoints_array5 = {.length = UZ_ARRAY_SIZE(breakpoints5), .data = breakpoints5};
    uz_array_float_t data_array20 = {.length = UZ_ARRAY_SIZE(data20), .data = data20};
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(&breakpoints_array5, &data_array20));
}

void test_uz_LUT_1D_get_value_assert_Null_pointer_to_instance(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_get_value(NULL, 1.0f));
}

void test_uz_LUT_1D_get_value_5values(void) {
    float breakpoints5[5] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    float data5[5] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f};
    uz_array_float_t breakpoints_array5 = {.length = UZ_ARRAY_SIZE(breakpoints5), .data = breakpoints5};
    uz_array_float_t data_array5 = {.length = UZ_ARRAY_SIZE(data5), .data = data5};

    uz_LUT_1D_t* instance = uz_LUT_1D_init(&breakpoints_array5, &data_array5);
    float output = uz_LUT_1D_get_value(instance, 1.0f);
    float expected = 2.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    //lin interpolation
    output = uz_LUT_1D_get_value(instance, 2.5f);
    expected = 5.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    //out of bounds
    output = uz_LUT_1D_get_value(instance, -1.0f);
    expected = 0.0f;//first value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    output = uz_LUT_1D_get_value(instance, 5.0f);
    expected = 8.0f;//last value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}

void test_uz_LUT_1D_get_value_20values(void) {
    float breakpoints20[20] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f};
    float data20[20] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f, 34.0f, 36.0f, 38.0f};

    uz_array_float_t breakpoints_array20 = {.length = UZ_ARRAY_SIZE(breakpoints20), .data = breakpoints20};
    uz_array_float_t data_array20 = {.length = UZ_ARRAY_SIZE(data20), .data = data20};

    uz_LUT_1D_t* instance = uz_LUT_1D_init(&breakpoints_array20, &data_array20);
    float output = uz_LUT_1D_get_value(instance, 1.0f);
    float expected = 2.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    //lin interpolation
    output = uz_LUT_1D_get_value(instance, 7.5f);
    expected = 15.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    //Max value
    output = uz_LUT_1D_get_value(instance, 19.0f);
    expected = 38.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    //out of bounds
    output = uz_LUT_1D_get_value(instance, -1.0f);
    expected = 0.0f;//first value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    output = uz_LUT_1D_get_value(instance, 22.0f);
    expected = 38.0f;//last value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}

void test_uz_LUT_1D_get_value_non_monotonic_data(void)
{
    float LUT_breakpoints_array[5] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    float LUT_data_array[5]        = {10.0f, 4.0f, 8.0f, -1.0f, 6.0f};
    uz_array_float_t breakpoints_array = {.length = UZ_ARRAY_SIZE(LUT_breakpoints_array), .data = LUT_breakpoints_array};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(LUT_data_array), .data = LUT_data_array};
    uz_LUT_1D_t *instance = uz_LUT_1D_init(&breakpoints_array, &data_array);

    float output = uz_LUT_1D_get_value(instance, 1.5f);
    float expected = 6.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);

    output = uz_LUT_1D_get_value(instance, -1.0f);
    expected = 10.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);

    output = uz_LUT_1D_get_value(instance, 5.0f);
    expected = 6.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}

void test_uz_LUT_1D_get_linear_interpolated_value(void)
{
    float LUT_breakpoints_array[6] = {0.0f, 1.0f, 2.0f,  3.0f,  4.0f,  5.0f};
    float LUT_data_array[6]        = {0.0f, 5.0f, 10.0f, 15.0f, 20.0f, 25.0f};
    uz_array_float_t breakpoints_array = {.length = UZ_ARRAY_SIZE(LUT_breakpoints_array), .data = LUT_breakpoints_array};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(LUT_data_array), .data = LUT_data_array};
    uz_LUT_1D_t *instance = uz_LUT_1D_init(&breakpoints_array, &data_array);
    float output = uz_LUT_1D_get_value(instance, 1.5f);
    float expected = 7.5f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}

void test_uz_LUT_1D_get_linear_interpolated_value_negative(void)
{
    float LUT_breakpoints_array[6] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float LUT_data_array[6] = {0.0f, -5.0f, -10.0f, -15.0f, -20.0f, -25.0f};
    uz_array_float_t breakpoints_array = {.length = UZ_ARRAY_SIZE(LUT_breakpoints_array), .data = LUT_breakpoints_array};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(LUT_data_array), .data = LUT_data_array};
    uz_LUT_1D_t *instance = uz_LUT_1D_init(&breakpoints_array, &data_array);
    float output = uz_LUT_1D_get_value(instance, 1.5f);
    float expected = -7.5f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}

void test_uz_LUT_1D_get_value_exact_interior_breakpoint(void)
{
    float LUT_breakpoints_array[5] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    float LUT_data_array[5] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f};
    uz_array_float_t breakpoints_array = {.length = UZ_ARRAY_SIZE(LUT_breakpoints_array), .data = LUT_breakpoints_array};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(LUT_data_array), .data = LUT_data_array};
    uz_LUT_1D_t *instance = uz_LUT_1D_init(&breakpoints_array, &data_array);
    float output = uz_LUT_1D_get_value(instance, 2.0f);
    float expected = 4.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}


void test_uz_LUT_1D_get_value_out_of_bounds_clamps_to_endpoints(void)
{
    float breakpoints20[20] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f};
    float data20[20] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f, 34.0f, 36.0f, 38.0f};

    uz_array_float_t breakpoints_array20 = {.length = UZ_ARRAY_SIZE(breakpoints20), .data = breakpoints20};
    uz_array_float_t data_array20 = {.length = UZ_ARRAY_SIZE(data20), .data = data20};

    uz_LUT_1D_t *instance = uz_LUT_1D_init(&breakpoints_array20, &data_array20);

    float output = uz_LUT_1D_get_value(instance, -100.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, data20[0], output);

    output = uz_LUT_1D_get_value(instance, 100.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, data20[UZ_ARRAY_SIZE(data20) - 1U], output);
}

void test_uz_LUT_1D_Assert_duplicate_breakpoints(void)
{
    float duplicate_breakpoints[3] = {0.0f, 0.0f, 1.0f};
    float duplicate_data[3] = {1.0f, 2.0f, 3.0f};
    uz_array_float_t breakpoints_array = {.length = UZ_ARRAY_SIZE(duplicate_breakpoints), .data = duplicate_breakpoints};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(duplicate_data), .data = duplicate_data};
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(&breakpoints_array, &data_array));
}

#endif // TEST
