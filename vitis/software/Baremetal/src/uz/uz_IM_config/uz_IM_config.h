#ifndef UZ_IM_CONFIG_H
#define UZ_IM_CONFIG_H

#pragma once

#include "uz_IM_motor_config.h"

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
 * @brief Return the compile-time selected induction-machine preset.
 *
 * Selection and preset values are defined in uz_IM_motor_config.h.
 */
uz_IM_t uz_IM_config_get_selected_motor(void);

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

/**
 * @brief Calculates the steady-state d-axis current required for a desired rotor flux.
 *
 * For the rotor-flux model used here, the steady-state relation is psi_r = Lm * i_d.
 *
 * @param config    uz_IM_t configuration struct
 * @param psi_r_Vs  Desired rotor flux linkage in Volt-seconds. Must be greater than 0.0f
 * @return float    Required d-axis current in Ampere
 */
float uz_IM_get_id_ref_for_psi_r(uz_IM_t config, float psi_r_Vs);

/**
 * @brief Discretized state-space matrices for an induction machine observer.
 *
 * Precomputed from uz_IM_t + sample period Ts using Forward Euler discretization.
 * All matrices use the state vector x = [i_alpha, i_beta, Psi_r_alpha, Psi_r_beta].
 * Ts is fixed at runtime (set at ISR init) but may differ between runs.
 */
typedef struct {
    /** Speed-independent skeleton of A = I + F*Ts.
     *  Four speed-dependent elements (A[0][3], A[1][2], A[2][3], A[3][2]) are zero
     *  here and must be filled per ISR step using x_m_D_Ts and Ts. */
    float A_base[4][4];
    /** Input matrix B = Ts/sigmaLs * P_ab (rows 0-1), zeros (rows 2-3).
     *  Absorbs the Clarke abc->alphabeta transform so 3-phase voltages [V] are
     *  passed directly as input u_abc. */
    float B[4][3];
    /** Process noise diagonal Q_diag.
     *  Default values are configured in uz_global_configuration.h. */
    float Q_diag[4];
    /** Measurement noise diagonal R_diag [A^2].
     *  Default values are configured in uz_global_configuration.h. */
    float R_diag[2];
    /** Combined speed-coupling coefficient c*Ts = Lm*Ts/(sigmaLs*Lr).
     *  Used to update A[0][3] and A[1][2] each ISR step. */
    float x_m_D_Ts;
    /** Sample period Ts [s]. Used to update A[2][3] and A[3][2] each ISR step. */
    float Ts;
    /** Slip coefficient Lm*Rr/Lr = Lm/tau_r.
     *  Used to compute slip_estimate = x_m_tau_r_inv * i_q / psi_r_mag. */
    float x_m_tau_r_inv;
    /** Number of pole pairs, copied from uz_IM_t for use in omega_el computation. */
    float polePairs;
} uz_IM_ss_t;

/**
 * @brief Compute discretized state-space matrices from motor parameters and sample period.
 *
 * Compute once after the ISR sample rate is known (e.g. after measurement calibration).
 * The returned struct is small and passed by value.
 *
 * @param config  Motor electrical parameters (validated internally)
 * @param Ts      ISR sample period in seconds (e.g. 100e-6 for 10 kHz). Must be > 0.
 * @return        Fully populated uz_IM_ss_t
 */
uz_IM_ss_t uz_IM_ss_compute(uz_IM_t config, float Ts);

#endif // UZ_IM_CONFIG_H
