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

This PCB is designed to measure voltages up to 60V or 1000V on four channels depending on the configuration of the voltage dividers. 
The supply can be taken from the voltage interface connector of an :ref:`Analog_LTC2311_16` board (24V). Alternatively, an external power supply with 7V to 65V can be used.
The measurement signals are reduced to a level of +-5V and low-pass filtered. 
The measurement signals from all four channels are routed to an Ethernet connector and can be connected to an ADC channel of :ref:`Analog_LTC2311_16`.

Layout
------

.. _voltage_meas_box_function:

.. figure:: voltage_meas_box_altium.jpg
   :width: 90%

   Functional areas of the voltage measurement box frontside


.. _voltage_meas_box_function_back:

.. figure:: voltage_meas_box_altium_back.jpg
   :width: 90%

   Functional areas of the voltage measurement box backside

The PCB is structured in functional areas as shown in Fig. :numref:`voltage_meas_box_function` and :numref:`voltage_meas_box_function_back`.

1. 4mm jack connectors for voltage measurement. V+ and V- for each channel.
2. Ethernet connector to the ADC adapter card :ref:`Analog_LTC2311_16`.
3. Isolation of measurement signal and signal adaption to +- 5V and low pass filtering.
4. Power supply with 7V to 65V input range. Either use connectors J1, J2 (IPL1-102-02-L-D-K, Cable: ``MMSD-02-xx-x-xx.xx-x-x``) or J4 (TSW-102-07-F-S).
5. Voltage dividers for up to 1000V measurement range.

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
*************************
A 3D-printable housing is available for the voltage measurement PCB. 
The assembly with all necessary parts, including a bill of materials (BOM), is shown below. The PCB can be used without the housing, 
but the setup is more rugged and clean with the housing.

.. figure:: voltage_box_assembly.png
  :width: 80%

  Assembly drawing of the torque_box


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
