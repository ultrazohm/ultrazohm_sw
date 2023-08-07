.. _uz_subspace_resonant_control:

=============================
Resonant Control for Subspace
=============================

General
-------

This module packages two :ref:`uz_resonant_controller` together, so that it can be used easier for controlling a complete subspace.
The idea is similar as for the :ref:`uz_CurrentControl`, as it is easier to just call one function instead of two seperate PI-Controllers or two seperate Resonant-Controllers in this case.
However this module adds no new math to the control and to understand the control scheme of the Resonant-Controller, please visit :ref:`uz_resonant_controller`.

Functions
---------

.. doxygentypedef:: uz_subspace_resonant_control

.. doxygenstruct:: uz_subspace_resonant_control_config
  :members:

.. doxygenfunction:: uz_subspace_resonant_control_init

.. doxygenfunction:: uz_subspace_resonant_control_step_dq

.. doxygenfunction:: uz_subspace_resonant_control_step_alphabeta

.. doxygenfunction:: uz_subspace_resonant_control_reset

.. doxygenfunction:: uz_subspace_resonant_control_set_gains

.. doxygenfunction:: uz_subspace_resonant_control_get_config

Usage
-----

During initialization, many of the parameters, such as the limits, the harmonic order, sampling time and anti-windup gain are shared for both controllers.
However, the user can set different gains for both controllers.
The control is executed with the step function, which is available for either dq- or :math:`\alpha\beta`-setpoints.

.. note::
   Be advised that not only the UZ_SUBSYSTEM_RESONANT_CONTROL_MAX_INSTANCES of this module must be high enough, but there also have to be enough UZ_RESONANT_CONTROLLER_MAX_INSTANCES, as two resonant controllers are initalized for each subsystem control object.

Example
-------

.. code-block:: c
  :linenos:
  :caption: Example to create and initialize the instance in ``main.c``

  #include "uz/uz_subspace_resonant_control/uz_subspace_resonant_control.h"
  struct uz_subspace_resonant_control_config config = {
	.antiwindup_gain = 10.0f,
	.gain_1 = 10.0f,
	.gain_2 = 15.0f,
	.harmonic_order = 5.0f,
	.lower_limit = -10.f,
	.upper_limit = 10.0f,
	.sampling_time = 0.0001f};
  uz_subspace_resonant_control* instance;
  ..
  instance = uz_subspace_resonant_control_init(config);

.. code-block:: c
  :linenos:
  :caption: Example to step the controller instance in ``isr.c``

  #include "../uz/uz_subspace_resonant_control/uz_subspace_resonant_control.h"
  extern uz_subspace_resonant_control* instance;
  ..
  uz_3ph_dq_t xy_rotating = uz_subspace_resonant_control_step_dq(instance, setpoint, actual, omega_el);

