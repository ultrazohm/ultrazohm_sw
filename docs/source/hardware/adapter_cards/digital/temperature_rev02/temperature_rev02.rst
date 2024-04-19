.. _temperature_card_rev02:

======================
Temperature Card Rev02 
======================

Detailed Description
-----------------------
Extends the UltraZohm with a temperature measurement ability. This digital adapter card is based on the LTC2983 temperature measurement system.
With the ability to measure different sensor types and built-in data preparation, this card extends the functionality of the UltraZohm.
The total amount of 60-Channels (40 on the frontpanel, 20 internal) could be wired directly on the card or in the plug for different kind of sensors.

.. _temperature_card_v1_pcb:

.. figure:: Overview_tempcard_notes.png
   :width: 800
   :align: center

   uz_d_temperature adapter board

Functionality
-----------------------
Based on the LTC2983:

* Directly Digitize RTDs, Thermocouples, Thermistors, and Diodes
* Results Reported in °C or °F
* 20 Flexible Inputs Allow Interchanging Sensors
* Automatic Thermocouple Cold Junction Compensation
* Built-In Standard and User-Programmable Coefficients for Thermocouples, RTDs and Thermistors
* Configurable 2-, 3- or 4-Wire RTD Configurations
* Measures Negative Thermocouple Voltages
* Automatic Burn Out, Short-Circuit and Fault Detection
* Simultaneous 50Hz/60Hz Rejection
* Includes 10ppm/°C (max) Reference (I-Grade)
* 3 Galvanic isolated LTC2983 available (2 reachable directly on the Front, 1 could be reached with riser-cable)
* build-in RC-lowpass filter for each channel
* on-board-wiring for easy channel/sensor configuration

Before first use
----------------
* Determine correct placement options for correct function
* Program CPLDs with the firmware needed for the temperature card `uz_d_temperature_ltc2983 <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/uz_d_temperature_ltc2983/>`_, see :ref:`label_cpld_programming` for details

Compatibility 
-------------
* The version of this card is compatible with slots D1-D4. D5 could be used with an own CPLD-file that is not provided right now.

Channelgroup Connector and Pinout
---------------------------------
The pinout is identical for each channelgroup ``A-C`` on the temperature card. For connecting sensors to the connector, pre-assembled cables are 
a good starting point. Use ``Samtec MMSD-15-xxx-x-xx.xx-D-P-LDX`` cables or for assembly of own cables the ``Samtec IPD1-15-D-K`` with crimps ``Samtec CC79L`` (proper tools required).

.. _channel_group_pinout:

.. figure:: pinout_overview.png
   :width: 1000
   :align: center

   Channelgroup Pinout

Implementation with Temperature_Card_Interface IP-Core
------------------------------------------------------
* The following describes the connecting of the adapter board with the respective IP-Core at the example of digital adapter slot ``D4``. 
* For further details on the IP-Core, see :ref:`temperature_card_IPcore_v1`.

.. note::
   | Users who use the adapter card for the first time are recommended to use the following step-by-step instructions for didactic reasons. 
   | See ``Step by step guide``.
   | More experienced users that quickly want to implement the IP-Core can use a tcl-script in Vivado and execute it from the tcl-console after opening the block design. 
   | See ``tcl commands``.

tcl commands
************
* cd [ get_property DIRECTORY [current_project] ]
* source ../../tcl_scripts/ip_uz_user_temp_ip_core.tcl

**Manual steps:**

* delete all input/output ports that refer to ``D4``
* create proper input/output ports, e.g. ``Dig_03_Ch4`` etc.
* connect the ports with the proper signals at the ``user`` hierarchy
* do all the steps for building a bitstream and export it

Step by step guide
******************

In general, one has to add the ``Temperature_Card_Interface`` IP-Core e.g. to the ``user`` hierarchy in the block design of the Vivado project. 
This is achieved by right click and ``Add IP...`` and typing in the name of the IP-Core in the search field.
Furthermore, one has to create pins inside the ``user`` hierarchy for later connecting them to the proper ports of the adapter board slots, outside of the ``user`` hierarchy. 
Creating pins is achieved by right click and ``Create Pin...``, defining proper names and direction.
The figure below shows how the result should look like with the IP_Core placed and all necessary pins created.
The not connected pins are for development and debugging purpose only.

