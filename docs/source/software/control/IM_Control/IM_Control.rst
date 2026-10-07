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
* an optional simplified scalar current Kalman filter followed by the Tustin
  rotor-current model,
* scalar U/f operation with frequency ramp, voltage boost and SVM,
* safe-operating-region checks and a latched fault state.

Structure
=========

The implementation is located in ``uz/uz_IM_Control`` and is split into two
modules, each with its own header and implementation:

* ``uz_im_control.c/.h`` owns the current and speed controllers, resonant
  controllers, setpoint filters, U/f generation, SVM, voltage history and SOR.
* ``uz_im_observer.c/.h`` owns the deterministic rotor-flux model, both Kalman
  variants, their states and covariances, both angle PLLs, and the derived
  flux, current, torque and frequency diagnostics.

Machine parameters are passed to ``uz_im_control_init`` using
:ref:`uz_IM_config`; neither module contains machine-specific presets.
IM Control allocates and owns one opaque observer instance. The existing
control configuration, runtime selection functions and diagnostic getters
remain the application interface; JavaScope mappings do not need to change.

.. mermaid::
   :caption: Ownership and call boundary between control and observer

   flowchart TD
       ISR["ISR: measurements and references"] --> Control["uz_im_control_sample_duty"]
       Control --> Observer["uz_im_observer_sample: once per control sample"]
       History["IM Control: applied voltage from k-1"] --> Observer
       Observer --> Results["Flux, dq currents, frequencies, torque and validity"]
       Results --> ControlLoop["IM Control: SOR and U/f or FOC"]
       ControlLoop --> SVM["SVM and duty cycles"]
       SVM --> History
       Observer --> Diagnostics["Read-only states and matrices via control getter"]

The ISR must call only the control sampling API, not additionally sample or
reset its observer. ``uz_im_control_sample_duty`` already invokes the observer
through ``uz_im_control_sample_dq``. A second observer call would advance its
state and PLL twice while the configured sampling time remains unchanged.
Read-only getters do not advance the observer.

The observer input explicitly expects the voltage from the preceding applied
interval together with the current measurement at the current sample. The
one-period delay remains in IM Control, not in the observer. Independent users
of ``uz_im_observer_sample`` must supply this timing themselves; a synchronized
external voltage measurement can be supplied through this observer interface.
This extraction does not change how the control API reconstructs its voltage.

An observer reset clears estimates, covariances, PLLs and angle history, but
does not reset the current/speed controllers or acknowledge a SOR fault.
Changing observer implementation triggers this reset; selecting the same
implementation retains state. A full control reset additionally clears the
controllers and voltage history. Only the control error-acknowledgement API
clears a latched SOR fault. Numerical observer failures are reported to IM
Control, which retains responsibility for latching the fault and returning
the configured default duty cycles.

Both files must be compiled into the application. Static observer allocation
uses ``UZ_IM_CONTROL_MAX_INSTANCES`` and each observer consumes two
``uz_pos_to_speed_pll`` instances, as before the extraction. No additional
observer allocation or initialization is needed in the ISR.

Operation
=========

FOC is the default mode. ``uz_im_control_sample_duty`` executes observation,
speed control when enabled, both current controllers, IM decoupling and SVM.
In U/f mode, the same function ramps the requested stator frequency and
generates the rotating voltage vector internally. Observer diagnostics remain
available in both modes.

The control flow of ``uz_im_control_sample_duty`` is deliberately parallel to
that of :ref:`uz_pmsm_control`: measurements and references are conditioned
first, the selected operating mode generates a voltage reference, and SVM
finally produces the duty cycles. The IM-specific sequence is:

#. Store the measurements and replace ``v_abc_V`` with the reconstructed phase
   voltage that was applied in the preceding control period.
#. Filter the measured rotor speed when the optional actual-speed filter is
   configured.
#. Execute the selected rotor-flux observer from phase current, rotor speed and
   the delayed applied-voltage vector. The observer provides flux magnitude,
   flux angle, dq current, stator frequency and diagnostic values.
#. Check the safe operating region. A disabled controller or a latched
   violation suppresses voltage generation and returns the configured default
   duty cycle.
#. In U/f mode, limit and ramp the frequency reference, calculate voltage
   magnitude and electrical angle, and pass the resulting dq voltage directly
   to SVM. The observer continues running but does not close the U/f loop.
#. In FOC mode, limit and optionally filter speed and dq-current references.
   Current-control mode uses both external dq references. Speed-control mode
   preserves the external d-current reference for magnetization and replaces
   only the q-current reference with the speed-PI output.
#. Force the q-current reference to zero until the rotor-flux estimate is valid,
   then execute both current PIs. Add IM decoupling and optional resonant-control
   voltages and limit the combined voltage vector with
   ``uz_CurrentControl_SpaceVector_Limitation``.
#. Run SVM with the U/f angle or estimated rotor-flux angle. Reconstruct
   ``v_abc_V[k]`` from the resulting duty cycles and DC-link voltage and retain
   it as observer input for period :math:`k+1`.

When the controller is disabled or a safe-operating-region violation is
active, ``uz_im_control_sample_dq`` returns a zero dq-voltage vector and
``uz_im_control_sample_duty`` returns ``default_duty_cycle`` from the
configuration.

.. mermaid::
   :caption: Control flow of uz_im_control_sample_duty

   ---
   config:
     layout: elk
   ---

   flowchart TD

       subgraph Inputs
           direction TB
           i_abc_A
           v_dc_V
           i_dc_A
           rotor_speed_rpm
           rotor_mechanical_angle_rad
           reference_speed_rpm
           i_dq_ref_A
           u_f_frequency_ref_Hz
       end

       subgraph uz_im_control_sample_duty
           direction LR

           previous_voltage["v_abc[k-1]"] --> selected_observer["Selected rotor-flux observer"]
           i_abc_A --> abc_to_alphabeta["abc to alpha/beta"] --> selected_observer
           rotor_speed_filter["uz_signals_IIR_Filter_sample"] --> selected_observer
           selected_observer --> observer_outputs["flux magnitude, flux angle, i_dq, frequencies"]
           observer_outputs --> sor["Safe operating region"]
           sor --> mode{"U/f or FOC"}

           mode -->|U/f| uf_limit_ramp["Frequency saturation and ramp"]
           u_f_frequency_ref_Hz --> uf_limit_ramp
           uf_limit_ramp --> uf_voltage["U/f voltage magnitude and angle"]
           uf_voltage --> svm["uz_Space_Vector_Modulation"]

           mode -->|FOC| foc_path["uz_im_control_sample_dq"]
           reference_speed_rpm --> speed_limit["uz_signals_saturation"] --> speed_ref_filter["uz_signals_IIR_Filter_sample"]
           speed_ref_filter --> speed_or_current{"Speed or current control"}
           rotor_speed_filter --> speed_pi["Speed PI"] --> speed_or_current
           i_dq_ref_A --> current_limit_filter["Saturation and optional dq filter"] --> speed_or_current
           foc_path --> speed_or_current
           speed_or_current --> flux_valid{"rotor_flux_valid"}
           flux_valid -->|invalid: i_q_ref = 0| current_ref_limit["dq-current saturation"]
           flux_valid -->|valid| current_ref_limit
           current_ref_limit --> current_pi["d/q current PIs"]
           observer_outputs --> current_pi
           observer_outputs --> decoupling["IM decoupling"]
           current_ref_limit --> resonant["Optional resonant control"]
           current_pi --> voltage_sum(["+"])
           decoupling --> voltage_sum
           resonant --> voltage_sum
           voltage_sum --> voltage_limit["uz_CurrentControl_SpaceVector_Limitation"]
           v_dc_V --> voltage_limit
           voltage_limit --> svm

           observer_outputs -->|FOC flux angle| svm
           v_dc_V --> svm
           svm --> duty_cycle
           duty_cycle --> reconstruct["Reconstruct and store v_abc[k]"]
           v_dc_V --> reconstruct
           reconstruct --> previous_voltage
       end

       rotor_speed_rpm --> rotor_speed_filter
       rotor_speed_filter --> sor
       i_abc_A --> sor
       i_dc_A --> sor
       v_dc_V --> sor
       rotor_mechanical_angle_rad --> observer_outputs

