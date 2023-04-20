#ifndef UZ_ENCODER_OFFSET_ESTIMATION_H
#define UZ_ENCODER_OFFSET_ESTIMATION_H

#include "../uz_SystemTime/uz_SystemTime.h"
#include "../uz_filter_cumulativeavg/uz_filter_cumulativeavg.h"
#include "../../globalData.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"

#define OFFSET_STEP_RAD 0.01f                       // set stepsize to step through thetas
#define OFFSET_RANGE_RAD 0.2f                       // set range to measure around inital theta (start at init_theta-OFFSET_RANGE_RAD and end at init_theta+OFFSET_RANGE_RAD), should be integer multiple of OFFSET_STEP_RAD
#define OFFSET_DELAY_BETWEEN_SETPOINTS_SEC 1.0f     // a delay between the rotations (positive, negative and next theta's positive can be set)
#define OFFSET_ACCELLERATE_TIME_SEC 3.0f            // the time to let the motor accellerate with the given q-current

/**
 * @brief Configuration struct for the PMSM model IP-Core driver
 * 
 */
struct uz_encoder_offset_estimation_config {
    actualValues *actual;       /**< Pointer to global data actual values */
    float polepair;             /**< Polepairs of maschine */
    float setpoint_current;     /**< Setpoint current for tests */
};

/**
 * @brief Object definition for generating a PI-Controller
 *
 */
typedef struct uz_encoder_offset_estimation_t uz_encoder_offset_estimation_t;

/**
 * @brief Initialize an instance
 * 
 * @param config Config struct
 * @return uz_encoder_offset_estimation_t* Pointer to an initialized instance
 */
uz_encoder_offset_estimation_t* uz_encoder_offset_estimation_init(struct uz_encoder_offset_estimation_config);

/**
 * @brief Step the function
 * 
 * @param self Pointer to instance
 * @return setpoint for current controller
 */
uz_3ph_dq_t uz_encoder_offset_estimation_step(uz_encoder_offset_estimation_t* self);

/**
 * @brief Get finished flag
 * 
 * @param self Pointer to instance
 * @return finished flag
 */
bool uz_encoder_offset_estimation_get_finished(uz_encoder_offset_estimation_t* self);

#endif // uz_encoder_offset_estimation_H
