.. _pyuzlib:

=======
pyuzlib
=======

``pyuzlib`` is a small Python helper library for documentation and data-processing tasks in the UltraZohm repository.

The package provides PMSM data helpers for scalar machine parameters, flux-map CSV files, fitting routines, plotting, and CSV export.
The CSV files it operates on are the motor datasets of the :ref:`uz_pmsm` motor database; see that page for the canonical file formats and the workflow for adding a new motor.

Installation
============

Inside the repository, install the package in editable mode:

.. code-block:: bash

	python -m pip install -e ./pyuzlib

For development and unit tests, install ``'./pyuzlib[dev]'`` instead; the extra adds pytest and Ruff.
From the repository root, ``make pyuzlib-test`` runs the Python tests.
Installing Bokeh additionally enables the optional Bokeh docs reader test.
``make pyuzlib-smoke-pmsm-plot`` runs a separate end-to-end check using real C exports and a headless Matplotlib plot.
This command also requires Ceedling and a host C compiler, and uses temporary build/output directories without modifying the tracked configuration header.

Flux-map and differential-inductance CSV readers first resolve relative paths against the current working directory.
If the file is absent there and pyuzlib lives in a repository checkout, they also try the repository root, discovered by its directory markers rather than a fixed parent depth.
Absolute paths are used directly.
Outside a checkout, these readers support absolute and working-directory-relative files; they do not search arbitrary installation directories.
This does not make the repository-dependent catalog generation commands standalone.

Public API
==========

The package root exposes the ``pmsm``, ``docs``, and ``machine_catalog`` namespaces:

.. code-block:: python

	import pyuzlib

	print(pyuzlib.__version__)
	motor = pyuzlib.pmsm.PMSM()
	pyuzlib.docs.pmsm.plot_flux_map(...)

PMSM Workflow
=============

The object-oriented PMSM API keeps scalar machine parameters, flux maps, fitting results, and export routines together:

.. code-block:: python

	import pyuzlib

	motor = pyuzlib.pmsm.PMSM()
	motor.load_parameters_csv(
	    "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/machine_parameters.csv"
	)
	motor.load_flux_map_csv(
	    "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
	)

	fit = motor.fit_linear_flux_model()
	motor.export_result_csv("linear_no_saturation", "linear_flux_fit.csv")

The same object can calculate and plot a linear PMSM operation area from the scalar machine parameters:

.. code-block:: python

	import numpy as np

	operation_area = motor.calculate_operation_area(
	    v_dc_V=24.0,
	    speed_rpm=1000.0,
	    grid_points=40,
	    speeds_rpm=np.linspace(0.0, 1500.0, 6),
	)
	motor.plot_operation_area(operation_area)
	motor.plot_max_torque_curve(operation_area.max_torque)

The flux-map importer accepts custom column names and normalizes the data internally to ``i_d_A``, ``i_q_A``, ``psi_d_Vs``, and ``psi_q_Vs``:

.. code-block:: python

	motor.load_flux_map_csv(
	    "flux_map.csv",
	    i_d_col="Id",
	    i_q_col="Iq",
	    psi_d_col="PsiD",
	    psi_q_col="PsiQ",
	)

``PMSMParameters`` stores all 20 C-compatible fields of ``uz_PMSM_t``: ``machine_id``, the physical parameters (``R_ph_Ohm``, ``Ld_Henry``, ``Lq_Henry``, ``Psi_PM_Vs``, ``polePairs``, ``J_kg_m_squared``), and the rating and limit values (``I_max_Ampere``, ``I_rated_Ampere``, ``Torque_rated_Nm``, ``Torque_max_Nm``, ``Torque_min_Nm``, ``speed_rated_rpm``, ``speed_max_rpm``, ``speed_min_rpm``, ``V_dc_nominal_V``, ``I_d_max_A``, ``I_d_min_A``, ``I_q_max_A``, ``I_q_min_A``).
Additional scalar values from parameter CSV files (e.g. ``machine_name``) are preserved separately in ``additional_parameters`` for documentation and controller workflows.

