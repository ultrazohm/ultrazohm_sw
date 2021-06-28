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
static uz_FOC_VoltageReference instances_FOC_VoltageReference[UZ_FOC_PI_VOLTAGEREFERENCE_MAX_INSTANCES] = { 0 };
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
	uz_assert(instances_counter_FOC_VoltageReference < UZ_FOC_PI_VOLTAGEREFERENCE_MAX_INSTANCES);
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

float uz_FOC_Dead_Zone(float preSat, uz_FOC_config config) {

}
bool uz_FOC_Clamping_Circuit(float preIntegrator, float preSat, uz_FOC_config config) {

}
float uz_FOC_PI_Controller_id(uz_FOC_ActualValues* ActualValues, uz_FOC_config config, uz_FOC_PI_Controller_variables* variables, bool ext_clamping) {

}
