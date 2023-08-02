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

#include "uz_VSD_9ph_FD.h"
#include "../uz_global_configuration.h"
#if UZ_9PH_OPEN_PHASE_FAULT_DETECTION > 0U

#include "../uz_signals/uz_signals.h"
#include <math.h>
#include "../uz_movingAverageFilter/uz_movingAverageFilter.h"
#include <stdbool.h>
#include "../uz_HAL.h"


const float inv_vsd_mat_asym_9ph[9][9] = 
        {
            { 1.0000000f, -0.0000000f, 1.0000000f, 0.0000000f, 1.0000000f, -0.0000000f, 1.0000000f, -0.0000000f, 1.0000000f },
            { -0.5000000f, 0.8660254f, 1.0000000f, -0.0000000f, -0.5000000f, -0.8660254f, -0.5000000f, 0.8660254f, 1.0000000f },
            { -0.5000000f, -0.8660254f, 1.0000000f, 0.0000000f, -0.5000000f, 0.8660254f, -0.5000000f, -0.8660254f, 1.0000000f },
            { 0.9396926f, 0.3420201f, 0.5000000f, 0.8660254f, -0.1736482f, 0.9848078f, -0.7660444f, 0.6427876f, -1.0000000f },
            { -0.7660444f, 0.6427876f, 0.5000000f, 0.8660254f, 0.9396926f, -0.3420201f, -0.1736482f, -0.9848078f, -1.0000000f },
            { -0.1736482f, -0.9848078f, 0.5000000f, 0.8660254f, -0.7660444f, -0.6427876f, 0.9396926f, 0.3420201f, -1.0000000f },
            { 0.7660444f, 0.6427876f, -0.5000000f, 0.8660254f, -0.9396926f, -0.3420201f, 0.1736482f, -0.9848078f, 1.0000000f },
            { -0.9396926f, 0.3420201f, -0.5000000f, 0.8660254f, 0.1736482f, 0.9848078f, 0.7660444f, 0.6427876f, 1.0000000f },
            { 0.1736482f, -0.9848078f, -0.5000000f, 0.8660254f, 0.7660444f, -0.6427876f, -0.9396926f, 0.3420201f, 1.0000000f }};

typedef struct uz_VSD_9ph_FD_t{
	bool is_ready;
    float upperlimit;                   /**< upper limit of hysteresis band */
    float lowerlimit;                   /**< lowerlimit lower limit of hysteresis band */
    float threshold;                    /**< threshold value from which a fault index is judged as an error */
    uint32_t mov_average_filter_length;    /**< mov_average_filter_length maximal length of moving average filter */
    float sample_frequency_Hz;          /**< sample_frequency_Hz sample frequency in Hz */
    float percent_of_el_period;         /**< percent_of_el_period desired filter length in percent of an electric period */
	uz_movingAverageFilter_t* movingAverageFilter_R1; /**< moving average filter for fault index R1*/
    uz_movingAverageFilter_t* movingAverageFilter_R2; /**< moving average filter for fault index R2*/
    uz_movingAverageFilter_t* movingAverageFilter_R3; /**< moving average filter for fault index R3*/
    uz_movingAverageFilter_t* movingAverageFilter_R4; /**< moving average filter for fault index R4*/
    uz_movingAverageFilter_t* movingAverageFilter_R5; /**< moving average filter for fault index R5*/
    uz_movingAverageFilter_t* movingAverageFilter_R6; /**< moving average filter for fault index R6*/
	uz_movingAverageFilter_t* movingAverageFilter_R7; /**< moving average filter for fault index R7*/
	uz_movingAverageFilter_t* movingAverageFilter_R8; /**< moving average filter for fault index R8*/
	uz_movingAverageFilter_t* movingAverageFilter_R9; /**< moving average filter for fault index R9*/
}uz_VSD_9ph_FD_t;

static uint32_t instance_VSD_9ph_FD_counter = 0U;
static uz_VSD_9ph_FD_t instances_VSD_9ph_FD[UZ_9PH_OPEN_PHASE_FAULT_DETECTION] = { 0 };

static uz_VSD_9ph_FD_t* uz_VSD_9ph_FD_allocation(void);
static uz_9phFD_indices uz_vsd_fd_hysteresis_filter(uz_9phFD_indices input, float lowerlimit, float upperlimit);
static uz_9phFD_indices uz_vsd_fd_evaluation(uz_9phFD_indices input, float threshold);
static inline float uz_vsd_opf_9ph_fault_index_general(float VSD_line[9], uz_9ph_alphabeta_t currents);

static uz_VSD_9ph_FD_t* uz_VSD_9ph_FD_allocation(void){
 	uz_assert(instance_VSD_9ph_FD_counter < UZ_9PH_OPEN_PHASE_FAULT_DETECTION);
 	uz_VSD_9ph_FD_t* self = &instances_VSD_9ph_FD[instance_VSD_9ph_FD_counter];
  	instance_VSD_9ph_FD_counter = instance_VSD_9ph_FD_counter + 1U;
 	uz_assert_false(self->is_ready);
 	self->is_ready = true;
 	return (self);
}

