.. _torque_box:

================
Torque Box PCB
================
	   

.. figure:: torque_box.jpg
   :width: 60%

   Torque Box PCB

Source
******

- `Torque box PCB repository <https://bitbucket.org/ultrazohm/uz_per_torque_box/>`_

Revisions
*********

Rev01

General description
*******************

This PCB is designed to supply external torque sensor `Burster 8656 Torque Sensor <https://www.burster.com/en/torque-sensors/p/detail/8656/>`_  and send the signals to the :ref:`Analog_LTC2311_16` Card
The supply is taken from the voltage interface connector of an :ref:`Analog_LTC2311_16` board.
The torque signal (+-10V) is reduced to a level of +-5V and low-pass filtered. 
The torque signal is connected to ADC1 channel of LTC2311 and the remaining 3 Channels ADC2-ADC 4 can still be used via the Application Input Port
.. _ADC_Loopback_Layout:

.. figure:: uz_per_torque_functional.svg

  Functional areas of the uz per torque pcb

Layout
------

The PCB is structured by functional areas as shown in the :numref:`ADC_Loopback_Layout` on the right.


1. Double Ethernet connector to ADC Card
2. Voltage reduction to +-5V and low-pass filtering.
3. Supply voltage 24V from ADC Card with Samtec (3V3, 5V, 15V, 24V)
4. Connector to the Torque Sensor D-Sub 15  

Downloads
*********

Rev01

 * :download:`Schematics <SCH_uz_per_torque_box_Default_Rev01.pdf>`
 * :download:`Bill of Material <BOM_JLC-uz_per_torque_box(Default)_JLC_Upload.xlsx>`


Designer
********

Designed by Michael Hoerner (TH Nürnberg), 07/2024
