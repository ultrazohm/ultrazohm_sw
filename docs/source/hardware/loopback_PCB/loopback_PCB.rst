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
Furthermore eight of the twelve gate signals are filtered and can be looped back to the ADC card (:ref:`Analog_LTC2311_16_v3`, :ref:`Analog_LTC2311_16_v2` ) via Ethernet connector. 

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

  Summary of netnames on connecotrs

.. list-table::
    :name: IPL1-115-01-L-D-K_table
    :widths: 5 45 45 45 
    :header-rows: 0

    * - **Pin**
      - **Digital voltage card**
      - **Loopback PCB**
      - **ADC card**
    * - 1
      - VIN
      - 24V
      - /
    * - 2
      - DIG_IO_P1
      - PWM_G1
      - AIN_A_P4
    * - 3
      - DIG_IO_P2
      - PWM_G7
      - AIN_B_P2
    * - 4
      - DIG_IO_P3
      - PWM_G2
      - AIN_A_P3
    * - 5
      - DIG_IO_P4
      - PWM_G9
      - /
    * - 6
      - DIG_IO_P5
      - PWM_G3
      - AIN_A_P2
    * - 7
      - DIG_IO_P6
      - PWM_G10
      - /
    * - 8
      - DIG_IO_P7
      - IO_P1
      - /
    * - 9
      - DIG_IO_P8
      - IO_P2
      - /
    * - 10
      - 15V
      - 15V
      - /
    * - 11
      - DIG_IO_P9
      - IO_P3
      - /
    * - 12
      - DIG_IO_P10
      - IO_P4
      - /
    * - 13
      - DIG_IO_P11
      - IO_P5
      - /
    * - 14
      - DIG_IO_P12
      - IO_P6
      - /
    * - 15
      - DIG_IO_P13
      - IO_P7
      - /

**IPL1-120-01-L-D-K**

.. figure:: summary_netnames_IPL120.png
  :align: right
  :width: 350

  Summary of netnames on connecotrs

.. list-table::
    :name: IPL1-120-01-L-D-K_table
    :widths: 5 45 45 45 
    :header-rows: 0

    * - **Pin**
      - **Digital voltage card**
      - **Loopback PCB**
      - **ADC card**
    * - 1
      - VIN
      - 24V
      - /
    * - 2
      - DIG_IO_P14
      - PWM_G4
      - AIN_A_P1
    * - 3
      - DIG_IO_P15
      - PWM_G8
      - AIN_B_P1
    * - 4
      - DIG_IO_P16
      - PWM_G5
      - AIN_B_P4
    * - 5
      - DIG_IO_P17
      - PWM_G11
      - /
    * - 6
      - DIG_IO_P18
      - PWM_G6
      - AIN_B_P3
    * - 7
      - DIG_IO_P19
      - PWM_G12
      - /
    * - 8
      - DIG_IO_P20
      - IO_P8
      - /
    * - 9
      - DIG_IO_P21
      - IO_P9
      - /
    * - 10
      - 3V3
      - 3V3
      - /
    * - 11
      - DIG_IO_P22
      - IO_P10
      - /
    * - 12
      - DIG_IO_P23
      - IO_P11
      - /
    * - 13
      - DIG_IO_P24
      - IO_P12
      - /
    * - 14
      - DIG_IO_P25
      - IO_P13
      - /
    * - 15
      - DIG_IO_P26
      - IO_P14
      - /
    * - 16
      - DIG_IO_P27
      - IO_P15
      - /
    * - 17
      - DIG_IO_P28
      - IO_P16
      - /
    * - 18
      - DIG_IO_P29
      - IO_P17
      - /
    * - 19
      - DIG_IO_P30
      - IO_P18
      - /
    * - 20
      - 5V
      - 5V
      - /


Documentation
-------------

A ZIP file with documentation can be downloaded :download:`here <docs.zip>`.
It contains:

 * SCH
 * ASM
 * BOM




