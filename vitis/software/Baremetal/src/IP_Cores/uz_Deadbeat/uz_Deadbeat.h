#ifndef UZ_DEADBEAT_H
#define UZ_DEADBEAT_H

#include <stdint.h>

typedef struct uz_Deadbeat_t uz_Deadbeat_t;

struct uz_Deadbeat_config_t {
    uint32_t base_address;
    uint32_t ip_clk_frequency_Hz;
};

struct uz_Deadbeat_inputs_t {
    float id_ref;
    float iq_ref;
    float id;
    float iq;
    float theta;
    float theta_0;
    float w_e;
    float ua_0_input;
    float ub_0_input;
    float uc_0_input;
};

struct uz_Deadbeat_outputs_t {
    float ua_0;
    float ub_o;
    float uc_0;
};

uz_Deadbeat_t* uz_Deadbeat_init(struct uz_Deadbeat_config_t config);

void uz_Deadbeat_write_inputs(
    uz_Deadbeat_t* self,
    const struct uz_Deadbeat_inputs_t* inputs
);

struct uz_Deadbeat_outputs_t uz_Deadbeat_read_outputs(
    uz_Deadbeat_t* self
);

#endif
