=============
Loopback PCB
=============

..	toctree::
	:maxdepth: 2
	   
Designed by Nina Diringer (TH Nürnberg), 07/2022

.. figure:: sphx_glr_loopback_pcb.jpg
   :width: 45%

   Loopback PCB

Revisions
*********
insert revisions here

General description
********
This PCB is used for the :ref:`adc_loopback` tutorial. 
The LEDs indicate the state of the signals from the digital voltage card (:ref:`digitalVoltage`). 
Furthermore eight of the twelve gate signals are filtered and can be looped back to the ADC card (:ref:`Analog_LTC2311_16_v3`, :ref:`Analog_LTC2311_16_v2` ) via Ethernet connector. 

.. figure:: sphx_glr_pcb_functional_areas.png
  :align: right
  :width: 350

  Functional areas

Layout
------

The PCB is structured by functional areas as shown in the figure on the right.

#. Connectors to digital adapter card (hardware/adapter_cards/adapter_cards)
#. Pinheader for measuring all signals
#. Voltage state indicated by LEDs 
#. State of gate signals indicated by LEDs
#. State of remaining IOs indicated by LEDs
#. Low pass filter for filtering the gate signals
#. Ethernet connector

Documentation
-------------

A ZIP file with complete documentation can be downloaded here *insert link* .

It contains:
  - DOC
  - ASM
  - BOM






