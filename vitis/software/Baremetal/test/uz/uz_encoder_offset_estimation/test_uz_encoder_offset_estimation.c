#ifdef TEST

#include "unity.h"

#include "uz_encoder_offset_estimation.h"
#include "uz_encoder_offset_estimation.c"

#include "mock_uz_SystemTime.h"
#include "uz_filter_cumulativeavg.h"
#include "globalData.h"
#include "uz_Transformation.h"
#include "uz_HAL.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_encoder_offset_estimation_find_best_theta(void)
{
    #define OFFSET_ARRAYSIZE 5U
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
    array[4U] = meas5;

    //float best_theta = uz_encoder_offset_estimation_find_best_theta(array);
    //printf("\ntheta: %f", best_theta);
}

#endif // TEST
