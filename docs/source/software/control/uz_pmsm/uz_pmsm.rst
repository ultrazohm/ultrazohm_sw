.. _uz_pmsm:

=======
uz_pmsm
=======

.. warning:: This feature is work in progress but available and merged to enable real-world testing!

``uz_pmsm`` defines a CSV based data scheme for machine parameters of PMSM to be used with the UltraZohm software framework.
The goal is to generate a unified data structure to match the controller, software models, and plots.

The data is split into:

* ``machine_parameters.csv`` contains the parameters that map directly to the existing ``uz_PMSM_t`` struct.
* ``flux_map.csv`` contains the regular nonlinear flux-linkage map :math:`\psi_d(i_d,i_q)` and :math:`\psi_q(i_d,i_q)`.
* ``differential_inductances.csv`` contains the derivatives of the flux map when a model or controller needs them explicitly.

The Python companion library :ref:`pyuzlib` reads, validates, plots, and exports these files and generates the C machine catalog.
The files used by code generation and plots should use the canonical names and ordering described in the :ref:`file format reference <uz_pmsm_file_formats>`.
The repository contains CSV examples with column names that do not match the data format but imported using the ``pyuzlib`` library to fit the standard.

The intended workflow is to add raw flux-map data obtained by FEM or measurement, convert it to the canonical CSV format, and then generate the C macros for use in the controller and software model.
How are differential inductances generated? Only using toolchain, or?


Quick start: use an existing motor in C
=======================================

Every motor dataset in this database is exported as a C initializer macro.
To configure a PMSM with an existing dataset:

.. code-block:: c

   #include "uz_PMSM_config.h"

   uz_PMSM_t motor = UZ_PMSM_DUMMY_MOTOR_NOMINAL_V1_INIT;
   uz_PMSM_config_assert(motor);

The macro name is ``UZ_PMSM_<CATALOG_ID>_INIT``, where the catalog identifier is derived from ``<MOTOR_DIR>_<DATASET_DIR>``.
The generator replaces each run of non-alphanumeric characters with ``_``, removes leading and trailing underscores, and converts the result to uppercase.
If the normalized identifier begins with a digit, it is prefixed with ``MACHINE_``.
For example, ``my--motor/nominal_v1`` becomes ``UZ_PMSM_MY_MOTOR_NOMINAL_V1_INIT``, and ``123motor/nominal_v1`` becomes ``UZ_PMSM_MACHINE_123MOTOR_NOMINAL_V1_INIT``.
All available macros are listed in the table below, and the struct fields are documented in :ref:`uz_PMSM_config`.
To analyze or plot the underlying motor data in Python, use :ref:`pyuzlib`.

Available motor datasets
========================

The generated machine inventory lists every dataset with its C macro name and all parameter values:

.. csv-table:: Generated machine inventory ``available_machines.csv``
   :file: available_machines.csv
   :header-rows: 1

.. toctree::
    :maxdepth: 1
    :caption: PMSM motors

    dummy_motor/dummy_motor
    beckhoff_AM8141-0j00-000/beckhoff_AM8141-0j00-000
    mh_prototype/mh_prototype

Adding a new motor
==================

The workflow has four phases: create the dataset directory, fill in the machine data (optionally preprocessing raw data), regenerate the catalog, and use the generated macro in C code.

.. rubric:: Phase 1 — Create the dataset directory (manual)

Use the ``add_machine`` subcommand of ``generate_available_machines.py`` to scaffold the required directory structure and a ``machine_parameters.csv`` template with all row names pre-filled.
Run the following script commands from the repository root:

.. code-block:: bash

   # from the repository root
   python docs/source/software/control/uz_pmsm/generate_available_machines.py add_machine <motor_name> <dataset_name>

   # example
   python docs/source/software/control/uz_pmsm/generate_available_machines.py add_machine my_motor nominal_v1

With ``pyuzlib`` installed in editable mode from this checkout, the equivalent module command works from any working directory because it discovers the default dataset paths from the package location:

