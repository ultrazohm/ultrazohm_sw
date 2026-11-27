#include "../../uz/uz_global_configuration.h"
#include "uz_sogipll.h"

#if UZ_SOGIPLL_MAX_INSTANCES > 0U
#include <stdbool.h>
#include <stddef.h>
#include "../../uz/uz_HAL.h"
#include "uz_sogipll_hw.h"

#define UZ_SOGIPLL_CLOCK_HZ 100000000U
#define UZ_SOGIPLL_SAMPLE_TIME_S 2.0e-6f

struct uz_sogipll_t {
	bool is_ready;
	uint32_t base_address;
};

static uint32_t instance_counter = 0U;
static uz_sogipll_t instances[UZ_SOGIPLL_MAX_INSTANCES] = {0};

static void validate_config(struct uz_sogipll_config_t config);
static void validate_instance(const uz_sogipll_t *self);
static uz_sogipll_t *allocate_instance(void);

static void validate_config(struct uz_sogipll_config_t config) {
	uz_assert(config.base_address != 0U);
	uz_assert((config.base_address & 3U) == 0U);
	uz_assert(config.ip_clk_frequency_Hz == UZ_SOGIPLL_CLOCK_HZ);
	uz_assert(config.omega_feedforward_rad_per_s > 0.0f);
	uz_assert(config.sogi_gain > 0.0f);
	uz_assert(config.proportional_gain >= 0.0f);
	uz_assert(config.integral_gain >= 0.0f);
	uz_assert((config.voltage_scaling < 0.0f) || (config.voltage_scaling > 0.0f));
	for (uint32_t i = 0U; i < instance_counter; i++) {
		uz_assert(instances[i].base_address != config.base_address);
	}
}

static void validate_instance(const uz_sogipll_t *self) {
	uz_assert(self != NULL);
	uz_assert(self->is_ready);
}

static uz_sogipll_t *allocate_instance(void) {
	uz_assert(instance_counter < UZ_SOGIPLL_MAX_INSTANCES);
	uz_sogipll_t *self = &instances[instance_counter];
	uz_assert_false(self->is_ready);
	instance_counter++;
	return self;
}

uz_sogipll_t *uz_sogipll_init(struct uz_sogipll_config_t config) {
	validate_config(config);
	uz_sogipll_t *self = allocate_instance();
	self->base_address = config.base_address;
	// Keep algorithm state in reset while configuring the free-running core.
	uz_sogipll_hw_write_in_rst(self->base_address, true);
	uz_sogipll_hw_write_in_v(self->base_address, 0.0f);
	uz_sogipll_hw_write_in_omega_ff(self->base_address, config.omega_feedforward_rad_per_s);
	uz_sogipll_hw_write_in_k(self->base_address, config.sogi_gain);
	uz_sogipll_hw_write_in_kp(self->base_address, config.proportional_gain);
	uz_sogipll_hw_write_in_ki(self->base_address, config.integral_gain);
	uz_sogipll_hw_write_in_t_sample(self->base_address, UZ_SOGIPLL_SAMPLE_TIME_S);
	uz_sogipll_hw_write_in_v_scaling(self->base_address, config.voltage_scaling);
	uz_sogipll_hw_write_in_rst(self->base_address, false);
	self->is_ready = true;
	return self;
}

void uz_sogipll_set_voltage(const uz_sogipll_t *self, float voltage_V) {
	validate_instance(self);
	uz_sogipll_hw_write_in_v(self->base_address, voltage_V);
}

void uz_sogipll_reset(const uz_sogipll_t *self) {
	validate_instance(self);
	uz_sogipll_hw_write_in_rst(self->base_address, true);
	uz_sogipll_hw_write_in_rst(self->base_address, false);
}

struct uz_sogipll_outputs_t uz_sogipll_read_outputs(const uz_sogipll_t *self) {
	validate_instance(self);
	struct uz_sogipll_outputs_t outputs = {0};
	outputs.voltage_estimate = uz_sogipll_hw_read_out_v_est(self->base_address);
	outputs.quadrature_voltage_estimate = uz_sogipll_hw_read_out_qv_est(self->base_address);
	outputs.voltage_d = uz_sogipll_hw_read_out_v_d(self->base_address);
	outputs.voltage_q = uz_sogipll_hw_read_out_v_q(self->base_address);
	outputs.theta_rad = uz_sogipll_hw_read_out_theta_est(self->base_address);
	outputs.omega_rad_per_s = uz_sogipll_hw_read_out_omega_est(self->base_address);
	return outputs;
}

#endif // UZ_SOGIPLL_MAX_INSTANCES
