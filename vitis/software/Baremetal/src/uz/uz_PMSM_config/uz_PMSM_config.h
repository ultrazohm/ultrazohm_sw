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

typedef struct uz_PMSM_flux_fitting_parameter_config_t{
    float ad1_parameter; /**Fitting Parameter for Flux approximation*/
    float ad2_parameter; /**Fitting Parameter for Flux approximation*/
    float ad3_parameter; /**Fitting Parameter for Flux approximation*/
    float ad4_parameter; /**Fitting Parameter for Flux approximation*/
    float ad5_parameter; /**Fitting Parameter for Flux approximation*/
    float ad6_parameter; /**Fitting Parameter for Flux approximation*/
    float aq1_parameter; /**Fitting Parameter for Flux approximation*/
    float aq2_parameter; /**Fitting Parameter for Flux approximation*/
    float aq3_parameter; /**Fitting Parameter for Flux approximation*/
    float aq4_parameter; /**Fitting Parameter for Flux approximation*/
    float aq5_parameter; /**Fitting Parameter for Flux approximation*/
    float aq6_parameter; /**Fitting Parameter for Flux approximation*/
    float F1G1_parameter; /**Fitting Parameter for Flux approximation*/
    float F2G2_parameter; /**Fitting Parameter for Flux approximation*/
    }uz_PMSM_flux_fitting_parameter_config_t;

/**
 * @brief Asserts all input values
 *
 * @param config uz_PMSM_t config struct
 */
void uz_PMSM_config_assert(uz_PMSM_t config);

/**
 * @brief Asserts all input values
 *
 * @param config uz_PMSM_t config struct
 */
void uz_fitting_parameter_config_assert(uz_PMSM_flux_fitting_parameter_config_t fitting_config);

#endif // UZ_PMSM_CONFIG_H
