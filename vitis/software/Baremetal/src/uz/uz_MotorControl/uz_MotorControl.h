#ifndef UZ_MOTORCONTROL_H
#define UZ_MOTORCONTROL_H

#include "../uz_HAL.h"
#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include <stdlib.h>
#include <stdbool.h>

struct uz_MotorControl_config {
	uz_PMSM_t config_PMSM; /**< Configuration struct for PMSM parameters */

};

/**
 * @brief Object definition for MotorControl
 *
 */
typedef struct uz_MotorControl_t uz_MotorControl_t;

/**
 * @brief Initialization of the uz_MotorControl_t object
 *
 * @param config configuration struct for MotorControl
 * @return uz_MotorControl_t* Pointer to uz_MotorControl_t instance
 */
uz_MotorControl_t* uz_MotorControl_init(struct uz_CurrentControl_config config);


#endif // UZ_MOTORCONTROL_H
