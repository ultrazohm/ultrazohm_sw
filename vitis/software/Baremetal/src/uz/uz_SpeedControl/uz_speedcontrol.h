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
 * @brief Calculates reference torque 
 * 
 * @param self pointer to uz_SpeedControl_t object
 * @param omega_m_rad_per_sec mechanical rotational speed in 1/rad
 * @param n_ref_rpm reference speed in 1/min
 * @return reference torque in Nm
 */
float uz_SpeedControl_sample(uz_SpeedControl_t* self, float omega_m_rad_per_sec, float n_ref_rpm);

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

#endif // UZ_SPEEDCONTROL_H
