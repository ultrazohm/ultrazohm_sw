#include "../main.h"
extern DS_Data Global_Data;
float Limitation_saftey_factor = 0.707106781f; //To represent the saftey factor from simulation

#define SAMPLE_TIME_SEC_CURRENT_CONTROL   1.0f/UZ_PWM_FREQUENCY
#define SAMPLE_TIME_SEC_SPEED_CONTROL  SAMPLE_TIME_SEC_CURRENT_CONTROL
//#define LIMITATION_SAFETY_FACTOR 0.707106781186f   //(1/sqrtf(2.0f))
#define TAU_SIGMA (1.5f * SAMPLE_TIME_SEC_CURRENT_CONTROL)

static const struct uz_PMSM_t pmsm_config_Pruef_dq = {
        .Ld_Henry = 0.00058f,
        .Lq_Henry = 0.00071f,
        .Psi_PM_Vs = 0.0143f,
		.I_max_Ampere = 15.0f,
		.R_ph_Ohm = 0.2f,
        .polePairs = 5.0f
        };

static const struct uz_PMSM_t pmsm_config_Pruef_xy = {
        .Ld_Henry = 0.00029f,
        .Lq_Henry = 0.00027f,
        .Psi_PM_Vs = 0.0f,
		.I_max_Ampere = 15.0f,
		.R_ph_Ohm = 0.2f,
        .polePairs = 5.0f
        };

static const struct uz_PMSM_t pmsm_config_Last_dq = {
        .Ld_Henry = 0.00058f,
        .Lq_Henry = 0.00071f,
        .Psi_PM_Vs = 0.0143f,
		.I_max_Ampere = 15.0f,
		.R_ph_Ohm = 0.1f,
        .polePairs = 5.0f,
        };

struct uz_pmsmModel_6ph_dqxy_config_t pmsm_config={
  .base_address=XPAR_UZ_PMSM_MODEL_6PH_DQXY_0_BASEADDR,
  .ip_core_frequency_Hz=100000000,
  .simulate_mechanical_system = false,
  .r_1 = 0.2f,
  .L_d = 0.00058f,
  .L_q = 0.00071f,
  .L_x = 0.00029f,
  .L_y = 0.00027f,
  .psi_pm = 0.0143f,
  .polepairs = 5.0f,
  .inertia = 0.001,
  .coulomb_friction_constant = 0.01f,
  .friction_coefficient = 0.001f};

struct uz_PI_Controller_config config_id_Pruef = {
		.Kp = pmsm_config_Pruef_dq.Ld_Henry / (2*TAU_SIGMA),
		.Ki = pmsm_config_Pruef_dq.R_ph_Ohm / (2*TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
        };

struct uz_PI_Controller_config config_iq_Pruef = {
		.Kp = pmsm_config_Pruef_dq.Lq_Henry / (2*TAU_SIGMA),
		.Ki = pmsm_config_Pruef_dq.R_ph_Ohm / (2*TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
        };

struct uz_PI_Controller_config config_ix_Pruef = {
        .Kp = pmsm_config_Pruef_xy.Ld_Henry / (2*TAU_SIGMA),
        .Ki = pmsm_config_Pruef_xy.R_ph_Ohm / (2*TAU_SIGMA),
        .samplingTime_sec = 0.0001f,
        };

struct uz_PI_Controller_config config_iy_Pruef = {
        .Kp = pmsm_config_Pruef_xy.Lq_Henry / (2*TAU_SIGMA),
        .Ki = pmsm_config_Pruef_xy.R_ph_Ohm / (2*TAU_SIGMA),
        .samplingTime_sec = 0.0001f,
        };


struct uz_PI_Controller_config config_id_Last = {
		.Kp = pmsm_config_Last_dq.Ld_Henry / (2*TAU_SIGMA),
		.Ki = pmsm_config_Last_dq.R_ph_Ohm / (2*TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
        };

struct uz_PI_Controller_config config_iq_Last = {
		.Kp = pmsm_config_Last_dq.Lq_Henry / (2*TAU_SIGMA),
		.Ki = pmsm_config_Last_dq.R_ph_Ohm / (2*TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
        };


uz_CurrentControl_t* init_xy_FOC_Pruef(void) {
	struct uz_CurrentControl_config CC_xy_config_Pruef = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_ix_Pruef,
	    .config_iq = config_iy_Pruef,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_Pruef_xy
	};
	return(uz_CurrentControl_init(CC_xy_config_Pruef));
}

uz_CurrentControl_t* init_dq_FOC_Pruef(void) {
	struct uz_CurrentControl_config CC_dq_config_Pruef = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_id_Pruef,
	    .config_iq = config_iq_Pruef,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_Pruef_dq
	};
	return(uz_CurrentControl_init(CC_dq_config_Pruef));
}

uz_CurrentControl_t* init_dq_FOC_Last(void) {
	struct uz_CurrentControl_config CC_dq_config_Last = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_id_Last,
	    .config_iq = config_iq_Last,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,
		.config_PMSM = pmsm_config_Last_dq
	};
	return(uz_CurrentControl_init(CC_dq_config_Last));
}

const struct uz_PI_Controller_config config_speed_Last = {
		   .Kp = 0.01f,
		   .Ki = 16.6667f,
		   .samplingTime_sec = SAMPLE_TIME_SEC_SPEED_CONTROL,
		   .upper_limit = 2.4f,
		   .lower_limit = -2.4f,
		   .type = UZ_PI_IDEAL
};

const struct uz_SpeedControl_config config_speed_ctrl_Last = {
			   .config_controller = config_speed_Last
	   };

const struct uz_SetPoint_config config_setpoint_Last = {
			.config_PMSM = pmsm_config_Last_dq,
			.control_type = FOC,
		    .id_ref_Ampere = 0.0f,
		    .is_field_weakening_enabled = false,
		    .motor_type = IPMSM,
		    .relative_torque_tolerance = 0.001f
};

uz_SetPoint_t* setpoint_ctrl_Last_init(void) {
	   return(uz_SetPoint_init(config_setpoint_Last));
}

uz_SpeedControl_t* speed_ctrl_Last_init(void) {
	   return(uz_SpeedControl_init(config_speed_ctrl_Last));
}

uz_pmsmModel_6ph_dqxy_t* pmsmModel_init(void) {
	return(uz_pmsmModel_6ph_dqxy_init(pmsm_config));
}








