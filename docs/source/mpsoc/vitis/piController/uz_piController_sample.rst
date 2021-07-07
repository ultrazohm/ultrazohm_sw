.. _uz_piController_sample:

====================
PI-Controller sample
====================

.. doxygenfunction:: uz_PI_Controller_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the PI-Controller output. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
     float referenceValue = 1.5f;
     float actualValue = 1.1f;
     bool ext_clamping = false;
     float output = uz_PI_Controller_sample(PI_instance, referenceValue, actualValue, ext_clamping);
  }

Description
===========

Calculates the last sample of the PI-Controller. Has an integrated clamping circuit and an input port for an external
clamping signal. The error between the reference and actual value will be calculated inside the function. 

   


