#include "uz_FOC.h"
#define max_FOC_CurrentControl_instances 1
#define max_FOC_SpeedControl_instances 1

static size_t counter_FOC_CurrentControl = 0;
static size_t counter_FOC_SpeedControl = 0;

static uz_FOC_CurrentControl_parameters instances_FOC_CurrentControl[max_FOC_CurrentControl_instances] = { 0 };
static uz_FOC_SpeedControl_parameters instances_FOC_SpeedControl[max_FOC_SpeedControl_instances] = { 0 };

uz_FOC_CurrentControl_parameters* uz_FOC_CurrentControl_init(uz_FOC_CurrentControl_config config) {
	uz_assert(counter_FOC_CurrentControl < max_FOC_CurrentControl_instances);
	uz_FOC_CurrentControl_parameters* self = &instances_FOC_CurrentControl[counter_FOC_CurrentControl];
	uz_assert(self->is_ready == false);
	counter_FOC_CurrentControl += 1;
	self->is_ready = true;
	return (self);
}
