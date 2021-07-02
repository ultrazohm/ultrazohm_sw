#include "uz_PI_controller.h"
#include "../uz_global_configuration.h"

struct uz_PI_Controller {
	bool is_ready;
	float I_sum;
	float P_sum;
	float Kp;
	float Ki;
	float d_y_max;
	float d_y_min;
	float samplingTime_sec;
};
static size_t instances_counter_PI_Controller = 0;

static uz_PI_Controller instances_PI_Controller[UZ_FOC_PI_CONTROLLER_MAX_INSTANCES] = { 0 };

/**
 * @brief Memory allocation of the PI-Controller object
 *
 * @return Pointer to PI-Controller instance
 */
static uz_PI_Controller* uz_PI_Controller_allocation(void);

static uz_PI_Controller* uz_PI_Controller_allocation(void) {
	uz_assert(instances_counter_PI_Controller < UZ_FOC_PI_CONTROLLER_MAX_INSTANCES);
	uz_PI_Controller* self = &instances_PI_Controller[instances_counter_PI_Controller];
	uz_assert(self->is_ready == false);
	instances_counter_PI_Controller++;
	self->is_ready = true;
	return (self);
}

uz_PI_Controller* uz_PI_Controller_init(uz_PI_Controller_config config) {
	uz_PI_Controller* self = uz_PI_Controller_allocation();
	self->Ki = config.Ki;
	self->Kp = config.Kp;
	self->samplingTime_sec = config.samplingTime_sec;
	self->d_y_max = config.d_y_max;
	self->d_y_min = config.d_y_min;
	return (self);
}
float uz_PI_Controller_sample(uz_PI_Controller* self, float referenceValue, float actualValue, bool ext_clamping) {
	float output = 0.0f;
	return (output);
}
