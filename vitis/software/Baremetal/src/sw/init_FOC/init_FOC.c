#include "../../main.h"
extern DS_Data Global_Data;
float Limitation_saftey_factor = 0.8f; //To represent the saftey factor from simulation


#if DEPENGINE==1
struct uz_PI_Controller_config config_id = {
        		.Kp = 5.0f,//5.8f,//5.0f
        		.Ki = 1000.0f,//900.0f,//1000.0f
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iq = {
        		.Kp = 5.0f,//12.67f,//5.0f
        	    .Ki = 1000.0f,900.0f,//1000.0f
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_ix = {
        		.Kp = 15.0f,//9.33f,//15.0f
        		.Ki = 500.0f,//900.0f,//500.0f
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iy = {
        		.Kp = 15.0f,//8.83f,//15.0f
        	    .Ki = 500.0f,900.0f,//500.0f
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PMSM_t pmsm_config_dq = {
        		.Ld_Henry = 0.00174f,
        	    .Lq_Henry = 0.0038f,
        	    .Psi_PM_Vs = 0.194f,
        	    .R_ph_Ohm = 0.27f,
        	    .polePairs = 5.0f
        	};
#endif


#if HEIDRIVE==1
struct uz_PI_Controller_config config_id = {
        		.Kp = 3.767f,
        		.Ki = 1810.0f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iq = {
        		.Kp = 4.733f,
        	    .Ki = 1810.0f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_ix = {
        		.Kp = 4.167f,
        		.Ki = 1810.0f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iy = {
        		.Kp = 4.0f,
        	    .Ki = 1810.0f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PMSM_t pmsm_config_dq = {
        		.Ld_Henry = 0.00113f,
        	    .Lq_Henry = 0.00142f,
        	    .Psi_PM_Vs = 0.0169f,
        	    .R_ph_Ohm = 0.543f,
        	    .polePairs = 3.0f
        	};
#endif

#if BROSE==1
struct uz_PI_Controller_config config_id = {
        		.Kp = 0.491f,
        		.Ki = 426.0f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iq = {
        		.Kp = 0.495f,
        	    .Ki = 426.0f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_ix = {
        		.Kp = 0.186f,
        		.Ki = 426.0f,
        		.samplingTime_sec = 0.0001f,
        	};
        	struct uz_PI_Controller_config config_iy = {
        		.Kp = 0.166f,
        	    .Ki = 426.0f,
        	    .samplingTime_sec = 0.0001f,
        	};
        	struct uz_PMSM_t pmsm_config_dq = {
        		.Ld_Henry = 0.0001473f,
        	    .Lq_Henry = 0.0001484f,
        	    .Psi_PM_Vs = 0.0047f,
        	    .R_ph_Ohm = 0.1278f,
        	    .polePairs = 5.0f
        	};
#endif


void init_FOC(void) {
	struct uz_CurrentControl_config CC_dq_config = {
	    .decoupling_select = no_decoupling,
	    .config_id = config_id,
	    .config_iq = config_iq,
	    .max_modulation_index = (1.0f / sqrtf(3.0f)) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_dq
	};

	struct uz_CurrentControl_config CC_xy_config = {
	    .decoupling_select = no_decoupling,
	    .config_id = config_ix,
	    .config_iq = config_iy,
	    .max_modulation_index = (1.0f / sqrtf(3.0f)) * Limitation_saftey_factor
	};

	Global_Data.objects.CC_dq_instance = uz_CurrentControl_init(CC_dq_config);
	Global_Data.objects.CC_xy_instance = uz_CurrentControl_init(CC_xy_config);

}
