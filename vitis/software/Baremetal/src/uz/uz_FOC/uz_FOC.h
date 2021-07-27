#ifndef UZ_FOC_H
#define UZ_FOC_H

#pragma once
#include "../uz_HAL.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Configuration struct for FOC. Accessible by the user
 */
typedef struct uz_FOC_config {
	float iq_ref_Ampere;
	float id_ref_Ampere;
	float n_ref_rpm;
	unsigned int FOC_Select; //1=CurrentControl 2=SpeedControl
	float polePairs;
	float L_q;
	float L_d;
	float psi_pm;
	bool Reset;
} uz_FOC_config;

/**
 * @brief Struct for measured parameters, which are needed for the FOC. Accessible by the user
 *
 */
typedef struct uz_FOC_ActualValues {
	bool is_ready;
	float i_d_Ampere;
	float i_q_Ampere;
	float omega_el_rad_per_sec;
	float theta_el_rad;
	float U_zk_Volts;
} uz_FOC_ActualValues;

/**
 * @brief Object definition for FOC
 *
 */
typedef struct uz_FOC uz_FOC;



/**
 * @brief Initialization of the uz_FOC object
 *
 * @param config_FOC configuration struct for FOC
 * @param config_id configuration struct for id-PI-Controller
 * @param config_iq configuration struct for iq-PI-Controller
 * @param config_n configuration struct for n-PI-Controller
 * @return uz_FOC* Pointer to uz_FOC instance
 */
uz_FOC* uz_FOC_init(uz_FOC_config config_FOC, uz_PI_Controller_config config_id, uz_PI_Controller_config config_iq, uz_PI_Controller_config config_n);
struct uz_dq_t uz_FOC_sample(uz_FOC* self, uz_FOC_ActualValues values);
struct uz_dq_t uz_FOC_linear_decouppling(uz_FOC_ActualValues values, uz_FOC* self);
struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_dq_ref_Volts, uz_FOC_ActualValues values, bool* ext_clamping);
#endif // UZ_FOC_H
