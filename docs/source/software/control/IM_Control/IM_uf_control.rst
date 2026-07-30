.. _uz_IM_uf_control:

========================
Induction machine U/f control
========================

The U/f controller is an open-loop commissioning alternative to FOC. It ramps
the requested electrical frequency, calculates voltage magnitude from a V/Hz
ratio and boost voltage, integrates the electrical phase and produces phase
voltages and PWM duties.

Configuration and state
=======================

.. doxygenstruct:: im_uf_control_config_t
   :members:

.. doxygenstruct:: im_uf_control_state_t
   :members:

``frequency_ramp_Hz_per_s`` limits the rate of change of the internal frequency
command. ``max_frequency_Hz`` and ``max_voltage_V`` constrain the operating
range. ``applied_voltage_magnitude_V`` is a read-only diagnostic value.

Step function
=============

.. doxygenfunction:: im_uf_control_step

Example
-------

.. code-block:: c

   im_uf_control_config_t config = {
      .frequency_setpoint_Hz = 10.0f,
      .ratio_V_per_Hz = 8.0f,
      .boost_voltage_V = 1.0f,
      .max_frequency_Hz = 50.0f,
      .max_voltage_V = 400.0f,
      .frequency_ramp_Hz_per_s = 2.5f,
   };

   uz_3ph_abc_t voltage_abc =
      im_uf_control_step(&actual_values,
                         &reference_values,
                         &config,
                         &state);

Reset
=====

.. doxygenfunction:: im_uf_control_reset

Reset clears the ramped frequency, integrated phase and applied-voltage
diagnostic. The controller must be reset when switching away from U/f control
or stopping the machine.
