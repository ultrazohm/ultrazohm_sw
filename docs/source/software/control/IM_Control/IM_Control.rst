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
* two optional resonant current controllers for periodic d/q-current errors,
* a Tustin-discretized rotor-current-model flux observer,
* a four-state Kalman observer for alpha/beta current and rotor flux,
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

.. doxygenstruct:: uz_im_observer_diagnostics_t
   :members:

Operation
=========

FOC is the default mode. ``uz_im_control_sample_duty`` executes observation,
speed control when enabled, both current controllers, IM decoupling and SVM.
In U/f mode, the same function ramps the requested stator frequency and
generates the rotating voltage vector internally. Observer diagnostics remain
available in both modes.

Observer structure
------------------

The Kalman observer estimates
``[i_alpha, i_beta, psi_r_alpha, psi_r_beta]`` from the measured phase
currents, rotor speed and applied stator voltage. The voltage and current must
refer to the same physical interval. A current sample acquired at the start of
control period ``k`` is the response to the voltage that was applied during
period ``k-1``. The observer must therefore use ``v_abc[k-1]`` together with
``i_abc[k]``; using the voltage command calculated later in period ``k`` would
introduce a one-sample timing error.

The complete sequence performed by ``uz_im_control_sample_duty`` is:

#. acquire and pass the current and rotor-speed measurements for period ``k``;
#. execute the observer with the internally stored ``v_abc[k-1]``;
#. execute U/f or FOC and calculate the new duty cycles ``D_abc[k]``;
#. reconstruct the average inverter pole voltages using the DC-link voltage
   sampled in the same call;
#. store this reconstructed vector for the observer call in period ``k+1``.

The reconstruction is

.. math::

   v_a[k] = D_a[k] V_{DC}[k], \qquad
   v_b[k] = D_b[k] V_{DC}[k], \qquad
   v_c[k] = D_c[k] V_{DC}[k].

These are pole voltages and may contain a common-mode component. This does not
affect the machine model because the subsequent Clarke transformation removes
it. For example, ``D_a = D_b = D_c = 0.5`` produces three pole voltages of
``V_DC/2``, but still results in

.. math::

   v_\alpha = \frac{2}{3}v_a-\frac{1}{3}v_b-\frac{1}{3}v_c=0,
   \qquad
   v_\beta = \frac{v_b-v_c}{\sqrt{3}}=0.

The opaque control instance owns the delayed voltage vector. Initialization,
disabling the controller and resetting an error clear it. Consequently, the
first observer execution after such an event intentionally uses a zero-voltage
vector. No additional delay state is required in the ISR or application.

When the lower-level ``uz_im_control_sample_dq`` API is used directly, no duty
cycles are available. In that case the module assumes that the returned dq
voltage command is applied without an additional modification. It transforms
that command back to abc and stores it for the next call. Applications that
apply another saturation, modulation or voltage modification after
``uz_im_control_sample_dq`` should instead use ``uz_im_control_sample_duty`` or
extend the API with explicit applied-voltage feedback.

Compatibility and modeling assumptions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This internal delay does not change the U/f or FOC command-generation chain,
the SVM result, PI states, reference filters or safe-operating-region checks.
It only changes the source and ownership of the Kalman observer's voltage
input. It also restores the timing convention of the original commissioning
observer, where the previously applied inverter voltage was paired with the
new current sample.

There is one intentional API-semantic change: caller-provided
``measurements.v_abc_V`` is overwritten and is no longer used as the observer
input. Code that previously supplied physically measured phase voltages through
this member will no longer influence the observer. In this repository no such
caller existed when the change was introduced. The member remains in the
structure for source compatibility and exposes the internally selected voltage
through ``uz_im_control_get_im_measurement_values``.

The duty-cycle reconstruction represents an ideal average inverter. It does
not compensate dead time, semiconductor voltage drops, PWM update delay or a
DC-link change within one PWM period. These deviations can matter at low
voltage or low speed. If real phase-voltage measurements or an inverter
nonlinearity model become available, an explicit configuration or API
selection should be added rather than silently writing
``measurements.v_abc_V``.

Duty-cycle range
~~~~~~~~~~~~~~~~

