#ifdef TEST

#include "unity.h"

#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"

#define NUMBER_OF_INPUTS 2
#define NUMBER_OF_OUTPUTS 1
#define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 3

float mse1[1] = {5};
float mse2[1] = {4};
float bmse3[3] = {8,7,9};
float bmse4[3] = {12,14,28};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_mse_one(void)
{
    struct uz_matrix_t testmatrix1={0};
    uz_matrix_t* test1=uz_matrix_init(&testmatrix1, mse1,UZ_MATRIX_SIZE(mse1),1,UZ_MATRIX_SIZE(mse1));
    struct uz_matrix_t testmatrix2={0};
    uz_matrix_t* test2=uz_matrix_init(&testmatrix2, mse2,UZ_MATRIX_SIZE(mse2),1,UZ_MATRIX_SIZE(mse2));
    float msetest =  uz_nn_mse(test1,test2);
    float expected_result = 1;
    TEST_ASSERT_EQUAL_FLOAT(expected_result, msetest);
}
void test_uz_nn_mse_three(void)
{
    struct uz_matrix_t testmatrix3={0};
    uz_matrix_t* test3=uz_matrix_init(&testmatrix3, bmse3,UZ_MATRIX_SIZE(bmse3),1,UZ_MATRIX_SIZE(bmse3));
    struct uz_matrix_t testmatrix4={0};
    uz_matrix_t* test4=uz_matrix_init(&testmatrix4, bmse4,UZ_MATRIX_SIZE(bmse4),1,UZ_MATRIX_SIZE(bmse4));
    float msetest2 =  uz_nn_mse(test3,test4);
    float expected_result = 142;
    TEST_ASSERT_EQUAL_FLOAT(expected_result, msetest2);
}
#endif // TEST
