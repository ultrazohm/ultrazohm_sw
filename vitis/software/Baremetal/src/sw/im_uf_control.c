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
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
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
                                 im_uf_control_state_t *state)
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

    float const omega_cmd_rad_s = 2.0f * UZ_PIf * freq_limited;
    state->electrical_phase_rad += omega_cmd_rad_s * ts;
    state->electrical_phase_rad = fmodf(state->electrical_phase_rad, 2.0f * UZ_PIf);
    if (state->electrical_phase_rad < 0.0f) {
        state->electrical_phase_rad += 2.0f * UZ_PIf;
    }

    /* voltage_magnitude is RMS L-L (nameplate convention).
     * SVM expects peak L-N: V_peak_LN = V_rms_LL * sqrt(2/3).
     * Applying as v_d with v_q=0 in the frame aligned to electrical_phase_rad
     * produces a rotating voltage vector of the correct magnitude and angle. */
    float const V_peak_LN = voltage_magnitude * sqrtf(2.0f / 3.0f);
    uz_3ph_dq_t const v_ref = {.d = V_peak_LN, .q = 0.0f, .zero = 0.0f};
    struct uz_DutyCycle_t const svm_duty_cycles = uz_Space_Vector_Modulation(v_ref, fmaxf(av->IM_vdc, 1.0f), state->electrical_phase_rad);

    uz_3ph_abc_t const three_phase_duty = {.a = svm_duty_cycles.DutyCycle_A, .b = svm_duty_cycles.DutyCycle_B, .c = svm_duty_cycles.DutyCycle_C};
    rasv->halfBridge1DutyCycle = three_phase_duty.a;
    rasv->halfBridge2DutyCycle = three_phase_duty.b;
    rasv->halfBridge3DutyCycle = three_phase_duty.c;
    return three_phase_duty;
}