.. code-block:: bash

   python -m pyuzlib.machine_catalog add_machine my_motor nominal_v1

This creates:

.. code-block:: text

   uz_pmsm/
     my_motor/
       nominal_v1/
         machine_parameters.csv   ← template with all parameter names; machine_name and machine_id are pre-filled, all other values are empty

The script also prints the C macro name that will be generated:

.. code-block:: text

   Created: .../my_motor/nominal_v1/machine_parameters.csv
   Fill in all empty values, then run the catalog generator.
   C macro will be: UZ_PMSM_MY_MOTOR_NOMINAL_V1_INIT

``machine_id`` is pre-filled with the next unused integer.
It is a stable identifier reserved for future runtime machine selection and must stay unique across all motors.
Use positive values only; ``machine_id = 0`` is reserved for manual or unassigned configurations and is rejected by the catalog generator.
The script also prints a table of every parameter's constraint and unit, so you can fill in the CSV without leaving the terminal.

If the motor data starts from a raw FEM or measurement file with non-standard column names, pass ``--with-raw-data``.
This additionally creates a ``preprocess_to_correct_data_format.py`` template in the dataset directory with ``TODO`` comments for column name mapping:

.. code-block:: bash

   # from the repository root
   python docs/source/software/control/uz_pmsm/generate_available_machines.py add_machine my_motor nominal_v1 --with-raw-data

.. rubric:: Phase 2 — Fill in machine_parameters.csv (manual)

Open the generated template and fill in every empty value.
The required parameter rows map directly to fields of ``uz_PMSM_t`` and must satisfy the constraints documented in :ref:`uz_PMSM_config`.
The optional ``machine_name`` row is metadata and is not a C struct field.
The generator validates these constraints and reports errors with field names when they are violated.

If you also have flux-map data, place ``flux_map.csv`` in the same directory using the canonical column order ``operating_point,i_d_A,i_q_A,psi_d_Vs,psi_q_Vs`` (see the :ref:`file format reference <uz_pmsm_file_formats>`).
For raw FEM or measurement files with different column names, edit the ``preprocess_to_correct_data_format.py`` template created by ``--with-raw-data`` and run it manually before the next step.
See ``mh_prototype/fem_overaged_over_angle/preprocess_to_correct_data_format.py`` for an example.

.. rubric:: Phase 3 — Regenerate the catalog (scripted)

Run the catalog generator once to update both output artifacts:

.. code-block:: bash

   # from docs/
   make auto_generate_available_machines

   # or from the repo root
   PYTHONPATH=pyuzlib/src python3 -m pyuzlib.machine_catalog

If the dataset also contains ``flux_map.csv`` or ``differential_inductances.csv``, regenerate their headers too.
From the repository root, ``make pyuzlib-generate-machines`` runs both the scalar catalog and the flux-map and differential-inductance generators in one step (see :ref:`uz_pmsm_flux_map` and :ref:`uz_pmsm_differential_inductance`), so prefer it when unsure.
The existing ``make auto_generate_all`` command in ``docs/`` forwards to this root target.

The scalar catalog generator:

1. Parses the ``uz_PMSM_t`` struct definition from ``uz_PMSM_config.h`` and verifies that the Python model matches it exactly.
2. Finds every ``machine_parameters.csv`` file two levels deep under ``uz_pmsm/``.
3. Validates all parameter values and checks that every ``machine_id`` is positive and unique.
4. Validates canonical ``flux_map.csv`` and ``differential_inductances.csv`` files when present.
5. Writes ``available_machines.csv`` — a tabular inventory for humans and Sphinx.
6. Writes ``uz_available_machines_auto_generated.h`` — C designated-initializer macros, one per motor dataset.

Both output files must be committed to the repository after running.
All C float exports reject non-finite values, values outside the IEEE-754 float32 range, and nonzero values that would underflow to zero.
This also prevents positive scalar parameters from becoming zero in the generated machine configuration.

To verify that committed files are still in sync with the CSV sources:

