/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Dennis Hufnagel
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

#include "uz_space_vector_modulation.h"
#include "../uz_HAL.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>

#define ONE_DIVIDED_BY_SQRT_THREE  (1.0f / sqrtf(3.0f))
#define TWO_DIVIDED_BY_SQRT_THREE  (2.0f / sqrtf(3.0f))
#define TWO_DIVIDED_BY_THREE (2.0f/3.0f) 

struct uz_DutyCycle_t  uz_Space_Vector_Modulation(uz_3ph_dq_t v_ref_Volts, float V_DC_Volts, float theta_el_rad) {
	struct uz_DutyCycle_t output = {0};
	uz_3ph_alphabeta_t reference = uz_transformation_3ph_dq_to_alphabeta(v_ref_Volts, theta_el_rad);
	float V_DC_scaling = 1.0f / (V_DC_Volts * TWO_DIVIDED_BY_THREE);
	float abs_alpha = fabsf(reference.alpha);
	float abs_beta = fabsf(reference.beta);
	float a = (abs_alpha + (ONE_DIVIDED_BY_SQRT_THREE * abs_beta)) * V_DC_scaling;
	float b = (abs_alpha - (ONE_DIVIDED_BY_SQRT_THREE * abs_beta)) * V_DC_scaling;
	float c = (TWO_DIVIDED_BY_SQRT_THREE * abs_beta) * V_DC_scaling;
	uint32_t quadrant = 0U;
	uint32_t sector = 0U;

	//Determine the sector&quadrant of the space vector
	if(reference.beta < 0.0f) {
		if(reference.alpha < 0.0f) {
			quadrant = 3U;
			if(b < 0.0f) {
				sector = 5U;
			} else {
				sector = 4U;
			}
		} else {
			quadrant = 4U;
			if(b < 0.0f) {
				sector = 5U;
			} else {
				sector = 6U;
			}
		}
	} else {
		if(reference.alpha < 0.0f) {
			quadrant = 2U;
			if(b < 0.0f) {
				sector = 2U;
			} else {
            	sector = 3U;
			}
		} else {
			quadrant = 1U;
			if(b < 0.0f) {
				sector = 2U;
			} else {
				sector = 1U;
			}
		}
	}

	//Calculate output DutyCycle
	switch(sector) {

    	case 1U:
    		output.DutyCycle_A = (1.0f + b + c);
    		output.DutyCycle_B = (1.0f - b + c);
    		output.DutyCycle_C = (1.0f - b - c);
        break;
        
        case 2U:
            if(quadrant == 1U) {
                output.DutyCycle_A = (1.0f + a + b);
                output.DutyCycle_B = (1.0f + a - b);
                output.DutyCycle_C = (1.0f - a + b);
            } else {
                output.DutyCycle_A = (1.0f - a - b);
                output.DutyCycle_B = (1.0f + a - b);
                output.DutyCycle_C = (1.0f - a + b);
            }
        break;

        case 3U:
            output.DutyCycle_A = (1.0f - b - c);
            output.DutyCycle_B = (1.0f + b + c);
            output.DutyCycle_C = (1.0f + b - c);
        break;

        case 4U:
            output.DutyCycle_A = (1.0f - b - c);
            output.DutyCycle_B = (1.0f + b - c);
            output.DutyCycle_C = (1.0f + b + c);
        break;

        case 5U:
            if(quadrant == 3U) {
                output.DutyCycle_A = (1.0f - a - b);
                output.DutyCycle_B = (1.0f - a + b);
                output.DutyCycle_C = (1.0f + a - b);
            } else {
                output.DutyCycle_A = (1.0f + b + a);
                output.DutyCycle_B = (1.0f + b - a);
                output.DutyCycle_C = (1.0f - b + a);
            }
        break;

        case 6U:
            output.DutyCycle_A = (1.0f + b + c);
            output.DutyCycle_B = (1.0f - b - c);
            output.DutyCycle_C = (1.0f - b + c);
        break;

        default:
            uz_assert(0);
        break;
    }

    output.DutyCycle_A *= 0.5f;
    output.DutyCycle_B *= 0.5f;
    output.DutyCycle_C *= 0.5f;

    output.DutyCycle_A = uz_signals_saturation(output.DutyCycle_A, 1.0f, 0.0f);
    output.DutyCycle_B = uz_signals_saturation(output.DutyCycle_B, 1.0f, 0.0f);
    output.DutyCycle_C = uz_signals_saturation(output.DutyCycle_C, 1.0f, 0.0f);

    return (output);
}

struct uz_DutyCycle_t uz_FOC_generate_DutyCycles(uz_3ph_abc_t input, float V_dc_volts){
	//Uses continuous sinusoidal PWM (SPWM)
	struct uz_DutyCycle_t output = {0};
	output.DutyCycle_A = ( (input.a / (0.5f * V_dc_volts) ) +1.0f) * 0.5f;
	output.DutyCycle_B = ( (input.b / (0.5f * V_dc_volts) ) +1.0f) * 0.5f;
	output.DutyCycle_C = ( (input.c / (0.5f * V_dc_volts) ) +1.0f) * 0.5f;
	output.DutyCycle_A = uz_signals_saturation(output.DutyCycle_A, 1.0f, 0.0f);
	output.DutyCycle_B = uz_signals_saturation(output.DutyCycle_B, 1.0f, 0.0f);
	output.DutyCycle_C = uz_signals_saturation(output.DutyCycle_C, 1.0f, 0.0f);
	return(output);
}


struct uz_DutyCycle_2x3ph_t uz_FOC_generate_DutyCycles_6ph(uz_6ph_abc_t input, float V_dc_volts){
	struct uz_DutyCycle_2x3ph_t output = {0};
	uz_3ph_abc_t abc_system1 = {
		.a = input.a1,
		.b = input.b1,
		.c = input.c1};
	uz_3ph_abc_t abc_system2 = {
		.a = input.a2,
		.b = input.b2,
		.c = input.c2};
	output.system1 = uz_FOC_generate_DutyCycles(abc_system1, V_dc_volts);
	output.system2 = uz_FOC_generate_DutyCycles(abc_system2, V_dc_volts);
	return output;
}
