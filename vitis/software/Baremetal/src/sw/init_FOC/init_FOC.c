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
        	struct uz_pmsm_model6ph_dq_config_t pmsm_CIL_config = {
        			.base_address = XPAR_UZ_USER_PMSM_CIL_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
        			.ip_core_frequency_Hz = 100000000U,
        			.polepairs = 5.0f,
        			.r_1 = 0.27f,
        			.inductance.d = 0.00174f,
        			.inductance.q = 0.0038f,
        			.inductance.x = 0.0028f,
        			.inductance.y = 0.00265f,
        			.inductance.z1 = 0.00153f,
        			.inductance.z2 = 0.00120f,
        			.psi_pm = 0.194f,
        			.friction_coefficient = 0.001f,
        			.coulomb_friction_constant = 0.001f,
        			.inertia = 0.001f,
        			.simulate_mechanical_system = false,
        			.switch_pspl = true
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
        	struct uz_pmsm_model6ph_dq_config_t pmsm_CIL_config = {
        			.base_address = XPAR_UZ_USER_PMSM_CIL_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
        			.ip_core_frequency_Hz = 100000000U,
        			.polepairs = 3.0f,
        			.r_1 = 0.543f,
        			.inductance.d = 0.00113f,
        			.inductance.q = 0.00142f,
        			.inductance.x = 0.00125f,
        			.inductance.y = 0.0012f,
        			.inductance.z1 = 0.00153f,
        			.inductance.z2 = 0.00120f,
        			.psi_pm = 0.0169f,
        			.friction_coefficient = 0.001f,
        			.coulomb_friction_constant = 0.001f,
        			.inertia = 0.001f,
        			.simulate_mechanical_system = false,
        			.switch_pspl = true
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
        	struct uz_pmsm_model6ph_dq_config_t pmsm_CIL_config = {
        			.base_address = XPAR_UZ_USER_PMSM_CIL_UZ_PMSM_MODEL_6PH_DQ_0_BASEADDR,
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

void init_CIL_6ph_PMSM(void) {
	Global_Data.objects.CIL_pmsm = uz_pmsm_model6ph_dq_init(pmsm_CIL_config);
}
