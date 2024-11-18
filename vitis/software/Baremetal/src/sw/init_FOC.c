#include "../include/init_FOC.h"
#include <math.h>
struct uz_pmsmModel_config_t pmsm_config={
  .base_address=XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
  .ip_core_frequency_Hz=100000000,
    .simulate_mechanical_system = false,
	.simulate_nonlinear = false,
    .r_1 = 0.27f,
    .L_d = 0.00049f,
    .L_q = 0.0021f,
    .psi_pm = 0.0195f,
    .polepairs = 4.0f,
    .inertia = 0.001,
    .coulomb_friction_constant = 0.01f,
    .friction_coefficient = 0.001f};

struct uz_PMSM_flux_fitting_parameter_config_t fitting_config = {
			.ad1_parameter = 0.030483840951002f,
			.ad2_parameter = 0.040244227373267f,
            .ad3_parameter = -16.481195185733903f,
			.ad4_parameter = 1.296438633344970f,
			.ad5_parameter = 6.183163374457993e-04f,
			.ad6_parameter = -12.275586044862504f,
			.aq1_parameter = 0.004816670542863f,
			.aq2_parameter = 0.171595254784258f,
			.aq3_parameter = 9.262938633610718e-04f,
			.aq4_parameter = 0.005001870975338f,
			.aq5_parameter = 0.170521235710151f,
			.aq6_parameter = 9.186084507499523e-04f,
			.F1G1_parameter = -0.001356794026337f,
			.F2G2_parameter = 0.078813850391713f

};

struct uz_PMSM_t config_PMSM = {
      .Ld_Henry = 0.00049f,
      .Lq_Henry = 0.0021f,
      .Psi_PM_Vs = 0.0195f
};//these parameters are only needed if linear decoupling is selected

struct uz_PI_Controller_config config_id = {
      .Kp = 2.45f,
      .Ki = 1350.0f,
      .samplingTime_sec = 0.0001f
};

struct uz_PI_Controller_config config_iq = {
      .Kp = 10.5f,
      .Ki = 1350.0f,
      .samplingTime_sec = 0.0001f
};



uz_pmsmModel_t * uz_init_pmsm_model(void) {
	return(uz_pmsmModel_init(pmsm_config));
}

uz_approximate_flux_t* uz_init_approximate_flux(void) {
	return(uz_approximate_flux_init(fitting_config));
}

uz_CurrentControl_t* uz_init_CC(void) {
	struct uz_CurrentControl_config CC_config = {
	      .decoupling_select = linear_decoupling,
	      .config_PMSM = config_PMSM,
	      .config_id = config_id,
	      .config_iq = config_iq,
	      .max_modulation_index = 1.0f / sqrtf(3.0f)
	};
	return(uz_CurrentControl_init(CC_config));
}
