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

#include "uz_MotorControl.h"
#include "../uz_global_configuration.h"
#if UZ_MOTORCONTROL_MAX_INSTANCES > 0
typedef struct uz_MotorControl_t {
	bool is_ready;
	uz_CurrentControl_t* CurrentControl;
	uz_SpeedControl_t* SpeedControl;
	uz_SetPoint_t* SetPoint;
	uz_PWM_SS_2L_t* pwm_d1_pin_0_to_5;
	struct uz_MotorControl_config config;
	bool ext_clamping;
}uz_MotorControl_t;

static uint32_t instances_counter = 0;

static uz_MotorControl_t instances[UZ_MOTORCONTROL_MAX_INSTANCES] = {0};


/**
 * @brief Memory allocation of the uz_MotorControl_t struct
 *
 * @return Pointer to uz_MotorControl_t instance
 */
static uz_MotorControl_t* uz_MotorControl_allocation(void);

static uz_MotorControl_t* uz_MotorControl_allocation(void) {
	uz_assert(instances_counter < UZ_MOTORCONTROL_MAX_INSTANCES);
	uz_MotorControl_t* self = &instances[instances_counter];
	uz_assert(self->is_ready == false);
	instances_counter++;
	self->is_ready = true;
	return (self);
}

uz_MotorControl_t* uz_MotorControl_init(struct uz_MotorControl_config config, uz_PWM_SS_2L_t* pwm_d1_pin_0_to_5) {
	uz_MotorControl_t* self = uz_MotorControl_allocation();
	//Ensure, that the SetPoint module is enabled, if SpeedControl is enabled
	if(config.is_SpeedControl_selected) {
		uz_assert(config.is_SetPoint_selected);
	}
	self->config.CC_config.config_PMSM = config.config_PMSM;
	self->CurrentControl = uz_CurrentControl_init(config.CC_config);
	self->SpeedControl = uz_SpeedControl_init(config.SC_config);
	self->config.SP_config.config_PMSM = config.config_PMSM;
	self->SetPoint = uz_SetPoint_init(config.SP_config);
	self->pwm_d1_pin_0_to_5 = pwm_d1_pin_0_to_5;
	self->config = config;
	return (self);
}

void uz_MotorControl_sample(uz_MotorControl_t* self, uz_3ph_dq_t i_meas_Ampere, float V_DC_Volts, float omega_m_rad_per_sec, float theta_el_rad) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(V_DC_Volts > 0.0f);
	uz_3ph_dq_t v_ref_Volts = {0};
	uz_3ph_dq_t i_ref_Ampere = {0};
	float M_ref_Nm = 0.0f;
	struct uz_DutyCycle_t DutyCycle = {0};

	if(self->config.is_SpeedControl_selected) {
		//SpeedControl is used
		uz_SpeedControl_set_ext_clamping(self->SpeedControl, self->ext_clamping);
		M_ref_Nm =  uz_SpeedControl_sample(self->SpeedControl, omega_m_rad_per_sec, self->config.n_ref_rpm);
		i_ref_Ampere = uz_SetPoint_sample(self->SetPoint, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, i_meas_Ampere);
		v_ref_Volts = uz_CurrentControl_sample(self->CurrentControl, i_ref_Ampere, i_meas_Ampere, V_DC_Volts, omega_m_rad_per_sec);
	} else if((self->config.is_SetPoint_selected) && (!self->config.is_SpeedControl_selected)){
		//Manual reference torque is used
		i_ref_Ampere = uz_SetPoint_sample(self->SetPoint, omega_m_rad_per_sec, self->config.M_ref_Nm, V_DC_Volts, i_meas_Ampere);
		v_ref_Volts = uz_CurrentControl_sample(self->CurrentControl, i_ref_Ampere, i_meas_Ampere, V_DC_Volts, omega_m_rad_per_sec);
	} else {
		//Only CurrentControl with manual reference currents is used
		v_ref_Volts = uz_CurrentControl_sample(self->CurrentControl, self->config.i_ref_Ampere, i_meas_Ampere, V_DC_Volts, omega_m_rad_per_sec);
	}
	self->ext_clamping = (self->CurrentControl);
	DutyCycle = uz_Space_Vector_Modulation(v_ref_Volts, V_DC_Volts, theta_el_rad);
	uz_PWM_SS_2L_set_duty_cycle(self->pwm_d1_pin_0_to_5, DutyCycle.DutyCycle_A, DutyCycle.DutyCycle_B, DutyCycle.DutyCycle_C);
}

