#include "uz_pmsm_control.h"

#include "../uz_global_configuration.h"
#if UZ_PMSM_CONTROL_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_pmsm_control.h"
#include "../uz_math_constants.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_piController/uz_piController.h"

struct uz_pmsm_control_t
{
    bool is_ready;
    struct uz_pmsm_control_configuration_t config;
    struct uz_pmsm_measurement_values measurement;
    struct uz_pmsm_reference_values reference_values;
    struct uz_pmsm_actual_data actual_values;
    uz_CurrentControl_t *current_controller;
    uz_SpeedControl_t *speed_controller;
    uz_SetPoint_t *setpoint_module;
    uz_dq_setpoint_filter *setpoint_filter_i_dq;
    uz_IIR_Filter_t *setpoint_filter_speed;
    uz_IIR_Filter_t *speed_filter;
    uz_PMSM_t machine_data;
    bool enable;
    bool safe_operating_region_violation;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_control_t instances[UZ_PMSM_CONTROL_MAX_INSTANCES] = {0};

void uz_pmsm_controller_measured_to_actual_values(uz_pmsm_control_t *self);
void uz_pmsm_controller_check_safe_operating_region(uz_pmsm_control_t *self);

static uz_pmsm_control_t *uz_pmsm_control_allocation(void);

static uz_pmsm_control_t *uz_pmsm_control_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_CONTROL_MAX_INSTANCES);
    uz_pmsm_control_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_pmsm_control_t *uz_pmsm_control_init(struct uz_pmsm_control_configuration_t config, uz_PMSM_t machine_data)
{
    uz_pmsm_control_t *self = uz_pmsm_control_allocation();
    self->config = config;
    self->machine_data = machine_data;
    self->enable = false;

    struct uz_CurrentControl_config current_controller_configuration = {
        .decoupling_select = config.decoupling_method,
        .config_PMSM = machine_data,
        .config_id = {
            .Kp = config.current_controller_d_kp,
            .Ki = config.current_controller_d_ki,
            .samplingTime_sec = config.sample_time,
            .upper_limit = 1.0f,
            .lower_limit = -1.0f},
        .config_iq = {.Kp = config.current_controller_q_kp, .Ki = config.current_controller_q_ki, .samplingTime_sec = config.sample_time, .upper_limit = 1.0f, .lower_limit = -1.0f},
        .max_modulation_index = 1.0f / sqrtf(3.0f)};

    struct uz_SpeedControl_config speed_controller_configuration = {
        .config_controller.Kp = config.speed_controller_kp,
        .config_controller.Ki = config.speed_controller_ki,
        .config_controller.samplingTime_sec = config.sample_time,
        .config_controller.upper_limit = config.speed_controller_max_torque,
        .config_controller.lower_limit = -1.0f * config.speed_controller_max_torque,
        .config_controller.type = UZ_PI_PARALLEL};

    struct uz_SetPoint_config setpoint_configuration = {
        .config_PMSM = machine_data,
        .control_type = FOC,
        .motor_type = config.motor_type,
        .is_field_weakening_enabled = config.enable_field_weakening,
        .id_ref_Ampere = 0.0f,
        .relative_torque_tolerance = config.relative_torque_tolerance};

    self->current_controller = uz_CurrentControl_init(current_controller_configuration);
    self->speed_controller = uz_SpeedControl_init(speed_controller_configuration);
    self->setpoint_module = uz_SetPoint_init(setpoint_configuration);

    if (config.speed_actual_value_filter_cutoff_frequency != 0.0f)
    {
        struct uz_IIR_Filter_config speed_filter_config = {
            .selection = LowPass_first_order,
            .cutoff_frequency_Hz = config.speed_actual_value_filter_cutoff_frequency,
            .sample_frequency_Hz = 1.0f / config.sample_time};
        self->speed_filter = uz_signals_IIR_Filter_init(speed_filter_config);
    }

    // Filter config
    if (config.setpoint_filter_i_dq_cutoff_frequency != 0.0f)
    {
        struct uz_dq_setpoint_filter_config setpoint_filter_config =
            {
                .config_filter_d = {
                    .cutoff_frequency_Hz = config.setpoint_filter_i_dq_cutoff_frequency,
                    .sample_frequency_Hz = 1.0f / config.sample_time,
                    .selection = LowPass_first_order,
                },
                .config_filter_q = {
                    .cutoff_frequency_Hz = config.setpoint_filter_i_dq_cutoff_frequency,
                    .sample_frequency_Hz = 1.0f / config.sample_time,
                    .selection = LowPass_first_order,
                }};
        self->setpoint_filter_i_dq = uz_uz_dq_setpoint_filter_init(setpoint_filter_config);
    }

    if (config.setpoint_filter_speed_cutoff_frequency != 0.0f)
    {
        struct uz_IIR_Filter_config setpoint_filter_speed_config = {
            .selection = LowPass_first_order,
            .cutoff_frequency_Hz = config.setpoint_filter_speed_cutoff_frequency,
            .sample_frequency_Hz = 1.0f / config.sample_time};
        self->setpoint_filter_speed = uz_signals_IIR_Filter_init(setpoint_filter_speed_config);
    }
    return (self);
}

