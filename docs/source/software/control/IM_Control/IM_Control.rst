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

.. doxygenstruct:: uz_im_setpoint_limits_t
   :members:

.. doxygenstruct:: uz_im_safe_operating_region_t
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

Speed and d/q-current references are first restricted to ``setpoint_limits``.
First-order low-pass filters for the d/q-current references, speed reference
and measured speed are enabled by setting their respective cutoff frequency
to a value greater than zero; a value of zero bypasses the filter. The speed
PI directly produces the q-current reference and therefore uses the configured
``i_q_in_A`` bounds. The torque bounds are retained in the public configuration
for a future torque-to-current setpoint stage, but are not applied by the
current q-current-based speed controller.

The safe-operating-region limits independently cover speed, d/q currents,
all three phase currents, DC-link voltage and DC-link current. Violations are
latched before a new inverter command is returned.

SOR diagnosis in JavaScope
--------------------------

``uz_im_actual_data.safe_operating_region_status`` exposes the latched SOR
state as an unsigned integer and can be added directly as a JavaScope variable.
The first detected violation remains visible until
``uz_im_control_acknowledge_and_reset_error`` is called.

.. list-table:: SOR status codes
   :header-rows: 1
   :widths: 15 45 40

   * - Code
     - Enum
     - Meaning
   * - 0
     - ``uz_im_control_no_violation``
     - No violation
   * - 1
     - ``uz_im_control_underspeed``
     - Speed below lower limit
   * - 2
     - ``uz_im_control_overspeed``
     - Speed above upper limit
   * - 3
     - ``uz_im_control_dc_overvoltage``
     - DC-link voltage above upper limit
   * - 4
     - ``uz_im_control_dc_undervoltage``
     - DC-link voltage below lower limit
   * - 5 / 6
     - ``uz_im_control_dc_overcurrent`` / ``uz_im_control_dc_undercurrent``
     - DC-link current above / below its limits
   * - 7 / 8
     - ``uz_im_control_i_d_overcurrent`` / ``uz_im_control_i_d_undercurrent``
     - d-current above / below its limits
   * - 9 / 10
     - ``uz_im_control_i_q_overcurrent`` / ``uz_im_control_i_q_undercurrent``
     - q-current above / below its limits
   * - 11 / 12
     - ``uz_im_control_phase_overcurrent`` / ``uz_im_control_phase_undercurrent``
     - At least one phase current above / below its limits
   * - 13
     - ``uz_im_control_observer_violation``
     - Observer produced a non-finite flux value

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

.. doxygenenum:: uz_im_control_safe_operating_region_violation

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
configuration validation, setpoint limiting, disabled output, fault latching
and U/f operation.
