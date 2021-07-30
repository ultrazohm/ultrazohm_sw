================================
Update config struct of instance
================================

.. doxygenfunction:: uz_PI_Controller_update_config

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
     uz_PI_Controller_config config = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.00002f,
        .upper_limit = 10.0f,
        .lower_limit = -10.0f
     };
  }
  PI_instance = uz_PI_Controller_update_config(PI_instance, config);

Description
===========

Updates every value in the config struct with the latest value in the uz_PI_Controller configuration struct.
It is mainly needed for the uz_FOC.