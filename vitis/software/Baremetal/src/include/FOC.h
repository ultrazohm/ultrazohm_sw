#include "../uz/uz_setpoint/uz_setpoint.h"
#include "../uz/uz_SpeedControl/uz_speedcontrol.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_subspace_resonant_control/uz_subspace_resonant_control.h"

uz_CurrentControl_t* init_FOC_CurrentControl();
uz_CurrentControl_t* init_FOC_xy_control();
uz_subspace_resonant_control* init_resonant_control_dq_2();
uz_subspace_resonant_control* init_resonant_control_xy_2();
uz_subspace_resonant_control* init_resonant_control_xy_6();
uz_SetPoint_t* setpoint_init(void);
uz_SpeedControl_t* speed_control_init(void);
uz_IIR_Filter_t* speed_ref_filt_init(void);

//typedef struct pre_calc_val_t {
//	float Rs_over_ZB;
//	float Ts_times_ZB_over_Ld;
//	float Ts_times_ZB_over_Lq;
//	float Ts_times_ZB_over_Lx;
//	float Ts_times_ZB_over_Ly;
//	float Ld_over_LB;
//	float Lq_over_LB;
//	float Lx_over_LB;
//	float Ly_over_LB;
//	float psi_pm_over_psiB;
//	float psi_pm_h_pu_over_psiB[2];
//	float phi_pm_h_over_psiB[2];
//}pre_calc_val_t;

typedef struct rated_val_t {
	float VR;
	float IR;
	float nR;
}rated_val_t;

typedef struct base_val_t {
	float VB;
	float IB;
	float omegaB;
	float ZB;
	float LB;
	float psiB;
}base_val_t;
