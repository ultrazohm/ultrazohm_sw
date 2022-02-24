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

void test_uz_matrix_dot_product_two_column_vectors(void){
    size_t rows=1;
    size_t columns=4;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    float C=uz_matrix_dot_product(A,B);
    TEST_ASSERT_EQUAL_FLOAT(30,C);
}

void test_uz_matrix_dot_product_two_row_vectors(void){
    size_t rows=4;
    size_t columns=1;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_dot_product(A,B));
}

void test_uz_matrix_dot_product_wrong_dimensions(void){
    size_t rows=2;
    size_t columns=2;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    uz_matrix_t* A=init_array_test_helper(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=init_array_test_helper(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_dot_product(A,B));
}

#endif // TEST
