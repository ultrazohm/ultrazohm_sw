.. _uz_pmsm:

=======
uz_pmsm
=======

.. note:: This has to be integrated with uz_PMSM_config

``uz_pmsm`` defines a CSV based data scheme for machine parameters of PMSM to be used with the UltraZohm software framework.
The goal is to generate a unified data structure to match the controller, software models, and plots.

The data is split into:

* ``machine_parameters.csv`` contains the parameters that map directly to the existing ``uz_PMSM_t`` struct.
* ``flux_map.csv`` contains the regular nonlinear flux-linkage map :math:`\psi_d(i_d,i_q)` and :math:`\psi_q(i_d,i_q)`.
* ``differential_inductances.csv`` contains the derivatives of the flux map when a model or controller needs them explicitly.

The files used by code generation and plots should use the canonical names and ordering described below. The repository also contains measured and FEM source CSV examples with older column names; these are useful as import examples, but they are not canonical dataset directories.

Directory layout
================

Use one directory per machine and one subdirectory per dataset or version.
The machine name belongs in the directory name, not in every file name.
This keeps import/export functions simple and makes it clear which files belong together.

.. code-block:: text

   uz_motors/
     dummy_motor/
       nominal_v1/
         machine_parameters.csv
         flux_map.csv
         differential_inductances.csv

Only ``machine_parameters.csv`` is required for a linear machine model.
Only ``flux_map.csv`` is required for a nonlinear flux map representation.
The directory ``dummy_motor/nominal_v1`` contains the canonical synthetic example dataset.

General CSV rules
=================

All canonical CSV files use these rules:

* Comma separated values with one header row.
* Decimal point notation, no thousands separators.
* SI base units in the stored values.
* Units are encoded in column names for map data, e.g. ``i_d_A`` and ``psi_d_Vs``, and in parameter names for scalar parameter tables.
* No unnamed index column.
* No comments or unit rows inside the CSV file.
* Empty values are not allowed in canonical files used for import or code generation.
* Additional columns are allowed after the required columns, but importers must ignore unknown columns unless they explicitly need them.

The canonical dq convention is the same one used by the UltraZohm PMSM controller and transformations.
Do not mix peak and RMS values in one dataset.

Machine parameters
==================

``machine_parameters.csv`` is a two-column long-form table with ``parameter`` and ``value``.
It has no ``unit`` column; units are part of the parameter name, following the existing UltraZohm C names where possible.
The file contains the linear PMSM parameters and the machine operating-envelope values.
The order of rows is not relevant.

.. code-block:: text

   parameter,value
   R_ph_Ohm,0.51
   Ld_Henry,0.002
   Lq_Henry,0.003
   Psi_PM_Vs,0.042
   polePairs,4
   J_kg_m_squared,0.000108
   I_max_Ampere,12
   I_rated_Ampere,8
   Torque_rated_Nm,1.2
   Torque_max_Nm,2
   Torque_min_Nm,-2
   speed_rated_rpm,1000
   speed_max_rpm,1500
   speed_min_rpm,-1500
   V_dc_nominal_V,24
   I_d_max_A,10
   I_d_min_A,-10
   I_q_max_A,10
   I_q_min_A,-10

Required machine rows
---------------------

The following rows map directly to ``uz_PMSM_t`` and are required by the existing PMSM controller, setpoint module, and software model.

.. list-table:: Required ``uz_PMSM_t`` rows
   :header-rows: 1
   :widths: 30 50 20

   * - Parameter
     - Meaning
     - Existing consumer
   * - ``R_ph_Ohm``
     - Stator phase resistance :math:`R_s` in Ohm.
     - ``uz_PMSM_t``
   * - ``Ld_Henry``
     - Linear d-axis inductance :math:`L_d` in H.
     - ``uz_PMSM_t``
   * - ``Lq_Henry``
     - Linear q-axis inductance :math:`L_q` in H.
     - ``uz_PMSM_t``
   * - ``Psi_PM_Vs``
     - Permanent magnet flux linkage :math:`\psi_{PM}` in V s.
     - ``uz_PMSM_t``
   * - ``polePairs``
     - Number of pole pairs.
     - ``uz_PMSM_t``
   * - ``J_kg_m_squared``
     - Rotor inertia in kg m^2.
     - ``uz_PMSM_t``
   * - ``I_max_Ampere``
     - Maximum allowed current used by the setpoint module for MTPA and field weakening in A.
     - ``uz_PMSM_t``

Recommended rating rows
-----------------------

The following rows are not consumed by ``uz_PMSM_t`` directly, but they belong in the same file because they define the machine operating envelope from datasheets, tests, or FEM data.
Importers may use them to derive controller limits.

.. list-table:: Recommended rating rows
   :header-rows: 1
   :widths: 35 65

   * - Parameter
     - Meaning
   * - ``I_rated_Ampere``
     - Rated continuous phase current in A.
   * - ``Torque_rated_Nm``
     - Rated continuous torque in Nm.
   * - ``Torque_max_Nm``
     - Maximum allowed positive torque command in Nm.
   * - ``Torque_min_Nm``
     - Maximum allowed negative torque command in Nm.
   * - ``speed_rated_rpm``
     - Rated mechanical speed in rpm.
   * - ``speed_max_rpm``
     - Maximum allowed positive mechanical speed in rpm.
   * - ``speed_min_rpm``
     - Maximum allowed negative mechanical speed in rpm.
   * - ``V_dc_nominal_V``
     - Nominal DC-link voltage in V.
   * - ``I_d_max_A``
     - Maximum allowed d-axis current in A.
   * - ``I_d_min_A``
     - Minimum allowed d-axis current in A.
   * - ``I_q_max_A``
     - Maximum allowed q-axis current in A.
   * - ``I_q_min_A``
     - Minimum allowed q-axis current in A.

