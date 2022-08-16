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
#include "../uz_newton_raphson/uz_newton_raphson.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#if UZ_SETPOINT_MAX_INSTANCES > 0
typedef struct uz_SetPoint_t {
	bool is_ready;
    bool is_field_weakening_active;
    float omega_cut_rad_per_sec;
	struct uz_SetPoint_config config;
    struct uz_newton_raphson_config newton_MTPA;
    struct uz_newton_raphson_config newton_FW;
}uz_SetPoint_t;

//Declare arrays for newton_MTPA raphson
static float derivate_poly_coefficients_MTPA[4] = {1.0f, 0.0f, 0.0f, 4.0f};
static float coefficients_MTPA[5] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

//Declare arrays for newton_FW raphson
static float derivate_poly_coefficients_FW[4] = {1.0f, 2.0f, 0.0f, 4.0f};
static float coefficients_FW[5] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

static uint32_t instance_counter = 0U;
static uz_SetPoint_t instances[UZ_SETPOINT_MAX_INSTANCES] = { 0 };

static uz_SetPoint_t* uz_SetPoint_allocation(void);

static uz_3ph_dq_t uz_SetPoint_FOC_control(uz_SetPoint_t* self, float omega_m_rad_per_sec, float M_ref_Nm, float V_DC_Volts, uz_3ph_dq_t actual_currents_Ampere);
static uz_3ph_dq_t uz_SetPoint_field_weakening(uz_SetPoint_t* self, float omega_m_rad_per_sec, float V_dc_volts, float i_ref, float M_ref_Nm);
static uz_3ph_dq_t uz_SetPoint_MTPA(uz_SetPoint_t* self, float i_ref_Ampere, float M_ref_Nm);
static void uz_SetPoint_calculate_omega_cut_rad_per_sec(uz_SetPoint_t* self, float V_SV_max, uz_3ph_dq_t actual_currents_Ampere);
static void uz_SetPoint_assert_motor_parameters(uz_PMSM_t input, enum uz_Setpoint_motor_type motor_type);
static float uz_SetPoint_newton_MTPA_raphson_iq_approximation(uz_SetPoint_t* self, float i_ref_Ampere, float M_ref_Nm);
static float uz_SetPoint_newton_FW_raphson_iq_approximation(uz_SetPoint_t* self, float i_ref_Ampere, float M_ref_Nm, float V_SV_max, float omega_el_rad_per_sec);
static float uz_SetPoint_calculate_IPMSM_id_current(uz_SetPoint_t* self, float iq_ref_Ampere);

static uz_SetPoint_t* uz_SetPoint_allocation(void){
 uz_assert(instance_counter < UZ_SETPOINT_MAX_INSTANCES);
 uz_SetPoint_t* self = &instances[instance_counter];
 uz_assert_false(self->is_ready);
 instance_counter++;
 self->is_ready = true;
 return (self);
}

uz_SetPoint_t* uz_SetPoint_init(struct uz_SetPoint_config config){
    uz_SetPoint_t* self = uz_SetPoint_allocation();
    uz_SetPoint_assert_motor_parameters(config.config_PMSM, config.motor_type);
	self->newton_MTPA.derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients_MTPA);
	self->newton_MTPA.derivate_poly_coefficients.data = &derivate_poly_coefficients_MTPA[0];
	self->newton_MTPA.coefficients.length = UZ_ARRAY_SIZE(coefficients_MTPA);
	self->newton_MTPA.coefficients.data = &coefficients_MTPA[0];
	self->newton_MTPA.initial_value = 0.0f;
	self->newton_MTPA.iterations = 12U;
	self->newton_FW.derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients_FW);
	self->newton_FW.derivate_poly_coefficients.data = &derivate_poly_coefficients_FW[0];
	self->newton_FW.coefficients.length = UZ_ARRAY_SIZE(coefficients_FW);
	self->newton_FW.coefficients.data = &coefficients_FW[0];
	self->newton_FW.initial_value = 0.0f;
	self->newton_FW.iterations = 12U;
    self->config = config;
    return(self);
}

