#ifndef UZ_PARAMETERID_RS_H
#define UZ_PARAMETERID_RS_H

#include "../uz_global_configuration.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object definition for the stator resistance measurement
 * 
 */
typedef struct uz_parameterid_rs_t uz_parameterid_rs_t;


/**
 * @brief Configuration struct for stator resistance measurement. Pass to init function. Accessible by the user
 * 
 */
struct uz_parameterid_rs_config_t
{
    float n_start_rpm; /**< Initial speed of the measurement routine.   */
    float n_end_rpm; /**< Final speed of the measurement routine.   */
    float n_steps; /**< Number of steps from initial to final speed.   */
    float i_pos_Amps; /**< Positive d-current for measurement. */
    float i_neg_Amps; /**< Negative d-current for measurement. */
    float i_repeats; /**< Number of repeats for the step from negative d-current to positive d-current . */
    float i_steptime; /**< Duration of one step . */
    float wait_time; /**< Wait time before data valid flag is set. */
    float isr_steptime; /**< Definition of isr steptime in order to configure internal counters. */
    float abs_iq_max_Amps; /**< Maximum q-current for heating phases. */
    bool check_temp; /**< Set true, if temperature should be checked between operating points.  */
 };

struct uz_parameterid_rs_increments_t
{
    float n_increment;
    float i_increment;

};

struct uz_parameterid_rs_counter_t
{
    uint32_t wait;
    uint32_t wait_max;
    uint32_t i_max;
    uint32_t i;
    uint32_t i_repeat;
    uint32_t n;
    uint32_t meas;
    uint32_t rs;
};


/**
 * @brief Output struct of the measurement routine. id_ref_Amps, iq_ref_Amps and n_ref_rpm define operating point.
 * 
 */
struct uz_parameterid_output
{
    float n_ref_rpm; /**< Reference value for speed.  */
    float id_ref_Amps; /**< Reference value for id.  */
    float iq_ref_Amps; /**< Reference value for iq.  */
    float data_valid; /**< Data valid flag. Is 1.0f, when data is valid. Can be used in post-processing to filter for valid data  */
};

enum state{
    start,
    i_pos_Amps,
    i_neg_Amps,
    wait,
    n_increment,
    finished,
    temp_check,
    };

struct uz_parameterid_rs_temp_check_t{
    float initial_temp;
    float temp_min;
    float temp_max;
    bool temp_check_done;
};


/** @brief Initialize the stator resistance measurement object
 * 
 * @param initial_config Configuration struct for the stator resistance measurement
 * @return uz_parameterid_rs_t* Pointer to the initialized object
 */
uz_parameterid_rs_t *uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config);
struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t* self);
struct uz_parameterid_rs_increments_t uz_parameterid_rs_get_current_increments(uz_parameterid_rs_t* self);
void uz_parameterid_rs_reset(uz_parameterid_rs_t* self);
struct uz_parameterid_output uz_parameterid_rs_generate_outputs(uz_parameterid_rs_t* self, float temp_degrees);
float uz_parameterid_rs_get_isr_counter(uz_parameterid_rs_t* self);
enum state uz_parameterid_rs_get_current_state(uz_parameterid_rs_t* self);
void uz_parameterID_rs_check_temperature(uz_parameterid_rs_t* self, float temp_degrees);




#endif // UZ_PARAMETERID_RS_H
