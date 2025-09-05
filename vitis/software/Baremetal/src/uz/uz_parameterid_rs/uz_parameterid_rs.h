#ifndef UZ_PARAMETERID_RS_H
#define UZ_PARAMETERID_RS_H

#include "../uz_global_configuration.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct uz_parameterid_rs_t uz_parameterid_rs_t;

struct uz_parameterid_rs_config_t
{
    float n_start_rpm;
    float n_end_rpm;
    float n_steps;
    float i_pos_Amps;
    float i_neg_Amps;
    float i_repeats;
    float i_steptime;
    float wait_time;
    float isr_steptime;
    float abs_iq_max_Amps;
    bool check_temp;
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

struct uz_parameterid_output
{
    float n_ref_rpm;
    float id_ref_Amps;
    float iq_ref_Amps;
    float isr_stepcounter;
    float isr_steptime;
    float data_valid;
    float i_repeat;
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




uz_parameterid_rs_t *uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config);
struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t* self);
struct uz_parameterid_rs_increments_t uz_parameterid_rs_get_current_increments(uz_parameterid_rs_t* self);
void uz_parameterid_rs_reset(uz_parameterid_rs_t* self);
struct uz_parameterid_output uz_parameterid_rs_generate_outputs(uz_parameterid_rs_t* self, float temp_degrees);
float uz_parameterid_rs_get_isr_counter(uz_parameterid_rs_t* self);
enum state uz_parameterid_rs_get_current_state(uz_parameterid_rs_t* self);
void uz_parameterID_rs_check_temperature(uz_parameterid_rs_t* self, float temp_degrees);




#endif // UZ_PARAMETERID_RS_H
