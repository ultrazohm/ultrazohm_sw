#ifndef UZ_PMSM_CONFIG_H
#define UZ_PMSM_CONFIG_H

#pragma once
#include "../uz_HAL.h"

struct uz_PMSM_t{
    float R_ph_Ohm;
    float Ld_Henry;
    float Lq_Henry;
    float Psi_PM_Vs;
    float polePairs;
    float J_kg_m_squared;
    float I_max_Ampere;
};

/**
 * @brief Asserts all input values
 *
 * @param config uz_PMSM_t config struct
 */
void uz_PMSM_config_assert(struct uz_PMSM_t config);

#endif // UZ_PMSM_CONFIG_H
