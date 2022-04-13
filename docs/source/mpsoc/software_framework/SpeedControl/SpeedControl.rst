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

.. doxygentypedef:: uz_SpeedControl_t

.. _uz_SpeedControl_config:

Configuration
-------------

.. doxygenstruct:: uz_SpeedControl_config
  :members:

In order to configure the SpeedControl check the :ref:`configuration section of the PI-Controller <uz_piController_config>` for further information.
If field_weakening is to be used, some values of the :ref:`uz_PMSM_t struct <uz_PMSM_config>` have to be initialized as well. Otherwise they can be left zero.

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration
  
  #include "uz/uz_SpeedControl/uz_speedcontrol.h"
  int main(void) {
     struct uz_SpeedControl_config config = {
        .config_controller.Kp = 10.0f,
        .config_controller.Ki = 10.0f,
        .config_controller.samplingTime_sec = 0.00005f,
        .config_controller.upper_limit = 10.0f,
        .config_controller.lower_limit = -10.0f,
        .config.config_PMSM.R_ph_Ohm = 0.08f,
        .config.config_PMSM.Ld_Henry = 0.00027f,
        .config.config_PMSM.Lq_Henry = 0.00027f,
        .config.config_PMSM.Psi_PM_Vs = 0.0082f,
        .config.config_PMSM.polePairs = 4.0f,
        .config.config_PMSM.I_max_Ampere = 10.0f,
        .enable_field_weakening = false
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
     uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
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