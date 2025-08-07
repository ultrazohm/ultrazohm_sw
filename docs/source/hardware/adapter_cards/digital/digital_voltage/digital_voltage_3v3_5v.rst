.. _digitalVoltage_3v3_5v:

=============================
Digital Voltage 3V3/5V Rev02
=============================


.. _uz_d_voltage_3v3_5v_functions:

.. figure:: digital_voltage_3v3_5v/uz_d_voltage_3v3_5v_functional.svg
	:width: 100%
	:align: center

	Functional blocks of the Voltage Adapter Card

The Voltage_3v3_5v adapter card enables general-purpose digital input/output (GPIO) functionalities at a selectable voltage level of 3.3 V or 5 V.
It, therefore, crosses between two voltage domains and is an extension of both the :ref:`digitalVoltage` and :ref:`digitalVoltage3v3rev01` cards, which have fixed voltages.
Like with the original Digital Voltage 5V card, signal directions can be set in groups of eight I/O pins.
The board supports voltage level shifting, supply rail monitoring, and I²C-based readout of the hardware configuration.

Functionality
-------------

The functionality of the adapter card is segmented into several key areas, as depicted in the figure above:

1. Four 8-Bit Level Shifters

   - The adapter card includes four 8-bit bidirectional level shifters, enabling voltage translation between the 3.3 V and 5 V domains.
   - Each digital I/O pin features an integrated 10 kΩ pulldown resistor to ensure a defined logic low state when the pin is not actively driven.

2. Signal direction

   Each level shifter can be individually configured for input or output operation via corresponding DIP switches.
   The four DIP switches allow groupwise control of the signal direction for each 8-bit group.

   .. csv-table:: Grouped signals and dedicated switches
     :file: digital_voltage_3v3_5v/switches.csv
     :widths: 50 80
     :header-rows: 1

   A DIP switch in the OFF position corresponds to a logic HIGH on the DIR line, configuring the direction as output (from the SoC).
   Conversely, a DIP switch in the ON position sets the direction to input (to the SoC).

   .. note:: Direction control is only available on a per-group basis. For fully flexible pin assignment, refer to :ref:`digitalVoltage3v3rev01`.

   .. _dig_3v3_5v_rev02_Supervisor:
