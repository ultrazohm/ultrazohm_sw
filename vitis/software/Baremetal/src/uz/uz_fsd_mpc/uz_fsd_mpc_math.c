#include "uz_fsd_mpc_private.h"
#include "uz_HAL.h"
#include <math.h>
#include <stddef.h>

const int32_t uz_fsd_mpc_half_paths[6][4] = {
	{0, 4, 6, 7}, {0, 2, 6, 7}, {0, 2, 3, 7},
	{0, 1, 3, 7}, {0, 1, 5, 7}, {0, 4, 5, 7}
};
const int32_t uz_fsd_mpc_clamp_phases[6][2] = {
	{0, 2}, {1, 2}, {1, 0}, {2, 0}, {2, 1}, {0, 1}
};
static const int32_t segment_index[8] = {0, 1, 2, 3, 3, 2, 1, 0};
static const float inv_sqrt_three = 0.5773502691896258f;
static const float sqrt_three_over_two = 0.8660254037844386f;
static const float pi = 3.14159265358979323846f;

static void stator_voltage_ab(int32_t state, float v_dc, float *alpha,
	float *beta) {
	int32_t a = (state >> 2) & 1;
	int32_t b = (state >> 1) & 1;
	int32_t c = state & 1;
	*alpha = v_dc * (float)(2 * a - b - c) / 3.0f;
	*beta = v_dc * (float)(b - c) * inv_sqrt_three;
}

bool uz_fsd_mpc_input_valid(const struct uz_fsd_mpc_input *input) {
	return isfinite(input->ia) && isfinite(input->ib) &&
		isfinite(input->ic) && isfinite(input->theta_e) &&
		isfinite(input->omega_e) && isfinite(input->v_dc) &&
		input->v_dc > 0.0f && isfinite(input->id_ref) &&
		isfinite(input->iq_ref);
}

void uz_fsd_mpc_phase_to_dq(float ia, float ib, float ic, float theta,
	float out_dq[2]) {
	uz_assert_not_NULL(out_dq);
	float alpha = (2.0f * ia - ib - ic) / 3.0f;
	float beta = (ib - ic) * inv_sqrt_three;
	float cosine = cosf(theta);
	float sine = sinf(theta);
	out_dq[0] = alpha * cosine + beta * sine;
	out_dq[1] = beta * cosine - alpha * sine;
}

void uz_fsd_mpc_gradients(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, int32_t path,
	float gradients[4][2]) {
	float cosine = cosf(problem->theta_mid);
	float sine = sinf(problem->theta_mid);
	float id = problem->start[0];
	float iq = problem->start[1];
	float omega = problem->omega;
	float resistance = cfg->resistance_ohm;
	float ld = cfg->inductance_d_h;
	float lq = cfg->inductance_q_h;
	float flux = cfg->flux_pm_wb;
	float voltage_base = 1.0f;
	if (cfg->coordinates == UZ_FSD_MPC_PU) {
		float impedance_base = cfg->base_voltage_v / cfg->base_current_a;
		float inductance_base = impedance_base / cfg->base_omega_rad_s;
		float flux_base = cfg->base_voltage_v / cfg->base_omega_rad_s;
		id /= cfg->base_current_a;
		iq /= cfg->base_current_a;
		omega /= cfg->base_omega_rad_s;
		resistance /= impedance_base;
		ld /= inductance_base;
		lq /= inductance_base;
		flux /= flux_base;
		voltage_base = cfg->base_voltage_v;
	}
	for (int32_t j = 0; j < 4; ++j) {
		float alpha;
		float beta;
		float ud;
		float uq;
		stator_voltage_ab(uz_fsd_mpc_half_paths[path][j],
			problem->v_dc, &alpha, &beta);
		ud = (alpha * cosine + beta * sine) / voltage_base;
		uq = (beta * cosine - alpha * sine) / voltage_base;
		gradients[j][0] = (ud - resistance * id + omega * lq * iq) / ld;
		gradients[j][1] = (uq - resistance * iq - omega * (ld * id + flux)) / lq;
	}
}

