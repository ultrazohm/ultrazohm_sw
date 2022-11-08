=============
Loopback PCB
=============

..	toctree::
	:maxdepth: 2
	   
Designed by Nina Diringer (TH Nürnberg), 07/2022

.. figure:: sphx_glr_loopback_pcb.png
   :width: 45%

   Loopback PCB

Revisions
*********
Rev01

General description
*******************
This PCB is used for the :ref:`adc_loopback` tutorial. 
The LEDs indicate the state of the signals from the digital voltage card (:ref:`digitalVoltage`). 
Furthermore eight of the signals (as documented in the section *Signal description* below) are filtered and can be looped back to the ADC card (:ref:`Analog_LTC2311_16_v3`, :ref:`Analog_LTC2311_16_v2` ) via Ethernet connector. 

.. figure:: sphx_glr_pcb_functional_areas.png
  :align: right
  :width: 350

  Functional areas

Layout
------

The PCB is structured by functional areas as shown in the figure on the right.

#. Connectors to :ref:`digital_adapter_boards`
#. Pinheader for measuring all signals
#. Supply voltage state indicated by LEDs 
#. State of gate signals indicated by LEDs
#. State of remaining IOs indicated by LEDs
#. Low pass filter for filtering the gate signals
#. Ethernet connector to ADC card

Signal description
------------------
*work in progress, needs better description* As the matching of the signal names between the PCBs used in the Loopback Tutorial is not intuitive, 
the following table gives an overview which signal from the Digital Voltage Card is looped back to which signal on the Analog Adapter card via the Loopback PCB.

.. hint::

    The signals on P2 to P7 are the gate signals. P2 being the gate signal for the first high side switch, P3 for the corresponding low side switch, P4 for the second high side switch and so on.
    All Gate signals for the High Side Switches and the First two for the low side switches are filtered and read back by the ADC card. 

**IPL1-115-01-L-D-K**

.. figure:: summary_netnames_IPL115.png
  :align: right
  :width: 350

  Summary of netnames on connectors

.. csv-table:: table
  :file: IPL115.csv
  :widths: 5 15 15 15
  :header-rows: 1


**IPL1-120-01-L-D-K**

.. figure:: summary_netnames_IPL120.png
  :align: right
  :width: 350

  Summary of netnames on connectors

.. csv-table:: table
  :file: IPL120.csv
  :widths: 5 15 15 15
  :header-rows: 1

Documentation
-------------

Rev01
 * :download:`Schematics <SCH_UZ_PER_loopback_tutorial_[No Variations]_Rev01.PDF>`
 * :download:`Bill of Material <BOM_JLC_UZ_PER_loopback_tutorial_[No Variations]_Rev01.xlsx>`
 * :download:`Assembly Drawing <ASM_UZ_PER_loopback_tutorial_[No Variations]_Rev01.PDF>`




