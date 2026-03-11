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

#ifndef IM_ROTOR_FLUX_OBSERVER_H_
#define IM_ROTOR_FLUX_OBSERVER_H_

#include "../globalData.h"
#include "../uz/uz_IM_config/uz_IM_config.h"
#include "../uz/uz_pos_to_speed_pll/uz_pos_to_speed_pll.h"

typedef struct {
    float psi_r_alpha;
    float psi_r_beta;
    float theta_flux_rad;
    float psi_r_mag;
    uz_pos_to_speed_pll_t *stator_frequency_pll;
} im_rotor_flux_observer_state_t;

typedef struct {
    float omega_el_rad_s;
    float theta_flux_rad;
    float theta_elec_rad;
    float psi_r_mag;
    float stator_current_fundamental_frequency_Hz;
    float i_d;
    float i_q;
} im_rotor_flux_observer_output_t;

void im_rotor_flux_observer_init(const uz_IM_t *im_config,
                                  float sampling_time_s,
                                  im_rotor_flux_observer_state_t *state);
void im_rotor_flux_observer_step(const actualValues *av,
                                  const uz_IM_t *im_config,
                                  im_rotor_flux_observer_state_t *state,
                                  im_rotor_flux_observer_output_t *output);

#endif /* IM_ROTOR_FLUX_OBSERVER_H_ */