.. tikz:: Signal flow of the integrated induction-machine controller

   \usetikzlibrary{arrows.meta,positioning,fit,calc,shapes.geometric}
   \begin{tikzpicture}[
      >=Latex,
      node distance=9mm and 13mm,
      block/.style={draw, rounded corners, fill=black!5, align=center,
                    minimum height=8mm, minimum width=22mm},
      choice/.style={draw, diamond, aspect=2.2, fill=blue!7, align=center,
                     inner sep=1.5pt},
      signal/.style={font=\small},
      group/.style={draw, dashed, rounded corners, inner sep=4mm}]
      \node[block] (meas) {measurements\\$i_{abc},\,n_r,\,\theta_r,\,V_{DC}$};
      \node[block, right=of meas] (obs) {selected rotor-flux\\observer};
      \node[block, right=of obs] (park) {flux angle and\\$abc\!\rightarrow\!dq$};
      \node[choice, right=14mm of park] (mode) {mode};

      \node[block, above right=8mm and 14mm of mode] (uf) {U/f ramp, boost\\and rotating vector};
      \node[block, below right=8mm and 14mm of mode] (foc) {speed PI, current PIs,\\decoupling, resonant control};
      \node[block, right=22mm of mode] (limit) {FOC voltage-vector\\limitation};
      \node[block, right=of limit] (svm) {SVM};
      \node[block, right=of svm] (duty) {$D_a,D_b,D_c$};
      \node[block, below=of svm] (delay) {reconstruct and store\\$v_{abc}[k]$};

      \draw[->] (meas) -- (obs);
      \draw[->] (obs) -- node[above,signal] {$\hat\psi_r,\hat\theta_\psi$} (park);
      \draw[->] (park) -- node[above,signal] {$i_{dq}$} (mode);
      \draw[->] (mode) |- node[pos=0.25,left,signal] {U/f} (uf);
      \draw[->] (mode) |- node[pos=0.25,left,signal] {FOC} (foc);
      \draw[->] (uf) -| (svm);
      \draw[->] (foc) -- (limit);
      \draw[->] (limit) -- (svm);
      \draw[->] (svm) -- (duty);
      \draw[->] (duty) |- (delay);
      \draw[->] (delay.west) -| node[pos=0.25,below,signal] {$v_{abc}[k-1]$}
         ($(obs.south)+(0,-2mm)$);
      \node[group, fit=(obs)(park), label=below:{observer and reference frame}] {};
   \end{tikzpicture}

The outer operating mode selects either scalar U/f voltage generation or
rotor-flux-oriented control (FOC). Within FOC, the controller can use an
external dq-current reference or generate the q-current reference with its
speed controller. The modes can be selected at runtime without constructing a
new controller instance.

U/f mode
~~~~~~~~

U/f mode is active when ``uz_im_control_mode_u_f`` is selected with
``uz_im_control_set_mode``. The ``u_f_frequency_reference_Hz`` argument of
``uz_im_control_sample_duty`` is limited to ``u_f_max_frequency_Hz`` and
ramped with ``u_f_frequency_ramp_Hz_per_s``. Positive and negative references
select the direction of the rotating voltage vector. Its magnitude is formed
from ``u_f_ratio_V_per_Hz`` and ``u_f_boost_voltage_V`` and is limited by
``u_f_max_voltage_V`` before SVM generates the duty cycles.

The boost voltage compensates the stator-resistance voltage drop at low
frequency. With an ideal constant U/f ratio, the commanded voltage approaches
zero together with frequency, while the resistive drop
:math:`R_s i_s` remains significant. The voltage available to establish the
air-gap and rotor flux would therefore become too small, causing weak flux,
reduced starting torque or a stalled machine. ``u_f_boost_voltage_V`` adds a
small frequency-independent voltage once the absolute command frequency
exceeds the internal zero-frequency threshold. This maintains usable flux in
the low-speed range. The value must be tuned conservatively: excessive boost
causes over-fluxing, increased magnetizing current and additional machine
heating, particularly close to standstill.

The current and speed controllers do not close a feedback loop in U/f mode.
Nevertheless, the selected observer and all diagnostic calculations continue
to run. This permits observer validation and flux buildup before changing to
FOC. U/f therefore does not require ``rotor_flux_valid`` to generate voltage.

FOC current-control mode
~~~~~~~~~~~~~~~~~~~~~~~~

FOC is active when ``uz_im_control_mode_foc`` is selected and is the mode used
after initialization. Current-control mode within FOC is active when speed
control is disabled. The ``current_reference_dq_A`` argument supplies both
:math:`i_d^*` and :math:`i_q^*`. The references are limited, optionally
filtered and limited again before entering the two PI current controllers.

The d-current reference establishes magnetization. Until the observer reports
a valid rotor flux, the controller retains :math:`i_d^*` but forces
:math:`i_q^*=0` so that no torque-producing current is requested with an
undefined flux angle. Once valid, the current-controller outputs are combined
with IM decoupling and optional resonant-controller voltages. The resulting
vector is limited before SVM.

FOC speed-control mode
~~~~~~~~~~~~~~~~~~~~~~

Speed-control mode is enabled with ``uz_im_control_enable_speed_control`` or
through ``enable_speed_control`` in the initial configuration. The
``reference_speed_rpm`` argument is limited, optionally filtered and compared
with the measured mechanical rotor speed. The speed PI directly generates the
q-current reference. Unlike :ref:`uz_pmsm_control`, no intermediate torque
setpoint or disturbance-torque input is used by the IM module.

The external d-current reference remains active and continues to define the
magnetizing current; only the external q-current reference is replaced by the
speed-controller output. Enabling or disabling speed control resets the speed
PI to prevent reuse of a previous integral state.

Mode transitions and disabled behavior
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Changing between U/f and FOC with ``uz_im_control_set_mode`` resets the current
PIs, speed PI, resonant controllers and reference filters. The selected
observer state and observer PLL are intentionally preserved so FOC can take
over an estimate established during U/f operation. Selecting another observer
is different: it resets the observer diagnostics, covariance and both observer
PLLs.

Disabling the module with ``uz_im_control_enable(control, false)`` performs a
complete controller reset. A latched safe-operating-region violation likewise
suppresses the generated voltage until it is acknowledged and reset.

Resonant current control
~~~~~~~~~~~~~~~~~~~~~~~~

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

Limiting and protection
=======================

Limiting is applied in layers so that references, controller outputs and the
final inverter command remain distinguishable:

* Speed and dq-current references are restricted to ``setpoint_limits`` before
  and after their optional filters.
* The U/f frequency and voltage commands are limited by
  ``u_f_max_frequency_Hz`` and ``u_f_max_voltage_V``.
* In FOC, the complete sum of PI, IM-decoupling and resonant voltages is passed
  through ``uz_CurrentControl_SpaceVector_Limitation``. This limits the vector
  to the linear SVM range and returns a saturation state for PI anti-windup.
* SVM retains its mathematical duty-cycle range from zero to one. IM Control
  does not apply an additional minimum-pulse-width clamp.
* Safe-operating-region checks supervise speed, phase and dq currents, DC-link
  voltage and DC-link current. The first violation is latched and forces the
  configured default duty cycle until it is explicitly acknowledged.
