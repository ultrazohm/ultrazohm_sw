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
    float pn;
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
    uint32_t repeat;
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
    float sum_M;
    float mean_ud;
    float mean_uq;
    float mean_id;
    float mean_iq;
    float mean_n;
    float mean_omega;
    float r_s;
};

struct uz_parameterid_rc_meas_out_t
{
    float mot_rc_d;
    float mot_rc_q;
    float gen_rc_d;
    float gen_rc_q;
    struct uz_parameterid_rc_set_values_t set_out;
    bool generator_mode; // is_generator_operating_point
    uint32_t finished;
};

struct uz_parameterid_rc_calc_rc_t
{
    float i_dm;
    float i_qm;
    float i_di;
    float i_qi;
    
};

enum rc_state{
    rc_sample,
    rc_generator,
    rc_wait,
	rc_wait_uind,
    rc_start,
    rc_calc_mot,
    rc_calc_gen,
    rc_switch2gen,
    rc_check_u_ind,
    rc_finished,
    rc_repeat,
    rc_calc_rc,
    };


struct uz_parameterid_rc_repeat{
    float save_mot_rc_d [10];
    float save_mot_rc_q [10];
    float save_gen_rc_d [10];
    float save_gen_rc_q [10];
    float save_p_fe_mot[10];
    float save_p_fe_gen[10];
    float save_p_el_gen[10];
    float save_p_el_mot[10];
    float save_p_cu_gen[10];
    float save_p_cu_mot[10];
    float save_p_wf_gen[10];
    float save_p_wf_mot[10];
    float save_p_mech_gen[10];
    float save_p_mech_mot[10];
    float save_M_i_mot[10];
    float save_M_i_gen[10];
    float save_M_meas_mot[10];
    float save_M_meas_gen[10];
    float save_M_wf_mot[10];
    float save_M_wf_gen[10];
    float save_iqm_mot[10];
    float save_iqm_gen[10];
    float save_iqi_mot[10];
    float save_iqi_gen[10];
    float save_idm_mot[10];
    float save_idm_gen[10];
    float save_idi_mot[10];
    float save_idi_gen[10];
    float save_u_ind_q_mot[10];
    float save_u_ind_q_gen[10];
    float save_u_ind_d_mot[10];
    float save_u_ind_d_gen[10];

};


uz_parameterid_rc_t* uz_parameterid_rc_init(struct uz_parameterid_rc_config_t internal_data);
struct uz_parameterid_rc_config_t uz_parameterid_rc_get_config(uz_parameterid_rc_t* self);
struct uz_parameterid_rc_meas_out_t uz_parameterid_rc_generate_outputs(uz_parameterid_rc_t* self, float ud, float uq, float id, float iq, float n, float M);
uz_parameterid_rc_t* uz_parameterid_rc_reset_meas(uz_parameterid_rc_t* self);
uz_parameterid_rc_t* uz_parameterid_rc_reset(uz_parameterid_rc_t* self);
void uz_parameterid_rc_repeat(uz_parameterid_rc_t* self);

#endif // UZ_PARAMETERID_RC_H
