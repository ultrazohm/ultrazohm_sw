.. _uz_per_voltage_measurement_box:

=======================
Voltage measurement box
=======================
      
.. figure:: voltage_meas_box.jpg
   :width: 80%

   Voltage measurement PCB


Source
******

- `Voltage measurement box PCB repository <https://bitbucket.org/ultrazohm/uz_per_voltage_measurement_box/>`_

General description
*******************

This PCB is designed to measure voltages up to 60V or 1000V on four channels, depending on the configuration of the voltage dividers. 
The supply can be taken from the voltage interface connector of an :ref:`Analog_LTC2311_16` board (24V). Alternatively, an external power supply with a voltage range of 7V to 65V can be used.
The measurement signals are reduced to a level of +-5V and low-pass filtered. 
The measurement signals from all four channels are routed to an Ethernet connector and can be connected to an ADC channel of :ref:`Analog_LTC2311_16`.

Layout
------

.. _voltage_meas_box_function_top:

.. figure:: voltage_meas_box_altium.jpg
   :width: 45%
   :align: left

   Functional areas of the voltage measurement box (top side)

.. _voltage_meas_box_function_bottom:

.. figure:: voltage_meas_box_altium_back.jpg
   :width: 45%
   :align: right

   Functional areas of the voltage measurement box (bottom side)


The PCB is structured in functional areas as shown in :numref:`voltage_meas_box_function_top` and :numref:`voltage_meas_box_function_bottom`.

1. 4mm jack connectors for voltage measurement. V+ and V- for each channel.
2. Ethernet connector to the ADC adapter card :ref:`Analog_LTC2311_16`.
3. Isolation of measurement signal and signal adaptation to +/- 5V and low-pass filtering.
4. Power supply with 7V to 65V input range. Either use connectors J1, J2 (IPL1-102-02-L-D-K, Cable: ``MMSD-02-xx-x-xx.xx-x-x``) or J4 (TSW-102-07-F-S).
5. Voltage dividers for up to 1000V measurement range.

Power supply
------------

.. _power_supply:

.. figure::  power_supply.jpg
   :width: 50%

   Pins for VIN are marked in blue and GND in orange. Connectors are marked in yellow. Cable should be configured accordingly. 

The PCB can be powered in two ways:

1.  J1,J2: VIN/GND from the :ref:`Analog_LTC2311_16` card with a manufactured power supply cable (Type ``MMSD-02-xx-x-xx.xx-x-x`` to ``MMSD-08-xx-x-xx.xx-x-x``). Alternatively to external power source. 


+-------------------------------------------------+-----------------------------------------------+
| .. figure:: connector_LTC2311.jpg               | .. figure:: pins-LTC2311.jpg                  |
|    :width: 75%                                  |    :width: 75%                                |
|                                                 |                                               |
|    Connector on the LTC2311_16 card for         |    Physical pins on the                       |
|    power supply to the voltage measurement      |    :ref:`Analog_LTC2311_16` card.             |
|    box.                                         |                                               |
|                                                 |                                               |
|    .. note:: Use pins 2 and 10 as return ground!|                                               |
+-------------------------------------------------+-----------------------------------------------+

2. J4: Connect external power supply to pins.

Pinout
------

The pairs of the RJ45 Ethernet connector map to the voltage measurement channels as follows:

=========  =======    ==========================    ===================================
Connected                         Pin on RJ45       (:ref:`RJ45-Belegung <rj45pinout>`)                         
---------  -------    -----------------------------------------------------------------
 ADC       Channel      :math:`V_\mathrm{in,p}`       :math:`V_\mathrm{in,n}`
=========  =======    ==========================    ===================================
ADC 1      1              7                                8                     
ADC 2      2              4                                5                     
ADC 3      3              3                                6                     
ADC 4      4              1                                2                     
=========  =======    ==========================    ===================================

Variants
--------

The PCB can be ordered in two variants:

* 60V Version with 2x 150k and 3x 0R resistors per voltage divider leg
  
  - measurement gain in DB: -23.67 dB
  - cutoff frequency: 2kHz

.. _voltage_meas_box_gain_60V:

.. figure::  60V_gain.jpg
   :width: 90%

   Verification of gain and cutoff frequency for 60V version

* 1000V Version with 5x 1M resistors per voltage divider leg

  - measurement gain in DB: -48.98 dB

Assembly and Connection
***********************

A 3D-printable housing is available for the voltage measurement PCB. 
The assembly with all necessary parts, including a bill of materials (BOM), is shown below. The PCB can be used without the housing, 
but the setup is more rugged and clean with the housing.

.. figure:: voltage_box_assembly.png
  :width: 80%

  Assembly drawing of the voltage measurement box


.. csv-table:: BOM for voltage_measurement_box assembly 
   :file: voltage_box_assembly_bom.csv
   :widths: 25 150 100 30 100
   :header-rows: 1


Downloads
*********
* :download:`Schematics 60V <uz_per_voltage_measurement.pdf>`
* :download:`BOM 60V <BOM_JLC_uz_per_voltage_measurement_60V_Rev01.xlsx>`
* :download:`Schematics 1000V <uz_per_voltage_measurement.pdf>`
* :download:`Housing body STL file <housing_body.stl>`
* :download:`Housing cover STL file <housing_cover.stl>`


Designer
********

Designed by Eyke Aufderheide (TU München), 07/2025