IM Control does not add a minimum-pulse-width clamp in either U/f or FOC mode.
Generated duty cycles retain the general SVM module's mathematical saturation
to the interval zero to one, so both modes can return exactly zero or one. A
configured default duty cycle returned while disabled or faulted is likewise
passed through unchanged.

If the PWM IP applies an additional hardware minimum-pulse-width clamp, that
modification is not represented by the internally reconstructed observer
voltage. An explicit applied-voltage or applied-duty feedback path should be
added if this difference becomes relevant for observer accuracy.

Kalman process-noise convention
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The two process-noise configuration values are continuous-time noise
densities, not covariance increments per ISR call. The module converts them to
the diagonal discrete-time covariance entries on every observer step:

.. math::

   Q_i = \mathtt{kalman\_process\_noise\_A2\_per\_s}\,T_s,
   \qquad
   Q_\psi = \mathtt{kalman\_flux\_process\_noise\_Vs2\_per\_s}\,T_s.

For example, with ``T_s = 100 us``, a current-state density of ``0.1 A2/s``
produces ``Q_i = 1e-5 A2`` per step, while a flux-state density of
``1e-3 Vs2/s`` produces ``Q_psi = 1e-7 Vs2`` per step. This is numerically
equivalent to the default per-step values in the original commissioning
observer. When the sample time changes, keeping the density constant preserves
the intended continuous-time tuning; copying an old per-step Q value directly
into these fields does not.

The state transition uses the configured IM parameters and rotor electrical
speed. Separate current and flux process-noise densities and the current
measurement variance configure the covariance update.

The alternative ``uz_im_control_observer_rotor_flux_model`` implements the
same rotor-current model with Tustin discretization. Each observer owns a PLL
which derives stator frequency from the estimated flux angle. Selecting a
different observer resets both observer states and PLLs, avoiding a transient
caused by incompatible internal states.

``uz_im_control_get_observer_diagnostics`` provides read-only access to all
four Kalman states, the complete covariance, innovation covariance, Kalman
gain, innovations and both deterministic flux states. The normal control
signals remain available through ``uz_im_control_get_actual_data``.

``actual_data.rotor_flux_valid`` is one only when the flux magnitude is finite
and exceeds ``minimum_observer_flux_Vs``. While it is zero, the observer's dq
current feedback and estimated electrical torque are forced to zero, torque
production is inhibited and only the commanded d-axis magnetizing-current
startup remains active. The estimated torque is exposed as
``actual_data.estimated_electrical_torque_Nm`` and is calculated as

.. math::

   \hat T_e = \frac{3}{2}p\frac{L_m}{L_r}|\hat\psi_r|\hat i_q.

An invalid numerical observer result latches
``uz_im_control_observer_violation`` in the same way as every other SOR error.
The module returns a safe clamped default duty cycle until
``uz_im_control_acknowledge_and_reset_error`` clears the error and resets the
observer state. It does not silently restart the observer while the system is
running.

Changing between U/f and FOC preserves the flux-observer state for a smooth
takeover while resetting the PI, resonant and setpoint-filter states. During
FOC startup the d-axis magnetizing-current reference remains active, but the
q-axis torque reference and decoupling terms are held at zero until the
estimated rotor flux exceeds ``minimum_observer_flux_Vs``.

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

Additional plausibility and limiting
------------------------------------

``maximum_slip_frequency_Hz`` limits the absolute estimated slip frequency.
``maximum_flux_angle_step_rad`` checks the wrapped observer-angle increment per
control step, while ``maximum_phase_current_sum_A`` checks the residual
``abs(i_a + i_b + i_c)``. These checks are exposed as diagnostics and do not
create additional latched SOR codes.

In every FOC control step, the complete voltage vector (PI, IM decoupling and
resonant contributions) is unconditionally passed through
``uz_CurrentControl_SpaceVector_Limitation``. This limits the vector to the
linear SVM range ``V_dc / sqrt(3)`` and applies the Current Control module's
95-percent reserve to the prioritized d or q axis when saturation is active.
The priority depends on the signs of electrical speed and q-current reference,
matching ``uz_CurrentControl``. The current-controller integrators receive the
resulting saturation state as external clamping for anti-windup in the next
control step. This path is used only in FOC; U/f does not use the Current
Control voltage-vector limitation.