.. code-block:: bash

   # from the repository root: all four generated artifacts
   make pyuzlib-check-generated

   # equivalent existing docs/ entry point (CI uses the root target above)
   make -C docs check_all

   # individual read-only checks from the repository root
   PYTHONPATH=pyuzlib/src python3 -m pyuzlib.machine_catalog --check
   PYTHONPATH=pyuzlib/src python3 -m pyuzlib.flux_map_catalog --check

Checks render the expected content in memory and compare it byte-for-byte with the existing files.
They do not rewrite artifacts, create temporary output files, or change machine IDs.
They exit with status 0 when everything matches, or status 1 with filenames, diffs for stale files, and a regeneration command when files are stale or missing.
``--check`` cannot be combined with ``--renumber`` or ``add_machine`` (argument error, status 2).
The individual ``docs/`` targets ``check_available_machines`` and ``check_flux_maps`` remain available.

.. rubric:: Phase 4 — Use the macro in C code (manual)

``uz_PMSM_config.h`` already includes ``uz_available_machines_auto_generated.h``, so no additional include is needed:

.. code-block:: c

   #include "uz_PMSM_config.h"

   uz_PMSM_t my_motor = UZ_PMSM_MY_MOTOR_NOMINAL_V1_INIT;
   uz_PMSM_config_assert(my_motor);

The macro expands to a C99 designated initializer with all 20 fields set.
``uz_PMSM_config_assert`` validates the physical parameters and the limit relations (e.g. rated below maximum, minimum below maximum) at runtime and fires ``uz_assert`` on violation; ``machine_id`` itself is not checked.
The PMSM controller and software model call ``uz_PMSM_config_assert_model`` and accept the original seven physical parameters without the rating envelope: ``R_ph_Ohm``, ``Ld_Henry``, ``Lq_Henry``, ``Psi_PM_Vs``, ``polePairs``, ``J_kg_m_squared``, and ``I_max_Ampere``.
The controller validates its separately supplied setpoint limits and safe operating region independently of the machine catalog ratings.
Setpoint generation validates only its own required parameters; inertia and the rating envelope are not required.
It is stricter for ``Psi_PM_Vs`` because FOC setpoint generation divides by this value; ``uz_SetPoint_init`` and ``uz_SetPoint_set_PMSM_config`` require ``Psi_PM_Vs > 0.0f``.

The current-control and setpoint configuration structs embed ``uz_PMSM_t`` by value.
Their runtime setters, ``uz_CurrentControl_set_PMSM_parameters`` and ``uz_SetPoint_set_PMSM_config``, accept a ``const uz_PMSM_t *`` and copy the complete struct into the instance's own configuration.
The caller's struct only needs to remain valid during the call, and later changes to it do not affect the instance.
``uz_CurrentControl_linear_decoupling`` also accepts a ``const uz_PMSM_t *`` and reads its parameters for that calculation.

.. _uz_PMSM_config:

PMSM config
===========

Motor parameters of a permanent magnet synchronous motor (PMSM) are needed for multiple functions.
To streamline the coding process, every necessary PMSM parameter is bundled inside a ``uz_PMSM_t`` struct, which can be used in the whole UltraZohm project.

.. doxygenstruct:: uz_PMSM_t
    :members:

Example
-------

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration

  #include "uz/uz_PMSM_config/uz_PMSM_config.h"
  int main(void) {
     uz_PMSM_t config = UZ_PMSM_DUMMY_MOTOR_NOMINAL_V1_INIT;
     uz_PMSM_config_assert(config);
  }

A struct can also be filled manually for a machine that is not part of the database.
When using the full validator ``uz_PMSM_config_assert``, all physical and rating/limit fields must satisfy the constraints listed above; ``machine_id`` is not checked.
For the controller, software model, or setpoint module, only the parameters required by that consumer need to be supplied as described above; unused fields may remain zero-initialized.

The full catalog validator and the model-only validator are available separately:

.. doxygenfunction:: uz_PMSM_config_assert

.. doxygenfunction:: uz_PMSM_config_assert_model

Troubleshooting
===============

