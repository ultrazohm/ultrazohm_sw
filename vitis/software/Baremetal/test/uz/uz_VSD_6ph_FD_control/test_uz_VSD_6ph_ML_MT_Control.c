#ifdef TEST

#include "unity.h"

#include "uz_VSD_6ph_ML_MT_Control.h"
#include "uz_VSD_6ph_FD.h"
#include "uz_VSD_6ph_ML_MT_Control.c"

void setUp(void)
{
}

void test_get_k_parameter(void)
{
    kparameter test_k_parameter = {0};

    int N1N2 = 1;
    int ML = 0;
    uz_6phFD_indices FD_indices = {0};

    // no phase faulted 1N MT:
    test_k_parameter = get_k_parameter(FD_indices, N1N2, ML);

    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.a, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k1, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k2, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k3, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k4, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k5, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k6, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k7, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k8, 0.0f);

    // 1 OPF 1N ML:
    N1N2 = 1;
    ML = 0;
    FD_indices.R1 = 1.0f;
    test_k_parameter = get_k_parameter(FD_indices, N1N2, ML);

    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.a, 0.694444);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k1, -0.641110f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k2, -0.208910f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k3, -0.754240f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k4, -0.295480f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k5, -0.358890f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k6, 0.208910f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k7, 0.358890f);
    TEST_ASSERT_EQUAL_FLOAT(test_k_parameter.k8, -0.208910f);

}

void test_uz_get_k_parameter_num_opf(void){
    uz_6phFD_opf test_struct = {0};
    uz_6phFD_indices input = {0};

    test_struct = uz_num_opf(input);

    TEST_ASSERT_EQUAL_INT(test_struct.num_opf, 0);

    input.R1 = 1.0f;
    test_struct = uz_num_opf(input);
    TEST_ASSERT_EQUAL_INT(test_struct.num_opf, 1);
    TEST_ASSERT_EQUAL_INT(test_struct.opf1, 1);

    input.R1 = 1.0f;
    input.R4 = 1.0f;
    test_struct = uz_num_opf(input);
    TEST_ASSERT_EQUAL_INT(test_struct.num_opf, 2);
    TEST_ASSERT_EQUAL_INT(test_struct.opf1, 1);
    TEST_ASSERT_EQUAL_INT(test_struct.opf2, 4);


    input.R1 = 0.0f;
    input.R4 = 1.0f;
    input.R6 = 1.0f;
    test_struct = uz_num_opf(input);
    TEST_ASSERT_EQUAL_INT(test_struct.num_opf, 2);
    TEST_ASSERT_EQUAL_INT(test_struct.opf1, 4);
    TEST_ASSERT_EQUAL_INT(test_struct.opf2, 6);


    input.R4 = 1.0f;
    input.R2 = 1.0f;
    input.R6 = 1.0f;
    test_struct = uz_num_opf(input);
    TEST_ASSERT_EQUAL_INT(test_struct.num_opf, 3);
    TEST_ASSERT_EQUAL_INT(test_struct.opf1, 2);
    TEST_ASSERT_EQUAL_INT(test_struct.opf2, 4);
    TEST_ASSERT_EQUAL_INT(test_struct.opf3, 6);


    input.R4 = 1.0f;
    input.R2 = 1.0f;
    input.R6 = 1.0f;
    input.R1 = 1.0f;
    input.R3 = 1.0f;
    test_struct = uz_num_opf(input);
    TEST_ASSERT_EQUAL_INT(test_struct.num_opf, 5);
    TEST_ASSERT_EQUAL_INT(test_struct.opf1, 1);
    TEST_ASSERT_EQUAL_INT(test_struct.opf2, 2);
    TEST_ASSERT_EQUAL_INT(test_struct.opf3, 3);
    TEST_ASSERT_EQUAL_INT(test_struct.opf4, 4);
    TEST_ASSERT_EQUAL_INT(test_struct.opf5, 6);
}

void test_uz_get_k_parameter_get_index_OPF_3(void){
    int index;
    int p1 = 1;
    int p2 = 2;
    int p3 = 3;

    index = get_index_OPF_3(p1, p2, p3);
    TEST_ASSERT_EQUAL_INT(index, 0);

    p1 = 1;
    p2 = 2;
    p3 = 4;
    index = get_index_OPF_3(p1, p2, p3);
    TEST_ASSERT_EQUAL_INT(index, 1);

    p1 = 4;
    p2 = 5;
    p3 = 6;
    index = get_index_OPF_3(p1, p2, p3);
    TEST_ASSERT_EQUAL_INT(index, 19);
}   


void test_uz_get_k_parameter_get_index_OPF_2(void){
    int index;
    int p1 = 1;
    int p2 = 2;

    index = get_index_OPF_2(p1, p2);
    TEST_ASSERT_EQUAL_INT(index, 0);

    p1 = 1;
    p2 = 3;
    index = get_index_OPF_2(p1, p2);
    TEST_ASSERT_EQUAL_INT(index, 1);

    p1 = 5;
    p2 = 6;
    index = get_index_OPF_2(p1, p2);
    TEST_ASSERT_EQUAL_INT(index, 14);
}   
#endif // TEST
