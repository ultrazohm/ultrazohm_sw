#ifndef UZ_APPROXIMATE_FLUX_Q_H
#define UZ_APPROXIMATE_FLUX_Q_H

#pragma once
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>

/**
 * @brief Struct definition for uz_appropriate_flux_d
 *
 */
typedef struct uz_approximate_flux_q_t uz_approximate_flux_q_t;

/**
 * @brief init function for the flux approximation
 * @return uz_approximate_flux_q*, pointer to the flux approximation q
 */
uz_approximate_flux_q_t* uz_approximate_flux_q_init( uz_PMSM_flux_fitting_parameter_config_t fitting_config);

/**
 * @brief approximate fluxq 
 * @return approximated fluxq
 */

float uz_approximate_flux_q_step(uz_approximate_flux_q_t* self, uz_3ph_dq_t i_Ampere);

/**
 * @brief approximate fluxq_setpoint
 * @return approximated fluxq_setpoint.
 */
float uz_approximate_flux_q_set_step(uz_approximate_flux_q_t* self, uz_3ph_dq_t i_reference_Ampere,uz_3ph_dq_t i_actual_Ampere);

#endif // UZ_APPROXIMATE_FLUX_Q_H