* Slip-frequency limiting, flux-angle-step checking and phase-current-sum
  checking provide additional observer plausibility diagnostics.

The later diagnostic sections describe the exact limits, status fields and SOR
codes. These protection mechanisms are independent of which observer is
selected.

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

FOC voltage and observer plausibility limits
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

Safe-operating-region diagnosis
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``uz_im_actual_data.safe_operating_region_status`` exposes the latched SOR
state as an unsigned integer and can be added directly as a JavaScope variable.
The first detected violation remains visible until
``uz_im_control_acknowledge_and_reset_error`` is called.

.. tikz:: Latched safe-operating-region protection and explicit recovery

   \usetikzlibrary{arrows.meta,positioning,shapes.geometric}
   \begin{tikzpicture}[
      >=Latex,
      node distance=13mm and 17mm,
      block/.style={draw,rounded corners,fill=black!5,align=center,
                    minimum height=10mm,minimum width=29mm},
      decision/.style={draw,diamond,aspect=2.1,fill=blue!7,align=center,
                       inner sep=1.5pt},
      fault/.style={block,fill=red!9}]
      \node[block] (sample) {new measurements};
      \node[decision,right=of sample] (limits) {inside SOR?};
      \node[block,right=of limits] (control) {observer and\\control step};
      \node[block,right=of control] (pwm) {return calculated\\duty cycles};
      \node[fault,below=of limits] (latch) {latch first\\violation code};
      \node[fault,right=of latch] (safe) {return safe default\\duty cycle};
      \node[block,below=of latch] (reset) {acknowledge and\\reset error};

      \draw[->] (sample) -- (limits);
      \draw[->] (limits) -- node[above] {yes} (control);
      \draw[->] (control) -- (pwm);
      \draw[->] (limits) -- node[left] {no} (latch);
      \draw[->] (latch) -- (safe);
      \draw[->] (safe.south) |- node[pos=0.25,right] {subsequent calls} (latch.east);
      \draw[->] (latch) -- node[right] {explicit action} (reset);
      \draw[->] (reset.west) -| node[pos=0.25,left] {fault cleared} (sample.south);
   \end{tikzpicture}

The SOR status is a latch, not a live comparator output. Once a violation is
stored, subsequent calls keep returning the safe default duty cycle even if
the measured value has returned inside its limits. Recovery therefore requires
an explicit acknowledge/reset after the physical cause has been removed.

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

Example
========

The following example configures the controller for FOC current-control mode
and requests duty cycles in the control interrupt. The numerical values are
example values and have to be adapted to the machine, inverter, observer, and
sampling time.

.. code-block:: c
   :linenos:
   :caption: Initialize IM FOC in current-control mode

   #include "uz/uz_IM_Control/uz_im_control.h"

   static uz_IM_t machine = {
       .Rs_Ohm = 2.0f,
       .Rr_Ohm = 1.5f,
       .Lsigma_s_Henry = 0.01f,
       .Lsigma_r_Henry = 0.01f,
       .Lm_Henry = 0.2f,
       .polePairs = 2.0f,
       .J_kg_m_squared = 0.01f,
       .I_max_Ampere = 10.0f,
       .Psi_rated_Vs = 0.5f};

   static struct uz_im_control_configuration_t config = {
       .sample_time_s = 1.0f / 10000.0f,
       .enable_speed_control = false,
       .speed_controller_kp = 0.01f,
       .speed_controller_ki = 0.05f,
       .current_controller_d_kp = 5.0f,
       .current_controller_d_ki = 1500.0f,
       .current_controller_q_kp = 5.0f,
       .current_controller_q_ki = 1500.0f,
       .u_f_ratio_V_per_Hz = 4.0f,
       .u_f_boost_voltage_V = 1.0f,
       .u_f_max_frequency_Hz = 50.0f,
       .u_f_max_voltage_V = 20.0f,
       .u_f_frequency_ramp_Hz_per_s = 5.0f,
       .kalman_process_noise_A2_per_s = 1.0f,
       .kalman_flux_process_noise_Vs2_per_s = 0.01f,
       .kalman_measurement_noise_A2 = 0.01f,
       .observer_pll_kp = 100.0f,
       .observer_pll_ki = 1000.0f,
       .minimum_observer_flux_Vs = 0.001f,
       .maximum_slip_frequency_Hz = 20.0f,
       .maximum_flux_angle_step_rad = 0.5f,
       .maximum_phase_current_sum_A = 1.0f,
       .resonant_gain_d = 0.0f,
       .resonant_gain_q = 0.0f,
       .resonant_harmonic_order = 6.0f,
       .resonant_antiwindup_gain = 0.0f,
       .resonant_voltage_limit_V = 10.0f,
       .setpoint_limits = {
           .speed_controller_torque_in_Nm = {.upper_bound = 2.0f, .lower_bound = -2.0f},
           .i_d_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
           .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
           .speed_in_rpm = {.upper_bound = 1100.0f, .lower_bound = -1100.0f}},
       .safe_operating_region = {
           .speed_in_rpm = {.upper_bound = 1500.0f, .lower_bound = -1500.0f},
           .i_d_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
           .i_q_in_A = {.upper_bound = 10.0f, .lower_bound = -10.0f},
           .i_abc_in_A = {.upper_bound = 20.0f, .lower_bound = -20.0f},
           .v_dc_in_V = {.upper_bound = 28.0f, .lower_bound = 12.0f},
           .i_dc_in_A = {.upper_bound = 15.0f, .lower_bound = -1.0f}},
       .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
       .setpoint_filter_speed_cutoff_frequency = 0.0f,
       .speed_actual_value_filter_cutoff_frequency = 0.0f,
       .enable_resonant_control = false,
       .observer = uz_im_control_observer_rotor_flux_model,
       .default_duty_cycle = {
           .DutyCycle_A = 0.5f,
           .DutyCycle_B = 0.5f,
           .DutyCycle_C = 0.5f}};

   static uz_im_control_t *im_control = NULL;

   void init_control(void) {
       im_control = uz_im_control_init(config, machine);
       uz_im_control_set_mode(im_control, uz_im_control_mode_foc);
       uz_im_control_enable(im_control, true);
   }

.. code-block:: c
   :linenos:
   :caption: Sample IM FOC in the control interrupt

   void ISR_Control(void) {
       struct uz_im_measurement_values measurements = {
           .i_abc_A = {.a = 1.0f, .b = -0.5f, .c = -0.5f},
           .v_abc_V = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
           .v_dc_V = 24.0f,
           .i_dc_A = 0.0f,
           .rotor_speed_rpm = 100.0f,
           .rotor_mechanical_angle_rad = 0.0f};

       uz_3ph_dq_t i_reference_A = {.d = 1.0f, .q = 0.5f, .zero = 0.0f};
       struct uz_DutyCycle_t duty_cycle = uz_im_control_sample_duty(
           im_control,
           measurements,
           0.0f,
           i_reference_A,
           0.0f);
   }

To use speed-control mode, enable the speed loop and pass a speed reference in
rpm. The q-current reference is then generated by the speed controller. The
d-current reference remains active and must provide the required magnetizing
current.

.. code-block:: c
   :linenos:
   :caption: Runtime selection of IM speed-control mode

   uz_im_control_enable_speed_control(im_control, true);

   uz_3ph_dq_t magnetizing_current_reference_A = {
       .d = 1.0f,
       .q = 0.0f,
       .zero = 0.0f};
   struct uz_DutyCycle_t duty_cycle = uz_im_control_sample_duty(
       im_control,
       measurements,
       500.0f,
       magnetizing_current_reference_A,
       0.0f);

