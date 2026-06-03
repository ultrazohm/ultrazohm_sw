.. _uz_pmsm_control:

==============================
PMSM Control (uz_pmsm_control)
==============================


Description
-----------

The PMSM control module combines :ref:`Speed Control <uz_SpeedControl>`, :ref:`Set Point <uz_SetPoint>`, :ref:`CurrentControl <uz_CurrentControl>`, coordinate transformations, and :ref:`Space vector Modulation <uz_spacevectormodulation>` to provide a complete field-oriented control (FOC) for permanent magnet synchronous machines.
The module supports two operating modes: current-control mode and speed-control mode.
In current-control mode, the externally supplied :math:`i_d`/:math:`i_q` references are used.
In speed-control mode, the module calculates the current reference from a speed reference using the :ref:`Set Point <uz_SetPoint>`, :ref:`CurrentControl <uz_CurrentControl>`.

The module outputs can be requested either as a dq-voltage vector or as duty cycles for an inverter where space vector modulation is used by the module.
Thus, the output can be fed to the :ref:`PWM and SS Control V4 <uz_pwm_ss_2l>`.
The module offers reference limitation, optional first-order setpoint and speed filtering, rotor-angle compensation, controller reset behavior, and safe operating region monitoring.

Control
-------

Call one of the two available sample functions exactly once per control tick, i.e., in the interrupt service routine.
Use ``uz_pmsm_control_sample_dq`` if the next layer needs dq-voltages, e.g., for :ref:`controller in the loop <cil>` or when using the :ref:`software PMSM model <uz_pmsm_swmodel>`.
Use ``uz_pmsm_control_sample_duty`` if the next layer needs duty cycles; this function calls ``uz_pmsm_control_sample_dq`` internally before running :ref:`Space vector Modulation <uz_spacevectormodulation>`.

For each sample, the implementation performs the following steps:

#. Saturate the speed reference, current references, and disturbance torque input to ``setpoint_limits``.
#. Optionally low-pass filter the measured mechanical speed if ``speed_actual_value_filter_cutoff_frequency`` is non-zero.
#. Store the measurements and calculate actual control values:

   .. math::

      \omega_{el} = p \omega_{mech}

   .. math::

      n_{mech} = \omega_{mech} \frac{60}{2 \pi}

   .. math::

      \theta_{el} =
      \operatorname{wrap}(p \theta_{mech}, 2 \pi) - \theta_{offset}
      + k_{sampling} \omega_{el} T_s

   After this sampling compensation, ``theta_el`` is wrapped to :math:`2 \pi`.
   ``theta_el_advanced`` is calculated by the following equation:

   .. math::

      \theta_{el,advanced} =
      \theta_{el} + k_{svm} \omega_{el} T_s

   where :math:`p` is ``machine_data.polePairs``, :math:`T_s` is ``sample_time``, :math:`k_{sampling}` is ``theta_sampling_compensation``, and :math:`k_{svm}` is ``theta_svm_delay_compensation``.
   The measured phase currents are transformed to dq with ``theta_el``.
   The measured phase voltages are transformed with the following angle:

   .. math::

      \theta_{voltage} =
      \theta_{el} - k_{voltage} \omega_{el} T_s

   where ``k_voltage`` is ``voltage_theta_shift`` and ``theta_el`` is the offset- and sampling-compensated angle before the final wrapping step.
#. Check the safe operating region.
#. Optionally low-pass filter the speed reference if ``setpoint_filter_speed_cutoff_frequency`` is non-zero.
#. If the controller is enabled and no safe operating region violation is active, execute either current-control mode or speed-control mode.
#. Saturate the generated dq-current reference to ``setpoint_limits.i_d_in_A`` and ``setpoint_limits.i_q_in_A``.
#. Run the current controller and transform the resulting dq voltage to the abc-frame with ``theta_el_advanced``.
#. If duty cycles were requested, run SVM with the dq-voltage output, ``v_dc_in_V``, and ``theta_el_advanced``.

When the controller is disabled or a safe operating region violation is active, ``uz_pmsm_control_sample_dq`` resets the internal controller and filter states and returns a zero dq-voltage vector.
In the same condition, ``uz_pmsm_control_sample_duty`` returns ``default_duty_cycle`` from the configuration.
Choose this default value to match the safe state of the inverter hardware.

