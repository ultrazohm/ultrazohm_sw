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

void test_uz_matrix_matrix_multiply(void){
    float A_data[6]={1,2,3,4,5,6};
    float B_data[4]={2,1,8,5};
    float C_data[6]={5};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),3, 2 );
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(A,0,0));
    TEST_ASSERT_EQUAL_FLOAT(2,uz_matrix_get_element_zero_based(A,0,1));
    TEST_ASSERT_EQUAL_FLOAT(3,uz_matrix_get_element_zero_based(A,1,0));

    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),2, 2 );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),3, 2 );
    // C=A * B
    uz_matrix_multiply(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(18,uz_matrix_get_element_zero_based(C,0,0) );
    TEST_ASSERT_EQUAL_FLOAT(11,uz_matrix_get_element_zero_based(C,0,1) );
    TEST_ASSERT_EQUAL_FLOAT(38,uz_matrix_get_element_zero_based(C,1,0) );
    TEST_ASSERT_EQUAL_FLOAT(23,uz_matrix_get_element_zero_based(C,1,1) );
    TEST_ASSERT_EQUAL_FLOAT(58,uz_matrix_get_element_zero_based(C,2,0) );
    TEST_ASSERT_EQUAL_FLOAT(35,uz_matrix_get_element_zero_based(C,2,1) );
}
void test_uz_matrix_matrix_multiply_scalar_result(void){
    float A_data[3]={1,2,3};
    float B_data[3]={1,2,3};
    float C_data[1]={5};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),1, 3 );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),3, 1 );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),1, 1 );
    // C=A * B
    uz_matrix_multiply(A,B, C);
    TEST_ASSERT_EQUAL_FLOAT(14,uz_matrix_get_element_zero_based(C,0,0) );
}

void test_uz_matrix_matrix_multiply_extend_matrix(void){
    float A_data[3]={1,2,3};
    float B_data[3]={1,2,3};
    float C_data[9]={5};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),1, 3 );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),3, 1 );
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),3, 3 );
    // C=A * B
    uz_matrix_multiply(B,A, C);
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(C,0,0) );
}

void test_uz_matrix_columnvec_concatenate_horizontal(void){
    float A_data[3]={1,2,3};
    float B_data[4]={4,5,6,7};
    float C_data[7]={0};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),3,1);
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),4,1);
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),7,1);
    uz_matrix_columnvec_concatenate_horizontal(A,B,C);
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(C,0,0));
    TEST_ASSERT_EQUAL_FLOAT(2,uz_matrix_get_element_zero_based(C,1,0));
    TEST_ASSERT_EQUAL_FLOAT(3,uz_matrix_get_element_zero_based(C,2,0));
    TEST_ASSERT_EQUAL_FLOAT(4,uz_matrix_get_element_zero_based(C,3,0));
    TEST_ASSERT_EQUAL_FLOAT(5,uz_matrix_get_element_zero_based(C,4,0));
    TEST_ASSERT_EQUAL_FLOAT(6,uz_matrix_get_element_zero_based(C,5,0));
    TEST_ASSERT_EQUAL_FLOAT(7,uz_matrix_get_element_zero_based(C,6,0));
}

void test_uz_matrix_reshape_1d(void){
    float A_data[6]={1,2,3,4,5,6};
    float B_data[4]={7,8,9,10};
    float C_data[10]={0};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),3,2);
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),4,1);
    uz_matrix_t* C=init_array_test_helper(C_data,UZ_MATRIX_SIZE(C_data),10,1);
    uz_matrix_reshape_and_concatenate(A,B,C);
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(C,0,0));
    TEST_ASSERT_EQUAL_FLOAT(3,uz_matrix_get_element_zero_based(C,1,0));
    TEST_ASSERT_EQUAL_FLOAT(5,uz_matrix_get_element_zero_based(C,2,0));
    TEST_ASSERT_EQUAL_FLOAT(2,uz_matrix_get_element_zero_based(C,3,0));
    TEST_ASSERT_EQUAL_FLOAT(4,uz_matrix_get_element_zero_based(C,4,0));
    TEST_ASSERT_EQUAL_FLOAT(6,uz_matrix_get_element_zero_based(C,5,0));
    TEST_ASSERT_EQUAL_FLOAT(7,uz_matrix_get_element_zero_based(C,6,0));
    TEST_ASSERT_EQUAL_FLOAT(8,uz_matrix_get_element_zero_based(C,7,0));
    TEST_ASSERT_EQUAL_FLOAT(9,uz_matrix_get_element_zero_based(C,8,0));
    TEST_ASSERT_EQUAL_FLOAT(10,uz_matrix_get_element_zero_based(C,9,0));
}

#endif // TEST
