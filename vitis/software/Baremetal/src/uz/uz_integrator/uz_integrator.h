#ifndef UZ_INTEGRATOR_H
#define UZ_INTEGRATOR_H

#include <stdbool.h>

/**
 * @brief Discrete time integration using Euler forward method
 *
 * @param current_value Value of x(k) at current time step k
 * @param old_value Value of x(k-1) at last time step k-1
 * @param sample_time Sample time of the discrete integration
 * @param clamping_active If true, clamping is active and integration is stopped
 * @return float
 */
float uz_integrator_eulerforward(float current_value, float old_value, float sample_time, bool clamping_active);



#endif // UZ_INTEGRATOR_H
