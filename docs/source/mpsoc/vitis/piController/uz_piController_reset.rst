====================
PI-Controller reset
====================

.. doxygenfunction:: uz_PI_Controller_reset

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the PI-Controller output. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
  uz_PI_Controller_reset(PI_instance);
  }

Description
===========

Resets the PI-Controller. Initial condition for the integrator after the reset is 0.0f.

   


