#ifndef UZ_RLCC_H
#define UZ_RLCC_H

#include <stdint.h>
#include "../uz_matrix/uz_matrix.h"
#include "../uz_nn/uz_nn.h"
#include "../uz_Transformation/uz_Transformation.h"

typedef struct uz_rlcc_t uz_rlcc_t;

struct uz_rlcc_config_t
{
    float ts_in_second;                  // integration time, i.e., ISR time
    float current_scaling_1_by_norminal; // e.g., 1.0f/PMSM_rated_current_hoerner
    float speed_scaling_1_by_norminal_omega_el;   // based on omega_el now, thus 1.0f/(1500/60*2*pi*pole_pairs) for Hoerner -> check it!
    float voltage_scaling;
    uint32_t number_of_observations; // 9
    float voltage_output_scaling;
    float max_modulation_index;
    bool use_ip_core;
    uint32_t base_address;
};

uz_rlcc_t *uz_rlcc_init(struct uz_rlcc_config_t config, struct uz_nn_layer_config neural_network_config[], uint32_t number_of_layer, float *input_data, uint32_t length_of_input_data);
uz_3ph_dq_t uz_rlcc_sample(uz_rlcc_t *self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec);

void uz_rlcc_reset(uz_rlcc_t *self);

#endif // UZ_RLCC_H
