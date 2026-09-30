.. _uz_IM_config:

===============================
Induction Machine Configuration
===============================

The induction-machine configuration module is structured in parallel to
:ref:`uz_pmsm_control` and its :ref:`uz_PMSM_config`. All machine parameters
required by IM control and observers are bundled in :c:type:`uz_IM_t` so one
configuration can be reused throughout the application.

Electrical quantities are phase values referred to the stator side. Controller
tuning and application-specific limits are intentionally kept separate.

Machine parameter structure
===========================

.. doxygenstruct:: uz_IM_t
   :members:

Validation and derived parameters
=================================

Call :c:func:`uz_IM_config_assert` after creating a configuration to verify
that every parameter is positive and that ``polePairs`` is an integer. The
helper functions calculate commonly required quantities for
equivalent-circuit parameters, keeping these calculations consistent between
users of the configuration.

.. doxygenfunction:: uz_IM_config_assert
.. doxygenfunction:: uz_IM_config_get_Ls
.. doxygenfunction:: uz_IM_config_get_Lr
.. doxygenfunction:: uz_IM_config_get_sigma
.. doxygenfunction:: uz_IM_config_get_rotor_time_constant

Example
-------

The following example creates and validates an induction-machine
configuration. Replace the example values with parameters referred to the
stator side of the machine being used.

.. code-block:: c
   :linenos:
   :caption: Example induction-machine configuration

   #include "uz/uz_IM_config/uz_IM_config.h"

   int main(void) {
       uz_IM_t machine_config = {
           .Rs_Ohm = 2.0f,
           .Rr_Ohm = 1.5f,
           .Lsigma_s_Henry = 0.01f,
           .Lsigma_r_Henry = 0.01f,
           .Lm_Henry = 0.2f,
           .polePairs = 2.0f,
           .J_kg_m_squared = 0.01f,
           .I_max_Ampere = 10.0f,
           .Psi_rated_Vs = 0.5f,
       };
       uz_IM_config_assert(machine_config);
   }