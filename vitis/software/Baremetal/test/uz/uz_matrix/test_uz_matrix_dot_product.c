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

void test_uz_matrix_dot_product_1d(void){
    int rows=1;
    int columns=4;
    float A_data[4]={1,2,3,4};
    float B_data[4]={1,2,3,4};
    uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),rows, columns );
    uz_matrix_t* B=uz_matrix_init(B_data,UZ_MATRIX_SIZE(B_data),rows, columns );
    float C=uz_matrix_dot_product(A,B);
    TEST_ASSERT_EQUAL_FLOAT(30,C);
}

#endif // TEST
