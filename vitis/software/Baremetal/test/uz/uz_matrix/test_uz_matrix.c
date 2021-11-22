#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_matrix.h"
#include "uz_nn_activation_functions.h" // used for uz_matrix_apply_function_to_each_element test

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_matrix_init_1d_vector(void)
{
    int rows=1;
    int columns=3;
    float test_vector[3]={1,2,3};
    uz_matrix_init(test_vector,UZ_MATRIX_SIZE(test_vector),rows, columns );
}

void test_uz_matrix_init_wrong_data_dimension(void){
    int rows=3;
    int columns=3;
    float mat[6]={0}; // Mat needs to be of length 9, thus a assertion fires in the test
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_init(mat,UZ_MATRIX_SIZE(mat), rows,columns));
}

void test_uz_matrix_init_zero_rows(void){
    int rows=0;
    int columns=3;
    float mat[5]={0};
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_init(mat,UZ_MATRIX_SIZE(mat), rows,columns));
}

void test_uz_matrix_init_zero_columns(void){
    int rows=3;
    int columns=0;
    float mat[5]={0};
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_init(mat,UZ_MATRIX_SIZE(mat), rows,columns));
}

void test_uz_matrix_init_3_times_3_matrix(void){
    int rows=3;
    int columns=3;
    float mat[9]={1,2,3,4,5,6,7,8,9};
    uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    
}

void test_uz_matrix_get_number_of_rows_and_columns(void){
    int rows=3;
    int columns=2;
    float mat[6]={1,2,3,4,5,6};
    uz_matrix_t* matrix=uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    size_t number_of_rows=uz_matrix_get_number_of_rows(matrix);
    size_t number_of_columns=uz_matrix_get_number_of_columns(matrix);
    TEST_ASSERT_EQUAL_INT(rows, number_of_rows);
    TEST_ASSERT_EQUAL_INT(columns, number_of_columns);
}

void test_uz_matrix_add_scalar(void){
    int rows=3;
    int columns=3;
    float mat[9]={1,2,3,4,5,6,7,8,9};
    uz_matrix_t* matrix=uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    float scalar=1.1f;
    uz_matrix_add_scalar(matrix,scalar);
    float expect[9]={2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1,10.1};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expect,mat,UZ_MATRIX_SIZE(mat));
}

void test_uz_matrix_multiply_by_scalar(void){
    int rows=3;
    int columns=3;
    float mat[9]={1,2,3,4,5,6,7,8,9};
    uz_matrix_t* matrix=uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    float scalar=1.1f;
    uz_matrix_multiply_by_scalar(matrix,scalar);
    float expect[9]={1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expect,mat,UZ_MATRIX_SIZE(mat));
}

void test_uz_matrix_multiply_3_times_2(void){
    //          | 1 2 |
    // A (3x2)= | 3 4 |
    //          | 5 6 |
    //
    // B (2x3)= | 1 3 5 |
    //          | 2 4 6 |
    //
    //          | 5  11 17 |
    // C (3x3)= | 11 25 39 |
    //          | 17 39 61 |
    float A_data[6]={1,2,3,4,5,6};
    float B_data[6]={1,3,5,2,4,6};
    float C_data[9]={0};
    float C_expected[9]={5,11,17,11,25,39,17,39,61};
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),3,2);
    uz_matrix_t* B=uz_matrix_init(B_data,UZ_MATRIX_SIZE(B_data),2,3);
    uz_matrix_t* C=uz_matrix_init(C_data,UZ_MATRIX_SIZE(C_data),3,3);
    uz_matrix_multiply(A,B,C);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(C_expected,C_data,UZ_MATRIX_SIZE(C_expected));
}

void test_uz_matrix_apply_function_to_each_element(void){
    float (*fcn_pointer)(float);
    fcn_pointer=&uz_nn_activation_function_relu;
    float A_data[5]={1,-1,2,-2,5};
    float expected[5]={1,0,2,0,5}; // Relu function just sets every element that is negative to zero
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),1,5);
    uz_matrix_apply_function_to_each_element(A,fcn_pointer);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected,A_data,UZ_MATRIX_SIZE(expected));
}

#endif // TEST