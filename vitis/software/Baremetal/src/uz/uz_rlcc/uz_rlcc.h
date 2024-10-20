#ifndef UZ_RLCC_H
#define UZ_RLCC_H

#include <stdint.h>
#include "../uz_matrix/uz_matrix.h"
#include "../uz_nn/uz_nn.h"

typedef struct uz_rlcc_t uz_rlcc_t;

struct uz_rlcc_config_t
{
    float ts_in_second;                  // integration time, i.e., ISR time
    float current_scaling_1_by_norminal; // e.g., 1.0f/PMSM_rated_current_hoerner
    float speed_scaling_1_by_norminal;   // based on omega_el now, thus 1.0f/(1500/60*2*pi*pole_pairs) for Hoerner -> check it!
    float voltage_scaling;
    uint32_t number_of_observations; // 9
    float voltage_output_scaling;
    float max_modulation_index;
};

uz_rlcc_t *uz_rlcc_init(struct uz_rlcc_config_t config, struct uz_nn_layer_config neural_network_config[], uint32_t number_of_layer, float *input_data, uint32_t length_of_input_data);

#endif // UZ_RLCC_H
