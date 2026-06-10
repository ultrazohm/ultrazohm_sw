=======
pyuzlib
=======

``pyuzlib`` is a small Python helper library for documentation and data-processing tasks in the UltraZohm repository.

At the moment, the package mainly provides plotting helpers for PMSM flux-map datasets stored as CSV files.

Installation
============

Inside the repository, install the package in editable mode:

.. code-block:: bash

	python -m pip install -e ./pyuzlib

Public API
==========

The package root exposes the ``docs`` namespace:

.. code-block:: python

	import pyuzlib

	print(pyuzlib.__version__)
	pyuzlib.docs.pmsm.plot_flux_map(...)

PMSM Helpers
============

The module ``pyuzlib.docs.pmsm`` currently provides these helpers:

* ``plot_flux_map(csv_path)`` for a Matplotlib-based static plot that integrates with the Sphinx ``plot`` directive.
* ``plot_flux_map_plotly(csv_path)`` for a Plotly-based interactive figure that integrates with the Sphinx ``plotly`` directive.

The CSV file is expected to contain the columns ``i_d_A``, ``i_q_A``, ``psi_d_Vs``, and ``psi_q_Vs`` on a regular grid.

Example
=======

.. code-block:: python

	import pyuzlib

	pyuzlib.docs.pmsm.plot_flux_map(
		 "docs/source/software/control/uz_pmsm/beckhoff_HMD06_005_048_30_00M1IY170/"
		 "measured_psi_dq_averaged_800_rpm/flux_map.csv"
	)

Related Documentation
=====================

For a concrete dataset example, see :doc:`../control/uz_pmsm/beckhoff_HMD06_005_048_30_00M1IY170/beckhoff_HMD06_005_048_30_00M1IY170`.
