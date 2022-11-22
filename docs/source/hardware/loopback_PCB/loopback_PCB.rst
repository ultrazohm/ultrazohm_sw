=============
Loopback PCB
=============

..	toctree::
	:maxdepth: 2
	   
Designed by Nina Diringer (TH Nürnberg), 07/2022

.. figure:: Loopback_PCB.png
   :width: 37%

   Loopback PCB

Revisions
*********
Rev01

General description
*******************
This PCB is part of the :ref:`adc_loopback` tutorial. 

The LEDs indicate the state of the signals from the digital voltage card (:ref:`digitalVoltage`). 
Furthermore eight of the signals (as documented in the section *Signal description* below) are first filtered and then output via the Ethernet connector to the ADC card (:ref:`Analog_LTC2311_16_v3`, :ref:`Analog_LTC2311_16_v2` ). 

.. _ADC_Loopback_Layout:

.. figure:: loopback_pcb_functional_areas.png
  :align: right
  :width: 355

  Functional areas of the Loopback PCB

Layout
------

The PCB is structured by functional areas as shown in the :numref:`ADC_Loopback_Layout` on the right.

1. Connectors to the Digital Voltage Card
   
   * Connector 1: IPL1-115-01-L-D-K, top (green)
   * Connector 2: IPL1-120-01-L-D-K, left (blue)
  
2. Pin header for measuring all signals
3. Supply voltage state indicated by LEDs (3V3, 5V, 15V, 24V)
4. State of gate signals indicated by LEDs
5. State of remaining IOs indicated by LEDs
6. Low pass filter for filtering the gate signals
7. Ethernet connector to ADC Card
   

Signal description
------------------
Since the matching of the signal names between the PCBs used in the Loopback Tutorial is not intuitive, 
the following table matches the signal names of the Digital Voltage Card to the signal names on the Loopback PCB and the ADC card. Additionally, the name of the corresponding LED as marked on the Loopback PCB is given. 

Connector 1: IPL1-115-01-L-D-K
______________________________

.. csv-table:: Signal matching of connector IPL1-115-01-L-D-K
  :file: IPL115.csv
  :widths: 5 15 15 15 15
  :header-rows: 1

.. figure:: net_names_dvc_IPL115.png
  :width: 325

  Netnames of connector 1 (IPL1-115-01-L-D-K) on Digital voltage card

.. figure:: net_names_PCB_IPL115.png
  :width: 325

  Netnames of connector 1 (IPL1-115-01-L-D-K) on Loopback PCB 

.. figure:: net_names_dac.png
  :width: 325

  Netnames of Ethernet connector on ADC card

Connector 2: IPL1-120-01-L-D-K
______________________________

.. csv-table:: Signal matching of connector IPL1-120-01-L-D-K
  :file: IPL120.csv
  :widths: 5 15 15 15 15
  :header-rows: 1

.. figure:: net_names_dvc_IPL120.png
  :width: 325

  Netnames of connector 2 (IPL1-120-01-L-D-K) on Digital voltage card

.. figure:: net_names_PCB_IPL120.png
  :width: 325

  Netnames of connector 2 (IPL1-120-01-L-D-K) on Loopback PCB 

.. figure:: net_names_dac.png
  :width: 325

  Netnames of Ethernet connector on ADC card

.. hint::

    To sum this up: The signals on Pin 2 to Pin 7 on both connectors (IPL1-115-01-L-D-K & IPL1-120-01-L-D-K) are used for the gate signals in the Loopback tutorial. P2 being the gate signal for the first high side switch, P3 for the corresponding low side switch, P4 for the second high side switch and so on.
    All Gate signals for the high side switches (Pin 2, Pin 4, Pin 6) and the first for the low side switches (Pin 3) are filtered and can be read back by the ADC card. 

Documentation
*************

Rev01
 * :download:`Schematics <SCH_UZ_PER_loopback_tutorial_[No Variations]_Rev01.PDF>`
 * :download:`Bill of Material <BOM_JLC_UZ_PER_loopback_tutorial_[No Variations]_Rev01.xlsx>`
 * :download:`Assembly Drawing <ASM_UZ_PER_loopback_tutorial_[No Variations]_Rev01.PDF>`