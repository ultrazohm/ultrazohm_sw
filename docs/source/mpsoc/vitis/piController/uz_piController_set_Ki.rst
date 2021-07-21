===================
Set new Ki function
===================

.. doxygenfunction:: uz_PI_Controller_set_Ki

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
  float new_Ki = 14.5f;
     uz_PI_Controller_set_Ki(PI_instance, new_Ki);
  }

Description
===========

Updates the integral gain of the PI-Controller during runtime.
Asserts that the new value is greater or equal than 0.0f.