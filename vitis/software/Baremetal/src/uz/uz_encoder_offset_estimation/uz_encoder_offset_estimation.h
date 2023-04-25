#ifndef UZ_ENCODER_OFFSET_ESTIMATION_H
#define UZ_ENCODER_OFFSET_ESTIMATION_H

#include "../uz_SystemTime/uz_SystemTime.h"
#include "../uz_filter_cumulativeavg/uz_filter_cumulativeavg.h"
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
    float* ptr_measured_rotor_angle;/**< Pointer to rotor angle measurement */
    float* ptr_offset_angle;        /**< Pointer to offset variable */
    float* ptr_actual_omega_el;     /**< Pointer to actual omega electric in rad/s */
    float* ptr_actual_u_q_V;        /**< Pointer to actual q-axis voltage in V */
    float setpoint_current;         /**< Setpoint current for tests */
    float min_omega_el;             /**< Target omega electric (rad/s) to reach for flux linkage measurement */
};

/**
 * @brief enum with error/status messages
 */
enum uz_encoder_offset_estimation_diagnose
{
    encoderoffset_no_error = 0,
    encoderoffset_speed_not_reached,
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
 * @brief Get progress status in range 0..1
 * 
 * @param self Pointer to instance
 * @return progress normed to 1, meaning 0 is not started and 1 is finished
 */
float uz_encoder_offset_estimation_get_progress_status(uz_encoder_offset_estimation_t* self);

#endif // uz_encoder_offset_estimation_H
