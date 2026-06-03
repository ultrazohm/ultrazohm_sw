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
    enum uz_pmsm_control_safe_operating_region_violation safe_operating_region_violation;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_control_t instances[UZ_PMSM_CONTROL_MAX_INSTANCES] = {0};

static void uz_pmsm_control_measured_to_actual_values(uz_pmsm_control_t *self);
static void uz_pmsm_control_check_safe_operating_region(uz_pmsm_control_t *self);

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
    uz_PMSM_config_assert(machine_data);
    uz_assert(config.sample_time > 0.0f);
    uz_assert(config.speed_controller_kp >= 0.0f);
    uz_assert(config.speed_controller_ki >= 0.0f);
    uz_assert(config.current_controller_d_kp >= 0.0f);
    uz_assert(config.current_controller_d_ki >= 0.0f);
    uz_assert(config.current_controller_q_kp >= 0.0f);
    uz_assert(config.current_controller_q_ki >= 0.0f);
    uz_assert(config.setpoint_limits.speed_controller_torque_in_Nm.upper_bound >= config.setpoint_limits.speed_controller_torque_in_Nm.lower_bound);
    uz_assert(config.setpoint_limits.i_d_in_A.upper_bound >= config.setpoint_limits.i_d_in_A.lower_bound);
    uz_assert(config.setpoint_limits.i_q_in_A.upper_bound >= config.setpoint_limits.i_q_in_A.lower_bound);
    uz_assert(config.setpoint_limits.speed_in_rpm.upper_bound >= config.setpoint_limits.speed_in_rpm.lower_bound);
    uz_assert(config.setpoint_limits.disturbance_input_in_Nm.upper_bound >= config.setpoint_limits.disturbance_input_in_Nm.lower_bound);

    uz_assert(config.safe_operating_region.speed_in_rpm.upper_bound >= config.safe_operating_region.speed_in_rpm.lower_bound);
    uz_assert(config.safe_operating_region.i_d_in_A.upper_bound >= config.safe_operating_region.i_d_in_A.lower_bound);
    uz_assert(config.safe_operating_region.i_q_in_A.upper_bound >= config.safe_operating_region.i_q_in_A.lower_bound);
    uz_assert(config.safe_operating_region.i_abc_in_A.upper_bound >= config.safe_operating_region.i_abc_in_A.lower_bound);
    uz_assert(config.safe_operating_region.v_dc_in_V.upper_bound >= config.safe_operating_region.v_dc_in_V.lower_bound);
    uz_assert(config.safe_operating_region.i_dc_in_A.upper_bound >= config.safe_operating_region.i_dc_in_A.lower_bound);

    uz_assert(config.setpoint_filter_i_dq_cutoff_frequency >= 0.0f);
    uz_assert(config.setpoint_filter_speed_cutoff_frequency >= 0.0f);
    uz_assert(config.speed_actual_value_filter_cutoff_frequency >= 0.0f);

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
            .upper_limit = 1.0f, // Voltage limits are set to infinity internally by current control and voltage limitation acts on the output voltage vector determined by max modulation index.
            .lower_limit = -1.0f},
        .config_iq = {.Kp = config.current_controller_q_kp, .Ki = config.current_controller_q_ki, .samplingTime_sec = config.sample_time, .upper_limit = 1.0f, .lower_limit = -1.0f},
        .max_modulation_index = 1.0f / sqrtf(3.0f)};

    struct uz_SpeedControl_config speed_controller_configuration = {
        .config_controller.Kp = config.speed_controller_kp,
        .config_controller.Ki = config.speed_controller_ki,
        .config_controller.samplingTime_sec = config.sample_time,
        .config_controller.upper_limit = config.setpoint_limits.speed_controller_torque_in_Nm.upper_bound,
        .config_controller.lower_limit = config.setpoint_limits.speed_controller_torque_in_Nm.lower_bound,
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
        self->setpoint_filter_i_dq = uz_dq_setpoint_filter_init(setpoint_filter_config);
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

const struct uz_pmsm_actual_data *uz_pmsm_control_get_actual_data(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return &self->actual_values;
}

const struct uz_pmsm_reference_values *uz_pmsm_control_get_reference_values(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return &self->reference_values;
}

const struct uz_pmsm_measurement_values *uz_pmsm_control_get_pmsm_measurement_values(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return &self->measurement;
}

const float *uz_pmsm_control_get_pointer_to_theta_offset(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return &self->config.theta_el_offset;
}

enum uz_pmsm_control_safe_operating_region_violation uz_pmsm_control_get_safe_operating_area_violation(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->safe_operating_region_violation;
}

void uz_pmsm_control_reset(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_reset(self->current_controller);
    uz_SpeedControl_reset(self->speed_controller);
    if (self->setpoint_filter_i_dq != NULL)    {
        uz_dq_setpoint_filter_reset(self->setpoint_filter_i_dq);
    }
    if (self->setpoint_filter_speed != NULL)    {
        uz_signals_IIR_Filter_reset(self->setpoint_filter_speed);
    }
    if (self->speed_filter != NULL)    {
        uz_signals_IIR_Filter_reset(self->speed_filter);
    }

}

void uz_pmsm_control_enable(uz_pmsm_control_t *self, bool enable)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->enable = enable;
}

