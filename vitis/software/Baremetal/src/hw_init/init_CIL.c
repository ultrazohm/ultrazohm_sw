#include "../include/init_CIL.h"
#include "xparameters.h"


uz_inverter_3ph_t* init_CIL_inv1(void){
	struct uz_inverter_3ph_config_t cil_inverter1_config = {
		.base_address = XPAR_UZ_USER_NINEPHASE_CIL_UZ_INVERTER_3PH_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.switch_pspl_abc = false,
		.switch_pspl_gate = false,
		.udc = UDC_CIL};
	return uz_inverter_3ph_init(cil_inverter1_config);
}

uz_inverter_3ph_t* init_CIL_inv2(void){
	struct uz_inverter_3ph_config_t cil_inverter2_config = {
		.base_address = XPAR_UZ_USER_NINEPHASE_CIL_UZ_INVERTER_3PH_1_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.switch_pspl_abc = false,
		.switch_pspl_gate = false,
		.udc = UDC_CIL};
	return uz_inverter_3ph_init(cil_inverter2_config);
}

uz_inverter_3ph_t* init_CIL_inv3(void){
	struct uz_inverter_3ph_config_t cil_inverter3_config = {
		.base_address = XPAR_UZ_USER_NINEPHASE_CIL_UZ_INVERTER_3PH_2_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.switch_pspl_abc = false,
		.switch_pspl_gate = false,
		.udc = UDC_CIL};
	return uz_inverter_3ph_init(cil_inverter3_config);
}

uz_pmsm9ph_transformation_t* init_CIL_trafo(void){
	struct uz_pmsm9ph_config_t trafo_config = {
		.base_address = XPAR_UZ_USER_NINEPHASE_CIL_UZ_NINEPHASE_VSD_TRA_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f
	};
	return uz_pmsm9ph_transformation_init(trafo_config);
}

uz_pmsm_model9ph_dq_t* init_CIL_pmsm(void){
	struct uz_pmsm_model9ph_dq_config_t pmsm_config = {
		.base_address = XPAR_UZ_USER_NINEPHASE_CIL_UZ_PMSM_MODEL_9PH_DQ_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000.0f,
		.polepairs = UZ_D5_MOTOR_POLE_PAIR_NUMBER,
		.r_1 = 0.3411f,
		.inductance.d = 0.0029587f,
		.inductance.q = 0.0038f,
		.inductance.x1 = 0.0019410f,
		.inductance.y1 = 0.0014541f,
		.inductance.x2 = 0.0020143f,
		.inductance.y2 = 0.0021166f,
		.inductance.x3 = 0.0019249f,
		.inductance.y3 = 0.0030169f,
		.inductance.zero = 0.0019548f,
		.psi_pm = 0.0741442f,
		.friction_coefficient = 0.01f,
		.coulomb_friction_constant = 0.01f,
		.inertia = 0.01,
		.simulate_mechanical_system = false,
		.switch_pspl = false
	};
	return uz_pmsm_model9ph_dq_init(pmsm_config);
}

struct CIL_objects init_all_objects_CIL(void){
	struct CIL_objects out = {
		.inv1 = init_CIL_inv1(),
		.inv2 = init_CIL_inv1(),
		.inv3 = init_CIL_inv1(),
		.transformation = init_CIL_trafo(),
		.pmsm = init_CIL_pmsm()
	};
	return out;
}
