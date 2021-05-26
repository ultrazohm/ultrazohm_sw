.. _temperature_card_v1:

==========================
Temperature Card V1 
==========================

Extends the UltraZohm with a temperature measurement ability.

.. image:: temperature_v1/Overview_tempcard.png
   :height: 500

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

Detailed Description
-----------------------
This digital adapter card is based on the LTC2983 temperature measurement system.
With the ability to measure different sensor types and build-in data preparation this card extends the functionality of the Ultrazohm. The total amount of 60-Channels (40 on the frontpanel, 20 internal) could be wired directly on the card or in the plug for different kind of sensors.


Before first use
----------------------------
* Determine correct placement options for correct function
* Program CPLDs with the firmware needed for the temperature card, see :ref:`label_cpld_programming` for details

Known issues
-----------------------
none

Compatibility 
----------------------
* The version of this card is compatible with slots D1-D4.

Pinout
----------------------
The pinout is identical for each receptacle on the temperature card.

.. image:: temperature_v1/pinout_onePlug.png
   :height: 500

IP-Core
-----------------------
The temperature card is provided with an IP-Core, which handles the configuration and triggeres a periodical measurement. For this purpose the core contains a memory-mapped-interface, wich stores the channel configurations and a freely configurable trigger-generator.

To generate the needed channel configuration, it's neccessary to read the datasheet of the `LTC2983 <https://www.analog.com/en/products/ltc2983.html>`_. for easier use of the card, there will be a C-library.

Wiring
------------------------
Since there exists many possible configuration for the temperature card, its possible to manage some wiring directly on the PCB. 

.. image:: temperature_v1/Onboard_Wiring.png
   :height: 500

This area is dedicated to implement RC-lowpass filter (C left, R middle) or the placement of the Rsense needed for RTD's. Further it is possible to enable Rsense-Sharing with 0R-Resistor or solder bridges (R right).
For most usecases this Filter-and-Wiring-Area should be enough, so that 9 RTD's can be implemented directly without the need of extra wiring. If more RTD's are needed, the user could extend the amount of sensors to 18 RTD's on one LTC (see `LTC_Application_Note <https://www.analog.com/media/en/reference-design-documentation/design-notes/DN1035f.pdf>`_ ), but this requires special wiring which is up to the user.



References
-----------------------
* :download:`Schematic 1v00 <temperature_v1/UZ_D_Temperature_Card_LTC2983.pdf>`
* :ref:`label_cpld_programming`


Designed by 
-----------------------
Robert Zipprich (Universität Kassel / EMA) in 05/2021
