#ifdef TEST

#include "unity.h"

#include "uz_encoder_offset_estimation.h"
#include "uz_encoder_offset_estimation.c"

#include "mock_uz_SystemTime.h"
#include "uz_filter_cumulativeavg.h"
#include "globalData.h"
#include "uz_Transformation.h"
#include "uz_HAL.h"


float ptr = 0.0f;

struct uz_encoder_offset_estimation_config config;

void setUp(void)
{
    config.ptr_measured_rotor_angle = &ptr;
    config.ptr_offset_angle = &ptr;
    config.ptr_actual_omega_el = &ptr;
    config.ptr_actual_u_q_V = &ptr;
    config.setpoint_current = 1.0f;
    config.min_omega_el = 100.0f;
}

void tearDown(void)
{
}

   

void test_uz_encoder_offset_estimation_init(void){
    uz_encoder_offset_estimation_t* obj = uz_encoder_offset_estimation_init(config);
    TEST_ASSERT_NOT_NULL(obj);

    struct uz_encoder_offset_estimation_status status = uz_encoder_offset_estimation_get_status(obj);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, status.progress);
    TEST_ASSERT_EQUAL(0, status.diagnose);
}

void test_uz_encoder_offset_estimation_find_best_theta(void)
{
    struct measurement meas1 = {
        .theta_offset = 1.0f,
        .psi_d_positive = 5.0f,
        .psi_d_negative = 6.0f};
    struct measurement meas2 = {
        .theta_offset = 2.0f,
        .psi_d_positive = 5.1f,
        .psi_d_negative = 6.0f};
    struct measurement meas3 = {
        .theta_offset = 3.0f,
        .psi_d_positive = 5.2f,
        .psi_d_negative = 6.0f};
    struct measurement meas4 = {
        .theta_offset = 4.0f,
        .psi_d_positive = 5.0f,
        .psi_d_negative = 5.4f};
    struct measurement meas5 = {
        .theta_offset = 5.0f,
        .psi_d_positive = 4.9f,
        .psi_d_negative = 6.2f};
    struct measurement array[OFFSET_ARRAYSIZE];
    array[0U] = meas1;
    array[1U] = meas2;
    array[2U] = meas3;
    array[3U] = meas4;
    for(uint32_t i=4U; i<OFFSET_ARRAYSIZE; i++){
        array[i] = meas5;
    }

    float best_theta = uz_encoder_offset_estimation_find_best_theta(array);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, best_theta);
}


#endif // TEST
