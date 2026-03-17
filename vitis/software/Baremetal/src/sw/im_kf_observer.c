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

#include "../include/im_kf_observer.h"
#include "../include/error_checks.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_math_constants.h"
#include <math.h>

void im_kf_observer_init(const uz_IM_t *im_config,
                           float sampling_time_s,
                           im_kf_observer_state_t *state)
{
    uz_assert_not_NULL(im_config);
    uz_assert_not_NULL(state);
    uz_assert(sampling_time_s > 0.0f);

    state->innov[0] = 0.0f;
    state->innov[1] = 0.0f;
    state->S_diag[0] = 0.0f;
    state->S_diag[1] = 0.0f;
    state->K_diag[0] = 0.0f;
    state->K_diag[1] = 0.0f;
    for (int i = 0; i < 4; i++) {
        state->x[i] = 0.0f;
        for (int j = 0; j < 4; j++) {
            state->P[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    if (state->stator_frequency_pll == NULL) {
        struct uz_pos_to_speed_pll_config_t const pll_cfg = {
            .machine_polepairs = fmaxf(im_config->polePairs, 1.0e-3f),
            .kp_pll = 628.3185f,
            .ki_pll = 98696.0f,
            .sampling_time_in_seconds = fmaxf(sampling_time_s, 1.0e-6f),
        };
        state->stator_frequency_pll = uz_pos_to_speed_pll_init(pll_cfg);
    } else {
        uz_pos_to_speed_pll_reset(state->stator_frequency_pll);
    }
}

void im_kf_observer_step(const actualValues *av,
                           const uz_IM_ss_t *ss,
                           float u_a, float u_b, float u_c,
                           im_kf_observer_state_t *state,
                           im_rotor_flux_observer_output_t *output)
{
    uz_assert_not_NULL(av);
    uz_assert_not_NULL(ss);
    uz_assert_not_NULL(state);
    uz_assert_not_NULL(output);
    uz_assert_not_NULL(state->stator_frequency_pll);

    // -------------------------------------------------------------------------
    // 1. Electrical angular velocity from encoder
    // -------------------------------------------------------------------------
    float const omega_r_el = av->IM_mechanicalRotorSpeed_filtered
                           * (2.0f * UZ_PIf / 60.0f)
                           * ss->polePairs;
    output->omega_r_el_rad_s = omega_r_el;

    // -------------------------------------------------------------------------
    // 2. Build A: copy speed-independent skeleton, fill 4 speed-dependent terms
    // -------------------------------------------------------------------------
    float A[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = ss->A_base[i][j];
        }
    }
    float const wr_Ts      = omega_r_el * ss->Ts;
    float const wr_Ts_xmD  = omega_r_el * ss->x_m_D_Ts;
    A[0][3] =  wr_Ts_xmD;
    A[1][2] = -wr_Ts_xmD;
    A[2][3] = -wr_Ts;
    A[3][2] =  wr_Ts;

    // -------------------------------------------------------------------------
    // 3. Prediction: x_pre = A*x + B*u_abc
    // -------------------------------------------------------------------------
    float const u_abc[3] = {u_a, u_b, u_c};
    float x_pre[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x_pre[i] += A[i][j] * state->x[j];
        }
        for (int j = 0; j < 3; j++) {
            x_pre[i] += ss->B[i][j] * u_abc[j];
        }
    }

    // -------------------------------------------------------------------------
    // 4. Predict covariance: P_pre = A*P*A' + diag(Q_diag)
    //    Computed as temp = A*P, then P_pre = temp*A'
    // -------------------------------------------------------------------------
    float temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += A[i][k] * state->P[k][j];
            }
            temp[i][j] = sum;
        }
    }
    float P_pre[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += temp[i][k] * A[j][k]; // A[j][k] = A'[k][j]
            }
            P_pre[i][j] = sum + (i == j ? ss->Q_diag[i] : 0.0f);
        }
    }

    // -------------------------------------------------------------------------
    // 5. Measurement: Clarke transform of measured currents
    // -------------------------------------------------------------------------
    uz_3ph_abc_t const i_abc = {.a = av->IM_ia, .b = av->IM_ib, .c = av->IM_ic};
    uz_3ph_alphabeta_t const i_ab = uz_transformation_3ph_abc_to_alphabeta(i_abc);

    // -------------------------------------------------------------------------
    // 6. Innovation: y_e = y - H*x_pre  (H=[I2|0] -> just first 2 components)
    // -------------------------------------------------------------------------
    float const y_e[2] = {i_ab.alpha - x_pre[0], i_ab.beta - x_pre[1]};

    // -------------------------------------------------------------------------
    // 7. Innovation covariance S (2x2): S = P_pre[0:2,0:2] + diag(R_diag)
    // -------------------------------------------------------------------------
    float const S00 = P_pre[0][0] + ss->R_diag[0];
    float const S01 = P_pre[0][1];
    float const S10 = P_pre[1][0];
    float const S11 = P_pre[1][1] + ss->R_diag[1];

    // -------------------------------------------------------------------------
    // 8. Analytic 2x2 inverse of S
    // -------------------------------------------------------------------------
    float const det_S = S00 * S11 - S01 * S10;
    // Guard against near-singular S (should not occur with well-tuned R, but
    // possible during startup or with extreme noise).
    if (fabsf(det_S) < 1e-10f) {
        error_checks_report(ERR_NAN_OBSERVER);
        output->theta_flux_rad = 0.0f;
        output->theta_elec_rad = 0.0f;
        output->psi_r_mag      = 0.0f;
        output->stator_current_fundamental_frequency_Hz = 0.0f;
        output->i_d = 0.0f;
        output->i_q = 0.0f;
        return;
    }
    float const det_S_inv = 1.0f / det_S;
    float const Si00 =  S11 * det_S_inv;
    float const Si01 = -S01 * det_S_inv;
    float const Si10 = -S10 * det_S_inv;
    float const Si11 =  S00 * det_S_inv;

    // -------------------------------------------------------------------------
    // 9. Kalman gain K (4x2): K = P_pre[:,0:2] * inv(S)
    // -------------------------------------------------------------------------
    float K[4][2];
    for (int i = 0; i < 4; i++) {
        K[i][0] = P_pre[i][0] * Si00 + P_pre[i][1] * Si10;
        K[i][1] = P_pre[i][0] * Si01 + P_pre[i][1] * Si11;
    }

    // Diagnostic outputs (available to caller via state struct)
    state->innov[0]  = y_e[0];
    state->innov[1]  = y_e[1];
    state->S_diag[0] = S00;
    state->S_diag[1] = S11;
    state->K_diag[0] = K[0][0];
    state->K_diag[1] = K[1][1];

    // -------------------------------------------------------------------------
    // 10. State update: x_k = x_pre + K*y_e
    // -------------------------------------------------------------------------
    float x_k[4];
    for (int i = 0; i < 4; i++) {
        x_k[i] = x_pre[i] + K[i][0] * y_e[0] + K[i][1] * y_e[1];
    }

    // -------------------------------------------------------------------------
    // 11. Covariance update: P_k = (I - KH)*P_pre
    //     Exploits H=[I2|0]: P_k[i][j] = P_pre[i][j] - K[i][0]*P_pre[0][j] - K[i][1]*P_pre[1][j]
    // -------------------------------------------------------------------------
    float P_k[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            P_k[i][j] = P_pre[i][j]
                        - K[i][0] * P_pre[0][j]
                        - K[i][1] * P_pre[1][j];
        }
    }

    // -------------------------------------------------------------------------
    // 12. NaN guard: reset state and covariance if any estimate is invalid
    // -------------------------------------------------------------------------
    bool nan_detected = false;
    for (int i = 0; i < 4; i++) {
        if (!isfinite(x_k[i]) || !isfinite(P_k[i][i])) {
            nan_detected = true;
            break;
        }
    }
    if (nan_detected) {
        for (int i = 0; i < 4; i++) {
            state->x[i] = 0.0f;
            for (int j = 0; j < 4; j++) {
                state->P[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
        error_checks_report(ERR_NAN_OBSERVER);
        // Fill outputs with safe defaults and return
        output->theta_flux_rad = 0.0f;
        output->theta_elec_rad = 0.0f;
        output->psi_r_mag = 0.0f;
        output->stator_current_fundamental_frequency_Hz = 0.0f;
        output->i_d = 0.0f;
        output->i_q = 0.0f;
        return;
    }

    // -------------------------------------------------------------------------
    // 13. Commit updated state and covariance
    // -------------------------------------------------------------------------
    for (int i = 0; i < 4; i++) {
        state->x[i] = x_k[i];
        for (int j = 0; j < 4; j++) {
            state->P[i][j] = P_k[i][j];
        }
    }

    // -------------------------------------------------------------------------
    // 14. Post-processing: flux angle, i_d/i_q, stator frequency
    // -------------------------------------------------------------------------
    float const psi_r_mag = sqrtf(x_k[2] * x_k[2] + x_k[3] * x_k[3]);
    float const theta_flux = atan2f(x_k[3], x_k[2]);

    // NOTE: PLL step (sinf/cosf) is intentionally NOT called here.
    // im_kf_observer_step has ~312 bytes of Kalman matrix locals on the stack;
    // calling sinf/cosf from inside would overflow the ISR stack.
    // Call im_kf_observer_pll_step() from the caller after this function returns.
    output->stator_current_fundamental_frequency_Hz = 0.0f;

    // Rotate corrected current estimate into d-q frame
    float i_d = 0.0f;
    float i_q = 0.0f;
    if (psi_r_mag > 1e-6f) {
        float const psi_r_mag_inv = 1.0f / psi_r_mag;
        float const cosphi = x_k[2] * psi_r_mag_inv;
        float const sinphi = x_k[3] * psi_r_mag_inv;
        i_d =  x_k[0] * cosphi + x_k[1] * sinphi;
        i_q = -x_k[0] * sinphi + x_k[1] * cosphi;
    }

    output->theta_flux_rad = theta_flux;
    output->theta_elec_rad = theta_flux; /* KF has no separate rotor-position estimate; both fields carry the flux angle */
    output->psi_r_mag      = psi_r_mag;
    output->i_d = i_d;
    output->i_q = i_q;
}

void im_kf_observer_pll_step(im_kf_observer_state_t *state,
                               im_rotor_flux_observer_output_t *output)
{
    uz_assert_not_NULL(state);
    uz_assert_not_NULL(output);
    uz_assert_not_NULL(state->stator_frequency_pll);

    float theta_flux_wrapped = output->theta_flux_rad;
    if (theta_flux_wrapped < 0.0f) {
        theta_flux_wrapped += 2.0f * UZ_PIf;
    }
    theta_flux_wrapped = fminf(fmaxf(theta_flux_wrapped, 0.0f), 2.0f * UZ_PIf);
    uz_pos_to_speed_pll_step(state->stator_frequency_pll, theta_flux_wrapped);
    float const omega_s_pll_rad_s = uz_pos_to_speed_pll_get_omega_mech_si(state->stator_frequency_pll);
    output->stator_current_fundamental_frequency_Hz = fabsf(omega_s_pll_rad_s) / (2.0f * UZ_PIf);
}
