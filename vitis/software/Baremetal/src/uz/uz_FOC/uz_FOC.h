#ifndef UZ_FOC_H
#define UZ_FOC_H

#endif // UZ_FOC_H

#include "../uz_HAL.h"
#include <math.h>
#include <stdbool.h>

typedef struct uz_FOC_CurrentControl_config {
	float Kp_id;
	float Tn_id;
	float Kp_iq;
	float Tn_iq;
	float iq_target_Ampere;
	float id_target_Ampere;
} uz_FOC_CurrentControl_config;

typedef struct uz_FOC_SpeedControl_config {
	float Kp_n;
	float Tn_n;
	float Kp_id;
	float Tn_id;
	float Kp_iq;
	float Tn_iq;
	float id_target_Ampere;
	float n_target_rpm;
} uz_FOC_SpeedControl_config;


typedef struct uz_FOC_CurrentControl_parameters {
	bool is_ready;
	float error_iq_sum;
	float error_id_sum;
	float id_Ampere;
	float iq_Ampere;
	float ud_target_Volt;
	float uq_target_Volt;
	uz_FOC_CurrentControl_config config;
} uz_FOC_CurrentControl_parameters;

typedef struct uz_FOC_SpeedControl_parameters {
	bool is_ready;
	float error_omega_sum;
	float error_iq_sum;
	float error_id_sum;
	float id_Ampere;
	float iq_Ampere;
	float ud_target_Volt;
	float uq_target_Volt;
	float omega_rad;
	uz_FOC_SpeedControl_config config;
} uz_FOC_SpeedControl_parameters;


uz_FOC_CurrentControl_parameters* uz_FOC_CurrentControl_init(uz_FOC_CurrentControl_config config);
void uz_FOC_CurrentControl(uz_FOC_CurrentControl_parameters* self);

uz_FOC_SpeedControl_parameters* uz_FOC_SpeedControl_init(uz_FOC_SpeedControl_config config);
void uz_FOC_SpeedControl(uz_FOC_SpeedControl_parameters* self);
