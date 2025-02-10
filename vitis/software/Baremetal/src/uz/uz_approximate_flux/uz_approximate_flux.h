#ifndef UZ_APPROXIMATE_FLUX_H
#define UZ_APPROXIMATE_FLUX_H

#pragma once
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>

/**
 * @brief Struct definition for uz_appropriate_flux
 *
 */
typedef struct uz_approximate_flux_t uz_approximate_flux_t;

/**
 * @brief init function for the flux approximation
 * @return uz_approximate_flux*, pointer to the flux approximation
 */
uz_approximate_flux_t* uz_approximate_flux_init(uz_PMSM_flux_fitting_parameter_config_t fitting_config);
/**
 * @brief approximate flux-linkages
 * @return uz_dq_t approximated flux-linkages for d- and q-axis
 */
uz_3ph_dq_t uz_approximate_flux_step(uz_approximate_flux_t* self, uz_3ph_dq_t i_actual_Ampere);

/**
 * @brief approximate reference flux-linkages.
 * @return uz_dq_t approximated reference flux-linkages for a specified reference ampere.
 */
uz_3ph_dq_t uz_approximate_flux_reference_step(uz_approximate_flux_t* self,  uz_3ph_dq_t i_reference_Ampere,uz_3ph_dq_t i_actual_Ampere);

#endif // UZ_APPROXIMATE_FLUX_H
