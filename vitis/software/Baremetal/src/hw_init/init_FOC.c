#include "../main.h"
extern DS_Data Global_Data;

static const struct uz_PMSM_t PMSM_DUT_config = { //Hoerner Prototyp
        .Ld_Henry = 0.00044f,
        .Lq_Henry = 0.00245f,
        .Psi_PM_Vs = 0.02f,
		.I_max_Ampere = 20.0f,
		.R_ph_Ohm = 0.249f,
        .polePairs = 4.0f,
		.M_rated_Nm = 1.6f,
		.I_rated_Ampere = 15.0f,
		.n_rated_rpm = 1500.0f};

static const struct uz_PMSM_t PMSM_Load_config = {//Beckhoff AM8141
        .Ld_Henry = 0.002f,
        .Lq_Henry = 0.002f,
        .Psi_PM_Vs = 0.042f,
		.I_max_Ampere = 15.0f,
		.R_ph_Ohm = 0.51f,
        .polePairs = 4.0f,
		.M_rated_Nm = 1.6f,
		.J_kg_m_squared = 0.000108f,
		.I_rated_Ampere = 11.3f,
		.n_rated_rpm = 1000.0f};

static const struct uz_PMSM_flux_fitting_parameter_config_t Fitting_parameter_DUT = {
		.ad1_parameter = 0.024902266251059f,
		.ad2_parameter = 0.048665940747155f,
		.ad3_parameter = -21.728876200244958f,
		.ad4_parameter = 0.025686294208918f,
		.ad5_parameter = 0.021304623129277f,
		.ad6_parameter = -24.167153248173516f,
		.aq1_parameter = 0.011336899936001f,
		.aq2_parameter = 0.126154283521831f,
		.aq3_parameter = 3.179837653870588e-04f,
		.aq4_parameter = -0.335577016710544f,
		.aq5_parameter = -0.010955695783842f,
		.aq6_parameter = -0.003063536538741f,
		.F1G1_parameter =0.174087113205129f,
		.F2G2_parameter = 0.266836735631787f
};

struct uz_pmsmModel_config_t IP_PMSM_config = {
		.base_address = XPAR_UZ_PMSM_MODEL_0_BASEADDR,
		.ip_core_frequency_Hz = 100000000U,
		.simulate_mechanical_system = false,
		.simulate_nonlinear = true,
		.r_1 = PMSM_DUT_config.R_ph_Ohm,
		.L_d = PMSM_DUT_config.Ld_Henry,
		.L_q = PMSM_DUT_config.Lq_Henry,
		.psi_pm = PMSM_DUT_config.Psi_PM_Vs,
		.polepairs = PMSM_DUT_config.polePairs,
		.coulomb_friction_constant = 0.01f,
		.friction_coefficient = 0.001f,
		.inertia = 0.001f,
		.ad1 = Fitting_parameter_DUT.ad1_parameter,
		.ad2 = Fitting_parameter_DUT.ad2_parameter,
		.ad3 = Fitting_parameter_DUT.ad3_parameter,
		.ad4 = Fitting_parameter_DUT.ad4_parameter,
		.ad5 = Fitting_parameter_DUT.ad5_parameter,
		.ad6 = Fitting_parameter_DUT.ad6_parameter,
		.aq1 = Fitting_parameter_DUT.aq1_parameter,
		.aq2 = Fitting_parameter_DUT.aq2_parameter,
		.aq3 = Fitting_parameter_DUT.aq3_parameter,
		.aq4 = Fitting_parameter_DUT.aq4_parameter,
		.aq5 = Fitting_parameter_DUT.aq5_parameter,
		.aq6 = Fitting_parameter_DUT.aq6_parameter,
		.F1G1 = Fitting_parameter_DUT.F1G1_parameter,
		.F2G2 = Fitting_parameter_DUT.F2G2_parameter
};

