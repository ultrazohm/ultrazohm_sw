.. _carrier_board_rev05_mios:

========================
Overview of the ARM Pins
========================

In the following table you will find an overview of the pin mapping of the SoC MIO pins (fixed pins of the SoC's Processing System).
All connector-accessible MIO pins -- i.e., those having an X... assignment in column **CB-Pin** -- are labeled with the associated net label/name (of the carrier board) in the fifth column and the connector pin in the **CB-Pin** column (CB --> Carrier Board).
The connectivity between MIO pins and the frontpanel I/Os -- four user LEDs and three buttons -- is shown by column **FP_**.

Itemized list of MIO-related changes next to :ref:`carrier_board_rev04_mio`:

- The retrofitted Ethernet PHY resets on Rev04 (cf. :ref:`carrier_known_issues_ethrst`) are moved from MIO26/27 to the S3C

	- MIO26 becomes a PMU spare (with IRQ capability)
	- MIO27 becomes part of DPaux

- Three LEDs (PS_1V8_GPIO2/3/4) on MIO33/34/39 and two frontpanel switches (PS_1V8_GPIO5/7) on MIO40/30 are moved to MIO56-60

	- MIO30 becomes DPaux (with MIO27-29)
	- MIO33 becomes a PMU spare
	- MIO34 becomes CS1 of SPI1
	- MIO39 becomes CS2 of SPI0
	- MIO40 becomes CS1 of SPI0

- The "External STOP" (isoEmergencyStop) on MIO31 is moved to MIO61, making room for a PMU spare (without IRQ capability)
- ``PS_ANL_sharedA`` on MIO45 is moved to MIO62, making room for CD of the µSD
- MIO52 is reserved for the PCIe reset
- The remaining isoGPIOs (MIO53-55) are assigned to power messaging (i.e., a ready-to-poweroff output and -- optionally, as the APU shall use I²C for it -- a power button input), an SMBus-like IRQ line for the user I²C and a reset for its bus mux/switch

Note that all changes affect only MIO pins that are used as GPIO in Rev04, which

- makes the Vivado design of Rev04 compatible to Rev05 (as GPIO remapping is already supported in software, cf. the ``uz_MioGpio`` module or the :ref:`uzpA53`), and
- limits (eventually required) changes to the Vivado design solely(!) to making any of the aforementioned new hardware features available, at a later point in time.

.. _carrier_board_rev05_mio:
.. csv-table:: Overview of the MIO Pins (Rev05)
  :file: interfaces/MIO_Pinout.csv
  :widths: 5 8 8 5 10 5 5
  :header-rows: 1

Keys:

- ¹) PMU-Out
- ²) PMU-In


Pin capabilities
----------------

For detailed information, see the `Xilinx Technical Reference Manual of the Zynq UltraScale+ aka UG1085 <https://docs.amd.com/r/en-US/ug1085-zynq-ultrascale-trm/Multiplexed-I/O>`_ (i.e., chapter *Multiplexed I/O* and table *MIO Interfaces*).
