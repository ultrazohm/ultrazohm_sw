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
#include "../uz_HAL.h"

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
