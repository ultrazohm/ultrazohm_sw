.. _uz_FOC_set_motor_param:

========================
Set new motor parameters
========================

.. doxygenfunction:: uz_FOC_set_Ld

.. doxygenfunction:: uz_FOC_set_Lq

.. doxygenfunction:: uz_FOC_set_Psi_PM

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the motor parameters. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     float Ld_Henry = 0.00027f;
     uz_FOC_set_Ld(FOC_instance, Ld_Henry);
     float Lq_Henry = 0.00027f;
     uz_FOC_set_Lq(FOC_instance, Lq_Henry);
     float Psi_PM_Vs = 0.0082f;
     uz_FOC_set_Psi_PM(FOC_instance, Psi_PM_Vs);
  }

Description
===========

Gives the option to change the motor parameters, which are needed for the linear decoupling, during runtime. 
``Ld``, ``Lq`` and ``Psi_PM`` have their own function.
The new values will be asserted again. 
