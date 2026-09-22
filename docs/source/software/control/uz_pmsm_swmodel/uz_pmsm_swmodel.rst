.. _uz_pmsm_swmodel:

=====================================
PMSM Software Model (uz_pmsm_swmodel)
=====================================

Software model of a PMSM for execution on the processor.

.. warning::
    Aligned the documentation with other PMSM models after https://bitbucket.org/ultrazohm/ultrazohm_sw/pull-requests/546 is merged

.. warning::
    This docs page acts as a test for new concepts such as visualizing data from the unit tests, which we want to test in the online version of the docs.

Example to plot test results
============================

The example scripts in this directory can visualize the results of the PMSM model tests.
Run ``ceedling --mixin=config/csv_export.yml test:test_uz_pmsm_swmodel`` from ``vitis/software/Baremetal`` to generate CSVs under ``vitis/software/Baremetal/build/artifacts/test-data/``; no docs preparation is needed.
The scripts read that location by default, or the directory selected by ``UZ_TEST_DATA_DIR``.
The mixin enables exports without editing the configuration header; ordinary test runs retain ``CEEDLING_GLOBAL_CSV_EXPORT=0`` and do not generate CSVs.
For a disposable end-to-end check, run ``make pyuzlib-smoke-pmsm-plot`` from the repository root.
Embedded plots are currently disabled so documentation builds remain independent of test execution.

.. The plot directives below read CSV files that the ceedling tests write to vitis/software/Baremetal/build/artifacts/test-data/.
   They are disabled because the CI docs build runs `make docs` without running ceedling first, and sphinx treats warnings as errors (-W).
   Only re-enable them with an explicit tests -> artifacts -> docs dependency, using fresh artifacts from the same revision; see the howToDocs guide.

.. .. plot:: software/control/uz_pmsm_swmodel/view_pmsm_model_test_results.py
..     :caption: Result of a test

.. .. plotly:: software/control/uz_pmsm_swmodel/view_pmsm_model_test_results_interactive.py
..     :iframe-width: 100%
..     :iframe-height: 900px

.. Interactive result of the same test.

.. .. bokeh-plot:: software/control/uz_pmsm_swmodel/view_pmsm_model_test_results_bokeh.py
..     :source-position: none

.. Interactive Bokeh result of the same test.


Short-circuit steady-state derivation
=====================================

The software model equations are

.. math::

    v_d = R_s i_d - \omega_e \psi_q,

.. math::

    v_q = R_s i_q + \omega_e \psi_d,

with flux linkages

.. math::

    \psi_d = L_d i_d + \psi_f, \qquad \psi_q = L_q i_q.

These are the steady-state form of the standard PMSM dq voltage equations (:math:`\dot{i}_d=\dot{i}_q=0`).
For a short circuit at constant speed, set

.. math::

    v_d = 0, \qquad v_q = 0.

Then

.. math::

    R_s i_d = \omega_e L_q i_q,

.. math::

    R_s i_q = -\omega_e (L_d i_d + \psi_f).

Insert :math:`i_d = (\omega_e L_q / R_s) i_q` into the second equation:

.. math::

    i_q = -\frac{\omega_e \psi_f / R_s}{1 + \omega_e^2 L_d L_q / R_s^2},

.. math::

    i_d = \frac{\omega_e L_q}{R_s} i_q.

For :math:`L_d = L_q = L`, this becomes

.. math::

    i_q = -\frac{\omega_e \psi_f R_s}{R_s^2 + (\omega_e L)^2},

.. math::

    i_d = -\frac{\omega_e^2 L \psi_f}{R_s^2 + (\omega_e L)^2}.

Integration method and oversampling
===================================

The model integrates the dq electrical ODE with a selectable method, set via the ``integration_method`` field of :c:struct:`uz_pmsm_swmodel_config_t`.

* ``uz_pmsm_swmodel_euler_forward`` -- explicit Euler (1st order, default).
* ``uz_pmsm_swmodel_heun`` -- Heun's method (explicit trapezoidal rule, 2nd order), see :ref:`uz_integrator <uz_integrator>` (``Heun's method``).

Choosing a sample time
----------------------

Each call to ``uz_pmsm_swmodel_step`` advances the model by the configured ``sample_time``; the model does not perform internal oversampling or adjust the step size automatically.
To oversample a controller, call the model multiple times per control period and hold the applied voltage constant between control updates (zero-order hold).
When mechanical simulation is disabled, the supplied speed can also be held constant between control updates.
When mechanical simulation is enabled, speed is an internal state and evolves at every model step.
Recording each substep gives a denser output trajectory, but smooth plots alone do not establish numerical accuracy.

