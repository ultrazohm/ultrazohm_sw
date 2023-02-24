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
    bool enable_field_weakening; /**< flag to enable field_weaking */
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
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @param n_ref_rpm reference speed in 1/min
 * @param V_dc_volts DC-link voltage in volts
 * @param id_ref_Ampere reference d-axis current
 * @param config_PMSM uz_PMSM_t config struct
 * @param ext_clamping external clamping signal
 * @return uz_3ph_dq_t reference currents in Ampere
 */
uz_3ph_dq_t uz_SpeedControl_sample(uz_SpeedControl_t* self, float omega_el_rad_per_sec, float n_ref_rpm, float V_dc_volts, float id_ref_Ampere, uz_PMSM_t config_PMSM, bool ext_clamping);

/**
 * @brief Resets the PI-Controller inside the uz_SpeedControl_t 
 *
 * @param self pointer to uz_SpeedControl_t object
 */
void uz_SpeedControl_reset(uz_SpeedControl_t* self);

/**
 * @brief Enables or disables the field weakening
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param field_weakening_status status flag if field_weakening should be enabled = true or disabled
 */
void uz_SpeedControl_set_field_weakening(uz_SpeedControl_t* self, bool field_weakening_status);

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
 * @param new_Kp value for Kp. Must be greater or equal than 0.0f
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
#endif // UZ_SPEEDCONTROL_H
