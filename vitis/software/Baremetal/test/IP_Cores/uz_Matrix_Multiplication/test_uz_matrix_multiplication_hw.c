#ifdef TEST
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_matrix_multiplication_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x000000420 // random hex value that represents a fictional base address

#include "unity.h"
#include "uz_matrix_multiplication_hw.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_matrix_multiplication_hw_set_A_rows_assert_zero_base_address(void) { 
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_set_A_rows(0x0U, 4U));
}  

void test_uz_matrix_multiplication_hw_set_A_rows(void) {
    uint32_t rows = 4U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA, rows);
    uz_matrix_multiplication_hw_set_A_rows(TEST_BASE_ADDRESS, rows);
}

void test_uz_matrix_multiplication_hw_set_B_rows_assert_zero_base_address(void) { 
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_set_B_rows(0x0U, 4U));
}  

void test_uz_matrix_multiplication_hw_set_B_rows(void) {
    uint32_t rows = 4U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA, rows);
    uz_matrix_multiplication_hw_set_B_rows(TEST_BASE_ADDRESS, rows);
}

void test_uz_matrix_multiplication_hw_set_B_columns_assert_zero_base_address(void) { 
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_set_B_columns(0x0U, 4U));
}  

void test_uz_matrix_multiplication_hw_set_B_columns(void) {
    uint32_t columns = 4U;
    uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA, columns);
    uz_matrix_multiplication_hw_set_B_columns(TEST_BASE_ADDRESS, columns);
}

void test_uz_matrix_multiplication_hw_set_A_matrix_assert_zero_base_address(void) {
    float A_matrix[5] = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_set_A_matrix(0x0U, &A_matrix[0]));
}

void test_uz_matrix_multiplication_hw_set_A_matrix_assert_NULL_Array(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_set_A_matrix(TEST_BASE_ADDRESS, NULL));
}

void test_uz_matrix_multiplication_hw_set_A_matrix(void) {
    float A_matrix[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    for (uint32_t i = 0U; i < 5U; i++) {
        uz_axi_write_float_Expect(TEST_BASE_ADDRESS + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + 4U * i, A_matrix[i]);
    }
     uz_matrix_multiplication_hw_set_A_matrix(TEST_BASE_ADDRESS, &A_matrix[0]);   
    
}

void test_uz_matrix_multiplication_hw_set_B_matrix_assert_zero_base_address(void) {
    float B_matrix[5] = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_set_B_matrix(0x0U, &B_matrix[0]));
}

void test_uz_matrix_multiplication_hw_set_B_matrix_assert_NULL_Array(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_set_B_matrix(TEST_BASE_ADDRESS, NULL));
}

void test_uz_matrix_multiplication_hw_set_B_matrix(void) {
    float B_matrix[25] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 90.f, 10.0f, 11.0f, 12.0f, 1.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f, 24.0f, 25.0f};
    for (uint32_t i = 0U; i < 25U; i++) {
        uz_axi_write_float_Expect(TEST_BASE_ADDRESS + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + 4U * i, B_matrix[i]);
    }
     uz_matrix_multiplication_hw_set_B_matrix(TEST_BASE_ADDRESS, &B_matrix[0]);   
    
}

void test_uz_matrix_multiplication_hw_read_C_out_matrix_assert_zero_base_address(void) {
    float C_out[5] = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_read_C_out_matrix(0x0, &C_out[0]));
}

void test_uz_matrix_multiplication_hw_read_C_out_matrix_assert_NULL_array(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_multiplication_hw_read_C_out_matrix(TEST_BASE_ADDRESS, NULL));
}

void test_uz_matrix_multiplication_hw_read_C_out_matrix(void) {
    float C_out[5] = {0};
    float C_expected[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    for (uint32_t i = 0U; i < 5U; i++) {
        uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE +4U * i, C_expected[i]);
    }
    uz_matrix_multiplication_hw_read_C_out_matrix(TEST_BASE_ADDRESS, &C_out[0]);
    for (uint32_t i = 0U; i < 5U; i++) {
        TEST_ASSERT_EQUAL_FLOAT(C_expected[i], C_out[i]);
    }
}

#endif // TEST
