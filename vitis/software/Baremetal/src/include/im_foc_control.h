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

#ifndef IM_FOC_CONTROL_H_
#define IM_FOC_CONTROL_H_

#include "../globalData.h"
#include "../uz/uz_IM_config/uz_IM_config.h"
#include "../uz/uz_piController/uz_piController.h"
#include "../uz/uz_ResonantController/uz_resonant_controller.h"
#include <stdbool.h>

typedef struct {
    bool use_speed_control;
    bool use_resonant_6th;
    float id_ref_A;
    float iq_ref_A;
    float speed_ref_rpm;
    /** Measured d/q currents from raw abc → dq transform at theta_flux.
     *  Used by the resonant controller so it sees the full harmonic content
     *  even when the KF observer attenuates harmonics in av.I_d/I_q. */
    float id_meas_A;
    float iq_meas_A;
    /** Stator angular frequency [rad/s] for resonant controller frequency tracking.
     *  Prefer the deterministic observer PLL when available because it is
     *  smoother than the KF slip estimate. If the deterministic observer is
     *  disabled, the caller may fall back to the selected observer omega_s. */
    float omega_s_for_resonant_rad_s;
} im_foc_control_input_t;

typedef struct {
    float id_cmd_A;
    float iq_cmd_A;
    float ud_pi;      // d-axis PI output before decoupling (should approach Rs*id at steady state)
    float uq_pi;      // q-axis PI output before decoupling (should approach Rs*iq at steady state)
    float ud_decoup;  // d-axis feedforward: -omega_s * sigma_ls * iq
    float uq_decoup;  // q-axis feedforward: omega_s * sigma_ls * id + omega_s * (Lm/Lr) * psi_r
    float ud_res;     // d-axis resonant controller output (zero when resonant disabled)
    float uq_res;     // q-axis resonant controller output (zero when resonant disabled)
} im_foc_control_output_t;

typedef struct {
    uz_PI_Controller *pi_id;
    uz_PI_Controller *pi_iq;
    uz_PI_Controller *pi_speed;
    uz_resonantController_t *res_id_6th;
    uz_resonantController_t *res_iq_6th;
    bool resonant_enabled_last;
    float resonant_omega_filtered; // IIR-smoothed fundamental omega fed to resonant controller
} im_foc_control_state_t;

void im_foc_control_init(const uz_IM_t *im_config,
                          float sampling_time_s,
                          im_foc_control_state_t *state);
void im_foc_control_reset(im_foc_control_state_t *state);
void im_foc_control_step(actualValues *av,
                          referenceAndSetValues *rasv,
                          const uz_IM_t *im_config,
                          const im_foc_control_input_t *input,
                          float omega_el_rad_s,
                          float psi_r_mag,
                          float theta_flux_rad,
                          im_foc_control_state_t *state,
                          im_foc_control_output_t *output);

#endif /* IM_FOC_CONTROL_H_ */
