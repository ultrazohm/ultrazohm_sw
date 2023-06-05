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

void test_uz_matrix_vector_elementwise_multiplication_3_times_1(void){
    uint32_t rows=3;
    uint32_t columns=1;
    float A_data[3]={1,2,3};
    float B_data[3]={1,2,3};
    float C_data[3]={134513};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A .* B
    uz_matrix_elementwise_product(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(C,0,0));
    TEST_ASSERT_EQUAL_FLOAT(4,uz_matrix_get_element_zero_based(C,1,0));
    TEST_ASSERT_EQUAL_FLOAT(9,uz_matrix_get_element_zero_based(C,2,0));
}

void test_uz_matrix_matrix_elementwise_multiplication_2_times_2(void){
    uint32_t rows=2;
    uint32_t columns=2;
    // | 1 2 | .* | 1 2 | = | 1 4  |
    // | 3 4 |    | 3 4 |   | 9 16 |
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    float C_data[4]={63};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A .* B
    uz_matrix_elementwise_product(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(1, uz_matrix_get_element_zero_based(C,0,0));
    TEST_ASSERT_EQUAL_FLOAT(4, uz_matrix_get_element_zero_based(C,0,1));
    TEST_ASSERT_EQUAL_FLOAT(9, uz_matrix_get_element_zero_based(C,1,0));
    TEST_ASSERT_EQUAL_FLOAT(16,uz_matrix_get_element_zero_based(C,1,1));
}

void test_uz_matrix_matrix_elementwise_multiplication_1_times_4(void){
    uint32_t rows=1;
    uint32_t columns=4;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    float C_data[4]={21345};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A .* B
    uz_matrix_elementwise_product(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(1, uz_matrix_get_element_zero_based(C,0,0) );
    TEST_ASSERT_EQUAL_FLOAT(4, uz_matrix_get_element_zero_based(C,0,1) );
    TEST_ASSERT_EQUAL_FLOAT(9, uz_matrix_get_element_zero_based(C,0,2) );
    TEST_ASSERT_EQUAL_FLOAT(16,uz_matrix_get_element_zero_based(C,0,3) );
}

void test_uz_matrix_matrix_elementwise_matlab_multiplication_schroeder(void){
    float A_data[2]={0.0f,0.6f};
    float B_data[4]={-0.02f,-0.78f,5.36f,-1.26f};
    float C_data[4]={0.0f};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),2, 1 );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),2, 2 );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),2, 2 );
    // // C=A .* B
    uz_matrix_matlab_elementwise_product(A,B,C);
    TEST_ASSERT_FLOAT_WITHIN(1e-02f, 0.0f, uz_matrix_get_element_zero_based(C,0,0) );
    TEST_ASSERT_FLOAT_WITHIN(1e-02f,0.0f, uz_matrix_get_element_zero_based(C,0,1) );
    TEST_ASSERT_FLOAT_WITHIN(1e-02f,3.22f, uz_matrix_get_element_zero_based(C,1,0) );
    TEST_ASSERT_FLOAT_WITHIN(1e-02f,-0.76f ,uz_matrix_get_element_zero_based(C,1,1) );
}
#endif // TEST