void uz_pmsm_control_acknowledge_and_reset_error(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->measurement = measurements;
    uz_pmsm_control_measured_to_actual_values(self);
    self->safe_operating_region_violation = uz_pmsm_control_no_violation;
    uz_pmsm_control_check_safe_operating_region(self);
}

static void uz_pmsm_control_measured_to_actual_values(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->actual_values.omega_el_rad_per_sec = self->measurement.omega_mech_rad_per_sec * self->machine_data.polePairs;
    self->actual_values.speed_in_rpm = self->measurement.omega_mech_rad_per_sec * 60.0f / (2.0f * UZ_PIf);
    float theta_el_without_offset = uz_signals_wrap(self->measurement.theta_mech * self->machine_data.polePairs, 2.0f * UZ_PIf);
    self->actual_values.theta_el = theta_el_without_offset - self->config.theta_el_offset;
    self->actual_values.theta_el = self->actual_values.theta_el + (self->config.theta_sampling_compensation * self->actual_values.omega_el_rad_per_sec * self->config.sample_time);
    float angle_for_voltage_measurement = self->actual_values.theta_el - (self->config.voltage_theta_shift * self->actual_values.omega_el_rad_per_sec) * self->config.sample_time;
    self->actual_values.theta_el = uz_signals_wrap(self->actual_values.theta_el, 2.0f * UZ_PIf);
    self->actual_values.theta_el_advanced = self->actual_values.theta_el + (self->config.theta_svm_delay_compensation * self->actual_values.omega_el_rad_per_sec) * self->config.sample_time;
    self->actual_values.i_dq_in_A = uz_transformation_3ph_abc_to_dq(self->measurement.i_abc_in_A, self->actual_values.theta_el);
    self->actual_values.v_dq_in_V = uz_transformation_3ph_abc_to_dq(self->measurement.v_abc_in_V, angle_for_voltage_measurement);
}

static void uz_pmsm_control_check_safe_operating_region(uz_pmsm_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    if (self->safe_operating_region_violation == uz_pmsm_control_no_violation) // Only check for violation if no violation is currently present. This means that the first time a violation occurs is stored until acknowledge_and_reset_error is called. If multiple violations are present at the same time, only the last one that is checked is stored. For example, if in ISR the check is executed each isr cycle and there is a under voltage detected, which turns off the system and in the next cycle a under speed is detected, only the initial under voltage is stored.
    // Could be changed such that for the last X time steps, all violations that occur are stored and double violations are logged as well. E.g., have an array that states if i_abc is present at step k, if speed violation is present at step k, etc.
    {
        if (fabsf(self->measurement.i_abc_in_A.a) > self->config.safe_operating_region.i_abc_in_A.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_abc_violation_upper;
        }
        if (fabsf(self->measurement.i_abc_in_A.b) > self->config.safe_operating_region.i_abc_in_A.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_abc_violation_upper;
        }
        if (fabsf(self->measurement.i_abc_in_A.c) > self->config.safe_operating_region.i_abc_in_A.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_abc_violation_upper;
        }

        // Speed
        if (self->actual_values.speed_in_rpm > self->config.safe_operating_region.speed_in_rpm.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_speed_violation_upper;
        }
        if (self->actual_values.speed_in_rpm < self->config.safe_operating_region.speed_in_rpm.lower_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_speed_violation_lower;
        }

        // dc-voltage
        if (self->measurement.v_dc_in_V > self->config.safe_operating_region.v_dc_in_V.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_v_dc_violation_upper;
        }
        if (self->measurement.v_dc_in_V < self->config.safe_operating_region.v_dc_in_V.lower_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_v_dc_violation_lower;
        }

        // dc-current
        if (self->measurement.i_dc_in_A > self->config.safe_operating_region.i_dc_in_A.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_dc_violation_upper;
        }
        if (self->measurement.i_dc_in_A < self->config.safe_operating_region.i_dc_in_A.lower_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_dc_violation_lower;
        }

        // i_d-current
        if (self->actual_values.i_dq_in_A.d > self->config.safe_operating_region.i_d_in_A.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_d_violation_upper;
        }
        if (self->actual_values.i_dq_in_A.d < self->config.safe_operating_region.i_d_in_A.lower_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_d_violation_lower;
        }
        // i_q-current
        if (self->actual_values.i_dq_in_A.q > self->config.safe_operating_region.i_q_in_A.upper_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_q_violation_upper;
        }
        if (self->actual_values.i_dq_in_A.q < self->config.safe_operating_region.i_q_in_A.lower_bound)
        {
            self->safe_operating_region_violation = uz_pmsm_control_i_q_violation_lower;
        }
    }
}

