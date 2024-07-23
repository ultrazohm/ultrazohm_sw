uz_CurrentControl_t* init_FOC_CurrentControl();

typedef struct pre_calc_val_t {
	float Rs_over_ZB;
	float Ts_times_ZB_over_Ld;
	float Ts_times_ZB_over_Lq;
	float Ts_times_ZB_over_Lx;
	float Ts_times_ZB_over_Ly;
	float Ld_over_LB;
	float Lq_over_LB;
	float Lx_over_LB;
	float Ly_over_LB;
	float psi_pm_over_psiB;
}pre_calc_val_t;

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
