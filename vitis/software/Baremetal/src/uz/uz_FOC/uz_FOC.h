#ifndef UZ_FOC_H
#define UZ_FOC_H

#endif // UZ_FOC_H

#include "../uz_HAL.h"
#include <math.h>
#include <stdbool.h>

typedef struct uz_FOC_CurrentControl_config {
	float Rs_mOhm;
	float Ld_mH;
	float Lq_mH;
	float Psi_PM_mVs;
	float polePairs;
	float iq_target_Ampere;
	float id_target_Ampere;
} uz_FOC_CurrentControl_config;

typedef struct uz_FOC_SpeedControl_config {
	float Rs_mOhm;
	float Ld_mH;
	float Lq_mH;
	float Psi_PM_mVs;
	float polePairs;
	float rotorInertia;
	float dampingFactor;
	float n_target_rpm;
} uz_FOC_SpeedControl_config;


typedef struct uz_FOC_CurrentControl_parameters {
	bool is_ready;
	float Kp_id;
	float Tn_id;
	float Kp_iq;
	float Tn_iq;
	float bandwith_Hz;
	float id_Ampere;
	float iq_Ampere;
	uz_FOC_CurrentControl_config config;
} uz_FOC_CurrentControl_parameters;

typedef struct uz_FOC_SpeedControl_parameters {
	bool is_ready;
	float Kp_n;
	float Tn_n;
	float Kp_id;
	float Tn_id;
	float Kp_iq;
	float Tn_iq;
	float bandwith_Hz;
	float id_Ampere;
	float iq_Ampere;
	float n_rpm;
	uz_FOC_SpeedControl_config config;
} uz_FOC_SpeedControl_parameters;


uz_FOC_CurrentControl_parameters* uz_FOC_CurrentControl_init(uz_FOC_CurrentControl_config config);
void uz_FOC_CurrentControl(uz_FOC_CurrentControl_parameters* self);

uz_FOC_SpeedControl_parameters* uz_FOC_SpeedControl_init(uz_FOC_SpeedControl_config config);
void uz_FOC_SpeedControl(uz_FOC_SpeedControl_parameters* self);
