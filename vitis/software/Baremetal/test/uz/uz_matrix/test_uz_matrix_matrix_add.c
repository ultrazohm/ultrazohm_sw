#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_matrix.h"
#include "uz_matrix_init_helper.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_matrix_matrix_add_column_vector(void){
    size_t rows=1;
    size_t columns=4;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    float C_data[4]={113};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A + B
    uz_matrix_sum(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(2,uz_matrix_get_element_zero_based(C,0,0));
    TEST_ASSERT_EQUAL_FLOAT(4,uz_matrix_get_element_zero_based(C,0,1));
    TEST_ASSERT_EQUAL_FLOAT(6,uz_matrix_get_element_zero_based(C,0,2));
    TEST_ASSERT_EQUAL_FLOAT(8,uz_matrix_get_element_zero_based(C,0,3));
}

void test_uz_matrix_matrix_add_row_vector(void){
    size_t rows=4;
    size_t columns=1;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    float C_data[4]={1523};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A + B
    uz_matrix_sum(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(2,uz_matrix_get_element_zero_based(C,0,0) );
    TEST_ASSERT_EQUAL_FLOAT(4,uz_matrix_get_element_zero_based(C,1,0) );
    TEST_ASSERT_EQUAL_FLOAT(6,uz_matrix_get_element_zero_based(C,2,0) );
    TEST_ASSERT_EQUAL_FLOAT(8,uz_matrix_get_element_zero_based(C,3,0) );
}

void test_uz_matrix_matrix_add_2_times2(void){
    size_t rows=2;
    size_t columns=2;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    float C_data[4]={4286};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A + B
    uz_matrix_sum(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(2,uz_matrix_get_element_zero_based(C,0,0) );
    TEST_ASSERT_EQUAL_FLOAT(4,uz_matrix_get_element_zero_based(C,0,1) );
    TEST_ASSERT_EQUAL_FLOAT(6,uz_matrix_get_element_zero_based(C,1,0) );
    TEST_ASSERT_EQUAL_FLOAT(8,uz_matrix_get_element_zero_based(C,1,1) );
}

#endif // TEST