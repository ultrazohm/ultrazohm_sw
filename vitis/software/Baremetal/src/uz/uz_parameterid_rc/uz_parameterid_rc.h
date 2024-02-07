#ifndef UZ_PARAMETERID_RC_H
#define UZ_PARAMETERID_RC_H

#include "../uz_global_configuration.h"
#include <stdbool.h> 
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct uz_parameterid_rc_t uz_parameterid_rc_t; 

struct uz_parameterid_rc_config_t
{
    float id_ref;
    float iq_ref;
    float n_ref;
    float wait_time;
    float isr_steptime;
    float sample_time;
};

struct uz_parameterid_rc_set_values_t
{
    float id_set;
    float iq_set;
    float n_set;
};

struct uz_parameterid_rc_counter_t
{
    uint32_t wait;
    uint32_t wait_max;
    uint32_t meas;
    uint32_t meas_max;
    uint32_t isr;
};

struct uz_parameterid_rc_u_ind_t
{
    float gen_d;
    float gen_q;
    float mot_d;
    float mot_q;
};

struct uz_parameterid_rc_i_meas_t
{
    float gen_id;
    float gen_iq;
    float mot_id;
    float mot_iq;
};

struct uz_parameterid_rc_u_meas_t
{
    float gen_ud;
    float gen_uq;
    float mot_ud;
    float mot_uq;
};

struct uz_parameterid_rc_sample_var_t
{
    float sum_ud;
    float sum_uq;
    float sum_id;
    float sum_iq;
    float sum_n;
    float mean_ud;
    float mean_uq;
    float mean_id;
    float mean_iq;
    float mean_n;
    float r_s;
};

struct uz_parameterid_rc_meas_out_t
{
    float rc_d;
    float rc_q;
    struct uz_parameterid_rc_u_ind_t u_ind_gen_out;
    struct uz_parameterid_rc_set_values_t set_out;
    bool gen;
};

struct uz_parameterid_rc_calc_rc_t
{
    float i_dm;
    float i_qm;
    float i_di;
    float i_qi;
    
};

enum state{
    sample,
    generator,
    wait,
    start,
    calc_mot,
    calc_gen,
    switch2gen,
    check_u_ind,
    finished,
    calc_rc,
    };

uz_parameterid_rc_t* uz_parameterid_rc_init(struct uz_parameterid_rc_config_t internal_data);
struct uz_parameterid_rc_config_t uz_parameterid_rc_get_config(uz_parameterid_rc_t* self);
struct uz_parameterid_rc_meas_out_t uz_parameterid_rc_generate_outputs(uz_parameterid_rc_t* self, float ud, float uq, float id, float iq, float n);
uz_parameterid_rc_t* uz_parameterid_rc_reset_meas(uz_parameterid_rc_t* self);

#endif // UZ_PARAMETERID_RC_H
