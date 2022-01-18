#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_matrix.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_matrix_vector_elementwise_multiplication_3_times_1(void){
    size_t rows=3;
    size_t columns=1;
    float A_data[3]={1,2,3};
    float B_data[3]={1,2,3};
    float C_data[3]={134513};
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=uz_matrix_init(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=uz_matrix_init(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A .* B
    uz_matrix_elementwise_product(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(C,0,0));
    TEST_ASSERT_EQUAL_FLOAT(4,uz_matrix_get_element_zero_based(C,1,0));
    TEST_ASSERT_EQUAL_FLOAT(9,uz_matrix_get_element_zero_based(C,2,0));
}

void test_uz_matrix_matrix_elementwise_multiplication_2_times_2(void){
    size_t rows=2;
    size_t columns=2;
    // | 1 2 | .* | 1 2 | = | 1 4  |
    // | 3 4 |    | 3 4 |   | 9 16 |
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    float C_data[4]={63};
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=uz_matrix_init(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=uz_matrix_init(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A .* B
    uz_matrix_elementwise_product(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(1, uz_matrix_get_element_zero_based(C,0,0));
    TEST_ASSERT_EQUAL_FLOAT(4, uz_matrix_get_element_zero_based(C,0,1));
    TEST_ASSERT_EQUAL_FLOAT(9, uz_matrix_get_element_zero_based(C,1,0));
    TEST_ASSERT_EQUAL_FLOAT(16,uz_matrix_get_element_zero_based(C,1,1));
}

void test_uz_matrix_matrix_elementwise_multiplication_1_times_4(void){
    size_t rows=1;
    size_t columns=4;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    float C_data[4]={21345};
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=uz_matrix_init(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    uz_matrix_t* C=uz_matrix_init(C_data,UZ_MATRIX_SIZE(C_data),rows, columns );
    // C=A .* B
    uz_matrix_elementwise_product(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(1, uz_matrix_get_element_zero_based(C,0,0) );
    TEST_ASSERT_EQUAL_FLOAT(4, uz_matrix_get_element_zero_based(C,0,1) );
    TEST_ASSERT_EQUAL_FLOAT(9, uz_matrix_get_element_zero_based(C,0,2) );
    TEST_ASSERT_EQUAL_FLOAT(16,uz_matrix_get_element_zero_based(C,0,3) );
}

#endif // TEST
