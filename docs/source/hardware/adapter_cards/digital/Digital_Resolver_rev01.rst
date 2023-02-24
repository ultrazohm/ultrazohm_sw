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
---------------------------

The UltraZohm digital resolver adapter board features three channels of resolver interfaces, including excitation signal generation and serial interfaces.
Each channel is based on the AD2S1210 integrated-circuit.
The board features separated grounds for each channel of the excitation circuit (GND_EXC), which can be connected to the common logic ground via a resistor.
Each resolver channel can be configured with several pull-up and pull-down resistors. Default configuration sets:

* ``RES0`` and ``RES1`` to ``HIGH`` - max resolution of 16 bit
* ``RD`` to ``HIGH`` - output buffer disabled as ``SOE`` to LOW - Serial Interface is selected (this adapter card is only to be operated in serial configuration)
* Excitation Ground ``GND_EXC[1..3]`` and ``GND`` connected (Remove ``R50[A..C]`` to disconnect the grounds)
* Excitation Ground ``GND_EXC[1..3]`` connecting resistors to DSUB Connectors ``J2[A..C]`` NOT connected (Place 0 Ohm at ``R3``, ``R4``, ``R5`` and ``R51`` each ``[A..C]`` to connect grounds)
* ``N_SAMPLE`` to HIGH (also see known issues section for this)

.. note:: The clock speed of the Clock in Rev01 is 8.192 MHz, which is relevant to the Specifications of the AD2S1210 IC

.. note:: As the resolver only operates with the 16 bit resolution in the board's default configuration, the measurable rotational speed is limited to 125 rounds per second (rps) (equals :math:`7500\frac{1}{min}`) with a clock speed of 8.192 MHz. For higher speeds the resolution has to be lowered. This affects RES0 and RES1 resistor configuration as well as ip-core driver configuration.

With the Signals A0 and A1 the resolver`s operation mode can be configured. This is done through the ip-core driver:

* ``A0`` to LOW and ``A1`` to LOW = Normal mode - position output
* ``A0`` to LOW and ``A1`` to HIGH = Normal mode - velocity output
* ``A0`` to HIGH and ``A1`` to LOW = Reserved (not used)
* ``A0`` to HIGH and ``A1`` to HIGH = Configuration Mode

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

.. warning:: There are two different CPLD programms in the ``cpld_lattice`` repository for ``uz_d_resolver``. One for usage of the adapter board in slots D1 to D4 (sub-folder: ``digital_D1_to_D4``). And a special one for usage in slot D5 (sub-folder: ``digital_D5``). Due to the limited number of pins at D5 there are only two resolver channels available (``Ch A/1`` and ``Ch B/2``).

Known issues
------------

.. warning:: N_SAMPLE is pulled to HIGH using 5V on Rev01. It should be 3V3 to ensure safe operation of the AD2S1210 IC. This has been fixed for Rev02. Before first use of Rev01 boards, carefully check, if resistors R14[A..C] are **NOT** placed.

Compatibility 
-------------

* This Board is compatible with slots D1-D5. In Slot D5 only CH A/1 and CH B/2 are available. Also, there is a special CPLD programm needed for D5, D1 to D4 share a common CPLD programm

Pinout
------

.. image:: Digital_Resolver_rev01/Pinout_Adapter_Card_Digital_Resolver_edited.png
  :height: 300

.. image:: Digital_Resolver_rev01/Pinout2_Adapter_Card_Digital_Resolver_edited.png
  :height: 700

Implementation with Resolver Interface IP-Core
----------------------------------------------

* The following describes the connecting of the adapter board with the resolver interface ip-cores.
* Two cases have to be distinguished here: ``3 channels in slot D1 to D4``, ``2 channels in slot D5``

In general one has to add the ``Resolver Interface`` ip-core e.g. to the ``user`` hierarchy in the block design as many times as channels are needed. 
The port names of the ip-core and at the adapterboard slightly differ. Therefore it is useful to create ports at the ``user`` hierarchy with the adapter boards' signal names in order to avoid confusion. 
E.g. the picture below shows the ip-core and respective ports for channel A/1. Pay attention to the signals ``SDI`` and ``SDO``. Depending on the perspective, serial data in and out can change. 
In this example it is seen from the FPGA perspective, therefore, ``SPI_MOSI`` is labeled to ``SDO_1``.

.. image:: Digital_Resolver_rev01/resolverIP_interfaces.png
  :height: 500

Outside the ``user`` hierarchy it then depends on the physical adapter board slot that you are using, what signal has to be connected to which pin. 
Again, pay attention to ``SDI`` and ``SDO`` signals. Now we connect the signals to the adapter card pins. Here, our ``SDO`` signal from the block design 
has to be connected to the pin number that provides the ``SDI`` signal of the adapter board and vice versa.

2 Channels in Slot D5 (Ch A/1 and Ch B/2)
=========================================

The constraint file for slot D5 gives by default access to every single pin using the naming convention ``Dig_xx_Ch5``, where ``xx`` is the IO number [00...29]. 
Simply create input and output ports as shown below and connect them.

.. image:: Digital_Resolver_rev01/resolverIP_pinout_D5.png
  :height: 500

3 Channels in Slots D1 to D4
============================

Below you'll find an example on how to use the adapter board in slot D4. By default the constraint file for D4 is written in a vectorized (``packed``) manner that is not proper for accessing single pins. 
But there are also constraint files provided that allow access to the single pins. As shown below find the files in the sources section in Vivado. Right click on ``Digital_D4_packed.xdc`` and ``Disable File``. 
Then right click on ``Digital_AdapterBoard_D4.xdc`` and ``Enable File``. 

.. image:: Digital_Resolver_rev01/constraints_D4.png
  :height: 500

Now we can access D4 pins with the same naming convention as above and create and connect respective ports as shown in the picture below.

.. image:: Digital_Resolver_rev01/resolverIP_pinout_D4.png
  :height: 750

Finally do not forget to connect ip-core clocks (100 MHz) and AXI interfaces, as well as a proper ``sampling_trigger`` signal (e.g. ``trigger_conversion`` signal that also triggers the ADC's).
Build the bitstream and see the respective ip-core driver docs for the software part.

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