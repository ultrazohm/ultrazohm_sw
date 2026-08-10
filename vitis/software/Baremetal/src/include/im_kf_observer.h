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

#ifndef IM_KF_OBSERVER_H
#define IM_KF_OBSERVER_H

#pragma once

#include "../globalData.h"
#include "../uz/uz_IM_config/uz_IM_config.h"
#include "im_rotor_flux_observer.h"

/**
 * @brief Dynamic state of the Kalman Filter observer.
 *
 * Contains the time-varying KF quantities together with the owned PLL instance
 * used to derive stator frequency from the KF flux angle.
 * All precomputed motor-model matrices live in uz_IM_ss_t.
 *
 * Initialize P to identity and x to zeros before first use:
 *   im_kf_observer_state_t s = { .P = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} };
 */
typedef struct {
    float x[4];    /**< State estimate: [i_alpha, i_beta, Psi_r_alpha, Psi_r_beta] */
    float P[4][4]; /**< Error covariance matrix (4x4) */
    /* Diagnostic outputs — updated each step, readable after im_kf_observer_step() */
    float innov[2];   /**< Innovation y_e = meas - pred for [i_alpha, i_beta] */
    float S_diag[2];  /**< Innovation covariance diagonal: S[0][0], S[1][1] */
    float K_diag[2];  /**< Kalman gain diagonal: K[0][0], K[1][1] */
    uz_pos_to_speed_pll_t *stator_frequency_pll; /**< PLL driven by KF theta_flux_rad */
} im_kf_observer_state_t;

void im_kf_observer_init(const uz_IM_t *im_config,
                           float sampling_time_s,
                           im_kf_observer_state_t *state);

/**
 * @brief Execute one Kalman Filter observer step.
 *
 * Implements a discrete-time linear KF exploiting H = [I2 | 0] to avoid
 * full-matrix inversions. Covariance update uses (I-KH)*P_pre matching
 * the MATLAB reference KF_obs_FPGA.m.
 *
 * Populates output->i_d, output->i_q, output->theta_elec_rad together with
 * flux magnitude/angle and PLL-based stator frequency estimates.
 *
 * @param av        Measured values (reads I_U/V/W, mechanicalRotorSpeed_filtered)
 * @param ss        Precomputed discretized motor model (from uz_IM_ss_compute())
 * @param u_a       Phase-a voltage applied in the PREVIOUS ISR step [V]
 * @param u_b       Phase-b voltage applied in the PREVIOUS ISR step [V]
 * @param u_c       Phase-c voltage applied in the PREVIOUS ISR step [V]
 *                  Compute as: (halfBridgeXDutyCycle - 0.5f) * U_DC
 *                  Read BEFORE the control step overwrites duty cycles.
 * @param state     KF dynamic state (updated in-place)
 * @param output    Observer outputs: omega_el, theta_flux, psi_r_mag, f_stator
 */
void im_kf_observer_step(const actualValues *av,
                           const uz_IM_ss_t *ss,
                           float u_a, float u_b, float u_c,
                           im_kf_observer_state_t *state,
                           im_rotor_flux_observer_output_t *output);

/**
 * @brief Run the PLL to update stator_current_fundamental_frequency_Hz.
 *
 * Must be called AFTER im_kf_observer_step() has returned so the large Kalman
 * matrix locals are no longer on the ISR stack when sinf/cosf execute.
 *
 * @param state   KF state (owns the PLL)
 * @param output  Observer output populated by im_kf_observer_step() (updated in-place)
 */
void im_kf_observer_pll_step(im_kf_observer_state_t *state,
                               im_rotor_flux_observer_output_t *output);

#endif // IM_KF_OBSERVER_H
