#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"


#include "uz_Space_Vector_Modulation_6ph.h"
#include "uz_Space_Vector_Modulation_6ph.c"
#include "uz_HAL.h"
#include "uz_complex/uz_complex.h"
#include "uz_signals/uz_signals.h"
#include "uz_math_constants.h"
#include "uz_space_vector_modulation.h"
#include "uz_Transformation.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_svm_6ph_get_sector(void)
{
    int sector = uz_svm_6ph_get_sector(0.1f, 0.01f);
    TEST_ASSERT_EQUAL(1, sector);
    sector = uz_svm_6ph_get_sector(0.1f, 0.05f);
    TEST_ASSERT_EQUAL(2, sector);
    sector = uz_svm_6ph_get_sector(0.2f, 0.15f);
    TEST_ASSERT_EQUAL(3, sector);
    sector = uz_svm_6ph_get_sector(0.1f, 0.15f);
    TEST_ASSERT_EQUAL(4, sector);
    sector = uz_svm_6ph_get_sector(0.1f, 0.2f);
    TEST_ASSERT_EQUAL(5, sector);
    sector = uz_svm_6ph_get_sector(0.01f, 0.2f);
    TEST_ASSERT_EQUAL(6, sector);
    sector = uz_svm_6ph_get_sector(-0.01f, 0.2f);
    TEST_ASSERT_EQUAL(7, sector);
    sector = uz_svm_6ph_get_sector(-0.1f, 0.2f);
    TEST_ASSERT_EQUAL(8, sector);
    sector = uz_svm_6ph_get_sector(-0.15f, 0.2f);
    TEST_ASSERT_EQUAL(9, sector);
    sector = uz_svm_6ph_get_sector(-0.2f, 0.2f);
    TEST_ASSERT_EQUAL(10, sector);
    sector = uz_svm_6ph_get_sector(-0.2f, 0.1f);
    TEST_ASSERT_EQUAL(11, sector);
    sector = uz_svm_6ph_get_sector(-0.2f, 0.01f);
    TEST_ASSERT_EQUAL(12, sector);
}

void test_uz_svm_6ph_calculate_dwell_times_2N_2nd_sector(void)
{
    uz_6ph_alphabeta_t setpoints = {
        .alpha = 0.1f,
        .beta = 0.05f,
        .x = 0.0005f,
        .y = -0.0003f,
        .z1 = 3.0f,
        .z2 = -5.0f};
    int sector = uz_svm_6ph_get_sector(setpoints.alpha, setpoints.beta);

    // calculate dwell times
    float dwell_times[5];
    for(int i=0; i<5; i++){
        dwell_times[i] = uz_svm_6ph_calculate_dwell_times_2N(setpoints, &inverse_T_tv_all[sector-1][i][0]);
    }

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0220f, dwell_times[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0116f, dwell_times[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0846f, dwell_times[2]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0761f, dwell_times[3]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.8057f, dwell_times[4]);
}

void test_uz_svm_6ph_calculate_duty_cycles(void)
{
    float dwell_times[5] = {0.0220f, 0.0116f, 0.0736f, 0.0871f, 0.8057f};
    int sector = 2;
    // calculate duty cycles from dwell times
    float Duty_Cycles[6];
    uz_svm_6ph_calculate_duty_cycles(&Duty_Cycles[0], &dwell_times[0], &svm_offline_order[sector-1][0]);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5972f, Duty_Cycles[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5010f, Duty_Cycles[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.4028f, Duty_Cycles[2]);

    int shift = uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles[0], sector);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5972f, Duty_Cycles[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5010f, Duty_Cycles[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.4028f, Duty_Cycles[2]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5862f, Duty_Cycles[3]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.4138f, Duty_Cycles[4]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.4254f, Duty_Cycles[5]);

    TEST_ASSERT_EQUAL(2, shift);
}

void test_uz_svm_6ph_alphabeta_limitation(void){
    uz_6ph_alphabeta_t setpoints = {
        .alpha = 1.5f,
        .beta = -3.0f,
        .x = 10.0f,
        .y = 90.0f,
        .z1 = 0.0f,
        .z2 = -20.0f};
    bool flag = false;
    uz_6ph_alphabeta_t limited = uz_svm_6ph_alphabeta_limitation(setpoints, 1.0f, &flag);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-SVM_6PH_MAXIMUM_XY_RELATIVE, sqrtf(limited.alpha*limited.alpha+limited.beta*limited.beta));
    TEST_ASSERT_TRUE(flag);
    limited.alpha *= 0.99f; // fix numeric/float number error
    limited = uz_svm_6ph_alphabeta_limitation(limited, 1.0f, &flag);
    TEST_ASSERT_FALSE(flag);
    TEST_ASSERT_FAIL_ASSERT(uz_svm_6ph_alphabeta_limitation(setpoints, -1.0f, &flag));
}

void test_uz_svm_6ph_xy_limitation(void){
    uz_6ph_alphabeta_t setpoints = {
        .alpha = 1.0f,
        .beta = -0.5f,
        .x = 0.1f,
        .y = 0.2f,
        .z1 = 0.0f,
        .z2 = -20.0f};
    bool flag = false;
    uz_6ph_alphabeta_t limited = uz_svm_6ph_xy_limitation(setpoints, &flag);
    float abs_ab = sqrtf(limited.alpha*limited.alpha+limited.beta*limited.beta);
    float abs_xy = sqrtf(limited.x*limited.x+limited.y*limited.y);
    TEST_ASSERT_EQUAL_FLOAT(abs_xy, abs_ab*SVM_6PH_MAXIMUM_XY_RELATIVE);
    TEST_ASSERT_TRUE(flag);
    limited = uz_svm_6ph_xy_limitation(limited, &flag);
    TEST_ASSERT_FALSE(flag);
}


#endif // TEST
