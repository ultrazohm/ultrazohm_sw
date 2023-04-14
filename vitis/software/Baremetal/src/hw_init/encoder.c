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
#include "../IP_Cores/uz_incrementalEncoder_V26/uz_incrementalEncoder_V26.h"
#include "xparameters.h"

// Declares pointer to instance on file scope. DO NOT DO THIS! Just done here to be compatible to the rest of the legacy code in this file!
static uz_incrementalEncoder_t_V26* encoder_D5;

//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------

#define OMEGA_PER_OVER_SAMPLE_RPM 500.0f
#define IncEncoderLPF_freq 1000.0f

void initialize_incremental_encoder_ipcore_on_D5(float incrementalEncoderResolution, float motorPolePairNumber, uint32_t Mech_Offset, uint32_t Elec_Offset, float speed_timeout){
	struct uz_incrementalEncoder_config_V26 encoder_D5_config={
		.base_address = XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_0_BASEADDR,
		.ip_core_frequency_Hz = 50000000U,
		.line_number_per_turn_mech = incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm = OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair = motorPolePairNumber,
		.Encoder_mech_Offset = Mech_Offset,
		.Encoder_elec_Offset = Elec_Offset,
		.d_axis_Hit_Offset 	= 0U,
		.Counting_Direction = CW_Counting,
		.Speed_Timeout_s = speed_timeout
	};
	encoder_D5=uz_incrementalEncoder_init_V26(encoder_D5_config);
}

void update_speed_and_position_of_encoder_on_D5(DS_Data* const data){	// update speed and position in global data struct
	data->av.theta_elec=uz_incrementalEncoder_get_theta_el_V26(encoder_D5);
	data->av.mechanicalRotorSpeed = uz_incrementalEncoder_get_omega_mech_V26(encoder_D5) * 60.0f / (2.0f*M_PI);

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(	data->av.mechanicalRotorSpeed, &speed_lpf_mem_in, &speed_lpf_mem_out,
			data->av.isr_samplerate_s, IncEncoderLPF_freq);

}

void update_encoder_offsets(uint32_t Mech_Offset, uint32_t Elec_Offset){
	uz_incrementalEncoder_set_new_mechanical_Offset_V26(encoder_D5, Mech_Offset);
	uz_incrementalEncoder_set_new_electrical_Offset_V26(encoder_D5, Elec_Offset);
}
