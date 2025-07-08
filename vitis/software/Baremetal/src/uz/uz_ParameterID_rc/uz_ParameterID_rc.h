#ifndef UZ_PARAMETERID_RC_H
#define UZ_PARAMETERID_RC_H

#include "../uz_global_configuration.h"
#include <stdbool.h> 
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/**
 * @brief Object definition for the flux maps measurement
 * 
 */
typedef struct uz_parameterID_rc_t uz_parameterID_rc_t;

/**
 * @brief Configuration struct for flux maps measurement. Pass to init function. Accessible by the user
 * 
 */
struct uz_parameterID_rc_config_t {
    float abs_id_max_Amps ; /**< Absolute maximum value of d-current.   */
    float abs_iq_max_Amps ; /**< Absolute maximum value of q-current.  */
    float n_start_rpm; /**< Initial speed of the measurement routine.  */
    float n_stop_rpm; /**< Final speed of the measurement routine.  */
    uint32_t id_steps; /**< Number of steps from -id to zero.  */
    uint32_t iq_steps; /**< Number of steps from iq to zero.  */
    uint32_t n_steps; /**< Number of steps from initial to final speed.  */
    bool check_temp; /**< Set true, if temperature should be checked between operating points.  */
};

/**
 * @brief Output struct of the measurement routine. id_ref_Amps, iq_ref_Amps and n_ref_rpm define operating point.
 * 
 */
struct uz_parameterID_rc_ref_val_t {
    float id_ref_Amps; /**< Reference value for id.  */
    float iq_ref_Amps; /**< Reference value for iq.  */
    float n_ref_rpm; /**< Reference value for speed.  */
    float data_valid; /**< Data valid flag. Is 1.0f, when data is valid. Used to average each operating point in post processing  */
    float operating_points_all /**< Operating point counter */;
};


struct uz_parameterID_rc_set_values_t{
    float id_set_Amps;
    float iq_set_Amps;
    float n_set_rpm;
};

struct uz_parameterID_rc_max_steps_t{
    uint32_t operatingpoints_idq;
    uint32_t operatingpoints_n;
};

struct uz_parameterid_rc_counter_t{
    float increment_id;
    float increment_iq;
    uint32_t increment_n;
    uint32_t isr;
    uint32_t wait;
    uint32_t operating_points_idq;
    uint32_t operating_points_n;
    uint32_t operating_points_all;
};

struct uz_parameterid_rc_size_increments_t{
    float id_Amps;
    float iq_Amps;
    float n_rpm;
};

struct uz_parameterid_rc_temp_check_t{
    float initial_temp;
    float temp_min;
    float temp_max;
    bool temp_check_done;
};

enum rc_state{
    rc_start,
    rc_set_idq,
    rc_finished,
    rc_wait,
    rc_idle,
    rc_sample_on,
    rc_sample_off,
    rc_increment_idq,
    rc_increment_n,
};


/**
 * @brief Initialization of the measurement rountine
 * 
 * @param initial_config uz_parameterID_rc_config_t configuration struct
 * @return uz_parameterID_rc_t* Pointer to the uz_parameterID_rc instance
 */
uz_parameterID_rc_t* uz_parameterID_rc_init(struct uz_parameterID_rc_config_t initial_config);

struct uz_parameterID_rc_config_t uz_parameterID_rc_get_config(uz_parameterID_rc_t* self);

/**
 * @brief Controls the measurement protocol for the flux maps measurement.
 * 
 * @param self uz_parameterID_rc instance
 * @param temp_degrees External value from temperature measurement. Only needed, if check_temp is true
 * @return struct uz_parameterID_rc_ref_val_t Returns reference values for speed and current control, as well as data valid flag and operating point counter.
 */
struct uz_parameterID_rc_ref_val_t uz_parameterID_rc_generate_idq_ref(uz_parameterID_rc_t* self, float temp_degrees);
void uz_parameterID_rc_set_next_operating_point_idq(uz_parameterID_rc_t* self);
void uz_parameterID_rc_set_next_operating_point_n(uz_parameterID_rc_t* self);
struct uz_parameterid_rc_counter_t uz_parameterID_rc_get_counter(uz_parameterID_rc_t* self);
void uz_parameterID_rc_check_temperature(uz_parameterID_rc_t* self, float temp_degrees);
#endif // UZ_PARAMETERID_RC_H
