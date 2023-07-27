#include "PI_R.h"
static const uz_3ph_alphabeta_t zero_ref = {0};

// resonant
struct uz_subspace_resonant_control_config resonant_config_XY1 = {
    .sampling_time = SAMPLETIME,
    .gain_1 = PI_R_GAIN_X1,
    .gain_2 = PI_R_GAIN_Y1,
    .harmonic_order = 3.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
struct uz_subspace_resonant_control_config resonant_config_XY2 = {
    .sampling_time = SAMPLETIME,
    .gain_1 = PI_R_GAIN_X2,
    .gain_2 = PI_R_GAIN_Y2,
    .harmonic_order = 5.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
struct uz_subspace_resonant_control_config resonant_config_XY3 = {
    .sampling_time = SAMPLETIME,
    .gain_1 = PI_R_GAIN_X3,
    .gain_2 = PI_R_GAIN_Y3,
    .harmonic_order = 7.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};

uz_subspace_resonant_control* init_PI_R_resonant_XY1(void){
	uz_subspace_resonant_control* ptr = uz_subspace_resonant_control_init(resonant_config_XY1);
	return ptr;
}
uz_subspace_resonant_control* init_PI_R_resonant_XY2(void){
	uz_subspace_resonant_control* ptr = uz_subspace_resonant_control_init(resonant_config_XY2);
	return ptr;
}
uz_subspace_resonant_control* init_PI_R_resonant_XY3(void){
	uz_subspace_resonant_control* ptr = uz_subspace_resonant_control_init(resonant_config_XY3);
	return ptr;
}

uz_9ph_abc_t step_controllers_PI_R(DS_Data* Data, struct pointers_PI_R objects){
	uz_3ph_dq_t dq_ref = uz_CurrentControl_sample(objects.dq, Data->rasv.dq_setpoints, Data->av.currents_dq, Data->av.U_ZK, Data->av.omega_el);
	uz_3ph_alphabeta_t XY1_ref = uz_subspace_resonant_control_step_alphabeta(objects.XY1, zero_ref, Data->av.currents_XY1, Data->av.omega_el);
	uz_3ph_alphabeta_t XY2_ref = uz_subspace_resonant_control_step_alphabeta(objects.XY2, zero_ref, Data->av.currents_XY2, Data->av.omega_el);
	uz_3ph_alphabeta_t XY3_ref = uz_subspace_resonant_control_step_alphabeta(objects.XY3, zero_ref, Data->av.currents_XY3, Data->av.omega_el);

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

void reset_controllers_PI_R(struct pointers_PI_R objects){
	uz_CurrentControl_reset(objects.dq);
	uz_subspace_resonant_control_reset(objects.XY1);
	uz_subspace_resonant_control_reset(objects.XY2);
	uz_subspace_resonant_control_reset(objects.XY3);
}
