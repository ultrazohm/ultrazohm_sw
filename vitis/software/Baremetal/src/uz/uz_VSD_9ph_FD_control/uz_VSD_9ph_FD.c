/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Valentin Hoppe
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
static uz_9ph_abc_t uz_vsd_fd_hysteresis_filter(uz_9ph_abc_t input, float lowerlimit, float upperlimit);
static uz_9ph_abc_t uz_vsd_fd_9ph_evaluation(uz_9ph_abc_t input, float threshold);
static inline float uz_vsd_opf_9ph_fault_index_general(const float VSD_line[9], uz_9ph_alphabeta_t currents);

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

int uz_vsd_opf_9ph_get_n_fault(uz_9ph_abc_t indices){
	float sum = indices.a1 + indices.b1 + indices.c1 + indices.a2 + indices.b2 + indices.c2 + indices.a3 + indices.b3 + indices.c3; 
	return (int)sum;
}

float index_a1_raw;
float index_a1_filtered;
float index_a1_th;

uz_9ph_abc_t uz_vsd_opf_9ph_faultdetection_step(uz_VSD_9ph_FD_t* VSD_FD, uz_9ph_alphabeta_t vsdcurrents, float omega_el_rad_per_sec){
	uz_9ph_abc_t indices = {0};

	// calculate fault indices
	indices = uz_vsd_opf_9ph_fault_indices_calculation(vsdcurrents);
	index_a1_raw = indices.a1;
	// filter with hysteresis filter
	indices = uz_vsd_fd_hysteresis_filter(indices, VSD_FD->lowerlimit, VSD_FD->upperlimit);
	index_a1_th = indices.a1;
	// set filterlength of moving average filter according to current omega_el
	uint32_t new_filterLength = 1;
	if (omega_el_rad_per_sec != 0){
		new_filterLength = (uint32_t)(VSD_FD->percent_of_el_period*VSD_FD->sample_frequency_Hz*2.0f*(float)M_PI/fabsf(omega_el_rad_per_sec));
	}

	if(new_filterLength > VSD_FD->mov_average_filter_length){
		new_filterLength = VSD_FD->mov_average_filter_length;
	}else if(new_filterLength < 10){
		new_filterLength = 10;
	}


	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R1, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R2, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R3, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R4, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R5, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R6, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R7, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R8, new_filterLength);
	uz_movingAverageFilter_set_filterLength(VSD_FD->movingAverageFilter_R9, new_filterLength);

	// moving average filter
	indices.a1 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R1, indices.a1);
	indices.b1 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R2, indices.b1);
	indices.c1 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R3, indices.c1);
	indices.a2 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R4, indices.a2);
	indices.b2 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R5, indices.b2);
	indices.c2 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R6, indices.c2);
	indices.a3 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R7, indices.a3);
	indices.b3 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R8, indices.b3);
	indices.c3 = uz_movingAverageFilter_sample_variable_length(VSD_FD->movingAverageFilter_R9, indices.c3);
	index_a1_filtered = indices.a1;
	// evaluation of fault indices
	indices = uz_vsd_fd_9ph_evaluation(indices, VSD_FD->threshold);
	return indices;
}

static float uz_divide(float num, float denom){
	float result = 0.0f;
	if(denom != 0.0f){
		result = num/denom;
	}
	return result;
}

uz_9ph_abc_t uz_vsd_opf_9ph_fault_indices_calculation(uz_9ph_alphabeta_t input){
	uz_9ph_abc_t output = {
		.a1 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[0][0], input),
		.b1 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[1][0], input),
	 	.c1 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[2][0], input),
		.a2 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[3][0], input),
		.b2 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[4][0], input),
		.c2 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[5][0], input),
		.a3 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[6][0], input),
		.b3 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[7][0], input),
		.c3 = uz_vsd_opf_9ph_fault_index_general(&inv_vsd_mat_asym_9ph[8][0], input)};
	return output;
}

static uz_9ph_abc_t uz_vsd_fd_hysteresis_filter(uz_9ph_abc_t input, float lowerlimit, float upperlimit){
	uz_9ph_abc_t output = {
		.a1 = uz_signals_hysteresisband_filter(input.a1, upperlimit, lowerlimit),
		.b1 = uz_signals_hysteresisband_filter(input.b1, upperlimit, lowerlimit),
		.c1 = uz_signals_hysteresisband_filter(input.c1, upperlimit, lowerlimit),
		.a2 = uz_signals_hysteresisband_filter(input.a2, upperlimit, lowerlimit),
		.b2 = uz_signals_hysteresisband_filter(input.b2, upperlimit, lowerlimit),
		.c2 = uz_signals_hysteresisband_filter(input.c2, upperlimit, lowerlimit),
		.a3 = uz_signals_hysteresisband_filter(input.a3, upperlimit, lowerlimit),
		.b3 = uz_signals_hysteresisband_filter(input.b3, upperlimit, lowerlimit),
		.c3 = uz_signals_hysteresisband_filter(input.c3, upperlimit, lowerlimit)};
	return output;
}


static uz_9ph_abc_t uz_vsd_fd_9ph_evaluation(uz_9ph_abc_t input, float threshold){
	uz_9ph_abc_t output = {
		.a1 = uz_signals_threshold_Evaluation(input.a1, threshold),
		.b1 = uz_signals_threshold_Evaluation(input.b1, threshold),
		.c1 = uz_signals_threshold_Evaluation(input.c1, threshold),
		.a2 = uz_signals_threshold_Evaluation(input.a2, threshold),
		.b2 = uz_signals_threshold_Evaluation(input.b2, threshold),
		.c2 = uz_signals_threshold_Evaluation(input.c2, threshold),
		.a3 = uz_signals_threshold_Evaluation(input.a3, threshold),
		.b3 = uz_signals_threshold_Evaluation(input.b3, threshold),
		.c3 = uz_signals_threshold_Evaluation(input.c3, threshold)};
	return output;
}

static inline float uz_vsd_opf_9ph_fault_index_general(const float VSD_line[9], uz_9ph_alphabeta_t currents){
	float numinator = -VSD_line[2]*currents.x1 - VSD_line[3]*currents.y1 - VSD_line[4]*currents.x2 - VSD_line[5]*currents.y2 - VSD_line[6]*currents.x3 - VSD_line[7]*currents.y3 - VSD_line[8]*currents.zero;
	float denominator = VSD_line[0]*currents.alpha +  VSD_line[1]*currents.beta;
	return uz_divide(numinator, denominator);
}

#endif