struct uz_pmsm_actual_data *uz_pmsm_control_get_actual_data(uz_pmsm_control_t *self)
{
    return &self->actual_values;
}

struct uz_pmsm_reference_values *uz_pmsm_control_get_reference_values(uz_pmsm_control_t *self)
{
    return &self->reference_values;
}

struct uz_pmsm_measurement_values *uz_pmsm_control_get_pmsm_measurement_values(uz_pmsm_control_t *self)
{
    return &self->measurement;
}

float *uz_pmsm_control_get_pointer_to_theta_offset(uz_pmsm_control_t *self)
{
    return &self->config.theta_el_offset;
}

bool uz_pmsm_controller_get_safe_operating_area_violation(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->safe_operating_region_violation;
}

void uz_pmsm_controller_reset(uz_pmsm_control_t *self)
{
    uz_assert(self->is_ready);
    uz_CurrentControl_reset(self->current_controller);
    uz_SpeedControl_reset(self->speed_controller);
}

void uz_pmsm_controller_enable(uz_pmsm_control_t *self, bool enable)
{
    uz_assert(self->is_ready);
    self->enable = enable;
}

void uz_pmsm_controller_acknowledge_and_reset_error(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements)
{
    uz_assert(self->is_ready);
    self->measurement = measurements;
    self->safe_operating_region_violation = false;
    uz_pmsm_controller_check_safe_operating_region(self);
}