uz_VSD_9ph_FD_t* uz_VSD_9ph_FD_init(struct uz_VSD_9ph_FD_config config){
	uz_VSD_9ph_FD_t* self = uz_VSD_9ph_FD_allocation();

    self->upperlimit = config.upperlimit;                  
    self->lowerlimit = config.lowerlimit;                   
    self->threshold = config.threshold;                    
    self->mov_average_filter_length = config.mov_average_filter_length;    
    self->sample_frequency_Hz = config.sample_frequency_Hz;            
    self->percent_of_el_period = config.percent_of_el_period;
	self->movingAverageFilter_R1 = config.movingAverageFilter_R1;
	self->movingAverageFilter_R2 = config.movingAverageFilter_R2;
	self->movingAverageFilter_R3 = config.movingAverageFilter_R3;
	self->movingAverageFilter_R4 = config.movingAverageFilter_R4;
	self->movingAverageFilter_R5 = config.movingAverageFilter_R5;
	self->movingAverageFilter_R6 = config.movingAverageFilter_R6;
	self->movingAverageFilter_R7 = config.movingAverageFilter_R7;
	self->movingAverageFilter_R8 = config.movingAverageFilter_R8;
	self->movingAverageFilter_R9 = config.movingAverageFilter_R9;
    return(self);
}

uz_9phFD_indices uz_vsd_opf_9ph_faultdetection_step(uz_VSD_9ph_FD_t* VSD_FD, uz_9ph_alphabeta_t vsdcurrents, float omega_el_rad_per_sec){
	uz_9phFD_indices indices = {0};

	// calculate fault indices
	indices = uz_vsd_opf_9ph_fault_indices_calculation(vsdcurrents);

	// filter with hysteresis filter
	indices = uz_vsd_fd_hysteresis_filter(indices, VSD_FD->lowerlimit, VSD_FD->upperlimit);

	// set filterlength of moving average filter according to current omega_el
	uint32_t new_filterLength = 1;
	if (omega_el_rad_per_sec != 0){
		new_filterLength = (uint32_t)(VSD_FD->percent_of_el_period*VSD_FD->sample_frequency_Hz*2.0f*(float)M_PI/fabsf(omega_el_rad_per_sec));
	}

	if(new_filterLength > VSD_FD->mov_average_filter_length){
		new_filterLength = VSD_FD->mov_average_filter_length;
	}else if(new_filterLength < 1){
		new_filterLength = 1;
	}


	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R1, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R2, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R3, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R4, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R5, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R6, new_filterLength);

	// moving average filter
	indices.R1 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R1, indices.R1);
	indices.R2 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R2, indices.R2);
	indices.R3 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R3, indices.R3);
	indices.R4 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R4, indices.R4);
	indices.R5 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R5, indices.R5);
	indices.R6 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R6, indices.R6);


	// evaluation of fault indices
	return uz_vsd_fd_evaluation(indices, VSD_FD->threshold);
}

static float uz_divide(float num, float denom){
	float result = 0.0f;
	if(denom != 0.0f){
		result = num/denom;
	}
	return result;
}

uz_9phFD_indices uz_vsd_opf_9ph_fault_indices_calculation(uz_9ph_alphabeta_t input){
	uz_9phFD_indices output = {
		.R1 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[0][0], input),
		.R2 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[1][0], input),
	 	.R3 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[2][0], input),
		.R4 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[3][0], input),
		.R5 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[4][0], input),
		.R6 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[5][0], input),
		.R7 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[6][0], input),
		.R8 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[7][0], input),
		.R9 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[8][0], input)};
	return output;
}

static uz_9phFD_indices uz_vsd_fd_hysteresis_filter(uz_9phFD_indices input, float lowerlimit, float upperlimit){
	input.R1 = uz_signals_hysteresisband_filter(input.R1, upperlimit, lowerlimit);
	input.R2 = uz_signals_hysteresisband_filter(input.R2, upperlimit, lowerlimit);
	input.R3 = uz_signals_hysteresisband_filter(input.R3, upperlimit, lowerlimit);
	input.R4 = uz_signals_hysteresisband_filter(input.R4, upperlimit, lowerlimit);
	input.R5 = uz_signals_hysteresisband_filter(input.R5, upperlimit, lowerlimit);
	input.R6 = uz_signals_hysteresisband_filter(input.R6, upperlimit, lowerlimit);
	input.R7 = uz_signals_hysteresisband_filter(input.R7, upperlimit, lowerlimit);
	input.R8 = uz_signals_hysteresisband_filter(input.R8, upperlimit, lowerlimit);
	input.R9 = uz_signals_hysteresisband_filter(input.R9, upperlimit, lowerlimit);

	return input;
}


static uz_9phFD_indices uz_vsd_fd_evaluation(uz_9phFD_indices input, float threshold){
	input.R1 = uz_signals_threshold_Evaluation(input.R1, threshold);
	input.R2 = uz_signals_threshold_Evaluation(input.R2, threshold);
	input.R3 = uz_signals_threshold_Evaluation(input.R3, threshold);
	input.R4 = uz_signals_threshold_Evaluation(input.R4, threshold);
	input.R5 = uz_signals_threshold_Evaluation(input.R5, threshold);
	input.R6 = uz_signals_threshold_Evaluation(input.R6, threshold);
	input.R7 = uz_signals_threshold_Evaluation(input.R7, threshold);
	input.R8 = uz_signals_threshold_Evaluation(input.R8, threshold);
	input.R9 = uz_signals_threshold_Evaluation(input.R9, threshold);
	return input;
}

static inline float uz_vsd_opf_9ph_fault_index_general(float VSD_line[9], uz_9ph_alphabeta_t currents){
	float numinator = -VSD_line[2]*currents.x1 - VSD_line[3]*currents.y1 - VSD_line[4]*currents.x2 - VSD_line[5]*currents.y2 - VSD_line[6]*currents.x3 - VSD_line[7]*currents.y3 - VSD_line[8]*currents.zero;
	float denominator = VSD_line[0]*currents.alpha +  VSD_line[1]*currents.beta;
	return uz_divide(numinator, denominator);
}

#endif

