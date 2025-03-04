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


//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------

#define OMEGA_PER_OVER_SAMPLE_RPM 500.0f
#define IncEncoderLPF_freq 1000.0f

uz_incrementalEncoder_t* initialize_incremental_encoder_ipcore_on_D5(float incrementalEncoderResolution, float motorPolePairNumber){
	struct uz_incrementalEncoder_config encoder_D5_config={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_0_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=incrementalEncoderResolution,
		.OmegaPerOverSample_in_rpm=OMEGA_PER_OVER_SAMPLE_RPM,
		.drive_pole_pair=motorPolePairNumber,
		.Encoder_elec_Offset = 0U,
		.counting_direction = uz_incrementalEncoder_counting_clock_wise,
		.Speed_Timeout_ms = 10U //10ms
	};
	return(uz_incrementalEncoder_init(encoder_D5_config));
}

void update_speed_and_position_of_encoder_on_D5(DS_Data* const data){	// update speed and position in global data struct
	data->av.theta_elec=uz_incrementalEncoder_get_theta_el(data->objects.encoder_D5);
	data->av.mechanicalRotorSpeed = uz_incrementalEncoder_get_omega_mech(data->objects.encoder_D5) * 60.0f / (2.0f*M_PI);

	//low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(	data->av.mechanicalRotorSpeed, &speed_lpf_mem_in, &speed_lpf_mem_out,
			data->av.isr_samplerate_s, IncEncoderLPF_freq);

}
