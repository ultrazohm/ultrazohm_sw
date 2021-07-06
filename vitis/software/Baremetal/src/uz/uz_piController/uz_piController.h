#ifndef UZ_PICONTROLLER_H
#define UZ_PICONTROLLER_H

#pragma once
#include "../uz_HAL.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Configuration struct for PI-Controller. Pass to init function. Accessible by the user
 */
typedef struct uz_PI_Controller_config {
	float Kp;
	float Ki;
	float samplingTime_sec;
	float upper_threshold;
	float lower_threshold;
} uz_PI_Controller_config;

/**
 * @brief Object definition for generating a PI-Controller
 *
 */
typedef struct uz_PI_Controller uz_PI_Controller;

/**
 * @brief Initialization of the PI-Controller object
 *
 * @param config uz_PI_Controller_config configuration struct
 * @return Pointer to uz_PI_Controller instance
 */
uz_PI_Controller* uz_PI_Controller_init(uz_PI_Controller_config config);

/**
 * @brief Compares the values before and after the Integrator and decides if clamping is necessary
 *
 * @param preIntegrator value before the integrator
 * @param preSat value after the integrator and before the saturation
 * @param upper_threshold Max limit for deadzone
 * @param lower_threshold min limit for deadzone
 * @return Returns true if clamping is necessary
 */
bool uz_PI_Controller_Clamping_Circuit(float preIntegrator, float preSat, float upper_threshold, float lower_threshold);

/**
 * @brief Calculates the last sample of the PI-Controller
 * 
 * @param self uz_PI_Controller instance
 * @param referenceValue reference value for error calculation
 * @param actualValue actual value for error calculation
 * @param ext_clamping input port for an external clamping signal
 * @return float 
 */
float uz_PI_Controller_sample(uz_PI_Controller* self, float referenceValue, float actualValue, bool ext_clamping);

/**
 * @brief Resets the PI-Controller 
 * 
 * @param self uz_PI_Controller instance
 */
void uz_PI_Controller_reset(uz_PI_Controller* self);

/**
 * @brief Function to change the Ki-value of the PI-Controller during runtime
 * 
 * @param self uz_PI_Controller instance
 * @param new_Ki new value for Ki. Must be >=0.0f
 */
void uz_PI_Controller_set_Ki(uz_PI_Controller* self, float new_Ki);

/**
 * @brief Function to change the Kp-value of the PI-Controller during runtime
 * 
 * @param self uz_PI_Controller instance
 * @param new_Kp new value for Kp. Must be >=0.0f
 */
void uz_PI_Controller_set_Kp(uz_PI_Controller* self, float new_Kp);
#endif // UZ_PICONTROLLER_H
