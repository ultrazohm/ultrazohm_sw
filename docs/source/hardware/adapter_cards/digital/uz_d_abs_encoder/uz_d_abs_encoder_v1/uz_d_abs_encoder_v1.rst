.. _uz_d_absolute_encoder_v1:

==============================
Digital Absolute Encoder Rev01
==============================

The ``uz_d_absolute_encoder`` adapter board interfaces absolute position encoders with the UltraZohm.
The adapter board is intended for encoders using EnDat and SSI-style differential serial communication.
It provides the physical layer between the encoder connector and the FPGA pins on the UltraZohm carrier board.


 .. image:: uz_d_abs_encoder_rev01.png

Source
======

* `uz_d_absolute_encoder repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_absolute_encoder>`_
* TODO: Add links to schematic and assembly drawing once the files are added to this folder.

Functionality
=============

The adapter board is intended to provide:

* Three independent absolute encoder channels with one female D-Sub9 connector per channel.
* Differential clock output for absolute encoder communication.
* Bidirectional differential data path for encoder communication.
* ``5V`` Encoder supply routed to the external connectors.
* Protection via a ``TVS diode`` and serial resistors. Parallel termination for the encoder interface.

.. important::
   Verify voltage levels, encoder supply current, line termination and connector pinout before connecting an encoder.
   Absolute encoder interfaces are not mechanically or electrically interchangeable across all manufacturers.

.. figure:: encoder_channels.png
  :width: 200
  
  Numbering of the encoder channels as seen when adapter board is mounted in the UltraZohm

Technical Overview
==================

The adapter board provides three independent encoder interface channels each employing a pair of THVD1450DR RS-485 transceivers.
The two transceivers per channel are configured for transmitting or receiving by the IP-core that is utilizing them via dedicated pins. 
This makes them compatible with many common encoder protocols or even as a generic RS-485 communication device.

.. figure:: thvd1450dr_rs485.png
  :width: 200
  
  RS-485 transceiver according to THVD1450DR datasheet

Supported Interfaces
====================

EnDat
-----

The EnDat interface uses a differential clock output and a bidirectional differential data channel to/from the encoder.

Document the following EnDat-specific properties here:

* Supported EnDat version or operating mode.
* Maximum tested clock frequency.
* Encoder supply voltage and maximum current.
* Single-turn and multi-turn bit widths used during testing.
* CRC handling and supported command set.
* Required Vivado IP core and driver configuration.

Software support for the EnDat IP core is documented in :ref:`uz_endat_interface`.

SSI
---

docs coming soon.

Connectors and Pinout
=====================

External Encoder Connector
--------------------------

The pinout of the female D-Sub9 encoder connectors is shown below.

.. figure:: dsub9female.png
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

UltraZohm Digital Slot Mapping
------------------------------

On the D-slot side of the adapter board the mapping of the pins can be seen from the schematic. 
However, in order to keep the adapter board compatible to all D-slots (``D1-D5``), the pinout is rerouted within the 
CPLD program ``uz_d_abs_encoder``. Therefore, keep in mind: 

- Follow the pinout in the tables below when connecting IP-cores in the FPGA design to the adapter board. ``Typical usecase`` 
- Follow the pinout in the schematic when investigating the adapter board connector or the adapter board itself.

The tables are separate for each of the three encoder channels.

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
     - ...
   * - TX-S DATA SH1
     - Dig_08_Chx
     - endat_mode_data_out
     - ...
   * - READ WRITE DATA SH1
     - Dig_11_Chx
     - RW_data
     - ...
   * - TX-S CLOCK SH1
     - Dig_15_Chx
     - endat_clk
     - ...
   * - READ WRITE CLOCK SH1
     - Dig_17_Chx
     - RW_clk
     - ...

