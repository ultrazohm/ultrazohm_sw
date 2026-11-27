#include "../uz_global_configuration.h"
#include "uz_sogipll_sw.h"

#if UZ_SOGIPLL_SW_MAX_INSTANCES > 0U
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include "../uz_HAL.h"
#include "../uz_integrator/uz_integrator.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_piController/uz_piController.h"

// Same single-precision value as the model's single(2*pi), VHDL 0x40c90fdb.
#define UZ_SOGIPLL_SW_TWO_PI 6.2831853071795864769f

struct uz_sogipll_sw_t {
	bool is_ready;
	struct uz_sogipll_sw_config_t config;
	float voltage_estimate;
	float quadrature_voltage_estimate;
	uz_PI_Controller *pi_controller;
	float theta_rad;
};

static uz_sogipll_sw_t *uz_sogipll_sw_allocation(void);
static float uz_sogipll_sw_wrap_phase(float theta_rad);
static float uz_sogipll_sw_integrator_eulerbackward(float current_derivative, float previous_state, float sample_time_s);

static uz_sogipll_sw_t *uz_sogipll_sw_allocation(void) {
	static uint32_t instance_counter = 0U;
	static uz_sogipll_sw_t instances[UZ_SOGIPLL_SW_MAX_INSTANCES] = {0};
	uz_assert(instance_counter < UZ_SOGIPLL_SW_MAX_INSTANCES);
	uz_sogipll_sw_t *self = &instances[instance_counter];
	uz_assert_false(self->is_ready);
	instance_counter++;
	self->is_ready = true;
	return self;
}

uz_sogipll_sw_t *uz_sogipll_sw_init(struct uz_sogipll_sw_config_t config) {
	uz_assert(config.sample_time_s > 0.0f);
	uz_assert(config.omega_feedforward_rad_per_s > 0.0f);
	uz_assert(config.sogi_gain > 0.0f);
	uz_assert(config.proportional_gain >= 0.0f);
	uz_assert(config.integral_gain >= 0.0f);
	uz_assert((config.voltage_scaling < 0.0f) || (config.voltage_scaling > 0.0f));
	uz_sogipll_sw_t *self = uz_sogipll_sw_allocation();
	self->config = config;
	// The IP has no PI output limits; use the full finite float range.
	struct uz_PI_Controller_config pi_config = {
		.type = UZ_PI_PARALLEL,
		.Kp = config.proportional_gain,
		.Ki = config.integral_gain,
		.samplingTime_sec = config.sample_time_s,
		.upper_limit = FLT_MAX,
		.lower_limit = -FLT_MAX
	};
	self->pi_controller = uz_PI_Controller_init(pi_config);
	uz_sogipll_sw_reset(self);
	return self;
}

// Pure backward-Euler step: the caller supplies the derivative at the new state.
static float uz_sogipll_sw_integrator_eulerbackward(float current_derivative, float previous_state, float sample_time_s) {
	return previous_state + (sample_time_s * current_derivative);
}

static float uz_sogipll_sw_wrap_phase(float theta_rad) {
	float wrapped_rad = uz_signals_wrap(theta_rad, UZ_SOGIPLL_SW_TWO_PI);
	// Addition can round a small negative remainder up to exactly 2*pi.
	if (wrapped_rad >= UZ_SOGIPLL_SW_TWO_PI) {
		wrapped_rad = 0.0f;
	}
	return wrapped_rad;
}

struct uz_sogipll_sw_outputs_t uz_sogipll_sw_sample(uz_sogipll_sw_t *self, float voltage_V) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_3ph_alphabeta_t stationary_voltage = {
		.alpha = self->voltage_estimate,
		.beta = self->quadrature_voltage_estimate,
		.gamma = 0.0f
	};
	uz_3ph_dq_t rotating_voltage = uz_transformation_3ph_alphabeta_to_dq(stationary_voltage, self->theta_rad);
	struct uz_sogipll_sw_outputs_t outputs = {0};
	outputs.voltage_estimate = self->voltage_estimate;
	outputs.quadrature_voltage_estimate = self->quadrature_voltage_estimate;
	outputs.theta_rad = self->theta_rad;
	outputs.voltage_d = rotating_voltage.d;
	outputs.voltage_q = rotating_voltage.q;
	float delta_omega_rad_per_s = uz_PI_Controller_sample(self->pi_controller, outputs.voltage_q, 0.0f, false);
	outputs.omega_rad_per_s = delta_omega_rad_per_s + self->config.omega_feedforward_rad_per_s;

	float scaled_voltage = self->config.voltage_scaling * voltage_V;
	float voltage_error = scaled_voltage - self->voltage_estimate;
	float correction = (self->config.sogi_gain * voltage_error) - self->quadrature_voltage_estimate;
	float voltage_derivative = correction * outputs.omega_rad_per_s;

	// Section III Euler arrangement: update the in-phase state first.
	self->voltage_estimate = uz_integrator_eulerforward(voltage_derivative, self->voltage_estimate, self->config.sample_time_s, false);
	// Backward Euler uses the updated in-phase state and this sample's frequency.
	float quadrature_derivative = self->voltage_estimate * outputs.omega_rad_per_s;
	self->quadrature_voltage_estimate = uz_sogipll_sw_integrator_eulerbackward(quadrature_derivative, self->quadrature_voltage_estimate, self->config.sample_time_s);
	float integrated_phase_rad = uz_integrator_eulerforward(outputs.omega_rad_per_s, self->theta_rad, self->config.sample_time_s, false);
	self->theta_rad = uz_sogipll_sw_wrap_phase(integrated_phase_rad);
	if (self->config.rescale_voltage_outputs) {
		outputs.voltage_estimate /= self->config.voltage_scaling;
		outputs.quadrature_voltage_estimate /= self->config.voltage_scaling;
		outputs.voltage_d /= self->config.voltage_scaling;
		outputs.voltage_q /= self->config.voltage_scaling;
	}
	return outputs;
}

void uz_sogipll_sw_reset(uz_sogipll_sw_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->voltage_estimate = 0.0f;
	self->quadrature_voltage_estimate = 0.0f;
	uz_PI_Controller_reset(self->pi_controller);
	self->theta_rad = 0.0f;
}

#endif // UZ_SOGIPLL_SW_MAX_INSTANCES
