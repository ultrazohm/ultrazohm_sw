

#include "uz_VSD6phFD.h"
#include <math.h>

float uz_hysteresisband_filter(float input, float lowerlimit, float upperlimit);
float uz_thresholdEvaluation(float input, float threshold);

uz_6phFD_indices uz_vsd_opf_6ph_faultdetection(uz_6ph_alphabeta_t input){

	uz_6phFD_indices output = {0};
	float denum = 0;

/////////////////////////
/*
		//fault index for phase 1
	if(input.alpha + input.z1 == 0){
		output.R1 = 0.0f;
	}else{
		output.R1 = -input.x/(input.alpha + input.z1);
	}


	//fault index for phase 2
	denum = -input.alpha + sqrt(3)* input.beta - sqrt(3)*input.y + 2*input.z1;
	if(denum == 0){
		output.R2 = 0.0f;
	}else{
		output.R2 = input.x/(denum);
	}

	//fault index for phase 3
	denum = -input.alpha - sqrt(3)*input.beta + sqrt(3)*input.y +2*input.z1;
	if(denum == 0){
		output.R3 = 0.0f;
	}else{
		output.R3 = input.x/(denum);
	}

	//fault index for phase 4
	denum = input.alpha + 1/sqrt(3)*input.beta + 1/sqrt(3)*input.y + 2/sqrt(3) * input.z2;
	if(input.alpha + input.z1 == 0){
		output.R4 = 0.0f;
	}else{
		output.R4 = input.x/(denum);
	}

	//fault index for phase 5
	denum = input.alpha - 1/sqrt(3)*input.beta - 1/sqrt(3)*input.y - 2/sqrt(3)*input.z2;
	if(denum == 0){
		output.R5 = 0.0f;
	}else{
		output.R5 = input.x/(denum);
	}

	//fault index for phase 6
	if(input.beta - input.z2 == 0){
		output.R6 = 0.0f;
	}else{
		output.R6 = -input.y/(input.beta - input.z2);
	}

*/
/////////////////////////

	//fault index for phase 1
	if(input.alpha + input.z1 == 0){
		output.R1 = 0.0f;
	}else{
		output.R1 = -input.x/(input.alpha + input.z1);
	}


	//fault index for phase 2
	denum = -input.alpha + sqrt(3)* input.beta;
	if(denum == 0){
		output.R2 = 0.0f;
	}else{
		output.R2 = (input.x + sqrt(3)*input.y - 2*input.z1)/(denum);
	}

	//fault index for phase 3
	denum = -input.alpha - sqrt(3)*input.beta;
	if(denum == 0){
		output.R3 = 0.0f;
	}else{
		output.R3 = (input.x - sqrt(3)*input.y -2*input.z1)/(denum);
	}

	//fault index for phase 4
	denum = input.alpha + 1/sqrt(3)*input.beta;
	if(input.alpha + input.z1 == 0){
		output.R4 = 0.0f;
	}else{
		output.R4 = (input.x -1/sqrt(3)*input.y - 2/sqrt(3) * input.z2)/(denum);
	}

	//fault index for phase 5
	denum = input.alpha - 1/sqrt(3)*input.beta;
	if(denum == 0){
		output.R5 = 0.0f;
	}else{
		output.R5 = (input.x  + 1/sqrt(3)*input.y + 2/sqrt(3)*input.z2)/(denum);
	}

	//fault index for phase 6
	if(input.beta - input.z2 == 0){
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

uz_6phFD_indices uz_fsd_fd_evaluation(uz_6phFD_indices input, float threshold){
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
