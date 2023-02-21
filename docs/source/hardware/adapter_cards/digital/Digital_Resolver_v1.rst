.. _dig_resolver_v1:

==========================
Digital Resolver 1v00
==========================

.. image:: Digital_Resolver_v1/Adapter_Card_Digital_Resolver.png
  :height: 500

Source
------

* `uz_d_resolver Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_resolver>`_


Interface and Functionality
---------------------------------------------------

The Ultrazohm digital resolver Board features three Channels of Resolver controllers with excitation signal generation and serial interfaces and is built for flexible testing. 
The Board features separated Grounds for the Excitation Circuits (GND_EXC), which can be connected to the general Ground via Jumpers.
Each Resolver can be configured with several pull-up and pull-down resistors and jumpers. Default configuration sets:

* RES0 and RES1 to HIGH - max resolution of 16 bit
* RD to HIGH - output buffer disabled as SOE to LOW - Serial Interface is selected (this adapter card is only to be operated in serial configuration)
* Excitation Ground GND_EXC[1..3] and GND connected
* Excitation Ground GND_EXC[1..3] jumpers to DSUB Connectors J2[A..C] NOT connected
* N_SAMPLE to HIGH

.. note:: The clock speed of the Clock in Rev00 is 8.192 MHz, which is relevant to the Specifications of the AD2S1210 IC

.. note:: As the resolver only operates with the 16 bit resolution in the boards default configuration, it is limited to 125 rps (:math:`7500\frac{1}{min}`) with a clock speed of 8.192 MHz

With the Signals A0 and A1 the resolver`s operation Mode can be configured:

* A0 to HIGH and A1 to HIGH = Normal model - position output
* A0 to LOW and A1 to HIGH = Normal model - velocity output
* A0 to HIGH and A1 to LOW = Reserved (not used)
* A0 to LOW and A1 to LOW = Configuration Mode

In position and velocity mode the corresponding data can be obtained directly by toggling the clock line without sending the register addresses first. 
Further access to the devices registers and configurations is possible in the configuration mode. 
In this mode, changing the excitation frequency or reading back position and velocity data is possible.
This is equivalent to :ref:`dig_encoder_v1`.


.. figure:: encoder_v1/Position_Plot.png
  :width: 1000
  
  Position Data from Resolver
  
.. figure:: encoder_v1/Velocity_Plot2.png
  :width: 1000
  
  Velocity Data from Resolver

When communicating with the controller, attention has to be payed on the SPI mode. The correct one is MODE1 with clock polarity idle low and clock phase one meaning falling edge.

.. figure:: encoder_v1/Resolver_Data_Transmission_Normal_Mode.png
  :width: 1000
  
  Data Transmission in normal mode (position or velocity), yellow: MISO, blue: FSYNC, red: CLK

.. figure:: encoder_v1/Resolver_Data_Transmission_Config_Mode.png
  :width: 1000
  
  Data Transmission in config mode, yellow: MISO, blue: FSYNC, red: CLK

Before first use
----------------

* Determine correct placement options for correct function
* Program CPLDs with firmware, see :ref:`label_cpld_programming` for details

Known issues
------------

* N_SAMPLE is pulled to HIGH using 5V on Rev00. It should be 3V3 to ensure safe operation of the AD2S1210 IC. This has been chaned for Rev01.

Compatibility 
-------------

* This Board version is compatible with slots D1-D5

Pinout
------

.. image:: Digital_Resolver_v1/Pinout_Adapter_Card_Digital_Resolver_edited.png
  :height: 300

.. image:: Digital_Resolver_v1/Pinout2_Adapter_Card_Digital_Resolver_edited.png
  :height: 700

References
""""""""""

* :download:`Schematic 1v01 <Digital_Resolver_v1/SCH_UZ_D_Resolver_Default_Rev01.pdf>`
* :download:`Datasheet AD2S1210 IC <Digital_Resolver_v1/AD2S1210.pdf>`
* :ref:`dig_encoder_v1`
* :ref:`label_cpld_programming`

Designed by 
"""""""""""""""
Martin Bauer (THN), Eyke Aufderheide (TUM) in 02/2022
based on design by Thomas Effenberger (TUM)