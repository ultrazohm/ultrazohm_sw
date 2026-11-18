/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <string.h>
#include "../../uz_global_configuration.h"
#if (UZ_NN_MAX_INSTANCES > 0U) && (UZ_PMSM_SWMODEL_MAX_INSTANCES > 0U)
#include "uz_actor_pmsm_example.h"
#include "../../uz_HAL.h"
#include <math.h>
void uz_actor_pmsm_example_init(uz_actor_pmsm_example_t *self, const struct uz_exported_actor_config *actor,
                                struct uz_pmsm_swmodel_config_t plant, uint32_t oversampling) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(actor);
	uz_assert(oversampling > 0U);
	uz_assert(isfinite(plant.sample_time));
	uz_assert(plant.sample_time > 0.0f);
	uz_assert(actor->command_count == 2U);
	uz_assert(!plant.simulate_mechanical_system);
	uz_assert(plant.integrator_state == uz_pmsm_swmodel_integrator_state_current);
	const float oversampling_factor = (float)oversampling;
	const float control_sample_time_s = plant.sample_time * oversampling_factor;
	uz_assert(isfinite(control_sample_time_s));
	uz_assert(control_sample_time_s > 0.0f);
	uz_exported_actor_init(&self->actor, actor, 1.0f / control_sample_time_s);
	self->plant = uz_pmsm_swmodel_init(plant);
	self->oversampling = oversampling;
	uz_actor_pmsm_example_reset(self);
}
void uz_actor_pmsm_example_reset(uz_actor_pmsm_example_t *self) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(self->plant);
	uz_pmsm_swmodel_reset(self->plant);
	uz_exported_actor_reset(&self->actor, NULL);
	const struct uz_pmsm_swmodel_outputs_t reset_output = {0};
	self->output = reset_output;
}
struct uz_pmsm_swmodel_outputs_t uz_actor_pmsm_example_step(uz_actor_pmsm_example_t *self, float id_reference,
                                                            float iq_reference, float speed_rpm) {
	uz_assert_not_NULL(self);
	/* Keep this C99 constant independent of the nonstandard M_PI macro. */
	static const float rpm_to_rad_per_second = 6.2831853071795864769f / 60.0f;
	uz_assert(isfinite(id_reference));
	uz_assert(isfinite(iq_reference));
	uz_assert(isfinite(speed_rpm));
	const struct uz_exported_actor_signals signals = {.current = {self->output.i_dq_A.d, self->output.i_dq_A.q},
	                                                  .reference = {id_reference, iq_reference},
	                                                  .speed_rpm = speed_rpm};
	uz_exported_actor_sample(&self->actor, signals);
	const struct uz_pmsm_swmodel_inputs_t inputs = {.v_dq_V = {.d = self->actor.applied[0], .q = self->actor.applied[1]},
	                                                .omega_mech_1_s = speed_rpm * rpm_to_rad_per_second,
	                                                .load_torque = 0.0f};
	for (uint32_t i = 0U; i < self->oversampling; ++i) {
		self->output = uz_pmsm_swmodel_step(self->plant, inputs);
	}
	return self->output;
}
#endif