Relation to ``uz_pmsm_control`` limits
--------------------------------------

The motor CSV stores machine capability, not a complete ``uz_pmsm_control_configuration_t``.
The ``setpoint_limits`` of ``uz_pmsm_control`` are controller policy and can be derived from ratings such as ``Torque_max_Nm``, ``Torque_min_Nm``, ``speed_max_rpm``, ``speed_min_rpm``, ``I_d_max_A``, and ``I_q_max_A`` when a concrete controller configuration is generated.
DC-link voltage and DC-link current limits also stay outside this motor CSV because they depend on the inverter, DC source, and test setup.

Nonlinear flux map
==================

``flux_map.csv`` is a long-form table with one row per support point.
It represents a complete regular grid and is directly compatible with :ref:`uz_LUT_2D`.

.. code-block:: text

   operating_point,i_d_A,i_q_A,psi_d_Vs,psi_q_Vs
   0,-10,-10,0.022,-0.03
   1,0,-10,0.042,-0.03
   2,10,-10,0.062,-0.03
   3,-10,0,0.022,0

Required columns are:

.. list-table:: Flux map columns
   :header-rows: 1
   :widths: 25 75

   * - Column
     - Meaning
   * - ``operating_point``
     - Integer row index in LUT order. This column is useful for checks and plots, but importers should be able to regenerate it.
   * - ``i_d_A``
     - d-axis current breakpoint in A.
   * - ``i_q_A``
     - q-axis current breakpoint in A.
   * - ``psi_d_Vs``
     - d-axis flux linkage in V s.
   * - ``psi_q_Vs``
     - q-axis flux linkage in V s.

Ordering contract
-----------------

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
For example, the measured source column ``dut_id_set`` maps to ``i_d_A`` and ``dut_iq_set`` maps to ``i_q_A``; source columns ``psi_d`` and ``psi_q`` map to ``psi_d_Vs`` and ``psi_q_Vs``.

Differential inductances
========================

``differential_inductances.csv`` uses the same grid and the same ordering as ``flux_map.csv``.

.. code-block:: text

   operating_point,i_d_A,i_q_A,L_dd_H,L_dq_H,L_qd_H,L_qq_H
   0,-10,-10,0.002,0,0,0.003
   1,0,-10,0.002,0,0,0.003
   2,10,-10,0.002,0,0,0.003

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

Relation to controller and models
=================================

The existing PMSM software path is linear:

* :ref:`uz_PMSM_config` defines ``uz_PMSM_t`` with ``R_ph_Ohm``, ``Ld_Henry``, ``Lq_Henry``, ``Psi_PM_Vs``, ``polePairs``, ``J_kg_m_squared``, and ``I_max_Ampere``.
* :ref:`uz_pmsm_control` receives ``uz_PMSM_t`` and forwards it to the current controller and setpoint generation.
* :ref:`uz_pmsm_swmodel` currently evaluates the linear flux linkages

  .. math::

     \psi_d = L_d i_d + \psi_{PM}, \qquad \psi_q = L_q i_q.

The nonlinear data scheme should not replace this path.
Instead, ``machine_parameters.csv`` remains the source for the existing modules, while ``flux_map.csv`` and ``differential_inductances.csv`` are the source for optional nonlinear behavior.
For example, nonlinear static decoupling needs :math:`\psi_d` and :math:`\psi_q` at the actual current point, which can later be supplied by two ``uz_LUT_2D`` instances.
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

Importer and exporter contract
==============================

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
====================

Before a dataset is used in the controller or a model, check the following:

* ``machine_parameters.csv`` has exactly the columns ``parameter`` and ``value``.
* ``machine_parameters.csv`` contains every required ``uz_PMSM_t`` field exactly once.
* ``machine_parameters.csv`` contains the recommended machine envelope rows, including rated current, torque limits, speed limits, and d/q current limits, when it is used to derive controller limits.
* ``R_ph_Ohm``, ``Ld_Henry``, ``Lq_Henry``, ``polePairs``, ``J_kg_m_squared``, and ``I_max_Ampere`` are greater than zero.
* ``Psi_PM_Vs`` is greater than or equal to zero.
* ``flux_map.csv`` has the required columns ``operating_point``, ``i_d_A``, ``i_q_A``, ``psi_d_Vs``, and ``psi_q_Vs``.
* ``i_d_A`` and ``i_q_A`` form a complete rectangular grid.
* Breakpoints are strictly increasing after sorting.
* File order is sorted by ``i_q_A`` first and then by ``i_d_A``.
* ``differential_inductances.csv``, if present, has exactly the same ``operating_point``, ``i_d_A``, and ``i_q_A`` columns as ``flux_map.csv``.
* Source CSV files are not exported to C unless they have first been converted to the canonical regular map.


Available motor datasets
========================

.. toctree::
    :maxdepth: 1
    :caption: PMSM motors

    dummy_motor/dummy_motor
    beckhoff_HMD06_005_048_30_00M1IY170/beckhoff_HMD06_005_048_30_00M1IY170