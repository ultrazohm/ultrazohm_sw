#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../include/FOC.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_global_configuration.h"

// Machine parameters
const struct uz_PMSM_t config_PMSM = {
		.R_ph_Ohm = 0.27f,
		.Ld_Henry = 0.0017f,
		.Lq_Henry = 0.0038f,
		.Psi_PM_Vs = 0.19f,
		.polePairs = 5.0f,
		.I_max_Ampere = 18.0f
};
const float Lx_Henry = 0.0027f;
const float Ly_Henry = 0.0027f;

// PI controllers
const struct uz_PI_Controller_config config_id = {
		.Kp = 10.0f,
		.Ki = 1500.0f,
		.samplingTime_sec = 0.0001f,
		.type = ideal,
};

const struct uz_PI_Controller_config config_iq = {
		.Kp = 10.0f,
		.Ki = 1500.0f,
		.samplingTime_sec = 0.0001f,
		.type = ideal,
};

struct uz_CurrentControl_config current_control_config = {
		.config_PMSM = config_PMSM,
		.config_id = config_id,
		.config_iq = config_iq,
		.decoupling_select = no_decoupling,
		.max_modulation_index = 0.5f
};

// MPC controller

// rated values
const rated_val_t rated_values={
		.IR=10.0f/sqrt(2),
		.VR=565.0f/sqrt(2),
		.nR=3000.0f
};

// per unit base values
const base_val_t base_val={
		.VB=sqrt(2.0f/3.0f)*rated_values.VR,
		.IB=sqrt(2.0f)*rated_values.IR,
		.omegaB=rated_values.nR*2.0f*UZ_PIf/60.0f*config_PMSM.polePairs,
		.ZB=(sqrt(2.0f/3.0f)*rated_values.VR)/(sqrt(2.0f)*rated_values.IR),
		.LB=(sqrt(2.0f/3.0f)*rated_values.VR)/(sqrt(2.0f)*rated_values.IR)/(rated_values.nR*2.0f*UZ_PIf/60.0f*config_PMSM.polePairs),
		.psiB=(sqrt(2.0f/3.0f)*rated_values.VR)/(rated_values.nR*2.0f*UZ_PIf/60.0f*config_PMSM.polePairs)
};

const base_val_t inverse_base_val={
		.VB=1.0f/base_val.VB,
		.IB=1.0f/base_val.IB,
		.omegaB=1.0f/base_val.omegaB,
		.ZB=1.0f/base_val.ZB,
		.LB=1.0f/base_val.LB,
		.psiB=1.0f/base_val.psiB
};

const pre_calc_val_t pre_calc_val={
		.Rs_over_ZB = config_PMSM.R_ph_Ohm/base_val.ZB,
		.Ts_times_ZB_over_Ld = UZ_TIME_ISR*base_val.ZB/config_PMSM.Ld_Henry,
		.Ts_times_ZB_over_Lq = UZ_TIME_ISR*base_val.ZB/config_PMSM.Lq_Henry,
		.Ts_times_ZB_over_Lx = UZ_TIME_ISR*base_val.ZB/Lx_Henry,
		.Ts_times_ZB_over_Ly = UZ_TIME_ISR*base_val.ZB/Ly_Henry,
		.Ld_over_LB = config_PMSM.Ld_Henry/base_val.LB,
		.Lq_over_LB = config_PMSM.Lq_Henry/base_val.LB,
		.Lx_over_LB = Lx_Henry/base_val.LB,
		.Ly_over_LB = Ly_Henry/base_val.LB,
		.psi_pm_over_psiB = config_PMSM.Psi_PM_Vs/base_val.psiB
};

uz_CurrentControl_t* init_FOC_CurrentControl() {
	return(uz_CurrentControl_init(current_control_config));
}
