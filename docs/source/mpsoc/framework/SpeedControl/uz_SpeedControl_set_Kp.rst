===================
Set new Kp function
===================

.. doxygenfunction:: uz_SpeedControl_set_Kp

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call.

  int main(void) {
  float new_Kp = 14.5f;
     uz_SpeedControl_set_Ki(SpeedControl_instance, new_Kp);
  }

Description
===========

Updates the proportional gain of the PI-Controller inside the SpeedControl during runtime.
Asserts that the new value is greater or equal than 0.0f.