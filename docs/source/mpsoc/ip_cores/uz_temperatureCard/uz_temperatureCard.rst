.. _temperature_card_IPcore_v1:

===========================
Temperature Card IP-Core V1 
===========================

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

Detailed Description
-----------------------
This digital adapter card is based on the LTC2983 temperature measurement system.
With the ability to measure different sensor types and build-in data preparation this card extends the functionality of the Ultrazohm. The total amount of 60-Channels (40 on the frontpanel, 20 internal) could be wired directly on the card or in the plug for different kind of sensors.

IP-Core
-----------------------
The temperature card is provided with an IP-core, which handles the configuration and triggers a periodical measurement. For this purpose the core contains a memory-mapped-interface, which stores the channel configurations and a freely configurable trigger-generator. To get the temperature card working, its neccessary to connect the IP-core via smart connects to the PS and map the IP-core Pins to the dedicated digital Slot, further the IP-Core is designed to work with an 100MHz clock. 

It's crucial to use the Pins as shown in the picture below, otherwise the mapping won't fit with the created CPLD-File!

.. image:: IP_Core_TempCard.png
   :height: 400

To generate the needed channel configuration, it's neccessary to read the datasheet of the `LTC2983 <https://www.analog.com/en/products/ltc2983.html>`_. For easier use of the card, there exists a C-library.
The library contains functions to provide a simple way to configure and read the Temperature Card.

Representation in software
**************************

.. _config_typedef:

.. doxygentypedef:: uz_temperaturecard_t

.. _config_struct:

.. doxygenstruct:: uz_temperaturecard_config_t
   :members:
.. doxygenstruct:: uz_temperaturecard_OneGroup
   :members:

Operation
*********

.. doxygenfunction:: uz_temperaturecard_init

.. doxygenfunction:: uz_TempCard_IF_Reset

.. doxygenfunction:: uz_TempCard_IF_Start

.. doxygenfunction:: uz_TempCard_IF_Stop

.. doxygenfunction:: uz_TempCard_IF_MeasureTemps_all

.. doxygenfunction:: uz_TempCard_IF_MeasureTemps_cyclic

How the driver could be used
--------------------------------
This library provide an easy way to use the UZ_Temperature_Card.
For easier handling, the library uses an internal structure to mirror the Registers of the Interface-IP.
The Channels can be addressed by values from 0-59 and all needed address calculation will be performed internally.
(Software Channel 0-19 equals Hardware Channel_A 0-19, Software Channel 20-39 equals Hardware Channel_B 0-19 and Software Channel 40-59 equals Hardware Channel_C 0-19).

Designed by 
-----------------------
Robert Zipprich (Universität Kassel / EMA) in 01/2023
