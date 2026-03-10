/******************************************************************************
 * Copyright 2026
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

#include "../include/im_uf_control.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_math_constants.h"
#include <math.h>

void im_uf_control_reset(im_uf_control_state_t *state)
{
    uz_assert_not_NULL(state);
    state->frequency_command_Hz = 0.0f;
    state->electrical_phase_rad = 0.0f;
}

uz_3ph_abc_t im_uf_control_step(const actualValues *av,
                                 referenceAndSetValues *rasv,
                                 const im_uf_control_config_t *config,
                                 im_uf_control_state_t *state,
                                 float duty_offset)
{
    uz_assert_not_NULL(av);
    uz_assert_not_NULL(rasv);
    uz_assert_not_NULL(config);
    uz_assert_not_NULL(state);

    float const ts = fmaxf(av->isr_samplerate_s, 1.0e-6f);
    float const freq_target_limited = fminf(fmaxf(config->frequency_setpoint_Hz, 0.0f), config->max_frequency_Hz);
    float const freq_step_max = fmaxf(config->frequency_ramp_Hz_per_s, 0.1f) * ts;
    float const freq_error = freq_target_limited - state->frequency_command_Hz;
    if (freq_error > freq_step_max) {
        state->frequency_command_Hz += freq_step_max;
    } else if (freq_error < -freq_step_max) {
        state->frequency_command_Hz -= freq_step_max;
    } else {
        state->frequency_command_Hz = freq_target_limited;
    }

    float const freq_limited = state->frequency_command_Hz;
    float const boost_voltage = (freq_limited > 0.1f) ? config->boost_voltage_V : 0.0f;
    float voltage_magnitude = (config->ratio_V_per_Hz * freq_limited) + boost_voltage;
    voltage_magnitude = fminf(voltage_magnitude, config->max_voltage_V);

    float duty_amplitude = voltage_magnitude / fmaxf(av->U_DC, 1.0f);
    duty_amplitude = fminf(duty_amplitude, 0.45f);
    duty_amplitude = fmaxf(duty_amplitude, 0.0f);

    float const omega_cmd_rad_s = 2.0f * UZ_PIf * freq_limited;
    state->electrical_phase_rad += omega_cmd_rad_s * ts;
    state->electrical_phase_rad = fmodf(state->electrical_phase_rad, 2.0f * UZ_PIf);
    if (state->electrical_phase_rad < 0.0f) {
        state->electrical_phase_rad += 2.0f * UZ_PIf;
    }

    float v1 = duty_amplitude * sinf(state->electrical_phase_rad) + duty_offset;
    float v2 = duty_amplitude * sinf(state->electrical_phase_rad - (2.0f * UZ_PIf / 3.0f)) + duty_offset;
    float v3 = duty_amplitude * sinf(state->electrical_phase_rad - (4.0f * UZ_PIf / 3.0f)) + duty_offset;

    int const pwm_mode = 0;
    if (pwm_mode == 1) {
        float const cm = fminf(fminf(v1, v2), v3);
        v1 -= cm;
        v2 -= cm;
        v3 -= cm;
    }

    v1 = fminf(fmaxf(v1, 0.0f), 1.0f);
    v2 = fminf(fmaxf(v2, 0.0f), 1.0f);
    v3 = fminf(fmaxf(v3, 0.0f), 1.0f);

    uz_3ph_abc_t const three_phase_duty = {.a = v1, .b = v2, .c = v3};
    rasv->halfBridge1DutyCycle = three_phase_duty.a;
    rasv->halfBridge2DutyCycle = three_phase_duty.b;
    rasv->halfBridge3DutyCycle = three_phase_duty.c;
    return three_phase_duty;
}
