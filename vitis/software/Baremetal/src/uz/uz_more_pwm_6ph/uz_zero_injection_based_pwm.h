#ifndef UZ_ZERO_INJECTION_BASED_PWM_H
#define UZ_ZERO_INJECTION_BASED_PWM_H
#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_Space_Vector_Modulation.h"


struct uz_DutyCycle_2x3ph_t uz_6ph_calculated_dutycycle_and_phaseshift(struct uz_DutyCycle_2x3ph_t input, int phaseshiftoption, float *shift_system_1, float *shift_system_2);



/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: CSVPWM_24_2L_1ML_1M_v2_INJ, CSVPWM_24_3L_1M_v1_INJ and the MIX-Variations of both depending on carrier phase shift
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);


/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: CSVPWM_24_2L_1ML_1M_v1_INJ, CSVPWM_24_3L_1M_v2_INJ and the MIX-Variations of both depending on carrier phase shift
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);


/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: CSVPWM_24_3L_2M_INJ, CSVPWM_24_2L_1ML_2M_INJ, CSVPWM_24_3L_2M_MIX_2L_1ML_2M_v1_INJ and CSVPWM_24_3L_2M_MIX_2L_1ML_2M_v2_INJ depending on carrier phase shift
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_5_active_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);




/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: CSVPWM_24_2L_1ML_1M_v2_INJ and CSVPWM_24_3L_1M_v1_INJ depending on carrier phase shift
 *
 * @param u_6ph_abc1abc2_ref_Volts abc1abc2 reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);


/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: CSVPWM_24_2L_1ML_1M_v1_INJ and CSVPWM_24_3L_1M_v2_INJ depending on carrier phase shift
 *
 * @param u_6ph_abc1abc2_ref_Volts abc1abc2 reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_4_active_SV_V2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);


/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: CSVPWM_24_3L_2M_INJ, CSVPWM_24_2L_1ML_2M_INJ, CSVPWM_24_3L_2M_MIX_2L_1ML_2M_v1_INJ and CSVPWM_24_3L_2M_MIX_2L_1ML_2M_v2_INJ depending on carrier phase shift
 *
 * @param u_6ph_abc1abc2_ref_Volts abc1abc2 reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_CSVPWM_24_5_active_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);



/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v1_D1
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v1_D2
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v2_D1
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v2_D2
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_2M_D1
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_2M_D2
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_2M_D1
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_2M_D2
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v1_D1
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v1_D2
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v2_D1
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D1_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v2_D2
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D2_alphabeta_INJ(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v1_D1
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v1_D2
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v1_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v2_D1
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_1M_v2_D2
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_1M_v2_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_2M_D1
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_2M_D2
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_2M_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_2M_D1
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_2L_1ML_2M_D2
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_2L_1ML_2M_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v1_D1_abc
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v1_D2
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v1_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v2_D1
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D1_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);

/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based equivalent to Space-Vector Modulations: DSVPWM_24_3L_1M_v2_D2
 *
 * @param u_6ph_abc1abc2_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_t generated DutyCycles
 */
struct uz_DutyCycle_2x3ph_t  uz_6ph_DSVPWM_24_3L_1M_v2_D2_abc_INJ(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts);






/*
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
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v1_D1_INJ",
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v1_D2_INJ",
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v2_D1_INJ",
"DSVPWM_24_3L_2M_MIX_2L_1ML_2M_v2_D2_INJ"
*/

#endif // UZ_ZERO_INJECTION_BASED_PWM_H
