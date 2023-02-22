.. _dig_resolver_rev01:

======================
Digital Resolver Rev01
======================

.. image:: Digital_Resolver_rev01/Adapter_Card_Digital_Resolver.png
  :height: 500

Source
------

* `uz_d_resolver Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_resolver>`_


Interface and Functionality
---------------------------------------------------

The UltraZohm digital resolver adapter board features three channels of resolver interfaces, including excitation signal generation and serial interfaces.
Each channel is based on the AD2S1210 integrated-circuit.
The board features separated grounds for each channel of the excitation circuit (GND_EXC), which can be connected to the common logic ground via a resistor.
Each resolver channel can be configured with several pull-up and pull-down resistors. Default configuration sets:

* RES0 and RES1 to HIGH - max resolution of 16 bit
* RD to HIGH - output buffer disabled as SOE to LOW - Serial Interface is selected (this adapter card is only to be operated in serial configuration)
* Excitation Ground GND_EXC[1..3] and GND connected (Remove R50[A..C] to disconnect the grounds)
* Excitation Ground GND_EXC[1..3] connecting resistors to DSUB Connectors J2[A..C] NOT connected (Place 0 Ohm at R3, R4, R5 and R51 each[A..C] to connect grounds)
* N_SAMPLE to HIGH (also see known issues section for this)

.. note:: The clock speed of the Clock in Rev01 is 8.192 MHz, which is relevant to the Specifications of the AD2S1210 IC

.. note:: As the resolver only operates with the 16 bit resolution in the board's default configuration, the measurable rotational speed is limited to 125 rounds per second (rps) (equals :math:`7500\frac{1}{min}`) with a clock speed of 8.192 MHz. For higher speeds the resolution has to be lowered. This affects RES0 and RES1 resistor configuration as well as ip-core driver configuration.

With the Signals A0 and A1 the resolver`s operation mode can be configured. This is done through the ip-core driver:

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

* Determine correct placement options for correct function (Default is 16-bit resolution) and one common GND for all channels
* Program CPLD with proper firmware, `uz_d_resolver CPLD program <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/uz_d_resolver/>`_. See :ref:`label_cpld_programming` for details.

Known issues
------------

.. warning:: N_SAMPLE is pulled to HIGH using 5V on Rev01. It should be 3V3 to ensure safe operation of the AD2S1210 IC. This has been fixed for Rev02. Before first use of Rev01 boards, carefully check, if resistors R14[A..C] are not placed.

Compatibility 
-------------

* This Board is compatible with slots D1-D5

Pinout
------

.. image:: Digital_Resolver_rev01/Pinout_Adapter_Card_Digital_Resolver_edited.png
  :height: 300

.. image:: Digital_Resolver_rev01/Pinout2_Adapter_Card_Digital_Resolver_edited.png
  :height: 700

References
""""""""""

* :download:`Schematic Rev01 <Digital_Resolver_rev01/SCH_UZ_D_Resolver_Default_Rev01.pdf>`
* :download:`Datasheet AD2S1210 IC <Digital_Resolver_rev01/AD2S1210.pdf>`
* :ref:`dig_encoder_v1`
* :ref:`label_cpld_programming`

Designed by 
"""""""""""""""
Martin Bauer (THN), Eyke Aufderheide (TUM) in 02/2022
based on design by Thomas Effenberger (TUM)