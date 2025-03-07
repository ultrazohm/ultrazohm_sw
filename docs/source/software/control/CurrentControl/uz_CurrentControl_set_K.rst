.. _uz_CurrentControl_set_Kp_Ki:

================
Set new Ki or Kp
================

.. doxygenfunction:: uz_CurrentControl_set_Kp_id

.. doxygenfunction:: uz_CurrentControl_set_Kp_iq

.. doxygenfunction:: uz_CurrentControl_set_Ki_id

.. doxygenfunction:: uz_CurrentControl_set_Ki_iq


Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the Kp or Ki parameters. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     float Kp_id = 4.0f;
     uz_CurrentControl_set_Kp_id(CC_instance, Kp_id);
     float Kp_iq = 4.0f;
     uz_CurrentControl_set_Kp_iq(CC_instance, Kp_iq);
     float Ki_id = 20.0f;
     uz_CurrentControl_set_Ki_id(CC_instance, Ki_id);
     float Ki_iq = 20.0f;
     uz_CurrentControl_set_Ki_iq(CC_instance, Ki_iq);
  }

Description
===========

Gives the option to change the controller parameters during runtime. 
Each ``Ki`` and ``Kp`` of the two PI-Controllers have their own function.
The new values will be asserted again. 
