.. _uz_FOC_change_control_method:

=====================
Change control method
=====================

.. doxygenfunction:: uz_FOC_change_control_Method

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the FOC control method. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     FOC_instance = uz_FOC_change_control_Method(FOC_instance, config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
  }

Description
===========

Gives the option to change the control method of the FOC from SpeedControl to CurrentControl or vice versa after the FOC instance has been initialized.
Too ensure proper functionality in either mode, all config structs have to be written from and asserted again. 
This function can only be called if the ``FOC_Select`` actually changes from the old value, otherwise an assert will be triggered since the function would just resemble a :ref:`reset function <uz_FOC_reset>`.  
