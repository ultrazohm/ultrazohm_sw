#include "PI_0.h"
static const uz_PMSM_t config_PMSM = {
	.I_max_Ampere = 10.0f,
	.J_kg_m_squared = 1.0f,
	.Ld_Henry = 1.0f,
	.Lq_Henry = 1.0f,
	.Psi_PM_Vs = 1.0f,
	.R_ph_Ohm = 1.0f,
	.polePairs = UZ_D5_MOTOR_POLE_PAIR_NUMBER};
const struct uz_PI_Controller_config config_d = {
	.type = parallel,
	.Kp = PI_PI_KP_D,
	.Ki = PI_PI_KI_D,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = DQ_SYSTEM_LIMIT,
	.lower_limit = -DQ_SYSTEM_LIMIT};
const struct uz_PI_Controller_config config_q = {
	.type = parallel,
	.Kp = PI_PI_KP_Q,
	.Ki = PI_PI_KI_Q,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = DQ_SYSTEM_LIMIT,
	.lower_limit = -DQ_SYSTEM_LIMIT};
struct uz_CurrentControl_config cc_config_dq = {
	.config_PMSM = config_PMSM,
	.config_id = config_d,
	.config_iq = config_q,
	.decoupling_select = linear_decoupling,
	.max_modulation_index = MODULATION_INDEX};

uz_CurrentControl_t* init_PI_0_cc_dq(void){
	uz_CurrentControl_t* ptr = uz_CurrentControl_init(cc_config_dq);
	return ptr;
}

uz_9ph_abc_t step_controllers_PI_0(DS_Data* Data, uz_CurrentControl_t* object){
	float omega_el = Data->av.rotational_position.omega_mech_rad_s*UZ_D5_MOTOR_POLE_PAIR_NUMBER;
	uz_3ph_dq_t dq_ref = uz_CurrentControl_sample(object, Data->rasv.dq_setpoints, Data->av.currents_dq, Data->av.U_ZK, omega_el);
	uz_9ph_dq_t out_dq = {
		.d = dq_ref.d,
		.q = dq_ref.q,
		.x1 = 0.0f,
		.y1 = 0.0f,
		.x2 = 0.0f,
		.y2 = 0.0f,
		.x3 = 0.0f,
		.y3 = 0.0f,
		.zero = 0.0f};
	return uz_transformation_9ph_dq_to_abc(out_dq, Data->av.rotational_position.position_el_2pi);
}
