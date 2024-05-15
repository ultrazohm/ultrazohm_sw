#include "../include/impl_mod_mpc.h"
#include "../Codegen/uz_codegen.h"
#include "../main.h"
uz_codegen codegenInstance;

const float polepairs = 4.0f;

#define UZ_PIf		3.14159265358979323846
#define UZ_PWM_FREQUENCY_0                       4.0e3f
#define UZ_PWM_FREQUENCY_1                     100.0e3f

typedef struct uz_PMSM_t{
    float R_ph_Ohm;/**< phase resitance inductance in Ohm. Must be greater than 0.0f */
    float Ld_Henry; /**< d-axis inductance in Henry. Must be greater than 0.0f */
    float Lq_Henry;/**< q-axis inductance in Henry. Must be greater than 0.0f */
    float Psi_PM_Vs;/**< permanent magnet flux linkage in Volt-seconds. Must be greater or equal than 0.0f */
    float polePairs; /**< number of polePairs of the machine. Must be greater than 0.0f. Must be no decimal value (i.e. 2.5f is not allowed) */
    float J_kg_m_squared; /**< inertia of the PMSM. Must be greater than 0.0f */
    float I_max_Ampere; /**< max allowed current per phase. Must be greater than 0.0f */
}uz_PMSM_t;

const struct uz_PMSM_t AM8141_MPC = {
  .R_ph_Ohm = 0.51,
  .Ld_Henry = 0.002f,
  .Lq_Henry = 0.002f,
  .Psi_PM_Vs = 0.042f,
  .polePairs = 4.0f,
  .I_max_Ampere = 12.0f,
  .J_kg_m_squared = 0.000108
};//these parameters are only needed if linear decoupling is selected


typedef struct pre_calc_val_t {
	float Rs_over_ZB;
	float Ts_times_ZB_over_Ld;
	float Ts_times_ZB_over_Lq;
	float Ld_over_LB;
	float Lq_over_LB;
	float psi_pm_over_psiB;
}pre_calc_val_t;

typedef struct rated_val_t {
	float VR;
	float IR;
	float nR;
}rated_val_t;

typedef struct base_val_t {
	float VB;
	float IB;
	float omegaB;
	float ZB;
	float LB;
	float psiB;
}base_val_t;

// rated values of Beckhoff_AM8141
const rated_val_t rated_values={
		.IR=8.0f,
		.VR=48.0f/sqrt(2),
		.nR=1000.0f
};

// per unit base values
const base_val_t base_val={
		.VB=sqrt(2.0f/3.0f)*rated_values.VR,
		.IB=sqrt(2.0f)*rated_values.IR,
		.omegaB=rated_values.nR*2.0f*UZ_PIf/60.0f*polepairs,
		.ZB=(sqrt(2.0f/3.0f)*rated_values.VR)/(sqrt(2.0f)*rated_values.IR),
		.LB=(sqrt(2.0f/3.0f)*rated_values.VR)/(sqrt(2.0f)*rated_values.IR)/(rated_values.nR*2.0f*UZ_PIf/60.0f*polepairs),
		.psiB=(sqrt(2.0f/3.0f)*rated_values.VR)/(rated_values.nR*2.0f*UZ_PIf/60.0f*polepairs)
};

const float Ts_left = 1.0f/UZ_PWM_FREQUENCY_0;
const float Ts_right = 1.0f/UZ_PWM_FREQUENCY_1;

const pre_calc_val_t pre_calc_val_left={
		.Rs_over_ZB = AM8141_MPC.R_ph_Ohm/base_val.ZB,
		.Ts_times_ZB_over_Ld = Ts_left*base_val.ZB/AM8141_MPC.Ld_Henry,
		.Ts_times_ZB_over_Lq = Ts_left*base_val.ZB/AM8141_MPC.Lq_Henry,
		.Ld_over_LB = AM8141_MPC.Ld_Henry/base_val.LB,
		.Lq_over_LB = AM8141_MPC.Lq_Henry/base_val.LB,
		.psi_pm_over_psiB = AM8141_MPC.Psi_PM_Vs/base_val.psiB
};


void impl_mod_mpc_init() {

	codegenInstance.input.Rs_over_ZB = pre_calc_val_left.Rs_over_ZB;
	codegenInstance.input.Ts_times_ZB_over_Ld = pre_calc_val_left.Ts_times_ZB_over_Ld*2.0f;
	codegenInstance.input.Ts_times_ZB_over_Lq = pre_calc_val_left.Ts_times_ZB_over_Lq*2.0f;
	codegenInstance.input.Ld_over_LB = pre_calc_val_left.Ld_over_LB;
	codegenInstance.input.Lq_over_LB = pre_calc_val_left.Lq_over_LB;
	codegenInstance.input.psi_pm_over_psiB = pre_calc_val_left.psi_pm_over_psiB;
	codegenInstance.input.alpha0 = 10.0f;
	codegenInstance.input.lambda = 10.0f;
	codegenInstance.input.max_iter = 25.0f;
	codegenInstance.input.tolerance = 1e-6;

	uz_codegen_init(&codegenInstance);

}
