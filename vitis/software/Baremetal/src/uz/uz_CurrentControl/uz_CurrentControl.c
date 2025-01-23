/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2022 Dennis Hufnagel
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

#include "uz_CurrentControl.h"
#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_signals/uz_signals.h"
#include "uz_linear_decoupling.h"
#include "uz_static_nonlinear_decoupling.h"
#include "uz_space_vector_limitation.h"
#include <math.h>

#if UZ_CURRENTCONTROL_MAX_INSTANCES > 0
#include <math.h>
#include "../uz_HAL.h"
#include "uz_linear_decoupling.h"
#include "uz_static_nonlinear_decoupling.h"
#include "uz_space_vector_limitation.h"

typedef struct uz_CurrentControl_t {
	bool is_ready;
	bool ext_clamping;
	struct uz_CurrentControl_config config;
	struct uz_PI_Controller* Controller_id;
	struct uz_PI_Controller* Controller_iq;
	uz_3ph_dq_t flux_approx_real;
	uz_3ph_dq_t flux_approx_reference;
	uz_3ph_dq_t kp_adjustment_parameter;
}uz_CurrentControl_t;

static uz_3ph_dq_t uz_CurrentControl_sample_pi_controllers(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere);
static uz_3ph_dq_t uz_CurrentControl_decoupling(uz_CurrentControl_t* self, uz_3ph_dq_t actual_Ampere, float omega_el_rad_per_sec);
static uint32_t instances_counter_CurrentControl = 0;

static uz_CurrentControl_t instances_CurrentControl[UZ_CURRENTCONTROL_MAX_INSTANCES] = {0};


/**
 * @brief Memory allocation of the uz_CurrentControl_t struct
 *
 * @return Pointer to uz_CurrentControl_t instance
 */
static uz_CurrentControl_t* uz_CurrentControl_allocation(void);

static uz_CurrentControl_t* uz_CurrentControl_allocation(void) {
	uz_assert(instances_counter_CurrentControl < UZ_CURRENTCONTROL_MAX_INSTANCES);
	uz_CurrentControl_t* self = &instances_CurrentControl[instances_counter_CurrentControl];
	uz_assert(self->is_ready == false);
	instances_counter_CurrentControl++;
	self->is_ready = true;
	return (self);
}

uz_CurrentControl_t* uz_CurrentControl_init(struct uz_CurrentControl_config config) {
	uz_CurrentControl_t* self = uz_CurrentControl_allocation();
	//Disables the built in limitation of the PI-Controllers, since the limitation is done by the space-vector-limitation module
	config.config_id.upper_limit = INFINITY;
	config.config_id.lower_limit = -INFINITY;
	config.config_iq.upper_limit = INFINITY;
	config.config_iq.lower_limit = -INFINITY;
	uz_assert(config.max_modulation_index > 0.0f);
	self->Controller_id = uz_PI_Controller_init(config.config_id);
	self->Controller_iq = uz_PI_Controller_init(config.config_iq);
	self->config = config;
	return (self);
}

uz_3ph_dq_t uz_CurrentControl_sample(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(V_dc_volts > 0.0f);
	uz_3ph_dq_t v_pre_limit_Volts = uz_CurrentControl_sample_pi_controllers(self, i_reference_Ampere, i_actual_Ampere);
	uz_3ph_dq_t v_decoup_Volts = uz_CurrentControl_decoupling(self, i_actual_Ampere, omega_el_rad_per_sec);
	v_pre_limit_Volts.d += v_decoup_Volts.d;
	v_pre_limit_Volts.q += v_decoup_Volts.q;
	uz_3ph_dq_t v_output_Volts = uz_CurrentControl_SpaceVector_Limitation(v_pre_limit_Volts, V_dc_volts, self->config.max_modulation_index, omega_el_rad_per_sec, i_reference_Ampere, &self->ext_clamping);
	return (v_output_Volts);
}