Observer and Kalman filters
===========================

The observer and the control law are deliberately separated. The selected
observer supplies the rotor-flux magnitude and angle. The angle defines the
rotor-flux-oriented d/q frame used by FOC and by the diagnostic current
transformation. U/f voltage generation does not require a valid observer, but
the observer is still executed in U/f mode so that its convergence can be
checked before changing to FOC.

Observer selection and common processing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Three observer implementations are integrated. Only the selected observer is
executed; they are not evaluated in parallel. Consequently, a comparison of
the implementations must use repeated operating points or separate runs.
Changing the selection resets all observer states and both PLLs.

.. tikz:: Rotor-flux observer paths and common post-processing

   \usetikzlibrary{arrows.meta,positioning,fit,calc}
   \begin{tikzpicture}[
      >=Latex,
      node distance=10mm and 14mm,
      block/.style={draw, rounded corners, fill=black!5, align=center,
                    minimum height=9mm, minimum width=26mm},
      selected/.style={draw, rounded corners, fill=blue!9, align=center,
                       minimum height=9mm, minimum width=28mm},
      signal/.style={font=\small}]
      \node[block] (iabc) {$i_{abc}[k]$};
      \node[block, below=of iabc] (vabc) {$v_{abc}[k-1]$};
      \node[block, below=of vabc] (speed) {$\omega_{r,el}[k]$};
      \node[block, right=of iabc] (clarke) {Clarke\\transformation};
      \node[selected, above right=12mm and 18mm of clarke] (det)
         {deterministic\\Tustin flux model};
      \node[selected, right=18mm of clarke] (simple)
         {scalar current KFs\\+ Tustin flux model};
      \node[selected, below right=12mm and 18mm of clarke] (kf)
         {four-state motor-model\\Kalman filter};
      \node[block, right=32mm of simple] (select) {observer\\selection};
      \node[block, right=of select] (polar) {$\operatorname{atan2}$, norm\\and $\alpha\beta\!\rightarrow\!dq$};
      \node[block, above=of polar] (pll) {angle PLL};
      \node[block, right=of polar] (valid) {flux validation, slip,\\torque and diagnostics};

      \draw[->] (iabc) -- (clarke);
      \draw[->] (clarke) |- node[pos=0.65,above,signal] {$i_{\alpha\beta}$} (det);
      \draw[->] (clarke) -- node[above,signal] {$i_{\alpha\beta}$} (simple);
      \draw[->] (clarke) |- node[pos=0.65,below,signal] {$i_{\alpha\beta}$} (kf);
      \draw[->] (vabc.east) -| node[pos=0.2,below,signal] {$v_{\alpha\beta}$} (kf.south);
      \draw[->] (speed.east) -| (det.south);
      \draw[->] (speed.east) -| (simple.south);
      \draw[->] (speed.east) -| (kf.south);
      \draw[->] (det) -| (select);
      \draw[->] (simple) -- (select);
      \draw[->] (kf) -| (select);
      \draw[->] (select) -- node[above,signal] {$\hat\psi_{r,\alpha\beta}$} (polar);
      \draw[->] (polar) -- (valid);
      \draw[->] (polar) -- node[right,signal] {$\hat\theta_\psi$} (pll);
      \draw[->] (pll) -| node[pos=0.25,above,signal] {$\hat\omega_s$} (valid.north);
   \end{tikzpicture}

What the three observer choices mean
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The word *Kalman* refers to two substantially different implementations in
this module. The following table summarizes what is estimated and which
current enters the FOC feedback transformation:

.. list-table:: Comparison of the observer paths
   :header-rows: 1
   :widths: 22 24 27 27

   * - Selection
     - Kalman states
     - Rotor-flux source
     - Current used for ``i_dq_A``
   * - ``uz_im_control_observer_rotor_flux_model``
     - None
     - Tustin rotor-current model
     - Directly measured alpha/beta current
   * - ``uz_im_control_observer_filtered_rotor_flux_model``
     - Two independent scalar current estimates
     - Tustin model driven by the filtered currents
     - Scalar-Kalman-filtered alpha/beta current
   * - ``uz_im_control_observer_kalman_rotor_flux_model``
     - Current alpha/beta and rotor-flux alpha/beta
     - Flux states of the four-state motor model
     - Estimated current states of the four-state filter

All three paths finally calculate the flux angle, transform the selected
alpha/beta current into the flux-oriented dq frame and derive stator frequency
through a PLL. Consequently, changing the observer can alter both the FOC
angle **and** its current feedback. A different FOC response after switching
is therefore not necessarily caused by the angle alone.

Deterministic rotor-flux observer
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The deterministic observer uses the rotor-current model in stationary
alpha/beta coordinates. With rotor time constant
:math:`\tau_r=L_r/R_r`, electrical rotor speed :math:`\omega_r` and the
rotation matrix

.. math::

   J=\begin{bmatrix}0&-1\\1&0\end{bmatrix},

the continuous-time model represented by the implementation is

.. math::

   \frac{d\boldsymbol\psi_r}{dt}
   = -\frac{1}{\tau_r}\boldsymbol\psi_r
     +\omega_r J\boldsymbol\psi_r
     +\frac{L_m}{\tau_r}\boldsymbol i_s.

It is discretized with the trapezoidal, or Tustin, rule. Writing
:math:`F=-\tau_r^{-1}I+\omega_rJ`, one control step is

.. math::

   \left(I-\frac{T_s}{2}F\right)\boldsymbol\psi_r[k]
   =\left(I+\frac{T_s}{2}F\right)\boldsymbol\psi_r[k-1]
    +T_s\frac{L_m}{\tau_r}\boldsymbol i_s[k].

The two-by-two system is solved explicitly. A singular or non-finite result
causes ``uz_im_control_observer_violation``. Tustin discretization is used
instead of forward Euler because it provides better numerical damping for the
rotating first-order system at a finite control sample time.

Kalman-filter observers
~~~~~~~~~~~~~~~~~~~~~~~

Two Kalman-based alternatives are available. The full observer estimates
current and rotor flux jointly with the motor model, whereas the simplified
variant filters only the measured alpha/beta currents before applying the
deterministic rotor-current model.

Kalman prediction and correction in one control period
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A Kalman filter repeats two conceptually separate operations:

#. **Prediction:** propagate the previous estimate through a process model.
   The result :math:`\hat x_k^-` is what the machine model expects before the
   new current measurement is considered. Its uncertainty :math:`P_k^-`
   increases by the configured process noise :math:`Q`.
#. **Correction:** compare the measured current with the predicted current.
   This difference is the innovation :math:`\nu_k`. The Kalman gain
   :math:`K_k` determines how strongly the prediction is corrected.

The correction is not a separate controller and does not directly manipulate
the inverter voltage. It changes the estimated current and flux that are used
as FOC feedback. In U/f mode the observer still runs, but the U/f voltage
generation does not depend on its result. U/f operation is therefore the
preferred place to validate convergence before enabling FOC.

The relative size of model and measurement uncertainty determines the filter
behavior:

* Larger :math:`Q` means less trust in the model. The covariance and Kalman
  gain grow, so the estimate follows measured-current changes more quickly.
* Larger :math:`R` means less trust in the measured current. The Kalman gain
  falls, so the estimate becomes smoother but depends more strongly on motor
  parameters, rotor speed and reconstructed voltage.
* Very small :math:`Q` together with large :math:`R` can make a wrong model
  look smooth while its flux angle drifts away from the physical machine.
* Very large :math:`Q` or very small :math:`R` passes more measurement noise
  into the estimated currents and indirectly into the flux correction.