.. https://mermaid.live/edit#pako:eNqtVttu2zAM_RVDTxuWZM699sOArsWAAuu6pUUfNg-CasmOMVtyZCldevv2Ub7MTuI4xTA_RTyH5CElUXlEvqAMuajf73vcFzyIQtfjlhWTjdDKtVj8y-M56PEgFvf-kkhl3ZybtQVfpu9CSdKldcFTrbLCaD4aSearSHDr5mNtjTC583HE8WltW1e229omEhYSnDB_iSWhOGUSZ8yvcbVkimAWN6PQ3SBRaTptqsqUlneE-wwQUGzwL0lNkCxgkhk4SxmjBpZpshVzhYFUBWWc7rVCP-A0yRIM7VRSxDgjSRozcGzrzudF5W8-cM2ikJM4Ay9QSgynkPLDQ62oh35a_f6HpuvFxQJ_imIFXdupZztIg1dobMYy9LOtCrZl7uPWy8uLlcY6O0o0OQzxDeh5B0nfHutAY9-O9aEQUAc06xzwY0ge8bCGKktnzS2R2jWSIG_kkb06VmkjSpXrmqmvIuKq2b2rBeS4Nqz3Z1rCDiurFL6V42pxWPD031VOq6hl7p3t3fJupxh_ydbn32ouoWuzv21QV5intbmS5uY_5c1KCRz2W7hdQuJLQXVc1NSa5jV8uuos9tjM6rib5VwgvtIk_q_38-8wfHWV9VzrEAyUjKnUnMXyELZN8Rwqu4zXIlYkZHvtr4CcTFcjc8_2Juph4YWbVhvsb_yq8vzQlMcnwLvPSv30lDkLc_WSHDaWigvkwAPSMRYaHpXMtiemI0JOK9OvRoWm_MwMmjWiHgplRJGrpGY9lDCZELNEj8bVQ1BTAgfIhZ-UBUTHykMefwa3lPDvQiSVpxQ6XCI3ABWw0iklip1HBN62mgKbxOSZ0Fwhd3wymudBkPuIfiN3dOIMhuORPXTsyciZncynPbRB7nA4HYztyXg2t2dTAzjPPfSQ57UH84k9nDkTx7Ht4QjceojRCLb8svh3kv9Jef4DY9Lq4Q

.. mermaid::
  :caption: Control flow of uz_pmsm_control_sample

  ---
  config:
    layout: elk
  ---

  flowchart TD

      subgraph Inputs
          direction TB
          i_abc_in_A
          v_abc_in_V
          omega_mech_rad_per_sec
          theta_el
          v_dc_in_V
          i_dc_in_A
          disturbance_input_in_Nm
          reference_speed_in_rpm
          i_dq_ref_A
      end

      subgraph uz_pmsm_control_sample_dq
          direction LR

          uz_signals_saturation_speed["uz_signals_saturation"] --> uz_signals_IIR_Filter_reference_speed["uz_signals_IIR_Filter_sample"] --> uz_speedControl_sample
          uz_speedControl_sample ~~~ plus
          uz_speedControl_sample --> plus(["+"])
          uz_signals_saturation_disturbance["uz_signals_saturation"] --> plus

          plus --> clamping
          clamping --> uz_speedControl_sample

          plus --> uz_signals_saturation_after_speed["uz_signals_saturation"]
          uz_signals_saturation_after_speed --> uz_SetPoint_sample --> OR["Speed/Current Control"]
          OR --> uz_signals_saturation5["uz_signals_saturation"]
          uz_signals_saturation5 --> uz_CurrentControl_sample 
          uz_CurrentControl_sample --> revDQ
          advance --> revDQ
          uz_CurrentControl_sample -->|v_dq_in_V| uz_Space_Vector_Modulation
          advance --> uz_Space_Vector_Modulation
          dq --> uz_CurrentControl_sample
          omega_mech_rad_per_sec --> uz_signals_IIR_Filter_sample_actual_speed["uz_signals_IIR_Filter_sample"] --> uz_speedControl_sample
          v_dc_in_V --> uz_Space_Vector_Modulation
          i_dq_ref_A --> uz_signals_IIR_Filter_dq_setpoint --> OR
          v_abc_in_V --> advance_voltage
          advance_voltage --> dq2
      end

      uz_Space_Vector_Modulation --> duty_cycle
      revDQ --> ref_v_abc_in_V
      i_abc_in_A --> dq
      theta_el --> dq
      theta_el --> advance
      disturbance_input_in_Nm --> uz_signals_saturation_disturbance
      reference_speed_in_rpm --> uz_signals_saturation_speed
      dq2 --> actual.v_abc_in_V



