#include "uz_fsd_mpc_private.h"
#include "uz_HAL.h"
#include "uz_global_configuration.h"
#include <math.h>
#include <stddef.h>
#include <string.h>

#if UZ_FSD_MPC_MAX_INSTANCES > 0U
static uint32_t instance_counter = 0U;
static uz_fsd_mpc_t instances[UZ_FSD_MPC_MAX_INSTANCES] = {{0}};

static bool config_valid(struct uz_fsd_mpc_config cfg) {
	bool physical = isfinite(cfg.resistance_ohm) &&
		cfg.resistance_ohm > 0.0f && isfinite(cfg.inductance_d_h) &&
		cfg.inductance_d_h > 0.0f && isfinite(cfg.inductance_q_h) &&
		cfg.inductance_q_h > 0.0f && isfinite(cfg.flux_pm_wb) &&
		isfinite(cfg.period_s) && cfg.period_s > 0.0f &&
		isfinite(cfg.lambda) && cfg.lambda >= 0.0f;
	bool enums = (cfg.coordinates == UZ_FSD_MPC_SI ||
		cfg.coordinates == UZ_FSD_MPC_PU) &&
		(cfg.selector == UZ_FSD_MPC_EXHAUSTIVE ||
		 cfg.selector == UZ_FSD_MPC_DEADBEAT) &&
		(cfg.modulation >= UZ_FSD_MPC_SVM &&
		 cfg.modulation <= UZ_FSD_MPC_IFT) &&
		(cfg.solver == UZ_FSD_MPC_SIMPLEX_FACE ||
		 cfg.solver == UZ_FSD_MPC_GENERATED_ACTIVE_SET);
	if (!physical || !enums) {
		return false;
	}
#if !UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET
	if (cfg.solver == UZ_FSD_MPC_GENERATED_ACTIVE_SET) {
		return false;
	}
#endif
	if (cfg.coordinates == UZ_FSD_MPC_PU) {
		return isfinite(cfg.base_voltage_v) && cfg.base_voltage_v > 0.0f &&
			isfinite(cfg.base_current_a) && cfg.base_current_a > 0.0f &&
			isfinite(cfg.base_omega_rad_s) && cfg.base_omega_rad_s > 0.0f &&
			cfg.selector == UZ_FSD_MPC_EXHAUSTIVE &&
			cfg.solver == UZ_FSD_MPC_SIMPLEX_FACE;
	}
	return true;
}

static void invalid_output(struct uz_fsd_mpc_output *output,
	uz_fsd_mpc_status_t status) {
	memset(output, 0, sizeof(*output));
	output->duty_a = NAN;
	output->duty_b = NAN;
	output->duty_c = NAN;
	output->status = status;
	output->applied.path = -1;
	output->calculated.path = -1;
}

static bool finish_duties(struct uz_fsd_mpc_output *output,
	const struct uz_fsd_mpc_command *command) {
	float duties[3];
	uz_fsd_mpc_phase_duties(command, duties);
	for (int32_t phase = 0; phase < 3; ++phase) {
		if (!isfinite(duties[phase]) || duties[phase] < -2.0e-7f ||
			duties[phase] > 1.0f + 2.0e-7f) {
			return false;
		}
		/* Representation-only clipping of sub-tolerance roundoff. */
		duties[phase] = fminf(1.0f, fmaxf(0.0f, duties[phase]));
	}
	output->duty_a = duties[0];
	output->duty_b = duties[1];
	output->duty_c = duties[2];
	return true;
}

