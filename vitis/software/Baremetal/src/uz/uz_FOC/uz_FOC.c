#include "uz_FOC.h"
#include "../uz_global_configuration.h"

struct uz_FOC_PI_Controller_variables {
	bool is_ready;
	float I_sum;
	float P_sum;
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

uz_FOC_PI_Controller_variables* uz_FOC_PI_Controller_variables_init(void) {
	uz_FOC_PI_Controller_variables* self = uz_FOC_PI_Controller_variables_allocation();
	return (self);
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

