#ifndef UZ_IM_CONFIG_H
#define UZ_IM_CONFIG_H

#pragma once

/**
 * @brief Configuration struct for an induction machine (IM). Accessible by the user.
 *
 * Contains electrical and mechanical parameters for field-oriented control of induction machines.
 * All inductances are referred to the stator side.
 */
typedef struct uz_IM_t {
    // Electrical parameters
    float Rs_Ohm;              /**< Stator resistance per phase in Ohm. Must be greater than 0.0f */
    float Rr_Ohm;              /**< Rotor resistance referred to stator in Ohm. Must be greater than 0.0f */
    float Lsigma_s_Henry;      /**< Stator leakage inductance in Henry. Must be greater than 0.0f */
    float Lsigma_r_Henry;      /**< Rotor leakage inductance referred to stator in Henry. Must be greater than 0.0f */
    float Lm_Henry;            /**< Magnetizing inductance in Henry. Must be greater than 0.0f */

    // Mechanical parameters
    float polePairs;           /**< Number of pole pairs. Must be greater than 0.0f and integer value */
    float J_kg_m_squared;      /**< Rotor inertia in kg·m². Must be greater than 0.0f */

    // Limits
    float I_max_Ampere;        /**< Maximum allowed current per phase in Ampere. Must be greater than 0.0f */
    float Psi_rated_Vs;        /**< Rated rotor flux linkage in Volt-seconds. Must be greater than 0.0f */
} uz_IM_t;

/**
 * @brief Validates all input values of the IM configuration struct
 *
 * @param config uz_IM_t configuration struct to validate
 */
void uz_IM_config_assert(uz_IM_t config);

/**
 * @brief Calculates total stator inductance Ls = Lsigma_s + Lm
 *
 * @param config uz_IM_t configuration struct
 * @return float Total stator inductance in Henry
 */
float uz_IM_get_Ls(uz_IM_t config);

/**
 * @brief Calculates total rotor inductance Lr = Lsigma_r + Lm
 *
 * @param config uz_IM_t configuration struct
 * @return float Total rotor inductance in Henry
 */
float uz_IM_get_Lr(uz_IM_t config);

/**
 * @brief Calculates total leakage factor sigma = 1 - Lm²/(Ls·Lr)
 *
 * The leakage factor is used in transient inductance calculations for decoupling.
 *
 * @param config uz_IM_t configuration struct
 * @return float Leakage factor (dimensionless, typically 0.05 to 0.15)
 */
float uz_IM_get_sigma(uz_IM_t config);

/**
 * @brief Calculates rotor time constant tau_r = Lr/Rr
 *
 * The rotor time constant determines the speed of rotor flux dynamics.
 * Typical values: 0.1 to 1.0 seconds depending on machine size.
 *
 * @param config uz_IM_t configuration struct
 * @return float Rotor time constant in seconds
 */
float uz_IM_get_tau_r(uz_IM_t config);

#endif // UZ_IM_CONFIG_H
