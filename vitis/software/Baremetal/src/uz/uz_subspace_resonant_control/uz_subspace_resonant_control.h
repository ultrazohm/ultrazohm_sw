#ifndef UZ_SUBSPACE_RESONANT_CONTROL_H
#define UZ_SUBSPACE_RESONANT_CONTROL_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_ResonantController/uz_resonant_controller.h"
#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>


/**
 * @brief Configuration struct for CurrentControl. Accessible by the user
 */
struct uz_subspace_resonant_control_config {
    float sampling_time;         /**< SamplingTime of the PI-Controller in seconds. Must be greater than 0.0f */
    float gain_1;                /**< Gain of the resonant Controller*/
    float gain_2;                /**< Gain of the resonant Controller*/
    float harmonic_order;        /**< Order of harmonic to be controlled*/
    float lower_limit;           /**< Lower limit for the output limitation */
    float upper_limit;           /**< Upper limit for the output limitation. Must be greater than lower limit */
    float antiwindup_gain;       /**< Gain of anti-windup feedback*/
};

/**
 * @brief Object definition for CurrentControl
 *
 */
typedef struct uz_subspace_resonant_control uz_subspace_resonant_control;

/**
 * @brief Initialization of the uz_CurrentControl object
 *
 * @param config configuration struct for CurrentControl
 * @return uz_CurrentControl_t* Pointer to uz_CurrentControl_t instance
 */
uz_subspace_resonant_control* uz_subspace_resonant_control_init(struct uz_subspace_resonant_control_config config);

/**
 * @brief step the controllers with dq values
 *
 * @param self pointer to instance
 * @param i_reference_Ampere reference dq currents
 * @param i_actual_Ampere actual dq currents of subspace
 * @param omega_el_fundamental fundamental omega_el in rad_s (NOT order of harmonic's omega)
 * @return dq reference voltages
 */
uz_3ph_dq_t uz_subspace_resonant_control_step_dq(uz_subspace_resonant_control* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float omega_el_fundamental);

/**
 * @brief step the controllers with alpha beta values
 *
 * @param self pointer to instance
 * @param i_reference_Ampere reference alpha beta  currents
 * @param i_actual_Ampere actual alpha beta  currents of subspace
 * @param omega_el_fundamental fundamental omega_el in rad_s (NOT order of harmonic's omega)
 * @return alpha beta reference voltages
 */
uz_3ph_alphabeta_t uz_subspace_resonant_control_step_alphabeta(uz_subspace_resonant_control* self, uz_3ph_alphabeta_t i_reference_Ampere, uz_3ph_alphabeta_t i_actual_Ampere, float omega_el_fundamental);

/**
 * @brief resets both resonant instances
 *
 * @param self pointer to instance
 */
void uz_subspace_resonant_control_reset(uz_subspace_resonant_control* self);

#endif // UZ_SUBSPACE_RESONANT_CONTROL_H
