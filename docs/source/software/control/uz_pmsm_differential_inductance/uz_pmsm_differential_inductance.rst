.. _uz_pmsm_differential_inductance:

===============================
uz_pmsm_differential_inductance
===============================

``uz_pmsm_differential_inductance`` loads a PMSM differential-inductance map — the four entries
:math:`L_{dd}, L_{dq}, L_{qd}, L_{qq}` of the differential flux-linkage matrix — into four
:ref:`uz_LUT_2D` instances and returns the interpolated 2x2 matrix at a dq current operating point.
It is the companion of :ref:`uz_pmsm_flux_map`: the flux map gives :math:`\psi_{dq}(i_{dq})`, this
module gives its Jacobian :math:`\partial\psi_{dq}/\partial i_{dq}`.

.. math::

   \begin{bmatrix} \dot{\psi}_d \\ \dot{\psi}_q \end{bmatrix}
   =
   \begin{bmatrix} L_{dd} & L_{dq} \\ L_{qd} & L_{qq} \end{bmatrix}
   \begin{bmatrix} \dot{i}_d \\ \dot{i}_q \end{bmatrix}

Generated macro header
======================

``pyuzlib.flux_map_catalog`` scans every ``differential_inductances.csv`` under the motor database
(the same generator that emits the flux-map header) and writes
``vitis/software/Baremetal/src/uz/uz_pmsm_differential_inductance/uz_pmsm_differential_inductances_auto_generated.h``.
For each dataset it defines, using the same ``<MOTOR_DIR>_<DATASET_DIR>`` naming as the flux-map and
scalar catalogs:

* ``UZ_DIFFIND_<CATALOG_ID>_I_D_BREAKPOINTS_A`` / ``_I_Q_BREAKPOINTS_A`` — breakpoint initializer lists.
* ``UZ_DIFFIND_<CATALOG_ID>_L_DD_H`` / ``_L_DQ_H`` / ``_L_QD_H`` / ``_L_QQ_H`` — the four inductance
  grids, row-major with ``i_d`` (the LUT x-axis) changing fastest, matching :ref:`uz_LUT_2D`.
* ``UZ_DIFFIND_<CATALOG_ID>_I_D_LENGTH`` / ``_I_Q_LENGTH`` — the grid dimensions.

As with the flux-map header, these are only preprocessor macros: **a macro that is never used
contributes zero bytes to the binary.** Regenerate and verify the committed header:

.. code-block:: bash

   # from docs/
   make auto_generate_flux_maps    # regenerates BOTH the flux-map and differential-inductance headers
   make check_flux_maps            # CI check: both committed headers match the CSV sources

Instance counts
===============

Each ``uz_pmsm_differential_inductance`` instance builds **four** ``uz_LUT_2D`` instances (one per
matrix entry). Both module instance counts default to ``0`` in production. To use differential
inductances, set in ``uz_global_configuration.h``:

.. code-block:: c

   #define UZ_PMSM_DIFFERENTIAL_INDUCTANCE_MAX_INSTANCES  <n>
   // budget four LUTs per instance here, plus two per uz_pmsm_flux_map instance:
   #define UZ_LUT_2D_MAX_INSTANCES  (4 * <n> + 2 * <flux_map_instances>)

Usage
=====

The breakpoint and inductance arrays must outlive the instance because ``uz_LUT_2D`` stores pointers
to them, so declare them ``static``. They are non-``const`` to match ``uz_array_float_t``.

.. code-block:: c

   #include "uz_pmsm_differential_inductance.h"
   #include "uz_pmsm_differential_inductances_auto_generated.h"

   static float id_bp[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_I_D_BREAKPOINTS_A;
   static float iq_bp[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_I_Q_BREAKPOINTS_A;
   static float L_dd[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_DD_H;
   static float L_dq[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_DQ_H;
   static float L_qd[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_QD_H;
   static float L_qq[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_QQ_H;

   uz_pmsm_differential_inductance_t *diff_ind = uz_pmsm_differential_inductance_init(
       (struct uz_pmsm_differential_inductance_config_t){
           .i_d_breakpoints_A = {.length = UZ_ARRAY_SIZE(id_bp), .data = id_bp},
           .i_q_breakpoints_A = {.length = UZ_ARRAY_SIZE(iq_bp), .data = iq_bp},
           .L_dd_H = {.length = UZ_ARRAY_SIZE(L_dd), .data = L_dd},
           .L_dq_H = {.length = UZ_ARRAY_SIZE(L_dq), .data = L_dq},
           .L_qd_H = {.length = UZ_ARRAY_SIZE(L_qd), .data = L_qd},
           .L_qq_H = {.length = UZ_ARRAY_SIZE(L_qq), .data = L_qq}});

   uz_3ph_dq_t i_dq_A = {.d = 0.0f, .q = 5.0f};
   struct uz_pmsm_differential_inductance_matrix_t L = uz_pmsm_differential_inductance_get_L_dq_H(diff_ind, i_dq_A);

API
===

.. doxygenstruct:: uz_pmsm_differential_inductance_config_t
    :members:

.. doxygenstruct:: uz_pmsm_differential_inductance_matrix_t
    :members:

.. doxygentypedef:: uz_pmsm_differential_inductance_t

.. doxygenfunction:: uz_pmsm_differential_inductance_init

.. doxygenfunction:: uz_pmsm_differential_inductance_get_L_dq_H
