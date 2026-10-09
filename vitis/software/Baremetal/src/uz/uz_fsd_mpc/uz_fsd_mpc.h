#ifndef UZ_FSD_MPC_H
#define UZ_FSD_MPC_H

#include <stdint.h>

typedef enum {
	UZ_FSD_MPC_SI = 0,
	UZ_FSD_MPC_PU = 1
} uz_fsd_mpc_coordinates_t;

typedef enum {
	UZ_FSD_MPC_EXHAUSTIVE = 0,
	UZ_FSD_MPC_DEADBEAT = 1
} uz_fsd_mpc_selector_t;

typedef enum {
	UZ_FSD_MPC_SVM = 0,
	UZ_FSD_MPC_VFT = 1,
	UZ_FSD_MPC_IFT = 2
} uz_fsd_mpc_modulation_t;

typedef enum {
	UZ_FSD_MPC_SIMPLEX_FACE = 0,
	UZ_FSD_MPC_GENERATED_ACTIVE_SET = 1
} uz_fsd_mpc_solver_t;

typedef enum {
	UZ_FSD_MPC_OK = 0,
	UZ_FSD_MPC_INPUT_INVALID = 1,
	UZ_FSD_MPC_QP_FAILED = 2,
	UZ_FSD_MPC_OUTPUT_INVALID = 3,
	UZ_FSD_MPC_FAULTED = 4
} uz_fsd_mpc_status_t;

struct uz_fsd_mpc_config {
	float resistance_ohm;
	float inductance_d_h;
	float inductance_q_h;
	float flux_pm_wb;
	float period_s;
	float lambda;
	float base_voltage_v;
	float base_current_a;
	float base_omega_rad_s;
	uz_fsd_mpc_coordinates_t coordinates;
	uz_fsd_mpc_selector_t selector;
	uz_fsd_mpc_modulation_t modulation;
	uz_fsd_mpc_solver_t solver;
};

struct uz_fsd_mpc_input {
	float ia;
	float ib;
	float ic;
	float theta_e;
	float omega_e;
	float v_dc;
	float id_ref;
	float iq_ref;
};

struct uz_fsd_mpc_command {
	int32_t path;
	float x_half[4];
	int32_t clamp_phase;
	int32_t clamp_rail;
};

struct uz_fsd_mpc_output {
	float duty_a;
	float duty_b;
	float duty_c;
	uz_fsd_mpc_status_t status;
	float measured_dq_a[2];
	float predicted_start_dq_a[2];
	float theta_prediction_rad;
	float theta_optimization_rad;
	struct uz_fsd_mpc_command applied;
	struct uz_fsd_mpc_command calculated;
	uint32_t update_count;
};

/* Optional caller-owned fixed diagnostic workspace; no heap allocation. */
struct uz_fsd_mpc_diagnostics {
	float gradients[6][4][2];
	float affine[6][9][2][4];
	float h[6][4][4];
	float f[6][4];
	float x_half[6][4];
	float cost_a2[6];
	int32_t suppressed_zero[6];
	int32_t solver_status[6];
	int32_t candidate_count;
};

struct uz_fsd_mpc_schedule {
	int32_t states[7];
	float dwell_s[7];
	int32_t count;
};

typedef struct uz_fsd_mpc_t uz_fsd_mpc_t;

/* The initial sample is required to compute the one-period preload. */
uz_fsd_mpc_t *uz_fsd_mpc_init(struct uz_fsd_mpc_config config,
	const struct uz_fsd_mpc_input *initial,
	struct uz_fsd_mpc_output *preload);
uz_fsd_mpc_status_t uz_fsd_mpc_reset(uz_fsd_mpc_t *self,
	const struct uz_fsd_mpc_input *initial,
	struct uz_fsd_mpc_output *preload);
uz_fsd_mpc_status_t uz_fsd_mpc_step(uz_fsd_mpc_t *self,
	const struct uz_fsd_mpc_input *input,
	struct uz_fsd_mpc_output *output,
	struct uz_fsd_mpc_diagnostics *diagnostics);

/* Pure fixed-precision component boundaries for differential testing. */
void uz_fsd_mpc_phase_to_dq(float ia, float ib, float ic, float theta,
	float out_dq[2]);
void uz_fsd_mpc_phase_duties(const struct uz_fsd_mpc_command *command,
	float out_abc[3]);
uz_fsd_mpc_status_t uz_fsd_mpc_schedule(
	const struct uz_fsd_mpc_command *command, float period_s,
	struct uz_fsd_mpc_schedule *schedule);

#endif