uz_3ph_dq_t uz_SetPoint_sample(uz_SetPoint_t* self, float omega_m_rad_per_sec, float M_ref_Nm, float V_DC_Volts, uz_3ph_dq_t actual_currents_Ampere) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(V_DC_Volts > 0.0f);
    uz_3ph_dq_t output_currents = {0};
    switch (self->config.control_type)
    {
    case (FOC):
        output_currents = uz_SetPoint_FOC_control(self, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, actual_currents_Ampere);
        break;
    
    default:
        uz_assert(0);
        break;
    }
    
    return(output_currents);
}

void uz_SetPoint_set_field_weakening(uz_SetPoint_t* self, bool is_field_weakening_enabled) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	self->config.is_field_weakening_enabled = is_field_weakening_enabled;
}

void uz_SetPoint_set_PMSM_config(uz_SetPoint_t* self, uz_PMSM_t input) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_SetPoint_assert_motor_parameters(input, self->config.motor_type);
    self->config.config_PMSM = input;
}

void uz_SetPoint_set_id_ref(uz_SetPoint_t* self, float id_ref_Ampere) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.id_ref_Ampere = id_ref_Ampere;
}

static uz_3ph_dq_t uz_SetPoint_FOC_control(uz_SetPoint_t* self, float omega_m_rad_per_sec, float M_ref_Nm, float V_DC_Volts, uz_3ph_dq_t actual_currents_Ampere) {
    uz_3ph_dq_t output_currents = {0};
    float im_ref = M_ref_Nm / (1.5f * self->config.config_PMSM.polePairs * self->config.config_PMSM.Psi_PM_Vs);
    im_ref = uz_signals_saturation(im_ref, self->config.config_PMSM.I_max_Ampere, -self->config.config_PMSM.I_max_Ampere);

    if(self->config.is_field_weakening_enabled) {//Field-weakening
        float V_SV_max = ((V_DC_Volts / sqrtf(3.0f)) - (self->config.config_PMSM.R_ph_Ohm * self->config.config_PMSM.I_max_Ampere))*0.95f;
        uz_SetPoint_calculate_omega_cut_rad_per_sec(self, V_SV_max, actual_currents_Ampere);
        float omega_el_rad_per_sec = omega_m_rad_per_sec * self->config.config_PMSM.polePairs;
        if (fabsf(omega_el_rad_per_sec) > self->omega_cut_rad_per_sec) {
            self->is_field_weakening_active = true;
            output_currents = uz_SetPoint_field_weakening(self, omega_el_rad_per_sec, V_SV_max, im_ref, M_ref_Nm); 
        } else { //MPTA, if not in FW territory
            self->is_field_weakening_active = false;
            output_currents = uz_SetPoint_MTPA(self, im_ref, M_ref_Nm);
        }
    } else {//MPTA
        output_currents = uz_SetPoint_MTPA(self, im_ref, M_ref_Nm);
    }
    return(output_currents);
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

static uz_3ph_dq_t uz_SetPoint_field_weakening(uz_SetPoint_t* self, float omega_el_rad_per_sec, float V_SV_max, float im_ref, float M_ref_Nm){
    uz_assert(self->omega_cut_rad_per_sec > 0.0f);
    uz_3ph_dq_t output = {0};
    float I_max_squared = self->config.config_PMSM.I_max_Ampere * self->config.config_PMSM.I_max_Ampere;
    float id_limit = 0.0f;

    switch (self->config.motor_type)
	{
        case (SMPMSM):
            output.d = (self->config.config_PMSM.Psi_PM_Vs / self->config.config_PMSM.Ld_Henry) * ( (self->omega_cut_rad_per_sec / fabsf(omega_el_rad_per_sec) ) - 1.0f);
            id_limit = sqrtf(I_max_squared - output.d * output.d);
            output.q = uz_signals_saturation(im_ref, id_limit, -id_limit);//new max. ampere limit for q-axis current
            break;

        case (IPMSM):;
            output.q = uz_SetPoint_newton_FW_raphson_iq_approximation(self, im_ref, M_ref_Nm, V_SV_max, omega_el_rad_per_sec);
            float Lq_squared = self->config.config_PMSM.Lq_Henry * self->config.config_PMSM.Lq_Henry;
            float iq_fw_squared = output.q * output.q;
            float V_SV_squared = V_SV_max * V_SV_max;
            float omega_squared = omega_el_rad_per_sec * omega_el_rad_per_sec;
            float Psi_divided_Ld = self->config.config_PMSM.Psi_PM_Vs / self->config.config_PMSM.Ld_Henry;
            output.d = (-Psi_divided_Ld) + ((1.0f / self->config.config_PMSM.Ld_Henry) * sqrtf((V_SV_squared / omega_squared) - (Lq_squared * iq_fw_squared)));
            id_limit = sqrtf(I_max_squared - iq_fw_squared);
            output.d = uz_signals_saturation(output.d, 0.0f, -id_limit);//To prevent id being positive
            break;

        default:
            uz_assert(0);
            break;
    }
    return(output);
}

static uz_3ph_dq_t uz_SetPoint_MTPA(uz_SetPoint_t* self, float i_ref_Ampere, float M_ref_Nm){
    uz_3ph_dq_t output = {0};
    float I_max_squared = self->config.config_PMSM.I_max_Ampere * self->config.config_PMSM.I_max_Ampere;
    switch (self->config.motor_type)
	{
        case (SMPMSM):
            output.q = i_ref_Ampere;         
            output.d = 0.0f;
            break;

        case (IPMSM):
            output.q = uz_SetPoint_newton_MTPA_raphson_iq_approximation(self, i_ref_Ampere, M_ref_Nm);
            output.d = uz_SetPoint_calculate_IPMSM_id_current(self, output.q);
            break;

        default:
            uz_assert(0);
            break;
    }
    float id_limit = sqrtf((I_max_squared) - (output.q * output.q));
    output.d = uz_signals_saturation(output.d + self->config.id_ref_Ampere, id_limit, -id_limit);
    return(output);
}

static float uz_SetPoint_newton_FW_raphson_iq_approximation(uz_SetPoint_t* self, float i_ref_Ampere, float M_ref_Nm, float V_SV_max, float omega_el_rad_per_sec){
    //Calculate coefficients for polynomial
    float psi_pm_squared = self->config.config_PMSM.Psi_PM_Vs  * self->config.config_PMSM.Psi_PM_Vs;
    float Lq_squared = self->config.config_PMSM.Lq_Henry * self->config.config_PMSM.Lq_Henry;
    float Ld_minus_Lq = self->config.config_PMSM.Ld_Henry - self->config.config_PMSM.Lq_Henry;
    float Ld_minus_Lq_squared = Ld_minus_Lq * Ld_minus_Lq;
    float V_SV_squared = V_SV_max * V_SV_max;
    float omega_squared = omega_el_rad_per_sec * omega_el_rad_per_sec;
    float polepairs_squared = self->config.config_PMSM.polePairs * self->config.config_PMSM.polePairs;
    float M_ref_Ld = M_ref_Nm * self->config.config_PMSM.Ld_Henry;
    float M_ref_Ld_squared = M_ref_Ld * M_ref_Ld;
    self->newton_FW.coefficients.data[2] = ((psi_pm_squared * Lq_squared) - (Ld_minus_Lq_squared * (V_SV_squared / omega_squared))) / (Lq_squared * Ld_minus_Lq_squared);
    self->newton_FW.coefficients.data[1] = (-4.0f * M_ref_Ld * self->config.config_PMSM.Lq_Henry * self->config.config_PMSM.Psi_PM_Vs) / 
                                            (3.0f * Lq_squared * self->config.config_PMSM.polePairs * Ld_minus_Lq_squared);
    self->newton_FW.coefficients.data[0] = (4.0f * M_ref_Ld_squared) / (9.0f * Lq_squared * polepairs_squared * Ld_minus_Lq_squared);                           
    self->newton_FW.initial_value = i_ref_Ampere;
    float iq_ref_Ampere = uz_newton_raphson(self->newton_FW);
    iq_ref_Ampere = uz_signals_saturation(iq_ref_Ampere, self->config.config_PMSM.I_max_Ampere, -self->config.config_PMSM.I_max_Ampere);
    return(iq_ref_Ampere);

}

static float uz_SetPoint_newton_MTPA_raphson_iq_approximation(uz_SetPoint_t* self, float i_ref_Ampere, float M_ref_Nm){
    //Calculate coefficients for polynomial
    float Ld_Lq_squared = (self->config.config_PMSM.Ld_Henry - self->config.config_PMSM.Lq_Henry) * (self->config.config_PMSM.Ld_Henry - self->config.config_PMSM.Lq_Henry);
    float M_ref_squared = M_ref_Nm * M_ref_Nm;
    float polePairs_squared = self->config.config_PMSM.polePairs * self->config.config_PMSM.polePairs;
    self->newton_MTPA.coefficients.data[1] = (2.0f * M_ref_Nm * self->config.config_PMSM.Psi_PM_Vs) / (3.0f * Ld_Lq_squared * self->config.config_PMSM.polePairs);
    self->newton_MTPA.coefficients.data[0] = -(4.0f * M_ref_squared) / (9.0f * Ld_Lq_squared * polePairs_squared);
    self->newton_MTPA.initial_value = i_ref_Ampere;
    float iq_ref_Ampere = uz_newton_raphson(self->newton_MTPA);
    iq_ref_Ampere = uz_signals_saturation(iq_ref_Ampere, self->config.config_PMSM.I_max_Ampere, -self->config.config_PMSM.I_max_Ampere);
    return(iq_ref_Ampere);
}

static float uz_SetPoint_calculate_IPMSM_id_current(uz_SetPoint_t* self, float iq_ref_Ampere){
    float id_ref_Ampere = 0.0f;
    float psi_pm_squared = self->config.config_PMSM.Psi_PM_Vs * self->config.config_PMSM.Psi_PM_Vs;
    float Ld_minus_Lq = self->config.config_PMSM.Ld_Henry - self->config.config_PMSM.Lq_Henry;
    float Ld_minus_Lq_squared = Ld_minus_Lq * Ld_minus_Lq;
    float iq_ref_squared = iq_ref_Ampere * iq_ref_Ampere;
    if (self->config.config_PMSM.Ld_Henry < self->config.config_PMSM.Lq_Henry) {
        id_ref_Ampere = ((-self->config.config_PMSM.Psi_PM_Vs) / (2.0f * Ld_minus_Lq)) - sqrtf(((psi_pm_squared) / (4.0f * Ld_minus_Lq_squared)) + iq_ref_squared);
    } else {
        id_ref_Ampere = ((-self->config.config_PMSM.Psi_PM_Vs) / (2.0f * Ld_minus_Lq)) + sqrtf(((psi_pm_squared) / (4.0f * Ld_minus_Lq_squared)) + iq_ref_squared);
    }
    float id_limit = sqrtf((self->config.config_PMSM.I_max_Ampere * self->config.config_PMSM.I_max_Ampere) - (iq_ref_squared));
    id_ref_Ampere = uz_signals_saturation(id_ref_Ampere, id_limit, -id_limit);
    return(id_ref_Ampere);
}

static void uz_SetPoint_calculate_omega_cut_rad_per_sec(uz_SetPoint_t* self, float V_SV_max, uz_3ph_dq_t actual_currents_Ampere) {
    float I1 = sqrtf((actual_currents_Ampere.d * actual_currents_Ampere.d) + (actual_currents_Ampere.q * actual_currents_Ampere.q));
    float I_squared = I1 * I1;
    float Lq_squared = self->config.config_PMSM.Lq_Henry * self->config.config_PMSM.Lq_Henry;
    float psi_pm_squared = self->config.config_PMSM.Psi_PM_Vs * self->config.config_PMSM.Psi_PM_Vs;
    float R_ph_squared = self->config.config_PMSM.R_ph_Ohm * self->config.config_PMSM.R_ph_Ohm;
    float V_SV_max_squared = V_SV_max * V_SV_max;
    float a_omega = (I_squared * Lq_squared) + psi_pm_squared;
	float b_omega = 2.0f * self->config.config_PMSM.R_ph_Ohm * self->config.config_PMSM.Psi_PM_Vs * I1;
	float c_omega = (I_squared * R_ph_squared) - V_SV_max_squared;
    self->omega_cut_rad_per_sec = (-b_omega + sqrtf((b_omega * b_omega) - (4.0f * a_omega * c_omega) )) / (2.0f * a_omega);
}
#endif
