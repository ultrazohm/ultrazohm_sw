.. _uz_IM_config:

=========
IM config
=========

Motor parameters of an induction machine (IM) are needed for field-oriented control functions.
To streamline the coding process, every necessary IM parameter is bundled inside a ``uz_IM_t`` struct, which can be used throughout the UltraZohm project.
Unlike PMSM, induction machines have more complex electrical parameters due to the rotor circuit and require a flux observer for field-oriented control.

Configuration Struct
====================

.. doxygenstruct:: uz_IM_t
    :members:

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example configuration for a typical 2.2 kW induction motor

  #include "uz/uz_IM_config/uz_IM_config.h"

  int main(void) {
     uz_IM_t my_motor = {
        // Electrical parameters (4-pole, 50 Hz, 2.2 kW)
        .Rs_Ohm = 2.2f,              // Stator resistance
        .Rr_Ohm = 1.8f,              // Rotor resistance (referred to stator)
        .Lsigma_s_Henry = 0.006f,    // Stator leakage inductance
        .Lsigma_r_Henry = 0.006f,    // Rotor leakage inductance
        .Lm_Henry = 0.18f,           // Magnetizing inductance

        // Mechanical parameters
        .polePairs = 2.0f,
        .J_kg_m_squared = 0.01f,

        // Limits
        .I_max_Ampere = 10.0f,
        .Psi_rated_Vs = 0.85f        // Rated rotor flux linkage
     };

     // Validate configuration
     uz_IM_config_assert(my_motor);
  }

Validation Function
===================

To avoid code duplication and ensure parameter validity, an assertion function is available:

.. doxygenfunction:: uz_IM_config_assert

Helper Functions
================

Several helper functions calculate derived parameters from the configuration:

Total Stator Inductance
------------------------

.. doxygenfunction:: uz_IM_get_Ls

Total Rotor Inductance
----------------------

.. doxygenfunction:: uz_IM_get_Lr

Leakage Factor (Sigma)
----------------------

The total leakage factor :math:`\sigma = 1 - \frac{L_m^2}{L_s \cdot L_r}` is important for decoupling calculations.

.. doxygenfunction:: uz_IM_get_sigma

Rotor Time Constant
-------------------

The rotor time constant :math:`\tau_r = \frac{L_r}{R_r}` determines the dynamics of the rotor flux.

.. doxygenfunction:: uz_IM_get_tau_r


See Also
========

* :ref:`uz_PMSM_config` - PMSM configuration
* :ref:`uz_FluxObserver_IM` - Rotor flux observer (to be implemented)
* :ref:`uz_CurrentControl_IM` - IM current control (to be implemented)
