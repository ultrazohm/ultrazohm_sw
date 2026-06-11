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

The package root exposes the ``pmsm`` and ``docs`` namespaces:

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

``PMSMParameters`` stores the C-compatible fields ``R_ph_Ohm``, ``Ld_Henry``, ``Lq_Henry``, ``Psi_PM_Vs``, ``polePairs``, ``J_kg_m_squared``, and ``I_max_Ampere``. Additional scalar values from parameter CSV files are preserved separately for documentation and controller workflows.

Compatibility Helpers
=====================

The module ``pyuzlib.docs.pmsm`` still provides these helpers for documentation snippets:

* ``plot_flux_map(csv_path)`` for a Matplotlib-based static plot that integrates with the Sphinx ``plot`` directive.
* ``plot_flux_map_plotly(csv_path)`` for a Plotly-based interactive figure that integrates with the Sphinx ``plotly`` directive.
* ``L_dd_L_qq_from_flux_map_assuming_no_saturation(csv_path)`` for the existing linear-regression table.

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


.. code-block:: bash

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
* ``uz_avialable_machines_auto_generated.h`` is regenerated automatically.
* ``docs/source/software/control/uz_pmsm/generate_available_machines.py`` is only a thin wrapper.

The important guardrail is that ``pyuzlib.machine_catalog`` compares the parsed ``uz_PMSM_t`` field list against ``PMSMParameters``. If the C struct changes but the Python data model is not updated, catalog generation fails with a clear mismatch instead of silently producing incorrect macros.

This workflow assumes that the new member can still be represented as a scalar ``parameter,value`` entry in ``machine_parameters.csv`` and that the C declaration is a supported scalar field type. If a future member is an array, nested struct, or otherwise not representable in the current CSV scheme, both the CSV schema and the generator logic must be extended.