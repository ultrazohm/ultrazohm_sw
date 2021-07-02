#ifndef UZ_FOC_H
#define UZ_FOC_H

#pragma once
#include "../uz_HAL.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Configuration struct for FOC. Accessible by the user
 */
typedef struct uz_FOC_config {
	float Kp_id;
	float Kp_iq;
	float Kp_n;
	float Ki_id;
	float Ki_iq;
	float Ki_n;
	float iq_ref_Ampere;
	float id_ref_Ampere;
	float n_ref_rpm;
	float d_y_max;
	float d_y_min;
	float SamplingTime_sec;
	unsigned int FOC_Select;
	unsigned int polePairs;
	float L_q;
	float L_d;
	float psi_pm;
	bool Reset;
} uz_FOC_config;

/**
 * @brief Struct for measured parameters, which are needed for the FOC. Accessible by the user
 */
typedef struct uz_FOC_ActualValues {
	bool is_ready;
	float i_d_Ampere;
	float i_q_Ampere;
	float u_d_Volts;
	float u_q_Volts;
	float i_a_Ampere;
	float i_b_Ampere;
	float i_c_Ampere;
	float omega_el_rad_per_sec;
	float theta_el_rad;
	float U_zk_Volts;
	float u_a_Volts;
	float u_b_Volts;
	float u_c_Volts;
} uz_FOC_ActualValues;

/**
 * @brief Object definition for generating reference voltages via a FOC
 *
 */
typedef struct uz_FOC_VoltageReference {
	bool is_ready;
	float u_d_ref_Volts;
	float u_q_ref_Volts;
} uz_FOC_VoltageReference;

/**
 * @brief Initialization of a ActualValues struct
 *
 * @return Pointer to ActualValues instance
 */
uz_FOC_ActualValues* uz_FOC_ActualValues_init(void);

/**
 * @brief Initialization of a uz_FOC_VoltageReference struct
 *
 * @return Pointer to uz_FOC_VoltageReference instance
 */
uz_FOC_VoltageReference* uz_FOC_VoltageReference_init(void);


void uz_FOC_linear_decouppling(uz_FOC_ActualValues* values, uz_FOC_config config, float* u_d_vor, float* u_q_vor);
bool uz_FOC_SpaceVector_Limitation(uz_FOC_VoltageReference* reference, uz_FOC_ActualValues* values);
int uz_FOC_get_sign_of_value(float input);

#endif // UZ_FOC_H