* **The catalog generator fails with** ``Invalid PMSM parameter CSV <path>: ...`` — the named file contains an empty, unparsable, or constraint-violating value; the message names the offending parameter.
  A freshly scaffolded template fails like this until every value is filled in (Phase 2).
* **The catalog generator fails with** ``machine_id must be a positive integer ...`` — the dataset uses ``machine_id = 0`` or a negative value.
  Keep ``0`` for manual or unassigned configs and use a positive catalog ID for committed datasets.
* **The catalog generator fails with** ``Duplicate numeric machine_id ...`` — two ``machine_parameters.csv`` files use the same ``machine_id``; the message suggests the next unused value.
  This typically happens when two motors are added on separate branches and merged.
* **The catalog generator fails with** ``Invalid PMSM dataset maps ...`` — a canonical ``flux_map.csv`` is not finite, rectangular, or duplicate-free, or a sibling ``differential_inductances.csv`` does not match the same ``operating_point``, ``i_d_A``, and ``i_q_A`` order.
* **The CI check** ``make pyuzlib-check-generated`` **fails** — the committed generated files are out of sync with the CSV sources.
  Run ``make pyuzlib-generate-machines`` from the repository root and commit ``available_machines.csv`` and all three generated headers.
  CI only checks; it never regenerates or commits these files itself.
* **The catalog generator fails with** ``pyuzlib.PMSMParameters and uz_PMSM_t differ`` — the ``uz_PMSM_t`` struct in ``uz_PMSM_config.h`` was changed without updating the Python model.
  Mirror the change in the ``PMSMParameters`` dataclass (``pyuzlib/src/pyuzlib/pmsm/parameters.py``, same field order), extend ``PMSM_PARAMETER_CONSTRAINTS`` and ``uz_PMSM_config_assert`` consistently, then regenerate the catalog.

.. _uz_pmsm_file_formats:

File format reference
=====================

This section specifies the canonical dataset files.
It is required reading for writing importers/exporters or preparing data by hand; for the everyday workflows see the sections above.

Directory layout
----------------

Use one directory per machine and one subdirectory per dataset or version.
The machine name belongs in the directory name, not in every file name.
This keeps import/export functions simple and makes it clear which files belong together.

.. code-block:: text

   uz_pmsm/
     dummy_motor/
       nominal_v1/
         machine_parameters.csv
         flux_map.csv
         differential_inductances.csv

Only ``machine_parameters.csv`` is required for a linear machine model.
Only ``flux_map.csv`` is required for a nonlinear flux map representation.
The directory ``dummy_motor/nominal_v1`` contains the canonical synthetic example dataset.

General CSV rules
-----------------

All canonical CSV files use these rules:

* Comma separated values with one header row.
* Decimal point notation, no thousands separators.
* Units are encoded in column names for map data, e.g. ``i_d_A`` and ``psi_d_Vs``, and in parameter names for scalar parameter tables.
* SI units are used where practical; some parameters follow the existing C struct field names instead, e.g. rotational speeds are stored in rpm (``speed_max_rpm``).
* No unnamed index column.
* No comments or unit rows inside the CSV file.
* Empty values are not allowed in canonical files used for import or code generation.
* Flux-map and differential-inductance files may contain additional columns after the required columns; their importers ignore unknown columns.
* Machine parameter files use exactly two columns, ``parameter`` and ``value``; store additional metadata as parameter rows.

The canonical dq convention is the same one used by the UltraZohm PMSM controller and transformations.
Do not mix peak and RMS values in one dataset.

Machine parameters
------------------

``machine_parameters.csv`` is a two-column long-form table with ``parameter`` and ``value``.
It has no ``unit`` column; units are part of the parameter name, following the existing UltraZohm C names where possible.
The file contains the linear PMSM parameters and the machine operating-envelope values.
The order of rows is not relevant.
The canonical synthetic example from ``dummy_motor/nominal_v1/machine_parameters.csv`` is:

.. csv-table:: Example ``machine_parameters.csv``
   :file: dummy_motor/nominal_v1/machine_parameters.csv
   :header-rows: 1

