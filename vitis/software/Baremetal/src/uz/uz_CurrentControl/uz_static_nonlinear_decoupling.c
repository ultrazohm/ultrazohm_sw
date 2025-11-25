/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 
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

#include "uz_static_nonlinear_decoupling.h"
#include "../uz_HAL.h"

uz_3ph_dq_t uz_CurrentControl_static_nonlinear_decoupling(uz_3ph_dq_t flux_approx, float omega_el_rad_per_sec) {
	uz_3ph_dq_t v_dq_vor_Volts = {0};
	v_dq_vor_Volts.d = -1.0f * flux_approx.q * omega_el_rad_per_sec;
	v_dq_vor_Volts.q = flux_approx.d * omega_el_rad_per_sec;
	return (v_dq_vor_Volts);
}