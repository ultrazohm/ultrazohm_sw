.. _temperature_card_IPcore_v1:

===========================
Temperature Card IP-Core V1 
===========================

Detailed Description
--------------------
This IP-Core is designed for the LTC2983 temperature measurement system.
With the ability to measure different sensor types and build-in data preparation this card extends the functionality of the Ultrazohm.
The total amount of 60-Channels (40 on the frontpanel, 20 internal) could be wired directly on the card or in the plug for different kind of sensors.
The documentation for the Temperature Card can be found under :ref:`temperature_card_v1`.

Functionality
-------------
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

IP-Core
-------
The temperature card is provided with an IP-core, which handles the configuration and triggers a periodical measurement.
For this purpose the core contains a memory-mapped-interface, which stores the channel configurations and a freely configurable trigger-generator.
To get the temperature card working, its neccessary to connect the IP-core via smart connects to the PS and map the IP-core Pins to the dedicated digital Slot, further the IP-Core is designed to work with an 100MHz clock.

It's crucial to use the Pins as shown in the picture below, otherwise the mapping won't fit with the created CPLD-File!

.. image:: IP_Core_TempCard.png
   :height: 400

The I/O for the IP-Core and the Temperaturecard is based on the old constrain-files.

To generate the needed channel configuration, it's neccessary to read the datasheet of the `LTC2983 <https://www.analog.com/en/products/ltc2983.html>`_.
For easier use of the card, there exists an UZ-Driver, which is located inside the Folder ``IP_Cores``.
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

.. doxygenfunction:: uz_TempCard_IF_get_channel

.. doxygenfunction:: uz_TempCard_IF_average_temperature_for_valid

How the driver could be used
----------------------------
This library provide an easy way to use the UZ_Temperature_Card.
The Channels can be addressed by values from 0-59 and all needed address calculation will be performed internally.
(Software Channel 0-19 equals Hardware Channel_A 0-19, Software Channel 20-39 equals Hardware Channel_B 0-19 and Software Channel 40-59 equals Hardware Channel_C 0-19).

An easy way to get the configuration-words for each channel is given with fixed defines.
Inside the ``uz_temperaturecard.h`` the defines from Analog Devices are present.
With those defines, simply use bitwise-or to create the configuration-word for different kind of sensors.
It is neccessary to read the Datasheet of the `LTC2983 <https://www.analog.com/en/products/ltc2983.html>`_ carefully, especially page 16 to 54 for understandig how the LTC2983 needs to be configured.

To start using the Temperature Card with the provided IP-Core and UZ-Driver, an initialisation is needed.
The following is an example to read the internal PT100 of channel A.

.. code-block:: c
  :caption: Initialization of IP-Core driver instances

   // Init the Temperature-Card on D4 with 5Hz sampling frequency to measure the internal PT100 from Channel A. All other Channels were forced to zero (like C_19).
   struct uz_temperaturecard_config_t config_tempcard = {
      .base_address = XPAR_UZ_DIGITAL_ADAPTER_D4_ADAPTER_TEMPCARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR,
      .ip_clk_frequency_Hz = 100000000U,
      .Sample_Period = 5U,

      // free channel
      .Configdata_A[0] = 0,
      // Config of the 1k R_sense (Attention! fixed-point with 1/1024 resolution), Expression equals 0xE80FA000
      .Configdata_A[1] = 0x00000000|SENSOR_TYPE__SENSE_RESISTOR|0XFA000,
      // free channel
      .Configdata_A[2] = 0,
      // Config of the PT100, Expression equals 0x60854000
      .Configdata_A[3] = 0x00000000|SENSOR_TYPE__RTD_PT_100|RTD_RSENSE_CHANNEL__1|RTD_NUM_WIRES__2_WIRE|RTD_EXCITATION_MODE__NO_ROTATION_SHARING|RTD_EXCITATION_CURRENT__100UA|RTD_STANDARD__EUROPEAN,
		// free channel
      .Configdata_A[4] = 0,

      ...

      // free channel
      .Configdata_C[19] = 0,
   };

   // create the handler and store it inside the Global_Data
	Global_Data.objects.uz_TempCard = uz_temperaturecard_init(config_tempcard);

   // reset the card to force an update of the channels
	uz_TempCard_IF_Reset(Global_Data.objects.uz_TempCard);

   // start the periodical measurement
	uz_TempCard_IF_Start(Global_Data.objects.uz_TempCard);

