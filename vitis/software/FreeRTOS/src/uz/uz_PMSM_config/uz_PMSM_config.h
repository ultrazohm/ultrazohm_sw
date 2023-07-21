#ifndef UZ_PMSM_CONFIG_H
#define UZ_PMSM_CONFIG_H

#pragma once

/**
 * @brief Configuratin struct for a PMSM. Accessible by the user
 * 
 */
typedef struct uz_PMSM_t{
    float R_ph_Ohm;/**< phase resitance inductance in Ohm. Must be greater than 0.0f */
    float Ld_Henry; /**< d-axis inductance in Henry. Must be greater than 0.0f */
    float Lq_Henry;/**< q-axis inductance in Henry. Must be greater than 0.0f */
    float Psi_PM_Vs;/**< permanent magnet flux linkage in Volt-seconds. Must be greater or equal than 0.0f */
    float polePairs; /**< number of polePairs of the machine. Must be greater than 0.0f. Must be no decimal value (i.e. 2.5f is not allowed) */
    float J_kg_m_squared; /**< inertia of the PMSM. Must be greater than 0.0f */
    float I_max_Ampere; /**< max allowed current per phase. Must be greater than 0.0f */
}uz_PMSM_t;

/**
 * @brief Asserts all input values
 *
 * @param config uz_PMSM_t config struct
 */
void uz_PMSM_config_assert(uz_PMSM_t config);

#endif // UZ_PMSM_CONFIG_H
