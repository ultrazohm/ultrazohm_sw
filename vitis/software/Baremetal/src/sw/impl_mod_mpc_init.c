#include "../include/impl_mod_mpc.h"
#include "../Codegen/uz_codegen.h"
#include "../main.h"
uz_codegen codegenInstance;

typedef struct pre_calc_val_t {
	float Rs_over_ZB;
	float Ts_times_ZB_over_Ld;
	float Ts_times_ZB_over_Lq;
	float Ld_over_LB;
	float Lq_over_LB;
	float psi_pm_over_psiB;
}pre_calc_val_t;

extern const pre_calc_val_t pre_calc_val_left;

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