uz_3ph_abc_t uz_CurrentControl_sample_abc(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_3ph_dq_t v_dq_Volts = uz_CurrentControl_sample(self, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
	uz_3ph_abc_t v_output_Volts = uz_transformation_3ph_dq_to_abc(v_dq_Volts, theta_el_rad);
	return(v_output_Volts);
}

static uz_3ph_dq_t uz_CurrentControl_sample_pi_controllers(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_3ph_dq_t v_output_Volts = { 0 };
	v_output_Volts.q = uz_PI_Controller_sample(self->Controller_iq, i_reference_Ampere.q, i_actual_Ampere.q, self->ext_clamping);
	v_output_Volts.d = uz_PI_Controller_sample(self->Controller_id, i_reference_Ampere.d, i_actual_Ampere.d, self->ext_clamping);
	return (v_output_Volts);

}

void uz_CurrentControl_reset(uz_CurrentControl_t* self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_PI_Controller_reset(self->Controller_id);
	uz_PI_Controller_reset(self->Controller_iq);
	self->ext_clamping = false;
}

void uz_CurrentControl_set_flux_approx(uz_CurrentControl_t* self, uz_3ph_dq_t flux_approx_real, uz_3ph_dq_t flux_approx_reference){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->flux_approx_real = flux_approx_real;
	self->flux_approx_reference = flux_approx_reference;
}

void uz_CurrentControl_adjust_Kp(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere,  uz_3ph_dq_t i_actual_Ampere, float BO_factor){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_3ph_dq_t kp_adjusted = {0};
	uz_3ph_dq_t current_error = {0};
	current_error.d = i_reference_Ampere.d - i_actual_Ampere.d;
	  if (current_error.d == 0.0f) {
    	current_error.d = 1.1920929E-7f;
  		}
	current_error.q = i_reference_Ampere.q - i_actual_Ampere.q ;
	  if (current_error.q == 0.0f) {
    	current_error.q = 1.1920929E-7f;
  		}
	kp_adjusted.d = ((self->flux_approx_reference.d - self->flux_approx_real.d)/current_error.d) / (BO_factor * self->config.config_id.samplingTime_sec * 2.0f);
	kp_adjusted.q = ((self->flux_approx_reference.q - self->flux_approx_real.q)/current_error.q) / (BO_factor * self->config.config_iq.samplingTime_sec * 2.0f);
	if(self->config.Kp_adjustment_flag) {
		uz_CurrentControl_set_Kp_id(self, kp_adjusted.d);
		uz_CurrentControl_set_Kp_iq(self, kp_adjusted.q);
	}
}

void uz_CurrentControl_set_Kp_id(uz_CurrentControl_t* self, float Kp_id){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(Kp_id >= 0.0f);
	self->config.config_id.Kp = Kp_id;
	uz_PI_Controller_set_Kp(self->Controller_id, Kp_id);
}

void uz_CurrentControl_set_Ki_id(uz_CurrentControl_t* self, float Ki_id){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(Ki_id >= 0.0f);
	self->config.config_id.Ki = Ki_id;
	uz_PI_Controller_set_Ki(self->Controller_id, Ki_id);
}

void uz_CurrentControl_set_Kp_iq(uz_CurrentControl_t* self, float Kp_iq){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(Kp_iq >= 0.0f);
	self->config.config_iq.Kp = Kp_iq;
	uz_PI_Controller_set_Kp(self->Controller_iq, Kp_iq);
}

void uz_CurrentControl_set_Ki_iq(uz_CurrentControl_t* self, float Ki_iq){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(Ki_iq >= 0.0f);
	self->config.config_iq.Ki = Ki_iq;
	uz_PI_Controller_set_Ki(self->Controller_iq, Ki_iq);
}

float uz_CurrentControl_get_Kp_id(uz_CurrentControl_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->config.config_id.Kp);
}

float uz_CurrentControl_get_Kp_iq(uz_CurrentControl_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->config.config_iq.Kp);
}

void uz_CurrentControl_set_max_modulation_index(uz_CurrentControl_t* self, float max_modulation_index) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(max_modulation_index > 0.0f);
	self->config.max_modulation_index = max_modulation_index;
}
void uz_CurrentControl_set_PMSM_parameters(uz_CurrentControl_t* self, uz_PMSM_t pmsm_config) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	//Only assert relevant parts of the PMSM-struct
    uz_assert(pmsm_config.Ld_Henry > 0.0f);
	uz_assert(pmsm_config.Lq_Henry > 0.0f);
	uz_assert(pmsm_config.Psi_PM_Vs >= 0.0f);
	self->config.config_PMSM = pmsm_config;
}

void uz_CurrentControl_set_decoupling_method(uz_CurrentControl_t* self, enum uz_CurrentControl_decoupling_select decoupling_select) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.decoupling_select=decoupling_select;
}