Here, :math:`Q` and :math:`R` are variances, not standard deviations. Their
units are therefore squared units. The configured current and flux process
noise values are continuous-time densities and are multiplied by
``sample_time_s`` once per observer step. The current measurement-noise value
is already the per-sample variance and is not multiplied by the sample time.

Four-state Kalman observer
~~~~~~~~~~~~~~~~~~~~~~~~~~

The Kalman observer estimates
``[i_alpha, i_beta, psi_r_alpha, psi_r_beta]`` from the measured phase
currents, rotor speed and applied stator voltage. The voltage and current must
refer to the same physical interval. A current sample acquired at the start of
control period ``k`` is the response to the voltage that was applied during
period ``k-1``. The observer must therefore use ``v_abc[k-1]`` together with
``i_abc[k]``; using the voltage command calculated later in period ``k`` would
introduce a one-sample timing error.

The state and measurement vectors are

.. math::

   \boldsymbol x=
   \begin{bmatrix}i_\alpha&i_\beta&\psi_{r,\alpha}&\psi_{r,\beta}\end{bmatrix}^{\!T},
   \qquad
   \boldsymbol y=
   \begin{bmatrix}i_\alpha&i_\beta\end{bmatrix}^{\!T},
   \qquad
   H=\begin{bmatrix}1&0&0&0\\0&1&0&0\end{bmatrix}.

The implementation forms an operating-point-dependent discrete transition
matrix :math:`A(\omega_r)` with forward-Euler discretization of the IM state
model. Defining :math:`L_\sigma=\sigma L_s`, its scalar coefficients are

.. math::

   a=-\left(\frac{R_s}{L_\sigma}
      +\frac{L_m^2R_r}{L_\sigma L_r^2}\right),\quad
   b=\frac{L_mR_r}{L_\sigma L_r^2},\quad
   c=\frac{L_m}{L_\sigma L_r},\quad
   d=\frac{L_mR_r}{L_r},\quad e=\frac{R_r}{L_r}.

The resulting matrix used in the code is

.. math::

   A=\begin{bmatrix}
   1+aT_s&0&bT_s&c\omega_rT_s\\
   0&1+aT_s&-c\omega_rT_s&bT_s\\
   dT_s&0&1-eT_s&-\omega_rT_s\\
   0&dT_s&\omega_rT_s&1-eT_s
   \end{bmatrix},
   \qquad
   B\boldsymbol u=
   \frac{T_s}{L_\sigma}
   \begin{bmatrix}v_\alpha&v_\beta&0&0\end{bmatrix}^{\!T}.

Prediction and correction follow the standard discrete Kalman equations:

.. math::

   \hat x_k^- = A_k\hat x_{k-1}+B u_{k-1},\qquad
   P_k^- = A_kP_{k-1}A_k^T+Q,

.. math::

   \nu_k=y_k-H\hat x_k^-,\qquad
   S_k=HP_k^-H^T+R,\qquad
   K_k=P_k^-H^TS_k^{-1},

.. math::

   \hat x_k=\hat x_k^-+K_k\nu_k,\qquad
   P_k=P_k^- - K_kHP_k^-.

Because only currents are measured, the innovation is two-dimensional. The
rotor-flux states are corrected indirectly through the cross-covariances in
:math:`P`. The implementation explicitly inverts the two-by-two innovation
covariance :math:`S`; a singular or non-finite determinant is treated as an
observer violation.

The four states have the following concrete meaning:

.. list-table:: Four-state Kalman vector
   :header-rows: 1
   :widths: 14 28 58

   * - Index
     - State
     - Role
   * - 0
     - :math:`\hat i_\alpha`
     - Predicted and current-corrected stator current used for dq feedback.
   * - 1
     - :math:`\hat i_\beta`
     - Orthogonal stator-current component used for dq feedback.
   * - 2
     - :math:`\hat\psi_{r,\alpha}`
     - Rotor-flux component corrected indirectly through covariance coupling.
   * - 3
     - :math:`\hat\psi_{r,\beta}`
     - Together with state 2, provides flux magnitude and angle.

The measurement matrix observes only states 0 and 1. There is no direct flux
measurement. Flux correction is possible because the prediction creates
non-zero current/flux cross-covariances in :math:`P`; these appear in rows 2
and 3 of :math:`K`. If those gain entries remain close to zero, current
innovations cannot meaningfully correct the flux estimate.

The input voltage is the reconstructed voltage applied during the preceding
PWM period, not the voltage command being calculated in the current call.
Thus a wrong DC-link scaling, phase order, duty-cycle reconstruction or
one-sample alignment directly appears as model error in the full filter.

Simplified current Kalman filter with rotor-flux model
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``uz_im_control_observer_filtered_rotor_flux_model`` preserves the earlier,
computationally inexpensive implementation. It is not a four-state flux
Kalman observer. Instead, two independent scalar Kalman filters smooth the
measured alpha/beta currents before the filtered currents enter the same
Tustin rotor-current model used by the deterministic observer.

For each current axis, the scalar update is

.. math::

   P_k^- = P_{k-1}+Q_iT_s,\qquad
   K_k=\frac{P_k^-}{P_k^-+R},

.. math::

   \nu_k=i_k-\hat i_{k-1},\qquad
   \hat i_k=\hat i_{k-1}+K_k\nu_k,\qquad
   P_k=(1-K_k)P_k^-.

This variant does not use stator voltage, rotor speed or machine parameters
inside the Kalman correction. Rotor speed and machine parameters enter only
the subsequent deterministic flux model. It therefore behaves primarily as
an adaptive current low-pass filter. It is cheaper and less sensitive to an
incorrect reconstructed voltage, but it cannot use the coupled motor model to
correct the flux states and does not provide a full state covariance.

The simplified implementation assumes a random-walk current model,
:math:`\hat i_k^-=\hat i_{k-1}`. It has no voltage-driven current prediction
and no alpha/beta coupling. Its innovation therefore answers only: "How far
is the latest current sample from the filtered current?" It cannot determine
whether that deviation was caused by applied voltage, rotor motion or a model
parameter error. This makes it useful as a robust comparison filter, but it
must not be interpreted as a reduced version of the four-state motor-model
observer.

After reset, both scalar current estimates start at zero and both scalar
covariances start at ``1 A2``. The complete filter likewise starts with zero
state and an identity covariance matrix. The first samples can therefore show
a deliberate initialization transient; ``rotor_flux_valid`` must be checked
before the estimate is allowed to provide FOC feedback.

The default and recommended Kalman implementation is
``uz_im_control_observer_kalman_rotor_flux_model``. The simplified variant is
retained for commissioning and A/B comparison. The purely deterministic
``uz_im_control_observer_rotor_flux_model`` remains available when Kalman
filtering is disabled.

Calling ``uz_im_control_set_observer`` with a different selection clears the
four-state estimate, both covariance representations, deterministic flux
states, innovations, angle history and both PLLs. Runtime applications should
switch at zero frequency or in U/f mode; switching the angle source during
active FOC can otherwise produce an unavoidable transient even with clean
internal resets.

Runtime selection and reset behavior
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The module API selects one of three observer values directly. A testbench GUI
can expose this with two Boolean controls: one enables Kalman processing and a
second chooses the Kalman implementation. The resulting mapping is:

.. list-table:: Recommended two-button mapping
   :header-rows: 1
   :widths: 18 22 60

   * - Kalman enable
     - Simplified mode
     - Selected observer
   * - 0
     - 0 or 1
     - ``uz_im_control_observer_rotor_flux_model``
   * - 1
     - 0
     - ``uz_im_control_observer_kalman_rotor_flux_model`` (default Kalman mode)
   * - 1
     - 1
     - ``uz_im_control_observer_filtered_rotor_flux_model``

