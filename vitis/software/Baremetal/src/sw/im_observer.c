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

#include "../include/im_observer.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_math_constants.h"

im_observer_result_t im_observer_step(
    const actualValues              *av,
    const uz_IM_t                   *im_config,
    float                            u_a,
    float                            u_b,
    float                            u_c,
    bool                             kf_ready,
    bool                             use_kalman_filter,
    im_rotor_flux_observer_state_t  *det_state,
    const uz_IM_ss_t                *im_ss,
    im_kf_observer_state_t          *kf_state)
{
    uz_assert_not_NULL(av);
    uz_assert_not_NULL(im_config);
    uz_assert_not_NULL(det_state);
    uz_assert_not_NULL(im_ss);
    uz_assert_not_NULL(kf_state);

    im_observer_result_t result = {0};

    // Deterministic observer always runs — provides the smooth PLL-based stator
    // frequency used by the resonant controller.
    im_rotor_flux_observer_output_t det_output = {0};
    im_rotor_flux_observer_step(av, im_config, det_state, &det_output);
    result.det_psi_r_alpha  = det_state->psi_r_alpha;
    result.det_psi_r_beta   = det_state->psi_r_beta;
    result.det_omega_s_rad_s = 2.0f * UZ_PIf * det_output.stator_current_fundamental_frequency_Hz;

    if (!kf_ready) {
        result.output = det_output;
        return result;
    }

    // KF observer runs when the state-space matrices are valid and calibration is done.
    im_rotor_flux_observer_output_t kf_output = {0};
    im_kf_observer_step(av, im_ss, u_a, u_b, u_c, kf_state, &kf_output);
    result.kf_innov_alpha = kf_state->innov[0];
    result.kf_innov_beta  = kf_state->innov[1];
    result.kf_S_00        = kf_state->S_diag[0];
    result.kf_S_11        = kf_state->S_diag[1];
    result.kf_K_00        = kf_state->K_diag[0];
    result.kf_K_11        = kf_state->K_diag[1];

    result.output = use_kalman_filter ? kf_output : det_output;
    return result;
}
