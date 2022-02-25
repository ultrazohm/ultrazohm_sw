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
    TEST_ASSERT_EQUAL_FLOAT(0,uz_matrix_get_element_zero_based(A,0,1));

}

#endif // TEST
