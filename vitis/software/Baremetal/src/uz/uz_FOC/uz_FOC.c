#include "uz_FOC.h"
#include "../uz_global_configuration.h"

struct uz_FOC_PI_Controller_variables {
	bool is_ready;
	float I_sum;
	float P_sum;
	bool int_clamping;
	float error;
	float Kp;
	float Ki;
	float referenceValue;
	float actualValue;
};

static size_t instances_counter_FOC_ActualValues = 0;
static size_t instances_counter_FOC_PI_Controller_variables = 0;
static size_t instances_counter_FOC_VoltageReference = 0;

static uz_FOC_ActualValues instances_FOC_ActualValues[UZ_FOC_ACTUALVALUES_MAX_INSTANCES] = { 0 };
static uz_FOC_VoltageReference instances_FOC_VoltageReference[UZ_FOC_VOLTAGEREFERENCE_MAX_INSTANCES] = { 0 };
static uz_FOC_PI_Controller_variables instances_FOC_PI_Controller_variables[UZ_FOC_PI_CONTROLLER_VARIABLES_MAX_INSTANCES] = { 0 };

static uz_FOC_ActualValues* uz_FOC_ActualValues_allocation(void) {
	uz_assert(instances_counter_FOC_ActualValues < UZ_FOC_ACTUALVALUES_MAX_INSTANCES);
	uz_FOC_ActualValues* self = &instances_FOC_ActualValues[instances_counter_FOC_ActualValues];
	uz_assert(self->is_ready == false);
	instances_counter_FOC_ActualValues++;
	self->is_ready = true;
	return (self);
}

static uz_FOC_VoltageReference* uz_FOC_VoltageReference_allocation(void) {
	uz_assert(instances_counter_FOC_VoltageReference < UZ_FOC_VOLTAGEREFERENCE_MAX_INSTANCES);
	uz_FOC_VoltageReference* self = &instances_FOC_VoltageReference[instances_counter_FOC_VoltageReference];
	uz_assert(self->is_ready == false);
	instances_counter_FOC_VoltageReference++;
	self->is_ready = true;
	return (self);
}

static uz_FOC_PI_Controller_variables* uz_FOC_PI_Controller_variables_allocation(void) {
	uz_assert(instances_counter_FOC_PI_Controller_variables < UZ_FOC_PI_CONTROLLER_VARIABLES_MAX_INSTANCES);
	uz_FOC_PI_Controller_variables* self = &instances_FOC_PI_Controller_variables[instances_counter_FOC_PI_Controller_variables];
	uz_assert(self->is_ready == false);
	instances_counter_FOC_PI_Controller_variables++;
	self->is_ready = true;
	return (self);
}

uz_FOC_ActualValues* uz_FOC_ActualValues_init(void) {
	uz_FOC_ActualValues* self = uz_FOC_ActualValues_allocation();
	return (self);
}

uz_FOC_VoltageReference* uz_FOC_VoltageReference_init(void) {
	uz_FOC_VoltageReference* self = uz_FOC_VoltageReference_allocation();
	return (self);
}

uz_FOC_PI_Controller_variables* uz_FOC_PI_ID_Controller_variables_init(uz_FOC_config config, uz_FOC_ActualValues* values) {
	uz_FOC_PI_Controller_variables* self = uz_FOC_PI_Controller_variables_allocation();
	self->referenceValue = config.id_ref_Ampere;
	self->actualValue = values->i_d_Ampere;
	self->Kp = config.Kp_id;
	self->Ki = config.Ki_id;
	return (self);
}

uz_FOC_PI_Controller_variables* uz_FOC_PI_IQ_Controller_variables_init(uz_FOC_config config, uz_FOC_ActualValues* values) {
	uz_FOC_PI_Controller_variables* self = uz_FOC_PI_Controller_variables_allocation();
	self->referenceValue = config.iq_ref_Ampere;
	self->actualValue = values->i_q_Ampere;
	self->Kp = config.Kp_iq;
	self->Ki = config.Ki_iq;
	return (self);
}

uz_FOC_PI_Controller_variables* uz_FOC_PI_N_Controller_variables_init(uz_FOC_config config, uz_FOC_ActualValues* values) {
	uz_FOC_PI_Controller_variables* self = uz_FOC_PI_Controller_variables_allocation();
	self->referenceValue = config.n_ref_rpm / 60.0f * (2.0f * M_PI * config.polePairs);
	self->actualValue = values->omega_el_rad_per_sec;
	self->Kp = config.Kp_n;
	self->Ki = config.Ki_n;
	return (self);
}

uz_FOC_PI_Controller_variables* uz_FOC_update_PI_ID_Controller_variables(uz_FOC_PI_Controller_variables* self, uz_FOC_config config, uz_FOC_ActualValues* values){
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(values);
	self->referenceValue = config.id_ref_Ampere;
	self->actualValue = values->i_d_Ampere;
	self->Kp = config.Kp_id;
	self->Ki = config.Ki_id;
	return(self);
}

uz_FOC_PI_Controller_variables* uz_FOC_update_PI_IQ_Controller_variables(uz_FOC_PI_Controller_variables* self, uz_FOC_config config, uz_FOC_ActualValues* values){
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(values);
	self->referenceValue = config.iq_ref_Ampere;
	self->actualValue = values->i_q_Ampere;
	self->Kp = config.Kp_iq;
	self->Ki = config.Ki_iq;
	return(self);
}

uz_FOC_PI_Controller_variables* uz_FOC_update_PI_N_Controller_variables(uz_FOC_PI_Controller_variables* self, uz_FOC_config config, uz_FOC_ActualValues* values){
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(values);
	self->referenceValue = config.n_ref_rpm / 60.0f * (2.0f * M_PI * config.polePairs);
	self->actualValue = values->omega_el_rad_per_sec;
	self->Kp = config.Kp_n;
	self->Ki = config.Ki_n;
	return(self);
}