static uz_fsd_mpc_status_t solve_problem(uz_fsd_mpc_t *self,
	const struct uz_fsd_mpc_problem *problem,
	struct uz_fsd_mpc_command *chosen,
	struct uz_fsd_mpc_diagnostics *diagnostics) {
	int32_t first_path = 0;
	int32_t last_path = 5;
	float best_cost = INFINITY;
	bool found = false;
	if (diagnostics != NULL) {
		memset(diagnostics, 0, sizeof(*diagnostics));
	}
	if (self->config.selector == UZ_FSD_MPC_DEADBEAT) {
		first_path = uz_fsd_mpc_deadbeat_path(&self->config, problem);
		if (first_path < 0 || first_path > 5) {
			return UZ_FSD_MPC_OUTPUT_INVALID;
		}
		last_path = first_path;
	}
	for (int32_t path = first_path; path <= last_path; ++path) {
		struct uz_fsd_mpc_candidate *candidate = &self->candidates[path];
		float free_x[4] = {0.0f};
		float x[4] = {0.0f};
		int32_t solver_status = 0;
		int32_t suppressed = -1;
		bool need_free = self->config.modulation == UZ_FSD_MPC_SVM ||
			self->config.modulation == UZ_FSD_MPC_VFT ||
			(self->config.modulation == UZ_FSD_MPC_IFT &&
			 self->config.coordinates == UZ_FSD_MPC_PU);
		uz_fsd_mpc_gradients(&self->config, problem, path,
			candidate->gradients);
		uz_fsd_mpc_form_qp(&self->config, problem,
			candidate->gradients, candidate->affine,
			candidate->h, candidate->f);
		if (need_free && !uz_fsd_mpc_solve_qp(&self->config,
			candidate->h, candidate->f, -1, free_x, &solver_status)) {
			return UZ_FSD_MPC_QP_FAILED;
		}
		if (self->config.modulation == UZ_FSD_MPC_SVM) {
			for (int32_t j = 0; j < 4; ++j) {
				x[j] = free_x[j];
			}
		} else {
			suppressed = uz_fsd_mpc_suppressed_zero(&self->config,
				problem, path, free_x);
			if (!uz_fsd_mpc_solve_qp(&self->config,
				candidate->h, candidate->f, suppressed, x, &solver_status)) {
				return UZ_FSD_MPC_QP_FAILED;
			}
		}
		candidate->command.path = path;
		candidate->command.clamp_phase = suppressed < 0 ? -1 :
			uz_fsd_mpc_clamp_phases[path][suppressed == 0 ? 0 : 1];
		candidate->command.clamp_rail = suppressed < 0 ? 0 :
			(suppressed == 0 ? 1 : -1);
		for (int32_t j = 0; j < 4; ++j) {
			candidate->command.x_half[j] = x[j];
		}
		candidate->suppressed_zero = suppressed;
		candidate->solver_status = solver_status;
		candidate->cost_a2 = uz_fsd_mpc_trajectory_cost(&self->config,
			problem, candidate->affine, x, candidate->predicted);
		if (!isfinite(candidate->cost_a2)) {
			return UZ_FSD_MPC_OUTPUT_INVALID;
		}
		if (diagnostics != NULL) {
			int32_t index = diagnostics->candidate_count++;
			memcpy(diagnostics->gradients[index], candidate->gradients,
				sizeof(candidate->gradients));
			memcpy(diagnostics->affine[index], candidate->affine,
				sizeof(candidate->affine));
			memcpy(diagnostics->h[index], candidate->h, sizeof(candidate->h));
			memcpy(diagnostics->f[index], candidate->f, sizeof(candidate->f));
			memcpy(diagnostics->x_half[index], x, sizeof(x));
			diagnostics->cost_a2[index] = candidate->cost_a2;
			diagnostics->suppressed_zero[index] = suppressed;
			diagnostics->solver_status[index] = solver_status;
		}
		if (!found || candidate->cost_a2 < best_cost) {
			best_cost = candidate->cost_a2;
			*chosen = candidate->command;
			found = true;
		}
	}
	return found ? UZ_FSD_MPC_OK : UZ_FSD_MPC_QP_FAILED;
}

uz_fsd_mpc_t *uz_fsd_mpc_init(struct uz_fsd_mpc_config config,
	const struct uz_fsd_mpc_input *initial,
	struct uz_fsd_mpc_output *preload) {
	uz_assert_not_NULL(initial);
	uz_assert_not_NULL(preload);
	uz_assert(config_valid(config));
	uz_assert(instance_counter < UZ_FSD_MPC_MAX_INSTANCES);
	uz_fsd_mpc_t *self = &instances[instance_counter];
	uz_assert(!self->is_ready);
	instance_counter++;
	self->config = config;
	self->is_ready = true;
	self->faulted = false;
	(void)uz_fsd_mpc_reset(self, initial, preload);
	return self;
}

uz_fsd_mpc_status_t uz_fsd_mpc_reset(uz_fsd_mpc_t *self,
	const struct uz_fsd_mpc_input *initial,
	struct uz_fsd_mpc_output *preload) {
	struct uz_fsd_mpc_problem problem = {0};
	struct uz_fsd_mpc_command command = {0};
	float measured[2];
	uz_fsd_mpc_status_t status;
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(initial);
	uz_assert_not_NULL(preload);
	uz_assert(self->is_ready);
	invalid_output(preload, UZ_FSD_MPC_INPUT_INVALID);
	self->faulted = true;
	if (!uz_fsd_mpc_input_valid(initial)) {
		return UZ_FSD_MPC_INPUT_INVALID;
	}
	uz_fsd_mpc_phase_to_dq(initial->ia, initial->ib, initial->ic,
		initial->theta_e, measured);
	for (int32_t axis = 0; axis < 2; ++axis) {
		problem.start[axis] = measured[axis];
	}
	problem.reference[0] = initial->id_ref;
	problem.reference[1] = initial->iq_ref;
	problem.phase[0] = initial->ia;
	problem.phase[1] = initial->ib;
	problem.phase[2] = initial->ic;
	problem.theta_mid = initial->theta_e +
		1.5f * initial->omega_e * self->config.period_s;
	problem.omega = initial->omega_e;
	problem.v_dc = initial->v_dc;
	status = solve_problem(self, &problem, &command, NULL);
	if (status != UZ_FSD_MPC_OK) {
		invalid_output(preload, status);
		return status;
	}
	if (!finish_duties(preload, &command)) {
		invalid_output(preload, UZ_FSD_MPC_OUTPUT_INVALID);
		return UZ_FSD_MPC_OUTPUT_INVALID;
	}
	self->next_applied = command;
	self->updates = 0U;
	self->faulted = false;
	preload->status = UZ_FSD_MPC_OK;
	preload->applied = command;
	preload->calculated = command;
	preload->measured_dq_a[0] = measured[0];
	preload->measured_dq_a[1] = measured[1];
	preload->predicted_start_dq_a[0] = measured[0];
	preload->predicted_start_dq_a[1] = measured[1];
	preload->theta_prediction_rad = initial->theta_e +
		0.5f * initial->omega_e * self->config.period_s;
	preload->theta_optimization_rad = problem.theta_mid;
	preload->update_count = 0U;
	return UZ_FSD_MPC_OK;
}

