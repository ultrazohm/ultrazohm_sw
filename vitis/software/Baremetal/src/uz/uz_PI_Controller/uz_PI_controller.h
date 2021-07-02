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

float uz_PI_Controller_sample(uz_PI_Controller* self, float referenceValue, float actualValue, bool ext_clamping);

#endif // UZ_PI_CONTROLLER_H
