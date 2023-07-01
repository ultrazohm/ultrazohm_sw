#ifndef UZ_SPACE_VECTOR_MODULATION_H
#define UZ_SPACE_VECTOR_MODULATION_H
#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"

/**
 * @brief Struct for the three DutyCycles for a three-phase-system
 * 
 */
struct uz_DutyCycle_t {
	float DutyCycle_A; /**< DutyCycle for Phase U */
	float DutyCycle_B; /**< DutyCycle for Phase V */
	float DutyCycle_C; /**< DutyCycle for Phase W */
};

/**
 * @brief Generates a DutyCycle from dq-reference voltages via Space Vector Modulation for a carrier based PWM generation
 * 
 * @param v_ref_Volts reference voltages in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @param theta_el_rad electrical angle speed in 1/rad
 * @return struct uz_DutyCycle_t generated DutyCycles
 */
struct uz_DutyCycle_t  uz_Space_Vector_Modulation(uz_3ph_dq_t v_ref_Volts, float V_DC_Volts, float theta_el_rad);

#endif // UZ_SPACE_VECTOR_LIMITATION_H