uz_fsd_mpc_status_t uz_fsd_mpc_step(uz_fsd_mpc_t *self,
	const struct uz_fsd_mpc_input *input,
	struct uz_fsd_mpc_output *output,
	struct uz_fsd_mpc_diagnostics *diagnostics) {
	struct uz_fsd_mpc_problem applied_problem = {0};
	struct uz_fsd_mpc_problem next_problem = {0};
	struct uz_fsd_mpc_command calculated = {0};
	struct uz_fsd_mpc_config si_config;
	float measured[2];
	float gradients[4][2];
	float predicted[2];
	uz_fsd_mpc_status_t status;
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(input);
	uz_assert_not_NULL(output);
	uz_assert(self->is_ready);
	if (self->faulted) {
		invalid_output(output, UZ_FSD_MPC_FAULTED);
		return UZ_FSD_MPC_FAULTED;
	}
	if (!uz_fsd_mpc_input_valid(input)) {
		self->faulted = true;
		invalid_output(output, UZ_FSD_MPC_INPUT_INVALID);
		return UZ_FSD_MPC_INPUT_INVALID;
	}
	uz_fsd_mpc_phase_to_dq(input->ia, input->ib, input->ic,
		input->theta_e, measured);
	applied_problem.start[0] = measured[0];
	applied_problem.start[1] = measured[1];
	applied_problem.theta_mid = input->theta_e +
		0.5f * input->omega_e * self->config.period_s;
	applied_problem.omega = input->omega_e;
	applied_problem.v_dc = input->v_dc;
	si_config = self->config;
	si_config.coordinates = UZ_FSD_MPC_SI;
	uz_fsd_mpc_gradients(&si_config, &applied_problem,
		self->next_applied.path, gradients);
	for (int32_t axis = 0; axis < 2; ++axis) {
		float change = 0.0f;
		for (int32_t j = 0; j < 4; ++j) {
			change += (2.0f * self->next_applied.x_half[j]) *
				gradients[j][axis];
		}
		predicted[axis] = measured[axis] + self->config.period_s * change;
		if (!isfinite(predicted[axis])) {
			self->faulted = true;
			invalid_output(output, UZ_FSD_MPC_OUTPUT_INVALID);
			return UZ_FSD_MPC_OUTPUT_INVALID;
		}
	}
	next_problem.start[0] = predicted[0];
	next_problem.start[1] = predicted[1];
	next_problem.reference[0] = input->id_ref;
	next_problem.reference[1] = input->iq_ref;
	next_problem.phase[0] = input->ia;
	next_problem.phase[1] = input->ib;
	next_problem.phase[2] = input->ic;
	next_problem.theta_mid = input->theta_e +
		1.5f * input->omega_e * self->config.period_s;
	next_problem.omega = input->omega_e;
	next_problem.v_dc = input->v_dc;
	status = solve_problem(self, &next_problem, &calculated, diagnostics);
	if (status != UZ_FSD_MPC_OK) {
		self->faulted = true;
		invalid_output(output, status);
		return status;
	}
	if (!finish_duties(output, &calculated)) {
		self->faulted = true;
		invalid_output(output, UZ_FSD_MPC_OUTPUT_INVALID);
		return UZ_FSD_MPC_OUTPUT_INVALID;
	}
	output->status = UZ_FSD_MPC_OK;
	output->applied = self->next_applied;
	output->calculated = calculated;
	output->measured_dq_a[0] = measured[0];
	output->measured_dq_a[1] = measured[1];
	output->predicted_start_dq_a[0] = predicted[0];
	output->predicted_start_dq_a[1] = predicted[1];
	output->theta_prediction_rad = applied_problem.theta_mid;
	output->theta_optimization_rad = next_problem.theta_mid;
	self->next_applied = calculated;
	self->updates++;
	output->update_count = self->updates;
	return UZ_FSD_MPC_OK;
}
#endif
