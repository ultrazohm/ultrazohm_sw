#ifndef UZ_SPACE_VECTOR_MODULATION_6PH_H
#define UZ_SPACE_VECTOR_MODULATION_6PH_H

#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

#define SVM_6PH_MAXIMUM_XY_RELATIVE 0.1f
#define SVM_6PH_MAXIMUM_MODULATION_INDEX 0.62f


struct uz_svm_asym_6ph_CSVPWM24_out{
    struct uz_DutyCycle_2x3ph_t Duty_Cycle;
    float shift_system1;
    float shift_system2;
    bool limited_alphabeta;
    bool limited_xy;
};


struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta(uz_6ph_alphabeta_t setpoints, float V_dc);

struct uz_svm_asym_6ph_CSVPWM24_out uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_dq(uz_6ph_dq_t setpoints, float theta_el, float V_dc);


#endif // UZ_SPACE_VECTOR_MODULATION_6PH_H