There is deliberately no enable flag for this behavior: both d- and q-axis
current control always use the limiter. Their individual PI outputs retain the
additional static bounds ``+/-safe_operating_region.v_dc_in_V.upper_bound``.
The normally tighter final vector saturation drives the shared external
anti-windup signal. The complete ``uz_CurrentControl``
object is not instantiated because it is parameterized with ``uz_PMSM_t`` and
contains PMSM-specific decoupling. IM Control instead reuses its common
space-vector-limitation component after adding the IM-specific decoupling and
optional resonant voltage. This placement ensures that every contribution is
included in the final limit.

The corresponding fields in ``uz_im_actual_data`` are
``rotor_flux_valid``, ``slip_frequency_limited``,
``flux_angle_step_violation``, ``phase_current_sum_violation`` and
``voltage_vector_saturated``. Their associated continuous diagnostic values
are also available for detailed debugging.

Resonant current control
------------------------

The module always initializes one resonant controller per d/q axis. Set
``enable_resonant_control`` to enable their voltage contribution initially or
use ``uz_im_control_enable_resonant_control`` at runtime. A change of the enable
state resets both controller states. ``resonant_gain_d``, ``resonant_gain_q``,
``resonant_harmonic_order``, ``resonant_antiwindup_gain`` and
``resonant_voltage_limit_V`` configure the controllers. Their combined output
is exposed as ``actual_data.resonant_voltage_dq_V`` and is added to the PI and
decoupling voltages.

Each IM-control instance consumes two resonant-controller instances. Therefore
``UZ_RESONANT_CONTROLLER_MAX_INSTANCES`` must be at least twice
``UZ_IM_CONTROL_MAX_INSTANCES`` when IM Control is enabled.
It also consumes two ``uz_pos_to_speed_pll`` instances, so
``UZ_POS_TO_SPEED_PLL_MAX_INSTANCES`` must satisfy the same relationship.

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
.. doxygenfunction:: uz_im_control_enable_resonant_control
.. doxygenfunction:: uz_im_control_sample_duty
.. doxygenfunction:: uz_im_control_sample_dq
.. doxygenfunction:: uz_im_control_reset
.. doxygenfunction:: uz_im_control_get_actual_data
.. doxygenfunction:: uz_im_control_get_reference_values
.. doxygenfunction:: uz_im_control_get_im_measurement_values
.. doxygenfunction:: uz_im_control_get_observer_diagnostics
.. doxygenfunction:: uz_im_control_get_safe_operating_area_violation
.. doxygenfunction:: uz_im_control_acknowledge_and_reset_error
.. doxygenfunction:: uz_im_control_current_control_set_Kp_id
.. doxygenfunction:: uz_im_control_current_control_set_Ki_id
.. doxygenfunction:: uz_im_control_current_control_set_Kp_iq
.. doxygenfunction:: uz_im_control_current_control_set_Ki_iq
.. doxygenfunction:: uz_im_control_speed_control_set_Kp_speed
.. doxygenfunction:: uz_im_control_speed_control_set_Ki_speed
.. doxygenfunction:: uz_im_control_set_kalman_process_noise
.. doxygenfunction:: uz_im_control_set_kalman_measurement_noise
.. doxygenfunction:: uz_im_control_set_resonant_parameters
.. doxygenfunction:: uz_im_control_set_minimum_observer_flux

Tests
=====

Unit tests are located in ``test/uz/uz_IM_Control`` and cover initialization,
configuration validation, setpoint limiting, disabled output, fault latching
and U/f operation. They also verify FOC startup without valid flux, phase-current
sum diagnosis, final voltage-vector limiting and observer-state preservation
during mode changes. Observer-specific tests additionally cover the complete
four-state diagnostics, covariance and gain matrices, observer switching and
the Tustin rotor-flux model. They also verify the unmodified default-duty
range, zero dq feedback and zero torque while
the rotor-flux estimate is invalid, and finite torque diagnostics during
Kalman operation.
