.. _uz_piController_config:

===========================
PI-Controller Configuration
===========================

.. doxygenstruct:: uz_PI_Controller_config
  :members:

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call initialize the configuration struct

  #include "uz_piController.h"
  int main(void) {
     uz_PI_Controller_config config = {
        .Kp = 10.0f,
        .Ki = 10.0f,
        .samplingTime_sec = 0.001f,
        .upper_threshold = 10.0f,
        .lower_threshold = -10.0f
     };
  }

Description
===========

With this config struct one can customize the PI-Controller variables to its needs.
It has to be initialized before the :ref:`init-function <uz_piController_init>` is called.


