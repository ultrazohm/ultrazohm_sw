#ifdef TEST

#include "unity.h"

#include "uz_VSD_9ph_ML_MT_Control.h"
#include "uz_VSD_9ph_ML_MT_Control.c"

void setUp(void)
{
}

void test_fault_indices_to_OPF_index(void){
        uz_9ph_abc_t indices = {
            .a1 = 1.0f,//LSB
            .b1 = 0.0f,
            .c1 = 1.0f,
            .a2 = 1.0f,
            .b2 = 0.0f,
            .c2 = 0.0f,
            .a3 = 1.0f,
            .b3 = 0.0f,
            .c3 = 0.0f};//MSB
    uint16_t OPF_index = fault_indices_to_OPF_index(indices);
    TEST_ASSERT_EQUAL(OPF_index, 77); //=0b001001101
}

void test_return_k_param_set(void){
    uz_9ph_MLMT_kparameter_t param = return_k_param_set(5U, n1_ml);
    TEST_ASSERT_EQUAL_FLOAT(param.derating, 0.688366f);
}

void test_uz_get_k_parameter_9ph_ML(void){
    uz_9ph_abc_t indices = { //0b000001001=(int)9
            .a1 = 1.0f,//LSB
            .b1 = 0.0f,
            .c1 = 0.0f,
            .a2 = 1.0f,
            .b2 = 0.0f,
            .c2 = 0.0f,
            .a3 = 0.0f,
            .b3 = 0.0f,
            .c3 = 0.0f};//MSB
    uz_9ph_MLMT_kparameter_t param = uz_get_k_parameter_9ph_ML_N1(indices);
    TEST_ASSERT_EQUAL_FLOAT(0.386890f, param.derating);
    TEST_ASSERT_EQUAL_FLOAT(-0.473693f, param.k_X1a);
    TEST_ASSERT_EQUAL_FLOAT(-0.199119f, param.k_Y3b);
}

#endif