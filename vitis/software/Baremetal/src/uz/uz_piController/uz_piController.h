#ifndef UZ_PICONTROLLER_H
#define UZ_PICONTROLLER_H

#include <stdbool.h>

/**
 * @brief Configuration struct for PI-Controller. Pass to init function. Accessible by the user
 */
typedef struct uz_PI_Controller_config {
	float Kp; /**< Proportional gain for PI-Controller. Must be greater or equal than 0.0f */
	float Ki; /**< Integral gain for PI-Controller. Must be greater or equal than 0.0f */
	float samplingTime_sec; /**< SamplingTime of the PI-Controller in seconds. Must be greater than 0.0f */
	float upper_limit; /**< Upper limit for the output limitation. Must be greater than lower limit */
	float lower_limit; /**< Lower limit for the output limitation */
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
 * @param upper_limit Max limit for deadzone. Must be greater than lower limit
 * @param lower_limit min limit for deadzone
 * @return Returns true if clamping is necessary
 */
bool uz_PI_Controller_Clamping_Circuit(float preIntegrator, float preSat, float upper_limit, float lower_limit);

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
 * @param new_Ki new value for Ki. Must be greater or equal than 0.0f
 */
void uz_PI_Controller_set_Ki(uz_PI_Controller* self, float new_Ki);

/**
 * @brief Function to change the Kp-value of the PI-Controller during runtime
 *
 * @param self uz_PI_Controller instance
 * @param new_Kp new value for Kp. Must be greater or equal than 0.0f
 */
void uz_PI_Controller_set_Kp(uz_PI_Controller* self, float new_Kp);

/**
 * @brief Updates the config struct of the PI_Controller instance
 *
 * @param self uz_PI_Controller instance
 * @param config uz_PI_Controller_config configuration struct
 */
uz_PI_Controller* uz_PI_Controller_update_config(uz_PI_Controller* self, uz_PI_Controller_config config);

#endif // UZ_PICONTROLLER_H
