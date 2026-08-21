#include "../include/deskbench_control.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_PMSM_config/uz_PMSM_config.h"
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_math_constants.h"
#include "../IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../include/uz_platform_state_machine.h"
#include "xparameters.h"
#include <math.h>
#include "../uz/uz_signals/uz_signals.h"

#define DESKBENCH_CURRENT_TO_AMPERE 12.5f
#define DESKBENCH_VOLTAGE_TO_VOLTS 12.0f
#define DESKBENCH_MAX_CURRENT_AMPERE 15.0f
#define DESKBENCH_MAX_INVERTER_TEMP_DEGC 100.0f

static const struct uz_PMSM_t deskbench_beckhoff_am8141 = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.002f,
    .Lq_Henry = 0.002f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .I_max_Ampere = 12.0f,
    .J_kg_m_squared = 0.000108f};

static struct uz_pmsm_control_configuration_t pmsm_control_am8141_config = {
    .theta_el_offset = 0.0f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = false,
    .speed_controller_kp = 0.1f,
    .speed_controller_ki = 2.0f,
    .current_controller_d_kp = 5.8333f,
    .current_controller_d_ki = 1500.0f,
    .current_controller_q_kp = 5.8333f,
    .current_controller_q_ki = 1500.0f,
    .setpoint_limits = {
        .speed_controller_torque_in_Nm = {.upper_bound = 2.0f, .lower_bound = -2.0f},
        .i_d_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .speed_in_rpm = {.upper_bound = 1100.0f, .lower_bound = -1100.0f},
        .disturbance_input_in_Nm = {.upper_bound = 10.0f, .lower_bound = -10.0f}},
    .safe_operating_region = {.speed_in_rpm = {.upper_bound = 1500.0f, .lower_bound = -1500.0f}, .i_d_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f}, .i_q_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f}, .i_abc_in_A = {.upper_bound = 20.0f, .lower_bound = -20.0f}, .v_dc_in_V = {.upper_bound = 52.0f, .lower_bound = -1.0f}, .i_dc_in_A = {.upper_bound = 15.0f, .lower_bound = -15.0f}},
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = 0.0f,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .theta_sampling_compensation = 0.0f,
    .theta_svm_delay_compensation = 1.5f,
    .voltage_theta_shift = 0.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f}};


void deskbench_control_init(DS_Data *data)
{
    data->objects.prime_mover_control = uz_pmsm_control_init(pmsm_control_am8141_config, deskbench_beckhoff_am8141);
    uz_pmsm_control_enable(data->objects.prime_mover_control, true);
    data->objects.prime_mover_measurements = uz_pmsm_control_get_pmsm_measurement_values(data->objects.prime_mover_control);
    data->objects.prime_mover_actual_data = uz_pmsm_control_get_actual_data(data->objects.prime_mover_control);
    data->objects.prime_mover_reference_values = uz_pmsm_control_get_reference_values(data->objects.prime_mover_control);
    uz_pmsm_control_current_control_tune_magnitude_optimum(data->objects.prime_mover_control, 1.5f * pmsm_control_am8141_config.sample_time);
}

float dut_theta_mech_rad = 0.0f;
float prime_mover_theta_mech_rad = 0.0f;

void deskbench_update_measurements(DS_Data *data)
{
    data->av.prime_mover_measurements.i_abc_in_A.a = data->m1_phase_current.a;
    data->av.prime_mover_measurements.i_abc_in_A.b = data->m1_phase_current.b;
    data->av.prime_mover_measurements.i_abc_in_A.c = data->m1_phase_current.c;

    data->av.prime_mover_measurements.i_dc_in_A = data->m1_dc_current;
    data->av.prime_mover_measurements.v_abc_in_V.a = data->m1_phase_voltage.a;
    data->av.prime_mover_measurements.v_abc_in_V.b = data->m1_phase_voltage.b;
    data->av.prime_mover_measurements.v_abc_in_V.c = data->m1_phase_voltage.c;

    data->av.prime_mover_measurements.v_dc_in_V = data->m12_dc_voltage;
    data->av.prime_mover_measurements.theta_mech = data->av.resolver_pl_interface_d4_1_position_mech_2pi;
    data->av.prime_mover_measurements.omega_mech_rad_per_sec = data->av.resolver_pl_interface_d4_1_omega_mech_rad_s;
}
