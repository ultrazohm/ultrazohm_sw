/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2021 Dennis Hufnagel
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

#include "uz_FOC.h"


static struct uz_dq_t uz_FOC_CurrentControl(uz_FOC* self, struct uz_dq_t i_reference_Ampere, struct uz_dq_t i_actual_Ampere,uz_PI_Controller_config* Controller_id,uz_PI_Controller_config* Controller_iq);
static struct uz_dq_t uz_FOC_decoupling(enum uz_FOC_decoupling_select decoupling_select, struct uz_PMSM_t pmsm,struct uz_dq_t actual_Ampere, float omega_el_rad_per_sec);

void uz_FOC_sample(uz_FOC* self,uz_PI_Controller_config* Controller_id,uz_PI_Controller_config* Controller_iq, struct uz_dq_t i_reference_Ampere, struct uz_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float* output_volts_d, float* output_volts_q) {
	#pragma HLS INTERFACE s_axilite port=self                      bundle = Din
	#pragma HLS INTERFACE s_axilite port=Controller_id             bundle = Din
	#pragma HLS INTERFACE s_axilite port=Controller_iq             bundle = Din
	#pragma HLS INTERFACE s_axilite port=i_reference_Ampere        bundle = Din
	#pragma HLS INTERFACE s_axilite port=i_actual_Ampere           bundle = Din
	#pragma HLS INTERFACE s_axilite port=V_dc_volts                bundle = Din
	#pragma HLS INTERFACE s_axilite port=omega_el_rad_per_sec      bundle = Din
	#pragma HLS INTERFACE s_axilite port=return                    bundle = Din
	#pragma HLS INTERFACE m_axi port=output_volts_q offset=slave   bundle=Dout depth=50
	#pragma HLS INTERFACE m_axi port=output_volts_d offset=slave   bundle=Dout depth=50
	struct uz_dq_t u_pre_limit_Volts = uz_FOC_CurrentControl(self, i_reference_Ampere, i_actual_Ampere,Controller_id,Controller_iq);
	struct uz_dq_t u_decoup_Volts = uz_FOC_decoupling(self->decoupling_select, self->config_PMSM, i_actual_Ampere, omega_el_rad_per_sec);
	u_pre_limit_Volts.d += u_decoup_Volts.d;
	u_pre_limit_Volts.q += u_decoup_Volts.q;
	*output_volts_d = uz_FOC_SpaceVector_Limitation_d(u_pre_limit_Volts, V_dc_volts, omega_el_rad_per_sec, i_actual_Ampere, &self->ext_clamping);
	*output_volts_q = uz_FOC_SpaceVector_Limitation_q(u_pre_limit_Volts, V_dc_volts, omega_el_rad_per_sec, i_actual_Ampere, &self->ext_clamping);
	//*u_output_Volts = uz_FOC_SpaceVector_Limitation(u_pre_limit_Volts, V_dc_volts, omega_el_rad_per_sec, i_actual_Ampere, &self->ext_clamping);
}

static struct uz_dq_t uz_FOC_CurrentControl(uz_FOC* self, struct uz_dq_t i_reference_Ampere, struct uz_dq_t i_actual_Ampere,uz_PI_Controller_config* Controller_id,uz_PI_Controller_config* Controller_iq) {
	struct uz_dq_t u_output_Volts = { 0 };
	u_output_Volts.q = uz_PI_Controller_sample(Controller_iq,self->I_rst, i_reference_Ampere.q, i_actual_Ampere.q, self->ext_clamping);
	u_output_Volts.d = uz_PI_Controller_sample(Controller_id,self->I_rst, i_reference_Ampere.d, i_actual_Ampere.d, self->ext_clamping);
	return (u_output_Volts);

}

static struct uz_dq_t uz_FOC_decoupling(enum uz_FOC_decoupling_select decoupling_select, struct uz_PMSM_t config_PMSM, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec){
	struct uz_dq_t decouple_voltage={0};
	switch (decoupling_select)
    {
    case no_decoupling:
        // do nothing since no decoupling
        break;
    case linear_decoupling:
        decouple_voltage=uz_FOC_linear_decoupling(config_PMSM, i_actual_Ampere, omega_el_rad_per_sec);
        break;
    default:
        break;
    }
	return (decouple_voltage);
}

