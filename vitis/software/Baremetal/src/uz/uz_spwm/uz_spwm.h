#ifndef UZ_SPWM_H
#define UZ_SPWM_H
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz_Transformation/uz_Transformation.h"


/**
 * @brief SPWM for 3ph system with dq inputs
 * 
 * @param input dq values
 * @param V_dc_volts DC voltage
 * @param theta_el_rad electrical rotor angle for park transformation
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_spwm_dq(uz_3ph_dq_t input, float V_dc_volts, float theta_el_rad);

/**
 * @brief SPWM for 3ph system with abc inputs
 * 
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_spwm_abc(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief SPWM for 6ph system with dq inputs
 * 
 * @param input dq values
 * @param V_dc_volts DC voltage
 * @param theta_el_rad electrical rotor angle for park transformation
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_spwm_abc_dq(uz_6ph_dq_t input, float V_dc_volts, float theta_el_rad);

/**
 * @brief SPWM for 3ph system with abc inputs
 * 
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_spwm_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

#endif // UZ_SPWM_H