Required machine rows
~~~~~~~~~~~~~~~~~~~~~

The following rows map directly to ``uz_PMSM_t`` and are required for catalog generation.
The PMSM controller and software model require only the original seven physical parameters described above.
Setpoint generation requires its own subset, which excludes inertia and requires positive permanent-magnet flux linkage.

.. csv-table:: Required ``uz_PMSM_t`` rows
   :file: required_uz_pmsm_rows.csv
   :header-rows: 1
   :widths: 30 50 20

The ``machine_name`` row is optional.
Its value becomes the human-readable label in the generated C header comment and the machine inventory CSV.
If absent, the motor directory name is used instead.

Relation to ``uz_pmsm_control`` limits
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The motor CSV stores machine capability, not a complete ``uz_pmsm_control_configuration_t``.
The ``setpoint_limits`` of ``uz_pmsm_control`` are controller policy and can be derived from ratings such as ``Torque_max_Nm``, ``Torque_min_Nm``, ``speed_max_rpm``, ``speed_min_rpm``, ``I_d_max_A``, and ``I_q_max_A`` when a concrete controller configuration is generated.
DC-link voltage and DC-link current limits also stay outside this motor CSV because they depend on the inverter, DC source, and test setup.

Nonlinear flux map
------------------

``flux_map.csv`` is a long-form table with one row per support point.
It represents a complete regular grid and is directly compatible with :ref:`uz_LUT_2D`.

C export requires at least two breakpoints per axis, strictly increasing even after conversion to float32, and exactly one grid value per current pair for every exported quantity.
The same requirements apply to differential-inductance maps.
The Python analysis importers can still load grids or value ranges that are unsuitable for C export; the additional restrictions are checked by the header generators.

The canonical synthetic example from ``dummy_motor/nominal_v1/flux_map.csv`` is:

.. csv-table:: Example ``flux_map.csv``
   :file: dummy_motor/nominal_v1/flux_map.csv
   :header-rows: 1

Required columns are:

.. csv-table:: Flux map columns
   :file: flux_map_columns.csv
   :header-rows: 1
   :widths: 25 75

Ordering contract
~~~~~~~~~~~~~~~~~

Use ``i_d_A`` as the ``uz_LUT_2D`` x-axis and ``i_q_A`` as the y-axis.
Both breakpoint vectors must be strictly increasing.
The file order is row-major with x changing fastest:

#. Sort by ``i_q_A`` ascending.
#. Within each ``i_q_A`` row, sort by ``i_d_A`` ascending.
#. Store the corresponding ``psi_d_Vs`` or ``psi_q_Vs`` value in that exact row order when creating the flattened LUT data array.

This means the flattened index for a point is:

.. math::

   k = i_{q,idx} \cdot N_d + i_{d,idx}

where :math:`N_d` is the number of d-axis breakpoints.

With this convention the import/export functions can build a ``uz_LUT_2D`` instance as follows:

* ``breakpoints_x`` is the sorted unique vector of ``i_d_A``.
* ``breakpoints_y`` is the sorted unique vector of ``i_q_A``.
* ``psi_d_data`` is ``psi_d_Vs`` in file order.
* ``psi_q_data`` is ``psi_q_Vs`` in file order.

Measured or FEM source tables can be irregular, contain duplicate operating points, use different column names, or use a different order.
Convert such source data to ``flux_map.csv`` before it is used for C arrays or deterministic plots.
For example, the raw FEM export in ``mh_prototype/fem_overaged_over_angle/flux_map_raw_from_fem.csv`` uses the source columns ``I_d``, ``I_q``, ``Psi_d``, and ``Psi_q``; the ``preprocess_to_correct_data_format.py`` script in the same directory maps them to ``i_d_A``, ``i_q_A``, ``psi_d_Vs``, and ``psi_q_Vs``.

Differential inductances
------------------------

``differential_inductances.csv`` uses the same grid and the same ordering as ``flux_map.csv``.

The canonical synthetic example from ``dummy_motor/nominal_v1/differential_inductances.csv`` is:

