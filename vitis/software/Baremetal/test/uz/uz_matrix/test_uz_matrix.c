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
    size_t rows=1U;
    size_t columns=3U;
    float test_vector[3]={1.0f,2.0f,3.0f};
    uz_matrix_init(test_vector,UZ_MATRIX_SIZE(test_vector),rows, columns );
}

void test_uz_matrix_init_wrong_data_dimension(void){
    size_t rows=3U;
    size_t columns=3U;
    float mat[6]={0}; // Mat needs to be of length 9, thus a assertion fires in the test
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_init(mat,UZ_MATRIX_SIZE(mat), rows,columns));
}

void test_uz_matrix_init_zero_rows(void){
    size_t rows=0U;
    size_t columns=3U;
    float mat[5]={0};
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_init(mat,UZ_MATRIX_SIZE(mat), rows,columns));
}

void test_uz_matrix_init_zero_columns(void){
    size_t rows=3U;
    size_t columns=0U;
    float mat[5]={0};
    TEST_ASSERT_FAIL_ASSERT(uz_matrix_init(mat,UZ_MATRIX_SIZE(mat), rows,columns));
}

void test_uz_matrix_init_3_times_3_matrix(void){
    size_t rows=3U;
    size_t columns=3U;
    float mat[9]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8,9};
    uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    
}

void test_uz_matrix_get_number_of_rows_and_columns(void){
    size_t rows=3U;
    size_t columns=2U;
    float mat[6]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
    uz_matrix_t* matrix=uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    size_t number_of_rows=uz_matrix_get_number_of_rows(matrix);
    size_t number_of_columns=uz_matrix_get_number_of_columns(matrix);
    TEST_ASSERT_EQUAL_INT(rows, number_of_rows);
    TEST_ASSERT_EQUAL_INT(columns, number_of_columns);
}

void test_uz_matrix_add_scalar(void){
    size_t rows=3U;
    size_t columns=3U;
    float mat[9]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f};
    uz_matrix_t* matrix=uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    float scalar=1.1f;
    uz_matrix_add_scalar(matrix,scalar);
    float expect[9]={2.1f,3.1f,4.1f,5.1f,6.1f,7.1f,8.1f,9.1f,10.1f};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expect,mat,UZ_MATRIX_SIZE(mat));
}

void test_uz_matrix_multiply_by_scalar(void){
    size_t rows=3U;
    size_t columns=3U;
    float mat[9]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f};
    uz_matrix_t* matrix=uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    float scalar=1.1f;
    uz_matrix_multiply_by_scalar(matrix,scalar);
    float expect[9]={1.1f,2.2f,3.3f,4.4f,5.5f,6.6f,7.7f,8.8f,9.9f};
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
    float A_data[6]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
    float B_data[6]={1.0f,3.0f,5.0f,2.0f,4.0f,6.0f};
    float C_data[9]={0};
    float C_expected[9]={5.0f,11.0f,17.0f,11.0f,25.0f,39.0f,17.0f,39.0f,61.0f};
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),3,2);
    uz_matrix_t* B=uz_matrix_init(B_data,UZ_MATRIX_SIZE(B_data),2,3);
    uz_matrix_t* C=uz_matrix_init(C_data,UZ_MATRIX_SIZE(C_data),3,3);
    uz_matrix_multiply(A,B,C);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(C_expected,C_data,UZ_MATRIX_SIZE(C_expected));
}

void test_uz_matrix_apply_function_to_each_element(void){
    float (*fcn_pointer)(float);
    fcn_pointer=&uz_nn_activation_function_relu;
    float A_data[5]={1.0f,-1.0f,2.0f,-2.0f,5.0f};
    float expected[5]={1.0f,0.0f,2.0f,0.0f,5.0f}; // Relu function just sets every element that is negative to zero
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),1,5);
    uz_matrix_apply_function_to_each_element(A,fcn_pointer);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected,A_data,UZ_MATRIX_SIZE(expected));
}

void test_uz_matrix_get_max_element_value(void){
    float A_data[9]={1.0f, 3.0f, 5.0f, 9.0f, 1.0f, 1.0f, 1.0f, 2.0f,6.0f};
    float expected_maximum=9.0f;
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),1,9);
    float actual=uz_matrix_get_max_value(A);
    TEST_ASSERT_EQUAL_FLOAT(expected_maximum,actual);
}

void test_uz_matrix_get_max_index(void){
    float A_data[9]={1.0f, 3.0f, 5.0f, 9.0f, 1.0f, 1.0f, 1.0f, 2.0f,6.0f};
    size_t expected_maximum=3U;
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),1,9);
    size_t actual=uz_matrix_get_max_index(A);
    TEST_ASSERT_EQUAL_UINT32(expected_maximum,actual);
}


void test_uz_matrix_transpose(void){
    size_t rows=3;
    size_t columns=5;
    float A_data[15]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    // Initial 3x5
    // 1  2  3  4  5
    // 6  7  8  9  10
    // 11 12 13 14 15

    float expected[15]={1, 6, 11,2,7,12,3,8,13,4,9,14,5,10,15};
    // Transposed 5x3
    // 1 6 11
    // 2 7 12
    // 3 8 13
    // 4 9 14
    // 5 10 15


    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),rows,columns);
    uz_matrix_transpose(A);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected,A_data,UZ_MATRIX_SIZE(expected));

}

#endif // TEST
