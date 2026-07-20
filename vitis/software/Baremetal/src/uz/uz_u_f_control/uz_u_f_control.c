/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "../uz_global_configuration.h"
#if UZ_U_F_CONTROL_MAX_INSTANCES > 0U
#include "uz_u_f_control.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

struct uz_u_f_control_t
{
    bool is_ready;
    struct uz_u_f_control_config_t config;
    struct uz_u_f_control_data_t data;
    enum uz_u_f_control_safe_operating_region_violation safe_operating_region_violation;
};

static uint32_t instance_counter = 0U;
static uz_u_f_control_t instances[UZ_U_F_CONTROL_MAX_INSTANCES] = {0};

static uz_u_f_control_t *uz_u_f_control_allocation(void)
{
    uz_assert(instance_counter < UZ_U_F_CONTROL_MAX_INSTANCES);
    uz_u_f_control_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return self;
}

static void uz_u_f_control_check_dc_link_voltage(uz_u_f_control_t *self, float dc_link_voltage_V)
{
    if (self->safe_operating_region_violation == uz_u_f_control_no_violation)
    {
        if ((!isfinite(dc_link_voltage_V)) || (dc_link_voltage_V < self->config.dc_link_voltage_lower_bound_V))
        {
            self->safe_operating_region_violation = uz_u_f_control_dc_link_voltage_violation_lower;
        }
        else if (dc_link_voltage_V > self->config.dc_link_voltage_upper_bound_V)
        {
            self->safe_operating_region_violation = uz_u_f_control_dc_link_voltage_violation_upper;
        }
    }
}

static void uz_u_f_control_check_duty_cycle(uz_u_f_control_t *self, struct uz_DutyCycle_t duty_cycle)
{
    if (self->safe_operating_region_violation == uz_u_f_control_no_violation)
    {
        float const lower_bound = self->config.minimum_pulse_width;
        float const upper_bound = 1.0f - self->config.minimum_pulse_width;
        if ((!isfinite(duty_cycle.DutyCycle_A)) || (!isfinite(duty_cycle.DutyCycle_B)) || (!isfinite(duty_cycle.DutyCycle_C)) ||
            (duty_cycle.DutyCycle_A < lower_bound) || (duty_cycle.DutyCycle_B < lower_bound) || (duty_cycle.DutyCycle_C < lower_bound))
        {
            self->safe_operating_region_violation = uz_u_f_control_duty_cycle_violation_lower;
        }
        else if ((duty_cycle.DutyCycle_A > upper_bound) || (duty_cycle.DutyCycle_B > upper_bound) || (duty_cycle.DutyCycle_C > upper_bound))
        {
            self->safe_operating_region_violation = uz_u_f_control_duty_cycle_violation_upper;
        }
    }
}

uz_u_f_control_t *uz_u_f_control_init(struct uz_u_f_control_config_t config)
{
    uz_assert(config.max_frequency_Hz >= 0.0f);
    uz_assert(config.frequency_ramp_Hz_per_s >= 0.0f);
    uz_assert(config.ratio_V_per_Hz >= 0.0f);
    uz_assert(config.boost_voltage_V >= 0.0f);
    uz_assert(config.max_voltage_V >= 0.0f);
    uz_assert(config.minimum_pulse_width >= 0.0f);
    uz_assert(config.minimum_pulse_width < 0.5f);
    uz_assert(config.dc_link_voltage_lower_bound_V > 0.0f);
    uz_assert(config.dc_link_voltage_upper_bound_V >= config.dc_link_voltage_lower_bound_V);
    uz_assert(config.default_duty_cycle.DutyCycle_A >= 0.0f && config.default_duty_cycle.DutyCycle_A <= 1.0f);
    uz_assert(config.default_duty_cycle.DutyCycle_B >= 0.0f && config.default_duty_cycle.DutyCycle_B <= 1.0f);
    uz_assert(config.default_duty_cycle.DutyCycle_C >= 0.0f && config.default_duty_cycle.DutyCycle_C <= 1.0f);

    uz_u_f_control_t *self = uz_u_f_control_allocation();
    self->config = config;
    self->safe_operating_region_violation = uz_u_f_control_no_violation;
    uz_u_f_control_reset(self);
    return self;
}

