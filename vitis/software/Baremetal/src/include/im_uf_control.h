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

#ifndef IM_UF_CONTROL_H_
#define IM_UF_CONTROL_H_

#include "../globalData.h"
#include "../uz/uz_Transformation/uz_Transformation.h"

typedef struct {
    float frequency_setpoint_Hz;
    float ratio_V_per_Hz;
    float boost_voltage_V;
    float max_frequency_Hz;
    float max_voltage_V;
    float frequency_ramp_Hz_per_s;
} im_uf_control_config_t;

typedef struct {
    float frequency_command_Hz;
    float electrical_phase_rad;
    float applied_voltage_magnitude_V; /* last commanded voltage in RMS L-L — read-only, for diagnostics */
} im_uf_control_state_t;

void im_uf_control_reset(im_uf_control_state_t *state);
uz_3ph_abc_t im_uf_control_step(const actualValues *av,
                                 referenceAndSetValues *rasv,
                                 const im_uf_control_config_t *config,
                                 im_uf_control_state_t *state);

#endif /* IM_UF_CONTROL_H_ */
