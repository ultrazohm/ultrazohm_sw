#include "../include/uz_controller_and_converter_init.h"
#include "../uz/uz_global_configuration.h"

#define SAMPLE_TIME_SEC_CURRENT_CONTROL   1.0f/UZ_ISR_FREQUENCY
#define SAMPLE_TIME_SEC_SPEED_CONTROL     (SAMPLE_TIME_SEC_CURRENT_CONTROL)
//#define LIMITATION_SAFETY_FACTOR 0.707106781186f   //(1/sqrtf(2.0f))
#define TAU_SIGMA (1.5f * SAMPLE_TIME_SEC_CURRENT_CONTROL)

static const struct uz_IIR_Filter_config speed_prefilter_Last_config;
static const struct uz_IIR_Filter_config speed_prefilter_Pruef_config;
static const struct uz_SpeedControl_config speed_control_Last_config;
static const struct uz_SpeedControl_config speed_control_Pruef_config;
static const struct uz_CurrentControl_config current_control_Last_config;
static const struct uz_CurrentControl_config current_control_dq_Pruef_config;
static const struct uz_CurrentControl_config current_control_xy_Pruef_config;
static const struct uz_SetPoint_config torque_to_current_converter_Last_config;
static const struct uz_SetPoint_config torque_to_current_converter_Pruef_config;


struct uz_IIR_Filter_t* uz_speed_prefilter_Last_init(void) {
	return (uz_signals_IIR_Filter_init(speed_prefilter_Last_config));
}

struct uz_IIR_Filter_t* uz_speed_prefilter_Pruef_init(void) {
	return (uz_signals_IIR_Filter_init(speed_prefilter_Pruef_config));
}

struct uz_SpeedControl_t* uz_speed_control_Last_init(void) {
	return (uz_SpeedControl_init(speed_control_Last_config));
}

struct uz_SpeedControl_t* uz_speed_control_Pruef_init(void) {
	return (uz_SpeedControl_init(speed_control_Pruef_config));
}
struct uz_CurrentControl_t* uz_current_control_Last_init(void) {
	return (uz_CurrentControl_init(current_control_Last_config));
}

struct uz_CurrentControl_t* uz_current_control_dq_Pruef_init(void) {
	return (uz_CurrentControl_init(current_control_dq_Pruef_config));
}

struct uz_CurrentControl_t* uz_current_control_xy_Pruef_init(void) {
	return (uz_CurrentControl_init(current_control_xy_Pruef_config));
}

struct uz_SetPoint_t* uz_torque_to_current_converter_Last_init(void) {
	return (uz_SetPoint_init(torque_to_current_converter_Last_config));
}

struct uz_SetPoint_t* uz_torque_to_current_converter_Pruef_init(void) {
	return (uz_SetPoint_init(torque_to_current_converter_Pruef_config));
}


static const struct uz_PMSM_t config_PMSM_Last = {
	//these parameters are only needed if linear decoupling is selected
	.Ld_Henry = 0.00058f,//0.000588604f,
	.Lq_Henry = 0.00071f,// 0.000801443f,
	.Psi_PM_Vs = 0.0143f,
	.I_max_Ampere = 30.0f, // max Ampere peak
	.R_ph_Ohm = 0.1f,
	.polePairs = 5.0f,
};

static const struct uz_PMSM_t config_PMSM_Pruef = {
	//these parameters are only needed if linear decoupling is selected
	.Ld_Henry = 0.00058f,//0.000588604f,
	.Lq_Henry = 0.00071f,//0.000801443f,
	.Psi_PM_Vs = 0.0143f,
	.I_max_Ampere = 15.0f, // max Ampere peak
	.R_ph_Ohm = 0.2f,
	.polePairs = 5.0f,
};

static const struct uz_PI_Controller_config config_id_Last = {
	.Kp = config_PMSM_Last.Ld_Henry / (2*TAU_SIGMA), // = 1,96201 //0.4172f,
	.Ki = config_PMSM_Last.R_ph_Ohm / (2*TAU_SIGMA), // = 333,33 //214.33f,
	.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
};

static const struct uz_PI_Controller_config config_iq_Last = {
	.Kp = config_PMSM_Last.Lq_Henry / (2*TAU_SIGMA), // = 2,67148 //0.4198f,
	.Ki = config_PMSM_Last.R_ph_Ohm / (2*TAU_SIGMA), // = 333,33 //214.33f,
	.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
};