void uz_pmsm_control_enable_speed_control(uz_pmsm_control_t *self, bool enable_speed_control)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.enable_speed_control = enable_speed_control;
}

void uz_pmsm_control_set_theta_offset(uz_pmsm_control_t *self, float theta_offset)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.theta_el_offset = theta_offset;
}

struct uz_3ph_dq_t uz_pmsm_control_sample_dq(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements, float reference_speed_in_rpm, uz_3ph_dq_t reference_currents, float disturbance_input_in_Nm)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    reference_speed_in_rpm = uz_signals_saturation(reference_speed_in_rpm, self->config.setpoint_limits.speed_in_rpm.upper_bound, self->config.setpoint_limits.speed_in_rpm.lower_bound);
    reference_currents.d = uz_signals_saturation(reference_currents.d, self->config.setpoint_limits.i_d_in_A.upper_bound, self->config.setpoint_limits.i_d_in_A.lower_bound);
    reference_currents.q = uz_signals_saturation(reference_currents.q, self->config.setpoint_limits.i_q_in_A.upper_bound, self->config.setpoint_limits.i_q_in_A.lower_bound);
    disturbance_input_in_Nm = uz_signals_saturation(disturbance_input_in_Nm, self->config.setpoint_limits.disturbance_input_in_Nm.upper_bound, self->config.setpoint_limits.disturbance_input_in_Nm.lower_bound);

    if (self->config.speed_actual_value_filter_cutoff_frequency != 0.0f)
    {
        measurements.omega_mech_rad_per_sec = uz_signals_IIR_Filter_sample(self->speed_filter, measurements.omega_mech_rad_per_sec);
    }

    self->measurement = measurements;
    uz_pmsm_control_measured_to_actual_values(self);
    uz_pmsm_control_check_safe_operating_region(self);

    if (self->config.setpoint_filter_speed_cutoff_frequency != 0.0f)
    {
        self->reference_values.speed_in_rpm = uz_signals_IIR_Filter_sample(self->setpoint_filter_speed, reference_speed_in_rpm);
    }
    else
    {
        self->reference_values.speed_in_rpm = reference_speed_in_rpm;
    }

    if (self->enable && self->safe_operating_region_violation == uz_pmsm_control_no_violation)
    {
        if (self->config.enable_speed_control)
        {
            self->reference_values.M_in_Nm = uz_SpeedControl_sample(self->speed_controller, self->measurement.omega_mech_rad_per_sec, self->reference_values.speed_in_rpm);
            float ref_plus_disturbance_input = disturbance_input_in_Nm + self->reference_values.M_in_Nm;
            if ((ref_plus_disturbance_input > self->config.setpoint_limits.speed_controller_torque_in_Nm.upper_bound) || (ref_plus_disturbance_input < self->config.setpoint_limits.speed_controller_torque_in_Nm.lower_bound))
            {
                uz_SpeedControl_set_ext_clamping(self->speed_controller, true);
            }
            else
            {
                uz_SpeedControl_set_ext_clamping(self->speed_controller, false);
            }
            self->reference_values.M_in_Nm = uz_signals_saturation(ref_plus_disturbance_input, self->config.setpoint_limits.speed_controller_torque_in_Nm.upper_bound, self->config.setpoint_limits.speed_controller_torque_in_Nm.lower_bound);
            self->reference_values.i_dq_in_A = uz_SetPoint_sample(self->setpoint_module, self->measurement.omega_mech_rad_per_sec, self->reference_values.M_in_Nm, self->measurement.v_dc_in_V, self->actual_values.i_dq_in_A);
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
        self->reference_values.i_dq_in_A.d = uz_signals_saturation(self->reference_values.i_dq_in_A.d, self->config.setpoint_limits.i_d_in_A.upper_bound, self->config.setpoint_limits.i_d_in_A.lower_bound);
        self->reference_values.i_dq_in_A.q = uz_signals_saturation(self->reference_values.i_dq_in_A.q, self->config.setpoint_limits.i_q_in_A.upper_bound, self->config.setpoint_limits.i_q_in_A.lower_bound);
        self->reference_values.v_dq_in_V = uz_CurrentControl_sample(self->current_controller, self->reference_values.i_dq_in_A, self->actual_values.i_dq_in_A, self->measurement.v_dc_in_V, self->actual_values.omega_el_rad_per_sec);
        self->reference_values.v_abc_in_V = uz_transformation_3ph_dq_to_abc(self->reference_values.v_dq_in_V, self->actual_values.theta_el_advanced);
    }
    else
    {
        uz_pmsm_control_reset(self);
        self->reference_values.v_dq_in_V.d = 0.0f;
        self->reference_values.v_dq_in_V.q = 0.0f;
        self->reference_values.v_dq_in_V.zero = 0.0f;
    }
    return self->reference_values.v_dq_in_V;
}

