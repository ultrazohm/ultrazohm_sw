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
    float id_ref_Amps;
    float iq_ref_Amps;
    float n_ref_rpm;
    bool multiple_workingpoints;
    float delta_id_Amps;
    float delta_iq_Amps;
    uint32_t id_steps;
    uint32_t iq_steps;
    float wait_time_secs;
    float isr_steptime_secs;
    float sample_time_secs;
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
    uint32_t increment_id;
    uint32_t increment_iq;
    uint32_t working_points;
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
    uint32_t routine_finished_once;
    uint32_t program_finished;
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
    rc_finished_routine,
    rc_finished_program,
    rc_repeat,
    rc_calc_rc,
    };


struct uz_parameterid_rc_repeat{
    float sum_ud_mot;
    float sum_ud_gen;
    float sum_uq_mot;
    float sum_uq_gen;
    float sum_id_mot;
    float sum_id_gen;
    float sum_iq_mot;
    float sum_iq_gen;
    float sum_omega_el;
    float sum_rs;
    float sum_M_meas_mot;
    float sum_M_meas_gen;

    float save_ud_mot[20];
    float save_ud_gen[20];
    float save_uq_mot[20];
    float save_uq_gen[20];
    float save_id_mot[20];
    float save_id_gen[20];
    float save_iq_mot[20];
    float save_iq_gen[20];
    float save_omega_el[20];
    float save_rs[20];
    float save_M_meas_mot[20];
    float save_M_meas_gen[20];
};


uz_parameterid_rc_t* uz_parameterid_rc_init(struct uz_parameterid_rc_config_t internal_data);
struct uz_parameterid_rc_config_t uz_parameterid_rc_get_config(uz_parameterid_rc_t* self);
struct uz_parameterid_rc_meas_out_t uz_parameterid_rc_generate_outputs(uz_parameterid_rc_t* self, float ud, float uq, float id, float iq, float n, float M);
uz_parameterid_rc_t* uz_parameterid_rc_reset_meas(uz_parameterid_rc_t* self);
uz_parameterid_rc_t* uz_parameterid_rc_reset(uz_parameterid_rc_t* self);
void uz_parameterid_rc_repeat(uz_parameterid_rc_t* self);
void uz_parameterid_rc_set_next_workingpoint(uz_parameterid_rc_t* self);
uz_parameterid_rc_t* uz_parameterid_rc_reset_after_change_of_workingpoint(uz_parameterid_rc_t* self);

#endif // UZ_PARAMETERID_RC_H
