.. _uz_CurrentControl_set_motor_param:

========================
Set new motor parameters
========================

.. doxygenfunction:: uz_CurrentControl_set_PMSM_parameters

Example
=======

.. code-block:: c
  :linenos:
  :caption: Update the motor parameters of an instance created via :ref:`uz_CurrentControl_init`.

  int main(void) {
     struct uz_PMSM_t config = {      
      .Ld_Henry = 0.00027f,
      .Lq_Henry = 0.00027f,
      .Psi_PM_Vs = 0.0082f,
     };
     uz_CurrentControl_set_PMSM_parameters(CC_instance, &config);
  }

Description
===========

Gives the option to change the motor parameters, which are needed for the linear decoupling, during runtime. 
Pass a pointer to the updated :ref:`uz_PMSM_config` struct; the setter copies the complete struct into the instance's own configuration.
The caller's struct only needs to remain valid during the call, and later changes to it do not affect the instance.
The setter asserts ``Ld_Henry > 0.0f``, ``Lq_Henry > 0.0f``, and ``Psi_PM_Vs >= 0.0f``.
