#ifndef UZ_PARAMETERID_RC_H
#define UZ_PARAMETERID_RC_H

#include "../uz_global_configuration.h"
#include <stdbool.h> 
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


typedef struct uz_parameterID_rc_t uz_parameterID_rc_t;

struct uz_parameterID_rc_config_t {
    float abs_id_max_Amps ;
    float abs_iq_max_Amps ;
    float n_start_rpm;
    float n_stop_rpm;
    uint32_t id_steps;
    uint32_t iq_steps;
    uint32_t n_steps;
};

struct uz_parameterID_rc_ref_val_t {
    float id_ref_Amps;
    float iq_ref_Amps;
    float n_ref_rpm;
    float data_valid;
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
};

struct uz_parameterid_rc_size_increments_t{
    float id_Amps;
    float iq_Amps;
    float n_rpm;
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



uz_parameterID_rc_t* uz_parameterID_rc_init(struct uz_parameterID_rc_config_t initial_config);
struct uz_parameterID_rc_config_t uz_parameterID_rc_get_config(uz_parameterID_rc_t* self);
struct uz_parameterID_rc_ref_val_t uz_parameterID_rc_generate_idq_ref(uz_parameterID_rc_t* self);
void uz_parameterID_rc_set_next_operating_point_idq(uz_parameterID_rc_t* self);
void uz_parameterID_rc_set_next_operating_point_n(uz_parameterID_rc_t* self);
struct uz_parameterid_rc_counter_t uz_parameterID_rc_get_counter(uz_parameterID_rc_t* self);
#endif // UZ_PARAMETERID_RC_H