void uz_fsd_mpc_form_qp(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, float gradients[4][2],
	float affine[9][2][4], float h[4][4], float f[4]) {
	float scale = (cfg->coordinates == UZ_FSD_MPC_PU) ?
		cfg->base_current_a : 1.0f;
	float segment_time = (cfg->coordinates == UZ_FSD_MPC_PU) ?
		cfg->period_s * cfg->base_omega_rad_s : cfg->period_s;
	float error[2] = {
		(problem->start[0] - problem->reference[0]) / scale,
		(problem->start[1] - problem->reference[1]) / scale
	};
	for (int32_t axis = 0; axis < 2; ++axis) {
		for (int32_t j = 0; j < 4; ++j) {
			affine[0][axis][j] = 0.0f;
		}
	}
	for (int32_t k = 1; k < 9; ++k) {
		for (int32_t axis = 0; axis < 2; ++axis) {
			for (int32_t j = 0; j < 4; ++j) {
				affine[k][axis][j] = affine[k - 1][axis][j];
			}
			affine[k][axis][segment_index[k - 1]] +=
				segment_time * gradients[segment_index[k - 1]][axis];
		}
	}
	for (int32_t i = 0; i < 4; ++i) {
		float fi = 0.0f;
		for (int32_t j = 0; j < 4; ++j) {
			h[i][j] = 0.0f;
		}
		for (int32_t k = 1; k < 9; ++k) {
			float weight = (k == 8) ? cfg->lambda * cfg->lambda : 1.0f;
			for (int32_t axis = 0; axis < 2; ++axis) {
				fi += 2.0f * weight * affine[k][axis][i] * error[axis];
				for (int32_t j = 0; j < 4; ++j) {
					h[i][j] += 2.0f * weight * affine[k][axis][i] *
						affine[k][axis][j];
				}
			}
		}
		f[i] = fi;
	}
	if (cfg->coordinates == UZ_FSD_MPC_PU) {
		float physical_cost_scale = cfg->base_current_a * cfg->base_current_a;
		for (int32_t i = 0; i < 4; ++i) {
			f[i] *= physical_cost_scale;
			for (int32_t j = 0; j < 4; ++j) {
				h[i][j] *= physical_cost_scale;
			}
		}
	}
}

float uz_fsd_mpc_trajectory_cost(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, float affine[9][2][4],
	const float x[4], float predicted[9][2]) {
	float scale = (cfg->coordinates == UZ_FSD_MPC_PU) ?
		cfg->base_current_a : 1.0f;
	float total = 0.0f;
	for (int32_t k = 0; k < 9; ++k) {
		float term = 0.0f;
		for (int32_t axis = 0; axis < 2; ++axis) {
			float value = problem->start[axis];
			for (int32_t j = 0; j < 4; ++j) {
				value += scale * affine[k][axis][j] * x[j];
			}
			predicted[k][axis] = value;
			float error = value - problem->reference[axis];
			term += error * error;
		}
		if (k > 0) {
			total += (k == 8 ? cfg->lambda * cfg->lambda : 1.0f) * term;
		}
	}
	return total;
}

int32_t uz_fsd_mpc_deadbeat_path(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem) {
	float id = problem->start[0];
	float iq = problem->start[1];
	float omega = problem->omega;
	float ud = cfg->resistance_ohm * id -
		omega * cfg->inductance_q_h * iq +
		cfg->inductance_d_h * (problem->reference[0] - id) / cfg->period_s;
	float uq = cfg->resistance_ohm * iq +
		omega * (cfg->inductance_d_h * id + cfg->flux_pm_wb) +
		cfg->inductance_q_h * (problem->reference[1] - iq) / cfg->period_s;
	if (!isfinite(ud) || !isfinite(uq)) {
		return -1;
	}
	float cosine = cosf(problem->theta_mid);
	float sine = sinf(problem->theta_mid);
	float alpha = ud * cosine - uq * sine;
	float beta = ud * sine + uq * cosine;
	if (!isfinite(alpha) || !isfinite(beta)) {
		return -1;
	}
	float angle = atan2f(beta, alpha);
	if (angle < 0.0f) {
		angle += 2.0f * pi;
	}
	int32_t path = (int32_t)floorf(angle / (pi / 3.0f));
	return path > 5 ? 5 : path;
}

