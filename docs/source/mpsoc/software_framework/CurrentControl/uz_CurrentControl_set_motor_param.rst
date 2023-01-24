.. _uz_CurrentControl_set_motor_param:

========================
Set new motor parameters
========================

.. doxygenfunction:: uz_CurrentControl_set_PMSM_parameters

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the motor parameters. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`. PMSM struct via :ref:`uz_PMSM_config`.

  int main(void) {
     struct uz_PMSM_t config = {      
      .Ld_Henry = 0.00027f,
      .Lq_Henry = 0.00027f,
      .Psi_PM_Vs = 0.0082f,
     };
     uz_CurrentControl_set_PMSM_parameters(CC_instance, config_PMSM );
  }

Description
===========

Gives the option to change the motor parameters, which are needed for the linear decoupling, during runtime. 
The changed parameters can be written into a PMSM-struct and passed to the function.
The new values will be asserted again. 
