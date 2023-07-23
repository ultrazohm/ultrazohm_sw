#include "PIR_PIR.h"
static const uz_3ph_dq_t zero_ref_dq = {0};

// resonant
struct uz_subspace_resonant_control_config resonant_config_dq = {
    .sampling_time = SAMPLETIME,
    .gain_1 = PIR_PIR_GAIN_D,
    .gain_2 = PIR_PIR_GAIN_Q,
    .harmonic_order = 3.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
struct uz_subspace_resonant_control_config resonant_config_xy1 = {
    .sampling_time = SAMPLETIME,
    .gain_1 = PIR_PIR_GAIN_X1,
    .gain_2 = PIR_PIR_GAIN_Y1,
    .harmonic_order = 3.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
struct uz_subspace_resonant_control_config resonant_config_xy2 = {
    .sampling_time = SAMPLETIME,
    .gain_1 = PIR_PIR_GAIN_X2,
    .gain_2 = PIR_PIR_GAIN_Y2,
    .harmonic_order = 5.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
struct uz_subspace_resonant_control_config resonant_config_xy3 = {
    .sampling_time = SAMPLETIME,
    .gain_1 = PIR_PIR_GAIN_X3,
    .gain_2 = PIR_PIR_GAIN_Y3,
    .harmonic_order = 7.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};

uz_subspace_resonant_control* init_PIR_PIR_resonant_dq(void){
	uz_subspace_resonant_control* ptr = uz_subspace_resonant_control_init(resonant_config_dq);
	return ptr;
}
uz_subspace_resonant_control* init_PIR_PIR_resonant_xy1(void){
	uz_subspace_resonant_control* ptr = uz_subspace_resonant_control_init(resonant_config_xy1);
	return ptr;
}
uz_subspace_resonant_control* init_PIR_PIR_resonant_xy2(void){
	uz_subspace_resonant_control* ptr = uz_subspace_resonant_control_init(resonant_config_xy2);
	return ptr;
}
uz_subspace_resonant_control* init_PIR_PIR_resonant_xy3(void){
	uz_subspace_resonant_control* ptr = uz_subspace_resonant_control_init(resonant_config_xy3);
	return ptr;
}

uz_3ph_dq_t step_dq_res(uz_CurrentControl_t* PI, uz_subspace_resonant_control* res, DS_Data* Data){
	uz_3ph_dq_t pi_out = uz_CurrentControl_sample(PI, zero_ref_dq, Data->av.currents_xy1, Data->av.U_ZK, Data->av.omega_el);
	uz_3ph_dq_t res_out = uz_subspace_resonant_control_step_dq(res, zero_ref_dq, Data->av.currents_xy1, Data->av.omega_el);
	uz_3ph_dq_t out = {
			.d = pi_out.d + res_out.d,
			.q = pi_out.q + res_out.q,
			.zero = pi_out.zero + res_out.zero,
		};
		return out;
	return out;
}

uz_9ph_abc_t step_controllers_PIR_PIR(DS_Data* Data, struct pointers_PIR_PIR objects){
	// Park transform subsystems
	subspace_park_transform(Data);

	// step controllers
	uz_3ph_dq_t dq_ref = step_dq_res(objects.PI_dq, objects.RES_dq, Data);
	uz_3ph_dq_t xy1_ref = step_dq_res(objects.PI_xy1, objects.RES_xy1, Data);
	uz_3ph_dq_t xy2_ref = step_dq_res(objects.PI_xy2, objects.RES_xy2, Data);
	uz_3ph_dq_t xy3_ref = step_dq_res(objects.PI_xy3, objects.RES_xy3, Data);

	// inverse Park transform subsystems
	uz_3ph_alphabeta_t XY1_ref = uz_transformation_3ph_dq_to_alphabeta(xy1_ref, 3.0f*Data->av.rotational_position.position_el_2pi - PHASE_PSI_PM_3);
	uz_3ph_alphabeta_t XY2_ref = uz_transformation_3ph_dq_to_alphabeta(xy2_ref, 5.0f*Data->av.rotational_position.position_el_2pi - PHASE_PSI_PM_5);
	uz_3ph_alphabeta_t XY3_ref = uz_transformation_3ph_dq_to_alphabeta(xy3_ref, 7.0f*Data->av.rotational_position.position_el_2pi - PHASE_PSI_PM_7);

	// out
	uz_9ph_dq_t out_dq = {
		.d = dq_ref.d,
		.q = dq_ref.q,
		.x1 = XY1_ref.alpha,
		.y1 = XY1_ref.beta,
		.x2 = XY2_ref.alpha,
		.y2 = XY2_ref.beta,
		.x3 = XY3_ref.alpha,
		.y3 = XY3_ref.beta,
		.zero = 0.0f};
	return uz_transformation_9ph_dq_to_abc(out_dq, Data->av.rotational_position.position_el_2pi);
}

void reset_controllers_PIR_PIR(struct pointers_PIR_PIR objects){
	uz_CurrentControl_reset(objects.RES_dq);
	uz_subspace_resonant_control_reset(objects.RES_xy1);
	uz_subspace_resonant_control_reset(objects.RES_xy2);
	uz_subspace_resonant_control_reset(objects.RES_xy3);
	uz_CurrentControl_reset(objects.PI_dq);
	uz_CurrentControl_reset(objects.PI_xy1);
	uz_CurrentControl_reset(objects.PI_xy2);
	uz_CurrentControl_reset(objects.PI_xy3);
}
