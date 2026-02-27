#ifndef UZ_6PH_SVPWM_OPT_H
#define UZ_6PH_SVPWM_OPT_H

#include "uz_6ph_SVPWM_LUT.h"




/**
 * @brief asym 6ph  SVPWM with 4 active space vectors
 *
 * @param u_6ph_alphabeta_ref_Volts: reference voltage
 * @param V_DC_Volts: DC-Link voltage
 * @param version: selection of different space vector sequences
 * @param CD1D2: selection of continious and discontinious implementation
 */
struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_4_active_SV_alphabeta(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2);

/**
 * @brief asym 6ph  SVPWM with 4 active space vectors
 *
 * @param u_6ph_abc1abc2_ref_Volts: reference voltage
 * @param V_DC_Volts: DC-Link voltage
 * @param version: selection of different space vector sequences
 * @param CD1D2: selection of continious and discontinious implementation
 */
struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_4_active_SV_abc1abc2(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2);

/**
 * @brief asym 6ph  SVPWM with 5 active space vectors with two SV split 50:50
 *
 * @param u_6ph_alphabeta_ref_Volts: reference voltage
 * @param V_DC_Volts: DC-Link voltage
 * @param version: selection of different space vector sequences, only CSVPWM_24_2L_1ML_2M_M23_SV_SEQUENCE, CSVPWM_24_3L_2M_M32_SV_SEQUENCE, CSVPWM_24_2L_3M_L13_M123_SV_SEQUENCE, CSVPWM_24_1L_1ML_3M_L2_M132_SV_SEQUENCE are implementet as the other space vector sequences can be solved for the 50:50 split
 * @param CD1D2: selection of continious and discontinious implementation
 */
struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_5_active_SV_alphabeta(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts, svpwm_5active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2);

/**
 * @brief asym 6ph  SVPWM with 5 active space vectors with two SV split 50:50
 *
 * @param u_6ph_abc1abc2_ref_Volts: reference voltage
 * @param V_DC_Volts: DC-Link voltage
 * @param version: selection of different space vector sequences, only CSVPWM_24_2L_1ML_2M_M23_SV_SEQUENCE, CSVPWM_24_3L_2M_M32_SV_SEQUENCE, CSVPWM_24_2L_3M_L13_M123_SV_SEQUENCE, CSVPWM_24_1L_1ML_3M_L2_M132_SV_SEQUENCE are implementet as the other space vector sequences can be solved for the 50:50 split
 * @param CD1D2: selection of continious and discontinious implementation
 */
struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_5_active_SV_abc1abc2(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts, svpwm_5active_2zero_24sector_SV_sequence_t version, C_D1_D2 CD1D2);




#endif //UZ_6PH_SVPWM_OPT_H
