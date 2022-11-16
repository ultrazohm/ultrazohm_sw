.. _uz_cil_pmsm:

========
CIL PMSM
========

General description
===================

To use the CIL method for controller development for PMSM, as described in [[#uz_cil_paper1]_][[#uz_cil_paper2]_], several IP-Cores have been created.
A general overview over the available IP-Cores is given here.
Links to the individual Docs pages can be found below, as well as examples for the usage.
Models are available for sixphase and ninephase PMSM.

General setup
=============

.. figure:: skizze.pdf

   Necessary IP-Cores for CIL

The "X" for the transfromation and pmsm IP-Core serves as placeholder and the respective IP-Cores for the amount of phases should be used.
Individual documentation of the IP-Cores is linked below.

Machine model: :ref:`uz_pmsm_model_9ph_dq`

Transformation: :ref:`uz_pmsm9ph_transformation`

Inverter: :ref:`uz_inverter_3ph`

Flip Flop: :ref:`uz_rs_flip_flop`

Examples
========

Insert Links to extra docs pages, for example:

threephase CIL

Multiphase CIL

References
==========

.. [#uz_cil_paper1] E. Liegmann, T. Schindler, P. Karamanakos, A. Dietz and R. Kennel, "UltraZohm—An Open-Source Rapid Control Prototyping Platform for Power Electronic Systems," 2021 International Aegean Conference on Electrical Machines and Power Electronics (ACEMP) & 2021 International Conference on Optimization of Electrical and Electronic Equipment (OPTIM), 2021, pp. 445-450, doi: 10.1109/OPTIM-ACEMP50812.2021.9590016.
.. [#uz_cil_paper2] V. Hoppe, T. Schindler, M. Hoerner, A. Dietz and R. Kennel, "On-Chip Simulation of a Nine-Phase Electrical Drive and Power Electronics for Rapid Control Prototyping Applications," 2022