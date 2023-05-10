===================
Discrete integrator
===================

This module implements discrete time integrations as pure functions.
Thus, there is no internal state and the values of previous time steps have to be supplied.

Euler forward method
====================

Calculation of the discrete integration using the Euler forward method for discretization is simple but only provides sufficient accuracy if the sampling time is high compared to the system dynamics.
Calculation is as follows with the output value :math:`y(k)` at time step :math:`k`, the sampling time :math:`t_s` and the input to the integrator :math:`x(k)`:

.. math::

    y(k)=y(k-1)+t_s \cdot x(k)


Reference
=========

.. doxygenfunction:: uz_integrator_eulerforward

