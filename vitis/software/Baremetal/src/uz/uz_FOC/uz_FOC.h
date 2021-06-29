#ifndef UZ_FOC_H
#define UZ_FOC_H

#endif // UZ_FOC_H
#pragma once
#include "../uz_HAL.h"
#include <math.h>
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
	int FOC_Select;
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
 * @brief Object definition for internal FOC variables
 *
 */
typedef struct uz_FOC_PI_Controller_variables uz_FOC_PI_Controller_variables;

/**
 * @brief Memory allocation of the ActualValues struct
 *
 * @return Pointer to ActualValues instance
 */
static uz_FOC_ActualValues* uz_FOC_ActualValues_allocation(void);

/**
 * @brief Memory allocation of the uz_FOC_PI_Controller_output struct
 *
 * @return Pointer to uz_FOC_PI_Controller_output instance
 */
static uz_FOC_VoltageReference* uz_FOC_VoltageReference_allocation(void);

/**
 * @brief Memory allocation of the uz_FOC_VoltageReference struct
 *
 * @return Pointer to uz_FOC_VoltageReference instance
 */
static uz_FOC_PI_Controller_variables* uz_FOC_PI_Controller_variables_allocation(void);

/**
 * @brief Initialization of a ActualValues struct
 *
 * @return Pointer to ActualValues instance
 */
uz_FOC_ActualValues* uz_FOC_ActualValues_init(void);

/**
 * @brief Initialization of the struct for the i_d-PI-Controller
 *
 * @param ActualValues uz_FOC_ActualValues instance
 * @param config uz_FOC_config configuration struct
 * @return Pointer to uz_FOC_PI_Controller_variables instance
 */
uz_FOC_PI_Controller_variables* uz_FOC_PI_ID_Controller_variables_init(uz_FOC_config config, uz_FOC_ActualValues* values);

/**
 * @brief Initialization of the struct for the i_q-PI-Controller
 *
 * @param ActualValues uz_FOC_ActualValues instance
 * @param config uz_FOC_config configuration struct
 * @return Pointer to uz_FOC_PI_Controller_variables instance
 */
uz_FOC_PI_Controller_variables* uz_FOC_PI_IQ_Controller_variables_init(uz_FOC_config config, uz_FOC_ActualValues* values);

/**
 * @brief Initialization of the struct for the n-PI-Controller
 *
 * @param ActualValues uz_FOC_ActualValues instance
 * @param config uz_FOC_config configuration struct
 * @return Pointer to uz_FOC_PI_Controller_variables instance
 */
uz_FOC_PI_Controller_variables* uz_FOC_PI_N_Controller_variables_init(uz_FOC_config config, uz_FOC_ActualValues* values);

/**
 * @brief Initialization of a uz_FOC_VoltageReference struct
 *
 * @return Pointer to uz_FOC_VoltageReference instance
 */
uz_FOC_VoltageReference* uz_FOC_VoltageReference_init(void);

/**
 * @brief Returns the last calculated sample for u_d_ref
 *
 * @param ActualValues uz_FOC_ActualValues instance
 * @param config uz_FOC_config configuration struct
 * @param output uz_FOC_PI_Controller_output instance
 * @param internal values needed for further calculation
 * @return Returns last sample for u_d_ref
 */
float uz_FOC_PI_Controller(uz_FOC_PI_Controller_variables* variables, uz_FOC_config config, bool ext_clamping);

/**
 * @brief Compares the values before and after the Integrator and decides if clamping is necessary
 *
 * @param preIntegrator value before the integrator
 * @param preSat value after the integrator and before the saturation
 * @param config uz_FOC_config configuration struct
 * @return Returns true if clamping is necessary
 */
bool uz_FOC_Clamping_Circuit(float preIntegrator, float preSat, uz_FOC_config config);
float uz_FOC_Dead_Zone(float input, uz_FOC_config config);
int uz_FOC_get_sign_of_value(float input);
uz_FOC_PI_Controller_variables* uz_FOC_update_PI_ID_Controller_variables(uz_FOC_PI_Controller_variables* self, uz_FOC_config config, uz_FOC_ActualValues* values);

