#include "../main.h"
extern DS_Data Global_Data;
float Limitation_saftey_factor = 0.707106781f; //To represent the saftey factor from simulation

#define SAMPLE_TIME_SEC_CURRENT_CONTROL   1.0f/UZ_PWM_FREQUENCY
#define SAMPLE_TIME_SEC_SPEED_CONTROL  SAMPLE_TIME_SEC_CURRENT_CONTROL
//#define LIMITATION_SAFETY_FACTOR 0.707106781186f   //(1/sqrtf(2.0f))
#define TAU_SIGMA (1.5f * SAMPLE_TIME_SEC_CURRENT_CONTROL)

static const struct uz_PMSM_t pmsm_config_dq = {
        .Ld_Henry = 0.00012516f,
        .Lq_Henry = 0.00012595f,
        .Psi_PM_Vs = 0.0047f,
		.I_max_Ampere = 30.0f,
		.R_ph_Ohm = 0.0643f,
        .polePairs = 5.0f
        };

static const struct uz_PMSM_t pmsm_config_xy = {
        .Ld_Henry = 0.000039374f,
        .Lq_Henry = 0.000034854f,
        .Psi_PM_Vs = 0.0f,
		.I_max_Ampere = 30.0f,
		.R_ph_Ohm = 0.0643f,
        .polePairs = 5.0f
        };

struct uz_pmsmModel_6ph_dqxy_config_t pmsm_config={
  .base_address=XPAR_UZ_PMSM_MODEL_6PH_DQXY_0_BASEADDR,
  .ip_core_frequency_Hz=100000000,
  .simulate_mechanical_system = false,
  .r_1 = 0.0643f,
  .L_d = 0.00012516f,
  .L_q = 0.00012595f,
  .L_x = 0.000039374f,
  .L_y = 0.000034854f,
  .psi_pm = 0.0047f,
  .polepairs = 5.0f,
  .inertia = 0.001,
  .coulomb_friction_constant = 0.01f,
  .friction_coefficient = 0.001f};

struct uz_PI_Controller_config config_id = {
		.Kp = pmsm_config_dq.Ld_Henry / (2*TAU_SIGMA),
		.Ki = pmsm_config_dq.R_ph_Ohm / (2*TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
        };

struct uz_PI_Controller_config config_iq = {
		.Kp = pmsm_config_dq.Lq_Henry / (2*TAU_SIGMA),
		.Ki = pmsm_config_dq.R_ph_Ohm / (2*TAU_SIGMA),
		.samplingTime_sec = SAMPLE_TIME_SEC_CURRENT_CONTROL,
        };

struct uz_PI_Controller_config config_ix = {
        .Kp = pmsm_config_xy.Ld_Henry / (2*TAU_SIGMA),
        .Ki = pmsm_config_xy.R_ph_Ohm / (2*TAU_SIGMA),
        .samplingTime_sec = 0.0001f,
        };

struct uz_PI_Controller_config config_iy = {
        .Kp = pmsm_config_xy.Lq_Henry / (2*TAU_SIGMA),
        .Ki = pmsm_config_xy.R_ph_Ohm / (2*TAU_SIGMA),
        .samplingTime_sec = 0.0001f,
        };


uz_CurrentControl_t* init_xy_FOC(void) {
	struct uz_CurrentControl_config CC_xy_config = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_ix,
	    .config_iq = config_iy,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,//not used
		.config_PMSM = pmsm_config_xy
	};
	Global_Data.av.pmsm_config_xy = pmsm_config_xy;
	return(uz_CurrentControl_init(CC_xy_config));
}

uz_CurrentControl_t* init_dq_FOC(void) {
	struct uz_CurrentControl_config CC_dq_config = {
	    .decoupling_select = linear_decoupling,
	    .config_id = config_id,
	    .config_iq = config_iq,
	    .max_modulation_index = (1.0f / 2.0f) * Limitation_saftey_factor,//not used
		.config_PMSM = pmsm_config_dq
	};
	Global_Data.av.pmsm_config_dq = pmsm_config_dq;
	return(uz_CurrentControl_init(CC_dq_config));
}

uz_pmsmModel_6ph_dqxy_t* pmsmModel_init(void) {
	return(uz_pmsmModel_6ph_dqxy_init(pmsm_config));
}








