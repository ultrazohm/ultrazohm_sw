/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel, Tobias Schindler
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

#include <stdint.h>
#include <math.h>
#include "../include/encoder.h"
#include "../IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "xparameters.h"

// Declares pointer to instance on file scope. DO NOT DO THIS! Just done here to be compatible to the rest of the legacy code in this file!
static uz_incrementalEncoder_t* encoder_D5;
uz_incrementalEncoder_t* encoder_D4;

//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------

#define OMEGA_PER_OVER_SAMPLE_RPM 500.0f

uint32_t encoder_debug_position=0U;

void initialize_incremental_encoder_ipcore_on_D5(float incrementalEncoderResolution, float motorPolePairNumber){
	struct uz_incrementalEncoder_config encoder_D5_config={
		.base_address=XPAR_INCREENCODER_V24_IP_0_BASEADDR,
		.ip_core_frequency_Hz=50000000U,
		.line_number_per_turn_mech=incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber
	};
	encoder_D5=uz_incrementalEncoder_init(encoder_D5_config);
}

void initialize_incremental_encoder_ipcore_on_D4(float incrementalEncoderResolution, float motorPolePairNumber){
	struct uz_incrementalEncoder_config encoder_D4_config={
		.base_address=XPAR_INCREENCODER_V24_IP_1_BASEADDR,
		.ip_core_frequency_Hz=50000000U,
		.line_number_per_turn_mech=incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber
	};
	encoder_D4=uz_incrementalEncoder_init(encoder_D4_config);
}


void update_speed_and_position_of_encoder_on_D5(DS_Data* const data){	// update speed and position in global data struct
	data->av.theta_elec=uz_incrementalEncoder_get_theta_el(encoder_D5);
	data->av.theta_elec=fmodf(data->av.theta_elec*3.0f,2*M_PI);
	data->av.mechanicalRotorSpeed = uz_incrementalEncoder_get_omega_mech(encoder_D5) * 60.0f / (2.0f*M_PI);
	encoder_debug_position=uz_incrementalEncoder_get_position(encoder_D5);
	//encoder_debug_position=fmodf(encoder_debug_position,1024.0f/3.0f);
	// low-pass filter of mechanical speed
	// offset: 5.675603
	// 5.638787
	// 5.381082
	// 5.730824
	// 5.743183
	// 4.166177
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(	data->av.mechanicalRotorSpeed, &speed_lpf_mem_in, &speed_lpf_mem_out,
													data->ctrl.samplingFrequency, data->mrp.IncEncoderLPF_freq);

}
