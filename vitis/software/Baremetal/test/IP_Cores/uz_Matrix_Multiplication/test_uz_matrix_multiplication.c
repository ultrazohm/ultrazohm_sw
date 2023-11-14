#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_matrix_multiplication.h"
#include "uz_matrix.h"
#include "uz_matrix_multiplication_hwAddresses.h"
#include "mock_uz_matrix_multiplication_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>

#define TEST_BASE_ADDRESS 0x0000000F

float A_array[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
float B_array[25] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f, 24.0f, 25.0f};
float C_out_array[5] = {215.0f,230.0f,245.0f,260.0f,275.0f};
struct uz_Matrix_Multi_config config = {0};
void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS;
    config.A_columns = 5U;
    config.A_rows = 1U;
    config.A_length_of_data = UZ_MATRIX_SIZE(A_array);
    config.A_data = A_array;
    config.B_columns = 5U;
    config.B_rows = 5U;
    config.B_length_of_data = UZ_MATRIX_SIZE(B_array);
    config.B_data = B_array;
    config.C_columns = 5U;
    config.C_rows = 1U;
    config.C_length_of_data = UZ_MATRIX_SIZE(C_out_array);
    config.C_data = C_out_array;
}

void tearDown(void)
{
}

void test_uz_Matrix_Multi_init_assert_zero_base_address(void) {
    config.base_address = 0x0;
    uz_matrix_t A_matrix = {0};
    uz_matrix_t B_matrix = {0};
    uz_matrix_t C_out_matrix = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_Matrix_Multi_init(config, &A_matrix, &B_matrix, &C_out_matrix));
}

void test_uz_Matrix_Multi_init_assert_A_NULL(void) {
    uz_matrix_t B_matrix = {0};
    uz_matrix_t C_out_matrix = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_Matrix_Multi_init(config, NULL, &B_matrix, &C_out_matrix));
}

void test_uz_Matrix_Multi_init_assert_B_NULL(void) {
    uz_matrix_t A_matrix = {0};
    uz_matrix_t C_out_matrix = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_Matrix_Multi_init(config, &A_matrix, NULL, &C_out_matrix));
}

void test_uz_Matrix_Multi_init_assert_C_NULL(void) {
    uz_matrix_t A_matrix = {0};
    uz_matrix_t B_matrix = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_Matrix_Multi_init(config, &A_matrix, &B_matrix, NULL));
}

void test_uz_Matrix_Multi_write_input(void) {
    struct uz_matrix_t A_matrix = {0};
    struct uz_matrix_t B_matrix = {0};
    struct uz_matrix_t C_out_matrix = {0};
    uz_Matrix_Multi_t* instance = uz_Matrix_Multi_init(config, &A_matrix, &B_matrix, &C_out_matrix);
    uz_matrix_multiplication_hw_set_A_matrix_Expect(config.base_address, config.A_data);
    uz_matrix_multiplication_hw_set_A_rows_Expect(config.base_address, config.A_rows);
    uz_matrix_multiplication_hw_set_B_matrix_Expect(config.base_address, config.B_data);
    uz_matrix_multiplication_hw_set_B_rows_Expect(config.base_address, config.B_rows);
    uz_matrix_multiplication_hw_set_B_columns_Expect(config.base_address, config.B_columns);     
    uz_Matrix_Multi_write_input(instance);
}

void test_uz_Matrix_Multi_trigger_calculation_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_Matrix_Multi_trigger_calculation(NULL));
}

void test_uz_Matrix_Multi_read_output_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_Matrix_Multi_read_output(NULL));
}

void test_uz_Matrix_Multi_read_output(void) {
    struct uz_matrix_t A_matrix = {0};
    struct uz_matrix_t B_matrix = {0};
    struct uz_matrix_t C_out_matrix = {0};
    uz_Matrix_Multi_t* instance = uz_Matrix_Multi_init(config, &A_matrix, &B_matrix, &C_out_matrix);
    uz_matrix_multiplication_hw_set_A_matrix_Expect(config.base_address, config.A_data);
    uz_matrix_multiplication_hw_set_A_rows_Expect(config.base_address, config.A_rows);
    uz_matrix_multiplication_hw_set_B_matrix_Expect(config.base_address, config.B_data);
    uz_matrix_multiplication_hw_set_B_rows_Expect(config.base_address, config.B_rows);
    uz_matrix_multiplication_hw_set_B_columns_Expect(config.base_address, config.B_columns);     
    uz_Matrix_Multi_write_input(instance);
    uz_matrix_multiplication_hw_get_is_done_output_ExpectAndReturn(config.base_address, false);
    uz_Matrix_Multi_get_done_flag(instance);
    uz_matrix_multiplication_hw_read_C_out_matrix_Expect(config.base_address, config.C_data);
    uz_Matrix_Multi_read_output(instance);
}
#endif // TEST
