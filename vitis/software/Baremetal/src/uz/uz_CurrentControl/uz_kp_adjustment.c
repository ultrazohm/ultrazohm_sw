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

#include "uz_kp_adjustment.h"
#include "../uz_HAL.h"

uz_3ph_dq_t uz_CurrentControl_kp_adjustment(uz_3ph_dq_t i_actual_Ampere, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t flux_approx, uz_3ph_dq_t flux_ref, float sample_time, float BO_factor) {
	uz_3ph_dq_t kp_adjusted = {0};
	uz_3ph_dq_t divider = {0};
	divider.d = i_reference_Ampere.d - i_actual_Ampere.d;
	  if (divider.d == 0.0f) {
    	divider.d = 1.1920929E-7f;
  		}
	divider.q = i_reference_Ampere.q - i_actual_Ampere.q ;
	  if (divider.q == 0.0f) {
    	divider.q = 1.1920929E-7f;
  		}
	kp_adjusted.d = ((flux_ref.d - flux_approx.d)/divider.d) / (BO_factor * sample_time * 2.0f);
	kp_adjusted.q = ((flux_ref.q - flux_approx.q)/divider.q) / (BO_factor * sample_time * 2.0f);
	return (kp_adjusted);
}