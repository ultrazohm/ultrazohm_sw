.. _uz_SpeedControl:

=============
Speed Control
=============

Toolbox for a standard SpeedControl with a :ref:`PI-Controller <uz_piController>` in parallel form. 
It outputs only the reference **torque** for a subsequent setpoint and current-control module.
It can not control a machine on its own. 

Setup
=====

.. doxygentypedef:: uz_SpeedControl_t

.. _uz_SpeedControl_config:

Configuration
-------------

.. doxygenstruct:: uz_SpeedControl_config
  :members:

In order to configure the SpeedControl check the :ref:`configuration section of the PI-Controller <uz_piController_config>` for further information.

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration
  
  #include "uz/uz_SpeedControl/uz_speedcontrol.h"
  int main(void) {
     struct uz_SpeedControl_config SC_config = {
        .config_controller.Kp = 10.0f,
        .config_controller.Ki = 10.0f,
        .config_controller.samplingTime_sec = 0.00005f,
        .config_controller.upper_limit = 10.0f,
        .config_controller.lower_limit = -10.0f,
     };
  }

.. _uz_SpeedControl_init:

Init function
-------------

.. doxygenfunction:: uz_SpeedControl_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init the SpeedController for the SpeedControl. ``config`` according to :ref:`configuration section<uz_SpeedControl_config>`
  
  int main(void) {
     uz_SpeedControl_t* SC_instance = uz_SpeedControl_init(SC_config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the SpeedControl instance. 
Furthermore the input values of the configuration struct are asserted. 

.. _uz_SpeedControl_reset:

Reset
-----

.. doxygenfunction:: uz_SpeedControl_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the SpeedControl. SpeedControl instance via :ref:`init-function <uz_SpeedControl_init>`.

  int main(void) {
     uz_SpeedControl_reset(SC_instance);
  }

Description
^^^^^^^^^^^

Resets the PI-Controller of the SpeedControl. 
The initial condition for the integrator after the reset is 0.0f.

Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *