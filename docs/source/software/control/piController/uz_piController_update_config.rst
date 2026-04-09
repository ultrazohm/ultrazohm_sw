========================
Update saturation limits
========================

.. doxygenfunction:: uz_PI_Controller_update_limits

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
     float upper_limit = 5.0f;
     float lower_limit = -5.0f;
     PI_instance = uz_PI_Controller_update_limits(PI_instance, upper_limit, lower_limit);
  }
  

Description
===========

Updates the limits of the saturation function during runtime.