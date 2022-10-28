=========================
Updates saturation limits
=========================

.. doxygenfunction:: uz_SpeedControl_update_limits

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SpeedControl_init>`.

  int main(void) {
  float upper_limit = 14.5f;
  float lower_limit = -14.5f;
     uz_SpeedControl_update_limits(SpeedControl_instance, upper_limit, lower_limit);
  }

Description
===========

Updates the limits of the saturation function during runtime.