.. _uz_SetPoint_set_PMSM_config:

===========================================
Set motor related parameters of PMSM struct
===========================================

.. doxygenfunction:: uz_SetPoint_set_PMSM_config

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SetPoint_init>`.

  int main(void) {
    uz_PMSM_t input = {
      .R_ph_Ohm = 0.08f,
      .Ld_Henry = 0.00027f,
      .Lq_Henry = 0.00027f,
      .Psi_PM_Vs = 0.0082f,
      .polePairs = 4.0f,
      .J_kg_m_squared = 0.00001773f,
      .I_max_Ampere = 10.0f
    };
    uz_SetPoint_set_PMSM_config(SP_instance, input);
  }


Description
===========

Updates the PMSM-parameters in the SpeedControl object to the new input values.
Every value of the struct will be asserted again.
