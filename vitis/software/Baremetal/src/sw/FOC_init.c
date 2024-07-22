#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../include/FOC.h"

const struct uz_PMSM_t config_PMSM = {
		.R_ph_Ohm = 0.27f,
		.Ld_Henry = 0.0017f,
		.Lq_Henry = 0.0038f,
		.Psi_PM_Vs = 0.19f,
		.polePairs = 5.0f,
		.I_max_Ampere = 18.0f
};

const struct uz_PI_Controller_config config_id = {
		.Kp = 10.0f, //4.24f
		.Ki = 1500.0f, //159.0f
		.samplingTime_sec = 0.0001f,
		.type = ideal,
		.upper_limit = 326.0f,
		.lower_limit = -326.0f
};

const struct uz_PI_Controller_config config_iq = {
		.Kp = 10.0f, //9.5f
		.Ki = 1500.0f, //71.0f
		.samplingTime_sec = 0.0001f,
		.type = ideal,
		.upper_limit = 326.0f,
		.lower_limit = -326.0f
};

struct uz_CurrentControl_config current_control_config = {
		.config_PMSM = config_PMSM,
		.config_id = config_id,
		.config_iq = config_iq,
		.decoupling_select = no_decoupling
};

uz_CurrentControl_t* init_FOC_CurrentControl() {
	return(uz_CurrentControl_init(current_control_config));
}
