.. _uz_u_f_control:

============================
U/f Control (uz_u_f_control)
============================

Description
-----------

``uz_u_f_control`` implements scalar voltage-frequency control for a three-phase machine.
It wraps the former ISR implementation in a reusable stateful module. Each sample ramps the
electrical frequency, evaluates the U/f characteristic, integrates the electrical phase and
uses :ref:`Space vector Modulation <uz_spacevectormodulation>` to produce duty cycles.

The commanded RMS line-to-line voltage is

.. math::

   V_{LL,rms} = \min(k_{U/f} f + V_{boost}, V_{max}).

The boost is active only above 0.1 Hz, matching the original implementation. Before SVM,
the voltage is converted to peak line-to-neutral voltage by

.. math::

   V_{LN,peak} = V_{LL,rms}\sqrt{\frac{2}{3}}.

It is additionally limited from the measured DC-link voltage and ``minimum_pulse_width``.
Frequency setpoints are limited to ``[0, max_frequency_Hz]`` and approached with the configured
``frequency_ramp_Hz_per_s``. Sample times below 1 us, ramp values below 0.1 Hz/s, and DC-link
voltages below 1 V use the same lower limits as the original ISR code.

Usage
-----

.. code-block:: c

   #include "uz/uz_u_f_control/uz_u_f_control.h"

   static uz_u_f_control_t *u_f_control;

   void init_control(void)
   {
       struct uz_u_f_control_config_t config = {
           .frequency_setpoint_Hz = 0.0f,
           .max_frequency_Hz = 50.0f,
           .frequency_ramp_Hz_per_s = 10.0f,
           .ratio_V_per_Hz = 4.0f,
           .boost_voltage_V = 5.0f,
           .max_voltage_V = 230.0f,
           .minimum_pulse_width = 0.05f,
           .dc_link_voltage_lower_bound_V = 20.0f,
           .dc_link_voltage_upper_bound_V = 450.0f,
           .default_duty_cycle = {
               .DutyCycle_A = 0.5f,
               .DutyCycle_B = 0.5f,
               .DutyCycle_C = 0.5f}};
       u_f_control = uz_u_f_control_init(config);
   }

   void ISR_Control(void)
   {
       uz_u_f_control_set_frequency(u_f_control, frequency_reference_Hz);
       struct uz_DutyCycle_t duty = uz_u_f_control_sample(
           u_f_control, measured_dc_link_voltage_V, isr_sample_time_s);
       /* Pass duty.DutyCycle_A/B/C to the PWM driver. */
   }

The pointer returned by ``uz_u_f_control_get_data`` exposes the ramped frequency, phase and
applied voltage for JavaScope without exposing mutable module state. Call
``uz_u_f_control_reset`` when the control state is left.

Safety behavior
---------------

The SVM implementation saturates its output to the absolute range ``[0, 1]``. In addition,
this module limits the voltage vector so that the configured usable range
``[minimum_pulse_width, 1 - minimum_pulse_width]`` is respected. The resulting duty cycles
are checked explicitly after SVM. DC-link under- and overvoltage are checked before executing
the control algorithm. Non-finite voltage or duty-cycle values are treated as violations.

A violation is latched and subsequent samples return ``default_duty_cycle``. Use
``uz_u_f_control_get_safe_operating_area_violation`` for diagnostics. The fault can only be
cleared with ``uz_u_f_control_acknowledge_and_reset_error`` while the supplied DC-link voltage
is inside the configured limits. Successful acknowledgement also resets ramp and phase state.

The number of available instances is selected with ``UZ_U_F_CONTROL_MAX_INSTANCES`` in
``uz_global_configuration.h``.

API Reference
-------------

.. doxygenstruct:: uz_u_f_control_config_t
   :members:

.. doxygenstruct:: uz_u_f_control_data_t
   :members:

.. doxygentypedef:: uz_u_f_control_t

.. doxygenenum:: uz_u_f_control_safe_operating_region_violation

.. doxygenfunction:: uz_u_f_control_init

.. doxygenfunction:: uz_u_f_control_sample

.. doxygenfunction:: uz_u_f_control_set_frequency

.. doxygenfunction:: uz_u_f_control_reset

.. doxygenfunction:: uz_u_f_control_get_data

.. doxygenfunction:: uz_u_f_control_get_safe_operating_area_violation

.. doxygenfunction:: uz_u_f_control_acknowledge_and_reset_error