.. tikz:: Runtime observer selection controlled by Kalman enable and mode buttons

   \usetikzlibrary{arrows.meta,positioning,shapes.geometric}
   \begin{tikzpicture}[
      >=Latex,
      node distance=22mm and 28mm,
      state/.style={draw,rounded corners,align=center,minimum width=35mm,
                    minimum height=12mm,fill=black!5},
      active/.style={state,fill=blue!10},
      label/.style={align=center,font=\small}]
      \node[state] (det) {deterministic\\Tustin observer};
      \node[active, above right=of det] (full) {full four-state\\Kalman observer};
      \node[active, below right=of det] (simple) {scalar current KFs\\+ Tustin observer};

      \draw[->,bend left=12] (det) to node[label,above left]
         {enable Kalman\\mode = full} (full);
      \draw[->,bend left=12] (full) to node[label,below right]
         {disable Kalman} (det);
      \draw[->,bend right=12] (det) to node[label,below left]
         {enable Kalman\\mode = simplified} (simple);
      \draw[->,bend right=12] (simple) to node[label,above right]
         {disable Kalman} (det);
      \draw[<->] (full) -- node[label,right] {toggle Kalman mode} (simple);
   \end{tikzpicture}

The mode button may be changed while Kalman processing is disabled; this only
changes which Kalman implementation will be activated next. If Kalman is
already enabled, changing the mode immediately calls
``uz_im_control_set_observer`` and therefore performs the complete observer
reset. Enabling Kalman also calls this function and initializes the selected
filter from a defined zero state. Disabling it selects the deterministic
observer and performs the same reset sequence.

The reset deliberately clears

* the four-state Kalman estimate and its :math:`4\times4` covariance,
* both scalar current estimates and scalar covariances,
* deterministic rotor-flux alpha/beta states,
* innovations and derived observer diagnostics,
* both angle PLLs and the previous-angle validity state.

The PI controllers and the U/f frequency state are not reset merely by an
observer selection change. A full controller reset additionally clears these
states. Even though the observer reset is deterministic, changing observers
inside active FOC changes the feedback angle source abruptly. Prefer switching
at zero frequency or while U/f is active, validate ``rotor_flux_valid`` and
only then transfer to FOC.

Observer timing and applied-voltage delay
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. tikz:: Timing of current measurement, observer update and voltage application

   \usetikzlibrary{arrows.meta,positioning,calc}
   \begin{tikzpicture}[>=Latex, x=1.35cm, y=1cm, font=\small]
      \draw[->] (0,0) -- (8.4,0) node[right] {time};
      \foreach \x/\k in {0/{k-1},4/{k},8/{k+1}} {
         \draw (\x,0.12) -- (\x,-0.12) node[below=2mm] {$t_{\k}$};
      }
      \draw[very thick,blue] (0,0.7) -- (4,0.7)
         node[midway,above] {$v_{abc}[k-1]$ physically applied};
      \draw[very thick,blue] (4,0.7) -- (8,0.7)
         node[midway,above] {$v_{abc}[k]$ physically applied};
      \node[draw,rounded corners,fill=black!5,align=center] at (4,1.75)
         {sample $i_{abc}[k]$\\observer uses $v_{abc}[k-1]$};
      \node[draw,rounded corners,fill=black!5,align=center] at (5.8,1.75)
         {calculate $D_{abc}[k]$\\store reconstructed $v_{abc}[k]$};
      \draw[->] (4,1.38) -- (4,0.15);
      \draw[->] (5.8,1.38) -- (5.8,0.75);
   \end{tikzpicture}

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

``measurements.v_abc_V`` represents the phase-voltage measurement consumed by
the observer. In the normal integration it is populated internally with the
reconstructed voltage of the preceding PWM period and is exposed through
``uz_im_control_get_im_measurement_values``. The same member can represent
phase voltages measured by an external measurement box. Such an integration
must explicitly select the external values instead of the internal
reconstruction; the current ``uz_im_control_sample_duty`` path overwrites the
caller-provided value and therefore uses the reconstructed voltage by default.

The duty-cycle reconstruction represents an ideal average inverter. It does
not compensate dead time, semiconductor voltage drops, PWM update delay or a
DC-link change within one PWM period. These deviations can matter at low
voltage or low speed. If real phase-voltage measurements or an inverter
nonlinearity model are used, the application must provide an explicit
configuration or API selection for the voltage source. This keeps the
measurement origin visible and prevents an external sample from being silently
replaced by the reconstruction.

Observer outputs and derived quantities
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For every observer path, flux magnitude and angle are calculated from

.. math::

   |\hat\psi_r|=\sqrt{\hat\psi_{r,\alpha}^2+\hat\psi_{r,\beta}^2},
   \qquad
   \hat\theta_\psi=\operatorname{atan2}
      (\hat\psi_{r,\beta},\hat\psi_{r,\alpha}).

The PLL differentiates the wrapped flux angle while filtering phase error. Its
signed output is retained, so reverse rotation produces a negative stator
frequency. The electrical rotor speed and slip are

.. math::

   \omega_{r,el}=p\frac{2\pi n_r}{60},\qquad
   \omega_{sl}=\hat\omega_s-\omega_{r,el},\qquad
   s[\%]=100\frac{\omega_{sl}}{\hat\omega_s}.

Here, :math:`\hat\omega_s` is the electrical angular velocity of the rotating
stator field (the synchronous speed), not a mechanical speed of the stationary
stator. The mechanical rotor speed is converted to the same electrical domain
with the pole-pair number :math:`p` before both quantities are compared.

In steady-state motoring operation, rotor and stator field rotate in the same
direction and the magnitude of the rotor speed is slightly smaller than the
synchronous speed. Therefore, the normalized slip :math:`s` is positive. This
also applies at no load: the slip approaches zero, but normally remains small
and positive because the machine must still produce torque to compensate
friction, windage, and iron losses. At standstill and nonzero stator frequency,
the normalized slip is approximately :math:`100\,\%`.

The signed slip frequency :math:`\omega_{sl}` must be interpreted together
with the direction of rotation. For example, in reverse motoring operation
:math:`\hat\omega_s=-100\,\mathrm{rad/s}` and
:math:`\omega_{r,el}=-98\,\mathrm{rad/s}` result in
:math:`\omega_{sl}=-2\,\mathrm{rad/s}`, but in a positive normalized motoring
slip of :math:`s=2\,\%`. Thus, a negative *slip frequency* is expected for
reverse motoring and does not indicate generator operation. In generator
operation, the rotor magnitude exceeds the synchronous-field magnitude; the
normalized slip is then negative with this definition. Transients and braking
operation must likewise be assessed using all three signed quantities rather
than the sign of :math:`\omega_{sl}` alone.

Close to zero stator frequency, the implementation sets the slip percentage to
zero to avoid division by a small value. Consequently, the percentage is not a
meaningful diagnostic at or near zero synchronous speed.

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

Practical Kalman tuning order
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Tune the observer only after current offsets, phase order, rotor-speed sign,
machine parameters, DC-link scaling and delayed-voltage timing have been
verified. A recommended sequence is:

#. Run the deterministic observer in U/f mode and verify that flux rotation,
   rotor electrical frequency and stator frequency have consistent signs.
#. Select the full Kalman observer at zero frequency, then repeat identical
   positive and negative U/f plateaus. Do not tune during FOC because a wrong
   estimate then changes the excitation being used to validate it.
#. Start with the configured defaults and log measured currents, states 0/1,
   states 2/3, both innovations, flux magnitude, flux angle and
   ``rotor_flux_valid`` simultaneously as FastData.
#. Correct a persistent innovation mean through sensor-offset, voltage or
   machine-model corrections. Do not hide a non-zero mean by changing noise
   parameters.
