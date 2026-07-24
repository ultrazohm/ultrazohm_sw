.. _uz_integrator:

===================
Discrete integrator
===================

This module implements discrete time integrations as pure functions.
Thus, there is no internal state and the values of previous time steps have to be supplied.

Euler forward method
====================

Calculation of the discrete integration using the Euler forward method for discretization is simple but only provides sufficient accuracy if the sampling time is low (i.e., high sampling frequency) compared to the system dynamics (i.e., time constant).
Calculation is as follows with the output value :math:`y(k)` at time step :math:`k`, the sampling time :math:`T_s` and the input to the integrator :math:`x(k)`:

.. math::

    y(k)=y(k-1)+T_s \cdot x(k)


Heun's method
=============

Heun's method (the explicit trapezoidal rule, a 2nd-order Runge-Kutta method) is more accurate than Euler forward for the same sampling time, because it averages the derivative at the start and at the (predicted) end of the step instead of holding the start-of-step derivative across the whole step.
For a system :math:`\dot{y}=f(y)` it first forms an Euler predictor and then corrects with the trapezoidal average:

.. math::

    \hat{y}(k) &= y(k-1) + T_s \cdot f\big(y(k-1)\big)

    y(k) &= y(k-1) + \frac{T_s}{2} \Big( f\big(y(k-1)\big) + f\big(\hat{y}(k)\big) \Big)

To keep the function pure (no internal state, like the rest of this module), the caller supplies both derivative evaluations: :math:`f(y(k-1))` at the start of the step and :math:`f(\hat{y}(k))` at the Euler-predicted state.
The caller is responsible for forming the predictor (e.g. with :c:func:`uz_integrator_eulerforward`) and re-evaluating the derivative there.
This is required for coupled systems where the derivative of one state depends on the other states, so a single scalar derivative is not sufficient.


Reference
=========

.. doxygenfunction:: uz_integrator_eulerforward

.. doxygenfunction:: uz_integrator_heun

