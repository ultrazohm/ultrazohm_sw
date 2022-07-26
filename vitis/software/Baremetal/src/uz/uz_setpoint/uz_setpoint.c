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


#include "uz_setpoint.h"
#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#if UZ_SETPOINT_MAX_INSTANCES > 0
typedef struct uz_SetPoint_t {
	bool is_ready;
    bool ext_clamping;
	struct uz_SetPoint_t_config config;
}uz_SetPoint_t;

static uint32_t instance_counter = 0U;
static uz_SetPoint_t instances[UZ_SETPOINT_MAX_INSTANCES] = { 0 };

static uz_SetPoint_t* uz_SetPoint_allocation(void);

static uz_3ph_dq_t uz_SetPoint_field_weakening(uz_SetPoint_t* self, float id_ref_Ampere, float omega_m_rad_per_sec, float V_dc_volts);
static float uz_SetPoint_decide_id_ref(float I_max, float id_ref_Ampere, float id_field_weakening_Ampere, bool fw_flag);
static float uz_SetPoint_calculate_omega_cut(uz_PMSM_t config_PMSM, float V_SV_max);
static uz_3ph_dq_t uz_SetPoint_calculate_fw_currents(uz_SetPoint_t* self, float omega_el_rad_per_sec, float omega_cut, float V_SV_max);
static void uz_SetPoint_assert_motor_parameters(uz_PMSM_t input, enum uz_Setpoint_motor_type motor_type);

static uz_SetPoint_t* uz_SetPoint_allocation(void){
 uz_assert(instance_counter < UZ_SETPOINT_MAX_INSTANCES);
 uz_SetPoint_t* self = &instances[instance_counter];
 uz_assert_false(self->is_ready);
 instance_counter++;
 self->is_ready = true;
 return (self);
}

uz_SetPoint_t* uz_SetPoint_init(struct uz_SetPoint_t_config config){
    uz_SetPoint_t* self = uz_SetPoint_allocation();
    uz_SetPoint_assert_motor_parameters(config.config_PMSM, config.motor_type);
    self->config = config;
    return(self);
}

uz_3ph_dq_t uz_SetPoint_sample(uz_SetPoint_t* self, float omega_m_rad_per_sec, float M_ref_Nm, float id_ref_Ampere, float V_DC_Volts) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(V_DC_Volts > 0.0f);
    uz_3ph_dq_t output_currents = {0};

    float i_ref = M_ref_Nm / (1.5f * self->config.config_PMSM.polePairs * self->config.config_PMSM.Psi_PM_Vs);
    i_ref = uz_signals_saturation(i_ref, self->config.config_PMSM.I_max_Ampere, -self->config.config_PMSM.I_max_Ampere);
    float id_limit = sqrtf(powf(self->config.config_PMSM.I_max_Ampere, 2.0f) - powf(i_ref, 2.0f));

    switch (self->config.motor_type)
	{
        case (SMPMSM):
            output_currents.q = i_ref;         
            output_currents.d = uz_signals_saturation(id_ref_Ampere, id_limit, -id_limit);
            break;

        case (IPMSM):
            if(fabsf(id_ref_Ampere) > 0.0f) {
                output_currents.q = i_ref;
                output_currents.d = uz_signals_saturation(id_ref_Ampere, id_limit, -id_limit);
            } else { //If no input d-current is requested, calculate id-ref via MTPA
                output_currents.d = (self->config.config_PMSM.Psi_PM_Vs / (4.0f * (self->config.config_PMSM.Lq_Henry - self->config.config_PMSM.Ld_Henry))) - 
                (sqrtf((powf(self->config.config_PMSM.Psi_PM_Vs, 2.0f) / (16.0f * powf((self->config.config_PMSM.Lq_Henry - self->config.config_PMSM.Ld_Henry), 2.0f))) + (powf(i_ref, 2.0f) / 2.0f)));
                if (i_ref < 0.0f) {
                    output_currents.q = -sqrtf((powf(i_ref, 2.0f) - powf(output_currents.d, 2.0f)));//Negative torque
                } else {
                    output_currents.q = sqrtf((powf(i_ref, 2.0f) - powf(output_currents.d, 2.0f)));
                }
            }
            break;

        default:
            uz_assert(0);
    }
    if(self->config.is_field_weakening_active) {
        uz_3ph_dq_t fw_currents = uz_SetPoint_field_weakening(self, id_ref_Ampere, omega_m_rad_per_sec, V_DC_Volts);
        float q_current_before_limit = q_current_before_limit;
        output_currents.q = uz_signals_saturation(output_currents.q, fw_currents.q, -fw_currents.q);
        if(output_currents.q != q_current_before_limit) {
            self->ext_clamping = true;
        } else {
            self->ext_clamping = false;
        }
        output_currents.d  = fw_currents.d;
    }

    return(output_currents);
}

void uz_SetPoint_set_field_weakening(uz_SetPoint_t* self, bool is_field_weakening_active) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	self->config.is_field_weakening_active = is_field_weakening_active;
}

void uz_SetPoint_set_PMSM_config(uz_SetPoint_t* self, uz_PMSM_t input) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_SetPoint_assert_motor_parameters(input, self->config.motor_type);
    self->config.config_PMSM = input;
}

bool uz_SetPoint_get_ext_clamping(uz_SetPoint_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->ext_clamping);
}

