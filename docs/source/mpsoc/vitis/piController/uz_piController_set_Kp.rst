===================
Set new Kp function
===================

.. doxygenfunction:: uz_PI_Controller_set_Kp

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
  float new_Kp = 14.5f;
  uz_PI_Controller_set_Kp(PI_instance, new_Kp);
  }

Description
===========

Updates the proportional gain of the PI-Controller during runtime. Asserts, if the new value is greater or equal than 0.0f.

   


