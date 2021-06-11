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
* DOUBLE CHECK the directions of the dedicated pins of the IP-core to the temperature card.

Known issues
-----------------------
* Wrong naming of the Channels. This results in a wrong assignment of the Channels. On the PCB, Channels A and B are exposes, but the Channels A and C are accessable on the front Panel.

Compatibility 
----------------------
* The version of this card is compatible with slots D1-D4.

Pinout
----------------------
The pinout is identical for each receptacle on the temperature card.

.. image:: temperature_v1/pinout_onePlug.png
   :height: 350

IP-Core
-----------------------
The temperature card is provided with an IP-core, which handles the configuration and triggeres a periodical measurement. For this purpose the core contains a memory-mapped-interface, wich stores the channel configurations and a freely configurable trigger-generator. To get the temperature card working, its neccessary to connect the IP-core via smart connects to the PS and map the IP-core Pins to the dedicated digital Slot, further the IP-Core is designed to work with an 100MHz clock. 

It's crucial to use the Pins as shown in the picture below, otherwise the mapping won't fit with the created CPLD-File!

.. image:: temperature_v1/IP_Core_TempCard.png
   :height: 400

To generate the needed channel configuration, it's neccessary to read the datasheet of the `LTC2983 <https://www.analog.com/en/products/ltc2983.html>`_. For easier use of the card, there exists a C-library.
The library contains functions to provide a simple way to configure and read the Temperature Card.

.. code-block:: c
  :linenos:
  :caption: Functions of the Temperature Card Driver

   //Handling with the Core
   uz_TempCard_IF* uz_TempCard_IF_init(uz_TempCard_IF *self);

   //Functions
   void        uz_TempCard_IF_Reset(uz_TempCard_IF_handle self);                                               // Resets the Interface-IP to write new Channel configs
   void        uz_TempCard_IF_Start(uz_TempCard_IF_handle self);                                               // Starts the Interface-IP
   void        uz_TempCard_IF_Stop(uz_TempCard_IF_handle self);                                                // Stops the Interface-IP
   uint32_t    uz_TempCard_IF_ReadBack(uz_TempCard_IF_handle self);                                            // should always return 0xAFFEAFFE, otherwise there is no TempCard_Interface at the specified address
   void        uz_TempCard_IF_setCounter(uz_TempCard_IF_handle self, uint32_t Counter);                        // Set the Counter for the internal trigger generator
   uint32_t    uz_TempCard_IF_SetConfig(uz_TempCard_IF_handle self, uint32_t ConfigWord, uint32_t Channel);    // Set the ConfigWord for the specified channel
   uint32_t    uz_TempCard_IF_GetConfig(uz_TempCard_IF_handle self, uint32_t Channel);                         // Read the Config of the specified Channel
   void        uz_TempCard_IF_SyncConfig(uz_TempCard_IF_handle self);                                          // Writes the in the struct stored config down to the Interface-IP
   uint32_t    uz_TempCard_IF_CheckSync(uz_TempCard_IF_handle self);                                           // Checks wheather the in the IP stored config is in Sync with the config stored in the struct
   void        uz_TempCard_IF_MeasureTemps(uz_TempCard_IF_handle self);                                        // Gets the Temperature-Data from all LTC2983, converts the results and stores the tempvalue in the struct
   float       uz_TempCard_IF_ReadMeasurement_Channel(uz_TempCard_IF_handle self, uint32_t Channel);           // Read the Temperature Value of the specified Channel
   uint8_t     uz_TempCard_IF_CheckMeasurement_Channel(uz_TempCard_IF_handle self, uint32_t Channel);          // Checks wheather the measurement of the Channel is valid

How the driver could be used
--------------------------------
This library provide an easy way to use the UZ_Temperature_Card.
For easier handling, the library uses an internal structure to mirror the Registers of the Interface-IP.
The Channels can be addressed by values from 0-59 and all needed address calculation will be performed internally.
(Software Channel 0-19 equals Hardware Channel_A 0-19, Software Channel 20-39 equals Hardware Channel_B 0-19 and Software Channel 40-59 equals Hardware Channel_C 0-19).

1. create needed handler and assign the IP-Base-Addresse

   ``uz_TempCard_IF* uz_Tempcard = uz_TempCard_IF_init();``

2. Perform an Initial Reset for the Interface-IP

   ``uz_TempCard_IF_Reset(uz_Tempcard);``

3. Write the Channelconfigs according to the LTC2983-Datasheet. The config-words can be determined by (https://www.analog.com/en/products/ltc2983.html)

   ``uz_TempCard_IF_SetConfig(uz_Tempcard, Configword, Channel); [Repeat this for every channel needed]``

4. Sync the Configs to the Interface-IP

   ``uz_TempCard_IF_SyncConfig(uz_Tempcard);``

5. Set a counter period, which will trigger the continuous measurement

   ``uz_TempCard_IF_setCounter(uz_Tempcard, countervalue);``

6. Start the Interface-IP

   ``uz_TempCard_IF_Start(uz_Tempcard);``

7. Fetch the Measurements in the internal structure

   ``uz_TempCard_IF_MeasureTemps(uz_Tempcard);``

8. Enjoy Temperatures

   ``uz_TempCard_IF_ReadMeasurement_Channel(uz_Tempcard, Channel);``

Its important to call ``uz_TempCard_IF_SyncConfig(uz_Tempcard)`` right after setting the configs for each channel, otherwise the needed configns won't be written to the LTC2983!

Wiring
------------------------
Since there exists many possible configuration for the temperature card, its possible to manage some wiring directly on the PCB. 

.. image:: temperature_v1/Onboard_Wiring.png
   :height: 350

This area is dedicated to implement RC-lowpass filter (C left, R middle) to use themocouples or the placement of the Rsense needed for RTD's. Further it is possible to enable Rsense-Sharing with 0R-Resistor or solder bridges (R right).
For most usecases this Filter-and-Wiring-Area should be enough, so that 9 RTD's in 2-Wire-mode can be implemented directly without the need of extra wiring. If more RTD's are needed, the user could extend the amount of sensors by chainig up to 18 RTD's on one LTC (see `LTC_Application_Note <https://www.analog.com/media/en/reference-design-documentation/design-notes/DN1035f.pdf>`_ ), but this requires special wiring which is up to the user.



References
-----------------------
* :download:`Schematic 1v00 <temperature_v1/UZ_D_Temperature_Card_LTC2983.pdf>`
* :ref:`label_cpld_programming`


Designed by 
-----------------------
Robert Zipprich (Universität Kassel / EMA) in 06/2021
