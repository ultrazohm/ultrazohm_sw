#ifndef UZ_PARAMETERID_RS_H
#define UZ_PARAMETERID_RS_H

#include "../uz_global_configuration.h"

typedef struct uz_parameterid_rs_t uz_parameterid_rs_t;

struct uz_parameterid_rs_config_t
{
    float n_start;
    float n_end;
    float n_steps;
    float i_start;
    float i_diff;
    float i_steps;
    float isr_steptime;
};

struct uz_parameterid_rs_increments_t
{
    float n_increment;
    float i_increment;

};

struct uz_parameterid_output
{
    float n_sample;
    float i_sample;
    float isr_stepcounter;
};

uz_parameterid_rs_t *uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config);
struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t* self);
struct uz_parameterid_rs_increments_t uz_parameterid_rs_get_current_increments(uz_parameterid_rs_t* self);
float uz_parameterid_rs_get_elapsed_time(uz_parameterid_rs_t* self);
void uz_parameterid_rs_reset(uz_parameterid_rs_t* self);
struct uz_parameterid_output uz_parameterid_rs_generate_outputs(uz_parameterid_rs_t* self);
float uz_parameterid_rs_get_isr_counter(uz_parameterid_rs_t* self);
float uz_parameterid_rs_get_end_time(uz_parameterid_rs_t* self);
float uz_parameterid_rs_sample(uz_parameterid_rs_t* self, struct uz_parameterid_output input, float ud, float id, float n);


#endif // UZ_PARAMETERID_RS_H
