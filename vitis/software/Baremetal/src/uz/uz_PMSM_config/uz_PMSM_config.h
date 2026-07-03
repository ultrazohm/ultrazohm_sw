#ifndef UZ_PMSM_CONFIG_H
#define UZ_PMSM_CONFIG_H

#pragma once
#include <stdint.h>
#include "uz_available_machines_auto_generated.h"

/**
 * @brief Configuratin struct for a PMSM. Accessible by the user
 * 
 */
typedef struct uz_PMSM_t{
    uint32_t machine_id; /**< stable dataset id from machine_parameters.csv; reserved for future runtime machine selection, not checked by uz_PMSM_config_assert */
    float R_ph_Ohm;/**< phase resistance in Ohm. Must be greater than 0.0f */
    float Ld_Henry; /**< d-axis inductance in Henry. Must be greater than 0.0f */
    float Lq_Henry;/**< q-axis inductance in Henry. Must be greater than 0.0f */
    float Psi_PM_Vs;/**< permanent magnet flux linkage in Volt-seconds. Must be greater or equal than 0.0f */
    float polePairs; /**< number of polePairs of the machine. Must be greater than 0.0f. Must be no decimal value (i.e. 2.5f is not allowed) */
    float J_kg_m_squared; /**< inertia of the PMSM. Must be greater than 0.0f */
    float I_max_Ampere; /**< max allowed current per phase. Must be greater than 0.0f */
    float I_rated_Ampere; /**< rated current per phase. Must be greater than 0.0f */
    float Torque_rated_Nm; /**< rated torque in Nm. Must be greater than 0.0f */
    float Torque_max_Nm; /**< maximum torque in Nm. Must be greater or equal to rated torque */
    float Torque_min_Nm; /**< minimum torque in Nm. Must be less than or equal to 0.0f */
    float speed_rated_rpm; /**< rated mechanical speed in rpm. Must be greater than 0.0f */
    float speed_max_rpm; /**< maximum mechanical speed in rpm. Must be greater or equal to rated speed */
    float speed_min_rpm; /**< minimum mechanical speed in rpm. Must be less than or equal to 0.0f */
    float V_dc_nominal_V; /**< nominal DC-link voltage in V. Must be greater than 0.0f */
    float I_d_max_A; /**< maximum d-axis current in A */
    float I_d_min_A; /**< minimum d-axis current in A */
    float I_q_max_A; /**< maximum q-axis current in A */
    float I_q_min_A; /**< minimum q-axis current in A */
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
 * @brief Asserts only the physical machine-model parameters (R_ph_Ohm, Ld_Henry, Lq_Henry,
 * Psi_PM_Vs, polePairs, J_kg_m_squared, I_max_Ampere).
 *
 * Use this in modules that only evaluate the machine model (e.g. current control, setpoint
 * generation, software model) and do not need the rating/limit envelope. The envelope fields
 * (I_rated, Torque_*, speed_*, V_dc_nominal_V, I_d/I_q limits) are neither read nor asserted here.
 *
 * @param config uz_PMSM_t config struct
 */
void uz_PMSM_config_assert_model(uz_PMSM_t config);

/**
 * @brief Asserts all input values, i.e. the physical model parameters (see
 * uz_PMSM_config_assert_model) plus the full rating/limit envelope and its relations.
 *
 * @param config uz_PMSM_t config struct
 */
void uz_PMSM_config_assert(uz_PMSM_t config);

/**
 * @brief Asserts all input values
 *
 * @param fitting_config uz_PMSM_t fitting parameter config struct
 */
void uz_PMSM_fitting_parameter_config_assert(uz_PMSM_flux_fitting_parameter_config_t fitting_config);

#endif // UZ_PMSM_CONFIG_H
