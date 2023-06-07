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

void test_uz_matrix_set_matrix_to_zero(void){
    uint32_t rows=2;
    uint32_t columns=2;
    float A_data[4]={1,2,3,4};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_set_zero(A);
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,0,0));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,0,1));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,1,0));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,1,1));

}


void test_uz_matrix_set_unity_matrix(void){
    uint32_t rows=2;
    uint32_t columns=2;
    float A_data[4]={1,2,3,4};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_set_unity_matrix(A);
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(A,0,0));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,0,1));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,1,0));
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(A,1,1));

}

void test_uz_matrix_set_zero_except_diagonal(void){
    uint32_t rows=3;
    uint32_t columns=3;
    float A_data[9]={1,2,3,4,5,6,7,8,9};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns);
    uz_matrix_set_zero_except_diagonal(A);
    TEST_ASSERT_EQUAL_FLOAT(1,uz_matrix_get_element_zero_based(A,0,0));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,0,1));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,0,2));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,1,0));
    TEST_ASSERT_EQUAL_FLOAT(5,uz_matrix_get_element_zero_based(A,1,1));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,1,2));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,2,0));
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,2,1));
    TEST_ASSERT_EQUAL_FLOAT(9,uz_matrix_get_element_zero_based(A,2,2));
}

void test_uz_matrix_set_columnvector_as_diagonal(void){
    uint32_t rows=2;
    uint32_t columns=2;
    float A_data[4]={1,2,3,4};
    float vec_data[2]={5,10};
    uz_matrix_t* vector=init_array_test_helper(vec_data,UZ_MATRIX_SIZE(vec_data),1, columns);
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns);
    uz_matrix_set_columnvector_as_diagonal(A,vector);
    TEST_ASSERT_EQUAL_FLOAT(5,uz_matrix_get_element_zero_based(A,0,0));
    TEST_ASSERT_EQUAL_FLOAT(10,uz_matrix_get_element_zero_based(A,1,1));
}

void test_uz_matrix_set_rowvector_as_diagonal(void){
    uint32_t rows=2;
    uint32_t columns=2;
    float A_data[4]={1,2,3,4};
    float vec_data[2]={25,100};
    uz_matrix_t* vector=init_array_test_helper(vec_data,UZ_MATRIX_SIZE(vec_data),rows, 1);
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns);
    uz_matrix_set_columnvector_as_diagonal(A,vector);
    TEST_ASSERT_EQUAL_FLOAT(25,uz_matrix_get_element_zero_based(A,0,0));
    TEST_ASSERT_EQUAL_FLOAT(100,uz_matrix_get_element_zero_based(A,1,1));
}
#endif // TEST
