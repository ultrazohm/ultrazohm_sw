#ifndef UZ_CURRENTCONTROL_KP_IQ_ADJUSTMENT_H
#define UZ_CURRENTCONTROL_KP_IQ_ADJUSTMENT_H

#pragma once
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>

/**
 * @brief Struct definition for uz_CurrentControl_Kp_iq_adjustment
 *
 */
typedef struct uz_CurrentControl_Kp_iq_adjustment_t uz_CurrentControl_Kp_iq_adjustment_t;

/**
 * @brief init function for the Kp_iq_adjustment
 * @return uz_CurrentControl_Kp_iq_adjustment_t*, pointer to the Kp_iq_adjustment
 */
uz_CurrentControl_Kp_iq_adjustment_t* uz_CurrentControl_Kp_iq_adjustment_init(float dead_time_reciprocal);

float uz_CurrentControl_Kp_iq_adjustment_step(uz_CurrentControl_Kp_iq_adjustment_t* self, uz_3ph_dq_t i_reference_Ampere,uz_3ph_dq_t i_actual_Ampere,uz_3ph_dq_t flux_reference,uz_3ph_dq_t flux_actual);

#endif // UZ_CURRENTCONTROL_KP_IQ_ADJUSTMENT_H
