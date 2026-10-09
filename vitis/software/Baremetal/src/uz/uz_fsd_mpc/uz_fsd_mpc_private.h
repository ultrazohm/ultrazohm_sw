#ifndef UZ_FSD_MPC_PRIVATE_H
#define UZ_FSD_MPC_PRIVATE_H

#include "uz_fsd_mpc.h"
#include <stdbool.h>

/* Opt in only when the unchanged academic-use generated solver is supplied
 * by a local build. The distributable core needs no generated dependency. */
#ifndef UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET
#define UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET 0
#endif

struct uz_fsd_mpc_problem {
	float start[2];
	float reference[2];
	float phase[3];
	float theta_mid;
	float omega;
	float v_dc;
};

struct uz_fsd_mpc_candidate {
	struct uz_fsd_mpc_command command;
	float gradients[4][2];
	float affine[9][2][4];
	float h[4][4];
	float f[4];
	float cost_a2;
	float predicted[9][2];
	int32_t suppressed_zero;
	int32_t solver_status;
};

struct uz_fsd_mpc_t {
	bool is_ready;
	bool faulted;
	struct uz_fsd_mpc_config config;
	struct uz_fsd_mpc_command next_applied;
	uint32_t updates;
	struct uz_fsd_mpc_candidate candidates[6];
};

extern const int32_t uz_fsd_mpc_half_paths[6][4];
extern const int32_t uz_fsd_mpc_clamp_phases[6][2];

bool uz_fsd_mpc_input_valid(const struct uz_fsd_mpc_input *input);
void uz_fsd_mpc_gradients(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, int32_t path,
	float gradients[4][2]);
void uz_fsd_mpc_form_qp(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, float gradients[4][2],
	float affine[9][2][4], float h[4][4], float f[4]);
float uz_fsd_mpc_trajectory_cost(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, float affine[9][2][4],
	const float x[4], float predicted[9][2]);
int32_t uz_fsd_mpc_deadbeat_path(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem);
int32_t uz_fsd_mpc_suppressed_zero(const struct uz_fsd_mpc_config *cfg,
	const struct uz_fsd_mpc_problem *problem, int32_t path,
	const float free_x[4]);
bool uz_fsd_mpc_solve_qp(const struct uz_fsd_mpc_config *cfg,
	float h[4][4], float f[4], int32_t suppressed_zero,
	float x[4], int32_t *solver_status);

#endif
