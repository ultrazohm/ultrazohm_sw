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

#include "../include/im_foc_control.h"
#include "../include/motor_config.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include <math.h>

void im_foc_control_init(const uz_IM_t *im_config, float sampling_time_s, im_foc_control_state_t *state)
{
    uz_assert_not_NULL(im_config);
    uz_assert_not_NULL(state);
    uz_assert(sampling_time_s > 0.0f);

    if (state->pi_id == NULL) {
        float const ls = im_config->Lsigma_s_Henry + im_config->Lm_Henry;
        float const lr = im_config->Lsigma_r_Henry + im_config->Lm_Henry;
        float const sigma = 1.0f - (im_config->Lm_Henry * im_config->Lm_Henry) / (ls * lr);
        float const sigma_ls = sigma * ls;
        float const ts = fmaxf(sampling_time_s, 1.0e-6f);
        float const kp = sigma_ls / (2.0f * ts) * MOTOR_Current_Kp_scale;
        float const ki = im_config->Rs_Ohm / (2.0f * ts) * MOTOR_Current_Ki_scale;

        struct uz_PI_Controller_config const pi_cfg = {
            .type = UZ_PI_PARALLEL,
            .Kp = kp,
            .Ki = ki,
            .samplingTime_sec = ts,
            .upper_limit = 400.0f,
            .lower_limit = -400.0f,
        };
        state->pi_id = uz_PI_Controller_init(pi_cfg);
        state->pi_iq = uz_PI_Controller_init(pi_cfg);

        struct uz_PI_Controller_config const speed_cfg = {
            .type = UZ_PI_PARALLEL,
            .Kp = MOTOR_Speed_Kp,
            .Ki = MOTOR_Speed_Ki,
            .samplingTime_sec = ts,
            .upper_limit = im_config->I_max_Ampere,
            .lower_limit = -im_config->I_max_Ampere,
        };
        state->pi_speed = uz_PI_Controller_init(speed_cfg);

        struct uz_resonantController_config const resonant_cfg = {
            .sampling_time = ts,
            .gain = MOTOR_Resonant_gain_scale * kp,
            .harmonic_order = 6.0f,
            .fundamental_frequency = 1.0f,
            .lower_limit = -100.0f,
            .upper_limit = 100.0f,
            .antiwindup_gain = 10.0f,
            .in_reference_value = 0.0f,
            .in_measured_value = 0.0f
        };
        state->res_id_6th = uz_resonantController_init(resonant_cfg);
        state->res_iq_6th = uz_resonantController_init(resonant_cfg);
        state->resonant_enabled_last = false;
    }
}

void im_foc_control_reset(im_foc_control_state_t *state)
{
    uz_assert_not_NULL(state);
    if (state->pi_id != NULL) {
        uz_PI_Controller_reset(state->pi_id);
    }
    if (state->pi_iq != NULL) {
        uz_PI_Controller_reset(state->pi_iq);
    }
    if (state->pi_speed != NULL) {
        uz_PI_Controller_reset(state->pi_speed);
    }
    if (state->res_id_6th != NULL) {
        uz_resonantController_reset(state->res_id_6th);
    }
    if (state->res_iq_6th != NULL) {
        uz_resonantController_reset(state->res_iq_6th);
    }
    state->resonant_enabled_last = false;
    state->resonant_omega_filtered = 0.0f;
}

