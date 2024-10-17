========
Overview
========

These pages document the ongoing efforts towards the next revision of the UltraZohm carrier and its associated components (front panel, housing, etc.).

An overview about the interfaces of pre-Rev04 systems is shown in chapter :ref:`label_carrier_board_overview`, whilst the additions of Rev04 are documented :ref:`here <carrier_board_rev04_features>`.

Summary of new features and changes
-----------------------------------

* Integration of a **System Supply and Safety CPLD/Controller** ("S³C") that
	* monitors the various system parameters (e.g., supply voltage, power good signals and thermal status),
	* drives a "carrier ready" signal to the adapter cards (based thereon),
	* monitors status signals from the adapter cards (and, in case of D[1-5], also their slot-local CPLD),
	* drives and/or receives the twelve digital adapter card signals of slot D5 previously not connected, and
	* routes various PS-MIOs and up to six PL pins to wherever they are needed (e.g., on slot D5 or FP).
	* See :ref:`carrier_board_rev5_s3c` for details of the used part, its supply, and the already implemented and prospective functions
* New, fully PCB-based front panel (FP) with
	* added **Second Gigabit Ethernet** interface (via SGMII)
	* added 15-pin D-sub connector with 8+5 **Isolated IOs** ("isoIOs") for
		* up to 12 software-controlled general-purpose IOs (GPIOs),
		* up to 4 hardware-controllable GPIOs from/to S³C (and PL),
		* one dedicated hardware-controlled GPO for a heartbeat, and
		* an external output of the integrated isolated 3V3 supply.
	* improved isolated "External STOP" connector, where
		* the (normally-closed) signal now not only is sent to the PS but also can be routed to all the hardware-programmable devices (i.e., the CPLDs of the D slots and the PL) via the S³C, and
		* two optional software-controllable GPIOs are available.
	* the four serial **multi-Gigabit/s transceivers** of the PS ("PS-GTR"s) now being fully accessible and, as of Rev01 of the FP, used for the
		* second Gigabit Ethernet (as in Rev04, but now on the FP), an
		* internal M.2 slot for a 6 GBit/s SATA-2 SSD, and an
		* internal M.2 slot for a single-lane PCIe EP.
		* The fourth PS-GTR lane (pair) is currently not assigned but available on the FP connector for future extensions
* Isolated JTAG+UART interface to avoid ground loops during debugging
* Integrated thermal management for
	* configuration-free temperature-driven control of up to two fans, and
	* monitoring of fan status, SoM temperature and system temperature
* All shared signals between SoM (both PS and PL) and the adapter card slots have been removed, with the only exception being a per-group I²C bus and an ANL_Pin54_Legacy signal to maintain compability like already targeted in Rev04 (cf. last bullet point in :ref:`carrier_board_rev04_features` of Rev04)
* Support for adapter card identification (in line with the :ref:`corresponding retrofit for Rev04 <carrier_retrofits_cardid>`)
* Integrated identification EEPROM used by the :ref:`UZ platform identification framework <uzpA53>` with associated circuitry (including a battery-based power supply for the Zynq's RTC)
* The SD card slot now is on the northern edge of the carrier board
