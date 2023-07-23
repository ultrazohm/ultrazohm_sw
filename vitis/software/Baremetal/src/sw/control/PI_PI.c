#include "PI_PI.h"
static const uz_3ph_dq_t zero_ref = {0};;

///xy1///
const struct uz_PI_Controller_config config_x1 = {
	.type = parallel,
	.Kp = PI_PI_KP_X1,
	.Ki = PI_PI_KI_X1,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = ADDITIONAL_SYSTEM_LIMIT,
	.lower_limit = -ADDITIONAL_SYSTEM_LIMIT};
const struct uz_PI_Controller_config config_y1 = {
	.type = parallel,
	.Kp = PI_PI_KP_Y1,
	.Ki = PI_PI_KI_Y1,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = ADDITIONAL_SYSTEM_LIMIT,
	.lower_limit = -ADDITIONAL_SYSTEM_LIMIT};
struct uz_CurrentControl_config cc_config_xy1 = {
	.config_id = config_x1,
	.config_iq = config_y1,
	.decoupling_select = no_decoupling,
	.max_modulation_index = MODULATION_INDEX};

///xy2///
const struct uz_PI_Controller_config config_x2 = {
	.type = parallel,
	.Kp = PI_PI_KP_X2,
	.Ki = PI_PI_KI_X2,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = ADDITIONAL_SYSTEM_LIMIT,
	.lower_limit = -ADDITIONAL_SYSTEM_LIMIT};
const struct uz_PI_Controller_config config_y2 = {
	.type = parallel,
	.Kp = PI_PI_KP_Y2,
	.Ki = PI_PI_KI_Y2,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = ADDITIONAL_SYSTEM_LIMIT,
	.lower_limit = -ADDITIONAL_SYSTEM_LIMIT};
struct uz_CurrentControl_config cc_config_xy2 = {
	.config_id = config_x2,
	.config_iq = config_y2,
	.decoupling_select = no_decoupling,
	.max_modulation_index = MODULATION_INDEX};

///xy3///
const struct uz_PI_Controller_config config_x3 = {
	.type = parallel,
	.Kp = PI_PI_KP_X3,
	.Ki = PI_PI_KI_X3,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = ADDITIONAL_SYSTEM_LIMIT,
	.lower_limit = -ADDITIONAL_SYSTEM_LIMIT};
const struct uz_PI_Controller_config config_y3 = {
	.type = parallel,
	.Kp = PI_PI_KP_Y3,
	.Ki = PI_PI_KI_Y3,
	.samplingTime_sec = SAMPLETIME,
	.upper_limit = ADDITIONAL_SYSTEM_LIMIT,
	.lower_limit = -ADDITIONAL_SYSTEM_LIMIT};
struct uz_CurrentControl_config cc_config_xy3 = {
	.config_id = config_x3,
	.config_iq = config_y3,
	.decoupling_select = no_decoupling,
	.max_modulation_index = MODULATION_INDEX};


// init functions
uz_CurrentControl_t* init_PI_PI_cc_xy1(void){
	uz_CurrentControl_t* ptr = uz_CurrentControl_init(cc_config_xy1);
	return ptr;
}
uz_CurrentControl_t* init_PI_PI_cc_xy2(void){
	uz_CurrentControl_t* ptr = uz_CurrentControl_init(cc_config_xy2);
	return ptr;
}
uz_CurrentControl_t* init_PI_PI_cc_xy3(void){
	uz_CurrentControl_t* ptr = uz_CurrentControl_init(cc_config_xy3);
	return ptr;
}

uz_9ph_abc_t step_controllers_PI_PI(DS_Data* Data, struct pointers_PI_PI objects){
	// Park transform subsystems
	subspace_park_transform(Data);

	// step controllers
	uz_3ph_dq_t dq_ref = uz_CurrentControl_sample(objects.dq, Data->rasv.dq_setpoints, Data->av.currents_dq, Data->av.U_ZK, Data->av.omega_el);
	uz_3ph_dq_t xy1_ref = uz_CurrentControl_sample(objects.xy1, zero_ref, Data->av.currents_xy1, Data->av.U_ZK, Data->av.omega_el);
	uz_3ph_dq_t xy2_ref = uz_CurrentControl_sample(objects.xy2, zero_ref, Data->av.currents_xy2, Data->av.U_ZK, Data->av.omega_el);
	uz_3ph_dq_t xy3_ref = uz_CurrentControl_sample(objects.xy3, zero_ref, Data->av.currents_xy3, Data->av.U_ZK, Data->av.omega_el);

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

void reset_controllers_PI_PI(struct pointers_PI_PI objects){
	uz_CurrentControl_reset(objects.dq);
	uz_CurrentControl_reset(objects.xy1);
	uz_CurrentControl_reset(objects.xy2);
	uz_CurrentControl_reset(objects.xy3);
}