Operating modes
---------------

Current-control mode
====================

Current-control mode is active when ``enable_speed_control`` is ``false``.
The ``reference_currents`` argument of the sample function is used as the :math:`i_d`/:math:`i_q` reference.
The current references are first saturated to ``setpoint_limits.i_d_in_A`` and ``setpoint_limits.i_q_in_A``.
If ``setpoint_filter_i_dq_cutoff_frequency`` is non-zero, both current references are filtered.
The resulting dq-current reference is saturated again before it is passed to the current controller.

Speed-control mode
==================

Speed-control mode is active when ``enable_speed_control`` is ``true``.
It can be selected in the initialization configuration or changed at runtime with ``uz_pmsm_control_enable_speed_control``.
In this mode the ``reference_speed_in_rpm`` argument is used and the ``reference_currents`` argument is ignored.
The speed controller samples the measured mechanical speed in rad/s and the speed reference in rpm.
Its torque output is added to ``disturbance_input_in_Nm``.
The sum is limited by ``setpoint_limits.speed_controller_torque_in_Nm`` and passed to the setpoint module, which calculates the dq-current reference for the selected motor type and field-weakening setting.
If the torque sum would exceed the configured torque limits, the speed controller receives an external clamping signal to support anti-windup behavior.

Safe operating region
---------------------

The safe operating region is checked every time a sample function is called, independent of whether the controller output stage is enabled.
If a violation is detected, the controller output is suppressed until the fault is acknowledged.
The following values are monitored:

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Limit
     - Check
   * - ``i_abc_in_A``
     - Absolute value of each measured phase current against ``upper_bound``.
   * - ``speed_in_rpm``
     - Mechanical speed calculated from ``omega_mech_rad_per_sec`` against lower and upper bounds.
   * - ``v_dc_in_V``
     - Measured DC-link voltage against lower and upper bounds.
   * - ``i_dc_in_A``
     - Measured DC-link current against lower and upper bounds.
   * - ``i_d_in_A``
     - Measured d-current after abc-to-dq transformation against lower and upper bounds.
   * - ``i_q_in_A``
     - Measured q-current after abc-to-dq transformation against lower and upper bounds.

The first sample with an active violation latches a ``uz_pmsm_control_safe_operating_region_violation`` value.
While a violation is latched, later samples do not overwrite it.
If several limits are violated during the same fresh check, the violation checked later in the implementation order is the one stored.
The table above follows the source-level check order.
Use ``uz_pmsm_control_acknowledge_and_reset_error`` to acknowledge the latched fault.
The function stores the supplied measurements, recalculates actual values, clears the violation flag, and immediately checks the safe operating region again.
Therefore, the violation remains active if the supplied measurements are still outside the configured safe operating region.

Configuration
-------------

``uz_pmsm_control_init`` asserts that the PMSM configuration is valid, the sample time is positive, all controller gains and filter cutoff frequencies are non-negative, and every configured upper bound is greater than or equal to its lower bound.
Each instance allocates one current controller, one speed controller, one setpoint module, and the optional filters.
The number of available instances is configured with ``UZ_PMSM_CONTROL_MAX_INSTANCES``.
Important configuration groups:

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Field
     - Purpose
   * - ``setpoint_limits``
     - Limits references and generated setpoints before they enter the control loop.
   * - ``safe_operating_region``
     - Defines runtime fault thresholds for measured and derived actual values.
   * - ``sample_time``
     - Sampling time of the control loop.
   * - ``enable_speed_control``
     - Selects speed-control mode on initialization.
   * - ``*_kp`` and ``*_ki``
     - Initial PI gains for speed, d-current, and q-current controllers.
   * - ``setpoint_filter_i_dq_cutoff_frequency``
     - Optional first-order low-pass filter for current references.
   * - ``setpoint_filter_speed_cutoff_frequency``
     - Optional first-order low-pass filter for speed references.
   * - ``speed_actual_value_filter_cutoff_frequency``
     - Optional first-order low-pass filter for measured mechanical speed.
   * - ``decoupling_method``
     - Selects the current-control decoupling strategy.
   * - ``motor_type`` and ``enable_field_weakening``
     - Configure the setpoint module used in speed-control mode.
   * - ``relative_torque_tolerance``
     - Numerical tolerance for setpoint generation.
   * - ``theta_el_offset``
     - Electrical rotor-angle offset in rad.
   * - ``theta_sampling_compensation``
     - Multiplier for sampling-delay compensation of the measured electrical angle.
   * - ``theta_svm_delay_compensation``
     - Multiplier for advancing the angle used for voltage output and SVM.
   * - ``voltage_theta_shift``
     - Multiplier for shifting the angle used to transform measured phase voltages to dq.
   * - ``default_duty_cycle``
     - Duty cycle returned while the output is disabled or faulted.

