#include "../main.h"
extern DS_Data Global_Data;


static const struct uz_PMSM_t SynRM_config = {
        .Ld_Henry = 0.021f,
        .Lq_Henry = 0.0014f,
        .Psi_PM_Vs = 0.0f,
		.I_max_Ampere = 80.0f,
		.R_ph_Ohm = 0.0555f,
        .polePairs = 2.0f,
		.M_rated_Nm = 95.5f,
		.I_rated_Ampere = 66.0f,
		.n_rated_rpm = 2300.0f,

        };

static const struct uz_PMSM_flux_fitting_parameter_config_t fitting_parameter = {
		.ad1_parameter = 0.782989081743603f,
		.ad2_parameter = 0.036743796432364f,
		.ad3_parameter = 0.030581766186054f,
		.ad4_parameter = 0.792326765531242f,
		.ad5_parameter = 0.032425308612038f,
		.ad6_parameter = 0.032333635046391f,
		.aq1_parameter = 0.024334722246215f,
		.aq2_parameter = 0.999999915866979f,
		.aq3_parameter = 0.001825546424756f,
		.aq4_parameter = 0.007795446741636f,
		.aq5_parameter = 0.150130363856926f,
		.aq6_parameter = 0.001627574058652f,
		.F1G1_parameter = 1.367830576025495f,
		.F2G2_parameter = 1.368910728161520f
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
static float LUT_breakpoints_array[11] = {
#include "LUT_Breakpoints.csv"
};
static float LUT_CIL_current_angle_array[11] = {
#include "LUT_CIL_current_angle.csv"
};
static float LUT_CIL_Is_array[11] = {
#include "LUT_CIL_Is.csv"
};
static float LUT_bench_current_angle_array[11] = {
#include "LUT_bench_current_angle.csv"
};
static float LUT_bench_Is_array[11] = {
#include "LUT_bench_Is.csv"
};

//Create uz_arrays
uz_array_float_t LUT_breakpoints = {
		.length = UZ_ARRAY_SIZE(LUT_breakpoints_array),
		.data = &LUT_breakpoints_array[0]
};
uz_array_float_t LUT_CIL_current_angle = {
		.length = UZ_ARRAY_SIZE(LUT_CIL_current_angle_array),
		.data = &LUT_CIL_current_angle_array[0]
};
uz_array_float_t LUT_CIL_Is = {
		.length = UZ_ARRAY_SIZE(LUT_CIL_Is_array),
		.data = &LUT_CIL_Is_array[0]
};
uz_array_float_t LUT_bench_current_angle = {
		.length = UZ_ARRAY_SIZE(LUT_bench_current_angle_array),
		.data = &LUT_bench_current_angle_array[0]
};
uz_array_float_t LUT_bench_Is = {
		.length = UZ_ARRAY_SIZE(LUT_bench_Is_array),
		.data = &LUT_bench_Is_array[0]
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

uz_LUT_1D_t* init_LUT_CIL_current_angle(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_CIL_current_angle, 11U));
}

uz_LUT_1D_t* init_LUT_CIL_Is(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_bench_Is, 11U));
}

uz_LUT_1D_t* init_LUT_bench_current_angle(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_bench_current_angle, 11U));
}
uz_LUT_1D_t* init_LUT_bench_Is(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_bench_Is, 11U));
}


