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

The complete implementation is located in ``uz/uz_IM_Control`` and consists
of one public header and one implementation file. Machine parameters are passed
to ``uz_im_control_init`` using :ref:`uz_IM_config`; the control module contains
no machine-specific presets.

Configuration and data types
============================

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
and validation sections below.

Operation
=========

FOC is the default mode. ``uz_im_control_sample_duty`` executes observation,
speed control when enabled, both current controllers, IM decoupling and SVM.
In U/f mode, the same function ramps the requested stator frequency and
generates the rotating voltage vector internally. Observer diagnostics remain
available in both modes.

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

The observer and the control law are deliberately separated. The selected
observer supplies the rotor-flux magnitude and angle. The angle defines the
rotor-flux-oriented d/q frame used by FOC and by the diagnostic current
transformation. U/f voltage generation does not require a valid observer, but
the observer is still executed in U/f mode so that its convergence can be
checked before changing to FOC.

Observer structure
------------------

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

Deterministic rotor-current model
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

The slip percentage is set to zero close to zero stator frequency to avoid a
division by a small value. A negative slip is not inherently an error: its
sign depends on the selected direction conventions and operating quadrant.
Consistency of stator frequency, rotor frequency and slip is more meaningful
than checking the slip sign in isolation.

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

Observer commissioning and validation
=====================================

Validate the observer in U/f mode before it is used as the angle source for
FOC. U/f provides a defined rotating voltage command without requiring the
estimated flux angle for feedback. Start with low DC-link voltage and low
frequency, but ensure that voltage boost, dead time and semiconductor voltage
drops do not dominate the requested fundamental voltage.

A useful test sequence contains zero-frequency holds, slow ramps and stationary
plateaus in both directions, for example
``0, +1, +2, +4, +6, +2, 0, -2, -4, 0 Hz``. Change the observer only at zero
frequency and allow it to initialize before applying the next ramp. Since the
module executes only the selected observer, deterministic and Kalman results
must be compared at repeated operating points rather than sample by sample in
the same interval.

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
      \draw[blue,thick,domain=0:720,samples=120,smooth,variable=\t]
         plot ({\t/720*1.2*cos(\t)},{\t/720*1.0*sin(\t)});
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

The runtime observer and resonant-control functions
``uz_im_control_enable_resonant_control``,
``uz_im_control_get_observer_diagnostics``,
``uz_im_control_set_kalman_process_noise``,
``uz_im_control_set_kalman_measurement_noise``,
``uz_im_control_set_resonant_parameters`` and
``uz_im_control_set_minimum_observer_flux`` are declared in
``uz_im_control.h``. They are listed here as plain C identifiers until the
generated Doxygen XML used by the documentation build contains these newer API
symbols.

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
