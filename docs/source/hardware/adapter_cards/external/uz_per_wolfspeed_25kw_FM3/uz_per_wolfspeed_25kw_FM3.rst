.. _uz_per_wolfspeed_25kw_FM3:

========================================
Wolfspeed Inverter 2L 25 kW Interface
========================================

The ``uz_per_wolfspeed_25kw_FM3`` interface PCB connects the UltraZohm to the Wolfspeed
`CRD25DA12N-FMC 25 kW Three-Phase Inverter <https://www.wolfspeed.com/products/power/reference-designs/crd25da12n-fmc/>`_.
It plugs into the inverter in place of the Texas Instruments control card and adapts the inverter signals to the UltraZohm analog and digital interfaces.

Use this page as the entry point and select the page that matches the hardware revision in use.

Revisions
=========

.. toctree::
   :maxdepth: 1

   rev03/rev03
   rev04/rev04

Revision History
================

.. list-table::
   :header-rows: 1
   :widths: 15 25 60

   * - Revision
     - Status
     - Notes
   * - Rev01
     - Not functional
     - Early hardware revision; no productive documentation in this repository.
   * - Rev02
     - Not functional
     - Early hardware revision; no productive documentation in this repository.
   * - Rev03
     - Productive
     - First functional and documented revision. Tested up to 10 kW with an RL load.
   * - Rev04
     - Productive revision
     - Adds gate-enable derived fan control, overcurrent latch/reset logic, an optical temperature PWM output, and further hardware fixes.

Common Function
===============

The board adapts the following signal groups between the Wolfspeed inverter and the UltraZohm:

* Three phase-current measurements and the DC-link voltage measurement are converted from single-ended inverter-side signals to fully differential RJ45 signals for the UltraZohm ADC board.
* Six PWM gate signals are transmitted from the UltraZohm to the inverter through optical receivers.
* Inverter-side fault and status signals are transmitted back to the UltraZohm through optical transmitters.
* The global gate-driver disable signal is driven from the UltraZohm.

General Notes
=============

* Check the exact PCB revision before wiring the board or using a saved FPGA/Vitis project.
* The schematics state that the interface is for the Wolfspeed ``CRD25DA12N-FMC 25 kW inverter Rev2.0``.
* Rev03 and Rev04 use the same basic analog measurement concept, but Rev04 changes digital behavior around gate enable, overcurrent handling, fans, and temperature feedback.
* The Samtec HSEC8 edge-card connector numbering differs from the Texas Instruments control-card naming. Verify the schematic pinout when debugging connector-level issues.
* The board is mechanically long when plugged into the inverter. Use the matching support concept from the hardware repository or an equivalent mechanical support.

Documents and Links
===================

* `PCB repository uz_per_wolfspeed_25kw_FM3 <https://bitbucket.org/ultrazohm/uz_per_wolfspeed_25kw_fm3/src/main/>`_
* Wolfspeed 25 kW Three-Phase Inverter `CRD25DA12N-FMC <https://www.wolfspeed.com/products/power/reference-designs/crd25da12n-fmc/>`_
* TI E2E `thread on HSEC8 pinout <https://e2e.ti.com/support/microcontrollers/arm-based-microcontrollers-group/arm-based-microcontrollers/f/arm-based-microcontrollers-forum/1486750/tmdshsecdock-edge-connector-hsec8-160-wrong-orientation-and-position-of-pin-1/>`_
* Bachelor thesis :download:`download here <Thesis_Park_BA_UltraZohm_Wolfspeed_2L_Inverter_compressed.pdf>`
* Final presentation :download:`download here <FinalPresentation.pdf>`
* Poster KI-Power Symposium :download:`download here <Poster_UZandWolfspeedInterface.pptx>`

Designer
========

Rev03 was designed by S. Park. Rev04 was designed by S. Park and M. Hoerner.
