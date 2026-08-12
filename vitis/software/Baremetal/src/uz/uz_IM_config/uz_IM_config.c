#include "uz_IM_config.h"
#include "../uz_HAL.h"
#include <math.h>

void uz_IM_config_assert(uz_IM_t config) {
    uz_assert(config.Rs_Ohm > 0.0f);
    uz_assert(config.Rr_Ohm > 0.0f);
    uz_assert(config.Lsigma_s_Henry > 0.0f);
    uz_assert(config.Lsigma_r_Henry > 0.0f);
    uz_assert(config.Lm_Henry > 0.0f);
    uz_assert(config.polePairs > 0.0f);
    uz_assert(fmodf(config.polePairs, 1.0f) == 0.0f);
    uz_assert(config.J_kg_m_squared > 0.0f);
    uz_assert(config.I_max_Ampere > 0.0f);
    uz_assert(config.Psi_rated_Vs > 0.0f);
}

float uz_IM_config_get_Ls(uz_IM_t config) {
    uz_IM_config_assert(config);
    return config.Lsigma_s_Henry + config.Lm_Henry;
}

float uz_IM_config_get_Lr(uz_IM_t config) {
    uz_IM_config_assert(config);
    return config.Lsigma_r_Henry + config.Lm_Henry;
}

float uz_IM_config_get_sigma(uz_IM_t config) {
    float const ls = uz_IM_config_get_Ls(config);
    float const lr = uz_IM_config_get_Lr(config);
    return 1.0f - (config.Lm_Henry * config.Lm_Henry) / (ls * lr);
}

float uz_IM_config_get_rotor_time_constant(uz_IM_t config) {
    return uz_IM_config_get_Lr(config) / config.Rr_Ohm;
}