A common question is whether forward Euler is even valid here, since within one control period the current changes, which changes the flux :math:`\psi_d = L_d i_d + \psi_{pm},\; \psi_q = L_q i_q`, which changes the derivative, and so on.
Forward Euler does **not** ignore this coupling -- it resolves it *across* substeps: every oversampling substep recomputes :math:`\psi(i)` from the current state and forms a fresh derivative, so the next substep already sees the updated flux.
What forward Euler approximates is only the variation *within* a single substep: it freezes the start-of-substep derivative and applies it across the whole substep.
For smooth dynamics, its local truncation error is :math:`\mathcal{O}(T_s^2)` and its global error is first order in :math:`T_s`.
The required step size depends on the electrical time constants, speed-dependent dq coupling, and any simulated mechanical dynamics.
Choose a step that satisfies the method's stability requirements and check convergence by reducing ``sample_time`` while keeping the simulated input timing unchanged.

Heun's method attacks the within-step approximation directly: it evaluates the derivative at the start **and** at the Euler-predicted end of the step (re-evaluating :math:`\psi(i)` at the predicted current) and averages the two.
For smooth dynamics, it has second-order global accuracy and may achieve the same accuracy with fewer substeps.
It is still an explicit method with stability limits, so a larger step must be checked for the machine parameters and operating conditions in use.

Integrator state: current or flux
=================================

The ``integrator_state`` field of :c:struct:`uz_pmsm_swmodel_config_t` selects which electrical quantity is integrated:

* ``uz_pmsm_swmodel_integrator_state_current`` (default) integrates the dq **currents** and derives the flux algebraically, :math:`\psi_d = L_d i_d + \psi_f,\; \psi_q = L_q i_q`.
* ``uz_pmsm_swmodel_integrator_state_flux`` integrates the dq **flux linkages** and derives the current, :math:`i_d = (\psi_d - \psi_f)/L_d,\; i_q = \psi_q/L_q`.
  This matches the FPGA reference :ref:`uz_pmsmModel`.

Both share the voltage balance :math:`e_d = v_d - R_s i_d + \omega_e \psi_q`, :math:`e_q = v_q - R_s i_q - \omega_e \psi_d`; the current formulation integrates :math:`e/L`, the flux formulation integrates :math:`e`.
For a linear machine (constant :math:`L_d, L_q`) and equivalent initial conditions, the two formulations produce the same trajectory up to floating-point rounding.
Both formulations currently use the scalar inductances and permanent-magnet flux linkage; selecting flux integration does not enable nonlinear flux-map lookups.

For the flux formulation the reset value of the d-axis flux state matters, because the derived current is :math:`i_d = (\psi_d - \psi_f)/L_d`.
By default the integrator state resets to zero, which starts the machine at :math:`i_d = -\psi_f/L_d`.
Setting ``preload_flux_state = true`` instead preloads the d-axis flux state with :math:`\psi_f` on reset, so the machine starts from zero current (matching the current formulation).
The flag has no effect when ``integrator_state`` is current.

Mechanical model
================

By default the model is electrical only and the rotor speed :math:`\omega_{mech}` is an input that is passed straight through to the output.
In this mode ``load_torque`` does not affect the speed output.
Setting ``simulate_mechanical_system = true`` makes the model integrate the speed from the torque balance instead (the input speed is then ignored and :math:`\omega_{mech}` starts at zero; use :c:func:`uz_pmsm_swmodel_reset` to re-zero it), matching :ref:`uz_pmsmModel`:

.. math::

    \frac{d \omega_{mech}}{dt} = \frac{M_i - M_F - T_L}{J}, \qquad
    M_i = \tfrac{3}{2} p (\psi_d i_q - \psi_q i_d),

with Coulomb plus viscous friction

.. math::

    M_F = \operatorname{sign}(\omega_{mech})\,(M_{R0} + \mu\,|\omega_{mech}|).

The inertia :math:`J` is taken from ``pmsm_parameters.J_kg_m_squared``; the friction constants :math:`M_{R0}` and :math:`\mu` are the ``coulomb_friction_constant`` and ``friction_coefficient`` config fields, and the load torque :math:`T_L` is the ``load_torque`` model input.
Both friction constants must be nonnegative; zero is valid for friction-free simulations.
The mechanical state is integrated with the same selected ``integration_method`` (Euler or Heun) as the electrical state, as one coupled system.

Software reference
==================

.. doxygentypedef:: uz_pmsm_swmodel_t

.. doxygenenum:: uz_pmsm_swmodel_integration_method_t

.. doxygenenum:: uz_pmsm_swmodel_integrator_state_t

.. doxygenstruct:: uz_pmsm_swmodel_config_t
  :members:

.. doxygenstruct:: uz_pmsm_swmodel_outputs_t
  :members:

.. doxygenstruct:: uz_pmsm_swmodel_inputs_t
  :members:

.. doxygenfunction:: uz_pmsm_swmodel_init

.. doxygenfunction:: uz_pmsm_swmodel_step

.. doxygenfunction:: uz_pmsm_swmodel_reset
