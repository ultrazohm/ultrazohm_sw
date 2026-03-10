/******************************************************************************
* Copyright Contributors to the UltraZohm project.
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

#include "uz_IM_config.h"
#include "../uz_global_configuration.h"
#include "../../include/motor_config.h"
#include "../uz_HAL.h"
#include <math.h>

void uz_IM_config_assert(uz_IM_t config) {
    // Electrical parameters
    uz_assert(config.Rs_Ohm > 0.0f);
    uz_assert(config.Rr_Ohm > 0.0f);
    uz_assert(config.Lsigma_s_Henry > 0.0f);
    uz_assert(config.Lsigma_r_Henry > 0.0f);
    uz_assert(config.Lm_Henry > 0.0f);

    // Mechanical parameters
    uz_assert(config.polePairs > 0.0f);
    uz_assert(fmodf(config.polePairs, 1.0f) == 0);
    uz_assert(config.J_kg_m_squared > 0.0f);

    // Limits
    uz_assert(config.I_max_Ampere > 0.0f);
    uz_assert(config.Psi_rated_Vs > 0.0f);
}

float uz_IM_get_Ls(uz_IM_t config) {
    uz_assert(config.Lsigma_s_Henry > 0.0f);
    uz_assert(config.Lm_Henry > 0.0f);
    return (config.Lsigma_s_Henry + config.Lm_Henry);
}

float uz_IM_get_Lr(uz_IM_t config) {
    uz_assert(config.Lsigma_r_Henry > 0.0f);
    uz_assert(config.Lm_Henry > 0.0f);
    return (config.Lsigma_r_Henry + config.Lm_Henry);
}

float uz_IM_get_sigma(uz_IM_t config) {
    float Ls = uz_IM_get_Ls(config);
    float Lr = uz_IM_get_Lr(config);
    uz_assert(Ls > 0.0f);
    uz_assert(Lr > 0.0f);
    uz_assert(config.Lm_Henry > 0.0f);

    float sigma = 1.0f - (config.Lm_Henry * config.Lm_Henry) / (Ls * Lr);

    // Sigma should be between 0 and 1 for physically realizable machines
    // Typical values: 0.05 to 0.15
    uz_assert(sigma > 0.0f);
    uz_assert(sigma < 1.0f);

    return sigma;
}

float uz_IM_get_tau_r(uz_IM_t config) {
    uz_assert(config.Rr_Ohm > 0.0f);
    float Lr = uz_IM_get_Lr(config);
    uz_assert(Lr > 0.0f);

    float tau_r = Lr / config.Rr_Ohm;

    // Sanity check: rotor time constant should be positive and reasonable
    // Typical values: 0.01s (small) to 2.0s (large machines)
    uz_assert(tau_r > 0.0f);
    uz_assert(tau_r < 10.0f); // Extremely large machines might exceed this

    return tau_r;
}

float uz_IM_get_id_ref_for_psi_r(uz_IM_t config, float psi_r_Vs) {
    uz_IM_config_assert(config);
    uz_assert(psi_r_Vs > 0.0f);

    float const id_ref = psi_r_Vs / config.Lm_Henry;
    uz_assert(id_ref <= config.I_max_Ampere);

    return id_ref;
}

uz_IM_ss_t uz_IM_ss_compute(uz_IM_t config, float Ts) {
    uz_IM_config_assert(config);
    uz_assert(Ts > 0.0f);

    float const Ls      = uz_IM_get_Ls(config);
    float const Lr      = uz_IM_get_Lr(config);
    float const sigma   = uz_IM_get_sigma(config);
    float const sigma_Ls = sigma * Ls;
    float const Lm      = config.Lm_Henry;
    float const Rs      = config.Rs_Ohm;
    float const Rr      = config.Rr_Ohm;

    // Continuous-time F matrix coefficients (SI units)
    // F = [[a, 0, b, c*wr], [0, a, -c*wr, b], [d, 0, -e, -wr], [0, d, wr, -e]]
    float const a = -(Rs / sigma_Ls + Lm * Lm * Rr / (sigma_Ls * Lr * Lr));
    float const b = Lm * Rr / (sigma_Ls * Lr * Lr);
    float const c = Lm / (sigma_Ls * Lr);
    float const d = Lm * Rr / Lr;
    float const e = Rr / Lr;

    uz_IM_ss_t ss = {0};

    // A_base: Forward Euler A = I + F*Ts, speed-dependent elements left zero
    ss.A_base[0][0] = 1.0f + a * Ts;
    ss.A_base[1][1] = 1.0f + a * Ts;
    ss.A_base[0][2] = b * Ts;
    ss.A_base[1][3] = b * Ts;
    ss.A_base[2][0] = d * Ts;
    ss.A_base[3][1] = d * Ts;
    ss.A_base[2][2] = 1.0f - e * Ts;
    ss.A_base[3][3] = 1.0f - e * Ts;
    // A_base[0][3], A_base[1][2], A_base[2][3], A_base[3][2] remain 0

    // B = Ts/sigma_Ls * P_ab (amplitude-invariant Clarke, rows 2-3 = 0)
    // P_ab = (2/3)*[[1, -1/2, -1/2], [0, sqrt(3)/2, -sqrt(3)/2]]
    float const k = Ts / sigma_Ls;
    ss.B[0][0] =  k * (2.0f / 3.0f);
    ss.B[0][1] = -k * (1.0f / 3.0f);
    ss.B[0][2] = -k * (1.0f / 3.0f);
    ss.B[1][0] =  0.0f;
    ss.B[1][1] =  k / sqrtf(3.0f);
    ss.B[1][2] = -k / sqrtf(3.0f);
    // ss.B[2][*] and ss.B[3][*] remain 0

    // Default Kalman tuning — defined in motor_config.h alongside the motor parameters.
    ss.Q_diag[0] = MOTOR_KF_Q_i;
    ss.Q_diag[1] = MOTOR_KF_Q_i;
    ss.Q_diag[2] = MOTOR_KF_Q_psi;
    ss.Q_diag[3] = MOTOR_KF_Q_psi;

    ss.R_diag[0] = MOTOR_KF_R_i;
    ss.R_diag[1] = MOTOR_KF_R_i;

    // Speed-coupling coefficients for per-step A update
    ss.x_m_D_Ts       = c * Ts;                   // Lm*Ts/(sigmaLs*Lr)
    ss.Ts             = Ts;
    ss.x_m_tau_r_inv  = Lm * Rr / Lr;              // Lm/tau_r = Lm*Rr/Lr, for slip estimate
    ss.polePairs      = config.polePairs;

    return ss;
}
