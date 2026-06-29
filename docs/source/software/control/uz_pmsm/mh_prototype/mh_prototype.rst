============
mh_prototype
============

MH prototype machine.
The measured dataset in ``fem_overaged_over_angle/flux_map.csv`` can be plotted directly with ``pyuzlib``.

.. warning:: Dummy data for MH Prototype! The electrical parameters (R_ph_Ohm, Ld_Henry, Lq_Henry, Psi_PM_Vs) and inertia (J_kg_m_squared) in machine_parameters.csv are placeholder values copied from the beckhoff dataset and do not reflect actual characterization data.

Matplotlib
==========


.. plot::
  :caption: Flux map

   import pyuzlib
   pyuzlib.docs.pmsm.plot_flux_map('docs/source/software/control/uz_pmsm/mh_prototype/fem_overaged_over_angle/flux_map.csv')

Plotly
======

.. plotly::
  :iframe-width: 100%
  :caption: Flux map Plotly

   import pyuzlib
   pyuzlib.docs.pmsm.plot_flux_map_plotly('docs/source/software/control/uz_pmsm/mh_prototype/fem_overaged_over_angle/flux_map.csv')


Coefficients
============

.. plot::
  :caption: Linear flux model compared with measured flux-map data

   import pyuzlib

   pyuzlib.docs.pmsm.plot_linear_flux_model_comparison(
       'docs/source/software/control/uz_pmsm/mh_prototype/fem_overaged_over_angle/flux_map.csv',
       grid_points=20,
   )


Operating area
==============

.. warning:: Dummy data for MH Prototype!

.. plot::
  :caption: Operating area at rated speed

   import numpy as np
   import pyuzlib

   pyuzlib.docs.pmsm.plot_operation_area(
       'docs/source/software/control/uz_pmsm/mh_prototype/fem_overaged_over_angle/machine_parameters.csv',
       v_dc_V=48.0,
       speed_rpm=1000.0,
       current_limit_A=12.0,
       modulation='svpwm',
       grid_points=80,
       torque_isoline_levels=np.arange(-4.0, 4.5, 0.5),
   )

.. plot::
  :caption: Maximum torque curves

   import numpy as np
   import pyuzlib

   pyuzlib.docs.pmsm.plot_max_torque_curve(
       'docs/source/software/control/uz_pmsm/mh_prototype/fem_overaged_over_angle/machine_parameters.csv',
       v_dc_V=48.0,
       speeds_rpm=np.linspace(0.0, 1500.0, 20),
       current_limit_A=12.0,
       modulation='svpwm',
   )