struct uz_PI_Controller_config config_id_DUT = {
		.Kp = PMSM_DUT_config.Ld_Henry / (2.0f * TAU_SIGMA),
		.Ki = PMSM_DUT_config.R_ph_Ohm / (2.0f * TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
		.type = UZ_PI_PARALLEL
};

struct uz_PI_Controller_config config_iq_DUT = {
		.Kp = PMSM_DUT_config.Lq_Henry / (2.0f * TAU_SIGMA),
		.Ki = PMSM_DUT_config.R_ph_Ohm / (2.0f * TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
		.type = UZ_PI_PARALLEL
};

struct uz_PI_Controller_config config_id_Load = {
		.Kp = PMSM_Load_config.Ld_Henry / (2.0f * TAU_SIGMA),
		.Ki = PMSM_Load_config.R_ph_Ohm / (2.0f * TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
		.type = UZ_PI_PARALLEL
};

struct uz_PI_Controller_config config_iq_Load = {
		.Kp = PMSM_Load_config.Lq_Henry / (2.0f * TAU_SIGMA),
		.Ki = PMSM_Load_config.R_ph_Ohm / (2.0f * TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
		.type = UZ_PI_PARALLEL
};

static const struct uz_PI_Controller_config config_speed_Load = {
		.Kp = 0.1f,
		.Ki = 0.5f,
		.lower_limit = -3.0f,
		.upper_limit = 3.0f,
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
		.type = UZ_PI_PARALLEL
};

struct uz_SpeedControl_config config_SpeedControl_Load = {
		.config_controller = config_speed_Load
};

struct uz_SetPoint_config config_SetPoint_Load = {
		.config_PMSM = PMSM_Load_config,
		.control_type = FOC,
		.id_ref_Ampere = 0.0f,
		.is_field_weakening_enabled = false,
		.motor_type = SMPMSM,
		.relative_torque_tolerance = 0.05f
};

uz_CurrentControl_t* init_FOC_DUT(void) {
	struct uz_CurrentControl_config CC_config_DUT = {
			.decoupling_select = static_nonlinear_decoupling,
			.config_id = config_id_DUT,
			.config_iq = config_iq_DUT,
			.config_PMSM = PMSM_DUT_config,
			.Kp_adjustment_flag = true,
			.max_modulation_index = 1.0f/sqrtf(3.0f)
	};
	Global_Data.rasv.PMSM_DUT_config = PMSM_DUT_config;
	return(uz_CurrentControl_init(CC_config_DUT));
}

uz_CurrentControl_t* init_FOC_Load(void) {
	struct uz_CurrentControl_config CC_config_Load = {
			.decoupling_select = linear_decoupling,
			.config_id = config_id_Load,
			.config_iq = config_iq_Load,
			.config_PMSM = PMSM_Load_config,
			.Kp_adjustment_flag = false,
			.max_modulation_index = 1.0f/sqrtf(3.0f)
	};
	Global_Data.rasv.PMSM_Load_config = PMSM_Load_config;
	return(uz_CurrentControl_init(CC_config_Load));
}

uz_SpeedControl_t* init_SpeedControl_Load(void) {
	return(uz_SpeedControl_init(config_SpeedControl_Load));
}

uz_SetPoint_t* init_SetPoint_Load(void) {
	return(uz_SetPoint_init(config_SetPoint_Load));
}

uz_approximate_flux_t* init_FluxApproximation_DUT(void) {
	Global_Data.rasv.Fitting_parameter_DUT = Fitting_parameter_DUT;
	return(uz_approximate_flux_init(Fitting_parameter_DUT));
}

uz_pmsmModel_t* init_pmsmModel(void) {
	return(uz_pmsmModel_init(IP_PMSM_config));
}


//Arrays for LUTs
static float LUT_breakpoints_array[17] = {
#include "LUT_Breakpoints.csv"
};
static float LUT_current_angle_array[17] = {
#include "LUT_current_angle.csv"
};
static float LUT_Is_array[17] = {
#include "LUT_Is.csv"
};

//Create uz_arrays
uz_array_float_t LUT_breakpoints = {
		.length = UZ_ARRAY_SIZE(LUT_breakpoints_array),
		.data = &LUT_breakpoints_array[0]
};
uz_array_float_t LUT_current_angle = {
		.length = UZ_ARRAY_SIZE(LUT_current_angle_array),
		.data = &LUT_current_angle_array[0]
};
uz_array_float_t LUT_Is = {
		.length = UZ_ARRAY_SIZE(LUT_Is_array),
		.data = &LUT_Is_array[0]
};

uz_LUT_1D_t* init_LUT_current_angle(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_current_angle, 17U));
}
uz_LUT_1D_t* init_LUT_Is(void) {
	return(uz_LUT_1D_init(&LUT_breakpoints, &LUT_Is, 17U));
}






