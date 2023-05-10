#ifndef UZ_INTEGRATOR_H
#define UZ_INTEGRATOR_H

#include <stdbool.h>

float uz_integrator_eulerforward(float current_value, float old_value, float time_step, bool clamping_active);



#endif // UZ_INTEGRATOR_H
