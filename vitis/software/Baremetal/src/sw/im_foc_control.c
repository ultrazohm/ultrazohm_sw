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
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include <math.h>

void im_foc_control_init(const uz_IM_t *im_config, float sampling_time_s, im_foc_control_state_t *state)
{
    uz_assert_not_NULL(im_config);
    uz_assert_not_NULL(state);
    uz_assert(sampling_time_s > 0.0f);

    if (state->current_control == NULL) {
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
            .upper_limit = INFINITY,
            .lower_limit = -INFINITY,
        };
        struct uz_CurrentControl_config const current_cfg = {
            .decoupling_select = im_rotor_flux_decoupling,
            .config_id = pi_cfg,
            .config_iq = pi_cfg,
            .config_IM = *im_config,
            .Kp_adjustment_flag = false,
            .max_modulation_index = 1.0f / sqrtf(3.0f),
        };
        state->current_control = uz_CurrentControl_init(current_cfg);

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
    if (state->current_control != NULL) {
        uz_CurrentControl_reset(state->current_control);
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
                          float omega_s_rad_s,
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
    uz_assert_not_NULL(state->current_control);
    uz_assert_not_NULL(state->pi_speed);
    uz_assert_not_NULL(state->res_id_6th);
    uz_assert_not_NULL(state->res_iq_6th);

    output->id_cmd_A = input->id_ref_A;
    if (input->use_speed_control) {
        output->iq_cmd_A = uz_PI_Controller_sample(state->pi_speed, input->speed_ref_rpm, av->IM_mechanicalRotorSpeed_filtered, false);
    } else {
        output->iq_cmd_A = input->iq_ref_A;
        if (state->pi_speed != NULL) {
            uz_PI_Controller_reset(state->pi_speed);
        }
    }

    float ud_res = 0.0f;
    float uq_res = 0.0f;

    if (input->use_resonant_6th) {
        // Prefer the det PLL omega_s (smooth). If the deterministic observer is
        // disabled, the caller may fall back to the selected observer omega_s.
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

    uz_CurrentControl_input_t const current_input = {
        .i_reference_Ampere = {.d = input->id_ref_A, .q = output->iq_cmd_A, .zero = 0.0f},
        .i_actual_Ampere = {.d = av->IM_I_d, .q = av->IM_I_q, .zero = 0.0f},
        .V_dc_volts = av->IM_vdc,
        .omega_dq_rad_per_sec = omega_s_rad_s,
        .psi_r_Vs = psi_r_mag,
        .v_additional_Volts = {.d = ud_res, .q = uq_res, .zero = 0.0f},
        .omega_limitation_rad_per_sec = av->IM_mechanicalRotorSpeed_filtered
                                         * (2.0f * UZ_PIf / 60.0f)
                                         * im_config->polePairs,
    };
    uz_CurrentControl_output_t const current_output =
        uz_CurrentControl_sample_general(state->current_control, current_input);

    output->ud_pi    = current_output.v_pi_Volts.d;
    output->uq_pi    = current_output.v_pi_Volts.q;
    output->ud_decoup = current_output.v_decoupling_Volts.d;
    output->uq_decoup = current_output.v_decoupling_Volts.q;
    output->ud_res   = ud_res;
    output->uq_res   = uq_res;

    uz_3ph_dq_t const v_dq_ref = current_output.v_output_Volts;

    av->IM_vd = v_dq_ref.d;
    av->IM_vq = v_dq_ref.q;

    struct uz_DutyCycle_t const duty = uz_Space_Vector_Modulation(v_dq_ref, av->IM_vdc, theta_flux_rad);

    rasv->halfBridge1DutyCycle = duty.DutyCycle_A;
    rasv->halfBridge2DutyCycle = duty.DutyCycle_B;
    rasv->halfBridge3DutyCycle = duty.DutyCycle_C;
}
