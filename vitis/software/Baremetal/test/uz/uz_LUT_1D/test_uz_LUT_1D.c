#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_LUT_1D.h"
#include "uz_array.h"

float breakpoints5[5] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
float data5[5] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f};
float breakpoints20[20] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f};
float data20[20] = {0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f, 34.0f, 36.0f, 38.0f};

uz_array_float_t breakpoints_array5 = {.length = 5U, .data = breakpoints5};
uz_array_float_t data_array5 = {.length = 5U, .data = data5};
uz_array_float_t breakpoints_array20 = {.length = 20U, .data = breakpoints20};
uz_array_float_t data_array20 = {.length = 20U, .data = data20};
void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_LUT_1D_Successfull_Init(void)
{
    uz_LUT_1D_t* instance = uz_LUT_1D_init(&breakpoints_array5, &data_array5, 5U);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_LUT_1D_Assert_Breakpoints_Null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(NULL, &data_array5, 5U));
}

void test_uz_LUT_1D_Assert_Data_Null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(&breakpoints_array5, NULL, 5U));
}

void test_uz_LUT_1D_Successfull_length_unequal_to_array_length(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(&breakpoints_array5, &data_array5, 6U));
}

void test_uz_LUT_1D_Successfull_array_length_mismatch(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_init(&breakpoints_array5, &data_array20, 5U));
}

void test_uz_LUT_1D_get_value_assert_Null(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_1D_get_value(NULL, 1.0f));
}

void test_uz_LUT_1D_get_value_5values(void) {
    uz_LUT_1D_t* instance = uz_LUT_1D_init(&breakpoints_array5, &data_array5, 5U);
    float output = uz_LUT_1D_get_value(instance, 1.0f);
    float expected = 2.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    //lin interpolation
    output = uz_LUT_1D_get_value(instance, 2.5f);
    expected = 5.0f;
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    //out of bounds
    output = uz_LUT_1D_get_value(instance, -1.0f);
    expected = 0.0f;//min value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    output = uz_LUT_1D_get_value(instance, 5.0f);
    expected = 8.0f;//Max value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}

void test_uz_LUT_1D_get_value_20values(void) {
    uz_LUT_1D_t* instance = uz_LUT_1D_init(&breakpoints_array20, &data_array20, 20U);
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
    expected = 0.0f;//min value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
    output = uz_LUT_1D_get_value(instance, 22.0f);
    expected = 38.0f;//Max value of data array
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, expected, output);
}


#endif // TEST
