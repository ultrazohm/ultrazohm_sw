.. _uz_FOC_set_Kp_Ki:

================
Set new Ki or Kp
================

.. doxygenfunction:: uz_FOC_set_Kp_n

.. doxygenfunction:: uz_FOC_set_Kp_id

.. doxygenfunction:: uz_FOC_set_Kp_iq

.. doxygenfunction:: uz_FOC_set_Ki_n

.. doxygenfunction:: uz_FOC_set_Ki_id

.. doxygenfunction:: uz_FOC_set_Ki_iq


Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the Kp or Ki parameters. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     float Kp_n = 0.058f;
     uz_FOC_set_Kp_n(FOC_instance, float Kp_n);
     float Kp_id = 4.0f;
     uz_FOC_set_Kp_id(FOC_instance, float Kp_id);
     float Kp_iq = 4.0f;
     uz_FOC_set_Kp_iq(FOC_instance, float Kp_iq);
     float Ki_n = 0.100f;
     uz_FOC_set_Ki_n(FOC_instance, float Ki_n);
     float Ki_id = 20.0f;
     uz_FOC_set_Ki_id(FOC_instance, float Ki_id);
     float Ki_iq = 20.0f;
     uz_FOC_set_Ki_iq(FOC_instance, float Ki_iq);
  }

Description
===========

Gives the option to change the controller parameters during runtime. 
Each ``Ki`` and ``Kp`` of the three PI-Controllers have their own function.
The new values will be asserted again. 
