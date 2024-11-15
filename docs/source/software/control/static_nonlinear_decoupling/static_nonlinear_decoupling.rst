.. _uz_static_nonlineardecoupling:

===========================
Static nonlinear decoupling
===========================

.. doxygenfunction:: uz_CurrentControl_static_nonlinear_decoupling

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call for static nonlinear decoupling.

  #include "uz/uz_CurrentControl/uz_static_nonlinear_decoupling.h"
  int main(void) {
     float omega_el_rad_per_sec = 100.0f;
     struct uz_3ph_dq_t flux_approximation = {.d = 0.016f, .q = 0.010f, .zero = 0.0f};
     struct uz_3ph_dq_t output = uz_CurrentControl_static_nonlinear_decoupling(flux_approximation, omega_el_rad_per_sec);
  }

Description
===========

Calculates the values for a static nonlinear decoupling according to the following formulars:

.. math::

    v_{d,decoup} &= -\omega_{el} \cdot \psi_q\\
    v_{q,decoup} &= \omega_{el} \cdot \psi_d

This function is already included in the :ref:`uz_CurrentControl`, but it can be used independently for any other purpose.