#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"


#include "uz_Space_Vector_Modulation_6ph.h"
#include "uz_Space_Vector_Modulation_6ph.c"
#include "uz_HAL.h"
#include "uz_complex.h"
#include "uz_signals.h"
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

    float shift_1=0.0f;
    float shift_2=0.0f;
    uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles[0], sector, &shift_1, &shift_2);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5972f, Duty_Cycles[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5010f, Duty_Cycles[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.4028f, Duty_Cycles[2]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5862f, Duty_Cycles[3]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.4138f, Duty_Cycles[4]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.4254f, Duty_Cycles[5]);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, shift_1);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, shift_2);
}

void test_uz_svm_6ph_norm_vdc(void){
    uz_6ph_alphabeta_t setpoints = {
        .alpha = 1.5f,
        .beta = -3.0f,
        .x = 10.0f,
        .y = 90.0f,
        .z1 = 0.0f,
        .z2 = -20.0f};
    float v_dc = 20.0f;
    uz_6ph_alphabeta_t setpoints_normed = uz_svm_6ph_norm_vdc(setpoints, v_dc);
    TEST_ASSERT_EQUAL_FLOAT(setpoints.alpha/v_dc, setpoints_normed.alpha);
    TEST_ASSERT_EQUAL_FLOAT(setpoints.beta/v_dc, setpoints_normed.beta);
    TEST_ASSERT_EQUAL_FLOAT(setpoints.x/v_dc, setpoints_normed.x);
    TEST_ASSERT_EQUAL_FLOAT(setpoints.y/v_dc, setpoints_normed.y);
    TEST_ASSERT_EQUAL_FLOAT(setpoints.z1/v_dc, setpoints_normed.z1);
    TEST_ASSERT_EQUAL_FLOAT(setpoints.z2/v_dc, setpoints_normed.z2);
}

void test_uz_svm_6ph_overall_limitation_alphabeta(void){
    uz_6ph_alphabeta_t setpoints = {
        .alpha = 0.3f,
        .beta = -0.6f,
        .x = 0.0f,
        .y = 0.0f,
        .z1 = 0.0f,
        .z2 = -20.0f};
    bool limited_ab=false;
    bool limited_xy=false;
    uz_6ph_alphabeta_t limited = uz_svm_6ph_overall_limitation(setpoints, SVM_6PH_MAXIMUM_MODULATION_INDEX, &limited_ab, &limited_xy);
    TEST_ASSERT_TRUE(limited_ab);
    TEST_ASSERT_TRUE(limited_xy);
    TEST_ASSERT_EQUAL_FLOAT(SVM_6PH_MAXIMUM_MODULATION_INDEX, sqrtf(limited.alpha*limited.alpha+limited.beta*limited.beta));
    limited.beta *= 0.99f; // fix numeric/float number error
    limited = uz_svm_6ph_overall_limitation(limited, SVM_6PH_MAXIMUM_MODULATION_INDEX, &limited_ab, &limited_xy);
    TEST_ASSERT_FALSE(limited_ab);
    TEST_ASSERT_FALSE(limited_xy);
}

void test_uz_svm_6ph_overall_limitation_xy(void){
    uz_6ph_alphabeta_t setpoints = {
        .alpha = 1.0f,
        .beta = -0.5f,
        .x = 0.1f,
        .y = 0.3f,
        .z1 = 0.0f,
        .z2 = -20.0f};
    bool limited_ab=false;
    bool limited_xy=false;
    uz_6ph_alphabeta_t limited = uz_svm_6ph_overall_limitation(setpoints, 100.0f, &limited_ab, &limited_xy);
    TEST_ASSERT_FALSE(limited_ab);
    TEST_ASSERT_TRUE(limited_xy);
    float abs_ab = sqrtf(limited.alpha*limited.alpha+limited.beta*limited.beta);
    float abs_xy = sqrtf(limited.x*limited.x+limited.y*limited.y);
    TEST_ASSERT_EQUAL_FLOAT(abs_ab*SVM_6PH_MAXIMUM_XY_RELATIVE, abs_xy);
}

void test_uz_svm_6ph_calculate_and_shift_duty_cycles(void){
    float Duty_Cycles[6] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
    float Duty_Cycles_1[6] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
    float Duty_Cycles_2[6] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
    float Duty_Cycles_3[6] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
    float Duty_Cycles_4[6] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
    float shift_system_1 = 0.0f;
    float shift_system_2 = 0.0f;
    uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles_1[0], 2, &shift_system_1, &shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, shift_system_1);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[0], Duty_Cycles_1[0]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[1], Duty_Cycles_1[1]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[2], Duty_Cycles_1[2]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[3], Duty_Cycles_1[3]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[4], Duty_Cycles_1[4]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[5], Duty_Cycles_1[5]);
    uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles_2[0], 22, &shift_system_1, &shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, shift_system_1);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[0], Duty_Cycles_2[0]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[1], Duty_Cycles_2[1]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[2], Duty_Cycles_2[2]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[3], Duty_Cycles_2[3]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[4], Duty_Cycles_2[4]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[5], Duty_Cycles_2[5]);
    uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles_3[0], 7, &shift_system_1, &shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, shift_system_1);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[0], Duty_Cycles_3[0]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[1], Duty_Cycles_3[1]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[2], Duty_Cycles_3[2]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[3], Duty_Cycles_3[3]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[4], Duty_Cycles_3[4]);
    TEST_ASSERT_EQUAL_FLOAT(1.0f-Duty_Cycles[5], Duty_Cycles_3[5]);
    uz_svm_6ph_calculate_and_shift_duty_cycles(&Duty_Cycles_4[0], 4, &shift_system_1, &shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, shift_system_1);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, shift_system_2);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[0], Duty_Cycles_4[0]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[1], Duty_Cycles_4[1]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[2], Duty_Cycles_4[2]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[3], Duty_Cycles_4[3]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[4], Duty_Cycles_4[4]);
    TEST_ASSERT_EQUAL_FLOAT(Duty_Cycles[5], Duty_Cycles_4[5]);
}

#endif // TEST
