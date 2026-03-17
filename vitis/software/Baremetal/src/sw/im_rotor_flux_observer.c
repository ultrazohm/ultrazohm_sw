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

#include "../include/im_rotor_flux_observer.h"
#include "../include/error_checks.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_math_constants.h"
#include <math.h>

void im_rotor_flux_observer_init(const uz_IM_t *im_config,
                                  float sampling_time_s,
                                  im_rotor_flux_observer_state_t *state)
{
    uz_assert_not_NULL(im_config);
    uz_assert_not_NULL(state);
    uz_assert(sampling_time_s > 0.0f);

    state->psi_r_alpha = 0.0f;
    state->psi_r_beta = 0.0f;
    state->theta_flux_rad = 0.0f;
    state->psi_r_mag = 0.0f;

    if (state->stator_frequency_pll == NULL) {
        struct uz_pos_to_speed_pll_config_t const pll_cfg = {
            .machine_polepairs = fmaxf(im_config->polePairs, 1.0e-3f),
            .kp_pll = 628.3185f,
            .ki_pll = 98696.0f,
            .sampling_time_in_seconds = fmaxf(sampling_time_s, 1.0e-6f),
        };
        state->stator_frequency_pll = uz_pos_to_speed_pll_init(pll_cfg);
    }
}

void im_rotor_flux_observer_step(const actualValues *av,
                                  const uz_IM_t *im_config,
                                  im_rotor_flux_observer_state_t *state,
                                  im_rotor_flux_observer_output_t *output)
{
    uz_assert_not_NULL(av);
    uz_assert_not_NULL(im_config);
    uz_assert_not_NULL(state);
    uz_assert_not_NULL(output);

    float const ts = av->isr_samplerate_s;
    float const lr = im_config->Lsigma_r_Henry + im_config->Lm_Henry;
    float const tau_r = lr / im_config->Rr_Ohm;
    float const one_over_tau_r = 1.0f / tau_r;
    float const lm_over_tau_r = im_config->Lm_Henry * one_over_tau_r;

    uz_3ph_abc_t const i_abc = {.a = av->IM_ia, .b = av->IM_ib, .c = av->IM_ic};
    uz_3ph_alphabeta_t const i_ab = uz_transformation_3ph_abc_to_alphabeta(i_abc);

    output->omega_el_rad_s = av->IM_mechanicalRotorSpeed_filtered * (2.0f * UZ_PIf / 60.0f) * im_config->polePairs;

    // Bilinear/Tustin discretization of:
    //   psi_dot = A(omega_el) * psi + (Lm/tau_r) * i_ab
    float const half_ts = 0.5f * ts;
    float const alpha = one_over_tau_r;
    float const omega_el = output->omega_el_rad_s;

    float const m00 = 1.0f + half_ts * alpha;
    float const m01 = half_ts * omega_el;
    float const m10 = -half_ts * omega_el;
    float const m11 = 1.0f + half_ts * alpha;

    float const n00 = 1.0f - half_ts * alpha;
    float const n01 = -half_ts * omega_el;
    float const n10 = half_ts * omega_el;
    float const n11 = 1.0f - half_ts * alpha;

    float const rhs_alpha = n00 * state->psi_r_alpha
                          + n01 * state->psi_r_beta
                          + ts * lm_over_tau_r * i_ab.alpha;
    float const rhs_beta = n10 * state->psi_r_alpha
                         + n11 * state->psi_r_beta
                         + ts * lm_over_tau_r * i_ab.beta;

    float const det_m = m00 * m11 - m01 * m10;
    if (fabsf(det_m) < 1.0e-12f) {
        state->psi_r_alpha = 0.0f;
        state->psi_r_beta = 0.0f;
        state->theta_flux_rad = 0.0f;
        state->psi_r_mag = 0.0f;
        error_checks_report(ERR_NAN_OBSERVER);
    } else {
        state->psi_r_alpha = (m11 * rhs_alpha - m01 * rhs_beta) / det_m;
        state->psi_r_beta = (-m10 * rhs_alpha + m00 * rhs_beta) / det_m;
    }

    state->theta_flux_rad = atan2f(state->psi_r_beta, state->psi_r_alpha);
    state->psi_r_mag = sqrtf(state->psi_r_alpha * state->psi_r_alpha + state->psi_r_beta * state->psi_r_beta);

    if (!isfinite(state->psi_r_alpha) || !isfinite(state->psi_r_beta) ||
        !isfinite(state->theta_flux_rad) || !isfinite(state->psi_r_mag)) {
        state->psi_r_alpha = 0.0f;
        state->psi_r_beta = 0.0f;
        state->theta_flux_rad = 0.0f;
        state->psi_r_mag = 0.0f;
        error_checks_report(ERR_NAN_OBSERVER);
    }

    uz_assert_not_NULL(state->stator_frequency_pll);

    output->stator_current_fundamental_frequency_Hz = 0.0f;
    float theta_flux_wrapped = state->theta_flux_rad;
    if (theta_flux_wrapped < 0.0f) {
        theta_flux_wrapped += 2.0f * UZ_PIf;
    }
    theta_flux_wrapped = fminf(fmaxf(theta_flux_wrapped, 0.0f), 2.0f * UZ_PIf);
    uz_pos_to_speed_pll_step(state->stator_frequency_pll, theta_flux_wrapped);
    float const omega_s_pll_rad_s = uz_pos_to_speed_pll_get_omega_mech_si(state->stator_frequency_pll);
    output->stator_current_fundamental_frequency_Hz = fabsf(omega_s_pll_rad_s) / (2.0f * UZ_PIf);
    if (!isfinite(output->stator_current_fundamental_frequency_Hz)) {
        output->stator_current_fundamental_frequency_Hz = 0.0f;
    }

    output->theta_flux_rad = state->theta_flux_rad;
    output->theta_elec_rad = state->theta_flux_rad;
    output->psi_r_mag = state->psi_r_mag;

    uz_3ph_dq_t const i_dq = uz_transformation_3ph_abc_to_dq(i_abc, state->theta_flux_rad);
    output->i_d = i_dq.d;
    output->i_q = i_dq.q;
}
