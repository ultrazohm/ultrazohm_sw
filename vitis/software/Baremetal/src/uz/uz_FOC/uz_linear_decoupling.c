/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel
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

#include "uz_linear_decoupling.h"
#include "../uz_HAL.h"

uz_dq_t uz_FOC_linear_decoupling(struct uz_PMSM_t config, uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec) {
    uz_assert(config.Ld_Henry > 0.0f);
	uz_assert(config.Lq_Henry > 0.0f);
	uz_assert(config.Psi_PM_Vs >= 0.0f);
	uz_dq_t u_dq_vor_Volts = {0};
	u_dq_vor_Volts.d = i_actual_Ampere.q * -1.0f * config.Lq_Henry * omega_el_rad_per_sec;
	u_dq_vor_Volts.q = ( (i_actual_Ampere.d* config.Ld_Henry) + config.Psi_PM_Vs) * omega_el_rad_per_sec;
	return (u_dq_vor_Volts);
}