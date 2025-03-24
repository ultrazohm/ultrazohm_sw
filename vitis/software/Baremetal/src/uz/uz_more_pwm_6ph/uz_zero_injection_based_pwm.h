#ifndef UZ_ZERO_INJECTION_BASED_PWM_H
#define UZ_ZERO_INJECTION_BASED_PWM_H
#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_Space_Vector_Modulation.h"


/**
 * @brief Generates a DutyCycle from dq-reference voltages via Space Vector Modulation for a carrier based PWM generation
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_CSVPWM_24_2L_1ML_1M_v2_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);


float uz_getmax_3ph_abc(uz_3ph_abc_t input);
float uz_getmin_3ph_abc(uz_3ph_abc_t input);
float uz_getmid_3ph_abc(uz_3ph_abc_t input);

/*
"CSVPWM_24_2L_1ML_1M_v2_INJ",
"DSVPWM_24_2L_1ML_1M_v2_D1_INJ",
"DSVPWM_24_2L_1ML_1M_v2_D2_INJ",
"CSVPWM_24_3L_1M_v1_INJ",
"DSVPWM_24_3L_1M_v1_D1_INJ",
"DSVPWM_24_3L_1M_v1_D2_INJ",
"CSVPWM_24_3L_2M_INJ",
"DSVPWM_24_3L_2M_D1_INJ",
"DSVPWM_24_3L_2M_D2_INJ",
"CSVPWM_24_2L_1ML_1M_v1_INJ",
"CSVPWM_24_2L_1ML_2M_INJ",
"CSVPWM_24_3L_1M_v2_INJ",
"DSVPWM_24_2L_1ML_1M_v1_D1_INJ",
"DSVPWM_24_2L_1ML_1M_v1_D2_INJ",
"DSVPWM_24_2L_1ML_2M_D1_INJ",
"DSVPWM_24_2L_1ML_2M_D2_INJ",
"DSVPWM_24_3L_1M_v2_D1_INJ",
"DSVPWM_24_3L_1M_v2_D2_INJ",
"CSVPWM_24_2L_1ML_1M_v1_MIX_3L_1M_v1_0_63_INJ",
"CSVPWM_24_2L_1ML_1M_v1_MIX_3L_1M_v1_7_56_INJ",
"CSVPWM_24_2L_1ML_1M_v2_MIX_3L_1M_v2_0_63_INJ",
"CSVPWM_24_2L_1ML_1M_v2_MIX_3L_1M_v2_7_56_INJ",
"DSVPWM_24_2L_1ML_1M_v1_MIX_3L_1M_v1_0_63_D1_INJ",
"DSVPWM_24_2L_1ML_1M_v1_MIX_3L_1M_v1_0_63_D2_INJ",
"DSVPWM_24_2L_1ML_1M_v1_MIX_3L_1M_v1_7_56_D1_INJ",
"DSVPWM_24_2L_1ML_1M_v1_MIX_3L_1M_v1_7_56_D2_INJ",
"DSVPWM_24_2L_1ML_1M_v2_MIX_3L_1M_v2_0_63_D1_INJ",
"DSVPWM_24_2L_1ML_1M_v2_MIX_3L_1M_v2_0_63_D2_INJ",
"DSVPWM_24_2L_1ML_1M_v2_MIX_3L_1M_v2_7_56_D1_INJ",
"DSVPWM_24_2L_1ML_1M_v2_MIX_3L_1M_v2_7_56_D2_INJ",
"CSVPWM_24_3L_2M_MIX_2L_1ML_2M_v1_INJ",
"CSVPWM_24_3L_2M_MIX_2L_1ML_2M_v2_INJ",
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v1_D1_INJ",
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v1_D2_INJ",
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v2_D1_INJ",
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v2_D2_INJ"];
*/

#endif // UZ_ZERO_INJECTION_BASED_PWM_H
