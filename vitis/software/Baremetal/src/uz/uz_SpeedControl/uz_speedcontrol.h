#ifndef UZ_SPEEDCONTROL_H
#define UZ_SPEEDCONTROL_H

#pragma once
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"

/**
 * @brief Initialization of the PI-Controller object
 *
 * @param config uz_PI_Controller_config configuration struct
 * @return Pointer to uz_PI_Controller instance
 */
uz_PI_Controller* uz_SpeedControl_init(struct uz_PI_Controller_config config);

/**
 * @brief Calculates reference currents for a SpeedControl
 * 
 * @param self uz_PI_Controller instance
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @param n_ref_rpm reference speed in 1/min
 * @param V_dc_volts DC-link voltage in volts
 * @param id_ref_Ampere reference d-axis current
 * @param config_PMSM uz_PMSM_t config struct
 * @param ext_clamping external clamping signal
 * @return uz_dq_t reference currents in Ampere
 */
uz_3ph_dq_t uz_SpeedControl_sample(uz_PI_Controller* self, float omega_el_rad_per_sec, float n_ref_rpm, float V_dc_volts, float id_ref_Ampere, uz_PMSM_t config_PMSM, bool ext_clamping);

/**
 * @brief Resets the PI-Controller
 *
 * @param self uz_PI_Controller instance
 */
void uz_SpeedControl_reset(uz_PI_Controller* self);
#endif // UZ_SPEEDCONTROL_H
