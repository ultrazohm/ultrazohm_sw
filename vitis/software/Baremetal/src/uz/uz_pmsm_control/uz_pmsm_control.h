#ifndef UZ_PMSM_CONTROL_H
#define UZ_PMSM_CONTROL_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_setpoint/uz_setpoint.h"
#include "../uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"
#include "../uz_signals/uz_signals.h"

typedef struct uz_pmsm_control_t uz_pmsm_control_t;

struct uz_pmsm_control_configuration_t
{
    uz_3ph_abc_t current_conversion_factors;
    uz_3ph_abc_t current_offsets;
    uz_3ph_abc_t voltage_conversion_factors;
    uz_3ph_abc_t voltage_offsets;
    float v_dc_in_V_conversion_factor;
    float v_dc_in_V_offset;
    float i_dc_in_V_conversion_factor;
    float i_dc_in_V_offset;
    float theta_el_offset;
    float sample_time; // typically 1/PWM
    bool enable_speed_control;
    float speed_controller_max_torque;
    float speed_controller_kp;
    float speed_controller_ki;
    float current_controller_d_kp;
    float current_controller_d_ki;
    float current_controller_q_kp;
    float current_controller_q_ki;
    float setpoint_upper_bound_i_d_in_A;
    float setpoint_lower_bound_i_d_in_A;
    float setpoint_upper_bound_i_q_in_A;
    float setpoint_lower_bound_i_q_in_A;
    float setpoint_upper_bound_speed_in_rpm;
    float setpoint_lower_bound_speed_in_rpm;
    float error_upper_bound_speed_in_rpm;
    float error_lower_bound_speed_in_rpm;
    float disturbance_input_lower_bound_in_Nm;
    float disturbance_input_upper_bound_in_Nm;
    float setpoint_filter_i_dq_cutoff_frequency;  // Do not use setpoint filter if 0
    float setpoint_filter_speed_cutoff_frequency; // Do not use setpoint filter if 0
    float speed_actual_value_filter_cutoff_frequency; // Do not use filter if 0
    enum uz_CurrentControl_decoupling_select decoupling_method;
    enum uz_Setpoint_motor_type motor_type;
    bool enable_field_weakening;
    float relative_torque_tolerance;
    float theta_sampling_compensation; // multiple of sampling time
    float voltage_theta_shift; // Multiple of sampling time for shifting the measured voltages used in dq transformation v_abc to v_dq
    struct uz_DutyCycle_t default_duty_cycle; // returned duty cycle if control is not enabled
};

struct uz_pmsm_actual_data
{
    uz_3ph_abc_t i_abc_in_A;
    uz_3ph_abc_t v_abc_in_V;
    uz_3ph_dq_t i_dq_in_A;
    uz_3ph_dq_t v_dq_in_V;
    float v_dc_in_V;
    float i_dc_in_A;
    float omega_el_rad_per_sec;
    float speed_in_rpm;
    float theta_el;
    float theta_el_advanced;
};

struct uz_pmsm_measurement_values
{
    uz_3ph_abc_t phase_currents_from_adc_ampere_per_volt; // Values are in V before unit conversion
    uz_3ph_abc_t phase_voltage_from_adc_voltage_per_volt; // Values are in V before unit conversion
    float omega_mech_rad_per_sec;
    float theta_mech;
    float v_dc_from_adc_volt_per_volt;
    float i_dc_from_adc_ampere_per_volt;
};

struct uz_pmsm_reference_values
{
    float speed_in_rpm;
    float M_in_Nm;
    uz_3ph_dq_t i_dq_in_A;
    uz_3ph_dq_t v_dq_in_V;
    uz_3ph_abc_t v_abc_in_V;
    struct uz_DutyCycle_t duty_cycle;
};

uz_pmsm_control_t *uz_pmsm_control_init(struct uz_pmsm_control_configuration_t config, uz_PMSM_t machine_data);
struct uz_pmsm_actual_data *uz_pmsm_control_get_actual_data(uz_pmsm_control_t *self);
struct uz_pmsm_reference_values *uz_pmsm_control_get_reference_values(uz_pmsm_control_t *self);
struct uz_pmsm_measurement_values *uz_pmsm_control_get_uz_pmsm_measurement_values(uz_pmsm_control_t *self);

void uz_pmsm_controller_enable(uz_pmsm_control_t *self, bool enable);
struct uz_DutyCycle_t uz_pmsm_controller_sample(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements, float reference_speed_in_rpm, uz_3ph_dq_t reference_currents, float disturbance_input_in_Nm);

void uz_pmsm_controller_acknowledge_and_reset_error(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements);
float *uz_pmsm_control_get_pointer_to_theta_offset(uz_pmsm_control_t *self);
bool uz_pmsm_controller_get_safe_operating_area_violation(uz_pmsm_control_t *self);
void uz_pmsm_controller_enable_speed_control(uz_pmsm_control_t *self, bool enable_speed_control);
void uz_pmsm_controller_set_theta_offset(uz_pmsm_control_t *self, float theta_offset);
#endif // UZ_PMSM_CONTROL_H
