/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Josef Knoblach
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

#include "uz_VSD_6ph_FD.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>




uz_6phFD_indices uz_vsd_opf_6ph_faultdetection(uz_6ph_alphabeta_t vsdcurrents, float upperlimit, float lowerlimit, float threshold, uint32_t mov_average_filter_length, float sample_frequency_Hz, float percent_of_el_period, float omega_el_rad_per_sec, uz_movingAverageFilter_t* movingAverageFilter_R1, uz_movingAverageFilter_t* movingAverageFilter_R2, uz_movingAverageFilter_t* movingAverageFilter_R3, uz_movingAverageFilter_t* movingAverageFilter_R4, uz_movingAverageFilter_t* movingAverageFilter_R5, uz_movingAverageFilter_t* movingAverageFilter_R6 ){

	uz_6phFD_indices indices = {0};

	// calculate fault indices
	indices = uz_vsd_opf_6ph_fault_indices_calculation(vsdcurrents);

	// filter with hysteresis filter
	indices = uz_vsd_fd_hysteresis_filter(indices, lowerlimit, upperlimit);

	// set filterlength of moving average filter according to current omega_el
	uint32_t new_filterLength = 1;
	if (omega_el_rad_per_sec != 0){
		new_filterLength = (uint32_t)(percent_of_el_period*sample_frequency_Hz*2.0f*(float)M_PI/fabsf(omega_el_rad_per_sec));
	}

	if(new_filterLength > mov_average_filter_length){
		new_filterLength = mov_average_filter_length;
	}else if(new_filterLength < 1){
		new_filterLength = 1;
	}


	uz_movingAverageFilter_set_filterLength(movingAverageFilter_R1, new_filterLength);
	uz_movingAverageFilter_set_filterLength(movingAverageFilter_R2, new_filterLength);
	uz_movingAverageFilter_set_filterLength(movingAverageFilter_R3, new_filterLength);
	uz_movingAverageFilter_set_filterLength(movingAverageFilter_R4, new_filterLength);
	uz_movingAverageFilter_set_filterLength(movingAverageFilter_R5, new_filterLength);
	uz_movingAverageFilter_set_filterLength(movingAverageFilter_R6, new_filterLength);

	// moving average filter
	indices.R1 = uz_movingAverageFilter_sample_variable_length(movingAverageFilter_R1, indices.R1);
	indices.R2 = uz_movingAverageFilter_sample_variable_length(movingAverageFilter_R2, indices.R2);
	indices.R3 = uz_movingAverageFilter_sample_variable_length(movingAverageFilter_R3, indices.R3);
	indices.R4 = uz_movingAverageFilter_sample_variable_length(movingAverageFilter_R4, indices.R4);
	indices.R5 = uz_movingAverageFilter_sample_variable_length(movingAverageFilter_R5, indices.R5);
	indices.R6 = uz_movingAverageFilter_sample_variable_length(movingAverageFilter_R6, indices.R6);


	// evaluation of fault indices
	indices = uz_vsd_fd_evaluation(indices, threshold);

	return indices;
}


/**
 * @brief helper function for dividing with protection against divide by zero, returns zero if denominator is zero
 * 
 * @param num numinator
 * @param denom denominator
 * @return float num/denom 
 */
static float uz_divide(float num, float denom){
	float result = 0.0f;
	if(denom != 0.0f){
		result = num/denom;
	}
	return result;
}

uz_6phFD_indices uz_vsd_opf_6ph_fault_indices_calculation(uz_6ph_alphabeta_t input){

	uz_6phFD_indices output = {0};

	//fault index for phase 1
	output.R1 = uz_divide(-input.x, input.alpha + input.z1);

	//fault index for phase 2
	output.R2 = uz_divide(input.x + sqrtf(3.0f)*input.y - 2.0f*input.z1, -input.alpha + sqrtf(3.0f)* input.beta);

	//fault index for phase 3
	output.R3 = uz_divide(input.x - sqrtf(3.0f)*input.y -2.0f*input.z1, -input.alpha - sqrtf(3.0f)*input.beta);

	//fault index for phase 4
	output.R4 = uz_divide(input.x -1/sqrtf(3.0f)*input.y - 2.0f/sqrtf(3.0f) * input.z2, input.alpha + 1.0f/sqrtf(3.0f)*input.beta);

	//fault index for phase 5
	output.R5 = uz_divide(input.x  + 1/sqrtf(3.0f)*input.y + 2.0f/sqrtf(3.0f)*input.z2, input.alpha - 1/sqrtf(3.0f)*input.beta);

	//fault index for phase 6
	output.R6 = uz_divide(-input.y, (input.beta - input.z2));

	return output;
}



uz_6phFD_indices uz_vsd_fd_hysteresis_filter(uz_6phFD_indices input, float lowerlimit, float upperlimit){

	input.R1 = uz_signals_hysteresisband_filter(input.R1, upperlimit, lowerlimit);
	input.R2 = uz_signals_hysteresisband_filter(input.R2, upperlimit, lowerlimit);
	input.R3 = uz_signals_hysteresisband_filter(input.R3, upperlimit, lowerlimit);
	input.R4 = uz_signals_hysteresisband_filter(input.R4, upperlimit, lowerlimit);
	input.R5 = uz_signals_hysteresisband_filter(input.R5, upperlimit, lowerlimit);
	input.R6 = uz_signals_hysteresisband_filter(input.R6, upperlimit, lowerlimit);
	return input;
}


uz_6phFD_indices uz_vsd_fd_evaluation(uz_6phFD_indices input, float threshold){
	input.R1 = uz_signals_threshold_Evaluation(input.R1, threshold);
	input.R2 = uz_signals_threshold_Evaluation(input.R2, threshold);
	input.R3 = uz_signals_threshold_Evaluation(input.R3, threshold);
	input.R4 = uz_signals_threshold_Evaluation(input.R4, threshold);
	input.R5 = uz_signals_threshold_Evaluation(input.R5, threshold);
	input.R6 = uz_signals_threshold_Evaluation(input.R6, threshold);
	return input;
}





