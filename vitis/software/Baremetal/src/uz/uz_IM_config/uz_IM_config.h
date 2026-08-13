#ifndef UZ_IM_CONFIG_H
#define UZ_IM_CONFIG_H

/**
 * @brief Configuration of an induction machine referred to the stator side.
 */
typedef struct uz_IM_t {
    float Rs_Ohm;             /**< Stator phase resistance in Ohm. */
    float Rr_Ohm;             /**< Rotor resistance referred to the stator in Ohm. */
    float Lsigma_s_Henry;     /**< Stator leakage inductance in Henry. */
    float Lsigma_r_Henry;     /**< Rotor leakage inductance referred to the stator in Henry. */
    float Lm_Henry;           /**< Magnetizing inductance in Henry. */
    float polePairs;          /**< Integer number of pole pairs. */
    float J_kg_m_squared;     /**< Rotor inertia in kg m^2. */
    float I_max_Ampere;       /**< Maximum phase-current magnitude in Ampere. */
    float Psi_rated_Vs;       /**< Rated rotor-flux linkage in Volt-seconds. */
} uz_IM_t;

/** @brief Assert that all induction-machine parameters are valid. */
void uz_IM_config_assert(uz_IM_t config);

/** @brief Return total stator inductance Lsigma_s + Lm. */
float uz_IM_config_get_Ls(uz_IM_t config);

/** @brief Return total rotor inductance Lsigma_r + Lm. */
float uz_IM_config_get_Lr(uz_IM_t config);

/** @brief Return the total leakage factor. */
float uz_IM_config_get_sigma(uz_IM_t config);

/** @brief Return the rotor time constant Lr/Rr in seconds. */
float uz_IM_config_get_rotor_time_constant(uz_IM_t config);

#endif
