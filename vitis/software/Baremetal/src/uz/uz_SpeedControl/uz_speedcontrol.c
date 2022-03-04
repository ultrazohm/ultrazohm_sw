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


#include "uz_speedcontrol.h"
#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#if UZ_SPEEDCONTROL_MAX_INSTANCES > 0
typedef struct uz_SpeedControl_t {
	bool is_ready;
    bool enable_field_weakening;
	struct uz_PI_Controller* Controller;
}uz_SpeedControl_t;

static uint32_t instance_speedcontrol_counter = 0U;
static uz_SpeedControl_t instances_speedcontrol[UZ_SPEEDCONTROL_MAX_INSTANCES] = { 0 };

static uz_SpeedControl_t* uz_SpeedControl_allocation(void);

static uz_dq_t uz_SpeedControl_field_weakening(uz_PMSM_t config_PMSM, float id_ref_Ampere, float omega_el_rad_per_sec, float V_dc_volts);
static float uz_SpeedControl_decide_id_ref(float I_max, float id_ref_Ampere, float id_field_weakening_Ampere, bool fw_flag);
static float uz_SpeedControl_calculate_omega_cut(uz_PMSM_t config_PMSM, float V_SV_max);
static uz_dq_t uz_SpeedControl_calculate_fw_currents(uz_PMSM_t config_PMSM, float omega_el_rad_per_sec, float omega_cut, float V_SV_max);

static uz_SpeedControl_t* uz_SpeedControl_allocation(void){
 uz_assert(instance_speedcontrol_counter < UZ_SPEEDCONTROL_MAX_INSTANCES);
 uz_SpeedControl_t* self = &instances_speedcontrol[instance_speedcontrol_counter];
 uz_assert_false(self->is_ready);
 instance_speedcontrol_counter++;
 self->is_ready = true;
 return (self);
}

uz_SpeedControl_t* uz_SpeedControl_init(struct uz_SpeedControl_config config){
    uz_SpeedControl_t* self = uz_SpeedControl_allocation();
    self->Controller = uz_PI_Controller_init(config.config_controller);
    self->enable_field_weakening = config.enable_field_weakening;
    return(self);
}

uz_dq_t uz_SpeedControl_sample(uz_SpeedControl_t* self, float omega_el_rad_per_sec, float n_ref_rpm, float V_dc_volts, float id_ref_Ampere, uz_PMSM_t config_PMSM, bool ext_clamping){
    uz_assert_not_NULL(self);
    uz_dq_t i_output_Ampere = {0};
	float omega_el_ref_rad_per_sec = (n_ref_rpm * 2.0f * UZ_PIf * config_PMSM.polePairs) / 60.0f;
    if(self->enable_field_weakening) {
        uz_assert(self->is_ready);
        uz_assert(config_PMSM.polePairs > 0.0f);
	    uz_assert(fmodf(config_PMSM.polePairs, 1.0f) == 0);
        uz_assert(config_PMSM.R_ph_Ohm > 0.0f);
        uz_assert(config_PMSM.I_max_Ampere > 0.0f);
        uz_assert(config_PMSM.Ld_Henry > 0.0f);
        uz_assert(config_PMSM.Lq_Henry > 0.0f);
        uz_assert(config_PMSM.Psi_PM_Vs >= 0.0f);
        uz_assert(V_dc_volts > 0.0f);
        uz_dq_t i_field_weakening_Ampere = uz_SpeedControl_field_weakening(config_PMSM, id_ref_Ampere, omega_el_rad_per_sec, V_dc_volts);
	    i_output_Ampere.d = i_field_weakening_Ampere.d;
        uz_PI_Controller_update_limits(self->Controller, i_field_weakening_Ampere.q, -i_field_weakening_Ampere.q);
    } else {
        i_output_Ampere.d = uz_signals_saturation(id_ref_Ampere, config_PMSM.I_max_Ampere, -config_PMSM.I_max_Ampere);
    }
    i_output_Ampere.q = uz_PI_Controller_sample(self->Controller, omega_el_ref_rad_per_sec, omega_el_rad_per_sec, ext_clamping);
    return(i_output_Ampere);
}

void uz_SpeedControl_reset(uz_SpeedControl_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	uz_PI_Controller_reset(self->Controller);
}

void uz_SpeedControl_set_field_weakening(uz_SpeedControl_t* self, bool field_weakening_status) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	self->enable_field_weakening = field_weakening_status;
}

