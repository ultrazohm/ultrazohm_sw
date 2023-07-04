#include "../../main.h"
extern DS_Data Global_Data;
float Limitation_saftey_factor = 0.8f; //To represent the saftey factor from simulation

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
        	struct uz_pmsm_model6ph_dq_config_t pmsm_CIL_config = {
        			.base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
        			.ip_core_frequency_Hz = 100000000U,
        			.polepairs = 5.0f,
        			.r_1 = 0.1278f,
        			.inductance.d = 0.0001473f,
        			.inductance.q = 0.0001484,
        			.inductance.x = 0.0000557f,
        			.inductance.y = 0.0000499f,
        			.inductance.z1 = 0.0000889f,
        			.inductance.z2 = 0.0000863f,
        			.psi_pm = 0.0047f,
        			.friction_coefficient = 0.001f,
        			.coulomb_friction_constant = 0.001f,
        			.inertia = 0.001f,
        			.simulate_mechanical_system = false,
        			.switch_pspl = true
        	};


uz_CurrentControl_t* init_xy_FOC(void) {
	struct uz_CurrentControl_config CC_xy_config = {
	    .decoupling_select = no_decoupling,
	    .config_id = config_ix,
	    .config_iq = config_iy,
	    .max_modulation_index = (1.0f / sqrtf(3.0f)) * Limitation_saftey_factor
	};
	return(uz_CurrentControl_init(CC_xy_config));

}

uz_CurrentControl_t* init_dq_FOC(void) {
	struct uz_CurrentControl_config CC_dq_config = {
	    .decoupling_select = no_decoupling,
	    .config_id = config_id,
	    .config_iq = config_iq,
	    .max_modulation_index = (1.0f / sqrtf(3.0f)) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_dq
	};
	return(uz_CurrentControl_init(CC_dq_config));
}

uz_pmsm_model6ph_dq_t* init_CIL_6ph_PMSM(void) {
	return(uz_pmsm_model6ph_dq_init(pmsm_CIL_config));
}
