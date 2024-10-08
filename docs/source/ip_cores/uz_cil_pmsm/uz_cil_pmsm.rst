.. _uz_cil_pmsm:

========
CIL PMSM
========

General description
===================

To use the CIL method for controller development for PMSM, as described in [[#uz_cil_paper1]_][[#uz_cil_paper2]_], several IP-Cores have been created.
A general overview of the available IP-Cores is given here.
Links to the individual Docs pages can be found below, as well as examples for the usage.
Models are available for six-phase and nine-phase PMSM.

.. note:: 

   The multiphase CIL projects model machines with isolated neutral points, meaning 2N and 3N configurations for six-phase and nine-phase CIL.
   Changing the neutral configuration is not possible at this moment.

General setup
=============

.. figure:: skizze.jpg

    Example CIL setup


The "X" for the transformation and PMSM IP-Core serves as a placeholder and the respective IP-Cores for the number of phases should be used.
Individual documentation of the IP-Cores is linked below.

..  toctree::
    :maxdepth: 1
    :glob:
    
    uz_pmsm_model_multiph_dq/uz_pmsm_model_multiph_dq
    uz_vsd_transformation/uz_vsd_transformation
    ../uz_inverter_3ph/uz_inverter_3ph

Examples
========

To use the CIL, the following examples have been created to show the necessary steps in Vivado and Vitis.
Depending on the use case, some steps might differ.

..  toctree::
    :maxdepth: 1
    :glob:
    
    uz_cil_examples/uz_6ph_cil_example


References
==========

.. [#uz_cil_paper1] E. Liegmann, T. Schindler, P. Karamanakos, A. Dietz and R. Kennel, "UltraZohm—An Open-Source Rapid Control Prototyping Platform for Power Electronic Systems," 2021 International Aegean Conference on Electrical Machines and Power Electronics (ACEMP) & 2021 International Conference on Optimization of Electrical and Electronic Equipment (OPTIM), 2021, pp. 445-450, doi: 10.1109/OPTIM-ACEMP50812.2021.9590016.
.. [#uz_cil_paper2] V. Hoppe, T. Schindler, M. Hoerner, A. Dietz and R. Kennel, "On-Chip Simulation of a Nine-Phase Electrical Drive and Power Electronics for Rapid Control Prototyping Applications," 2022