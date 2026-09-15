.. _uz_per_wolfspeed_25kw_FM3_rev03:

===========================================
Wolfspeed Inverter 2L 25 kW Interface Rev03
===========================================

Rev03 is the first productive revision of the ``uz_per_wolfspeed_25kw_FM3`` interface PCB.
It interfaces the UltraZohm with the Wolfspeed ``CRD25DA12N-FMC`` inverter by replacing the original control card.

.. _uz_per_wolfspeed_rev03_function:

.. figure:: ../InterfaceBoardLayout.png

   Functional areas of the Rev03 interface PCB

Layout
======

The PCB is structured by functional areas as shown in :ref:`uz_per_wolfspeed_rev03_function`.

1. HFBR-1521Z/2521Z digital optical transmitters and receivers
2. RJ45 port for analog signal transmission
3. Driver stages for the optical links
4. TI THS4561 fully differential amplifier stages
5. Power section with TPS7A20 3.3 V LDO and REF35 voltage references
6. Samtec HSEC8 120-pin edge-card connector mating with the Wolfspeed inverter

Analog Signals
==============

The inverter-side analog signals are single-ended and are converted to fully differential signals for noise-robust transmission to the UltraZohm ADC board.
The interface scales the single-ended signals by a factor of ``1.5038`` (``10 / 6.65``) to match the inverter-side 3.3 V analog range to the 5 V input range of the UltraZohm ADC board.

The reported total sensing gain was measured experimentally and includes both the inverter-side measurement device and the interface board.
The bandwidth was determined theoretically from LTSpice simulations.

.. list-table::
   :header-rows: 1
   :widths: 25 25 30 20

   * - Signal
     - Source
     - Total measurement gain
     - UltraZohm ADC channel
   * - Phase current U
     - LEM LAH 50-P
     - 0.02417 V/A, bandwidth about 50 kHz
     - ``I_U`` / Ch1
   * - Phase current V
     - LEM LAH 50-P
     - 0.02417 V/A, bandwidth about 50 kHz
     - ``I_V`` / Ch2
   * - Phase current W
     - LEM LAH 50-P
     - 0.02417 V/A, bandwidth about 50 kHz
     - ``I_W`` / Ch3
   * - DC-link voltage
     - Non-isolated voltage divider
     - 0.003744 Vsec/Vprim, bandwidth about 7 kHz
     - ``V_DC`` / Ch4

Digital Signals
===============

Rev03 uses optical receivers for the UltraZohm-to-inverter PWM and gate-disable signals.
The inverter-to-UltraZohm overcurrent and temperature signals use optical transmitters.

The overcurrent detection signal is active low.
When an overcurrent event is detected, the signal goes low and the transmitter LED is off.
The default Wolfspeed overcurrent limits are set to approximately ``+/-79 A`` and can be adjusted with the reference resistors described in the Wolfspeed documentation.

.. list-table::
   :header-rows: 1
   :widths: 30 20 25 25

   * - Signal
     - Direction
     - Conditioning
     - Notes
   * - ``U_HS_PWM``, ``U_LS_PWM``, ``V_HS_PWM``, ``V_LS_PWM``, ``W_HS_PWM``, ``W_LS_PWM``
     - UltraZohm to inverter
     - Optical receivers
     - High-side and low-side PWM for three phases; dead time is generated in the UltraZohm.
   * - ``GD_DIS``
     - UltraZohm to inverter
     - Optical receiver
     - Global gate-driver disable signal.
   * - ``OC``
     - Inverter to UltraZohm
     - SN74HCS08DR AND logic and optical transmitter
     - Consolidated overcurrent signal from six comparator outputs.
   * - ``NTC_ISO``
     - Inverter to UltraZohm
     - Optical transmitter
     - Inverter-side temperature signal forwarded as a digital optical signal.

Testing
=======

Rev03 was tested up to 10 kW with an RL load consisting of a 14 Ohm resistor and a 1 mH inductor.

.. figure:: ../FinalSetup.png

   Integrated testing setup with RL load

Stable three-phase sinusoidal currents were measured using a Rohde & Schwarz MXO 5 series oscilloscope.

.. figure:: ../Testgraph.png

   Oscilloscope measurement at 100 kHz switching frequency with a 999 V / 8.33 A DC-link input

Mechanical Support
==================

A 3D-printed support stand was added to keep the board mechanically stable when plugged into the inverter.
The step file of the stand is available in the PCB repository.

.. figure:: ../stand.jpg
   :width: 60%
   :align: center

   Interface board with 3D-printed stand for mechanical stability

Software Used for Testing
=========================

The inverter was tested with the ``feature/wolfspeed_inverter_adapterboard`` branch of the `ultrazohm_sw <https://bitbucket.org/ultrazohm/ultrazohm_sw/src/>`_ repository.
The branch comparison is available `here <https://bitbucket.org/ultrazohm/ultrazohm_sw/branches/compare/feature%2Fwolfspeed_inverter_adapterboard%0Ddevelop#diff>`_.

Documents
=========

* :download:`Schematic Rev03 <../SCH_uz_per_wolfspeed_25kw_FM3_jlc_Rev03.pdf>`
* :download:`Bachelor thesis <../Thesis_Park_BA_UltraZohm_Wolfspeed_2L_Inverter_compressed.pdf>`
* :download:`Final presentation <../FinalPresentation.pdf>`
* :download:`Poster KI-Power Symposium <../Poster_UZandWolfspeedInterface.pptx>`