#. Adjust the current process-noise density against measurement variance to
   obtain the desired current tracking/noise compromise. Then adjust flux
   process noise only if the current fit is plausible but the flux response is
   too slow or cannot follow repeatable operating-point changes.
#. Enable FOC only after the flux orbit is bounded, the innovations remain
   bounded and approximately zero-mean, the frequency signs agree, and mode
   changes repeatedly produce the same result.

.. list-table:: Effect of Kalman configuration values
   :header-rows: 1
   :widths: 34 33 33

   * - Configuration value
     - Increasing it
     - Typical symptom when excessive
   * - ``kalman_process_noise_A2_per_s``
     - Makes estimated currents react more strongly to measurements.
     - Noisy current states and noisy dq feedback.
   * - ``kalman_flux_process_noise_Vs2_per_s``
     - Allows current innovations to correct flux states more rapidly.
     - Noisy or rapidly moving flux angle and frequency.
   * - ``kalman_measurement_noise_A2``
     - Reduces the correction from measured currents and trusts the model more.
     - Smooth estimate with bias, lag or divergence when the model is wrong.

``uz_im_control_set_kalman_process_noise`` changes only the current-state
process-noise density at runtime, while
``uz_im_control_set_kalman_measurement_noise`` changes the current measurement
variance. The flux process-noise density is currently supplied through the
controller configuration. Changing these values does not reset the current
state or covariance; explicitly switch/reset the observer when a clean A/B
comparison is required.

The deterministic and simplified observer paths share the Tustin rotor-current
model and its PLL. The full four-state Kalman observer owns a separate PLL.
Selecting a different observer resets all observer states and both PLLs,
preventing stale or mutually incompatible internal states from being reused.

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

Observer commissioning and validation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Validate the observer in U/f mode before it is used as the angle source for
FOC. U/f provides a defined rotating voltage command without requiring the
estimated flux angle for feedback. Start with low DC-link voltage and low
frequency, but ensure that voltage boost, dead time and semiconductor voltage
drops do not dominate the requested fundamental voltage.

A useful test sequence contains zero-frequency holds and stationary operating
points in both directions, for example
``0, +2.5, +5, 0, -2.5, -5, 0 Hz``. Change the observer only at zero
frequency and allow it to initialize before applying the next operating point.
Since the module executes only the selected observer, deterministic and Kalman
results must be compared at repeated operating points rather than sample by
sample in the same interval.

Automated three-observer test profile
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``feature/wizard_asm_testing`` application contains an automated 105 s U/f
profile in ``im_observer_validation_profile.csv``. Button 8 starts or stops
the profile. The same seven-point frequency sequence is executed three times.
Each reference point is applied as a zero-order hold for exactly 5 s; the
profile itself does not interpolate or generate ramps between points. The U/f
controller's configured ``u_f_frequency_ramp_Hz_per_s`` nevertheless remains
active and limits the physical command transition. Consequently, the beginning
of each 5 s interval is an intentional settling region rather than a stationary
measurement interval.

.. list-table:: Automated validation blocks
   :header-rows: 1
   :widths: 20 20 60

   * - Profile time
     - ``observer_mode``
     - Observer
   * - 0 <= t < 35 s
     - 0
     - Deterministic Tustin rotor-current model
   * - 35 <= t < 70 s
     - 2
     - Simplified scalar current Kalman filters followed by the Tustin model
   * - 70 <= t < 105 s
     - 1
     - Full four-state current/rotor-flux Kalman observer

Every change of observer occurs at zero frequency and resets all observer
states. ``IM_VALIDATION_OBSERVER_MODE`` is logged independently of
``IM_VALIDATION_PROFILE_STAGE`` so the recorded CSV can be segmented without
depending on hard-coded time limits. The stage values are 0 for inactive, 1
for armed, 2 for zero-frequency initialization, 3 for the positive-frequency
sequence, 4 for the negative-frequency sequence and 5 for the final zero hold.
The analyzer discards the first second of every 5 s plateau by default, which
removes the configured U/f transition and the dominant observer transient from
the evaluated interval. Increase ``--settle-s`` if a commanded transition has
not settled within one second.

JavaScope's default 20-channel selection for this test contains profile time,
observer mode, stage, frequency reference, speed, all phase currents, active
flux magnitude and angle, stator/rotor/slip frequency, both innovations, dq
currents, flux-valid status, flux-angle step and phase-current sum. The active
alpha/beta flux orbit can be reconstructed from magnitude and angle for every
observer path, which makes the three sequential blocks directly comparable.

The accompanying standard-library Python tool evaluates an exported FastData
CSV:

.. code-block:: console

   python vitis/software/Baremetal/src/sw/analyze_im_observer_validation.py \
      Log_YYYY-MM-DD_HH-MM-SS.csv

It writes ``plateau_metrics.csv`` and ``report.md`` to
``im_observer_validation_results``. If Matplotlib is installed it additionally
writes ``overview.png``. Its upper panel compares the estimated stator
frequency, while three separate lower panels show the alpha/beta flux orbit of
the deterministic, full-Kalman and simplified-Kalman modes without overlaying
the orbits. All orbit panels use identical axis limits for direct comparison.
The first second of each stationary plateau is discarded by default; use
``--settle-s`` to change that interval.

The metrics include stator-frequency bias and RMSE, frequency derived from the
flux-angle increment, flux ripple, flux-orbit center and axis ratio, innovation
mean/RMS, phase-current symmetry, current-sum RMS and flux-valid percentage.
These metrics compare repeatability and model consistency. They do not prove
absolute flux or torque accuracy because the testbench does not provide an
independent flux or torque reference. Absolute validation requires an
independent reference measurement or a trusted offline machine model.

Reproducible documentation example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A compact synthetic JavaScope log is supplied as
:download:`im_observer_validation_example.csv <im_observer_validation_example.csv>`.
It contains deterministic, full-Kalman and simplified-Kalman data at
``-2 Hz``, ``+2 Hz`` and ``+6 Hz``. The values are intentionally synthetic:
they demonstrate file parsing, plateau segmentation, metric calculation and
plot generation, but they are not acceptance limits for a physical machine.

Run the example from the repository root:

.. code-block:: console

   python vitis/software/Baremetal/src/sw/analyze_im_observer_validation.py \
      docs/source/software/control/IM_Control/im_observer_validation_example.csv \
      --output-dir im_observer_validation_example_results

The command must detect nine plateau summaries: three frequencies for each of
the three observer modes. It creates ``plateau_metrics.csv`` and ``report.md``;
with Matplotlib installed it also creates ``overview.png`` with one separate
flux-orbit panel per observer mode. All rows must show
``flux_valid_percent = 100``. The generated example is constructed such that
the full Kalman path has the lowest stator-frequency RMSE and the simplified
path has the lowest flux ripple. This provides a quick regression check of the
complete analysis path without requiring testbench hardware.

The input fixture can be regenerated deterministically with:

.. code-block:: console

   python vitis/software/Baremetal/src/sw/generate_im_observer_validation_example.py \
      docs/source/software/control/IM_Control/im_observer_validation_example.csv

For a real measurement, copy the JavaScope CSV instead of the example file and
retain the same channel names. Do not compare the numerical values of a real
machine against the synthetic fixture. Compare the three observers at matching
operating points and use an independent encoder, torque sensor or trusted
machine simulation when absolute estimator accuracy is required.

Recommended fast-data signals are:

