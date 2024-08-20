#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../include/FOC.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_global_configuration.h"
#include "../globalData.h"
#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../uz/uz_signals/uz_signals.h"

extern DS_Data Global_Data;



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
const float psi_pm_5 = 0.00080f;
const float psi_pm_7 = 0.00047f;

// PI controllers
const struct uz_PI_Controller_config config_id = {
		.Kp = config_PMSM.Ld_Henry/(1.5f*1.0f/UZ_PWM_FREQUENCY_ISR),
		.Ki = config_PMSM.R_ph_Ohm/(1.5f*1.0f/UZ_PWM_FREQUENCY_ISR),
		.samplingTime_sec = UZ_TIME_ISR,
		.type = parallel,
};

const struct uz_PI_Controller_config config_iq = {
		.Kp = config_PMSM.Lq_Henry/(1.5f*1.0f/UZ_PWM_FREQUENCY_ISR),
		.Ki = config_PMSM.R_ph_Ohm/(1.5f*1.0f/UZ_PWM_FREQUENCY_ISR),
		.samplingTime_sec = UZ_TIME_ISR,
		.type = parallel,
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
		.VR=400.0f/sqrt(2),
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

//const pre_calc_val_t pre_calc_val={
//		.Rs_over_ZB = config_PMSM.R_ph_Ohm/base_val.ZB,
//		.Ts_times_ZB_over_Ld = UZ_TIME_ISR*base_val.ZB/config_PMSM.Ld_Henry,
//		.Ts_times_ZB_over_Lq = UZ_TIME_ISR*base_val.ZB/config_PMSM.Lq_Henry,
//		.Ts_times_ZB_over_Lx = UZ_TIME_ISR*base_val.ZB/Lx_Henry,
//		.Ts_times_ZB_over_Ly = UZ_TIME_ISR*base_val.ZB/Ly_Henry,
//		.Ld_over_LB = config_PMSM.Ld_Henry/base_val.LB,
//		.Lq_over_LB = config_PMSM.Lq_Henry/base_val.LB,
//		.Lx_over_LB = Lx_Henry/base_val.LB,
//		.Ly_over_LB = Ly_Henry/base_val.LB,
//		.psi_pm_over_psiB = config_PMSM.Psi_PM_Vs/base_val.psiB,
//		.psi_pm_h_pu_over_psiB[0] = psi_pm_5/base_val.psiB,
//		.psi_pm_h_pu_over_psiB[1] = psi_pm_7/base_val.psiB
//};

const struct uz_PI_Controller_config config_speed = {
		   .Kp = 0.1f,
		   .Ki = 0.0f,
		   .samplingTime_sec = 1/UZ_PWM_FREQUENCY,
		   .upper_limit = 6.0f,
		   .lower_limit = -6.0f
};

const struct uz_SetPoint_config config_setpoint = {
		   .config_PMSM = config_PMSM,
		   .control_type = FOC,
		   .id_ref_Ampere = 0.0f,
		   .is_field_weakening_enabled = false,
		   .motor_type = IPMSM,
		   .relative_torque_tolerance = 0.01f
};

const struct uz_SpeedControl_config config_speed_ctrl = {
		   .config_controller = config_speed
};

struct uz_IIR_Filter_config config_IIR = { .selection = LowPass_first_order,
   		.cutoff_frequency_Hz = 0.5f, .sample_frequency_Hz = UZ_PWM_FREQUENCY};


uz_CurrentControl_t* init_FOC_CurrentControl() {

	Global_Data.av.Rs_over_ZB = Global_Data.av.Rs/base_val.ZB;
	Global_Data.av.Ts_times_ZB_over_Ld = UZ_TIME_ISR*base_val.ZB/Global_Data.av.Ld;
	Global_Data.av.Ts_times_ZB_over_Lq = UZ_TIME_ISR*base_val.ZB/Global_Data.av.Lq;
	Global_Data.av.Ts_times_ZB_over_Lx = UZ_TIME_ISR*base_val.ZB/Global_Data.av.Lx;
	Global_Data.av.Ts_times_ZB_over_Ly = UZ_TIME_ISR*base_val.ZB/Global_Data.av.Ly;
	Global_Data.av.Ld_over_LB = Global_Data.av.Ld/base_val.LB;
	Global_Data.av.Lq_over_LB = Global_Data.av.Lq/base_val.LB;
	Global_Data.av.Lx_over_LB = Global_Data.av.Lx/base_val.LB;
	Global_Data.av.Ly_over_LB = Global_Data.av.Ly/base_val.LB;
	Global_Data.av.psi_pm_over_psiB = Global_Data.av.psi_pm/base_val.psiB;
	Global_Data.av.psi_pm_h_pu_over_psiB[0] = Global_Data.av.psiPM_h_pu[0]/base_val.psiB;
	Global_Data.av.psi_pm_h_pu_over_psiB[1] = Global_Data.av.psiPM_h_pu[1]/base_val.psiB;

	Global_Data.av.Kp_id = current_control_config.config_id.Kp;
	Global_Data.av.Ki_id = current_control_config.config_id.Ki;
	Global_Data.av.Kp_iq = current_control_config.config_iq.Kp;
	Global_Data.av.Ki_iq = current_control_config.config_iq.Ki;

	return(uz_CurrentControl_init(current_control_config));
}

uz_SetPoint_t* setpoint_init(void) {
	return(uz_SetPoint_init(config_setpoint));

}

uz_SpeedControl_t* speed_control_init(void) {

	Global_Data.av.Kp_speed = config_speed_ctrl.config_controller.Kp;
	Global_Data.av.Ki_speed = config_speed_ctrl.config_controller.Ki;

	return(uz_SpeedControl_init(config_speed_ctrl));
}

uz_IIR_Filter_t* speed_ref_filt_init(void) {
	return(uz_signals_IIR_Filter_init(config_IIR));
}
