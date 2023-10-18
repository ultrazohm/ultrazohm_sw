#include "init_ParaID_6ph.h"

// Para ID
uz_ParameterID_Data_t ParaID_Data = { 0 };
//float meas_array[10000];  // voltage measurement
extern uz_6ph_dq_t controller_out;

uz_ParameterID_6ph_t* init_ParaID_6ph_wrapper(void){
	return uz_ParameterID_6ph_init(&ParaID_Data);
}

// Para ID Controller
const struct uz_PI_Controller_config PI_config_d = {
		.Ki = 40.0f,
		.Kp = 0.1f,
		.samplingTime_sec = UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE};
const struct uz_PI_Controller_config PI_config_q = {
		.Ki = 45.0f,
		.Kp = 0.1f,
		.samplingTime_sec = UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE};
const struct uz_PI_Controller_config PI_config_x = {
		.Ki = 40.0f,
		.Kp = 0.05f,
		.samplingTime_sec = UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE};
const struct uz_PI_Controller_config PI_config_y = {
		.Ki = 45.0f,
		.Kp = 0.05f,
		.samplingTime_sec = UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE};
struct uz_CurrentControl_config cc_config_dq = {
		.decoupling_select = linear_decoupling,
		.config_id = PI_config_d,
		.config_iq = PI_config_q,
		.max_modulation_index = 0.5f};
struct uz_CurrentControl_config cc_config_xy_z = {
		.decoupling_select = no_decoupling,
		.config_id = PI_config_x,
		.config_iq = PI_config_y,
		.max_modulation_index = 0.5f};
struct uz_subspace_resonant_control_config resonant_dq = {
		.antiwindup_gain = 10.0f,
		.gain_1 = 50.0f,
		.gain_2 = 50.0f,
		.harmonic_order = 2.0f,
		.lower_limit = -10.0f,
		.upper_limit = 10.0f,
		.sampling_time = UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE};
struct uz_subspace_resonant_control_config resonant_xy = {
		.antiwindup_gain = 10.0f,
		.gain_1 = 200.0f,
		.gain_2 = 200.0f,
		.harmonic_order = 6.0f,
		.lower_limit = -10.0f,
		.upper_limit = 10.0f,
		.sampling_time = UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE};
struct uz_subspace_resonant_control_config resonant_zero = {
		.antiwindup_gain = 10.0f,
		.gain_1 = 50.0f,
		.gain_2 = 50.0f,
		.harmonic_order = 6.0f,
		.lower_limit = -10.0f,
		.upper_limit = 10.0f,
		.sampling_time = UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE};
struct uz_SpeedControl_config speed_config = {
		.config_controller.type = parallel,
		.config_controller.Kp = 1.0f,
		.config_controller.Ki = 1.0f,
		.config_controller.samplingTime_sec =  UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE,
		.config_controller.upper_limit = 10.0f,
		.config_controller.lower_limit = -10.0f };
struct uz_SetPoint_config sp_config = {
		.id_ref_Ampere = 0.0f,
		.is_field_weakening_enabled = false,
		.motor_type = SMPMSM,
		.control_type = FOC
};
struct uz_ParameterID_controller init_ParaID_6ph_controller(void){
	cc_config_dq.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config;
	sp_config.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config;
	struct uz_ParameterID_controller out = {
			.CC_instance_dq = uz_CurrentControl_init(cc_config_dq),
			.CC_instance_xy = uz_CurrentControl_init(cc_config_xy_z),
			.CC_instance_zero = uz_CurrentControl_init(cc_config_xy_z),
			.res_instance_dq = uz_subspace_resonant_control_init(resonant_dq),
			.res_instance_xy = uz_subspace_resonant_control_init(resonant_xy),
			.res_instance_zero = uz_subspace_resonant_control_init(resonant_zero),
			.SP_instance = uz_SetPoint_init(sp_config),
			.SC_instance = uz_SpeedControl_init(speed_config)
	};
	return out;
}

// other
//void init_ParaID_6ph_misc(void){
//	uz_ParameterID_6ph_initialize_filter(&ParaID_Data, UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE);
//	uz_ParameterID_6ph_initialize_encoder_offset_estimation(&ParaID_Data, &controller_out.q);
//}

//void ParaID_calc_PsiPMs_wrapper(uz_ParameterID_6ph_t* self){
////	uz_ParameterID_6ph_calculate_PsiPMs(self, &ParaID_Data, meas_array);
//}
