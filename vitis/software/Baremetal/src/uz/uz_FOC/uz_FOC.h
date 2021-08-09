#ifndef UZ_FOC_H
#define UZ_FOC_H

#pragma once
#include "../uz_HAL.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "uz_linear_decoupling.h"
#include "uz_space_vector_limitation.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Configuration struct for FOC. Accessible by the user
 */
struct uz_FOC_config {
	struct uz_dq_t ref_current_Ampere; /**< Reference current for the dq-Axis in Ampere */
	float polePairs; /**< Number of polePairs for the machine. Must be greater than 0.0f. Must be no decimal value (i.e. 2.5f is not allowed) */
	struct uz_lin_decoupling_config config_lin_decoupling; /** Configuration struct for linear decoupling */
	uz_PI_Controller_config config_id; /** Configuration struct for id-Controller */
	uz_PI_Controller_config config_iq; /** Configuration struct for iq-Controller */
};

/**
 * @brief Object definition for FOC
 *
 */
typedef struct uz_FOC uz_FOC;

/**
 * @brief Initialization of the uz_FOC object
 *
 * @param config_FOC configuration struct for FOC
 * @return uz_FOC* Pointer to uz_FOC instance
 */
uz_FOC* uz_FOC_init(struct uz_FOC_config config_FOC);

/**
 * @brief calculates last sample for dq-reference voltages
 *
 * @param self uz_FOC instance
 * @param i_dq_meas_Ampere uz_dq_t struct for measured dq-currents
 * @param U_zk_Volts measured U_zk voltage. Must be greater than 0.0f
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @return struct uz_dq_t Output dq-reference voltage struct
 */
struct uz_dq_t uz_FOC_sample(uz_FOC* self, struct uz_dq_t i_dq_meas_Ampere, float U_zk_Volts, float omega_el_rad_per_sec);

/**
 * @brief Resets the FOC and the integrators of the PI-Controllers
 *
 * @param self uz_FOC instance
 */
void uz_FOC_reset(uz_FOC* self);

/**
 * @brief Function to change the Kp-value of the n-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Kp_n new Kp_n value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Kp_n(uz_FOC* self, float Kp_n);

/**
 * @brief Function to change the Ki-value of the n-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Ki_n new Ki_n value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Ki_n(uz_FOC* self, float Ki_n);

/**
 * @brief Function to change the Kp-value of the id-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Kp_n new Kp_id value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Kp_id(uz_FOC* self, float Kp_id);

/**
 * @brief Function to change the Ki-value of the id-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Kp_n new Ki_id value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Ki_id(uz_FOC* self, float Ki_id);

/**
 * @brief Function to change the Kp-value of the iq-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Kp_n new Kp_iq value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Kp_iq(uz_FOC* self, float Kp_iq);

/**
 * @brief Function to change the Ki-value of the iq-PI-Controller during runtime
 *
 * @param self uz_FOC instance
 * @param Kp_n new Ki_iq value. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Ki_iq(uz_FOC* self, float Ki_iq);

/**
 * @brief Function to change the d-reference current during runtime
 *
 * @param self uz_FOC instance
 * @param id_ref new id_ref value in Ampere
 */
void uz_FOC_set_id_ref(uz_FOC* self, float id_ref);

/**
 * @brief Function to change the q-reference current during runtime
 *
 * @param self uz_FOC instance
 * @param id_ref new iq_ref value in Ampere
 */
void uz_FOC_set_iq_ref(uz_FOC* self, float iq_ref);

/**
 * @brief Function to change the polePairs during runtime
 *
 * @param polePairs new value for polePairs. Must be greater than 0.0f. Must be no decimal value (i.e. 2.5f is not allowed)
 */
void uz_FOC_set_polePairs(uz_FOC* self, float polePairs);

/**
 * @brief Function to change Ld_Henry during runtime
 *
 * @param self uz_FOC instance
 * @param Ld_Henry New Value for d-axis inductance. Must be greater than 0.0f
 */
void uz_FOC_set_Ld(uz_FOC* self, float Ld_Henry);

/**
 * @brief Function to change Lq_Henry during runtime
 *
 * @param self uz_FOC instance
 * @param Lq_Henry New Value for q-axis inductance. Must be greater than 0.0f
 */
void uz_FOC_set_Lq(uz_FOC* self, float Lq_Henry);

/**
 * @brief Function to change Psi_PM_Vs during runtime
 *
 * @param self uz_FOC instance
 * @param Psi_PM_Vs New Value for permanent magnet flux linkage. Must be greater or equal than 0.0f
 */
void uz_FOC_set_Psi_PM(uz_FOC* self, float Psi_PM_Vs);
#endif // UZ_FOC_H
