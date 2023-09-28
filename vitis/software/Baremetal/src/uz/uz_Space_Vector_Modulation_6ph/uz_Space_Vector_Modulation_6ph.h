#ifndef UZ_SPACE_VECTOR_MODULATION_6PH_H
#define UZ_SPACE_VECTOR_MODULATION_6PH_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_space_vector_modulation/uz_space_vector_modulation.h"

struct uz_svm_asym_6ph_CSVPWM24_out{
    struct uz_DutyCycle_2x3ph_t Duty_Cycle;
    float shift_system1;
    float shift_system2;
};


struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24(uz_6ph_alphabeta_t setpoints, const float T_sw);

#endif // UZ_SPACE_VECTOR_MODULATION_6PH_H
