#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../include/foc.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_global_configuration.h"
#include "../globalData.h"

extern DS_Data Global_Data;

// Machine parameters
const struct uz_PMSM_t config_PMSM = {
		.R_ph_Ohm = 0.27f,
		.Ld_Henry = 0.00324f,
		.Lq_Henry = 0.00338f,
		.Psi_PM_Vs = 0.183f,
		.polePairs = 5.0f,
		.I_max_Ampere = 2.0f*16.0f*sqrt(2.0f)
};

// PI controllers
const struct uz_PI_Controller_config config_id = {
		.Kp = config_PMSM.Ld_Henry/(2.0f*1.0f/UZ_ISR_FREQUENCY),
		.Ki = config_PMSM.R_ph_Ohm/(2.0f*1.0f/UZ_ISR_FREQUENCY),
		.samplingTime_sec = UZ_TIME_ISR,
		.type = parallel,
};

const struct uz_PI_Controller_config config_iq = {
		.Kp = config_PMSM.Ld_Henry/(2.0f*1.0f/UZ_ISR_FREQUENCY),
		.Ki = config_PMSM.R_ph_Ohm/(2.0f*1.0f/UZ_ISR_FREQUENCY),
		.samplingTime_sec = UZ_TIME_ISR,
		.type = parallel,
};

struct uz_CurrentControl_config current_control_config = {
		.config_PMSM = config_PMSM,
		.config_id = config_id,
		.config_iq = config_iq,
		.decoupling_select = no_decoupling,
		.max_modulation_index = 1.0f/sqrt(3.0f)
};


uz_CurrentControl_t* init_FOC_CurrentControl() {
	return(uz_CurrentControl_init(current_control_config));
}