void uz_u_f_control_reset(uz_u_f_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->data.frequency_command_Hz = 0.0f;
    self->data.electrical_phase_rad = 0.0f;
    self->data.applied_voltage_magnitude_V = 0.0f;
}

void uz_u_f_control_set_frequency(uz_u_f_control_t *self, float frequency_setpoint_Hz)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.frequency_setpoint_Hz = frequency_setpoint_Hz;
}

const struct uz_u_f_control_data_t *uz_u_f_control_get_data(uz_u_f_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return &self->data;
}

enum uz_u_f_control_safe_operating_region_violation uz_u_f_control_get_safe_operating_area_violation(uz_u_f_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->safe_operating_region_violation;
}

void uz_u_f_control_acknowledge_and_reset_error(uz_u_f_control_t *self, float dc_link_voltage_V)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->safe_operating_region_violation = uz_u_f_control_no_violation;
    uz_u_f_control_check_dc_link_voltage(self, dc_link_voltage_V);
    if (self->safe_operating_region_violation == uz_u_f_control_no_violation)
    {
        uz_u_f_control_reset(self);
    }
}

struct uz_DutyCycle_t uz_u_f_control_sample(uz_u_f_control_t *self, float dc_link_voltage_V, float sample_time_s)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uz_u_f_control_check_dc_link_voltage(self, dc_link_voltage_V);
    if (self->safe_operating_region_violation != uz_u_f_control_no_violation)
    {
        return self->config.default_duty_cycle;
    }

    float const ts = fmaxf(sample_time_s, 1.0e-6f);
    float const frequency_target_limited = fminf(fmaxf(self->config.frequency_setpoint_Hz, 0.0f), self->config.max_frequency_Hz);
    float const frequency_step_max = fmaxf(self->config.frequency_ramp_Hz_per_s, 0.1f) * ts;
    float const frequency_error = frequency_target_limited - self->data.frequency_command_Hz;
    if (frequency_error > frequency_step_max)
    {
        self->data.frequency_command_Hz += frequency_step_max;
    }
    else if (frequency_error < -frequency_step_max)
    {
        self->data.frequency_command_Hz -= frequency_step_max;
    }
    else
    {
        self->data.frequency_command_Hz = frequency_target_limited;
    }

    float const frequency_limited = self->data.frequency_command_Hz;
    float const boost_voltage = (frequency_limited > 0.1f) ? self->config.boost_voltage_V : 0.0f;
    float voltage_magnitude = (self->config.ratio_V_per_Hz * frequency_limited) + boost_voltage;
    voltage_magnitude = fminf(voltage_magnitude, self->config.max_voltage_V);
    self->data.applied_voltage_magnitude_V = voltage_magnitude;

    float const omega_command_rad_per_s = 2.0f * UZ_PIf * frequency_limited;
    self->data.electrical_phase_rad += omega_command_rad_per_s * ts;
    self->data.electrical_phase_rad = fmodf(self->data.electrical_phase_rad, 2.0f * UZ_PIf);
    if (self->data.electrical_phase_rad < 0.0f)
    {
        self->data.electrical_phase_rad += 2.0f * UZ_PIf;
    }

    /* Nameplate voltage is RMS line-to-line; SVM expects peak line-to-neutral. */
    float const dc_link_voltage_limited = fmaxf(dc_link_voltage_V, 1.0f);
    float const peak_line_to_neutral_max = dc_link_voltage_limited * (1.0f - 2.0f * self->config.minimum_pulse_width) / sqrtf(3.0f);
    float const peak_line_to_neutral = fminf(voltage_magnitude * sqrtf(2.0f / 3.0f), peak_line_to_neutral_max);
    uz_3ph_dq_t const voltage_reference = {.d = peak_line_to_neutral, .q = 0.0f, .zero = 0.0f};
    struct uz_DutyCycle_t const duty_cycle = uz_Space_Vector_Modulation(voltage_reference, dc_link_voltage_limited, self->data.electrical_phase_rad);
    uz_u_f_control_check_duty_cycle(self, duty_cycle);
    if (self->safe_operating_region_violation != uz_u_f_control_no_violation)
    {
        return self->config.default_duty_cycle;
    }
    return duty_cycle;
}
#endif
