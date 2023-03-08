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

/**
 * @brief helper function for hysteresis filter
 * 
 * @param input value to be filtered
 * @param lowerlimit lower limit of hysteresis band
 * @param upperlimit upper limit of hysteresis band
 * @return float output of filter
 */
float uz_hysteresisband_filter(float input, float lowerlimit, float upperlimit);

/**
 * @brief helper function for evaluation function
 * 
 * @param input fault index value to be evaluated
 * @param threshold threshold value for the evaluation
 * @return float output of the evaluation
 */
float uz_thresholdEvaluation(float input, float threshold);


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





