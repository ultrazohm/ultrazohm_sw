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

        	const struct uz_PMSM_6ph_t pmsm_6ph_config = {
        		.Ld_Henry =  0.00012516f,
        		.Lq_Henry = 0.00012595f,
        		.LX_Henry = 0.000039374f,
        		.LY_Henry = 0.000034854f,
        		.Lz1_Henry = 0.0000889f,
        		.Lz2_Henry = 0.0000863f,
        		.Psi_PM_Vs = 0.0047f,
        		.R_ph_Ohm = 0.0643f,
        		.polePairs = 5.0f,
        	};


        	struct uz_PMSM_t pmsm_config_dq = {
        		.Ld_Henry = pmsm_6ph_config.Ld_Henry,
        	    .Lq_Henry = pmsm_6ph_config.Lq_Henry,
        	    .Psi_PM_Vs = pmsm_6ph_config.Psi_PM_Vs,
        	    .R_ph_Ohm = pmsm_6ph_config.R_ph_Ohm,
        	    .polePairs = pmsm_6ph_config.polePairs
        	};

        	struct uz_pmsm_model6ph_dq_config_t pmsm_CIL_config = {
        			.base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
        			.ip_core_frequency_Hz = 100000000U,
        			.polepairs = pmsm_6ph_config.polePairs,
        			.r_1 = pmsm_6ph_config.R_ph_Ohm,
        			.inductance.d = pmsm_6ph_config.Ld_Henry,
        			.inductance.q = pmsm_6ph_config.Lq_Henry,
        			.inductance.x = pmsm_6ph_config.LX_Henry,
        			.inductance.y = pmsm_6ph_config.LY_Henry,
        			.inductance.z1 = pmsm_6ph_config.Lz1_Henry,
        			.inductance.z2 = pmsm_6ph_config.Lz2_Henry,
        			.psi_pm = pmsm_6ph_config.Psi_PM_Vs,
        			.friction_coefficient = 0.001f,
        			.coulomb_friction_constant = 0.001f,
        			.inertia = 0.001f,
        			.simulate_mechanical_system = false,
        			.switch_pspl = true
        	};

void writePMSMValues_globalData(DS_Data* data){
	data->av.pmsm_6ph = pmsm_6ph_config;
}

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

uz_pmsm_model6ph_dq_t* init_CIL_6ph_PMSM(void) {
	return(uz_pmsm_model6ph_dq_init(pmsm_CIL_config));
}