static void uz_SetPoint_assert_motor_parameters(uz_PMSM_t input, enum uz_Setpoint_motor_type motor_type) {
    uz_assert(input.polePairs > 0.0f);
	uz_assert(fmodf(input.polePairs, 1.0f) == 0);
	uz_assert(input.R_ph_Ohm > 0.0f);
	uz_assert(input.I_max_Ampere > 0.0f);
	uz_assert(input.Ld_Henry > 0.0f);
	uz_assert(input.Lq_Henry > 0.0f);
	uz_assert(input.Psi_PM_Vs >= 0.0f);
    if(motor_type == IPMSM) {
        uz_assert(input.Ld_Henry != input.Lq_Henry);
    }
}

static uz_3ph_dq_t uz_SetPoint_field_weakening(uz_SetPoint_t* self, float id_ref_Ampere, float omega_m_rad_per_sec, float V_dc_volts){
    uz_3ph_dq_t output = {0};
    bool fw_flag = false;
    float V_SV_max =(V_dc_volts / sqrtf(3.0f) ) * 0.94f;
    float omega_el_rad_per_sec = omega_m_rad_per_sec * self->config.config_PMSM.polePairs;
	float omega_cut = uz_SetPoint_calculate_omega_cut(self->config.config_PMSM, V_SV_max);
    if (fabsf(omega_el_rad_per_sec) > omega_cut) {
        fw_flag = true;
        output = uz_SetPoint_calculate_fw_currents(self, omega_el_rad_per_sec, omega_cut, V_SV_max);
    } else {
	    fw_flag = false;
    }
	output.d = uz_SetPoint_decide_id_ref(self->config.config_PMSM.I_max_Ampere * 0.95f, id_ref_Ampere, output.d, fw_flag);//field-weakening current for d-axis
    output.q = sqrtf(powf(self->config.config_PMSM.I_max_Ampere, 2.0f) - powf(output.d, 2.0f));//new max. ampere limit for q-axis current
            
    return(output);
}

static float uz_SetPoint_decide_id_ref(float I_max, float id_ref_Ampere, float id_field_weakening_Ampere, bool fw_flag){
	//Gives out the input id_ref, as long as fw is off, or the input value is lower than the needed id_fw value to reach its n_ref speed
	float output = 0.0f;
    
    bool id_ref_smaller_than_id_fw = id_ref_Ampere <= id_field_weakening_Ampere;
    bool id_ref_valid = fabsf(id_ref_Ampere) < I_max;
    if(fw_flag == false){
		output = uz_signals_saturation(id_ref_Ampere, I_max, -I_max);      
	} else if ( (fw_flag == true) && (id_ref_smaller_than_id_fw == true) && (id_ref_valid == true)) {
		output = uz_signals_saturation(id_ref_Ampere, I_max, -I_max);
    } else {
	    output = id_field_weakening_Ampere;    
    }
    return(output);
}

static float uz_SetPoint_calculate_omega_cut(uz_PMSM_t config_PMSM, float V_SV_max) {
    float a_omega = (powf(config_PMSM.I_max_Ampere, 2.0f) * powf(config_PMSM.Lq_Henry, 2.0f)) + powf(config_PMSM.Psi_PM_Vs, 2.0f);
	float b_omega = 2.0f * config_PMSM.R_ph_Ohm * config_PMSM.Psi_PM_Vs * config_PMSM.I_max_Ampere;
	float c_omega = (powf(config_PMSM.I_max_Ampere, 2.0f) * powf(config_PMSM.R_ph_Ohm, 2.0f)) - powf(V_SV_max, 2.0f);
    float omega_cut = (-b_omega + sqrtf(powf(b_omega, 2.0f) - (4.0f * a_omega * c_omega) )) / (2.0f * a_omega);
	return (omega_cut);
}

static uz_3ph_dq_t uz_SetPoint_calculate_fw_currents(uz_SetPoint_t* self, float omega_el_rad_per_sec, float omega_cut, float V_SV_max) {
    uz_assert(omega_cut > 0.0f);
    uz_3ph_dq_t output = {0};

switch (self->config.motor_type)
	{
        case (SMPMSM):
            output.d = (self->config.config_PMSM.Psi_PM_Vs / self->config.config_PMSM.Ld_Henry) * ( (omega_cut / fabsf(omega_el_rad_per_sec) ) - 1.0f);
            output.d = uz_signals_saturation(output.d, self->config.config_PMSM.I_max_Ampere, -self->config.config_PMSM.I_max_Ampere);
            break;

        case (IPMSM):;
        float Ld_minus_Lq = powf(self->config.config_PMSM.Ld_Henry, 2.0f) - powf(self->config.config_PMSM.Lq_Henry, 2.0f);
        float psi_pm_times_Ld = self->config.config_PMSM.Psi_PM_Vs * self->config.config_PMSM.Ld_Henry;
        float Lq_times_I_max = powf(self->config.config_PMSM.Lq_Henry, 2.0f) * powf(self->config.config_PMSM.I_max_Ampere, 2.0f);
        float V_max_diff_omega = powf(V_SV_max, 2.0f) / powf(omega_el_rad_per_sec, 2.0f); 
        output.d = (-psi_pm_times_Ld + sqrtf(powf(psi_pm_times_Ld, 2.0f) - (Ld_minus_Lq * (powf(self->config.config_PMSM.Psi_PM_Vs, 2.0f) + Lq_times_I_max - V_max_diff_omega)))) / (Ld_minus_Lq);
        break;            

        default:
            uz_assert(0);
    }
	
	if (output.d < (-self->config.config_PMSM.I_max_Ampere)) {
		output.d = -self->config.config_PMSM.I_max_Ampere;
    }
    return(output);
}
#endif