Set filter cutoff frequencies to ``0.0f`` to disable the corresponding filter.
Call the sample function with the period configured in ``sample_time``.

Example
-------

The following example configures the controller for current-control mode and requests duty cycles in the control interrupt.
The numerical values are example values and have to be adapted to the machine, inverter, and sampling time.

.. code-block:: c
  :linenos:
  :caption: Initialize PMSM FOC in current-control mode

  #include "uz/uz_pmsm_control/uz_pmsm_control.h"

  static struct uz_PMSM_t machine = {
      .R_ph_Ohm = 0.51f,
      .Ld_Henry = 0.002f,
      .Lq_Henry = 0.002f,
      .Psi_PM_Vs = 0.042f,
      .polePairs = 4.0f,
      .J_kg_m_squared = 0.000108f,
      .I_max_Ampere = 12.0f};

  static struct uz_pmsm_control_configuration_t config = {
      .theta_el_offset = 0.0f,
      .sample_time = 1.0f / 10000.0f,
      .enable_speed_control = false,
      .speed_controller_kp = 0.01f,
      .speed_controller_ki = 0.05f,
      .current_controller_d_kp = 5.8333f,
      .current_controller_d_ki = 1500.0f,
      .current_controller_q_kp = 5.8333f,
      .current_controller_q_ki = 1500.0f,
      .setpoint_limits = {
          .speed_controller_torque_in_Nm = {.upper_bound = 2.0f, .lower_bound = -2.0f},
          .i_d_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
          .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
          .speed_in_rpm = {.upper_bound = 1100.0f, .lower_bound = -1100.0f},
          .disturbance_input_in_Nm = {.upper_bound = 10.0f, .lower_bound = -10.0f}},
      .safe_operating_region = {
          .speed_in_rpm = {.upper_bound = 1500.0f, .lower_bound = -1500.0f},
          .i_d_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
          .i_q_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
          .i_abc_in_A = {.upper_bound = 20.0f, .lower_bound = -20.0f},
          .v_dc_in_V = {.upper_bound = 28.0f, .lower_bound = 12.0f},
          .i_dc_in_A = {.upper_bound = 15.0f, .lower_bound = -1.0f}},
      .decoupling_method = linear_decoupling,
      .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
      .setpoint_filter_speed_cutoff_frequency = 0.0f,
      .motor_type = SMPMSM,
      .enable_field_weakening = false,
      .relative_torque_tolerance = 0.1f,
      .speed_actual_value_filter_cutoff_frequency = 0.0f,
      .theta_sampling_compensation = 0.0f,
      .theta_svm_delay_compensation = 1.5f,
      .voltage_theta_shift = 0.0f,
      .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f}};

  static uz_pmsm_control_t *pmsm_control = NULL;

  void init_control(void) {
      pmsm_control = uz_pmsm_control_init(config, machine);
      uz_pmsm_control_current_control_tune_magnitude_optimum(pmsm_control, 0.5f * config.sample_time);
      uz_pmsm_control_enable(pmsm_control, true);
  }

.. code-block:: c
  :linenos:
  :caption: Sample PMSM FOC in the control interrupt

  void ISR_Control(void) {
      struct uz_pmsm_measurement_values measurements = {
          .i_abc_in_A = {.a = 1.0f, .b = -0.5f, .c = -0.5f},
          .v_abc_in_V = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
          .v_dc_in_V = 24.0f,
          .i_dc_in_A = 0.0f,
          .omega_mech_rad_per_sec = 10.0f,
          .theta_mech = 0.0f};

      uz_3ph_dq_t i_reference_A = {.d = 0.0f, .q = 1.0f, .zero = 0.0f};
      struct uz_DutyCycle_t duty_cycle = uz_pmsm_control_sample_duty(
          pmsm_control,
          measurements,
          0.0f,
          i_reference_A,
          0.0f);
  }

To use speed-control mode, enable the speed loop and pass a speed reference in rpm.
The current-reference argument is ignored in this mode.

