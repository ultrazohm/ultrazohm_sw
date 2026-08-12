.. _uz_IM_config:

============================
Induction Machine Configuration
============================

``uz_IM_config`` contains the electrical and mechanical machine parameters
used by :ref:`uz_im_control`. It follows the same separation as
:ref:`uz_PMSM_config`: machine data is independent of controller tuning and no
application-specific motor preset is included.

.. code-block:: c

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

API reference
=============

.. doxygentypedef:: uz_IM_t

.. doxygenstruct:: uz_IM_t
   :members:

.. doxygenfunction:: uz_IM_config_assert
.. doxygenfunction:: uz_IM_config_get_Ls
.. doxygenfunction:: uz_IM_config_get_Lr
.. doxygenfunction:: uz_IM_config_get_sigma
.. doxygenfunction:: uz_IM_config_get_rotor_time_constant
