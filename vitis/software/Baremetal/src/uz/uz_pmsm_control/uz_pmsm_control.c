#include "uz_pmsm_control.h"

#include "../uz_global_configuration.h"
#if UZ_PMSM_CONTROL_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_pmsm_control.h"
#include "../uz_math_constants.h"
#include "../uz_signals/uz_signals.h"

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
    uz_PMSM_t machine_data;
    bool enable;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_control_t instances[UZ_PMSM_CONTROL_MAX_INSTANCES] = {0};

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
        .config_controller.type = parallel};

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

    return (self);
}

struct uz_pmsm_actual_data * uz_pmsm_control_get_actual_data(uz_pmsm_control_t *self)
{
    return &self->actual_values; // is this a good idea?
}

struct uz_pmsm_reference_values  * uz_pmsm_control_get_reference_values(uz_pmsm_control_t *self)
{
    return &self->reference_values; // is this a good idea?
}

struct uz_pmsm_measurement_values  * uz_pmsm_control_get_uz_pmsm_measurement_values(uz_pmsm_control_t *self)
{
    return &self->measurement; // is this a good idea?
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

struct uz_DutyCycle_t uz_pmsm_controller_sample(uz_pmsm_control_t *self, struct uz_pmsm_measurement_values measurements, float reference_speed_in_rpm, uz_3ph_dq_t reference_currents)
{
    uz_assert(self->is_ready);
    self->actual_values.i_abc_in_A.a = (self->config.current_conversion_factors.a * measurements.phase_currents_from_adc_ampere_per_volt.a) + self->config.current_conversion_factors.a;
    self->actual_values.i_abc_in_A.b = (self->config.current_conversion_factors.b * measurements.phase_currents_from_adc_ampere_per_volt.b) + self->config.current_conversion_factors.b;
    self->actual_values.i_abc_in_A.c = (self->config.current_conversion_factors.c * measurements.phase_currents_from_adc_ampere_per_volt.c) + self->config.current_conversion_factors.c;
    self->actual_values.v_dc_in_V = (self->config.v_dc_in_V_conversion_factor * measurements.v_dc_from_adc_volt_per_volt) + self->config.v_dc_in_V_offset;
    self->actual_values.i_dc_in_A = (self->config.v_dc_in_V_conversion_factor * measurements.i_dc_from_adc_ampere_per_volt) + self->config.v_dc_in_V_offset;

    self->actual_values.omega_el_rad_per_sec = measurements.omega_mech_rad_per_sec * self->machine_data.polePairs;
    float theta_el_without_offset = uz_signals_wrap(measurements.theta_mech * self->machine_data.polePairs, 2.0f * UZ_PIf);
    self->actual_values.theta_el = theta_el_without_offset - self->config.theta_el_offset;
    self->actual_values.theta_el_advanced = self->actual_values.theta_el + (1.5f * self->actual_values.omega_el_rad_per_sec) * self->config.sample_time;

    self->actual_values.i_dq_in_A = uz_transformation_3ph_abc_to_dq(self->actual_values.i_abc_in_A, self->actual_values.theta_el);
    // n_ref_rpm_heidrive_filtered = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_setpoint_filter_heidrive, n_ref_rpm_heidrive);

    if (self->enable)
    {
        if (self->config.enable_speed_control)
        {
            self->reference_values.speed_in_rpm = reference_speed_in_rpm;
            self->reference_values.M_in_Nm = uz_SpeedControl_sample(self->speed_controller, self->measurement.omega_mech_rad_per_sec, self->reference_values.speed_in_rpm);
            // M_ref_Nm_heidrive=0.11f*i_dq_in_A_ref_Amps_brose.q+M_ref_Nm_heidrive_without; // Vorsteuerung Lastmoment
            self->reference_values.i_dq_in_A = uz_SetPoint_sample(self->setpoint_module, self->measurement.omega_mech_rad_per_sec, self->reference_values.M_in_Nm, self->actual_values.v_dc_in_V, self->actual_values.i_dq_in_A);
        }
        else
        {
            self->reference_values.i_dq_in_A = reference_currents;
        }
        self->reference_values.v_dq_in_V = uz_CurrentControl_sample(self->current_controller, self->reference_values.i_dq_in_A, self->actual_values.i_dq_in_A, self->actual_values.v_dc_in_V, self->actual_values.omega_el_rad_per_sec);
        self->reference_values.duty_cycle = uz_Space_Vector_Modulation(self->reference_values.v_dq_in_V, self->actual_values.v_dc_in_V, self->actual_values.theta_el_advanced);
    }
    else
    {
        uz_pmsm_controller_reset(self);
        return self->config.default_duty_cycle;
    }
    return self->reference_values.duty_cycle;
}

#endif
