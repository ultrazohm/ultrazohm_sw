===================
Set new Ki function
===================

.. doxygenfunction:: uz_SpeedControl_set_Ki

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SpeedControl_init>`.

  int main(void) {
  float new_Ki = 14.5f;
     uz_SpeedControl_set_Ki(SpeedControl_instance, new_Ki);
  }

Description
===========

Updates the integral gain of the PI-Controller inside the SpeedControl during runtime.
Asserts that the new value is greater or equal than 0.0f.