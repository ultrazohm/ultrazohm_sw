#ifndef UZ_SVPWM_HELP_FUNCTIONS_H
#define UZ_SVPWM_HELP_FUNCTIONS_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"


struct uz_DutyCycle_2x3ph_PhaseShiftOpt{
    struct uz_DutyCycle_2x3ph_t Dutycles;
    int phaseshiftoption;
};

struct uz_DutyCycle_2x3ph_PhaseShiftOpt_more_info{
    struct uz_DutyCycle_2x3ph_PhaseShiftOpt Dutycles_PhaseShift;

};


struct uz_DutyCycle_2x3ph_t uz_add_zerosequence_and_saturate_6ph(uz_6ph_abc_t u_abc1abc2_ref, float u_n1, float u_n2, float V_dc_volts);

/*
 * @brief adds zeros sequence to reference voltages, saturates dutycycles
 *
 * @param u_abc_ref abc values input
 * @param u_n zero sequence in volts
 * @param v_dc_volts dc link voltage
 */
struct uz_DutyCycle_t uz_add_zerosequence_and_saturate_3ph(uz_3ph_abc_t u_abc_ref, float u_n, float V_dc_volts);


int getSector24(float theta);

int getSector12(float theta);

float uz_bring_angle_between_0_2_pi(float theta_rad);

float uz_get_angle_3ph_alphabeta_reference(uz_3ph_alphabeta_t u_alphabeta_ref);


#endif // UZ_SVPWM_HELP_FUNCTIONS_H
