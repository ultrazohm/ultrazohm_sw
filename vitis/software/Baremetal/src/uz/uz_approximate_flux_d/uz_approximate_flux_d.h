#ifndef UZ_APPROXIMATE_FLUX_D_H
#define UZ_APPROXIMATE_FLUX_D_H

#pragma once
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>

/**
 * @brief Struct definition for uz_appropriate_flux_d
 *
 */
typedef struct uz_approximate_flux_d_t uz_approximate_flux_d_t;

/**
 * @brief init function for the flux approximation
 * @return uz_approximate_flux_d*, pointer to the flux approximation d
 */
uz_approximate_flux_d_t* uz_approximate_flux_d_init( uz_PMSM_flux_fitting_parameter_config_t fitting_config);

float uz_approximate_flux_d_step(uz_approximate_flux_d_t* self, uz_3ph_dq_t i_Ampere);

float uz_approximate_flux_d_get_output(uz_approximate_flux_d_t* self);

#endif // UZ_APPROXIMATE_FLUX_D_H