.. code-block:: c
  :linenos:
  :caption: Runtime selection of speed-control mode

  uz_pmsm_control_enable_speed_control(pmsm_control, true);

  uz_3ph_dq_t unused_current_reference_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
  struct uz_DutyCycle_t duty_cycle = uz_pmsm_control_sample_duty(
      pmsm_control,
      measurements,
      500.0f,
      unused_current_reference_A,
      0.0f);

Tuning and runtime access
-------------------------

The current-controller tuning helpers wrap the corresponding ``uz_CurrentControl`` tuning functions and can be called after initialization.
The speed- and current-controller gains can also be updated directly with the provided setter functions.
Use ``uz_pmsm_control_get_actual_data``, ``uz_pmsm_control_get_reference_values``, and ``uz_pmsm_control_get_pmsm_measurement_values`` to inspect the stored values.
The returned pointers refer to internal storage and remain owned by the PMSM control instance.
``uz_pmsm_control_set_theta_offset`` changes the electrical angle offset at runtime.
``uz_pmsm_control_get_pointer_to_theta_offset`` returns a direct pointer to the same offset variable, for example for integration with observer or calibration code.

Observability of internal data
------------------------------

Internal data such as actual values, reference values, and measurement values are accessible by pointers, as shown in :numref:`lst_uz_pmsm_internal_data_pointers`.

.. code-block:: c
  :caption: Access to internal PMSM control data pointers
  :name: lst_uz_pmsm_internal_data_pointers

  struct uz_pmsm_actual_data *actual_data = uz_pmsm_control_get_actual_data(pmsm_control);
  struct uz_pmsm_reference_values *reference_values = uz_pmsm_control_get_reference_values(pmsm_control);
  struct uz_pmsm_measurement_values *measurement_values = uz_pmsm_control_get_pmsm_measurement_values(pmsm_control);

The pointers can be used to display the data in the Javascope like so:

.. code-block:: c
  :caption: Display of internal PMSM control data in the Javascope

    js_ch_observable[JSO_dut_iq] = &actual_data->i_dq_in_A.q;

API Reference
-------------

Configuration and data types
============================

.. doxygenenum:: uz_pmsm_control_safe_operating_region_violation

.. doxygenstruct:: uz_limits_t
   :members:

.. doxygenstruct:: uz_pmsm_setpoint_limits_t
   :members:

.. doxygenstruct:: uz_pmsm_safe_operating_region_t
   :members:

.. doxygenstruct:: uz_pmsm_control_configuration_t
   :members:

.. doxygenstruct:: uz_pmsm_measurement_values
   :members:

.. doxygenstruct:: uz_pmsm_actual_data
   :members:

.. doxygenstruct:: uz_pmsm_reference_values
   :members:

Object and functions
====================

.. doxygentypedef:: uz_pmsm_control_t

.. doxygenfunction:: uz_pmsm_control_init

.. doxygenfunction:: uz_pmsm_control_get_actual_data

.. doxygenfunction:: uz_pmsm_control_get_reference_values

.. doxygenfunction:: uz_pmsm_control_get_pmsm_measurement_values

.. doxygenfunction:: uz_pmsm_control_enable

.. doxygenfunction:: uz_pmsm_control_sample_duty

.. doxygenfunction:: uz_pmsm_control_sample_dq

.. doxygenfunction:: uz_pmsm_control_reset

.. doxygenfunction:: uz_pmsm_control_enable_speed_control

.. doxygenfunction:: uz_pmsm_control_acknowledge_and_reset_error

.. doxygenfunction:: uz_pmsm_control_get_safe_operating_area_violation

.. doxygenfunction:: uz_pmsm_control_set_theta_offset

.. doxygenfunction:: uz_pmsm_control_get_pointer_to_theta_offset

.. doxygenfunction:: uz_pmsm_control_current_control_tune_magnitude_optimum

.. doxygenfunction:: uz_pmsm_control_current_control_tune_symmetric_optimum

.. doxygenfunction:: uz_pmsm_control_current_control_tune_bandwidth

.. doxygenfunction:: uz_pmsm_control_current_control_set_Kp_iq

.. doxygenfunction:: uz_pmsm_control_current_control_set_Ki_iq

.. doxygenfunction:: uz_pmsm_control_current_control_set_Kp_id

.. doxygenfunction:: uz_pmsm_control_current_control_set_Ki_id

.. doxygenfunction:: uz_pmsm_control_speed_control_set_Kp_speed

.. doxygenfunction:: uz_pmsm_control_speed_control_set_Ki_speed
