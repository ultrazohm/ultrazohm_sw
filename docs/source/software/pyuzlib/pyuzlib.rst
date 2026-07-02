=======
pyuzlib
=======

``pyuzlib`` is a small Python helper library for documentation and data-processing tasks in the UltraZohm repository.

At the moment, the package mainly provides PMSM data helpers for scalar machine parameters, flux-map CSV files, fitting routines, plotting, and CSV export.

Installation
============

Inside the repository, install the package in editable mode:

.. code-block:: bash

	python -m pip install -e ./pyuzlib

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

``PMSMParameters`` stores all 20 C-compatible fields of ``uz_PMSM_t``: ``machine_id``, the physical parameters (``R_ph_Ohm``, ``Ld_Henry``, ``Lq_Henry``, ``Psi_PM_Vs``, ``polePairs``, ``J_kg_m_squared``), and the rating and limit values (``I_max_Ampere``, ``I_rated_Ampere``, ``Torque_rated_Nm``, ``Torque_max_Nm``, ``Torque_min_Nm``, ``speed_rated_rpm``, ``speed_max_rpm``, ``speed_min_rpm``, ``V_dc_nominal_V``, ``I_d_max_A``, ``I_d_min_A``, ``I_q_max_A``, ``I_q_min_A``). Additional scalar values from parameter CSV files (e.g. ``machine_name``) are preserved separately in ``additional_parameters`` for documentation and controller workflows.

PMSM API overview
=================

The ``pyuzlib.pmsm.PMSM`` class bundles the whole workflow. Besides the methods shown above it provides:

* ``update_parameters(**values)`` — update C fields or additional parameters in place.
* ``get_flux_map(name)`` — access a loaded flux map as a ``FluxMap`` object.
* ``compare_linear_flux_model(fit_name)`` / ``plot_linear_flux_model_comparison(fit_name)`` — compare a linear fit against the nonlinear flux map.
* ``calculate_differential_inductances()`` / ``get_differential_inductances()`` / ``plot_differential_inductances()`` — derive :math:`L_{dd}`, :math:`L_{dq}`, :math:`L_{qd}`, :math:`L_{qq}` from the flux map as a ``DifferentialInductanceMap``.
* ``export_parameters_csv(path)``, ``export_flux_map_csv(path)``, ``export_differential_inductances_csv(path)`` — write the canonical CSV files.

``calculate_operation_area`` returns an ``OperationArea`` object holding the feasible current region, torque isolines, and the maximum-torque-over-speed data used by the plot helpers.

A complete runnable example is included in the repository:

.. literalinclude:: pyuzlib_showcase.py
   :language: python
   :caption: ``docs/source/software/pyuzlib/pyuzlib_showcase.py``

Compatibility Helpers
=====================

The module ``pyuzlib.docs.pmsm`` still provides these helpers for documentation snippets:

* ``plot_flux_map(csv_path)`` for a Matplotlib-based static plot that integrates with the Sphinx ``plot`` directive.
* ``plot_flux_map_plotly(csv_path)`` for a Plotly-based interactive figure that integrates with the Sphinx ``plotly`` directive.
* ``L_dd_L_qq_from_flux_map_assuming_no_saturation(csv_path)`` for the existing linear-regression table.
* ``plot_linear_flux_model_comparison(csv_path)`` for comparing a linear fit against the flux map from a ``flux_map.csv`` file.
* ``plot_differential_inductances(csv_path)`` for deriving and plotting the differential inductances from a ``flux_map.csv`` file.
* ``plot_operation_area(machine_parameters_csv_path, ...)`` and ``plot_max_torque_curve(machine_parameters_csv_path, ...)`` for operation-area plots from a ``machine_parameters.csv`` file, as used by the motor dataset pages.

The CSV file is expected to contain the columns ``i_d_A``, ``i_q_A``, ``psi_d_Vs``, and ``psi_q_Vs`` on a regular grid.

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

Auto-generation for machine catalog
===================================

Run the catalog generator from the repository root (or use ``make auto_generate_available_machines`` from ``docs/``):

.. code-block:: bash

	# from the repo root
	PYTHONPATH=pyuzlib/src python3 -m pyuzlib.machine_catalog


Adding new members to uz_PMSM_t
===============================

The machine-catalog generation flow is designed so that changes to ``uz_PMSM_t`` mostly require schema updates, not generator updates.

If a new scalar member is added to ``uz_PMSM_t``, update these places:

* Add the new field to ``vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h``.
* Extend the checks in ``vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.c`` if the new field needs validation.
* Add the same field to the ``PMSMParameters`` dataclass in ``pyuzlib/src/pyuzlib/pmsm/parameters.py``.
* Extend ``PMSMParameters.validate_for_c()`` if the new field is required or constrained.
* Add the new parameter row to every ``machine_parameters.csv`` file under ``docs/source/software/control/uz_pmsm``.
* Update the canonical CSV documentation in ``docs/source/software/control/uz_pmsm/uz_pmsm.rst``.
* Regenerate the catalog using ``python -m pyuzlib.machine_catalog`` or ``uz-generate-pmsm-machine-catalog``.

The following parts do not usually need manual changes:

* ``pyuzlib.machine_catalog`` parses the field list directly from ``uz_PMSM_t`` in the C header.
* ``uz_available_machines_auto_generated.h`` is regenerated automatically.
* ``docs/source/software/control/uz_pmsm/generate_available_machines.py`` is only a thin wrapper.

The important guardrail is that ``pyuzlib.machine_catalog`` compares the parsed ``uz_PMSM_t`` field list against ``PMSMParameters``. If the C struct changes but the Python data model is not updated, catalog generation fails with a clear mismatch instead of silently producing incorrect macros.

This workflow assumes that the new member can still be represented as a scalar ``parameter,value`` entry in ``machine_parameters.csv`` and that the C declaration is a supported scalar field type. If a future member is an array, nested struct, or otherwise not representable in the current CSV scheme, both the CSV schema and the generator logic must be extended.