.. _user_hierarchy_pins:

.. figure:: user_hierarchy_pins.png
   :width: 600
   :align: center

   Pinout within the ``user`` hierarchy 

Outside the ``user`` hierarchy it then depends on the physical adapter board slot that you are using for the adapter board. Here it is shown at the example of adapter board 
slot ``D4``. Create ports by right click and ``Create Ports...`` and name the ports according to the figure below, where ``_Ch4`` refers to adapter board slot ``D4``. Pay attention 
that no other pins regarding ``_Ch4`` are present in the block design. Delete them to avoid errors during the build or damage to the hardware. Since all three channelgroups share the common 
reset signal ``LTC_resetn_1``, all other reset signals are left unconnected.

.. _outside_user_ports:

.. figure:: outside_user_ports.png
   :width: 700
   :align: center

   Pinout and ports outside the ``user`` hierarchy

The mapping between the names and physical pins at the hardware is managed by constraint files. Two types of constraint files are already prepared. They can be found in the ``sources`` section 
of the Vivado project, as shown below. By default the constraint file for D4 is written in a vectorized (``packed``) manner that is not proper for accessing single pins. But there are also 
constraint files provided that allow access to the single pins. Right click on ``Digital_D4_packed.xdc`` and ``Disable File``. Then right click on ``Digital_AdapterBoard_D4.xdc`` and 
``Enable File``. By double-clicking (opening) the recently enabled file you will recognize the port names you assigned in the block design and the correct mapping between the IP-Core 
and the adapter board slot is ensured.

.. _temperature_constraints_d4:

.. figure:: constraints_D4.png
  :width: 800
  :align: center

  Constraint file for ``D4``

Finally do not forget to connect ip-core clock (100 MHz), reset signals and AXI interfaces, as well as assigning an AXI base address to the IP_Core in the ``Address Editor``.
Build the bitstream, export the .xsa file, build the UltraZohm workspace in Vitis and see the respective ip-core driver docs for the software part.

Customize Wiring
----------------

Since there exists many possible configurations for the temperature card, its possible to manage some wiring directly on the PCB. 
For special applications that are not covered by provided assembly variants and the docs, carefully see the datasheet of the LTC2983.

.. _temperature_wiring:

.. figure:: Onboard_Wiring.png
   :width: 500
   :align: center

   Filter and Wiring area of one channelgroup for customizing the wiring

This area is dedicated to implement RC-lowpass filter (C left, R middle) for use with thermocouples or the placement of the Rsense needed for RTD's.
Further it is possible to enable Rsense-Sharing with 0R-Resistor or solder bridges (R right).
For some use-cases ``PT100`` measurements or ``Type K Thermocouple``, dedicated assembly variants of the PCB exist in the repository, where the user does not 
need to reconfigure or resolder the wiring in this section.

References
----------

* :download:`Schematic Rev02 <uz_d_temperature_card_LTC2983_all_thermocouple_rev02.pdf>`
* :ref:`label_cpld_programming`

Known issues
------------

* Wrong naming convention on the PCB for the channelgroups: ``Channel A`` on the PCB actually means ``ChannelGroup A``
* The assembly variant ``All_Thermocouple`` has some lacking parts and some should be removed. REMOVE: ``R55``, ``R61`` and ``R67``. ``R44`` (A-C) to ``R47`` (A-C). ADD: At ``P1`` connect  the ``DC/DC`` labeled pin and the middle pin for power supply. Add ``0 Ohm`` resistors at Channels ``1`` to ``4`` in the ``Filter and Wiring`` section of each channelgroup.
* Those issues are solved in Rev03 and beyond.

Designed by 
-----------

Robert Zipprich (Universität Kassel / EMA) // Michael Hoerner (TH Nürnberg) in 01/2023
