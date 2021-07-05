#ifndef UZ_PI_CONTROLLER_H
#define UZ_PI_CONTROLLER_H

#pragma once
#include "../uz_HAL.h"
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
	float d_y_max;
	float d_y_min;
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
 * @brief Similar to the Simulink-Deadzone block. If signal is within the deadzone, output is zero. Otherwise it outputs the input signal substracted by either the upper or lower limit.
 *
 * @param input any input signal
 * @param d_y_max Max limit for deadzone/saturation
 * @param d_y_min min limit for deadzone/saturation
 * @return float Returns last sample
 */
float uz_PI_Controller_Dead_Zone(float input, float d_y_max, float d_y_min);

/**
 * @brief Outputs 0 if input is 0. Outputs 1 if input is positive and -1 if input is negative. Similar to the sign block in Simulink.
 *
 * @param input any input signal
 * @return int Returns sign for last sample
 */
int uz_PI_Controller_get_sign_of_value(float input);

/**
 * @brief Compares the values before and after the Integrator and decides if clamping is necessary
 *
 * @param preIntegrator value before the integrator
 * @param preSat value after the integrator and before the saturation
 * @param d_y_max Max limit for deadzone/saturation
 * @param d_y_min min limit for deadzone/saturation
 * @return Returns true if clamping is necessary
 */
bool uz_PI_Controller_Clamping_Circuit(float preIntegrator, float preSat, float d_y_max, float d_y_min);

/**
 * @brief Calculates the last sample of the PI-Controller
 * 
 * @param self uz_PI_Controller object
 * @param referenceValue reference values for error calculation
 * @param actualValue actual value for error calculation
 * @param ext_clamping input for external clamping signal
 * @return float Returns last sample of PI-Controller
 */
float uz_PI_Controller_sample(uz_PI_Controller* self, float referenceValue, float actualValue, bool ext_clamping);

/**
 * @brief Resets the PI-Controller
 * 
 * @param self uz_PI_Controller object
 */
void uz_PI_Controller_reset(uz_PI_Controller* self);

/**
 * @brief Updates the Ki parameter with a new one
 * 
 * @param self uz_PI_Controller object
 * @param new_Ki new value for Ki
 */
void uz_PI_Controller_set_Ki(uz_PI_Controller* self, float new_Ki);

/**
 * @brief Updates the Kp parameter with a new one
 * 
 * @param self uz_PI_Controller object
 * @param new_Kp new value for Ki
 */
void uz_PI_Controller_set_Kp(uz_PI_Controller* self, float new_Kp);
#endif // UZ_PI_CONTROLLER_H
