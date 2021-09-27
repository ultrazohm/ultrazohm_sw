.. _uz_SpeedControl:

=============
Speed Control
=============

Toolbox for a standard SpeedControl with a :ref:`PI-Controller <uz_piController>` in parallel form. 
It outputs only the reference currents for the :ref:`FOC <uz_FOC>`.
Other control algorithms can be used as well.
It can not control a machine on its own. 

Setup
=====

.. _uz_SpeedControl_config:

Configuration
-------------

In order to configure the SpeedControl check the :ref:`configuration section of the PI-Controller <uz_piController_config>` for further information.
Some values of the :ref:`uz_PMSM_t struct <uz_PMSM_config>` have to be initialized as well.

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration
  
  #include "uz/uz_SpeedControl/uz_speedcontrol.h"
  int main(void) {
     struct uz_PI_Controller_config config = {
      .Kp = 10.0f,
      .Ki = 10.0f,
      .samplingTime_sec = 0.00005f,
      .upper_limit = 10.0f,
      .lower_limit = -10.0f
     }; 
     struct uz_PMSM_t config_PMSM = {
      .R_ph_Ohm = 0.08f,
      .Ld_Henry = 0.00027f,
      .Lq_Henry = 0.00027f,
      .Psi_PM_Vs = 0.0082f,
      .polePairs = 4.0f,
      .I_max_Ampere = 10.0f
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
  :caption: Example function call to init a PI-Controller for the SpeedControl. ``config`` according to :ref:`configuration section<uz_piController_config>`
  
  #include "uz/uz_SpeedControl/uz_speedcontrol.h"
  int main(void) {
     uz_PI_Controller* instance = uz_SpeedControl_init(config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the PI-Controller instance. 
Furthermore the input values of the configuration struct are asserted. 

.. _uz_SpeedControl_reset:

Reset
-----

.. doxygenfunction:: uz_SpeedControl_reset

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to reset the SpeedControl. PI-Controller instance via :ref:`init-function <uz_SpeedControl_init>`

  int main(void) {
     uz_SpeedControl_reset(instance);
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