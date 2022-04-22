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
#include "../include/encoder_v25.h"
#include "../IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "xparameters.h"

// Declares pointer to instance on file scope. DO NOT DO THIS! Just done here to be compatible to the rest of the legacy code in this file!
static uz_incrementalEncoder_t* encoder_D5_v25;

//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------

#define OMEGA_PER_OVER_SAMPLE_RPM 1000.0f



void initialize_incremental_encoder_ipcore_v25_on_D5(float incrementalEncoderResolution, float motorPolePairNumber, float speed_timeout){
	struct uz_incrementalEncoder_config encoder_D5_config_v25={
		.base_address=XPAR_ENCODER_INCENC_V25_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber,
		.speed_timeout_in_ms = speed_timeout,
	};
	encoder_D5_v25=uz_incrementalEncoder_init_v25(encoder_D5_config_v25);
}

float omegaA, omegaB,omegaANOT, omegaBNOT;

// update speed and position in global data struct
void update_speed_and_position_of_encoder_on_D5_ip_v25(DS_Data* const data){
	data->av_si.theta_elec_V25	= uz_incrementalEncoder_get_theta_el(encoder_D5_v25);
	data->av_si.mechanicalRotorSpeed_V25 = uz_incrementalEncoder_get_omega_mech_OS_N4(encoder_D5_v25) * 60.0f / (2.0f*M_PI);
	data->av_si.mechanicalRotorSpeed_V25_N8 = uz_incrementalEncoder_get_omega_mech_OS_N8(encoder_D5_v25) * 60.0f / (2.0f*M_PI);

	omegaA 		= uz_incrementalEncoder_get_omegaA(encoder_D5_v25) * 60.0f / (2.0f*M_PI);
	omegaB 		= uz_incrementalEncoder_get_omegaB(encoder_D5_v25) * 60.0f / (2.0f*M_PI);
	omegaANOT 	= uz_incrementalEncoder_get_omegaNOTA(encoder_D5_v25) * 60.0f / (2.0f*M_PI);
	omegaBNOT 	= uz_incrementalEncoder_get_omegaNOTB(encoder_D5_v25) * 60.0f / (2.0f*M_PI);

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av_si.mechanicalRotorSpeed_filtered_V25 = LPF1(	data->av_si.mechanicalRotorSpeed_V25_N8, &speed_lpf_mem_in, &speed_lpf_mem_out,
			pwm_freq, data->mrp.IncEncoderLPF_freq);

}
