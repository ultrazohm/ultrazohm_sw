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

float offset_theta_pendulum=0.0f;
static uz_incrementalEncoder_t* encoder_D5_1;
static uz_incrementalEncoder_t* encoder_D5_2;
static uz_incrementalEncoder_t* encoder_D5_3;
//----------------------------------------------------

//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------

#define OMEGA_PER_OVER_SAMPLE_RPM 500.0f
#define IncEncoderLPF_freq 1000.0f

// Incremental encoder from motor
void initialize_incremental_encoder_ipcore_on_D5_1(float incrementalEncoderResolution, float motorPolePairNumber){
	struct uz_incrementalEncoder_config encoder_D5_1_config={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREENCODER_V24_IP_0_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber
	};
	encoder_D5_1=uz_incrementalEncoder_init(encoder_D5_1_config);
}

void initialize_incremental_encoder_ipcore_on_D5_2(float PosEncoderResolution, float motorPolePairNumber){
	struct uz_incrementalEncoder_config encoder_D5_2_config={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREENCODER_V24_IP_1_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=PosEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber
	};
	encoder_D5_2=uz_incrementalEncoder_init(encoder_D5_2_config);
}
// Angle encoder pendulum
void initialize_incremental_encoder_ipcore_on_D5_3(float AngleEncoderResolution, float motorPolePairNumber){
	struct uz_incrementalEncoder_config encoder_D5_3_config={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREENCODER_V24_IP_2_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=AngleEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber,
	};
	encoder_D5_3=uz_incrementalEncoder_init(encoder_D5_3_config);
}


void update_speed_and_position_of_encoder_on_D5_1(DS_Data* const data){
	data->av.theta_elec1	= uz_incrementalEncoder_get_theta_el(encoder_D5_1);
	data->av.mechanicalRotorSpeed1 = uz_incrementalEncoder_get_omega_mech(encoder_D5_1) * 60.0f / (2.0f*M_PI);
	data->av.position_motor1 = uz_incrementalEncoder_get_position(encoder_D5_1);

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(data->av.mechanicalRotorSpeed1, &speed_lpf_mem_in, &speed_lpf_mem_out,
	data->av.isr_samplerate_s, IncEncoderLPF_freq);
	}

void update_speed_and_position_of_encoder_on_D5_2(DS_Data* const data){
	data->av.theta_elec2	= uz_incrementalEncoder_get_theta_el(encoder_D5_2);
	data->av.mechanicalRotorSpeed2 = uz_incrementalEncoder_get_omega_mech(encoder_D5_2) * 60.0f / (2.0f*M_PI);
	data->av.position_motor2 = uz_incrementalEncoder_get_position(encoder_D5_2);

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(data->av.mechanicalRotorSpeed2, &speed_lpf_mem_in, &speed_lpf_mem_out,
	data->av.isr_samplerate_s, IncEncoderLPF_freq);
}
void update_speed_and_position_of_encoder_on_D5_3(DS_Data* const data){
	data->av.theta_elec3	= uz_incrementalEncoder_get_theta_el(encoder_D5_3);
	data->av.mechanicalRotorSpeed3 = uz_incrementalEncoder_get_omega_mech(encoder_D5_3) * 60.0f / (2.0f*M_PI);
	data->av.position_motor3 = uz_incrementalEncoder_get_position(encoder_D5_3);

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(data->av.mechanicalRotorSpeed3, &speed_lpf_mem_in, &speed_lpf_mem_out,
	data->av.isr_samplerate_s, IncEncoderLPF_freq);

}

void reset_ip_core_of_encoder_on_D5_3(DS_Data* const data){
//	uz_incrementalEncoder_reset_ip_core(encoder_D5_3);
	offset_theta_pendulum=data->av.theta_pendulum;
}

