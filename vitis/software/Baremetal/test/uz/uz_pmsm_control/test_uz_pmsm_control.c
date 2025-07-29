#ifdef TEST

#include "unity.h"

#include "uz_pmsm_control.h"
#include "uz_HAL.h"
#include "uz_pmsm_control.h"
#include "uz_math_constants.h"
#include "uz_signals/uz_signals.h"
#include "uz_piController/uz_piController.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "uz_SpeedControl/uz_speedcontrol.h"
#include "uz_CurrentControl/uz_CurrentControl.h"
#include "uz_setpoint/uz_setpoint.h"
#include "uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"

#include "test_assert_with_exception.h"
#include "uz_CurrentControl.h"
#include "uz_piController/uz_piController.h"
#include "uz_signals/uz_signals.h"
#include "uz_linear_decoupling.h"
#include "uz_static_nonlinear_decoupling.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include <math.h>

TEST_FILE("uz_signals_iir_filter.c")
TEST_FILE("uz_newton_raphson.c")

void setUp(void)
{
}

void tearDown(void)
{
}

#define A_GAIN 1.0f
#define B_GAIN 1.0f
#define C_GAIN 1.0f
#define A_OFFSET 1.0f
#define B_OFFSET 1.0f
#define C_OFFSET 1.0f
#define A_VOLTAGE_GAIN 1.0f
#define B_VOLTAGE_GAIN 1.0f
#define C_VOLTAGE_GAIN 1.0f
#define A_VOLTAGE_OFFSET 1.0f
#define B_VOLTAGE_OFFSET 1.0f
#define C_VOLTAGE_OFFSET 1.0f

#define SETPOINT_FILTER_CUTTOFF_FREQUENCY 100.0f

struct uz_pmsm_control_configuration_t pmsm_controller_config = {
    .current_conversion_factors = {
        .a = A_GAIN,
        .b = B_GAIN,
        .c = C_GAIN},
    .current_offsets = {.a = A_OFFSET, .b = B_OFFSET, .c = C_OFFSET},
    .voltage_conversion_factors = {.a = A_VOLTAGE_GAIN, .b = B_VOLTAGE_GAIN, .c = C_VOLTAGE_GAIN},
    .voltage_offsets = {.a = A_VOLTAGE_OFFSET, .b = B_VOLTAGE_OFFSET, .c = C_VOLTAGE_OFFSET},
    .v_dc_in_V_conversion_factor = 12.0f,
    .v_dc_in_V_offset = 0.0f,
    .i_dc_in_V_conversion_factor = 12.5f,
    .i_dc_in_V_offset = 0.0f,
    .theta_el_offset = 1.56f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = true,
    .speed_controller_max_torque = 2.0f,
    .speed_controller_kp = 0.01f,
    .speed_controller_ki = 0.05f,
    .current_controller_d_kp = 5.8333f,
    .current_controller_d_ki = 1500.0f,
    .current_controller_q_kp = 5.8333f,
    .current_controller_q_ki = 1500.0f,
    .setpoint_lower_bound_i_d_in_A = -5.0f,
    .setpoint_upper_bound_i_d_in_A = 0.5f,
    .setpoint_lower_bound_i_q_in_A = -5.0f,
    .setpoint_upper_bound_i_q_in_A = 5.0f,
    .setpoint_upper_bound_speed_in_rpm = 1100.0f,
    .setpoint_lower_bound_speed_in_rpm = -1100.0f,
    .error_upper_bound_speed_in_rpm = 1500.0f,
    .error_lower_bound_speed_in_rpm = -1500.0f,
    .disturbance_input_lower_bound_in_Nm = -10.0f,
    .disturbance_input_upper_bound_in_Nm = 10.0f,
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = SETPOINT_FILTER_CUTTOFF_FREQUENCY,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .theta_sampling_compensation = 1.0f,
    .voltage_theta_shift=0.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t machine_config = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.002f,
    .Lq_Henry = 0.002f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 12.0f};


void test_uz_pmsm_control_test_call(void)
{
    uz_pmsm_control_t *controller = uz_pmsm_control_init(pmsm_controller_config, machine_config);
    struct uz_pmsm_actual_data *actual_data = uz_pmsm_control_get_actual_data(controller);
    struct uz_pmsm_reference_values *reference_values = uz_pmsm_control_get_reference_values(controller);
    struct uz_pmsm_measurement_values *measurement_values = uz_pmsm_control_get_pmsm_measurement_values(controller);
}


#endif // TEST
