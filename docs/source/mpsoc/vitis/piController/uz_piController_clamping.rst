==============================
PI-Controller clamping circuit
==============================

.. doxygenfunction:: uz_PI_Controller_Clamping_Circuit

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call for clamping circuit

  #include "uz_piController.h"
  int main(void) {
     float preIntegrator = 10.5f;
     float preSat = 1.1f;
     float upper_threshold = 10.0f;
     float lower_threshold = -8.0f;
     bool output = uz_PI_Controller_Clamping_Circuit(preIntegrator, preSat, upper_threshold, lower_threshold);
  }

Description
===========

Compares the values before and after the integrator and decides, if clamping is necessary. Is already integrated into the :ref:`sample-function <uz_piController_sample>` function. 

   