After calling ``uz_TempCard_IF_Start``, the IP-Core will do all measurements by itself and the user has no need to interact with the Card anymore.

To read the measured temperatures, the UZ-Driver provides two ways.
The first way is calling the function ``uz_TempCard_IF_MeasureTemps_all``, which will read the result from every channel and updates the stored measurements inside the driver. 
This function is only for Data-Logging-purpose since it will costs a lot of ISR-time, never use this function in fast control-loops!

The second way is preferred since it is compatible with fast control-loops.
To update the results inside the Driver, call the function ``uz_TempCard_IF_MeasureTemps_cyclic`` at the beginning of the ISR.
This function will only update one channel per call, but uses an incremental pointer.
To update every channel of the TemperatureCard, 60 calls are needed.

.. code-block:: c
  :caption: Reading the measurements from the IP-Core driver instances

   void ISR_Control(void *data)
   {
   // Reads out the global timer, has to be the first function in the isr
      uz_SystemTime_ISR_Tic();

      // Update Data and measurements
      ReadAllADC();
      update_speed_and_position_of_encoder_on_D5(&Global_Data);
      uz_TempCard_IF_MeasureTemps_cyclic(Global_Data.objects.uz_TempCard);
    ...
      // More ISR-Stuff
   };

Results
-------
The measured temperatures are stored inside the driver instance. 
For each LTC2983 on the temperature card, one group is declared and contains the configuration, raw-value, temperature value and error indicator for each channel of one LTC2983.
This allows the user a comprehensive use of the measured values with some manual implementations.
The driver will perform a small check if the measurement is valid and calculate the temperature value from the raw value and stores the results in the temperature-array inside the group.
If the measurement is not valid, the results in the temperature-array is fixed to the impossible value of -333.3f.

To get the temperature value, a direct access to the Global_Data is needed.

.. code-block:: c
  :caption: Get the temperature value for the PT100 on Channel_A

   float Temp_Winding = 0.0f;

   void ISR_Control(void *data)
   {
       // Some ISR-Stuff
      Temp_Winding = Global_Data.objects.uz_TempCard.Channel_A.temperature[3];
    ...
       // More ISR-Stuff
   };


Example
-------
In this example the temperaturecard is used to read six winding temperatures from an electric machine which uses PT100 sensors.
Since the mean value is of interest and non-valid values (e.g. due to EMI) should not make the average unusable, a specific averaging function is used.

.. code-block:: c
  :caption: ``main.c``

   // pre-loop
   #include "IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
   uz_temperaturecard_t* uz_Tempcard = NULL;
   struct uz_temperaturecard_config_t t_config = {
      .base_address = XPAR_UZ_USER_TEMP_CARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR,
      .ip_clk_frequency_Hz = 100000000,
      .Sample_Freq = 100,
      .Configdata_A = {0},
      .Configdata_A[1]  = 0xE80FA000,
      .Configdata_A[3]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
      .Configdata_A[5]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
      .Configdata_A[7]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
      .Configdata_A[9]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
      .Configdata_A[11] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
      .Configdata_A[13] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
      .Configdata_B = {0},
      .Configdata_C = {0}};

   // in switch-case
   case init_ip_cores:
      // uz tempcard
      uz_Tempcard = uz_temperaturecard_init(t_config);
      uz_TempCard_IF_Reset(uz_Tempcard);
      uz_TempCard_IF_Start(uz_Tempcard);


.. code-block:: c
  :caption: ``isr.c``

   // pre-loop
   #include "../IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
   extern uz_temperaturecard_t* uz_Tempcard;
   uz_temperaturecard_OneGroup channel_A_data;
   float average = 0.0f;

   // in isr
   uz_TempCard_IF_MeasureTemps_cyclic(uz_Tempcard);
   channel_A_data = uz_TempCard_IF_get_channel(uz_Tempcard, 'a');
   average = uz_TempCard_IF_average_temperature_for_valid(channel_A_data, 0U, 13U);


Designed by 
-----------------------
Robert Zipprich (Universität Kassel / EMA) in 01/2023