static const struct uz_PI_Controller_config config_id_Pruef = {
	.Kp = config_PMSM_Pruef.Ld_Henry / (2*TAU_SIGMA), // = 1,96201 //0.4172f,
	.Ki = config_PMSM_Pruef.R_ph_Ohm / (2*TAU_SIGMA), // = 666,67 //214.33f,
	.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
};

static const struct uz_PI_Controller_config config_iq_Pruef = {
	.Kp = config_PMSM_Pruef.Lq_Henry / (2*TAU_SIGMA), // = 2,67148 //0.4198f,
	.Ki = config_PMSM_Pruef.R_ph_Ohm / (2*TAU_SIGMA), // = 666,67 //214.33f,
	.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
};

static const struct uz_PI_Controller_config config_ix_Pruef = {
	.Kp = 0.1312f,
	.Ki = 214.33f,
	.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
};

static const struct uz_PI_Controller_config config_iy_Pruef = {
	.Kp = 0.1162f,
	.Ki = 214.33f,
	.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
};

static const struct uz_IIR_Filter_config speed_prefilter_Last_config = {
	.selection = LowPass_first_order,
	.cutoff_frequency_Hz = 10.0f,
	.sample_frequency_Hz = UZ_ISR_FREQUENCY
};

static const struct uz_IIR_Filter_config speed_prefilter_Pruef_config = {
	.selection = LowPass_first_order,
	.cutoff_frequency_Hz = 10.0f,
	.sample_frequency_Hz = UZ_ISR_FREQUENCY
};

static const struct uz_SpeedControl_config speed_control_Last_config = {
	.config_controller.Kp = 0.07f,//0.01f,
	.config_controller.Ki = 16.6667f,
	.config_controller.samplingTime_sec = SAMPLE_TIME_SEC_SPEED_CONTROL,
	.config_controller.upper_limit = 2.4f,
	.config_controller.lower_limit = -2.4f,
	.config_controller.type = UZ_PI_IDEAL,
};

static const struct uz_SpeedControl_config speed_control_Pruef_config = {
	.config_controller.Kp = 0.07f,//0.01f,
	.config_controller.Ki = 16.6667f,
	.config_controller.samplingTime_sec = SAMPLE_TIME_SEC_SPEED_CONTROL,
	.config_controller.upper_limit = 2.4f,
	.config_controller.lower_limit = -2.4f,
	.config_controller.type = UZ_PI_IDEAL,
};

static const struct uz_SetPoint_config torque_to_current_converter_Last_config = {
	.config_PMSM = config_PMSM_Last,
	.control_type = FOC,
	.motor_type = IPMSM,
	.is_field_weakening_enabled = false,
	.id_ref_Ampere = 0.0f,
	.relative_torque_tolerance = 0.001f,
};

static const struct uz_SetPoint_config torque_to_current_converter_Pruef_config = {
	.config_PMSM = config_PMSM_Pruef,
	.control_type = FOC,
	.motor_type = IPMSM,
	.is_field_weakening_enabled = false,
	.id_ref_Ampere = 0.0f,
	.relative_torque_tolerance = 0.001f,
};

static const struct uz_CurrentControl_config current_control_Last_config = {
	.decoupling_select = no_decoupling, // linear_decoupling
	.Kp_adjustment_flag = false,
	.config_PMSM = config_PMSM_Last,
	.config_id = config_id_Last,
	.config_iq = config_iq_Last,
	.max_modulation_index = 0.5f,
};

static const struct uz_CurrentControl_config current_control_dq_Pruef_config = {
	.decoupling_select = no_decoupling, // linear_decoupling
	.Kp_adjustment_flag = false,
	.config_PMSM = config_PMSM_Pruef,
	.config_id = config_id_Pruef,
	.config_iq = config_iq_Pruef,
	.max_modulation_index = 0.5f,
};

static const struct uz_CurrentControl_config current_control_xy_Pruef_config = {
	.decoupling_select = no_decoupling,
	.Kp_adjustment_flag = false,
	.config_PMSM = config_PMSM_Pruef,
	.config_id = config_ix_Pruef,
	.config_iq = config_iy_Pruef,
	.max_modulation_index = 0.5f,
};