void uz_pmsm_controller_measured_to_actual_values(uz_pmsm_control_t *self)
{
    self->actual_values.i_abc_in_A.a = (self->config.current_conversion_factors.a * self->measurement.phase_currents_from_adc_ampere_per_volt.a) + self->config.current_offsets.a;
    self->actual_values.i_abc_in_A.b = (self->config.current_conversion_factors.b * self->measurement.phase_currents_from_adc_ampere_per_volt.b) + self->config.current_offsets.b;
    self->actual_values.i_abc_in_A.c = (self->config.current_conversion_factors.c * self->measurement.phase_currents_from_adc_ampere_per_volt.c) + self->config.current_offsets.c;
    self->actual_values.v_abc_in_V.a = (self->config.voltage_conversion_factors.a * self->measurement.phase_voltage_from_adc_voltage_per_volt.a) + self->config.voltage_offsets.a;
    self->actual_values.v_abc_in_V.b = (self->config.voltage_conversion_factors.b * self->measurement.phase_voltage_from_adc_voltage_per_volt.b) + self->config.voltage_offsets.b;
    self->actual_values.v_abc_in_V.c = (self->config.voltage_conversion_factors.c * self->measurement.phase_voltage_from_adc_voltage_per_volt.c) + self->config.voltage_offsets.c;
    self->actual_values.v_dc_in_V = (self->config.v_dc_in_V_conversion_factor * self->measurement.v_dc_from_adc_volt_per_volt) + self->config.v_dc_in_V_offset;
    self->actual_values.i_dc_in_A = (self->config.i_dc_in_V_conversion_factor * self->measurement.i_dc_from_adc_ampere_per_volt) + self->config.i_dc_in_V_offset;

    self->actual_values.omega_el_rad_per_sec = self->measurement.omega_mech_rad_per_sec * self->machine_data.polePairs;
    self->actual_values.speed_in_rpm = self->measurement.omega_mech_rad_per_sec * 60.0f / (2.0f * UZ_PIf);
    float theta_el_without_offset = uz_signals_wrap(self->measurement.theta_mech * self->machine_data.polePairs, 2.0f * UZ_PIf);
    self->actual_values.theta_el = theta_el_without_offset - self->config.theta_el_offset;
    self->actual_values.theta_el = self->actual_values.theta_el + (self->config.theta_sampling_compensation * self->actual_values.omega_el_rad_per_sec * self->config.sample_time);
    float angle_for_voltage_measurement = self->actual_values.theta_el - (self->config.voltage_theta_shift * self->actual_values.omega_el_rad_per_sec) * self->config.sample_time;
    self->actual_values.theta_el = uz_signals_wrap(self->actual_values.theta_el, 2.0f * UZ_PIf);
    self->actual_values.theta_el_advanced = self->actual_values.theta_el + (1.5f * self->actual_values.omega_el_rad_per_sec) * self->config.sample_time;
    self->actual_values.i_dq_in_A = uz_transformation_3ph_abc_to_dq(self->actual_values.i_abc_in_A, self->actual_values.theta_el);
    self->actual_values.v_dq_in_V = uz_transformation_3ph_abc_to_dq(self->actual_values.v_abc_in_V, angle_for_voltage_measurement);
}

void uz_pmsm_controller_check_safe_operating_region(uz_pmsm_control_t *self)
{
    uz_assert(self->is_ready);
    if (1.3f * fabsf(self->actual_values.i_abc_in_A.a) > self->machine_data.I_max_Ampere)
    {
        self->safe_operating_region_violation = true;
    }
    if (1.3f * fabsf(self->actual_values.i_abc_in_A.b) > self->machine_data.I_max_Ampere)
    {
        self->safe_operating_region_violation = true;
    }
    if (1.3f * fabsf(self->actual_values.i_abc_in_A.c) > self->machine_data.I_max_Ampere)
    {
        self->safe_operating_region_violation = true;
    }
    if (self->actual_values.speed_in_rpm > self->config.error_upper_bound_speed_in_rpm)
    {
        // Too fast
        self->safe_operating_region_violation = true;
    }
    if (self->actual_values.speed_in_rpm < self->config.error_lower_bound_speed_in_rpm)
    {
        // Too slow
        self->safe_operating_region_violation = true;
    }
}

void uz_pmsm_controller_enable_speed_control(uz_pmsm_control_t *self, bool enable_speed_control)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.enable_speed_control = enable_speed_control;
}

void uz_pmsm_controller_set_theta_offset(uz_pmsm_control_t *self, float theta_offset)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.theta_el_offset = theta_offset;
}