void uz_MotorControl_reset(uz_MotorControl_t* self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_SpeedControl_reset(self->SpeedControl);
	uz_CurrentControl_reset(self->CurrentControl);
	self->ext_clamping = false;
}

void uz_MotorControl_set_CurrentControl_Kp_Ki(uz_MotorControl_t* self, float Kp_id, float Ki_id, float Kp_iq, float Ki_iq) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_CurrentControl_set_Ki_id(self->CurrentControl, Ki_id);	
	uz_CurrentControl_set_Kp_id(self->CurrentControl, Kp_id);	
	uz_CurrentControl_set_Ki_iq(self->CurrentControl, Ki_iq);	
	uz_CurrentControl_set_Kp_iq(self->CurrentControl, Kp_iq);	
}

void uz_MotorControl_set_SpeedControl_Kp_Ki(uz_MotorControl_t* self, float Kp_n, float Ki_n) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_SpeedControl_set_Ki(self->SpeedControl, Ki_n);
	uz_SpeedControl_set_Kp(self->SpeedControl, Kp_n);	
}

void uz_MotorControl_set_reference_speed(uz_MotorControl_t* self, float n_ref_rpm) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.n_ref_rpm = n_ref_rpm;
}

void uz_MotorControl_set_reference_torque(uz_MotorControl_t* self, float M_ref_Nm) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.M_ref_Nm = M_ref_Nm;
}

void uz_MotorControl_set_reference_currents(uz_MotorControl_t* self, uz_3ph_dq_t i_ref_Ampere) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->config.i_ref_Ampere = i_ref_Ampere;
}

void uz_MotorControl_set_PMSM_parameters(uz_MotorControl_t* self, uz_PMSM_t input) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_SetPoint_set_PMSM_parameters(self->SetPoint, input);
	uz_CurrentControl_set_PMSM_parameters(self->CurrentControl, input);
}

void uz_MotorControl_set_field_weakening(uz_MotorControl_t* self, bool is_field_weakening_enabled) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
	self->config.SP_config.is_field_weakening_enabled = is_field_weakening_enabled;
}

void uz_MotorControl_set_id_ref(uz_MotorControl_t* self, float id_ref_Ampere) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.SP_config.id_ref_Ampere = id_ref_Ampere;
}

void uz_MotorControl_set_decoupling_method(uz_MotorControl_t* self, enum uz_CurrentControl_decoupling_select decoupling_select) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	//Assert again, since the module could've been init with 0 values
	if(decoupling_select == linear_decoupling) {
		uz_assert(self->config.CC_config.config_PMSM.Ld_Henry > 0.0f);
		uz_assert(self->config.CC_config.config_PMSM.Lq_Henry > 0.0f);
		uz_assert(self->config.CC_config.config_PMSM.Psi_PM_Vs >= 0.0f);
	}
	self->config.CC_config.decoupling_select=decoupling_select;
}

void uz_MotorControl_set_SpeedControl(uz_MotorControl_t* self, bool is_SpeedControl_enabled) {
		uz_assert_not_NULL(self);
		uz_assert(self->is_ready);
		if(is_SpeedControl_enabled) {
			self->config.is_SpeedControl_selected = true;
			self->config.is_SetPoint_selected = true;
		} else {
			self->config.is_SpeedControl_selected = false;
		}
		
}

void uz_MotorControl_set_SetPoint(uz_MotorControl_t* self, bool is_SetPoint_enabled) {
		uz_assert_not_NULL(self);
		uz_assert(self->is_ready);
		if(is_SetPoint_enabled) {
			self->config.is_SetPoint_selected = true;
		} else {
			self->config.is_SpeedControl_selected = false;
			self->config.is_SetPoint_selected = false;
		}
}

#endif
