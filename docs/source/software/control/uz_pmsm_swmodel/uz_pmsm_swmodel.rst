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

The following plots are different examples to show the results of a unit test in the documentation.


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

These are the steady-state form of the standard PMSM dq voltage equations
(:math:`\dot{i}_d=\dot{i}_q=0`).
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

The model integrates the dq current ODE with a selectable method, set via the ``integration_method`` field of :cpp:struct:`uz_pmsm_swmodel_config_t`:

* ``uz_pmsm_swmodel_euler_forward`` -- explicit Euler (1st order, default).
* ``uz_pmsm_swmodel_heun`` -- Heun's method (explicit trapezoidal rule, 2nd order), see :ref:`uz_integrator <uz_integrator>` (``Heun's method``).

Why oversampling produces smooth *and* accurate output
------------------------------------------------------

When the model is driven from a controller, the controller input (the applied voltage :math:`\boldsymbol{v}_{dq}` and the speed :math:`\omega`) is held constant between control updates (zero-order hold).
"Smooth" output is then simply a matter of **output-point density**: the model is stepped many times (oversampled) per control period, so the plotted current trajectory is sampled finely while the input stays constant.

A common question is whether forward Euler is even valid here, since within one control period the current changes, which changes the flux :math:`\psi_d = L_d i_d + \psi_{pm},\; \psi_q = L_q i_q`, which changes the derivative, and so on.
Forward Euler does **not** ignore this coupling -- it resolves it *across* substeps: every oversampling substep recomputes :math:`\psi(i)` from the current state and forms a fresh derivative, so the next substep already sees the updated flux.
What forward Euler approximates is only the variation *within* a single substep: it freezes the start-of-substep derivative and applies it across the whole substep.
Its local truncation error is :math:`\mathcal{O}(T_s^2\,\ddot{y})`, so a small substep :math:`T_s` (i.e. a high oversampling factor relative to the electrical time constant :math:`L/R`) drives that residual to zero.
That is why fine-step Euler is both accurate and smooth.

Heun's method attacks the within-step approximation directly: it evaluates the derivative at the start **and** at the Euler-predicted end of the step (re-evaluating :math:`\psi(i)` at the predicted current) and averages the two.
It therefore captures the within-step current/flux change to 2nd order, achieving comparable accuracy at a much larger step -- i.e. with much less oversampling.

Software reference
==================

.. doxygentypedef:: uz_pmsm_swmodel_t

.. doxygenstruct:: uz_pmsm_swmodel_config_t
  :members:

.. doxygenstruct:: uz_pmsm_swmodel_outputs_t
  :members:

.. doxygenstruct:: uz_pmsm_swmodel_inputs_t
  :members:

.. doxygenfunction:: uz_pmsm_swmodel_init

.. doxygenfunction:: uz_pmsm_swmodel_step

.. doxygenfunction:: uz_pmsm_swmodel_reset
