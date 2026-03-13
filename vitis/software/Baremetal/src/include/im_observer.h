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

#ifndef IM_OBSERVER_H_
#define IM_OBSERVER_H_

#include "../globalData.h"
#include "../uz/uz_IM_config/uz_IM_config.h"
#include "im_rotor_flux_observer.h"
#include "im_kf_observer.h"
#include <stdbool.h>

/**
 * @brief Combined output of one observer step.
 *
 * output  — the merged result selected by use_kalman_filter.
 *           Always valid; falls back to det observer if kf_ready is false.
 *
 * det_*   — diagnostics from the deterministic observer (always updated).
 *           det_omega_s_rad_s is used as the frequency reference for the
 *           resonant controller (smoother than the KF slip estimate).
 *
 * kf_*    — KF diagnostics (zero-initialized when kf_ready is false).
 */
typedef struct {
    im_rotor_flux_observer_output_t output;
    float det_psi_r_alpha;
    float det_psi_r_beta;
    float det_omega_s_rad_s;
    float kf_innov_alpha;
    float kf_innov_beta;
    float kf_S_00;
    float kf_S_11;
    float kf_K_00;
    float kf_K_11;
    float electric_torque_estimate_Nm;
} im_observer_result_t;

/**
 * @brief Run deterministic + KF observer for one ISR step and return the selected result.
 *
 * The deterministic observer always runs. The KF observer runs only when
 * kf_ready is true. If use_kalman_filter is false, the deterministic output
 * is returned even when the KF has run.
 *
 * @param av                 Measured values (currents, rotor speed)
 * @param im_config          Induction machine parameters
 * @param u_a/u_b/u_c        Phase voltages applied in the PREVIOUS ISR step [V]
 * @param kf_ready           True when im_ss is valid and calibration is done
 * @param use_kalman_filter  True to return KF result; false to return det result
 * @param det_state          Deterministic observer state (updated in-place)
 * @param im_ss              Precomputed discretized state-space matrices
 * @param kf_state           KF observer state (updated in-place when kf_ready)
 */
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
    im_kf_observer_state_t          *kf_state);

#endif /* IM_OBSERVER_H_ */
