#ifndef UZ_SPACE_VECTOR_MODULATION_6PH_H
#define UZ_SPACE_VECTOR_MODULATION_6PH_H

#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

/**
 * @brief output struct for SVM 6ph
 *
 */
struct uz_svm_asym_6ph_CSVPWM24_out{
    struct uz_DutyCycle_2x3ph_t Duty_Cycle;     /**< Duty Cycles for PWM module */
    float shift_system1;                        /**< phase shift for PWM module system 1 (can be 0 or 0.5) */
    float shift_system2;                        /**< phase shift for PWM module system 2 (can be 0 or 0.5)  */
    bool limited_alphabeta;                     /**< limited flag for u_ref_V in alpha beta */
    bool limited_xy;                            /**< limited flag for u_ref_V in xy */
};

/**
 * @brief SVM 6ph with stationary input
 * 
 * @param u_ref_V reference voltages (controller output)
 * @param V_dc DC voltage (must be positive)
 * @return Duty cycles, limited flags and phase shift for PWM modules
 */
struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta(uz_6ph_alphabeta_t u_ref_V, float V_dc);

/**
 * @brief SVM 6ph with rotating input
 * 
 * @param u_ref_V reference voltages (controller output)
 * @param V_dc DC voltage (must be positive)
 * @param theta_el electric rotor angle
 * @return Duty cycles, limited flags and phase shift for PWM modules
 */
struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_dq(uz_6ph_dq_t u_ref_V, float V_dc, float theta_el);


#endif // UZ_SPACE_VECTOR_MODULATION_6PH_H
