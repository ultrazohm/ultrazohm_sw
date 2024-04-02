#ifndef UZ_FLUX_PREDICTION_H
#define UZ_FLUX_PREDICTION_H

#pragma once
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>

/**
 * @brief Struct definition for uz_flux_prediction
 *
 */
typedef struct uz_flux_prediction_t uz_flux_prediction_t;

/**
 * @brief init function for the flux_prediction
 * @return uz_flux_prediction*, pointer to the flux_prediction
 */
uz_flux_prediction_t* uz_flux_prediction_init(uz_PMSM_t config, float ts_regler, float omega_el);
/**
 * @brief flux_prediction
 * @return flux_prediction
 */
uz_3ph_dq_t uz_flux_prediction_step(uz_flux_prediction_t* self, uz_3ph_dq_t i_actual_Ampere, uz_3ph_dq_t u_k0, uz_3ph_dq_t u_k1, uz_3ph_dq_t flux);

/**
 * @brief approximate flux_prediction
 * @return approximated flux_prediction
 */

#endif // UZ_FLUX_PREDICTION_H
