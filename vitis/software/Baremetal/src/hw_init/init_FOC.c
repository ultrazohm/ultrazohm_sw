#include "../main.h"
extern DS_Data Global_Data;


static const struct uz_PMSM_t SynRM_config = {
        .Ld_Henry = 0.00025f,
        .Lq_Henry = 0.0001f,
        .Psi_PM_Vs = 0.0f,
		.I_max_Ampere = 150.0f,
		.R_ph_Ohm = 0.0216f,
        .polePairs = 2.0f,
		.M_rated_Nm = 2.5f,
		.I_rated_Ampere = 100.0f,
		.n_rated_rpm = 6000.0f,
		.V_DC_Volts = 48.0f
        };

static const struct uz_PMSM_flux_fitting_parameter_config_t fitting_parameter = {
		.ad1_parameter = 0.021844678923593f,
		.ad2_parameter = 0.015691946267988f,
		.ad3_parameter = 2.774655647742554f,
		.ad4_parameter = 0.021452939521217f,
		.ad5_parameter = 0.012851474250756f,
		.ad6_parameter = 2.544082676540874f,
		.aq1_parameter = 0.002055465770391f,
		.aq2_parameter = 0.060293284387075f,
		.aq3_parameter = 4.427388728224799e-05f,
		.aq4_parameter = 6.984208751521990e-04f,
		.aq5_parameter = 0.049312248321942f,
		.aq6_parameter = 4.146443160651400e-05f,
		.F1G1_parameter = 0.221350145237161f,
		.F2G2_parameter = 0.221214979405608f
};

struct uz_pmsmModel_config_t IP_SynRM_config = {
		.base_address = XPAR_UZ_PMSM_MODEL_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000U,
		.simulate_mechanical_system = false,
		.simulate_nonlinear = true,
		.r_1 = SynRM_config.R_ph_Ohm,
		.L_d = SynRM_config.Ld_Henry,
		.L_q = SynRM_config.Lq_Henry,
		.psi_pm = SynRM_config.Psi_PM_Vs,
		.polepairs = SynRM_config.polePairs,
		.coulomb_friction_constant = 0.01f,
		.friction_coefficient = 0.001f,
		.inertia = 0.001f,
		.ad1 = fitting_parameter.ad1_parameter,
		.ad2 = fitting_parameter.ad2_parameter,
		.ad3 = fitting_parameter.ad3_parameter,
		.ad4 = fitting_parameter.ad4_parameter,
		.ad5 = fitting_parameter.ad5_parameter,
		.ad6 = fitting_parameter.ad6_parameter,
		.aq1 = fitting_parameter.aq1_parameter,
		.aq2 = fitting_parameter.aq2_parameter,
		.aq3 = fitting_parameter.aq3_parameter,
		.aq4 = fitting_parameter.aq4_parameter,
		.aq5 = fitting_parameter.aq5_parameter,
		.aq6 = fitting_parameter.aq6_parameter,
		.F1G1 = fitting_parameter.F1G1_parameter,
		.F2G2 = fitting_parameter.F2G2_parameter
};

struct uz_PI_Controller_config config_id = {
		.Kp = SynRM_config.Ld_Henry / (2.0f * TAU_SIGMA),
		.Ki = SynRM_config.R_ph_Ohm / (2.0f * TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
		.type = UZ_PI_PARALLEL
};

struct uz_PI_Controller_config config_iq = {
		.Kp = SynRM_config.Lq_Henry / (2.0f * TAU_SIGMA),
		.Ki = SynRM_config.R_ph_Ohm / (2.0f * TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
		.type = UZ_PI_PARALLEL
};



//Arrays for LUTs
static float LUT_breakpoints_array[26] = {
#include "LUT_Breakpoints.csv"
};
static float LUT_CIL_id_array[26] = {
#include "LUT_CIL_id.csv"
};
static float LUT_CIL_iq_array[26] = {
#include "LUT_CIL_iq.csv"
};

//Create uz_arrays
uz_array_float_t LUT_breakpoints = {
		.length = UZ_ARRAY_SIZE(LUT_breakpoints_array),
		.data = &LUT_breakpoints_array[0]
};
uz_array_float_t LUT_CIL_id = {
		.length = UZ_ARRAY_SIZE(LUT_CIL_id_array),
		.data = &LUT_CIL_id_array[0]
};
uz_array_float_t LUT_CIL_iq = {
		.length = UZ_ARRAY_SIZE(LUT_CIL_iq_array),
		.data = &LUT_CIL_iq_array[0]
};

uz_CurrentControl_t* init_FOC(void) {
	struct uz_CurrentControl_config CC_config = {
			.decoupling_select = static_nonlinear_decoupling,
			.config_id = config_id,
			.config_iq = config_iq,
			.config_PMSM = SynRM_config,
			.Kp_adjustment_flag = true,
			.max_modulation_index = 1.0f/sqrt(3.0f)
	};
	Global_Data.av.SynRM_config = SynRM_config;
	return(uz_CurrentControl_init(CC_config));
}

uz_pmsmModel_t* init_pmsmModel(void) {
	return(uz_pmsmModel_init(IP_SynRM_config));
}

uz_approximate_flux_t* init_FluxApproximation(void) {
	Global_Data.av.fitting_parameter = fitting_parameter;
	return(uz_approximate_flux_init(fitting_parameter));
}

uz_LUT_1D_t* init_LUT_CIL_id(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_CIL_id, 26U));
}

uz_LUT_1D_t* init_LUT_CIL_iq(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_CIL_iq, 26U));
}


