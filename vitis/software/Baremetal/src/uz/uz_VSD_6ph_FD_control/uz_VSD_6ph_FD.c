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
 * @brief helper function vor evaluation function
 *
 * @param input fault index value to be evaluated
 * @param threshold threshold value for the evaluation
 * @return float output of the evaluation
 */
float uz_thresholdEvaluation(float input, float threshold);



uz_6phFD_indices uz_vsd_opf_6ph_faultdetection(uz_6ph_alphabeta_t input){

	uz_6phFD_indices output = {0};
	float denum = 0.0f;

	//fault index for phase 1
	if(input.alpha + input.z1 == 0){
		output.R1 = 0.0f;
	}else{
		output.R1 = -input.x/(input.alpha + input.z1);
	}


	//fault index for phase 2
	denum = -input.alpha + sqrtf(3.0f)* input.beta;
	if(denum == 0){
		output.R2 = 0.0f;
	}else{
		output.R2 = (input.x + sqrtf(3.0f)*input.y - 2.0f*input.z1)/(denum);
	}

	//fault index for phase 3
	denum = -input.alpha - sqrtf(3.0f)*input.beta;
	if(denum == 0){
		output.R3 = 0.0f;
	}else{
		output.R3 = (input.x - sqrtf(3.0f)*input.y -2.0f*input.z1)/(denum);
	}

	//fault index for phase 4
	denum = input.alpha + 1.0f/sqrtf(3.0f)*input.beta;
	if(input.alpha + input.z1 == 0.0f){
		output.R4 = 0.0f;
	}else{
		output.R4 = (input.x -1/sqrtf(3.0f)*input.y - 2.0f/sqrtf(3.0f) * input.z2)/(denum);
	}

	//fault index for phase 5
	denum = input.alpha - 1/sqrtf(3.0f)*input.beta;
	if(denum == 0){
		output.R5 = 0.0f;
	}else{
		output.R5 = (input.x  + 1/sqrtf(3.0f)*input.y + 2.0f/sqrtf(3.0f)*input.z2)/(denum);
	}

	//fault index for phase 6
	if(input.beta - input.z2 == 0.0f){
		output.R6 = 0.0f;
	}else{
		output.R6 = -input.y/(input.beta - input.z2);
	}

/////
	return output;
}

uz_6phFD_indices uz_vsd_fd_hysteresis_filter(uz_6phFD_indices input, float lowerlimit, float upperlimit){
	input.R1 = uz_hysteresisband_filter(input.R1, lowerlimit, upperlimit);
	input.R2 = uz_hysteresisband_filter(input.R2, lowerlimit, upperlimit);
	input.R3 = uz_hysteresisband_filter(input.R3, lowerlimit, upperlimit);
	input.R4 = uz_hysteresisband_filter(input.R4, lowerlimit, upperlimit);
	input.R5 = uz_hysteresisband_filter(input.R5, lowerlimit, upperlimit);
	input.R6 = uz_hysteresisband_filter(input.R6, lowerlimit, upperlimit);
	return input;
}


float uz_hysteresisband_filter(float input, float lowerlimit, float upperlimit){
	if((input > upperlimit) | (input < lowerlimit)){
		input = 0.0f;
	}
	return input;
}

uz_6phFD_indices uz_vsd_fd_evaluation(uz_6phFD_indices input, float threshold){
	input.R1 = uz_thresholdEvaluation(input.R1, threshold);
	input.R2 = uz_thresholdEvaluation(input.R2, threshold);
	input.R3 = uz_thresholdEvaluation(input.R3, threshold);
	input.R4 = uz_thresholdEvaluation(input.R4, threshold);
	input.R5 = uz_thresholdEvaluation(input.R5, threshold);
	input.R6 = uz_thresholdEvaluation(input.R6, threshold);
	return input;
}

float uz_thresholdEvaluation(float input, float threshold){
	if(input > threshold){
		return 1.0f;
	}else{
		return 0.0f;
	}
}



