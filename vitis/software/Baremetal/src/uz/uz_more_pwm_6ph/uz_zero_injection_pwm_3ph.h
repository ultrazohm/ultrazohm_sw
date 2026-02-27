#ifndef UZ_ZERO_INJECTION_PWM_3PH_H
#define UZ_ZERO_INJECTION_PWM_3PH_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_Space_Vector_Modulation.h"




/*
 * @brief function to get the max of the abc input reference
 *
 * @param input abc values
 * @return max value
 */
float uz_getmax_3ph_abc(uz_3ph_abc_t input);

/*
 * @brief function to get the min of the abc input reference
 *
 * @param input abc values
 * @return min value
 */
float uz_getmin_3ph_abc(uz_3ph_abc_t input);

/*
 * @brief function to get the middle of the abc input reference
 *
 * @param input abc values
 * @return mid value
 */
float uz_getmid_3ph_abc(uz_3ph_abc_t input);

/**
 * @brief PWM for 3 phase Systems with zero sequence injection of 3. Harmonic with 1/4 amplitude with abc inputs
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_PWM_THI_1_4_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief PWM for 3 phase Systems with zero sequence injection of 3. Harmonic with 1/6 amplitude with abc inputs
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_PWM_THI_1_6_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief Space Vector Modulation (SVM) for 3 phase Systems with zero sequence injection with abc inputs
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_SVM_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief GDPWM for 3ph system with abc inputs, General DPWM technique with angle phi defining the specific realization
 *
 * @param input abc values
 * @param phi_rad angle for DPWM
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_GDPWM_abc_3ph(uz_3ph_abc_t input, float phi_rad, float V_dc_volts);

/**
 * @brief GDPWM for 3ph system with abc inputs, General DPWM technique with angle phi defining the specific realization
 *
 * @param input abc values
 * @param phi_rad angle for DPWM
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_GDPWM_abc_3ph_V2(uz_3ph_abc_t input, float phi_rad, float V_dc_volts);

/**
 * @brief DPWM0 for 3ph system with abc inputs, equivalent to GDPWM with phi = pi/6
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM0_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM1 for 3ph system with abc inputs, equivalent to GDWPM with phi = pi/3
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM1_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM1 for 3ph system with abc inputs, equivalent to GDWPM with phi = pi/3
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM1PHI_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM2 for 3ph system with abc inputs, equivalent to GDPWM with phi = -pi/6
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM2_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM3 for 3ph system with abc inputs, equivalent to GDPWM with phi = 0
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM3_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM3 for 3ph system with abc inputs, equivalent to GDPWM with phi = 0
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM3PHI_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM Max for 3ph system with abc inputs, the injected zero sequence component is composed of the maximum of the 3 reference values
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM_MAX_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM Min for 3ph system with abc inputs, the injected zero sequence component is composed of the minimum of the 3 reference values
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_t uz_DPWM_MIN_abc_3ph(uz_3ph_abc_t input, float V_dc_volts);


#endif //UZ_ZERO_INJECTION_PWM_3PH_H