float uz_FOC_Dead_Zone(float input, uz_FOC_config config) {
	float output;
	uz_assert(config.d_y_max>config.d_y_min);
	if (input >= config.d_y_min && input <= config.d_y_max) {
		output = 0.0f;
	}
	else if (input > config.d_y_max)
	{
		output = input - config.d_y_max;
	}
        else {
		output = input - config.d_y_min;
	}
	return (output);
}

int uz_FOC_get_sign_of_value(float input) {
	int sign;
	if (input < 0)
		sign = -1;
	else if (input > 0) {
		sign = 1;
	} else {
		sign = 0;
	}
	return (sign);
}

bool uz_FOC_Clamping_Circuit(float preIntegrator, float preSat, uz_FOC_config config) {
	bool output = false;
	float value_after_deadzone = uz_FOC_Dead_Zone(preSat, config);
	int sign_after_deadzone = uz_FOC_get_sign_of_value(value_after_deadzone);
	int sign_preIntegrator = uz_FOC_get_sign_of_value(preIntegrator);
	if (0 != value_after_deadzone && sign_after_deadzone == sign_preIntegrator) {
		output = true;
	} else {
		output = false;
	}
	return (output);
}

float uz_FOC_PI_Controller(uz_FOC_PI_Controller_variables* variables, uz_FOC_config config, bool ext_clamping){
	uz_assert_not_NULL(variables);
	float preSat = 0.0f;
	float output = 0.0f;
	if (ext_clamping == true || variables->int_clamping == true) {
		variables->I_sum += 0.0f;
	} else {
		variables->I_sum += variables->error * variables->Ki * config.SamplingTime_sec;
	}
	variables->error = variables->referenceValue - variables->actualValue;
	variables->P_sum = variables->error * variables->Kp;
	if (config.Reset == true) {
		variables->I_sum = 0.0f;
		variables->P_sum = 0.0f;
		variables->error = 0.0f;
	}
	preSat = variables->I_sum + variables->P_sum;
	variables->int_clamping = uz_FOC_Clamping_Circuit(variables->I_sum,preSat,config);
	output = preSat;
	return(output);
}

void uz_FOC_linear_decouppling(uz_FOC_ActualValues* values, uz_FOC_config config, float* u_d_vor, float* u_q_vor){
	uz_assert_not_NULL(values);
	uz_assert_not_NULL(u_q_vor);
	uz_assert_not_NULL(u_d_vor);
	uz_assert(config.L_q>0.0f);
	uz_assert(config.L_d>0.0f);
	uz_assert(config.psi_pm>=0.0f);
	*u_d_vor = values->i_q_Ampere * -1.0f * config.L_q * values->omega_el_rad_per_sec;
	*u_q_vor = (values->i_d_Ampere * config.L_d + config.psi_pm) * values->omega_el_rad_per_sec;
}

bool uz_FOC_SpaceVector_Limitation(uz_FOC_VoltageReference* reference, uz_FOC_ActualValues* values){
	uz_assert_not_NULL(reference);
	uz_assert_not_NULL(values);
	uz_assert(values->U_zk_Volts > 0.0f);
	bool limit_on = false;
	float U_d_limit=0.0f;
	float U_q_limit=0.0f;

   	float U_RZ_max =values->U_zk_Volts / sqrtf(3.0f);
	float U_RZ_betrag = sqrtf(reference->u_d_ref_Volts * reference->u_d_ref_Volts + reference->u_q_ref_Volts * reference->u_q_ref_Volts);

	if ( U_RZ_betrag > U_RZ_max ){
		limit_on = true; 
		if ((uz_FOC_get_sign_of_value(values->omega_el_rad_per_sec) == uz_FOC_get_sign_of_value(values->i_q_Ampere))) {
			if ((abs(reference->u_d_ref_Volts) > 0.95f * U_RZ_max)) {
				U_d_limit = uz_FOC_get_sign_of_value(reference->u_d_ref_Volts) * 0.95f * U_RZ_max;
				U_q_limit = uz_FOC_get_sign_of_value(reference->u_q_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_d_limit * U_d_limit);
			} else {
				U_d_limit = reference->u_d_ref_Volts;
				U_q_limit = uz_FOC_get_sign_of_value(reference->u_q_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_d_limit * U_d_limit);
			}


	       } else if ((uz_FOC_get_sign_of_value(values->omega_el_rad_per_sec) != uz_FOC_get_sign_of_value(values->i_q_Ampere))) {
			if (abs(reference->u_q_ref_Volts) > 0.95f * U_RZ_max) {
				U_q_limit = uz_FOC_get_sign_of_value(reference->u_q_ref_Volts) * 0.95f * U_RZ_max;
				U_d_limit = uz_FOC_get_sign_of_value(reference->u_d_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_q_limit * U_q_limit);
			} else {
				U_q_limit = reference->u_q_ref_Volts;
				U_d_limit = uz_FOC_get_sign_of_value(reference->u_d_ref_Volts) * sqrtf(U_RZ_max * U_RZ_max - U_q_limit * U_q_limit);
			}
		} else {
			U_d_limit = reference->u_d_ref_Volts;
			U_q_limit = reference->u_q_ref_Volts;
		}

	} else {
		U_d_limit = reference->u_d_ref_Volts;
		U_q_limit = reference->u_q_ref_Volts;
		limit_on = false;
	}

reference->u_d_ref_Volts = U_d_limit;
reference->u_q_ref_Volts = U_q_limit;
	return (limit_on);
}
