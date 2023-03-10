#ifndef UZ_SPEEDCONTROL_H
#define UZ_SPEEDCONTROL_H

#pragma once
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
/**
 * @brief Object definition for uz_SpeedControl_t
 *
 */
typedef struct uz_SpeedControl_t uz_SpeedControl_t;

/**
 * @brief Configuration struct for SpeedControl. Accessible by the user
 */
struct uz_SpeedControl_config {
    bool is_field_weakening_active; /**< flag to enable field_weaking */
    uz_PMSM_t config_PMSM; /**< PMSM struct which carries necessary motor related parameters for field weakening */
	struct uz_PI_Controller_config config_controller; /**< Configuration struct for speed-Controller */
};

/**
 * @brief Initialization of the SpeedController object
 *
 * @param config uz_SpeedControl_config configuration struct
 * @return Pointer to uz_SpeedControl_t object
 */
uz_SpeedControl_t* uz_SpeedControl_init(struct uz_SpeedControl_config config);

/**
 * @brief Calculates reference currents for a SpeedControl
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param omega_m_rad_per_sec mechanical rotational speed in 1/rad
 * @param n_ref_rpm reference speed in 1/min
 * @param V_dc_volts DC-link voltage in volts
 * @param id_ref_Ampere reference d-axis current
 * @return uz_dq_t reference currents in Ampere
 */
uz_3ph_dq_t uz_SpeedControl_sample(uz_SpeedControl_t* self, float omega_m_rad_per_sec, float n_ref_rpm, float V_dc_volts, float id_ref_Ampere);

/**
 * @brief Resets the PI-Controller inside the uz_SpeedControl_t 
 *
 * @param self pointer to uz_SpeedControl_t object
 */
void uz_SpeedControl_reset(uz_SpeedControl_t* self);

/**
 * @brief Sets the ext_clamping signal true or false
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param ext_clamping external clamping signal. True=clamping gets activated, false=clamping gets disabled
 */
void uz_SpeedControl_set_ext_clamping(uz_SpeedControl_t* self, bool ext_clamping);

/**
 * @brief Enables or disables the field weakening
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param is_field_weakening_active status flag if field_weakening should be enabled = true or disabled
 */
void uz_SpeedControl_set_field_weakening(uz_SpeedControl_t* self, bool is_field_weakening_active);

/**
 * @brief  Function to change the Ki-value of the PI-Controller during runtime
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param new_Ki value for Ki. Must be greater or equal than 0.0f
 */
void uz_SpeedControl_set_Ki(uz_SpeedControl_t* self, float new_Ki);

/**
 * @brief  Function to change the Kp-value of the PI-Controller during runtime
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param new_Kp value for Ki. Must be greater or equal than 0.0f
 */
void uz_SpeedControl_set_Kp(uz_SpeedControl_t* self, float new_Kp);

/**
 * @brief Function to change the saturation limits of the PI-Controller during runtime 
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param upper_limit new value for upper limit. Must be greater than lower limit
 * @param lower_limit new value for lower limit
 */
void uz_SpeedControl_update_limits(uz_SpeedControl_t* self, float upper_limit, float lower_limit);

/**
 * @brief Updates the motor related params in the uz_PMSM_t struct
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param input uz_PMSM_t struct with new values
 */
void uz_SpeedControl_set_PMSM_config(uz_SpeedControl_t* self, uz_PMSM_t input);

#endif // UZ_SPEEDCONTROL_H
