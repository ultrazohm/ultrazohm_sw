.. _uz_CurrentControl_get_Kp:

======
Get Kp
======

.. doxygenfunction:: uz_CurrentControl_get_Kp_id

.. doxygenfunction:: uz_CurrentControl_get_Kp_iq


Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to receive the Kp parameters. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     float Kp_id = uz_CurrentControl_set_Kp_id(CC_instance);
     float Kp_iq = uz_CurrentControl_set_Kp_iq(CC_instance);
  }

Description
===========

Reads out the current value for Kp for each pi controller.