.. list-table:: D-slot pin mapping within the FPGA design, encoder channel 2
   :header-rows: 1
   :widths: 40 30 30 30

   * - Adapter board signal
     - Digital I/O pin
     - EnDat IP-core signal
     - SSI IP-core signal
   * - RX-S DATA SH1
     - Dig_06_Chx
     - endat_data_in
     - ...
   * - TX-S DATA SH1
     - Dig_09_Chx
     - endat_mode_data_out
     - ...
   * - READ WRITE DATA SH1
     - Dig_10_Chx
     - RW_data
     - ...
   * - TX-S CLOCK SH1
     - Dig_14_Chx
     - endat_clk
     - ...
   * - READ WRITE CLOCK SH1
     - Dig_16_Chx
     - RW_clk
     - ...

.. list-table:: D-slot pin mapping within the FPGA design, encoder channel 3
   :header-rows: 1
   :widths: 40 30 30 30

   * - Adapter board signal
     - Digital I/O pin
     - EnDat IP-core signal
     - SSI IP-core signal
   * - RX-S DATA SH1
     - Dig_18_Chx
     - endat_data_in
     - ...
   * - TX-S DATA SH1
     - Dig_12_Chx
     - endat_mode_data_out
     - ...
   * - READ WRITE DATA SH1
     - Dig_20_Chx
     - RW_data
     - ...
   * - TX-S CLOCK SH1
     - Dig_22_Chx
     - endat_clk
     - ...
   * - READ WRITE CLOCK SH1
     - Dig_23_Chx
     - RW_clk
     - ...

Electrical Specifications
=========================

.. TODO: Fill this table with measured or component-data based limits.

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

Before using the card:

* Check that the encoder supply voltage matches the connected encoder.
* Program the CPLD for the selected digital adapter slot with the program ``uz_d_abs_encoder``, see :ref:`label_cpld_programming`.
* Instantiate the matching FPGA IP core and connect it to the D-slot pins used by this adapter board.
* Instantiate and configure the software driver.
* Verify the external connector pinout against the encoder cable before powering the system.

Vivado and Software Integration
===============================

EnDat
-----

Use the EnDat FPGA IP core together with the bare-metal driver documented in :ref:`uz_endat_interface`.
The driver configuration must match the connected encoder and the IP core clock.

.. code-block:: c

   static struct uz_endat_interface_config_t endat_config = {
       .base_address = XPAR_UZ_USER_UZ_ENDAT_INTERFACE_0_BASEADDR,
       .ip_clk_frequency_Hz = 100000000U,
       .endat_clk_frequency_Hz = 2500000U,
       .endat_encoder_bit_width_single_turn = 19U,
       .endat_encoder_bit_width_multi_turn = 12U,
       .machine_polepairs = 4U,
       .sampling_interval_seconds = 0.0001f,
       .kp_pll = 628.0f,
       .ki_pll = 98696.0f,
       .position_mech_offset_si_single_turn = 0.0f
   };

.. TODO: Add a Vivado block design screenshot after the reference design is available.

SSI
---

Known Issues and Limitations
============================

* TODO: List known hardware issues, assembly variants or workarounds.
* TODO: List unsupported EnDat/SSI modes.
* TODO: List maximum verified cable length and clock frequency.

Compatibility
=============

.. TODO: Replace with verified slot compatibility.

* Digital adapter slots D1 to D5
* Carrier board revision compatibility: TODO.
* Required CPLD firmware revision: TODO.
* Required FPGA IP core revision: TODO.
* Required software driver revision: TODO.

References
==========

* :ref:`uz_endat_interface`
* :ref:`label_cpld_programming`
* TODO: Schematic Rev01
* TODO: Assembly drawing Rev01
* TODO: Bill of materials Rev01
* TODO: Altium project repository

Revision History
================

.. list-table::
   :header-rows: 1
   :widths: 20 30 50

   * - Revision
     - Date
     - Notes
   * - Rev01
     - TODO
     - Initial hardware revision.

Designer
========

Designed by Tom Gaupp (Zohm Control), Michael Hoerner (Zohm Control).