PMSM API overview
=================

The ``pyuzlib.pmsm.PMSM`` class bundles the whole workflow.
Besides the methods shown above it provides:

* ``update_parameters(**values)`` — update C fields or additional parameters in place.
* ``get_flux_map(name)`` — access a loaded flux map as a ``FluxMap`` object.
* ``compare_linear_flux_model(fit_name="Linear Fit")`` / ``plot_linear_flux_model_comparison(fit_name="Linear Fit")`` — calculate a new linear fit from the selected flux map and compare it against that map.
  ``fit_name`` is a keyword-only label for the new fit, not the key of a stored result.
* ``calculate_differential_inductances()`` / ``get_differential_inductances()`` / ``plot_differential_inductances()`` — derive :math:`L_{dd}`, :math:`L_{dq}`, :math:`L_{qd}`, :math:`L_{qq}` from the flux map as a ``DifferentialInductanceMap``.
* ``export_parameters_csv(path)``, ``export_flux_map_csv(path)``, ``export_differential_inductances_csv(path)`` — write the canonical CSV files.

``calculate_operation_area`` returns an ``OperationArea`` object containing the sampled dq current grid, torque and voltage values, and the supplied voltage and current limits.
The grid includes points outside the feasible region; the plot helper draws the current and voltage boundaries and torque contours from these arrays.
The optional maximum-torque-over-speed data is calculated only when ``speeds_rpm`` is supplied.
The optimization constrains voltage magnitude and current magnitude; catalog torque limits, speed limits, and individual d/q current limits are not enforced.

A complete runnable example is included in the repository:

.. literalinclude:: pyuzlib_showcase.py
   :language: python
   :caption: ``docs/source/software/pyuzlib/pyuzlib_showcase.py``

Documentation helpers
=====================

The module ``pyuzlib.docs.pmsm`` provides these helpers for documentation snippets:

* ``plot_flux_map(csv_path)`` for a Matplotlib-based static plot that integrates with the Sphinx ``plot`` directive.
* ``plot_flux_map_plotly(csv_path)`` for a Plotly-based interactive figure that integrates with the Sphinx ``plotly`` directive.
* ``L_dd_L_qq_from_flux_map_assuming_no_saturation(csv_path)`` for a linear-regression table.
* ``plot_linear_flux_model_comparison(csv_path)`` for comparing a linear fit against the flux map from a ``flux_map.csv`` file.
* ``plot_differential_inductances(csv_path)`` for deriving and plotting the differential inductances from a ``flux_map.csv`` file.
* ``plot_operation_area(machine_parameters_csv_path, ...)`` and ``plot_max_torque_curve(machine_parameters_csv_path, ...)`` for operation-area plots from a ``machine_parameters.csv`` file, as used by the motor dataset pages.

The flux-map helpers expect the columns ``i_d_A``, ``i_q_A``, ``psi_d_Vs``, and ``psi_q_Vs`` on a complete rectangular grid.
The operation-area helpers read scalar values from ``machine_parameters.csv``.

Example
=======

.. code-block:: python

	import pyuzlib

	pyuzlib.docs.pmsm.plot_flux_map(
		 "docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/"
		 "measured_psi_dq_averaged_800_rpm/flux_map.csv"
	)

Related Documentation
=====================

For a concrete dataset example, see :doc:`../control/uz_pmsm/beckhoff_AM8141-0j00-000/beckhoff_AM8141-0j00-000`.

Machine catalog generation
==========================

The root target prepares canonical maps and differential inductances from each ``dataset.json`` and ``flux_map_source.csv``, then generates the machine inventory CSV and C headers:

.. code-block:: bash

	# from the repository root
	make pyuzlib-generate-machines

The dataset layout, ``--with-flux-data`` flag, and generation command are documented in :ref:`uz_pmsm`, section "Adding a new motor".
