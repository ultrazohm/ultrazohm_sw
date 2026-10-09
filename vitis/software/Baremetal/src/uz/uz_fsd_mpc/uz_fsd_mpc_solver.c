#include "uz_fsd_mpc_private.h"
#if UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET
#include "fsd_quadprog_api.h"
#include <float.h>
#endif
#include <math.h>
#include <stddef.h>

/* The extracted generated solver uses double and static manager storage.
 * Calls to this adapter must be serialized by the embedding application. */

static bool solve_kkt(float matrix[5][6], int32_t n, float solution[5]) {
	for (int32_t col = 0; col < n; ++col) {
		int32_t pivot = col;
		for (int32_t row = col + 1; row < n; ++row) {
			if (fabsf(matrix[row][col]) > fabsf(matrix[pivot][col])) {
				pivot = row;
			}
		}
		if (fabsf(matrix[pivot][col]) < 1.0e-8f) {
			return false;
		}
		if (pivot != col) {
			for (int32_t j = col; j <= n; ++j) {
				float temp = matrix[col][j];
				matrix[col][j] = matrix[pivot][j];
				matrix[pivot][j] = temp;
			}
		}
		for (int32_t row = col + 1; row < n; ++row) {
			float ratio = matrix[row][col] / matrix[col][col];
			for (int32_t j = col; j <= n; ++j) {
				matrix[row][j] -= ratio * matrix[col][j];
			}
		}
	}
	for (int32_t row = n - 1; row >= 0; --row) {
		float value = matrix[row][n];
		for (int32_t j = row + 1; j < n; ++j) {
			value -= matrix[row][j] * solution[j];
		}
		solution[row] = value / matrix[row][row];
	}
	return true;
}

static bool simplex_face_solve(float h[4][4], float f[4],
	int32_t suppressed_zero, float x[4]) {
	float best_value = INFINITY;
	float qp_scale = 1.0f;
	bool found = false;
	for (int32_t i = 0; i < 4; ++i) {
		qp_scale = fmaxf(qp_scale, fabsf(f[i]));
		for (int32_t j = 0; j < 4; ++j) {
			qp_scale = fmaxf(qp_scale, fabsf(h[i][j]));
		}
	}
	for (int32_t mask = 1; mask < 16; ++mask) {
		int32_t free_index[4];
		int32_t count = 0;
		float matrix[5][6] = {{0.0f}};
		float result[5] = {0.0f};
		float trial[4] = {0.0f};
		float sum = 0.0f;
		float value = 0.0f;
		if (suppressed_zero >= 0 && (mask & (1 << suppressed_zero)) != 0) {
			continue;
		}
		for (int32_t j = 0; j < 4; ++j) {
			if ((mask & (1 << j)) != 0) {
				free_index[count++] = j;
			}
		}
		for (int32_t i = 0; i < count; ++i) {
			for (int32_t j = 0; j < count; ++j) {
				matrix[i][j] = h[free_index[i]][free_index[j]] / qp_scale;
			}
			matrix[i][count] = 1.0f;
			matrix[i][count + 1] = -f[free_index[i]] / qp_scale;
			matrix[count][i] = 1.0f;
		}
		matrix[count][count + 1] = 0.5f;
		if (!solve_kkt(matrix, count + 1, result)) {
			continue;
		}
		for (int32_t i = 0; i < count; ++i) {
			if (!isfinite(result[i]) || result[i] < -2.0e-7f) {
				sum = -1.0f;
				break;
			}
			trial[free_index[i]] = fmaxf(result[i], 0.0f);
			sum += trial[free_index[i]];
		}
		if (sum <= 0.0f || fabsf(sum - 0.5f) > 2.0e-6f) {
			continue;
		}
		for (int32_t i = 0; i < 4; ++i) {
			trial[i] *= 0.5f / sum;
			value += f[i] * trial[i];
			for (int32_t j = 0; j < 4; ++j) {
				value += 0.5f * trial[i] * h[i][j] * trial[j];
			}
		}
		if (isfinite(value) && (!found || value < best_value)) {
			for (int32_t i = 0; i < 4; ++i) {
				x[i] = trial[i];
			}
			best_value = value;
			found = true;
		}
	}
	return found;
}

#if UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET
static bool generated_active_set_solve(float h[4][4], float f[4],
	int32_t suppressed_zero, float x[4], int32_t *solver_status) {
	double hd[16];
	double fd[4];
	double aeq[12] = {0.0};
	for (int32_t col = 0; col < 4; ++col) {
		fd[col] = (double)f[col];
		aeq[3 * col] = 1.0;
		for (int32_t row = 0; row < 4; ++row) {
			hd[4 * col + row] = (double)h[row][col];
		}
	}
	if (suppressed_zero >= 0) {
		aeq[3 * suppressed_zero + 1] = 1.0;
	}
	fsd_quadprog_result_t result = fsd_quadprog_active_set_solve(hd, fd, aeq);
	*solver_status = (int32_t)result.exitflag;
	if (result.exitflag != 1.0 || !(fabs(result.objective) <= DBL_MAX) ||
		!(fabs(result.constraint_violation) <= DBL_MAX) ||
		result.reached_iteration_cap != 0) {
		return false;
	}
	for (int32_t j = 0; j < 4; ++j) {
		if (!(fabs(result.x[j]) <= DBL_MAX)) {
			return false;
		}
		x[j] = (float)result.x[j];
	}
	return true;
}
#endif

bool uz_fsd_mpc_solve_qp(const struct uz_fsd_mpc_config *cfg,
	float h[4][4], float f[4], int32_t suppressed_zero,
	float x[4], int32_t *solver_status) {
	bool solved;
	float sum = 0.0f;
	*solver_status = 0;
	for (int32_t i = 0; i < 4; ++i) {
		if (!isfinite(f[i])) {
			*solver_status = -2;
			return false;
		}
		for (int32_t j = 0; j < 4; ++j) {
			if (!isfinite(h[i][j])) {
				*solver_status = -2;
				return false;
			}
		}
	}
	if (cfg->solver == UZ_FSD_MPC_GENERATED_ACTIVE_SET) {
#if UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET
		solved = generated_active_set_solve(h, f, suppressed_zero,
			x, solver_status);
#else
		*solver_status = -3;
		return false;
#endif
	} else {
		solved = simplex_face_solve(h, f, suppressed_zero, x);
		*solver_status = solved ? 1 : -1;
	}
	if (!solved) {
		return false;
	}
	for (int32_t j = 0; j < 4; ++j) {
		if (!isfinite(x[j]) || x[j] < -2.0e-7f) {
			return false;
		}
		sum += x[j];
	}
	if (fabsf(sum - 0.5f) > 2.0e-7f) {
		return false;
	}
	if (suppressed_zero >= 0 && fabsf(x[suppressed_zero]) > 2.0e-7f) {
		return false;
	}
	return true;
}
