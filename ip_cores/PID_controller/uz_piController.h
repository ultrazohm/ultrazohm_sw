#ifndef UZ_PICONTROLLER_H
#define UZ_PICONTROLLER_H
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

/**
 * @brief Configuration struct for PI-Controller. Pass to init function. Accessible by the user
 */
typedef struct uz_PI_Controller_config {
	float Kp; /**< Proportional gain for PI-Controller. Must be greater or equal than 0.0f */
	float Ki; /**< Integral gain for PI-Controller. Must be greater or equal than 0.0f */
	float samplingTime_sec; /**< SamplingTime of the PI-Controller in seconds. Must be greater than 0.0f */
	float upper_limit; /**< Upper limit for the output limitation. Must be greater than lower limit */
	float lower_limit; /**< Lower limit for the output limitation */
}uz_PI_Controller_config;

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
void uz_PI_Controller_sample(uz_PI_Controller_config* self, bool I_rst, float referenceValue, float actualValue, bool ext_clamping, float* output);

#endif // UZ_PICONTROLLER_H
