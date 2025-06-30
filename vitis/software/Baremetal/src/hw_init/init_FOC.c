#include "../main.h"
extern DS_Data Global_Data;
float Limitation_saftey_factor = 0.707106781f; //To represent the saftey factor from simulation

struct uz_PI_Controller_config config_id_Pruef = {
        		.Kp = 0.4172f,
        		.Ki = 214.33f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iq_Pruef = {
        		.Kp = 0.4198f,
        	    .Ki = 214.33f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_ix_Pruef = {
        		.Kp = 0.1312f,
        		.Ki = 214.33f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iy_Pruef = {
        		.Kp = 0.1162f,
        	    .Ki = 214.33f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PMSM_t pmsm_config_dq = {
        		.Ld_Henry = 0.000588604f,
        	    .Lq_Henry = 0.000801443f,
        	    .Psi_PM_Vs = 0.01427f,
        	    .R_ph_Ohm = 0.2f,
        	    .polePairs = 5.0f
        	};

        	struct uz_PI_Controller_config config_id_Last = {
        	        .Kp = 0.4172f,
        	        .Ki = 214.33f,
        	        .samplingTime_sec = 0.0001f,
        	        	};
        	struct uz_PI_Controller_config config_iq_Last = {
        	        .Kp = 0.4198f,
        	        .Ki = 214.33f,
        	        .samplingTime_sec = 0.0001f,
        	        	};


uz_CurrentControl_t* init_xy_FOC_Pruef(void) {
	struct uz_CurrentControl_config CC_xy_config_Pruef = {
	    .decoupling_select = no_decoupling,
	    .config_id = config_ix_Pruef,
	    .config_iq = config_iy_Pruef,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor
	};
	return(uz_CurrentControl_init(CC_xy_config_Pruef));

}

uz_CurrentControl_t* init_dq_FOC_Pruef(void) {
	struct uz_CurrentControl_config CC_dq_config_Pruef = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_id_Pruef,
	    .config_iq = config_iq_Pruef,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_dq
	};
	return(uz_CurrentControl_init(CC_dq_config_Pruef));
}
uz_CurrentControl_t* init_dq_FOC_Last(void) {
	struct uz_CurrentControl_config CC_dq_config_Last = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_id_Last,
	    .config_iq = config_iq_Last,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_dq
	};
	return(uz_CurrentControl_init(CC_dq_config_Last));
}
//uz_pmsm_model6ph_dq_t* init_CIL_6ph_PMSM(void) {
//	return(uz_pmsm_model6ph_dq_init(pmsm_CIL_config));
//}







