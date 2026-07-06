.. _uz_pmsm_flux_map:

================
uz_pmsm_flux_map
================

``uz_pmsm_flux_map`` loads a nonlinear PMSM flux map (:math:`\psi_d(i_d,i_q)` and :math:`\psi_q(i_d,i_q)`) into two :ref:`uz_LUT_2D` instances and samples both flux linkages at a dq current operating point.
The flux-map data is generated **at compile time** from the :ref:`uz_pmsm` ``flux_map.csv`` datasets into a macro header, so only the maps you actually use end up in the ``.elf``.

Generated macro header
======================

``pyuzlib.flux_map_catalog`` scans every ``flux_map.csv`` under the motor database and emits ``vitis/software/Baremetal/src/uz/uz_pmsm_flux_map/uz_pmsm_flux_maps_auto_generated.h``.
For each dataset it defines, using the same ``<MOTOR_DIR>_<DATASET_DIR>`` naming as the scalar catalog:

* ``UZ_FLUXMAP_<CATALOG_ID>_I_D_BREAKPOINTS_A`` / ``_I_Q_BREAKPOINTS_A`` — breakpoint initializer lists.
* ``UZ_FLUXMAP_<CATALOG_ID>_PSI_D_VS`` / ``_PSI_Q_VS`` — the flux grids, row-major with ``i_d`` (the LUT x-axis) changing fastest, directly matching :ref:`uz_LUT_2D`.
* ``UZ_FLUXMAP_<CATALOG_ID>_I_D_LENGTH`` / ``_I_Q_LENGTH`` — the grid dimensions.

These are only preprocessor macros: **a macro that is never used contributes zero bytes to the binary.**
Storage is allocated only where you expand a macro into an array.
Regenerate and verify the committed header the same way as the machine catalog:

.. code-block:: bash

   # from docs/
   make auto_generate_flux_maps    # regenerate and commit the header
   make check_flux_maps            # CI check: committed header matches the CSV sources

Instance counts
===============

Each ``uz_pmsm_flux_map`` instance builds **two** ``uz_LUT_2D`` instances (one per flux axis).
Both module instance counts default to ``0`` in production.
To use flux maps, set in ``uz_global_configuration.h``:

.. code-block:: c

   #define UZ_PMSM_FLUX_MAP_MAX_INSTANCES  <n>
   #define UZ_LUT_2D_MAX_INSTANCES         (2 * <n>)   // at least two LUTs per flux map

Usage
=====

The breakpoint and flux arrays must outlive the instance because ``uz_LUT_2D`` stores pointers to them, so declare them ``static``.
They are non-``const`` to match ``uz_array_float_t``.

.. code-block:: c

   #include "uz_pmsm_flux_map.h"
   #include "uz_pmsm_flux_maps_auto_generated.h"

   static float id_bp[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_D_BREAKPOINTS_A;
   static float iq_bp[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_Q_BREAKPOINTS_A;
   static float psi_d[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_PSI_D_VS;
   static float psi_q[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_PSI_Q_VS;

   uz_pmsm_flux_map_t *flux_map = uz_pmsm_flux_map_init((struct uz_pmsm_flux_map_config_t){
       .i_d_breakpoints_A = {.length = UZ_ARRAY_SIZE(id_bp), .data = id_bp},
       .i_q_breakpoints_A = {.length = UZ_ARRAY_SIZE(iq_bp), .data = iq_bp},
       .psi_d_Vs = {.length = UZ_ARRAY_SIZE(psi_d), .data = psi_d},
       .psi_q_Vs = {.length = UZ_ARRAY_SIZE(psi_q), .data = psi_q}});

   uz_3ph_dq_t i_dq_A = {.d = 0.0f, .q = 5.0f};
   uz_3ph_dq_t psi_dq_Vs = uz_pmsm_flux_map_get_psi_dq_Vs(flux_map, i_dq_A);

API
===

.. doxygenstruct:: uz_pmsm_flux_map_config_t
    :members:

.. doxygentypedef:: uz_pmsm_flux_map_t

.. doxygenfunction:: uz_pmsm_flux_map_init

.. doxygenfunction:: uz_pmsm_flux_map_get_psi_dq_Vs

.. doxygenfunction:: uz_pmsm_flux_map_get_psi_d_Vs

.. doxygenfunction:: uz_pmsm_flux_map_get_psi_q_Vs
