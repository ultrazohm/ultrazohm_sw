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
