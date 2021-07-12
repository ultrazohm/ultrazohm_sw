#include "uz_piController.h"
#include "../uz_global_configuration.h"

struct uz_PI_Controller {
	bool is_ready;
	bool int_clamping;
	float I_sum;
	struct uz_PI_Controller_config config;
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
    uz_assert(config.Ki >= 0.0f);
    uz_assert(config.Kp >= 0.0f);
    uz_assert(config.samplingTime_sec > 0.0f);
    uz_assert(config.upper_limit > config.lower_limit);
	self->config = config;
	return (self);
}

bool uz_PI_Controller_Clamping_Circuit(float preIntegrator, float preSat, float upper_limit, float lower_limit) {
	bool output = false;
	float value_after_deadzone = uz_signals_dead_zone(preSat, upper_limit, lower_limit);
	float sign_after_deadzone = uz_signals_get_sign_of_value(value_after_deadzone);
	float sign_preIntegrator = uz_signals_get_sign_of_value(preIntegrator);
	if ( (0.0f != value_after_deadzone) && (sign_after_deadzone == sign_preIntegrator) ) {
		output = true;
	} else {
		output = false;
	}
	return (output);
}

float uz_PI_Controller_sample(uz_PI_Controller* self, float referenceValue, float actualValue, bool ext_clamping) {
	uz_assert_not_NULL(self);
	float error = referenceValue - actualValue;
	float preIntegrator = error * self->config.Ki;
	if (ext_clamping == true || self->int_clamping == true) {
		self->I_sum += 0.0f;
	} else {
		self->I_sum += preIntegrator * self->config.samplingTime_sec;
	}
	float P_sum = error * self->config.Kp;
	float preSat = self->I_sum + P_sum;
	self->int_clamping = uz_PI_Controller_Clamping_Circuit(preIntegrator, preSat, self->config.upper_limit, self->config.lower_limit);
	float output = uz_signals_saturation(preSat, self->config.upper_limit, self->config.lower_limit);
	return (output);
}


void uz_PI_Controller_reset(uz_PI_Controller* self){
    uz_assert_not_NULL(self);
    self->I_sum = 0.0f;
	self->int_clamping = false;
}

void uz_PI_Controller_set_Ki(uz_PI_Controller* self, float new_Ki){
    uz_assert_not_NULL(self);
    uz_assert(new_Ki >= 0.0f);
    self->config.Ki = new_Ki;
}

void uz_PI_Controller_set_Kp(uz_PI_Controller* self, float new_Kp){
    uz_assert_not_NULL(self);
    uz_assert(new_Kp >= 0.0f);
    self->config.Kp = new_Kp;    
}
