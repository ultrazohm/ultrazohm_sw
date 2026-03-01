#ifndef UZ_6PH_SVPWM_OPT_H
#define UZ_6PH_SVPWM_OPT_H
#include "uz_6ph_SVPWM_LUT.h"



/**
 * @brief Generates dutycycles for 2x3 phase machines, zero sequence injection based, optimized
 *
 * @param u_6ph_alphabeta_ref_Volts reference voltage in Volts (e.g. from current controller)
 * @param V_dc_volts DC-Link voltage in volts
 * @return struct uz_DutyCycle_2x3ph_PhaseShiftOptt generated DutyCycles and PhaseShiftOption
 */
struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_4_active_SV_opt_z1z2_alphabeta(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, float kappa, bool scaled);

struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_4_active_SV_opt_z1z2_abc1abc2(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, float kappa, bool scaled);

struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_5_active_SV_opt_z1z2_alphabeta(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts, svpwm_5active_2zero_24sector_SV_sequence_t version, float kappa, C_D1_D2 CD1D2, bool scaled);

struct uz_DutyCycle_2x3ph_PhaseShiftOpt  uz_6ph_SVPWM_24_5_active_SV_opt_z1z2_abc1abc2(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts, svpwm_5active_2zero_24sector_SV_sequence_t version, float kappa, C_D1_D2 CD1D2, bool scaled);

struct uz_DutyCycle_2x3ph_PhaseShiftOpt uz_6ph_SVPWM_24_4_active_SV_opt_d_alphabeta(uz_6ph_alphabeta_t u_6ph_alphabeta_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, float kappa);

struct uz_DutyCycle_2x3ph_PhaseShiftOpt uz_6ph_SVPWM_24_4_active_SV_opt_d_abc1abc2(uz_6ph_abc_t u_6ph_abc1abc2_ref_Volts, float V_DC_Volts, svpwm_4active_2zero_24sector_SV_sequence_t version, float kappa);



#endif // UZ_6PH_SVPWM_OPT_H