.. csv-table:: Example ``differential_inductances.csv``
   :file: dummy_motor/nominal_v1/differential_inductances.csv
   :header-rows: 1

The Python tests compare each committed differential-inductance dataset with derivatives recalculated from its sibling ``flux_map.csv`` (second-order edge differences where the grid permits).
Regenerate the derived CSV when changing the flux data.
This numerical check complements ``make -C docs check_all``, which checks generated headers against the committed CSVs.
Run ``make pyuzlib-test`` from the repository root; the tests also compile generated declarations using ``cc`` (or the command set in ``CC``).

The four inductances are the entries of the differential flux linkage matrix:

.. math::

   \begin{bmatrix}
   \dot{\psi}_d \\
   \dot{\psi}_q
   \end{bmatrix}
   =
   \begin{bmatrix}
   L_{dd} & L_{dq} \\
   L_{qd} & L_{qq}
   \end{bmatrix}
   \begin{bmatrix}
   \dot{i}_d \\
   \dot{i}_q
   \end{bmatrix}

with

.. math::

   L_{dd}=\frac{\partial \psi_d}{\partial i_d}, \quad
   L_{dq}=\frac{\partial \psi_d}{\partial i_q}, \quad
   L_{qd}=\frac{\partial \psi_q}{\partial i_d}, \quad
   L_{qq}=\frac{\partial \psi_q}{\partial i_q}.

For energy-consistent maps the two cross terms should be close to each other.
Store both terms anyway; an exporter can decide whether a later controller or model wants both terms, one selected term, or an averaged cross term.

Importer and exporter contract
------------------------------

MATLAB and Python helpers should implement the same checks and produce the same canonical order.
The recommended minimum API is:

* Read a dataset directory machine parameters, flux map, and optional differential inductances.
* Validate the mandatory columns and the units encoded in map column names or scalar parameter names.
* Validate that canonical maps are rectangular, have no duplicate ``(i_d_A, i_q_A)`` pairs, and use strictly increasing breakpoints.
* Sort maps into the canonical row-major order before writing.
* Export ``uz_PMSM_t`` values and derive controller limit values from the ratings in ``machine_parameters.csv``.
* Export ``uz_LUT_2D`` breakpoint and data arrays from ``flux_map.csv``.
* Optionally derive ``differential_inductances.csv`` from ``flux_map.csv`` using a documented method.

Importers may support legacy column aliases for convenience, such as ``i_d`` to ``i_d_A`` or ``psi_d`` to ``psi_d_Vs``.
Exporters should always write the canonical column names.

Validation checklist
--------------------

The catalog generator validates the required machine parameters and canonical maps on every run.
For parameter CSV headers, it checks the first two column names but does not reject additional header names; each data row must still contain exactly two entries.
Keep the header to exactly ``parameter,value`` to comply with the canonical format.
The positive-flux requirement for setpoint generation is checked by the setpoint module, while the catalog accepts zero permanent-magnet flux linkage.
Before a dataset is used in the controller or a model, check the following:

* ``machine_parameters.csv`` has exactly the columns ``parameter`` and ``value``.
* ``machine_parameters.csv`` contains every required ``uz_PMSM_t`` field exactly once.
* ``machine_parameters.csv`` contains the machine envelope rows, including rated current, torque limits, speed limits, and d/q current limits.
* ``machine_id`` is a positive integer and is unique across all committed PMSM datasets.
* ``R_ph_Ohm``, ``Ld_Henry``, ``Lq_Henry``, ``polePairs``, ``J_kg_m_squared``, and ``I_max_Ampere`` are greater than zero.
* ``Psi_PM_Vs`` is greater than or equal to zero.
* ``Psi_PM_Vs`` is greater than zero for configs passed to the setpoint module.
* ``flux_map.csv`` has the four required columns ``i_d_A``, ``i_q_A``, ``psi_d_Vs``, and ``psi_q_Vs``.
  The analysis importer regenerates ``operating_point`` automatically; the catalog generator checks that this column, when supplied, follows the canonical row order.