static uz_dq_t uz_SpeedControl_field_weakening(uz_PMSM_t config_PMSM, float id_ref_Ampere, float omega_el_rad_per_sec, float V_dc_volts){
    uz_dq_t output = {0};
    bool fw_flag = false;
    float V_SV_max =(V_dc_volts / sqrtf(3.0f) ) * 0.95f;
	float omega_cut = uz_SpeedControl_calculate_omega_cut(config_PMSM, V_SV_max);
    if (fabsf(omega_el_rad_per_sec) > omega_cut) {
        fw_flag = true;
        output = uz_SpeedControl_calculate_fw_currents(config_PMSM, omega_el_rad_per_sec, omega_cut, V_SV_max);
    } else {
	    fw_flag = false;
    }
	output.d = uz_SpeedControl_decide_id_ref(config_PMSM.I_max_Ampere * 0.95f, id_ref_Ampere, output.d, fw_flag);
    float iq_max = sqrtf(powf(config_PMSM.I_max_Ampere, 2.0f) - powf(output.d, 2.0f));
    if( (output.q > iq_max) || (fw_flag == false) ) {
         output.q = iq_max;
    }
    return(output);
}

static float uz_SpeedControl_decide_id_ref(float I_max, float id_ref_Ampere, float id_field_weakening_Ampere, bool fw_flag){
	//Gives out the input id_ref, as long as fw is off, or the input value is lower than the needed id_fw value to reach its n_ref speed
	float output = 0.0f;
    bool id_ref_smaller_than_id_fw = id_ref_Ampere <= id_field_weakening_Ampere;
    bool id_ref_valid = fabsf(id_ref_Ampere) < I_max;
    if(fw_flag == false){
		output = uz_signals_saturation(id_ref_Ampere, I_max, -I_max);
	} else if ( (fw_flag == true) && (id_ref_smaller_than_id_fw == true) && (id_ref_valid == true)) {
		output = uz_signals_saturation(id_ref_Ampere, I_max, -I_max);
    }else{
	    output = id_field_weakening_Ampere;
    }
    return(output);
}

static float uz_SpeedControl_calculate_omega_cut(uz_PMSM_t config_PMSM, float V_SV_max) {
	float a_omega = (powf(config_PMSM.I_max_Ampere, 2.0f) * powf(config_PMSM.Lq_Henry, 2.0f)) + powf(config_PMSM.Psi_PM_Vs, 2.0f);
	float b_omega = 2.0f * config_PMSM.R_ph_Ohm * config_PMSM.Psi_PM_Vs * config_PMSM.I_max_Ampere;
	float c_omega = (powf(config_PMSM.I_max_Ampere, 2.0f) * powf(config_PMSM.R_ph_Ohm, 2.0f)) - powf(V_SV_max, 2.0f);
    float omega_cut = (-b_omega + sqrtf(powf(b_omega, 2.0f) - (4.0f * a_omega * c_omega) )) / (2.0f * a_omega);
	return (omega_cut);
}

static uz_dq_t uz_SpeedControl_calculate_fw_currents(uz_PMSM_t config_PMSM, float omega_el_rad_per_sec, float omega_cut, float V_SV_max) {
    uz_assert(omega_cut > 0.0f);
    uz_dq_t output = {0};
	output.d = (config_PMSM.Psi_PM_Vs / config_PMSM.Ld_Henry) * ( (omega_cut / fabsf(omega_el_rad_per_sec) ) - 1.0f);
	if (output.d < (-config_PMSM.I_max_Ampere)) {
		output.d = -config_PMSM.I_max_Ampere;
    }
	float a_iq_fw = (powf(omega_el_rad_per_sec, 2.0f) * powf(config_PMSM.Lq_Henry, 2.0f)) + powf(config_PMSM.R_ph_Ohm, 2.0f);
	float b_iq_fw = 2.0f * config_PMSM.R_ph_Ohm * config_PMSM.Psi_PM_Vs * fabsf(omega_el_rad_per_sec);
	float c_iq_fw = (powf(output.d, 2.0f) * powf(config_PMSM.R_ph_Ohm, 2.0f))
	                + (powf(omega_el_rad_per_sec, 2.0f)
	                                * (powf(config_PMSM.Psi_PM_Vs, 2.0f) + (powf(config_PMSM.Ld_Henry, 2.0f) * powf(output.d, 2.0f))
	                                                + (2.0f * config_PMSM.Psi_PM_Vs * config_PMSM.Ld_Henry * output.d))) - powf(V_SV_max, 2.0f);
   	output.q = (-b_iq_fw + sqrtf(powf(b_iq_fw, 2.0f) - (4.0f * a_iq_fw * c_iq_fw) )) / (2.0f * a_iq_fw);
    return(output);
}

#endif
