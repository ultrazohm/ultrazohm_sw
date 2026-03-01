#ifndef UZ_ZERO_INJECTION__DUAL_PWM_3PH_H
#define UZ_ZERO_INJECTION__DUAL_PWM_3PH_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_Space_Vector_Modulation.h"
#include "../uz_Transformation/uz_Transformation.h"


typedef enum {

	// Dual 3ph
	Dual_PWM_THI_1_4_alphabeta_6ph,
	Dual_PWM_THI_1_6_alphabeta_6ph,
	Dual_SVM_alphabeta_6ph,
	Dual_GDPWM_alphabeta_6ph,
	Dual_GDPWM_alphabeta_6ph_V2,
	Dual_DPWM0_alphabeta_6ph,
	Dual_DPWM1_alphabeta_6ph,
	Dual_DPWM1PHI_alphabeta_6ph,
	Dual_DPWM2_alphabeta_6ph,
	Dual_DPWM3_alphabeta_6ph,
	Dual_DPWM3PHI_alphabeta_6ph,
	Dual_DPWM_MAX_alphabeta_6ph,
	Dual_DPWM_MIN_alphabeta_6ph,

} Dual_3ph_PWM_Verfahren;


/**
 * @brief PWM for 2x3 phase Systems with zero sequence injection of 3. Harmonic with 1/4 amplitude with abc inputs
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_4_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief PWM for 3 phase Systems with zero sequence injection of 2x3. Harmonic with 1/6 amplitude with abc inputs
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_6_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief Space Vector Modulation (SVM) for 2x3 phase Systems with zero sequence injection with abc inputs
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_SVM_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief GDPWM for 2x3ph system with abc inputs, General DPWM technique with angle phi defining the specific realization
 *
 * @param input abc values
 * @param phi_rad angle for DPWM
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_GDPWM_abc_6ph(uz_6ph_abc_t input, float phi_rad, float V_dc_volts);

/**
 * @brief GDPWM for 2x3ph system with abc inputs, General DPWM technique with angle phi defining the specific realization
 *
 * @param input abc values
 * @param phi_rad angle for DPWM
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_GDPWM_abc_6ph_V2(uz_6ph_abc_t input, float phi_rad, float V_dc_volts);

/**
 * @brief DPWM0 for 2x3ph system with abc inputs, equivalent to GDPWM with phi = pi/6
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM0_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM1 for 2x3ph system with abc inputs, equivalent to GDWPM with phi = pi/3
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM1 for 2x3ph system with abc inputs, equivalent to GDWPM with phi = pi/3
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1PHI_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM2 for 2x3ph system with abc inputs, equivalent to GDPWM with phi = -pi/6
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM2_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM3 for 2x3ph system with abc inputs, equivalent to GDPWM with phi = 0
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);


/**
 * @brief DPWM3 for 2x3ph system with abc inputs, equivalent to GDPWM with phi = 0
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3PHI_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM Max for 2x3ph system with abc inputs, the injected zero sequence component is composed of the maximum of the 3 reference values
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MAX_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);

/**
 * @brief DPWM Min for 2x3ph system with abc inputs, the injected zero sequence component is composed of the minimum of the 3 reference values
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MIN_abc_6ph(uz_6ph_abc_t input, float V_dc_volts);






/**
 * @brief PWM for asymmetrix 2x3 phase Systems with zero sequence injection of 3. Harmonic with 1/4 amplitude with alpha-beta-x-y inputs
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_4_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief PWM for asymmetrix 2x3 phase Systems with zero sequence injection of 3. Harmonic with 1/6 amplitude with alpha-beta-x-y inputs
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_PWM_THI_1_6_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief Space Vector Modulation (SVM) for asymmetrix 2x3 phase Systems with zero sequence injection with alpha-beta-x-y inputs
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_SVM_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief GDPWM for asym 2x3ph system with alpha-beta-x-y inputs, General DPWM technique with angle phi defining the specific realization
 *
 * @param input alpha-beta-x-y values
 * @param phi_rad angle for DPWM
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_GDPWM_alphabeta_6ph(uz_6ph_alphabeta_t input, float phi_rad, float V_dc_volts);

/**
 * @brief GDPWM for asym 2x3ph system with alpha-beta-x-y inputs, General DPWM technique with angle phi defining the specific realization
 *
 * @param input alpha-beta-x-y values
 * @param phi_rad angle for DPWM
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_GDPWM_alphabeta_6ph_V2(uz_6ph_alphabeta_t input, float phi_rad, float V_dc_volts);


/**
 * @brief DPWM0 for asym 2x3ph system with alpha-beta-x-y inputs, equivalent to GDPWM with phi = pi/6
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM0_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief DPWM1 for asym 2x3ph system with alpha-beta-x-y inputs, equivalent to GDWPM with phi = pi/3
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief DPWM1 for asym 2x3ph system with alpha-beta-x-y inputs, equivalent to GDWPM with phi = pi/3
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM1PHI_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief DPWM2 for asym 2x3ph system with alpha-beta-x-y inputs, equivalent to GDPWM with phi = -pi/6
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM2_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief DPWM3 for 2x3ph system with abc inputs, equivalent to GDPWM with phi = 0
 *
 * @param input abc values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);


/**
 * @brief DPWM3 for asym 2x3ph system with alpha-beta-x-y inputs, equivalent to GDPWM with phi = 0
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM3PHI_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief DPWM Max for asym 2x3ph system with alpha-beta-x-y inputs, the injected zero sequence component is composed of the maximum of the 3 reference values
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MAX_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);

/**
 * @brief DPWM Min for asym 2x3ph system with alpha-beta-x-y inputs, the injected zero sequence component is composed of the minimum of the 3 reference values
 *
 * @param input alpha-beta-x-y values
 * @param V_dc_volts DC voltage
 * @return duty cycle for PWM module
 */
struct uz_DutyCycle_2x3ph_t uz_Dual_DPWM_MIN_alphabeta_6ph(uz_6ph_alphabeta_t input, float V_dc_volts);


#endif //UZ_ZERO_INJECTION__DUAL_PWM_3PH_H
