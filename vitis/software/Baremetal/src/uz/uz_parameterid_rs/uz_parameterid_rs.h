#ifndef UZ_PARAMETERID_RS_H
#define UZ_PARAMETERID_RS_H

#include "../uz_global_configuration.h"
#include <stdint.h>

typedef struct uz_parameterid_rs_t uz_parameterid_rs_t;

struct uz_parameterid_rs_config_t
{
    float n_start;
    float n_end;
    float n_steps;
    float i_start;
    float i_diff;
    float i_repeats;
    float i_steptime;
    float wait_time;
    float isr_steptime;
};

struct uz_parameterid_rs_increments_t
{
    float n_increment;
    float i_increment;

};

struct uz_parameterid_rs_counter_t
{
    int32_t wait;
    int32_t wait_max;
    int32_t i_max;
    int32_t i;
    int32_t i_repeat;
    int32_t n;
    int32_t meas;
    int32_t rs;
};

struct uz_parameterid_output
{
    float n_sample;
    float i_sample;
    float isr_stepcounter;
};

struct uz_parameterid_rs_sample_var
{
    float sum_ud;
    float sum_id;
    float mean_ud;
    float mean_id;
    float ref_ud;
    float ref_id;
    float rs;
    float sum_rs;
};

struct uz_parameterid_rs_sample_output
{
    float rs_calc[10];
    float rs_speeds[10];

};

enum state{
    start,
    i_start,
    i_increment,
    wait,
    n_increment,
    finished,
    };

enum sample {
    sample_off,
    sample_on,
    calc,
    rs_write,
};




uz_parameterid_rs_t *uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config);
struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t* self);
struct uz_parameterid_rs_increments_t uz_parameterid_rs_get_current_increments(uz_parameterid_rs_t* self);
void uz_parameterid_rs_reset(uz_parameterid_rs_t* self);
struct uz_parameterid_output uz_parameterid_rs_generate_outputs(uz_parameterid_rs_t* self, float ud, float id);
float uz_parameterid_rs_get_isr_counter(uz_parameterid_rs_t* self);
void uz_parameterid_rs_sample(uz_parameterid_rs_t* self, float ud, float id);
enum state uz_parameterid_rs_get_current_state(uz_parameterid_rs_t* self);
struct uz_parameterid_rs_sample_output uz_parameterid_rs_get_rs(uz_parameterid_rs_t* self);
enum sample uz_parameterid_rs_get_current_sample_state(uz_parameterid_rs_t* self);


#endif // UZ_PARAMETERID_RS_H
