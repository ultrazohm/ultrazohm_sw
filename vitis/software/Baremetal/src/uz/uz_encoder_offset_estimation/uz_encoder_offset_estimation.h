#ifndef UZ_ENCODER_OFFSET_ESTIMATION_H
#define UZ_ENCODER_OFFSET_ESTIMATION_H

#include "../uz_SystemTime/uz_SystemTime.h"
#include "../uz_filter_cumulativeavg/uz_filter_cumulativeavg.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"

#define OFFSET_STEP_RAD 0.01f                       // set stepsize to step through thetas
#define OFFSET_RANGE_RAD 0.2f                       // set range to measure around inital theta (start at init_theta-OFFSET_RANGE_RAD and end at init_theta+OFFSET_RANGE_RAD), should be integer multiple of OFFSET_STEP_RAD


/**
 * @brief Configuration struct for the encoder offset estimation instance
 * 
 */
struct uz_encoder_offset_estimation_config {
    float* ptr_measured_rotor_angle;/**< Pointer to rotor angle measurement */
    float* ptr_offset_angle;        /**< Pointer to offset variable */
    float* ptr_actual_omega_el;     /**< Pointer to actual omega electric in rad/s */
    float* ptr_actual_u_q_V;        /**< Pointer to actual q-axis voltage in V */
    float setpoint_current;         /**< Setpoint current for tests */
    float min_omega_el;             /**< Target omega electric (rad/s) to reach for flux linkage measurement */
};

/**
 * @brief enum with error/status messages. See Table under Workflow for numeric expressions.
 */
enum uz_encoder_offset_estimation_diagnose
{
    encoderoffset_no_error = 0,         /**< Equals 0: No specific diagnose message active. */
    encoderoffset_speed_not_reached,    /**< Equals 1: The min_omega_el could not be reached with the given setpoint_current and the statemachine is stuck. */
    encoderoffset_finished,             /**< Equals 2: The process is finished and the resulting offset angle is saved in ptr_offset_angle. */
    encoderoffset_lower_limit,          /**< Equals 3: The process is finished and the resulting offset angle equals the smallest angle tested. Check that all inputs are correct or redo measurement with different range. */
    encoderoffset_upper_limit           /**< Equals 4: The process is finished and the resulting offset angle equals the largest angle tested. Check that all inputs are correct or redo measurement with different range. */
};

/**
 * @brief Feedback struct for user
 * 
 */
struct uz_encoder_offset_estimation_status {
    float progress;                                             /**< Progress of estimation from 0-1 */
    enum uz_encoder_offset_estimation_diagnose diagnose;        /**< Diagnose and status */
};

/**
 * @brief Object definition for generating encoder offset estimation instance
 *
 */
typedef struct uz_encoder_offset_estimation_t uz_encoder_offset_estimation_t;

/**
 * @brief Initialize an instance
 * 
 * @param config Config struct
 * @return uz_encoder_offset_estimation_t* Pointer to an initialized instance
 */
uz_encoder_offset_estimation_t* uz_encoder_offset_estimation_init(struct uz_encoder_offset_estimation_config config);

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

/**
 * @brief Set (new) setpoint_current to object
 * 
 * @param self Pointer to instance
 * @param float setpoint_current
 */
void uz_encoder_offset_estimation_set_setpoint_current(uz_encoder_offset_estimation_t* self, float setpoint_current);

/**
 * @brief Set (new) min_omega_el to object
 * 
 * @param self Pointer to instance
 * @param float min_omega_el
 */
void uz_encoder_offset_estimation_set_min_omega_el(uz_encoder_offset_estimation_t* self, float min_omega_el);

/**
 * @brief Reset states for new usage
 * 
 * @param self Pointer to instance
 */
void uz_encoder_offset_estimation_reset_states(uz_encoder_offset_estimation_t* self);

/**
 * @brief Get status
 * 
 * @param self Pointer to instance
 * @return status struct
 */
struct uz_encoder_offset_estimation_status uz_encoder_offset_estimation_get_status(uz_encoder_offset_estimation_t* self);

#endif // uz_encoder_offset_estimation_H