void im_foc_control_step(actualValues *av,
                          referenceAndSetValues *rasv,
                          const uz_IM_t *im_config,
                          const im_foc_control_input_t *input,
                          float omega_el_rad_s,
                          float psi_r_mag,
                          float theta_flux_rad,
                          im_foc_control_state_t *state,
                          im_foc_control_output_t *output)
{
    uz_assert_not_NULL(av);
    uz_assert_not_NULL(rasv);
    uz_assert_not_NULL(im_config);
    uz_assert_not_NULL(input);
    uz_assert_not_NULL(state);
    uz_assert_not_NULL(output);
    uz_assert_not_NULL(state->pi_id);
    uz_assert_not_NULL(state->pi_iq);
    uz_assert_not_NULL(state->pi_speed);
    uz_assert_not_NULL(state->res_id_6th);
    uz_assert_not_NULL(state->res_iq_6th);

    output->id_cmd_A = input->id_ref_A;
    if (input->use_speed_control) {
        output->iq_cmd_A = uz_PI_Controller_sample(state->pi_speed, input->speed_ref_rpm, av->mechanicalRotorSpeed_filtered, false);
    } else {
        output->iq_cmd_A = input->iq_ref_A;
        if (state->pi_speed != NULL) {
            uz_PI_Controller_reset(state->pi_speed);
        }
    }

    float const ud_pi = uz_PI_Controller_sample(state->pi_id, input->id_ref_A, av->I_d, false);
    float const uq_pi = uz_PI_Controller_sample(state->pi_iq, output->iq_cmd_A, av->I_q, false);
    float ud_res = 0.0f;
    float uq_res = 0.0f;

    if (input->use_resonant_6th) {
        // Use the det PLL omega_s (smooth) not KF omega_s (noisy) for frequency tracking.
        float const omega_raw = fmaxf(fabsf(input->omega_s_for_resonant_rad_s), 1.0f);
        // IIR low-pass filter on the fundamental frequency fed to the resonant controller.
        // fc ≈ 8 Hz at 25 kHz ISR (alpha = 0.002). Prevents abrupt omega_s jumps during
        // speed transients from pushing the resonant controller to an unsettled frequency.
        float const alpha_res = 0.002f;
        state->resonant_omega_filtered += alpha_res * (omega_raw - state->resonant_omega_filtered);
        // Use measured (raw abc→dq) currents for the resonant controller so that
        // the full harmonic content is visible even when the KF observer smooths av.I_d/I_q.
        ud_res = uz_resonantController_step(state->res_id_6th, input->id_ref_A, input->id_meas_A, state->resonant_omega_filtered);
        uq_res = uz_resonantController_step(state->res_iq_6th, output->iq_cmd_A, input->iq_meas_A, state->resonant_omega_filtered);
    } else if (state->resonant_enabled_last) {
        uz_resonantController_reset(state->res_id_6th);
        uz_resonantController_reset(state->res_iq_6th);
        state->resonant_omega_filtered = 0.0f;
    }
    state->resonant_enabled_last = input->use_resonant_6th;

    float const ls = im_config->Lsigma_s_Henry + im_config->Lm_Henry;
    float const lr = im_config->Lsigma_r_Henry + im_config->Lm_Henry;
    float const sigma = 1.0f - (im_config->Lm_Henry * im_config->Lm_Henry) / (ls * lr);
    float const sigma_ls = sigma * ls;
    float const ud_decoup = -omega_el_rad_s * sigma_ls * av->I_q;
    float const uq_decoup = omega_el_rad_s * sigma_ls * av->I_d +
                            omega_el_rad_s * (im_config->Lm_Henry / lr) * psi_r_mag;

    output->ud_pi    = ud_pi;
    output->uq_pi    = uq_pi;
    output->ud_decoup = ud_decoup;
    output->uq_decoup = uq_decoup;
    output->ud_res   = ud_res;
    output->uq_res   = uq_res;

    uz_3ph_dq_t const v_dq_ref = {
        .d = ud_pi + ud_res + ud_decoup,
        .q = uq_pi + uq_res + uq_decoup,
        .zero = 0.0f
    };

    av->U_d = v_dq_ref.d;
    av->U_q = v_dq_ref.q;

    struct uz_DutyCycle_t const duty = uz_Space_Vector_Modulation(v_dq_ref, av->U_DC, theta_flux_rad);

    rasv->halfBridge1DutyCycle = duty.DutyCycle_A;
    rasv->halfBridge2DutyCycle = duty.DutyCycle_B;
    rasv->halfBridge3DutyCycle = duty.DutyCycle_C;
}