.. list-table:: Observer validation signals
   :header-rows: 1
   :widths: 32 68

   * - Signal
     - Purpose
   * - Frequency reference and measured rotor speed
     - Verify operating point, direction and steady-state intervals.
   * - Measured phase currents
     - Check phase sequence, symmetry, current sum and measurement offsets.
   * - ``state[2]`` and ``state[3]``
     - Kalman rotor-flux alpha/beta components for an XY plot.
   * - ``deterministic_flux_alpha_Vs`` and ``deterministic_flux_beta_Vs``
     - Deterministic rotor-flux alpha/beta components for the corresponding XY plot.
   * - Rotor-flux magnitude and angle
     - Detect slow drift, magnitude ripple and angle discontinuities.
   * - Kalman and deterministic stator frequency
     - Compare mean value, ripple and direction at repeated operating points.
   * - Rotor and slip frequency
     - Verify :math:`f_s=f_{r,el}+f_{sl}`.
   * - Kalman innovations
     - Detect bias, periodic model mismatch and divergence.
   * - ``rotor_flux_valid`` and SOR status
     - Correlate invalid feedback or a shutdown with the observer result.

For a stationary operating point, plot
:math:`\hat\psi_{r,\beta}` over :math:`\hat\psi_{r,\alpha}`. With equal axis
scaling, a stable balanced estimate produces a narrow orbit centered close to
the origin. A growing spiral indicates divergence, a shrinking spiral excessive
damping, a displaced orbit an offset and a pronounced ellipse an alpha/beta
scaling or model asymmetry. Include only the stationary part of the plateau;
mixing ramps and holds naturally creates multiple concentric trajectories.

.. tikz:: Qualitative interpretation of stationary rotor-flux XY plots

   \usetikzlibrary{arrows.meta,positioning,calc}
   \begin{tikzpicture}[>=Latex,font=\small,
      panel/.style={draw,rounded corners,minimum width=35mm,minimum height=31mm},
      caption/.style={align=center,text width=35mm}]
      \node[panel] (good) {};
      \node[panel,right=12mm of good] (offset) {};
      \node[panel,right=12mm of offset] (ellipse) {};
      \node[panel,right=12mm of ellipse] (spiral) {};
      \foreach \p in {good,offset,ellipse,spiral} {
         \draw[->,gray] ($ (\p.center)+(-14mm,0) $) -- ($ (\p.center)+(14mm,0) $);
         \draw[->,gray] ($ (\p.center)+(0,-12mm) $) -- ($ (\p.center)+(0,12mm) $);
      }
      \draw[blue,thick] (good.center) circle[radius=9mm];
      \draw[blue,thick] ($ (offset.center)+(5mm,3mm) $) circle[radius=8mm];
      \draw[blue,thick] (ellipse.center) ellipse[x radius=12mm,y radius=6mm];
      \begin{scope}[shift={(spiral.center)}]
         \draw[blue,thick,domain=0:720,samples=120,smooth,variable=\t]
            plot ({\t/720*1.2*cos(\t)},{\t/720*1.0*sin(\t)});
      \end{scope}
      \node[caption,below=3mm of good] {centered orbit:\\stable balanced estimate};
      \node[caption,below=3mm of offset] {offset orbit:\\current or model bias};
      \node[caption,below=3mm of ellipse] {ellipse:\\axis scaling or asymmetry};
      \node[caption,below=3mm of spiral] {growing spiral:\\observer divergence};
   \end{tikzpicture}

The flux-magnitude ripple can be summarized by

.. math::

   r_\psi=\frac{\psi_{max}-\psi_{min}}{\overline{|\psi_r|}}.

The Kalman innovation
:math:`\boldsymbol\nu=[\nu_\alpha,\nu_\beta]^T` should have a mean close to
zero and should not grow with time. Compute its mean, RMS value and maximum
absolute value on every stationary plateau. A strong sinusoidal component at
the electrical frequency means that the filter is stable but repeatedly
corrects a systematic model error. Typical causes are inaccurate machine
parameters, phase-current offsets, incorrect phase order, voltage-vector
scaling, dead-time distortion or a mismatch between the voltage and current
sample intervals.

Do not tune :math:`Q` and :math:`R` before checking units, signs, sample time,
machine parameters and applied-voltage timing. Increasing process noise makes
the estimate follow measurements more rapidly but usually increases estimated
state noise. Increasing measurement noise reduces the current correction and
places more trust in the machine model. The innovations and their covariance
are the appropriate quantities for this tuning; a visually smooth flux alone
does not prove that the model is correct.

SlowData is suitable for status values and stationary summaries, but not for
XY plots, FFTs or transient comparison. Only one SlowData entry is transferred
per control interrupt, so individual entries are time-skewed. Use simultaneous
FastData channels for alpha/beta pairs and innovations.

Configuration and data types
============================

Public structures
~~~~~~~~~~~~~~~~~

After the functional behavior described above, this section provides the
exact public data structures used to configure the controller, supply its
measurements and references, and read back results.

The machine-data type :c:type:`uz_IM_t` and its derived-parameter helpers are
documented once on the :ref:`uz_IM_config` page. They are not repeated here to
avoid duplicate C-domain declarations in Sphinx.

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

``uz_im_observer_diagnostics_t`` contains the complete four-state estimate,
the covariance, innovation covariance, Kalman gain, innovations, deterministic
flux components, simplified filtered currents and their scalar covariances.
The individual members and their interpretation are described in the observer
and validation sections above.

API reference
=============

.. doxygentypedef:: uz_im_control_t

.. doxygenenum:: uz_im_control_mode

.. doxygenenum:: uz_im_control_observer

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

.. doxygenfunction:: uz_im_control_enable_resonant_control
.. doxygenfunction:: uz_im_control_get_observer_diagnostics
.. doxygenfunction:: uz_im_control_set_kalman_process_noise
.. doxygenfunction:: uz_im_control_set_kalman_measurement_noise
.. doxygenfunction:: uz_im_control_set_resonant_parameters
.. doxygenfunction:: uz_im_control_set_minimum_observer_flux

Observer module API
~~~~~~~~~~~~~~~~~~~

These lower-level functions permit independent observer tests or reuse without
PI controllers or SVM. Applications using IM Control should continue using the
control API above. Returned pointers remain owned by the observer; copy results
if a snapshot must survive the next sampling or reset operation.

.. c:struct:: uz_im_observer

   Opaque implementation structure. Its members are private to
   ``uz_im_observer.c``; use the public read-only getters.

.. doxygentypedef:: uz_im_observer_t

.. doxygenstruct:: uz_im_observer_config
   :members:

.. doxygenstruct:: uz_im_observer_input
   :members:

.. doxygenstruct:: uz_im_observer_output
   :members:

.. doxygenstruct:: uz_im_observer_diagnostics_t
   :members:

.. doxygenfunction:: uz_im_observer_init
.. doxygenfunction:: uz_im_observer_sample
.. doxygenfunction:: uz_im_observer_reset
.. doxygenfunction:: uz_im_observer_set_mode
.. doxygenfunction:: uz_im_observer_get_output
.. doxygenfunction:: uz_im_observer_get_diagnostics
.. doxygenfunction:: uz_im_observer_set_process_noise
.. doxygenfunction:: uz_im_observer_set_measurement_noise
.. doxygenfunction:: uz_im_observer_set_minimum_flux

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

``test_uz_im_observer.c`` tests the extracted module independently: the first
Tustin step against its analytic value, scalar process-noise scaling by sample
time, immediate consumption of the supplied previous-interval voltage, mode
selection, reset reproducibility, runtime settings and numerical-failure
recovery. The integration suite compares all observer outputs and diagnostics
against a standalone observer for each of the three modes over repeated
control cycles, including the one-cycle voltage history and its reset.

Run ``ceedling test:uz_im_control`` and ``ceedling test:uz_im_observer`` from
``vitis/software/Baremetal``. These host tests do not replace a timing check and
commissioning test on the target hardware.