struct uz_DutyCycle_t
uz_pmsm_controller_sample(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements, float reference_speed_in_rpm, uz_3ph_dq_t reference_currents, float disturbance_input_in_Nm)
{
    uz_assert(self->is_ready);
    uz_assert_not_NULL(self);
    reference_speed_in_rpm = uz_signals_saturation(reference_speed_in_rpm, self->config.setpoint_upper_bound_speed_in_rpm, self->config.setpoint_lower_bound_speed_in_rpm);
    reference_currents.d = uz_signals_saturation(reference_currents.d, self->config.setpoint_upper_bound_i_d_in_A, self->config.setpoint_lower_bound_i_d_in_A);
    reference_currents.q = uz_signals_saturation(reference_currents.q, self->config.setpoint_upper_bound_i_q_in_A, self->config.setpoint_lower_bound_i_q_in_A);
    disturbance_input_in_Nm = uz_signals_saturation(disturbance_input_in_Nm, self->config.disturbance_input_upper_bound_in_Nm, self->config.disturbance_input_lower_bound_in_Nm);

    if (self->config.speed_actual_value_filter_cutoff_frequency != 0.0f)
    {
        measurements.omega_mech_rad_per_sec = uz_signals_IIR_Filter_sample(self->speed_filter, measurements.omega_mech_rad_per_sec);
    }

    self->measurement = measurements;
    uz_pmsm_controller_measured_to_actual_values(self);
    uz_pmsm_controller_check_safe_operating_region(self);

    if (self->config.setpoint_filter_speed_cutoff_frequency != 0.0f)
    {
        self->reference_values.speed_in_rpm = uz_signals_IIR_Filter_sample(self->setpoint_filter_speed, reference_speed_in_rpm);
    }
    else
    {
        self->reference_values.speed_in_rpm = reference_speed_in_rpm;
    }

    if (self->enable && (!self->safe_operating_region_violation))
    {
        if (self->config.enable_speed_control)
        {
            self->reference_values.M_in_Nm = uz_SpeedControl_sample(self->speed_controller, self->measurement.omega_mech_rad_per_sec, self->reference_values.speed_in_rpm);
            float ref_plus_disturbance_input = disturbance_input_in_Nm + self->reference_values.M_in_Nm;
            if (fabsf(ref_plus_disturbance_input) > self->config.speed_controller_max_torque)
            {
                uz_SpeedControl_set_ext_clamping(self->speed_controller, true);
            }
            else
            {
                uz_SpeedControl_set_ext_clamping(self->speed_controller, false);
            }
            self->reference_values.M_in_Nm = uz_signals_saturation(ref_plus_disturbance_input, self->config.speed_controller_max_torque, -1.0f * self->config.speed_controller_max_torque);
            self->reference_values.i_dq_in_A = uz_SetPoint_sample(self->setpoint_module, self->measurement.omega_mech_rad_per_sec, self->reference_values.M_in_Nm, self->actual_values.v_dc_in_V, self->actual_values.i_dq_in_A);
        }
        else
        {
            if (self->config.setpoint_filter_i_dq_cutoff_frequency != 0.0f)
            {
                self->reference_values.i_dq_in_A = uz_signals_IIR_Filter_dq_setpoint(self->setpoint_filter_i_dq, reference_currents);
            }
            else
            {
                self->reference_values.i_dq_in_A = reference_currents;
            }
        }

        self->reference_values.v_dq_in_V = uz_CurrentControl_sample(self->current_controller, self->reference_values.i_dq_in_A, self->actual_values.i_dq_in_A, self->actual_values.v_dc_in_V, self->actual_values.omega_el_rad_per_sec);
        self->reference_values.duty_cycle = uz_Space_Vector_Modulation(self->reference_values.v_dq_in_V, self->actual_values.v_dc_in_V, self->actual_values.theta_el_advanced);
        self->reference_values.v_abc_in_V.a = self->reference_values.duty_cycle.DutyCycle_A * self->actual_values.v_dc_in_V; // uz_transformation_3ph_dq_to_abc(self->reference_values.v_dq_in_V, self->actual_values.theta_el);
        self->reference_values.v_abc_in_V.b = self->reference_values.duty_cycle.DutyCycle_B * self->actual_values.v_dc_in_V; // uz_transformation_3ph_dq_to_abc(self->reference_values.v_dq_in_V, self->actual_values.theta_el);
        self->reference_values.v_abc_in_V.c = self->reference_values.duty_cycle.DutyCycle_C * self->actual_values.v_dc_in_V; // uz_transformation_3ph_dq_to_abc(self->reference_values.v_dq_in_V, self->actual_values.theta_el);
    }
    else
    {
        uz_pmsm_controller_reset(self);
        self->reference_values.duty_cycle = self->config.default_duty_cycle;
    }
    return self->reference_values.duty_cycle;
}

#endif
