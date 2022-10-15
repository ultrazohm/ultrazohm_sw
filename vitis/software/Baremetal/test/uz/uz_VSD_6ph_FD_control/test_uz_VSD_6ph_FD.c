#ifdef TEST

#include "unity.h"

#include "uz_VSD_6ph_FD.h"


void test_uz_vsd_opf_6ph_faultdetection(void)
{
    uz_6phFD_indices indices = {0};
    uz_6ph_alphabeta_t currents = {0};

    indices = uz_vsd_opf_6ph_faultdetection(currents);

    TEST_ASSERT_EQUAL_FLOAT(indices.R1, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices.R2, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices.R3, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices.R4, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices.R5, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices.R6, 0.0f);

    currents.alpha = 1.0f;
    currents.beta = 2.0f;
    currents.x = 0.0f;
    currents.y = 1.0f;
    currents.z1 = 0.0f;
    currents.z2 = 0.0f;

    indices = uz_vsd_opf_6ph_faultdetection(currents);

    TEST_ASSERT_FLOAT_WITHIN(0.0f -0.001f, 0.0f +0.001f, indices.R1);
    TEST_ASSERT_FLOAT_WITHIN(0.7029f- 0.001f, 0.7029f+ 0.001f, indices.R2);
    TEST_ASSERT_FLOAT_WITHIN(0.3880f- 0.001f, 0.3880f+ 0.001f, indices.R3);
    TEST_ASSERT_FLOAT_WITHIN(-0.2679f -0.001f, -0.2679f +0.001f, indices.R4);
    TEST_ASSERT_FLOAT_WITHIN(-3.7321f -0.001f, -3.7321f +0.001f, indices.R5);
    TEST_ASSERT_FLOAT_WITHIN( -0.5f -0.001f, -0.5f +0.001f, indices.R6);

}

void test_uz_vsd_fd_hysteresis_filter(void)
{
    uz_6phFD_indices indices_filtered = {0};
    uz_6phFD_indices indices_input = {0};
    float lowerlimit = 0.9f;
    float upperlimit = 1.1f;

    indices_input.R1 = 4.0f;
    indices_input.R2 = 1.1f;
    indices_input.R3 = 1.2f;
    indices_input.R4 = 0.4f;
    indices_input.R5 = 0.1f;
    indices_input.R6 = 0.92f;

    indices_filtered = uz_vsd_fd_hysteresis_filter(indices_input, lowerlimit, upperlimit);

    TEST_ASSERT_EQUAL_FLOAT(indices_filtered.R1, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_filtered.R2, indices_input.R2);
    TEST_ASSERT_EQUAL_FLOAT(indices_filtered.R3, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_filtered.R4, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_filtered.R5, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_filtered.R6, indices_input.R6);
}


void test_uz_vsd_fd_evaluation(void)
{
    uz_6phFD_indices indices_evaluated = {0};
    uz_6phFD_indices indices_input = {0};
    float threshold = 0.4f;

    indices_input.R1 = 0.7f;
    indices_input.R2 = 0.3f;
    indices_evaluated = uz_vsd_fd_evaluation(indices_input, threshold);

    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R1, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R2, 0.0f);

    threshold = 0.8f;

    indices_evaluated = uz_vsd_fd_evaluation(indices_input, threshold);

    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R1, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(indices_evaluated.R2, 0.0f);
}




#endif // TEST
