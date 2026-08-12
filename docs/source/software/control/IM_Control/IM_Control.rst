.. _uz_im_control:

=========================
Induction Machine Control
=========================

``uz_im_control`` is a self-contained induction-machine controller following
the same module pattern as :ref:`uz_pmsm_control`. Application-specific data,
ISR code and hardware addresses are deliberately not part of the module.

The module owns all persistent state required by:

* two PI current controllers for the rotor-flux-oriented d/q axes,
* one PI speed controller whose output is the q-current reference,
* rotor-current-model flux observation,
* optional Kalman filtering of the measured alpha/beta currents,
* scalar U/f operation with frequency ramp, voltage boost and SVM,
* safe-operating-region checks and a latched fault state.

Structure
=========

The complete implementation is located in ``uz/uz_IM_Control`` and consists
of one public header and one implementation file. Machine parameters are passed
to ``uz_im_control_init`` using :ref:`uz_IM_config`; the control module contains
no machine-specific presets.

Configuration and data types
============================

.. doxygentypedef:: uz_IM_t

.. doxygenstruct:: uz_IM_t
   :members:

.. doxygenstruct:: uz_im_control_configuration_t
   :members:

.. doxygenstruct:: uz_im_control_limits_t
   :members:

.. doxygenstruct:: uz_im_measurement_values
   :members:

.. doxygenstruct:: uz_im_reference_values
   :members:

.. doxygenstruct:: uz_im_actual_data
   :members:

Operation
=========

FOC is the default mode. ``uz_im_control_sample_duty`` executes observation,
speed control when enabled, both current controllers, IM decoupling and SVM.
In U/f mode, the same function ramps the requested stator frequency and
generates the rotating voltage vector internally. Observer diagnostics remain
available in both modes.

.. code-block:: c

   uz_im_control_t *control = uz_im_control_init(configuration, machine);
   uz_im_control_enable(control, true);

   struct uz_DutyCycle_t duty = uz_im_control_sample_duty(
       control,
       measurements,
       speed_reference_rpm,
       current_reference_dq_A,
       u_f_frequency_reference_Hz);

The module returns the configured default duty cycle while disabled or after a
safe-operating-region violation. A fault remains latched until explicitly
acknowledged.

API reference
=============

.. doxygenfunction:: uz_im_control_init
.. doxygenfunction:: uz_im_control_enable
.. doxygenfunction:: uz_im_control_set_mode
.. doxygenfunction:: uz_im_control_enable_speed_control
.. doxygenfunction:: uz_im_control_set_observer
.. doxygenfunction:: uz_im_control_sample_duty
.. doxygenfunction:: uz_im_control_sample_dq
.. doxygenfunction:: uz_im_control_reset
.. doxygenfunction:: uz_im_control_get_actual_data
.. doxygenfunction:: uz_im_control_get_reference_values
.. doxygenfunction:: uz_im_control_get_im_measurement_values
.. doxygenfunction:: uz_im_control_get_safe_operating_area_violation
.. doxygenfunction:: uz_im_control_acknowledge_and_reset_error
.. doxygenfunction:: uz_im_control_current_control_set_Kp_id
.. doxygenfunction:: uz_im_control_current_control_set_Ki_id
.. doxygenfunction:: uz_im_control_current_control_set_Kp_iq
.. doxygenfunction:: uz_im_control_current_control_set_Ki_iq
.. doxygenfunction:: uz_im_control_speed_control_set_Kp_speed
.. doxygenfunction:: uz_im_control_speed_control_set_Ki_speed

Tests
=====

Unit tests are located in ``test/uz/uz_IM_Control`` and cover initialization,
disabled output, fault latching and U/f operation.
