.. _uz_VSD_9ph_fault_main:

========================================================
9 phase VSD open-phase-fault (OPF) detection and control
========================================================

Introduction
============

Multi-phase machines have the advantage to be fault tolerant.
This means, they can be operated under faulty conditions, such as open phase faults (OPF).
To achieve this, several approaches are available.
For this implementation, :ref:`uz_VSD_6ph_FD_control` was used as a basis.

The intended control structure is shown in the following figure.
To control subsystem harmonics, resonant controllers are used (not mandatory) and for post-fault optimization PI-controllers are used.

.. figure:: fault_control.png

    Controller structure


Components
==========

..	toctree::
    :maxdepth: 2
    :glob:
  
    *

Reference
=========

This module is based on :ref:`uz_VSD_6ph_FD_control` and the references are applicable here as well.
Furthermore, the implementation on nine-phase PMSM is analysed in "Feldorientierte Regelung und fehlertoleranter Betrieb einer neunsträngigen permanentmagneterregten Synchronmaschine", Master's Thesis, TH Nürnberg, 2023, Valentin Hoppe.