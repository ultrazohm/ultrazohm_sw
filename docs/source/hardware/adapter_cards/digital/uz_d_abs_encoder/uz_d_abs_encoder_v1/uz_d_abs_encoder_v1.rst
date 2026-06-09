.. _uz_d_absolute_encoder_v1:

==============================
Digital Absolute Encoder Rev01
==============================

The ``uz_d_absolute_encoder`` adapter board interfaces absolute position encoders with the UltraZohm.
The adapter board is intended for encoders using EnDat and SSI-style differential serial communication.
It provides the physical layer between the encoder connector and the FPGA pins on the UltraZohm carrier board.


 .. image:: uz_d_abs_encoder_rev01.png

Functionality
=============

The adapter board is intended to provide:

* Three independent absolute encoder channels with one female D-Sub9 connector per channel.
* Differential clock output for absolute encoder communication.
* Bidirectional differential data path for encoder communication.
* ``5V`` encoder supply routed to the external connectors.
* Protection via a ``TVS diode`` and serial resistors. Parallel termination for the encoder interface.

.. important::
   Verify voltage levels, encoder supply current, line termination and connector pinout before connecting an encoder.
   Absolute encoder interfaces are not mechanically or electrically interchangeable across all manufacturers.

Technical Overview
==================

When the adapter board ist mounted in one of the D-slots of the UltraZohm the encoder channels are numbered ``1`` to ``3``, top to bottom as shown below.

.. figure:: ../encoder_channels.png
  :width: 100
  
  Numbering of the encoder channels as seen when adapter board is mounted in the UltraZohm

The adapter board provides three independent encoder interface channels each employing a pair of THVD1450DR RS-485 transceivers.
The two transceivers per channel are configured for transmitting or receiving by the connected IP-core via dedicated pins. 
This makes them compatible with many common encoder protocols or even usable as a generic RS-485 communication device.

.. figure:: ../thvd1450dr_rs485.png
  :width: 200
  
  RS-485 transceiver according to THVD1450DR datasheet

Supported Interfaces
====================

EnDat
-----

The EnDat interface uses a differential clock output and a bidirectional differential data channel to/from the encoder.
The adapter board hardware therefore is able to support EnDat 2.1 and 2.2 protocols. However, supported functionality 
depends on the IP core and might not support all features of the protocols.

The UltraZohm EnDat IP core is documented in :ref:`uz_endat_interface`.

SSI
---

The SSI interface uses a differential clock output and a differential data channel for reading data from the encoder.
The adapter board hardware therefore is able to support industry standard SSI protocols. However, supported functionality 
depends on the IP core and might not support all features of the protocols.

The UltraZohm SSI IP core is documented in *coming soon*

Connectors and Pinout
=====================

External Encoder Connector
--------------------------

The pinout of the female D-Sub9 encoder connectors is shown below.

.. figure:: ../dsub9female.png
  :width: 400

.. list-table:: Female D-Sub9 pinout
   :header-rows: 1
   :widths: 10 50

   * - Pin
     - Description
   * - 1
     - RS485 B DATA (DATA-)
   * - 2
     - RS485 A DATA (DATA+)
   * - 3
     - RS485 B CLOCK (CLK-)
   * - 4
     - RS485 A CLOCK (CLK+)
   * - 5
     - V_Supply: +5V power supply for the encoder
   * - 6
     - GND: return path for V_Supply
   * - 7
     - N.C.
   * - 8
     - N.C.
   * - 9
     - N.C.

.. note::
   In the default assembly variant, the D-Sub9 connector housing and the cable shield are not connected to the adapter board.

UltraZohm Digital Slot Mapping
------------------------------

On the D-slot side of the adapter board the mapping of the pins can be seen from the schematic. 
However, in order to keep the adapter board compatible to all D-slots (``D1-D5``), the pinout is rerouted within the 
CPLD program ``uz_d_abs_encoder``. Therefore, keep in mind: 

- Follow the pinout in the tables below when connecting IP-cores in the FPGA design to the adapter board. => ``Typical usecase`` 
- Follow the pinout in the schematic when investigating the adapter board connector or the adapter board itself.

The tables are separate for each of the three encoder channels.

Channel 1
---------

.. list-table:: D-slot pin mapping within the FPGA design, encoder channel 1
   :header-rows: 1
   :widths: 40 30 30 30

   * - Adapter board signal
     - Digital I/O pin
     - EnDat IP-core signal
     - SSI IP-core signal
   * - RX-S DATA SH1
     - Dig_07_Chx
     - endat_data_in
     - ssi_data_in
   * - TX-S DATA SH1
     - Dig_08_Chx
     - endat_mode_data_out
     - N.A.
   * - READ WRITE DATA SH1
     - Dig_11_Chx
     - RW_data
     - RW_data
   * - TX-S CLOCK SH1
     - Dig_15_Chx
     - endat_clk
     - ssi_clk
   * - READ WRITE CLOCK SH1
     - Dig_17_Chx
     - RW_clk
     - RW_clk