struct uz_DutyCycle_t uz_pmsm_control_sample_duty(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements, float reference_speed_in_rpm, uz_3ph_dq_t reference_currents, float disturbance_input_in_Nm)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_3ph_dq_t v_dq_in_v = uz_pmsm_control_sample_dq(self, measurements, reference_speed_in_rpm, reference_currents, disturbance_input_in_Nm);
    if (self->enable && self->safe_operating_region_violation == uz_pmsm_control_no_violation)
    {
        self->reference_values.duty_cycle = uz_Space_Vector_Modulation(v_dq_in_v, self->measurement.v_dc_in_V, self->actual_values.theta_el_advanced);
    }
    else
    {
        self->reference_values.duty_cycle.DutyCycle_A = self->config.default_duty_cycle.DutyCycle_A;
        self->reference_values.duty_cycle.DutyCycle_B = self->config.default_duty_cycle.DutyCycle_B;
        self->reference_values.duty_cycle.DutyCycle_C = self->config.default_duty_cycle.DutyCycle_C;
    }

    return self->reference_values.duty_cycle;
}

void uz_pmsm_control_current_control_tune_magnitude_optimum(uz_pmsm_control_t *self, float tau_sigma_sec)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_tune_magnitude_optimum(self->current_controller, tau_sigma_sec);
}

void uz_pmsm_control_current_control_tune_symmetric_optimum(uz_pmsm_control_t *self, float tau_sigma_sec)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_tune_symmetric_optimum(self->current_controller, tau_sigma_sec);
}

void uz_pmsm_control_current_control_tune_bandwidth(uz_pmsm_control_t *self, float bandwidth_rad_per_sec)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_tune_bandwidth(self->current_controller, bandwidth_rad_per_sec);
}

void uz_pmsm_control_current_control_set_Kp_iq(uz_pmsm_control_t *self, float Kp_iq)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_set_Kp_iq(self->current_controller, Kp_iq);
}

void uz_pmsm_control_current_control_set_Ki_iq(uz_pmsm_control_t *self, float Ki_iq)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_set_Ki_iq(self->current_controller, Ki_iq);
}
void uz_pmsm_control_current_control_set_Kp_id(uz_pmsm_control_t *self, float Kp_id)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_set_Kp_id(self->current_controller, Kp_id);
}

void uz_pmsm_control_current_control_set_Ki_id(uz_pmsm_control_t *self, float Ki_id)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_CurrentControl_set_Ki_id(self->current_controller, Ki_id);
}

void uz_pmsm_control_speed_control_set_Kp_speed(uz_pmsm_control_t *self, float Kp_speed)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_SpeedControl_set_Kp(self->speed_controller, Kp_speed);
}

void uz_pmsm_control_speed_control_set_Ki_speed(uz_pmsm_control_t *self, float Ki_speed)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_SpeedControl_set_Ki(self->speed_controller, Ki_speed);
}
#endif
