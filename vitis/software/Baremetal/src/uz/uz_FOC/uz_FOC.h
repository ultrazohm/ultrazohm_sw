#ifndef UZ_FOC_H
#define UZ_FOC_H

#pragma once
#include "../uz_HAL.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
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
 * @brief Configuration struct for FOC. Accessible by the user
 */
struct uz_FOC_config {
	enum uz_FOC_decoupling_select decoupling_select; /**< FOC decoupling selector \n
													0 = no_decoupling \n
													1 = linear_decoupling*/
	struct uz_PI_Controller_config config_id; /**< Configuration struct for id-Controller */
	struct uz_PI_Controller_config config_iq; /**< Configuration struct for iq-Controller */
	uz_PMSM_t config_PMSM; /**< Configuration struct for PMSM parameters */

};
/**
 * @brief Struct for the three DutyCycles for a three-phase-system
 * 
 */
struct uz_DutyCycle_t {
	float DutyCycle_U; /**< DutyCycle for Phase U */
	float DutyCycle_V; /**< DutyCycle for Phase V */
	float DutyCycle_W; /**< DutyCycle for Phase W */
};


/**
 * @brief Object definition for FOC
 *
 */
typedef struct uz_FOC uz_FOC;

/**
 * @brief Initialization of the uz_FOC object
 *
 * @param config configuration struct for FOC
 * @return uz_FOC* Pointer to uz_FOC instance
 */
uz_FOC* uz_FOC_init(struct uz_FOC_config config);

/**
 * @brief calculates last sample for dq-reference voltages
 *
 * @param self uz_FOC instance
 * @param i_reference_Ampere uz_dq_t struct for reference dq-currents in Ampere
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param V_dc_volts DC link voltage. Must be greater than 0.0f
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @return uz_dq_t Output dq-reference voltage struct
 */
uz_3ph_dq_t uz_FOC_sample(uz_FOC* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec);

/**
 * @brief calculates last sample and transforms the dq-output voltage into the UVW-system
 * 
 * @param self uz_FOC instance
 * @param i_reference_Ampere uz_dq_t struct for reference dq-currents in Ampere
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param V_dc_volts DC link voltage. Must be greater than 0.0f
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @param theta_el_rad electrical theta in rad
 * @return uz_UVW_t Output UVW-voltage struct
 */
uz_3ph_abc_t uz_FOC_sample_UVW(uz_FOC* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad);
/**
 * @brief Resets the FOC and the integrators of the PI-Controllers
 *
 * @param self uz_FOC instance
 */
void uz_FOC_reset(uz_FOC* self);

/**
 * @brief Function to change the Kp-value of the id-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Kp_id new Kp_id value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Kp_id(uz_FOC* self, float Kp_id);

/**
 * @brief Function to change the Ki-value of the id-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Ki_id new Ki_id value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Ki_id(uz_FOC* self, float Ki_id);

/**
 * @brief Function to change the Kp-value of the iq-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Kp_iq new Kp_iq value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Kp_iq(uz_FOC* self, float Kp_iq);

/**
 * @brief Function to change the Ki-value of the iq-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Ki_iq new Ki_iq value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Ki_iq(uz_FOC* self, float Ki_iq);

/**
 * @brief Function to change the PMSM parameters during runtime
 * 
 * @param self uz_FOC instance
 * @param pmsm_config PMSM_config struct with updated values
 */
void uz_FOC_set_PMSM_parameters(uz_FOC* self, uz_PMSM_t pmsm_config);

/**
 * @brief Function to change the type of decoupling during runtime
 * 
 * @param self uz_FOC instance
 * @param decoupling_select enum FOC decoupling selector \n
							0 = no_decoupling \n
							1 = linear_decoupling
 */
void uz_FOC_set_decoupling_method(uz_FOC* self, enum uz_FOC_decoupling_select decoupling_select);

/**
 * @brief Returns the current value of the external clamping signal
 * 
 * @param self uz_FOC instance
 * @return current value as bool 
 */
bool uz_FOC_get_ext_clamping(uz_FOC* self);

/**
 * @brief Generates one sample for a continuous sinusoidal PWM (SPWM)  
 * 
 * @param input uz_UVW_t struct 
 * @param V_dc_volts DC link voltage. Must be greater than 0.0f
 * @return struct uz_DutyCycle_t outputs the corresponding DutyCycle for each phase
 */
struct uz_DutyCycle_t uz_FOC_generate_DutyCycles(uz_3ph_abc_t input, float V_dc_volts);
#endif // UZ_FOC_H
