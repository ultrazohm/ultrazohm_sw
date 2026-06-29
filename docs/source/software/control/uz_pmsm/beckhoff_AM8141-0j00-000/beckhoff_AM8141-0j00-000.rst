========================
beckhoff AM8141-0j00-000
========================

The measured dataset in ``measured_psi_dq_averaged_800_rpm/flux_map.csv`` can be plotted directly with ``pyuzlib``.

C usage
=======

.. code-block:: c

   #include "uz_PMSM_config.h"

   /* 800 RPM dataset — measured over a larger current range, generally preferred: */
   uz_PMSM_t motor = UZ_PMSM_BECKHOFF_AM8141_0J00_000_MEASURED_PSI_DQ_AVERAGED_800_RPM_INIT;
   uz_PMSM_config_assert(motor);

   /* 400 RPM dataset — alternative if needed: */
   uz_PMSM_t motor = UZ_PMSM_BECKHOFF_AM8141_0J00_000_MEASURED_PSI_DQ_AVERAGED_400_RPM_INIT;
   uz_PMSM_config_assert(motor);
``measured_psi_dq_averaged_800_rpm.csv`` is measured at 800 rpm and -800 rpm, where t he flux map is averaged for each operating point to counteract the influence of the iron losses.


Matplotlib
==========


.. plot::
  :caption: Flux map measured at 800 rpm

   import pyuzlib
   pyuzlib.docs.pmsm.plot_flux_map('docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/measured_psi_dq_averaged_800_rpm/flux_map.csv')

.. plot::
  :caption: Flux map measured at 400 rpm

   import pyuzlib
   pyuzlib.docs.pmsm.plot_flux_map('docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/measured_psi_dq_averaged_400_rpm/flux_map.csv')

Plotly
======

.. plotly::
  :iframe-width: 100%
  :caption: Flux map Plotly

   import pyuzlib
   pyuzlib.docs.pmsm.plot_flux_map_plotly('docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/measured_psi_dq_averaged_800_rpm/flux_map.csv')

Coefficients
============

.. plot::
  :caption: Linear flux model compared with measured flux-map data

   import pyuzlib

   pyuzlib.docs.pmsm.plot_linear_flux_model_comparison(
       'docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/measured_psi_dq_averaged_800_rpm/flux_map.csv',
       grid_points=20,
   )


Operating area
==============

.. plot::
  :caption: Operating area at rated speed

   import numpy as np
   import pyuzlib

   pyuzlib.docs.pmsm.plot_operation_area(
       'docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/measured_psi_dq_averaged_800_rpm/machine_parameters.csv',
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
       'docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/measured_psi_dq_averaged_800_rpm/machine_parameters.csv',
       v_dc_V=48.0,
       speeds_rpm=np.linspace(0.0, 1500.0, 20),
       current_limit_A=12.0,
       modulation='svpwm',
   )
