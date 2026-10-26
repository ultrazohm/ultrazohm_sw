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

/**
 * @brief Discrete time integration using Heun's method (explicit trapezoidal rule, 2nd order)
 *
 * Pure function: the caller supplies both derivative evaluations. For a system
 * \f$\dot{y}=f(y)\f$ the caller evaluates \f$f\f$ at the start of the step
 * (@p derivative_old), forms the Euler predictor \f$\hat{y}=y(k-1)+T_s\,f(y(k-1))\f$
 * (e.g. via uz_integrator_eulerforward), and evaluates \f$f\f$ again at that predicted
 * state (@p derivative_predicted). The new value is then the trapezoidal average
 * \f$y(k)=y(k-1)+\tfrac{T_s}{2}\big(\dot{y}_{old}+\dot{y}_{pred}\big)\f$.
 *
 * @param derivative_old Derivative \f$\dot{y}\f$ evaluated at the start of the step
 * @param derivative_predicted Derivative \f$\dot{y}\f$ evaluated at the Euler-predicted state
 * @param old_value Value of x(k-1) at last time step k-1
 * @param sample_time Sample time of the discrete integration
 * @param clamping_active If true, clamping is active and integration is stopped
 * @return float
 */
float uz_integrator_heun(float derivative_old, float derivative_predicted, float old_value, float sample_time, bool clamping_active);



#endif // UZ_INTEGRATOR_H
