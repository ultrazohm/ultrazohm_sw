#ifndef UZ_CURRENTCONTROL_H
#define UZ_CURRENTCONTROL_H

#pragma once
#include "../uz_piController/uz_piController.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include <stdbool.h>



/*! enum for readable configuring for the decoupling in the CurrentControl sample function */
enum uz_CurrentControl_decoupling_select {
	no_decoupling=0, 
	linear_decoupling,
	static_nonlinear_decoupling
	}; 

/**
 * @brief Configuration struct for CurrentControl. Accessible by the user
 */
struct uz_CurrentControl_config {
	enum uz_CurrentControl_decoupling_select decoupling_select; /**< CurrentControl decoupling selector \n
													 no_decoupling \n
													 linear_decoupling*/
	struct uz_PI_Controller_config config_id; /**< Configuration struct for id-Controller */
	struct uz_PI_Controller_config config_iq; /**< Configuration struct for iq-Controller */
	uz_PMSM_t config_PMSM; /**< Configuration struct for PMSM parameters */
	bool Kp_adjustment_flag; /**<Flag to turn the adjustment of Kp via nonlinear flux-maps on or off */
	float max_modulation_index; /**< Max possible modulation index for the chosen modulation method. I.e. 1/sqrt(3) for Space-Vector-Modulation*/
};

/**
 * @brief Object definition for CurrentControl
 *
 */
typedef struct uz_CurrentControl_t uz_CurrentControl_t;

/**
 * @brief Initialization of the uz_CurrentControl object
 *
 * @param config configuration struct for CurrentControl
 * @return uz_CurrentControl_t* Pointer to uz_CurrentControl_t instance
 */
uz_CurrentControl_t* uz_CurrentControl_init(struct uz_CurrentControl_config config);

/**
 * @brief calculates last sample for dq-reference voltages
 *
 * @param self uz_CurrentControl_t instance
 * @param i_reference_Ampere uz_dq_t struct for reference dq-currents in Ampere
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param V_dc_volts DC link voltage. Must be greater than 0.0f
 * @param omega_el_rad_per_sec electrical rotational speed in rad/s
 * @return uz_dq_t Output dq-reference voltage struct
 */
uz_3ph_dq_t uz_CurrentControl_sample(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec);

/**
 * @brief calculates last sample and transforms the dq-output voltage into the abc-system
 * 
 * @param self uz_CurrentControl_t instance
 * @param i_reference_Ampere uz_dq_t struct for reference dq-currents in Ampere
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param V_dc_volts DC link voltage. Must be greater than 0.0f
 * @param omega_el_rad_per_sec electrical rotational speed in rad/s
 * @param theta_el_rad electrical rotor angle in rad
 * @return uz_3ph_abc_t Output abc-voltage struct
 */
uz_3ph_abc_t uz_CurrentControl_sample_abc(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad);
/**
 * @brief Resets the CurrentControl and the integrators of the PI-Controllers
 *
 * @param self uz_CurrentControl_t instance
 */
void uz_CurrentControl_reset(uz_CurrentControl_t* self);

/**
 * @brief Function to change the flux-linkage value during runtime
 *
 * @param self uz_CurrentControl_t instance
 * @param flux_approx_real new flux-linkage value for measured current. 
 * @param flux_approx_reference new flux-linkage for reference current. 
 */
void uz_CurrentControl_set_flux_approx(uz_CurrentControl_t* self, uz_3ph_dq_t flux_approx_real, uz_3ph_dq_t flux_approx_reference);

/**
 * @brief Function to adjust the Kp parameter of the PI-Controllers during runtime based on nonlinear flux-maps
 * 
 * @param self uz_CurrentControl_t instance
 * @param i_reference_Ampere uz_dq_t struct for reference dq-currents in Ampere
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param BO_factor factor for magnitude optimum 
 */
void uz_CurrentControl_adjust_Kp(uz_CurrentControl_t* self, uz_3ph_dq_t i_reference_Ampere,  uz_3ph_dq_t i_actual_Ampere, float BO_factor);

/**
 * @brief Function to get the Kp-value of the id-PI-Controller during runtime
 *
 * @param self uz_CurrentControl_t instance
 */
float uz_CurrentControl_get_Kp_id(uz_CurrentControl_t* self);

/**
 * @brief Function to get the Kp-value of the iq-PI-Controller during runtime
 *
 * @param self uz_CurrentControl_t instance
 */
float uz_CurrentControl_get_Kp_iq(uz_CurrentControl_t* self);

/**
 * @brief Function to change the Kp-value of the id-PI-Controller during runtime
 *
 * @param self uz_CurrentControl_t instance
 * @param Kp_id new Kp_id value. Must be greater or equal than 0.0f
 */
void uz_CurrentControl_set_Kp_id(uz_CurrentControl_t* self, float Kp_id);

/**
 * @brief Function to change the Ki-value of the id-PI-Controller during runtime
 *
 * @param self uz_CurrentControl_t instance
 * @param Ki_id new Ki_id value. Must be greater or equal than 0.0f
 */
void uz_CurrentControl_set_Ki_id(uz_CurrentControl_t* self, float Ki_id);

/**
 * @brief Function to change the Kp-value of the iq-PI-Controller during runtime
 *
 * @param self uz_CurrentControl_t instance
 * @param Kp_iq new Kp_iq value. Must be greater or equal than 0.0f
 */
void uz_CurrentControl_set_Kp_iq(uz_CurrentControl_t* self, float Kp_iq);

/**
 * @brief Function to change the Ki-value of the iq-PI-Controller during runtime
 *
 * @param self uz_CurrentControl_t instance
 * @param Ki_iq new Ki_iq value. Must be greater or equal than 0.0f
 */
void uz_CurrentControl_set_Ki_iq(uz_CurrentControl_t* self, float Ki_iq);

/**
 * @brief Function to change the PMSM parameters during runtime
 * 
 * @param self uz_CurrentControl_t instance
 * @param pmsm_config PMSM_config struct with updated values
 */
void uz_CurrentControl_set_PMSM_parameters(uz_CurrentControl_t* self, uz_PMSM_t pmsm_config);

/**
 * @brief Function to change the type of decoupling during runtime
 * 
 * @param self uz_CurrentControl_t instance
 * @param decoupling_select enum CurrentControl decoupling selector \n
							 no_decoupling \n
							 linear_decoupling
 */
void uz_CurrentControl_set_decoupling_method(uz_CurrentControl_t* self, enum uz_CurrentControl_decoupling_select decoupling_select);

/**
 * @brief Function to change the max_modulation_index of the Space Vector Limitation during runtime
 * 
 * @param self uz_CurrentControl_t instance
 * @param max_modulation_index Max possible modulation index for the chosen modulation method. I.e. 1/sqrt(3) for Space-Vector-Modulation
 */
void uz_CurrentControl_set_max_modulation_index(uz_CurrentControl_t* self, float max_modulation_index);

/**
 * @brief Returns the current value of the external clamping signal
 * 
 * @param self uz_CurrentControl_t instance
 * @return current value as bool 
 */
bool uz_CurrentControl_get_ext_clamping(uz_CurrentControl_t* self);

#endif // UZ_CURRENTCONTROL_H
