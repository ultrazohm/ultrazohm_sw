#include "uz_im_decoupling.h"
#include "../uz_HAL.h"
#include <math.h>

uz_3ph_dq_t uz_CurrentControl_IM_decoupling(uz_IM_t config,
                                            uz_3ph_dq_t i_actual_Ampere,
                                            float omega_s_rad_per_sec,
                                            float psi_r_Vs)
{
    uz_IM_config_assert(config);
    uz_assert(isfinite(i_actual_Ampere.d));
    uz_assert(isfinite(i_actual_Ampere.q));
    uz_assert(isfinite(omega_s_rad_per_sec));
    uz_assert(isfinite(psi_r_Vs));
    uz_assert(psi_r_Vs >= 0.0f);

    float const ls = uz_IM_get_Ls(config);
    float const lr = uz_IM_get_Lr(config);
    float const sigma_ls = uz_IM_get_sigma(config) * ls;

    uz_3ph_dq_t const output = {
        .d = -omega_s_rad_per_sec * sigma_ls * i_actual_Ampere.q,
        .q = omega_s_rad_per_sec * sigma_ls * i_actual_Ampere.d
             + omega_s_rad_per_sec * (config.Lm_Henry / lr) * psi_r_Vs,
        .zero = 0.0f,
    };
    return output;
}