3. Supply Rail Monitoring, Output Enable Logic, and Source Control

   The card monitors both the 3.3 V and 5 V supply rails provided by the carrier board.
   By default, the level shifter output enable (nOE) is governed by these voltage monitors.
   Alternatively, by setting switch S2, control can be transferred to the nOE_Carrierboard signal, which is supported in carrier boards with a hardware revision :math:`\geq` ``Rev05`` (cf. :ref:`carrier_board_rev5`, ``SlotOE``).
 
   As an additional feature, the output signal of the card's on-board supply rail monitoring (i.e., are its local 3V3 and 5V rails both okay) is also fed back to the carrier board by means of D connector (``X6[A-E]``) pin 100.
   Formerly used as ``PILOT_IN`` (and available locally on the LC4xxx CPLDs as ``/PILOT_INx``), newer :math:`\geq` ``Rev05``-based UltraZohm systems (where per-slot ``SlotOK`` signals link each slot to the S³C) may utilize this signal to generate application-specific error conditions and responses.
   This holds true by means of the five per-slot CPLD *locally*, and -- as a feature not available on older carrier boards -- also on a *system*-wide scale via the S³C (cf. :ref:`carrier_board_rev5_s3c` for an overview and the "safety block diagram" at the end of the carrier's schematic for details).
 
4. I²C Port Expander

   An onboard I²C port expander provides additional flexibility and control:
   
   - LED indicators (on the rear side of the card) can be controlled via software to represent the selected output voltage and additional card/system states.
   - Signal direction configuration and output voltage selection statuses are accessible via I²C, enabling seamless integration with system control software.

As with some of the previous Digital Voltage cards, all internal rails -- that also are available on the external connector (3V3, 5V and VIN) -- are protected by polyfuses (``F[3-1]``).

Configuration
--------------

Prior to first use, ensure that the card is correctly configured according to the target system's requirements.
This includes setting DIP (i.e., I/O directions) and non-DIP (e.g., voltage selection) switches appropriately for the target voltage revision (e.g., Rev04 with a supervisor switch).

.. TODOs: Clarify "Rev04 with a supervisor switch" above and add pictures as per belowe

2 Pictures for Rev04 and Rev05

Measurements and technical background
----------------------------------------

As described :ref:`here <dig_3v3_5v_rev02_Supervisor>` the board features supervisor monitor devices to disable all digital outputs of the level shifter at undervoltage error state. 

.. figure:: digital_voltage_3v3_5v/uz_d_voltage_3v3_5v_block_diagram.png
	:width: 100%
	:align: center

	Block diagram of the UZ_D_Voltage_3V3_5V adapter card

The following two measurements show the switch-on and switch-off signal curves when pressing the UltraZohm system power switch. The oscilloscope monitors:

- CH1 (yellow): Supply Rail
- CH2 (green): nRESET
- CH3 (blue): nOE_Supervisor
- CH4 (red): Digital Output

The measurement results show that the level shifter outputs will we be disables as long as the supply rails are in their accepted range:

.. figure:: digital_voltage_3v3_5v/uz_d_voltage_3v3_5v_uz_switched_on.png
	:width: 80%
	:align: center

	Measurement during switch on of the UltraZohm system


.. figure:: digital_voltage_3v3_5v/uz_d_voltage_3v3_5v_uz_switched_off.png
	:width: 80%
	:align: center

	Measurement during switch off of the UltraZohm system

Attention: there is an exceptional situation where the output disable function does not work intuitively. It occurs only in an unrelevant situation where the output voltage is selected to 3.3V and the 5V supply rail on the adapter card fails. In that case the 5V voltage supervisor asserts the output disable function as long as the 5V supply rail voltage decrease under the power-on reset voltage (V_POR = 0.7 V) of the supervisor IC. Thus the open-drain NRESET output jumps back to HIGH level because the 3.3V supervisor IC states healthy condition and all level shifter outputs will be enabled again. This edge case is therefore irrelevant for safety issues, because the 5V rail has no functional meaning when using 3.3V as output voltage. It is recommended to stop inverter operation when this situation occurs. Measurements are shown in following:

.. _uz_d_voltage_3v3_5v_edge_case:
.. figure:: digital_voltage_3v3_5v/uz_d_voltage_3v3_5v_edge_case.png
	:width: 80%
	:align: center

	Measurement of edge case situation with error on 5V supply rail with 3.3V output voltage selection
	


Accessoires
------------

An optional front panel with integrated voltage indication LEDs is available for enhanced usability.

.. figure:: digital_voltage_3v3_5v/uz_d_voltage_3v3_5v_blend.svg
	:align: center

To utilize this functionality, a corresponding software extension must be activated manually in the Vitis development environment.
It is part of the demo integrated in the :ref:`uzpA53`'s :ref:`uzpA53_cardid` feature and is enabled by means of the ``UZ_PLATFORM_CARDID`` preprocessor ``#define`` as described :ref:`here <uzpA53_init>`.
Once enabled, the demo reads the card's voltage configuration at boot-up and drives the LED accordingly.
As of mid 2025, no error reporting has been defined, i.e., the red LED is still unused.
Additionally, the light guide component `LPF-C011304S <https://www.mouser.de/ProductDetail/Lumex/LPF-C011304S?qs=3ZOqpMxxriqLNJacoNbLgw%3D%3D>`_ must be installed on the PCB to support visual indication via the front panel.

References/Source
=================

.. _dig_3v3_5v_rev02_references:

* :download:`Schematic Rev02 <digital_voltage_3v3_5v/SCH_UZ_D_Voltage_3V3_5V_Default_Rev02.pdf>`
* `Digital Voltage 3V3/5V repository <https://bitbucket.org/ultrazohm/uz_d_voltage_3v3_5v>`_

Compatibility
=============

Slots D1 to D5 can be used without limitations.

See also
========

* `CPLD software git <https://bitbucket.org/ultrazohm/cpld_lattice/>`_
* :ref:`label_cpld_programming`

Designer
========

Designed by Andreas Geiger (Zohm Control GmbH), 03/2025