* ``i_d_A`` and ``i_q_A`` form a complete rectangular grid.
* Breakpoints are strictly increasing after sorting.
* File order is sorted by ``i_q_A`` first and then by ``i_d_A``.
* ``differential_inductances.csv``, if present, has exactly the same ``operating_point``, ``i_d_A``, and ``i_q_A`` columns as ``flux_map.csv``.
* Source CSV files are not exported to C unless they have first been converted to the canonical regular map.

Relation to controller and models
=================================

The existing PMSM software path is linear:

* :ref:`uz_PMSM_config` defines ``uz_PMSM_t`` with the required rows from ``machine_parameters.csv``.
* :ref:`uz_pmsm_control` receives ``uz_PMSM_t`` and forwards it to the current controller and setpoint generation.
* :ref:`uz_pmsm_swmodel` currently evaluates the linear flux linkages

  .. math::

     \psi_d = L_d i_d + \psi_{PM}, \qquad \psi_q = L_q i_q.

The flux-map and differential-inductance modules provide independent lookups and are not connected automatically to the controller or software model.
The nonlinear data scheme should not replace this path.
Instead, ``machine_parameters.csv`` remains the source for the existing modules, while ``flux_map.csv`` and ``differential_inductances.csv`` are the source for optional nonlinear behavior.
For example, nonlinear static decoupling needs :math:`\psi_d` and :math:`\psi_q` at the actual current point.
These are supplied by two ``uz_LUT_2D`` instances loaded at compile time from ``flux_map.csv`` via :ref:`uz_pmsm_flux_map`, which generates a macro header so that only the flux maps actually used are compiled into the firmware.
The differential inductance matrix :math:`L_{dd}, L_{dq}, L_{qd}, L_{qq}` is likewise loaded at compile time from ``differential_inductances.csv`` via :ref:`uz_pmsm_differential_inductance` (generated by the same tool as the flux-map header).
A nonlinear PMSM software model can use the same flux maps together with the differential inductance matrix to solve

.. math::

   \begin{bmatrix}
   L_{dd} & L_{dq} \\
   L_{qd} & L_{qq}
   \end{bmatrix}
   \begin{bmatrix}
   \dot{i}_d \\
   \dot{i}_q
   \end{bmatrix}
   =
   \begin{bmatrix}
   v_d - R_s i_d + \omega_e \psi_q \\
   v_q - R_s i_q - \omega_e \psi_d
   \end{bmatrix}.

For the linear case this reduces to the existing model equations with ``Ld_Henry`` and ``Lq_Henry`` on the diagonal.

TikZ plotting
=============

Because ``flux_map.csv`` is long-form and sorted in LUT order, it can be plotted directly with PGFPlots.
Set ``mesh/rows`` to the number of unique ``i_q_A`` breakpoints.

.. code-block:: latex

   \pgfplotstableread[col sep=comma]{dummy_motor/nominal_v1/flux_map.csv}\fluxmap

   \begin{tikzpicture}
       \begin{groupplot}[
           group style={group size=2 by 1, horizontal sep=2cm},
           view={45}{45},
           colormap/viridis,
           grid=both,
           width=0.45\columnwidth,
           height=6cm
       ]
       \nextgroupplot[
           xlabel={$i_d$ in A},
           ylabel={$i_q$ in A},
           zlabel={$\psi_d$ in mVs}
       ]
       \addplot3[surf, shader=interp, colormap/viridis, mesh/rows=3, mark=*]
           table[x=i_d_A, y=i_q_A, z expr=\thisrow{psi_d_Vs}*1000] \fluxmap;

       \nextgroupplot[
           xlabel={$i_d$ in A},
           ylabel={$i_q$ in A},
           zlabel={$\psi_q$ in mVs}
       ]
       \addplot3[surf, shader=interp, colormap/viridis, mesh/rows=3, mark=*]
           table[x=i_d_A, y=i_q_A, z expr=\thisrow{psi_q_Vs}*1000] \fluxmap;
       \end{groupplot}
   \end{tikzpicture}
