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
    float rs_calc[20];
    float rs_speeds[20];

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
    sample_finished,
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
