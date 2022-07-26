.. _uz_SetPoint:

=========
Set Point
=========

Toolbox for a standard set-point module. The input is a reference torque. This will then be converted, depending on the machine type selection, into d- and q-reference currents.
It currently supports surface-mounted (SMPMSM) and interior (IPMSM) permanent magnet synchronous machines. 
The output currents will either be calculated via MTPA or field-weakening, depending on the operating condition of the machine.
It can not control a machine on its own. 

Setup
=====

.. doxygentypedef:: uz_SetPoint_t

.. _uz_SetPoint_config:

Configuration
-------------

.. doxygenenum:: uz_Setpoint_motor_type
  
.. doxygenstruct:: uz_SetPoint_config
  :members:

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration
  
  #include "uz/uz_setpoint/uz_setpoint.h"
  int main(void) {
     struct uz_SpeedControl_config config = {
        .config_controller.Kp = 10.0f,
        .config_controller.Ki = 10.0f,
        .config_controller.samplingTime_sec = 0.00005f,
        .config_controller.upper_limit = 10.0f,
        .config_controller.lower_limit = -10.0f,
     };
  }

.. _uz_SetPoint_init:

Init function
-------------

.. doxygenfunction:: uz_SetPoint_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init the SpeedController for the SpeedControl. ``config`` according to :ref:`configuration section<uz_SetPoint_config>`
  
  int main(void) {
     uz_SetPoint_t* instance = uz_SetPoint_init(config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the SetPoint instance. 
Furthermore the input values of the configuration struct are asserted. 

Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *