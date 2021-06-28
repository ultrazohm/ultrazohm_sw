#include "uz_FOC.h"
#include "../uz_global_configuration.h"

static size_t instances_counter_FOC_ActualValues = 0;
static size_t instances_counter_FOC_PI_Controller_output = 0;

static uz_FOC_ActualValues instances_FOC_ActualValues[UZ_FOC_ACTUALVALUES_MAX_INSTANCES] = { 0 };
static uz_FOC_PI_Controller_output instances_FOC_PI_Controller_output[UZ_FOC_PI_CONTROLLER_OUTPUT_MAX_INSTANCES] = { 0 };



static uz_FOC_ActualValues* uz_FOC_ActualValues_allocation(void) {
	uz_assert(instances_counter_FOC_ActualValues < UZ_FOC_ACTUALVALUES_MAX_INSTANCES);
	uz_FOC_ActualValues* self = &instances_FOC_ActualValues[instances_counter_FOC_ActualValues];
	uz_assert(self->is_ready == false);
	instances_counter_FOC_ActualValues++;
	self->is_ready = true;
	return (self);
}

static uz_FOC_PI_Controller_output* uz_FOC_PI_Controller_output_allocation(void) {
	uz_assert(instances_counter_FOC_PI_Controller_output < UZ_FOC_PI_CONTROLLER_OUTPUT_MAX_INSTANCES);
	uz_FOC_PI_Controller_output* self = &instances_FOC_PI_Controller_output[instances_counter_FOC_PI_Controller_output];
	uz_assert(self->is_ready == false);
	instances_counter_FOC_PI_Controller_output++;
	self->is_ready = true;
	return (self);
}

uz_FOC_ActualValues* uz_FOC_ActualValues_init(void) {
	uz_FOC_ActualValues* self = uz_FOC_ActualValues_allocation();
	return (self);
}

uz_FOC_PI_Controller_output* uz_FOC_PI_Controller_output_init(void) {
	uz_FOC_PI_Controller_output* self = uz_FOC_PI_Controller_output_allocation();
	return (self);
}