Channel 2
---------

.. list-table:: D-slot pin mapping within the FPGA design, encoder channel 2
   :header-rows: 1
   :widths: 40 30 30 30

   * - Adapter board signal
     - Digital I/O pin
     - EnDat IP-core signal
     - SSI IP-core signal
   * - RX-S DATA SH2
     - Dig_06_Chx
     - endat_data_in
     - ssi_data_in
   * - TX-S DATA SH2
     - Dig_09_Chx
     - endat_mode_data_out
     - N.A.
   * - READ WRITE DATA SH2
     - Dig_10_Chx
     - RW_data
     - RW_data
   * - TX-S CLOCK SH2
     - Dig_14_Chx
     - endat_clk
     - ssi_clk
   * - READ WRITE CLOCK SH2
     - Dig_16_Chx
     - RW_clk
     - RW_clk

Channel 3
---------

.. list-table:: D-slot pin mapping within the FPGA design, encoder channel 3
   :header-rows: 1
   :widths: 40 30 30 30

   * - Adapter board signal
     - Digital I/O pin
     - EnDat IP-core signal
     - SSI IP-core signal
   * - RX-S DATA SH3
     - Dig_18_Chx
     - endat_data_in
     - ssi_data_in
   * - TX-S DATA SH3
     - Dig_12_Chx
     - endat_mode_data_out
     - N.A.
   * - READ WRITE DATA SH3
     - Dig_20_Chx
     - RW_data
     - RW_data
   * - TX-S CLOCK SH3
     - Dig_22_Chx
     - endat_clk
     - ssi_clk
   * - READ WRITE CLOCK SH3
     - Dig_23_Chx
     - RW_clk
     - RW_clk

Electrical Specifications
=========================

.. list-table:: Electrical characteristics
   :header-rows: 1
   :widths: 30 15 40

   * - Parameter
     - Value
     - Comment
   * - Encoder supply voltage
     - +5V
     - Supplied by the ``5V_PER`` rail of the D-slot
   * - Encoder supply current
     - max. 500 mA
     - As defined by the carrier connector ``X6``

Configuration Before First Use
==============================

Before using the adapter board:

* Check that the encoder supply voltage matches the connected encoder.
* Program the CPLD for the selected digital adapter slot with the program ``uz_d_abs_encoder``, see :ref:`label_cpld_programming`.
* Instantiate the matching FPGA IP core and connect it to the D-slot pins used by this adapter board, see :ref:`uz_endat_interface` or *uz_ssi_interface*.
* Instantiate and configure the software driver, see :ref:`uz_endat_interface` or *uz_ssi_interface*.
* Verify the external connector pinout against the encoder cable before powering the system.

Validated Encoder Setups
========================

The following encoder and motor-integrated encoder combinations were tested successfully with this adapter board revision.

.. list-table:: Tested encoder setups
   :header-rows: 1
   :widths: 15 40 45

   * - Interface
     - Device
     - Resolution / Notes
   * - EnDat
     - Heidenhain ECN125
     - 25-bit single-turn
   * - EnDat
     - Siemens 1FK7 motor encoder
     - 12-bit multi-turn, 25-bit single-turn
   * - SSI
     - RLS AksIM-2
     - 19-bit single-turn
   * - SSI
     - RLS Orbis
     - 14-bit single-turn

These validation results confirm practical operation with the listed encoders, but do not imply compatibility with all devices using the same protocol.

Known Issues and Limitations
============================

* Encoder supply voltage is fixed to ``5V``. However, some SSI encoders require ``10V`` to ``30V``. This is supported in Rev02. 

Compatibility
=============

* Digital adapter slots ``D1`` to ``D5``
* Carrier board revision compatibility: ``no restrictions``.
* Required CPLD firmware: ``uz_d_abs_encoder``.
* Required FPGA IP core revision: ``no restrictions``.
* Required software driver revision: ``no restrictions``.

References
==========

* `uz_d_absolute_encoder repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_absolute_encoder>`_
* :download:`Schematic Rev01 <SCH_uz_d_absolute_encoder_Default_Rev01.pdf>`
* :ref:`label_cpld_programming`
* :ref:`uz_endat_interface`

Designer
========

Designed by Tom Gaupp (TH Nuernberg).
