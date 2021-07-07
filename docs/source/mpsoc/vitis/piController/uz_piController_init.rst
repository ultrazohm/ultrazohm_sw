.. _uz_piController_init:

===========================
PI-Controller init function
===========================

.. doxygenfunction:: uz_PI_Controller_init

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to init a PI-Controller instance. Config according to :ref:`init-function <uz_piController_config>`

  #include "uz_piController.h"
  int main(void) {
     uz_PI_Controller PI_instance = uz_PI_Controller_init(config);
  }

Description
===========

Allocates the memory for the PI-Controller instance and asserts the input values of the configuration struct. 

   


