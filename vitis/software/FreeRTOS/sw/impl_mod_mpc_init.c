#include "../include/impl_mod_mpc.h"
#include "../Codegen/uz_codegen.h"
#include "../main.h"
uz_codegen codegenInstance;

void impl_mod_mpc_init() {

	codegenInstance.input.v_DC_pu = 565.0f;
	codegenInstance.input.theta_el = 0.0f;
	codegenInstance.input.Ts_times_ZB_over_Ld = 0.0f;
	codegenInstance.input.Ts_times_ZB_over_Lq = 0.0f;
	codegenInstance.input.Ts_times_ZB_over_Lx = 0.0f;
	codegenInstance.input.Ts_times_ZB_over_Ly = 0.0f;
	codegenInstance.input.Rs_over_ZB = 0.0f;
	codegenInstance.input.Ld_over_LB = 0.0f;
	codegenInstance.input.Lq_over_LB = 0.0f;
	codegenInstance.input.Lx_over_LB = 0.0f;
	codegenInstance.input.Ly_over_LB = 0.0f;
	codegenInstance.input.psi_pm_over_psiB = 0.0f;
	codegenInstance.input.omega_el_pu = 0.0f;
	codegenInstance.input.i_dq_pu[0] = 0.0f;
	codegenInstance.input.i_dq_pu[1] = 0.0f;
	codegenInstance.input.i_xy_pu[0] = 0.0f;
	codegenInstance.input.i_xy_pu[1] = 0.0f;
	codegenInstance.input.i_d_ref_pu = 0.0f;
	codegenInstance.input.i_q_ref_pu = 0.0f;
	codegenInstance.input.i_x_ref_pu = 0.0f;
	codegenInstance.input.i_y_ref_pu = 0.0f;
	codegenInstance.input.lambda = 10.0f;
	codegenInstance.input.tolerance = 1e-6;
	codegenInstance.input.max_iter = 10.0f;
	codegenInstance.input.HC_off_on = false;

	uz_codegen_init(&codegenInstance);

}
