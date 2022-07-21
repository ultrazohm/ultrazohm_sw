#ifndef UZ_FOC_H
#define UZ_FOC_H

#pragma once
#include "uz_piController.h"
#include "uz_signals.h"
#include "uz_Transformation.h"
#include "uz_linear_decoupling.h"
#include "uz_space_vector_limitation.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/*! enum for readable configuring for the decoupling in the FOC sample function */
enum uz_FOC_decoupling_select {
	no_decoupling=0, 
	linear_decoupling
	}; 

/**
 * @brief Object definition for FOC
 *
 */
typedef struct uz_FOC {
	bool decoupling_select;
	bool I_rst;
	bool ext_clamping;
	struct uz_PMSM_t config_PMSM; //< Configuration struct for PMSM parameters
}uz_FOC;

uz_PI_Controller_config config_id; //< Configuration struct for id-Controller
uz_PI_Controller_config config_iq; //< Configuration struct for iq-Controller
/**
 * @brief calculates last sample for dq-reference voltages
 *
 * @param self uz_FOC instance
 * @param i_reference_Ampere uz_dq_t struct for reference dq-currents in Ampere
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param V_dc_volts DC link voltage. Must be greater than 0.0f
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @return struct uz_dq_t Output dq-reference voltage struct
 */
void uz_FOC_sample(uz_FOC* self,uz_PI_Controller_config* Controller_id,uz_PI_Controller_config* Controller_iq, struct uz_dq_t i_reference_Ampere, struct uz_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float* output_volts_d, float* output_volts_q);
struct uz_dq_t uz_FOC_CurrentControl(uz_FOC* self, struct uz_dq_t i_reference_Ampere, struct uz_dq_t i_actual_Ampere,uz_PI_Controller_config* Controller_id,uz_PI_Controller_config* Controller_iq);
struct uz_dq_t uz_FOC_decoupling(enum uz_FOC_decoupling_select decoupling_select, struct uz_PMSM_t pmsm,struct uz_dq_t actual_Ampere, float omega_el_rad_per_sec);

#endif // UZ_FOC_H