bool uz_CurrentControl_get_ext_clamping(uz_CurrentControl_t* self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	return(self->ext_clamping);
}

static uz_3ph_dq_t uz_CurrentControl_decoupling(uz_CurrentControl_t* self, uz_3ph_dq_t i_actual_Ampere, float omega_el_rad_per_sec){
	uz_3ph_dq_t decouple_voltage={0};
	switch (self->config.decoupling_select)
    {
    case no_decoupling:
        // do nothing since no decoupling
        break;
    case linear_decoupling:
        decouple_voltage=uz_CurrentControl_linear_decoupling(self->config.config_PMSM, i_actual_Ampere, omega_el_rad_per_sec);
        break;
	case static_nonlinear_decoupling:
     	decouple_voltage = uz_CurrentControl_static_nonlinear_decoupling(self->flux_approx_real, omega_el_rad_per_sec);
     	break;
    default:
        break;
    }
	return (decouple_voltage);
}

void uz_CurrentControl_tune_magnitude_optimum(uz_CurrentControl_t* self, float tau_sigma_sec)
{
	uz_assert_not_NULL(self);
	uz_assert(tau_sigma_sec > 0.0f);
	uz_assert(self->config.config_PMSM.R_ph_Ohm > 0.0f);
	uz_assert(self->config.config_PMSM.Ld_Henry > 0.0f);
	uz_assert(self->config.config_PMSM.Lq_Henry > 0.0f);
	float Kp_id = self->config.config_PMSM.Ld_Henry / (2.0f * tau_sigma_sec);
	float Ki_id = self->config.config_PMSM.R_ph_Ohm / (2.0f * tau_sigma_sec);
	float Kp_iq = self->config.config_PMSM.Lq_Henry / (2.0f * tau_sigma_sec);
	float Ki_iq = self->config.config_PMSM.R_ph_Ohm / (2.0f * tau_sigma_sec);
	uz_CurrentControl_set_Kp_id(self, Kp_id);
	uz_CurrentControl_set_Kp_iq(self, Kp_iq);
	uz_CurrentControl_set_Ki_id(self, Ki_id);
	uz_CurrentControl_set_Ki_iq(self, Ki_iq);
}

void uz_CurrentControl_tune_symmetric_optimum(uz_CurrentControl_t* self, float tau_sigma_sec)
{
	uz_assert_not_NULL(self);
	uz_assert(tau_sigma_sec > 0.0f);
	uz_assert(self->config.config_PMSM.R_ph_Ohm > 0.0f);
	uz_assert(self->config.config_PMSM.Ld_Henry > 0.0f);
	uz_assert(self->config.config_PMSM.Lq_Henry > 0.0f);
	float Kp_id = self->config.config_PMSM.Ld_Henry / (2.0f * tau_sigma_sec);
	float Ki_id = self->config.config_PMSM.Ld_Henry / (8.0f * tau_sigma_sec * tau_sigma_sec);
	float Kp_iq = self->config.config_PMSM.Lq_Henry / (2.0f * tau_sigma_sec);
	float Ki_iq = self->config.config_PMSM.Lq_Henry / (8.0f * tau_sigma_sec * tau_sigma_sec);
	uz_CurrentControl_set_Kp_id(self, Kp_id);
	uz_CurrentControl_set_Kp_iq(self, Kp_iq);
	uz_CurrentControl_set_Ki_id(self, Ki_id);
	uz_CurrentControl_set_Ki_iq(self, Ki_iq);
}

void uz_CurrentControl_tune_bandwidth(uz_CurrentControl_t* self, float bandwidth_rad_per_sec)
{
	uz_assert_not_NULL(self);
	uz_assert(bandwidth_rad_per_sec > 0.0f);
	uz_assert(self->config.config_PMSM.R_ph_Ohm > 0.0f);
	uz_assert(self->config.config_PMSM.Ld_Henry > 0.0f);
	uz_assert(self->config.config_PMSM.Lq_Henry > 0.0f);
	float Kp_id = self->config.config_PMSM.Ld_Henry * bandwidth_rad_per_sec;
	float Ki_id = self->config.config_PMSM.R_ph_Ohm * bandwidth_rad_per_sec;
	float Kp_iq = self->config.config_PMSM.Lq_Henry * bandwidth_rad_per_sec;
	float Ki_iq = self->config.config_PMSM.R_ph_Ohm * bandwidth_rad_per_sec;
	uz_CurrentControl_set_Kp_id(self, Kp_id);
	uz_CurrentControl_set_Kp_iq(self, Kp_iq);
	uz_CurrentControl_set_Ki_id(self, Ki_id);
	uz_CurrentControl_set_Ki_iq(self, Ki_iq);
}

