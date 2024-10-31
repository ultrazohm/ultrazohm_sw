#ifndef UZ_PARAMETERID_RC_H
#define UZ_PARAMETERID_RC_H

#include "../uz_global_configuration.h"
#include <stdbool.h> 
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


typedef struct uz_parameterID_rc_t uz_parameterID_rc_t;

struct uz_parameterID_rc_config_t {
    float id_start_Amps;
    float iq_start_Amps;
    float id_stop_Amps;
    float iq_stop_Amps;
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
    bool data_valid;
};


struct uz_parameterID_rc_set_values_t{
    float id_set_Amps;
    float iq_set_Amps;
    float n_set_rpm;
};

struct uz_parameterid_rc_counter_t{
    uint32_t increment_id;
    uint32_t increment_iq;
    uint32_t increment_n;
};

enum rc_state{
    rc_start,
    rc_finished,
    rc_wait,
};

uz_parameterID_rc_t* uz_parameterID_rc_init(struct uz_parameterID_rc_config_t initial_config);
struct uz_parameterID_rc_config_t uz_parameterID_rc_get_config(uz_parameterID_rc_t* self);
struct uz_parameterID_rc_ref_val_t uz_parameterID_rc_generate_idq_ref(uz_parameterID_rc_t* self);


#endif // UZ_PARAMETERID_RC_H