int32_t uz_fsd_mpc_suppressed_zero(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, int32_t path,
	const float free_x[4]) {
	if (cfg->modulation == UZ_FSD_MPC_IFT) {
		int32_t positive_phase = uz_fsd_mpc_clamp_phases[path][0];
		int32_t negative_phase = uz_fsd_mpc_clamp_phases[path][1];
		float positive = fmaxf(problem->phase[positive_phase], 0.0f);
		float negative = fmaxf(-problem->phase[negative_phase], 0.0f);
		return positive >= negative ? 0 : 3;
	}
	if (cfg->modulation == UZ_FSD_MPC_VFT) {
		float alpha = 0.0f;
		float beta = 0.0f;
		float phase[3];
		int32_t selected = 0;
		for (int32_t j = 0; j < 4; ++j) {
			float a;
			float b;
			stator_voltage_ab(uz_fsd_mpc_half_paths[path][j],
				problem->v_dc, &a, &b);
			alpha += 2.0f * free_x[j] * a;
			beta += 2.0f * free_x[j] * b;
		}
		phase[0] = alpha;
		phase[1] = -0.5f * alpha + sqrt_three_over_two * beta;
		phase[2] = -0.5f * alpha - sqrt_three_over_two * beta;
		for (int32_t j = 1; j < 3; ++j) {
			if (fabsf(phase[j]) > fabsf(phase[selected])) {
				selected = j;
			}
		}
		return phase[selected] >= 0.0f ? 0 : 3;
	}
	return -1;
}

void uz_fsd_mpc_phase_duties(const struct uz_fsd_mpc_command *command,
	float out_abc[3]) {
	uz_assert_not_NULL(command);
	uz_assert_not_NULL(out_abc);
	for (int32_t phase = 0; phase < 3; ++phase) {
		float duty = 0.0f;
		for (int32_t j = 0; j < 4; ++j) {
			int32_t state = uz_fsd_mpc_half_paths[command->path][j];
			duty += 2.0f * command->x_half[j] *
				(float)((state >> (2 - phase)) & 1);
		}
		out_abc[phase] = duty;
	}
}

uz_fsd_mpc_status_t uz_fsd_mpc_schedule(
	const struct uz_fsd_mpc_command *command, float period_s,
	struct uz_fsd_mpc_schedule *schedule) {
	int32_t states[7];
	float durations[7];
	float sum = 0.0f;
	float tiny;
	uz_assert_not_NULL(command);
	uz_assert_not_NULL(schedule);
	if (command->path < 0 || command->path > 5 ||
		!isfinite(period_s) || period_s <= 0.0f) {
		return UZ_FSD_MPC_INPUT_INVALID;
	}
	for (int32_t j = 0; j < 4; ++j) {
		if (!isfinite(command->x_half[j]) ||
			command->x_half[j] < -2.0e-7f) {
			return UZ_FSD_MPC_OUTPUT_INVALID;
		}
		sum += command->x_half[j];
	}
	if (fabsf(sum - 0.5f) > 2.0e-7f) {
		return UZ_FSD_MPC_OUTPUT_INVALID;
	}
	states[0] = 0;
	states[1] = uz_fsd_mpc_half_paths[command->path][1];
	states[2] = uz_fsd_mpc_half_paths[command->path][2];
	states[3] = 7;
	states[4] = states[2];
	states[5] = states[1];
	states[6] = 0;
	durations[0] = command->x_half[0] * period_s;
	durations[1] = command->x_half[1] * period_s;
	durations[2] = command->x_half[2] * period_s;
	durations[3] = 2.0f * command->x_half[3] * period_s;
	durations[4] = durations[2];
	durations[5] = durations[1];
	durations[6] = durations[0];
	tiny = 1.0e-10f * period_s;
	schedule->count = 0;
	for (int32_t j = 0; j < 7; ++j) {
		if (durations[j] < -tiny) {
			return UZ_FSD_MPC_OUTPUT_INVALID;
		}
		if (durations[j] <= tiny) {
			continue;
		}
		if (schedule->count > 0 &&
			schedule->states[schedule->count - 1] == states[j]) {
			schedule->dwell_s[schedule->count - 1] += durations[j];
		} else {
			int32_t index = schedule->count++;
			schedule->states[index] = states[j];
			schedule->dwell_s[index] = durations[j];
		}
	}
	if (schedule->count == 0) {
		return UZ_FSD_MPC_OUTPUT_INVALID;
	}
	sum = 0.0f;
	for (int32_t j = 0; j < schedule->count; ++j) {
		sum += schedule->dwell_s[j];
	}
	if (fabsf(sum - period_s) > 2.0e-7f * period_s) {
		return UZ_FSD_MPC_OUTPUT_INVALID;
	}
	schedule->dwell_s[schedule->count - 1] += period_s - sum;
	return UZ_FSD_MPC_OK;
}
