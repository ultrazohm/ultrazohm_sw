.. _uz_FOC_set_Kp_Ki:

================
Set new Ki or Kp
================

.. doxygenfunction:: uz_FOC_set_Kp_id

.. doxygenfunction:: uz_FOC_set_Kp_iq

.. doxygenfunction:: uz_FOC_set_Ki_id

.. doxygenfunction:: uz_FOC_set_Ki_iq


Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the Kp or Ki parameters. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     float Kp_id = 4.0f;
     uz_FOC_set_Kp_id(FOC_instance, Kp_id);
     float Kp_iq = 4.0f;
     uz_FOC_set_Kp_iq(FOC_instance, Kp_iq);
     float Ki_id = 20.0f;
     uz_FOC_set_Ki_id(FOC_instance, Ki_id);
     float Ki_iq = 20.0f;
     uz_FOC_set_Ki_iq(FOC_instance, Ki_iq);
  }

Description
===========

Gives the option to change the controller parameters during runtime. 
Each ``Ki`` and ``Kp`` of the two PI-Controllers have their own function.
The new values will be asserted again. 
