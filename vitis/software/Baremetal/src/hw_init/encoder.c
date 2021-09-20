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

// Just for debugging & testing
static float debug_omega=0.0f;
static float debug_theta_el=0.0f;
static uint32_t debug_position_mech=0.0f;

//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------
void initialize_incremental_encoder_ipcore_on_D5(float incrementalEncoderResolution, float motorPolePairNumber){
	struct uz_incrementalEncoder_config encoder_D5_config={
		.base_address=XPAR_INCREENCODER_V24_IP_0_BASEADDR,
		.ip_core_frequency_Hz=50000000U,
		.line_number_per_turn_mech=incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm=500.0f,
		.drive_pole_pair=motorPolePairNumber
	};
	encoder_D5=uz_incrementalEncoder_init(encoder_D5_config);
}

float speed_rpm=0.0f;

void update_speed_and_position_of_encoder_on_D5(DS_Data* const data){	// update speed and position in global data struct
	debug_omega=uz_incrementalEncoder_get_omega(encoder_D5);
	debug_theta_el=uz_incrementalEncoder_get_theta_el(encoder_D5);
	debug_position_mech=uz_incrementalEncoder_get_position(encoder_D5);
	speed_rpm = debug_omega * 60 / (2*M_PI);

	//Speed over buffer
	data->av.mechanicalRotorSpeed = speed_rpm; //Calculate mean value for the speed

	// Get electrical angle theta
	data->av.theta_elec  = debug_theta_el;

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(	data->av.mechanicalRotorSpeed, &speed_lpf_mem_in, &speed_lpf_mem_out,
													data->ctrl.samplingFrequency, data->mrp.IncEncoderLPF_freq);

}
