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

static uz_incrementalEncoder_t* encoder_D5_1_v25;
static uz_incrementalEncoder_t* encoder_D5_2_v25;
static uz_incrementalEncoder_t* encoder_D5_3_v25;
//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------

#define OMEGA_PER_OVER_SAMPLE_RPM 1000.0f
#define IncEncoderLPF_freq 1000.0f





// Incremental encoder from motor
void initialize_incremental_encoder_ipcore_v25_on_D5_1(float incrementalEncoderResolution, float motorPolePairNumber, float speed_timeout){
	struct uz_incrementalEncoder_config encoder_D5_1_config_v25={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_0_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber,
		.speed_timeout_in_ms = speed_timeout,
	};
	encoder_D5_1_v25=uz_incrementalEncoder_init_v25(encoder_D5_1_config_v25);
}

void initialize_incremental_encoder_ipcore_v25_on_D5_2(float PosEncoderResolution, float motorPolePairNumber, float speed_timeout){
	struct uz_incrementalEncoder_config encoder_D5_2_config_v25={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_1_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=PosEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber,
		.speed_timeout_in_ms = speed_timeout,
	};
	encoder_D5_2_v25=uz_incrementalEncoder_init_v25(encoder_D5_2_config_v25);
}
// Angle encoder pendulum
void initialize_incremental_encoder_ipcore_v25_on_D5_3(float AngleEncoderResolution, float motorPolePairNumber, float speed_timeout){
	struct uz_incrementalEncoder_config encoder_D5_3_config_v25={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_2_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=AngleEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber,
		.speed_timeout_in_ms = speed_timeout,
	};
	encoder_D5_3_v25=uz_incrementalEncoder_init_v25(encoder_D5_3_config_v25);
}



float omegaA, omegaB,omegaANOT, omegaBNOT;

void update_speed_and_position_of_encoder_on_D5_1_ip_v25(DS_Data* const data){
	data->av.theta_elec	= uz_incrementalEncoder_get_theta_el(encoder_D5_1_v25);
	data->av.mechanicalRotorSpeed = uz_incrementalEncoder_get_omega_mech_OS_N4(encoder_D5_1_v25) * 60.0f / (2.0f*M_PI);
	data->av.mechanicalRotorSpeed_N8 = uz_incrementalEncoder_get_omega_mech_OS_N8(encoder_D5_1_v25) * 60.0f / (2.0f*M_PI);
	data->av.position_motor = uz_incrementalEncoder_get_position(encoder_D5_1_v25);

	omegaA 		= uz_incrementalEncoder_get_omegaA(encoder_D5_1_v25) * 60.0f / (2.0f*M_PI);
	omegaB 		= uz_incrementalEncoder_get_omegaB(encoder_D5_1_v25) * 60.0f / (2.0f*M_PI);
	omegaANOT 	= uz_incrementalEncoder_get_omegaNOTA(encoder_D5_1_v25) * 60.0f / (2.0f*M_PI);
	omegaBNOT 	= uz_incrementalEncoder_get_omegaNOTB(encoder_D5_1_v25) * 60.0f / (2.0f*M_PI);

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(	data->av.mechanicalRotorSpeed, &speed_lpf_mem_in, &speed_lpf_mem_out,
	data->av.isr_samplerate_s, IncEncoderLPF_freq);
}

void update_position_of_encoder_on_D5_2_ip_v25(DS_Data* const data){
	data->av.position_pendulum = uz_incrementalEncoder_get_position(encoder_D5_2_v25);
}
void update_angle_of_encoder_on_D5_3_ip_v25(DS_Data* const data){
	data->av.theta_pendulum	= uz_incrementalEncoder_get_theta_el(encoder_D5_3_v25);

}
