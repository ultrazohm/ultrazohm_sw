#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_LUT_2D.h"
#include <math.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_LUT_2D_successful_init(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 2.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 2.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    uz_LUT_2D_t *instance = uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_LUT_2D_init_assert_null_breakpoints_x(void)
{
    float breakpoints_y[2] = {0.0f, 1.0f};
    float data[4] = {0.0f, 1.0f, 1.0f, 2.0f};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(NULL, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_null_breakpoints_y(void)
{
    float breakpoints_x[2] = {0.0f, 1.0f};
    float data[4] = {0.0f, 1.0f, 1.0f, 2.0f};
    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, NULL, &data_array));
}

void test_uz_LUT_2D_init_assert_null_data(void)
{
    float breakpoints_x[2] = {0.0f, 1.0f};
    float breakpoints_y[2] = {0.0f, 1.0f};
    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, NULL));
}

void test_uz_LUT_2D_init_assert_null_data_pointer(void)
{
    float breakpoints_x[2] = {0.0f, 1.0f};
    float breakpoints_y[2] = {0.0f, 1.0f};
    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = 4U, .data = NULL};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_null_breakpoints_x_data_pointer(void)
{
    float breakpoints_y[2] = {0.0f, 1.0f};
    float data[4] = {0.0f, 1.0f, 1.0f, 2.0f};
    float breakpoints_x_dummy[2] = {0.0f, 1.0f};
    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x_dummy), .data = NULL};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_null_breakpoints_y_data_pointer(void)
{
    float breakpoints_x[2] = {0.0f, 1.0f};
    float data[4] = {0.0f, 1.0f, 1.0f, 2.0f};
    float breakpoints_y_dummy[2] = {0.0f, 1.0f};
    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y_dummy), .data = NULL};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_breakpoints_x_not_increasing(void)
{
    float breakpoints_x[3] = {0.0f, 2.0f, 1.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 2.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_breakpoints_y_not_increasing(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 2.0f};
    float breakpoints_y[3] = {0.0f, 2.0f, 1.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_duplicate_breakpoints_x(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 1.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 2.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_duplicate_breakpoints_y(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 2.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 1.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_breakpoints_x_length_one(void)
{
    float breakpoints_x[1] = {0.0f};
    float breakpoints_y[2] = {0.0f, 1.0f};
    float data[2] = {0.0f, 1.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_breakpoints_y_length_one(void)
{
    float breakpoints_x[2] = {0.0f, 1.0f};
    float breakpoints_y[1] = {0.0f};
    float data[2] = {0.0f, 1.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_init_assert_data_length_mismatch(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 2.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 2.0f};
    float data[8] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array));
}

void test_uz_LUT_2D_get_value_assert_null_instance(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_LUT_2D_get_value(NULL, 0.0f, 0.0f));
}

void test_uz_LUT_2D_get_value_bilinear_interpolation(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 2.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 2.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    uz_LUT_2D_t *instance = uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array);

    float output = uz_LUT_2D_get_value(instance, 0.5f, 0.5f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 1.0f, output);

    output = uz_LUT_2D_get_value(instance, 1.5f, 0.5f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 2.0f, output);

    output = uz_LUT_2D_get_value(instance, 1.5f, 1.5f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 3.0f, output);
}

void test_uz_LUT_2D_get_value_exact_grid_point(void)
{
    float breakpoints_x[4] = {0.0f, 1.0f, 2.0f, 3.0f};
    float breakpoints_y[3] = {0.0f, 2.0f, 4.0f};
    float data[12] = {
        0.0f, 1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f, 5.0f,
        4.0f, 5.0f, 6.0f, 7.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    uz_LUT_2D_t *instance = uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array);

    float output = uz_LUT_2D_get_value(instance, 2.0f, 2.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 4.0f, output);
}

void test_uz_LUT_2D_get_value_two_by_two_table(void)
{
    float breakpoints_x[2] = {0.0f, 2.0f};
    float breakpoints_y[2] = {0.0f, 4.0f};
    float data[4] = {
        0.0f, 2.0f,
        4.0f, 6.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    uz_LUT_2D_t *instance = uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array);

    float output = uz_LUT_2D_get_value(instance, 1.0f, 2.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 3.0f, output);

    output = uz_LUT_2D_get_value(instance, 2.0f, 4.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 6.0f, output);
}

void test_uz_LUT_2D_get_value_clamps_out_of_bounds(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 2.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 2.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    uz_LUT_2D_t *instance = uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array);

    float output = uz_LUT_2D_get_value(instance, -10.0f, -10.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 0.0f, output);

    output = uz_LUT_2D_get_value(instance, 10.0f, 10.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 4.0f, output);

    output = uz_LUT_2D_get_value(instance, -1.0f, 1.5f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 1.5f, output);

    output = uz_LUT_2D_get_value(instance, 1.25f, 5.0f);
    TEST_ASSERT_FLOAT_WITHIN(1e-06f, 3.25f, output);
}

void test_uz_LUT_2D_get_value_nan_input_returns_nan(void)
{
    float breakpoints_x[3] = {0.0f, 1.0f, 2.0f};
    float breakpoints_y[3] = {0.0f, 1.0f, 2.0f};
    float data[9] = {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f};

    uz_array_float_t breakpoints_array_x = {.length = UZ_ARRAY_SIZE(breakpoints_x), .data = breakpoints_x};
    uz_array_float_t breakpoints_array_y = {.length = UZ_ARRAY_SIZE(breakpoints_y), .data = breakpoints_y};
    uz_array_float_t data_array = {.length = UZ_ARRAY_SIZE(data), .data = data};

    uz_LUT_2D_t *instance = uz_LUT_2D_init(&breakpoints_array_x, &breakpoints_array_y, &data_array);

    float output = uz_LUT_2D_get_value(instance, NAN, 1.0f);
    TEST_ASSERT_TRUE(isnan(output));

    output = uz_LUT_2D_get_value(instance, 1.0f, NAN);
    TEST_ASSERT_TRUE(isnan(output));
}

#endif // TEST
