/******************************************************************************

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

#include "uz_VoltageCompensation.h"
#include "../uz_global_configuration.h"
#include <math.h>

#if UZ_VOLTAGE_COMPENSATION_MAX_INSTANCES > 0

typedef struct uz_VoltageCompensation_t {
    bool is_ready;
    struct uz_VoltageCompensation_config config;
} uz_VoltageCompensation_t;

static uint32_t instances_counter_VoltageCompensation = 0;
static uz_VoltageCompensation_t instances_VoltageCompensation[UZ_VOLTAGE_COMPENSATION_MAX_INSTANCES] = {0};

static float uz_VoltageCompensation_interpolate_voltage_drop(float current, float* currents, float* voltages, int size) {
    if (size < 2) return 0.0f;
    float abs_current = fabsf(current);
    if (abs_current <= currents[0]) return voltages[0];
    if (abs_current >= currents[size-1]) return voltages[size-1];
    for (int i = 0; i < size - 1; i++) {
        if (abs_current >= currents[i] && abs_current <= currents[i+1]) {
            float ratio = (abs_current - currents[i]) / (currents[i+1] - currents[i]);
            return voltages[i] + ratio * (voltages[i+1] - voltages[i]);
        }
    }
    return 0.0f;
}

static float uz_VoltageCompensation_interpolate_delay_time(float current, float* current_values, float* delay_time_values, int size) {
    if (size < 2) return delay_time_values[0];
    float abs_current = fabsf(current);
    if (abs_current <= current_values[0]) return delay_time_values[0];
    if (abs_current >= current_values[size-1]) return delay_time_values[size-1];
    for (int i = 0; i < size - 1; i++) {
        if (abs_current >= current_values[i] && abs_current <= current_values[i+1]) {
            float ratio = (abs_current - current_values[i]) / (current_values[i+1] - current_values[i]);
            return delay_time_values[i] + ratio * (delay_time_values[i+1] - delay_time_values[i]);
        }
    }
    return 0.0f;
}

static float uz_VoltageCompensation_lookup_table_sign(float value, const struct uz_VoltageCompensation_config* config) {
    if ((config->dead_time_lut_currents_A == NULL) || (config->dead_time_lut_values == NULL) || (config->dead_time_lut_size < 2)) {
        return 0.0f;
    }

    if (value <= config->dead_time_lut_currents_A[0]) {
        return config->dead_time_lut_values[0];
    }
    if (value >= config->dead_time_lut_currents_A[config->dead_time_lut_size - 1]) {
        return config->dead_time_lut_values[config->dead_time_lut_size - 1];
    }

    for (int i = 0; i < config->dead_time_lut_size - 1; i++) {
        if (value >= config->dead_time_lut_currents_A[i] && value <= config->dead_time_lut_currents_A[i + 1]) {
            float ratio = (value - config->dead_time_lut_currents_A[i]) /
                (config->dead_time_lut_currents_A[i + 1] - config->dead_time_lut_currents_A[i]);
            return config->dead_time_lut_values[i] + ratio * (config->dead_time_lut_values[i + 1] - config->dead_time_lut_values[i]);
        }
    }

    return 0.0f;
}

static float uz_VoltageCompensation_exponential_sign(float value, float threshold, const struct uz_VoltageCompensation_config* config) {
    float abs_threshold = fabsf(threshold);
    if (abs_threshold <= 0.0f) {
        if (value > 0.0f) return 1.0f;
        if (value < 0.0f) return -1.0f;
        return 0.0f;
    }

    if (value >= abs_threshold) return 1.0f;
    if (value <= -abs_threshold) return -1.0f;
    if (value == 0.0f) return 0.0f;

    float abs_value = fabsf(value);
    float inner = powf(config->dead_time_exp_B * abs_value, config->dead_time_exp_C);
    float amplitude = config->dead_time_exp_A * powf(1.0f - expf(-inner), config->dead_time_exp_S);
    if (amplitude > 1.0f) {
        amplitude = 1.0f;
    }
    return copysignf(amplitude, value);
}

static float uz_VoltageCompensation_dead_time_shape(float value, const struct uz_VoltageCompensation_config* config) {
    if (config->dead_time_compensation_type == UZ_VOLTAGE_COMPENSATION_DEAD_TIME_USE_EXPONENTIAL_FUNCTION) {
        return uz_VoltageCompensation_exponential_sign(value, config->threshold_current, config);
    }
    return uz_VoltageCompensation_lookup_table_sign(value, config);
}

static float clamp01(float x) {
    if (x < 0.0f) return 0.0f;
    if (x > 1.0f) return 1.0f;
    return x;
}

uz_VoltageCompensation_t* uz_VoltageCompensation_init(struct uz_VoltageCompensation_config config) {
    uz_assert(instances_counter_VoltageCompensation < UZ_VOLTAGE_COMPENSATION_MAX_INSTANCES);
    uz_VoltageCompensation_t* self = &instances_VoltageCompensation[instances_counter_VoltageCompensation];
    uz_assert_false(self->is_ready);
    self->is_ready = true;
    self->config = config;
    instances_counter_VoltageCompensation++;
    return self;
}

struct uz_DutyCycle_t uz_VoltageCompensation_sample(uz_VoltageCompensation_t* self, struct uz_DutyCycle_t duty_cycle_ref, uz_3ph_abc_t i_actual_abc_A, float dc_link_voltage_V) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    struct uz_DutyCycle_t compensated_duty_cycle = duty_cycle_ref;

    // Diode voltage drop compensation
    if (self->config.enable_voltage_drop_compensation) {
        float diode_voltage_offset_a = uz_VoltageCompensation_interpolate_voltage_drop(i_actual_abc_A.a, self->config.diode_currents_A, self->config.diode_voltages_V, self->config.diode_table_size);
        float diode_voltage_offset_b = uz_VoltageCompensation_interpolate_voltage_drop(i_actual_abc_A.b, self->config.diode_currents_A, self->config.diode_voltages_V, self->config.diode_table_size);
        float diode_voltage_offset_c = uz_VoltageCompensation_interpolate_voltage_drop(i_actual_abc_A.c, self->config.diode_currents_A, self->config.diode_voltages_V, self->config.diode_table_size);

        float transistor_voltage_offset_a = uz_VoltageCompensation_interpolate_voltage_drop(i_actual_abc_A.a, self->config.transistor_currents_A, self->config.transistor_voltages_V, self->config.transistor_table_size);
        float transistor_voltage_offset_b = uz_VoltageCompensation_interpolate_voltage_drop(i_actual_abc_A.b, self->config.transistor_currents_A, self->config.transistor_voltages_V, self->config.transistor_table_size);
        float transistor_voltage_offset_c = uz_VoltageCompensation_interpolate_voltage_drop(i_actual_abc_A.c, self->config.transistor_currents_A, self->config.transistor_voltages_V, self->config.transistor_table_size);

        if (i_actual_abc_A.a > 0) {  
            compensated_duty_cycle.DutyCycle_A = ((compensated_duty_cycle.DutyCycle_A * dc_link_voltage_V) + diode_voltage_offset_a) /
            (dc_link_voltage_V + diode_voltage_offset_a - transistor_voltage_offset_a);
        } else if(i_actual_abc_A.a < 0){
            compensated_duty_cycle.DutyCycle_A = ((compensated_duty_cycle.DutyCycle_A * dc_link_voltage_V) + transistor_voltage_offset_a) /
            (dc_link_voltage_V - diode_voltage_offset_a + transistor_voltage_offset_a);
        }
        if (i_actual_abc_A.b > 0) {  
            compensated_duty_cycle.DutyCycle_B = ((compensated_duty_cycle.DutyCycle_B * dc_link_voltage_V) + diode_voltage_offset_b) /
            (dc_link_voltage_V + diode_voltage_offset_b - transistor_voltage_offset_b);
        } else if(i_actual_abc_A.b < 0){
            compensated_duty_cycle.DutyCycle_B = ((compensated_duty_cycle.DutyCycle_B * dc_link_voltage_V) + transistor_voltage_offset_b) /
            (dc_link_voltage_V - diode_voltage_offset_b + transistor_voltage_offset_b);
        }
        if (i_actual_abc_A.c > 0) {  
            compensated_duty_cycle.DutyCycle_C = ((compensated_duty_cycle.DutyCycle_C * dc_link_voltage_V) + diode_voltage_offset_c) /
            (dc_link_voltage_V + diode_voltage_offset_c - transistor_voltage_offset_c);
        } else if(i_actual_abc_A.c < 0){
            compensated_duty_cycle.DutyCycle_C = ((compensated_duty_cycle.DutyCycle_C * dc_link_voltage_V) + transistor_voltage_offset_c) /
            (dc_link_voltage_V - diode_voltage_offset_c + transistor_voltage_offset_c);
        }
    }

    if (self->config.enable_R_on_compensation){
		if (fabs(i_actual_abc_A.a) > self->config.threshold_current){
			compensated_duty_cycle.DutyCycle_A += (fabs(i_actual_abc_A.a) * self->config.R_on_mOhm / 1000.0f)/dc_link_voltage_V;
		}
		if (fabs(i_actual_abc_A.b) > self->config.threshold_current){
			compensated_duty_cycle.DutyCycle_B += (fabs(i_actual_abc_A.b) * self->config.R_on_mOhm / 1000.0f)/dc_link_voltage_V;
		}
		if (fabs(i_actual_abc_A.c) > self->config.threshold_current){
			compensated_duty_cycle.DutyCycle_C += (fabs(i_actual_abc_A.c) * self->config.R_on_mOhm / 1000.0f)/dc_link_voltage_V;
		}
    }

    // Dead time compensation
    if (self->config.enable_dead_time_compensation) {
        float dead_time_duty_offset = (self->config.dead_time_us * 1e-6f) * self->config.switching_frequency_Hz;
        // Simple compensation: adjust duty cycle based on current direction
        compensated_duty_cycle.DutyCycle_A += uz_VoltageCompensation_dead_time_shape(i_actual_abc_A.a, &self->config) * dead_time_duty_offset;
        compensated_duty_cycle.DutyCycle_B += uz_VoltageCompensation_dead_time_shape(i_actual_abc_A.b, &self->config) * dead_time_duty_offset;
        compensated_duty_cycle.DutyCycle_C += uz_VoltageCompensation_dead_time_shape(i_actual_abc_A.c, &self->config) * dead_time_duty_offset;
    }

    // Compensation of on-delay-time of transistor and diode
    if(self->config.enable_on_delay_time_compensation){
        // Diode delay time
        float delay_time_diode_a = uz_VoltageCompensation_interpolate_delay_time(i_actual_abc_A.a, self->config.diode_delay_time_current_A, 
            self->config.diode_delay_time_s, self->config.diode_delay_time_table_size);
        float delay_time_diode_b = uz_VoltageCompensation_interpolate_delay_time(i_actual_abc_A.b, self->config.diode_delay_time_current_A, 
            self->config.diode_delay_time_s, self->config.diode_delay_time_table_size);
        float delay_time_diode_c = uz_VoltageCompensation_interpolate_delay_time(i_actual_abc_A.c, self->config.diode_delay_time_current_A, 
            self->config.diode_delay_time_s, self->config.diode_delay_time_table_size);

        // Transistor delay time
        float delay_time_transistor_a = uz_VoltageCompensation_interpolate_delay_time(i_actual_abc_A.a, self->config.transistor_delay_time_current_A, self->config.transistor_delay_time_s, self->config.transistor_delay_time_table_size);
        float delay_time_transistor_b = uz_VoltageCompensation_interpolate_delay_time(i_actual_abc_A.b, self->config.transistor_delay_time_current_A, self->config.transistor_delay_time_s, self->config.transistor_delay_time_table_size);
        float delay_time_transistor_c = uz_VoltageCompensation_interpolate_delay_time(i_actual_abc_A.c, self->config.transistor_delay_time_current_A, self->config.transistor_delay_time_s, self->config.transistor_delay_time_table_size);

        compensated_duty_cycle.DutyCycle_A += uz_VoltageCompensation_dead_time_shape(i_actual_abc_A.a, &self->config) * (delay_time_transistor_a - delay_time_diode_a) * self->config.switching_frequency_Hz;
        compensated_duty_cycle.DutyCycle_B += uz_VoltageCompensation_dead_time_shape(i_actual_abc_A.b, &self->config) * (delay_time_transistor_b - delay_time_diode_b) * self->config.switching_frequency_Hz;
        compensated_duty_cycle.DutyCycle_C += uz_VoltageCompensation_dead_time_shape(i_actual_abc_A.c, &self->config) * (delay_time_transistor_c - delay_time_diode_c) * self->config.switching_frequency_Hz;
    }

    // Clamp to [0,1]
    compensated_duty_cycle.DutyCycle_A = clamp01(compensated_duty_cycle.DutyCycle_A);
    compensated_duty_cycle.DutyCycle_B = clamp01(compensated_duty_cycle.DutyCycle_B);
    compensated_duty_cycle.DutyCycle_C = clamp01(compensated_duty_cycle.DutyCycle_C);


    return compensated_duty_cycle;
}

#endif