void uz_CurrentControl_tune_magnitude_optimum(uz_CurrentControl_t* self, float tau_sigma_sec)
{
	uz_assert_not_NULL(self);
	uz_assert(tau_sigma_sec > 0.0f);
	uz_assert(self->config.config_PMSM.R_ph_Ohm > 0.0f);
	uz_assert(self->config.config_PMSM.Ld_Henry > 0.0f);
	uz_assert(self->config.config_PMSM.Lq_Henry > 0.0f);
	float Kp_id = self->config.config_PMSM.Ld_Henry / (2.0f * tau_sigma_sec);
	float Ki_id = self->config.config_PMSM.R_ph_Ohm / (2.0f * tau_sigma_sec);
	float Kp_iq = self->config.config_PMSM.Lq_Henry / (2.0f * tau_sigma_sec);
	float Ki_iq = self->config.config_PMSM.R_ph_Ohm / (2.0f * tau_sigma_sec);
	uz_CurrentControl_set_Kp_id(self, Kp_id);
	uz_CurrentControl_set_Kp_iq(self, Kp_iq);
	uz_CurrentControl_set_Ki_id(self, Ki_id);
	uz_CurrentControl_set_Ki_iq(self, Ki_iq);
}

void uz_CurrentControl_tune_symmetric_optimum(uz_CurrentControl_t* self, float tau_sigma_sec)
{
	uz_assert_not_NULL(self);
	uz_assert(tau_sigma_sec > 0.0f);
	uz_assert(self->config.config_PMSM.R_ph_Ohm > 0.0f);
	uz_assert(self->config.config_PMSM.Ld_Henry > 0.0f);
	uz_assert(self->config.config_PMSM.Lq_Henry > 0.0f);
	float Kp_id = self->config.config_PMSM.Ld_Henry / (2.0f * tau_sigma_sec);
	float Ki_id = self->config.config_PMSM.Ld_Henry / (8.0f * tau_sigma_sec * tau_sigma_sec);
	float Kp_iq = self->config.config_PMSM.Lq_Henry / (2.0f * tau_sigma_sec);
	float Ki_iq = self->config.config_PMSM.Lq_Henry / (8.0f * tau_sigma_sec * tau_sigma_sec);
	uz_CurrentControl_set_Kp_id(self, Kp_id);
	uz_CurrentControl_set_Kp_iq(self, Kp_iq);
	uz_CurrentControl_set_Ki_id(self, Ki_id);
	uz_CurrentControl_set_Ki_iq(self, Ki_iq);
}

void uz_CurrentControl_tune_bandwidth(uz_CurrentControl_t* self, float bandwidth_rad_per_sec)
{
	uz_assert_not_NULL(self);
	uz_assert(bandwidth_rad_per_sec > 0.0f);
	uz_assert(self->config.config_PMSM.R_ph_Ohm > 0.0f);
	uz_assert(self->config.config_PMSM.Ld_Henry > 0.0f);
	uz_assert(self->config.config_PMSM.Lq_Henry > 0.0f);
	float Kp_id = self->config.config_PMSM.Ld_Henry * bandwidth_rad_per_sec;
	float Ki_id = self->config.config_PMSM.R_ph_Ohm * bandwidth_rad_per_sec;
	float Kp_iq = self->config.config_PMSM.Lq_Henry * bandwidth_rad_per_sec;
	float Ki_iq = self->config.config_PMSM.R_ph_Ohm * bandwidth_rad_per_sec;
	uz_CurrentControl_set_Kp_id(self, Kp_id);
	uz_CurrentControl_set_Kp_iq(self, Kp_iq);
	uz_CurrentControl_set_Ki_id(self, Ki_id);
	uz_CurrentControl_set_Ki_iq(self, Ki_iq);
}

void uz_CurrentControl_set_Kp_adjustment_flag(uz_CurrentControl_t *self, bool flag)
{
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.Kp_adjustment_flag = flag;
}
#endif
