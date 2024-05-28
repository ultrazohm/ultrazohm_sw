#include "../../main.h"

float Limitation_saftey_factor = 0.707106781f; //To represent the saftey factor from simulation

struct uz_PI_Controller_config config_id = {
        		.Kp = 0.4172f,
        		.Ki = 214.33f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iq = {
        		.Kp = 0.4198f,
        	    .Ki = 214.33f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_ix = {
        		.Kp = 0.1312f,
        		.Ki = 214.33f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iy = {
        		.Kp = 0.1162f,
        	    .Ki = 214.33f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PMSM_t pmsm_config_dq = {
        		.Ld_Henry = 0.00012516f,
        	    .Lq_Henry = 0.00012595f,
        	    .Psi_PM_Vs = 0.0047f,
        	    .R_ph_Ohm = 0.0643f,
        	    .polePairs = 5.0f
        	};

uz_CurrentControl_t* init_xy_FOC(void) {
	struct uz_CurrentControl_config CC_xy_config = {
	    .decoupling_select = no_decoupling,
	    .config_id = config_ix,
	    .config_iq = config_iy,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor
	};
	return(uz_CurrentControl_init(CC_xy_config));

}

uz_CurrentControl_t* init_dq_FOC(void) {
	struct uz_CurrentControl_config CC_dq_config = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_id,
	    .config_iq = config_iq,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_dq
	};
	return(uz_CurrentControl_init(CC_dq_config));
}

