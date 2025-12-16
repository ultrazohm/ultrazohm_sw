#ifdef TEST

#include "unity.h"
#include "../uz_buck_control/uz_buck_control.h"
#include "test_assert_with_exception.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdbool.h>

struct buck_control_config config = {
    .control_mode = uz_buck_input_current_mode,
    .input_current_max_reference = 5,
    .input_current_min_reference = -5,
    .input_current_controller_max_reference = 5,
    .input_current_controller_min_reference = -5,
    .input_current_controller_min_control_signal = -5,
    .input_current_controller_max_control_signal = 1,
    .input_current_controller_min_control_signal = -1,
    .input_current_controller_kp = 1,
    .input_current_controller_ki = 0,
    .output_voltage_controller_max_control_signal = 1,
    .output_voltage_controller_min_control_signal = -1,
    .output_voltage_controller_kp = 1,
    .output_voltage_controller_ki = 0,
    .output_current_controller_max_reference = 1,
    .output_current_controller_min_reference = -1,
    .output_current_controller_max_control_signal = 1,
    .output_current_controller_min_control_signal = -1,
    .output_current_controller_kp = 1,
    .output_current_controller_ki = 0,
    .output_voltage_controller_max_reference = 5,
    .output_voltage_controller_min_reference = -5,
    .sampling_frequency_Hz = 10000};

// static void uz_buck_control_controller_config(uz_buck_control_t *self)
// {
//     // initialize all PI controllers
//     // i_HS controller config
//     self->config.input_current_controller_config.Kp = 1.0f;
//     self->config.input_current_controller_config.Ki = 100.0f;
//     self->config.input_current_controller_config.lower_limit = 0.0f;
//     self->config.input_current_controller_config.upper_limit = 50.0f;
//     self->config.input_current_controller_config.samplingTime_sec = 0.0001f;
//     self->config.input_current_controller_config.type = UZ_PI_PARALLEL;

//     // u_UC controller config
//     self->config.output_voltage_controller_config.Kp = 10.0f;
//     self->config.output_voltage_controller_config.Ki = 2.5;
//     self->config.output_voltage_controller_config.lower_limit = -50.0f;
//     self->config.output_voltage_controller_config.upper_limit = 50.0f;
//     self->config.output_voltage_controller_config.samplingTime_sec = 0.0001f;
//     self->config.output_voltage_controller_config.type = UZ_PI_PARALLEL;

//     // i_UC controller config
//     self->config.output_current_controller_config.Kp = 0.01;
//     self->config.output_current_controller_config.Ki = 0.2f;
//     self->config.output_current_controller_config.lower_limit = -10.0f;
//     self->config.output_current_controller_config.upper_limit = 10.0f;
//     self->config.output_current_controller_config.samplingTime_sec = 0.0001f;
//     self->config.output_current_controller_config.type = UZ_PI_PARALLEL;
// }

void setUp(void)
{
    // config.control_mode = uz_buck_input_current_mode;
    // config.input_current_max_reference = 5;
    // config.input_current_min_reference = -5;
    // config.input_current_controller_max_reference = 5;
    // config.input_current_controller_min_reference = -5;
    // config.input_current_controller_min_control_signal = -5;
    // config.input_current_controller_max_control_signal = 1;
    // config.input_current_controller_min_control_signal = -1;
    // config.input_current_controller_kp = 1;
    // config.input_current_controller_ki = 0;
    // config.output_voltage_controller_max_control_signal = 1;
    // config.output_voltage_controller_min_control_signal = -1;
    // config.output_voltage_controller_kp = 1;
    // config.output_voltage_controller_ki = 0;
    // config.output_current_controller_max_control_signal = 1;
    // config.output_current_controller_min_control_signal = -1;
    // config.output_current_controller_kp = 1;
    // config.output_current_controller_ki = 0;
    // config.output_voltage_controller_max_reference = 5;
    // config.output_voltage_controller_min_reference = -5;
    // config.sampling_frequency_Hz = 10000;
}

void test_uz_buck_control_init(void)
{
    uz_buck_control_t *instance = uz_buck_control_init(config);
    TEST_ASSERT_NOT_NULL(instance);
}

void test_uz_buck_control_test_reset(void)
{
    config.control_mode = uz_buck_input_current_mode;
    config.input_current_controller_ki = 10;
    config.input_current_controller_kp = 10;
    config.control_mode = uz_buck_input_current_mode;
    struct buck_control_ref_val ref_val = {0};
    struct buck_control_act_val act_val = {0};
    act_val.input_voltage_Volt = 48;
    uz_buck_control_t *instance = uz_buck_control_init(config);
    ref_val.ref_input_current_Ampere = 10.0f;
    float duty = uz_buck_control_sample(instance, ref_val, act_val);
    TEST_ASSERT(duty > 0.0f);
}

void test_uz_buck_control_sample(void)
{
    config.control_mode = uz_buck_input_current_mode;
    uz_buck_control_t *instance = uz_buck_control_init(config);
    struct buck_control_ref_val ref_val = {0};
    struct buck_control_act_val act_val = {0};
    act_val.input_voltage_Volt = 48;
    float duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // TEST_ASSERT(duty_cycle==1.0f);
}

void test_uz_buck_control_test_current_control(void)
{
    config.control_mode = uz_buck_output_current_mode;
    uz_buck_control_t *instance = uz_buck_control_init(config);
    struct buck_control_ref_val ref_val = {0};
    struct buck_control_act_val act_val = {0};
    act_val.input_voltage_Volt = 48;
    float duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // duty_cycle = uz_buck_control_sample(instance, ref_val, act_val);
    // TEST_ASSERT(duty_cycle==1.0f);
}

#endif