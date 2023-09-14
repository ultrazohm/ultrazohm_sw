.. _temperature_card_IPcore_v1:

===========================
Temperature Card IP-Core V1 
===========================

Detailed Description
--------------------
This IP-Core is designed for the LTC2983 temperature measurement system.
With the ability to measure different sensor types and built-in data preparation, this card extends the functionality of the UltraZohm.
The total amount of 60-Channels (40 on the frontpanel, 20 internal) could be wired directly on the card or in the plug for different kind of sensors.
The documentation for the Temperature Card can be e.g. found under :ref:`temperature_card_rev02` or newer.

IP-Core
-------
The temperature card is provided with an IP-core, which handles the configuration, triggers periodical measurements, and provides the results that are 
collected afterwards by the software driver.

.. note:: 

   To simplify the usage of the IP-Core and to reduce possible errors, a tcl script was created, that places all necessary connections automatically.
   Only the hardware ports have to be assigned manually, according to the used digital adapter card slot.
   To use this, open the Vivado block design and run the following commands separately in the TCL-console.
   "cd [ get_property DIRECTORY [current_project] ]" 
   "cd $work_directory"
   "source ../../ip_cores/Temperature_Card_Interfrace_V1/temp_card_interface.tcl"
   "create_hier_cell_temp_card_interface / temp_card_interface"

The figure below shows the IP-Core in a Vivado block design environment.

.. _ip_core_temperature_card:

.. figure:: user_hierarchy_pins.png
   :width: 600
   :align: center

   IP-Core ``Temperature Card V1``

Depending on the physical adapter board slot that you are using for the adapter board, the IP-Core has to be connected to the pins of the proper adapter board slot. 
Here it is shown at the example of adapter board slot ``D4``, where ``_Ch4`` refers to adapter board slot ``D4``. Pay attention 
that no other pins regarding ``_Ch4`` are present in the block design. Delete them to avoid errors during the build or damage to the hardware. Since all three channelgroups ``A-C`` share the common 
reset signal ``LTC_resetn_1``, all other reset signals are left unconnected. For a more detailed description on how to implement the IP-Core into your block design, refer to :ref:`temperature_card_rev02`.

.. _ip_core_temperature_card_and_pins:

.. figure:: outside_user_ports.png
   :width: 700
   :align: center

   Pinout and connection to correct pins at the example of adapter board slot ``D4``

Software Driver
---------------
The LTC2983 is a powerful and complex temperature measurement IC. Since this documentation cannot cover all possible use-cases, just some relevant and specific ones are highlighted 
within the scope of this page. In particular, two examples are provided that match the existing assembly variants of the PCB repository, ``Thermocouples Type K`` and ``PT100`` resistance temperature detectors (RTD`s).
The driver is structured in order to reflect the underlying hardware with its three channelgroups ``A-C``. Within each channelgroup there are 20 Channels ``00-19`` that have to be configured and where 
results can be read from. An easy way to get the configuration-words for each channel is provided with fixed ``#defines``.
Inside the ``uz_temperaturecard.h`` the defines from Analog Devices (producer of the LTC2983) are present.
With those defines, simply use bitwise-or to create the configuration-word for different kind of sensors or use examples below.
It is necessary to read the datasheet of the `LTC2983 <https://www.analog.com/en/products/ltc2983.html>`_ carefully, especially page 16 to 54 for understanding how the LTC2983 needs to be configured when not using provided examples.

Regardless of what type of sensor configuration you want to use, some general steps for creating an instance of the IP_Core driver are similar for all use-cases. 
Below the necessary steps are shown at the example of one temperature adapter board mounted in adapter board slot ``D4``.

1. In Vitis, in the Baremetal project under the folder ``hw_init`` create a new file ``uz_temperature_card_init.c`` 
2. Include necessary files and create a ``config`` struct as well as an init function for one instance:

.. code-block:: c
 :caption: Example of uz_temperature_card_init.c

 #include "../include/uz_temperature_card_init.h"
 #include "../uz/uz_HAL.h"
 #include "../uz/uz_global_configuration.h"
 #include "xparameters.h"
 
   struct uz_temperaturecard_config_t config_temperature_card = {
   // general config
   .base_address = XPAR_UZ_USER_TEMP_CARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR,
   .ip_clk_frequency_Hz = 100000000U,
   .Sample_Freq_Hz = 5U, // we are fine with 5 Hz since the LTC2983 itself isn't that fast with updating the results
   // channelgroup A
   .Configdata_A = {0U}, // for proper configuration we will come back later
   // channelgroup B
   .Configdata_B = {0U},
   // channelgroup C
   .Configdata_C = {0U}
   };

 uz_temperaturecard_t* initialize_temperature_card_d4(void){
	return (uz_temperaturecard_init(config_tempcard));
 }

3. In the ``include`` folder, create a header file ``uz_temperature_card_init.h``
4. Include necessary files and the function prototype of your init routine:

.. code-block:: c
 :caption: Example of uz_temperature_card_init

 #pragma once
 #include "../IP_Cores/uz_temperaturecard/uz_temperaturecard.h"

 uz_temperaturecard_t* initialize_temperature_card_d4(void);

5. In the Global_Data header file ``globalData.h``, include necessary header and add an object pointer of the respective type in the ``object_pointer_t`` struct, as well as channelgroup data structs to the ``actualValues``:

.. code-block:: c
 :caption: Lines to add in Global_Data header file

 ... 
 #include "IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
 ...

 typedef struct{
 ...
 uz_temperaturecard_t* temperature_card_d4;
 ...
 }object_pointers_t;

 typedef struct _actualValues_ {
 ...
 uz_temperaturecard_OneGroup channel_A_data;
 uz_temperaturecard_OneGroup channel_B_data;
 uz_temperaturecard_OneGroup channel_C_data;
 ...
 } actualValues;

6. In ``main.c``, initialize an instance of the driver and assign it to the object pointer structure in the Global_Data inside the ``init_ip_cores`` case. Also ``Reset`` and ``Start`` the IP-Core by calling respective functions:

.. code-block:: c
 :caption: Example of init in main.c
 
 ...
 case init_ip_cores:
 ...
 Global_Data.objects.temperature_card_d4 = initialize_temperature_card_d4();
 uz_TempCard_IF_Reset(Global_Data.objects.temperature_card_d4);
 uz_TempCard_IF_Start(Global_Data.objects.temperature_card_d4);
 ...
 break;

7. In ``main.h``, include your init header file  ``#include "include/uz_temperature_card_init.h"``.
8. In ``isr.c``, now you can read the result values of the IP Core and use them:

.. code-block:: c
 :caption: Example of reading temperature results in isr.c to the channgroup data structs

 ...
 uz_TempCard_IF_MeasureTemps_cyclic(Global_Data.objects.temperature_card_d4);
 Global_Data.av.channel_A_data = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d4, 'A');
 Global_Data.av.channel_B_data = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d4, 'B');
 Global_Data.av.channel_C_data = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d4, 'C');
 ...

9. E.g. ``Global_Data.av.channel_A_data.temperature[4]`` will contain the temperature in degrees celsius of ``Ch5`` of ``ChannelGroup A``.

Configuration Examples
----------------------
Following, some example applications and respective configurations, hardware- and software-wise are presented. 
As you might remember from the above steps, we left the ``.Configdata_`` ``A-C`` all ``={0U}``, and therefore, unconfigured. 
The above steps are mandatory for all use-cases. Below the configuration for the specific use-cases for the specific assembly variants of the PCB are described.

16x Type K Thermocouple at ChannelGroup A
-----------------------------------------
This example shows how to read ``16 Type K thermocouples`` connected to ``ChannelGroup A``, using the temperature card in addition 
with an external connector box, designed for Type K thermocouples. 

PCB assembly variant
********************
The figure below shows the temperature adapter board ``Rev03`` with assembly variant ``All_Thermocouple``.
The main characteristics of this assembly variant are highlighted. 
In this variant, channel groups ``A`` to ``C`` are equipped for single-ended thermocouple measurement at ``Ch05`` to ``Ch20`` and each channel group has 
an own cold junction compensation (CJC), using a ``PT100`` sensor, located in the external connector box. Together with a necessary sense resistor, 
the CJC is connected to ``Ch1`` to ``Ch4`` of the LTC2983 of each channel group.

.. _all_thermocouple_pcb:

.. figure:: TypeK_Variant.png
   :width: 800
   :align: center

   uz_d_temperaturecard_ltc2983, Rev03, assembly variant: All_Thermocouple

External connector box
**********************
The external box shown below consists of mainly three components.
 * The ``uz_per_thermocoupler_connector`` PCB
 * The housing: ``Fischer Elektronik AKG 165 038 100 SA`` (with customized cutouts, see CAD data in the PCB repo of ``uz_per_thermocoupler_connector``)
 * Pre-assembled cable ``Samtec MMSD-15-xxx-x-xx.xx-D-P-LDX`` for connecting the external box to one of the ChannelGroup connectors

.. _external_box_front:

.. figure:: typek_box_front.png
   :width: 800
   :align: center

   Front view of the external box.

The numbers above the Type K connectors refer to the array entry number in the variable ``float temperature[20]`` in ``struct uz_temperaturecard_OneGroup``, that 
holds the results of the 20 measurement channels of each channel group. Since ``Ch1`` to ``Ch4`` (respectively array entry 0 to 3) are used for the cold junction compensation 
measurement, ``Ch5`` (array index 04) is the first channel number to be used for TypeK sensors.

.. _external_box_back:

.. figure:: typek_box_back.png
   :width: 800
   :align: center

   Rear view of the external box  

.. warning::For connecting the box to the temperature adapter board, only use Samtec cable ``MMSD-15-xxx-x-xx.xx-D-K-LDX``

Software driver configuration
*****************************

.. code-block:: c
  :caption: Configuration for Thermocouple Type K measurements at channelgroup A for 16 channels

   struct uz_temperaturecard_config_t config_temperature_card = {
   // general config
   .base_address = XPAR_UZ_USER_TEMP_CARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR,
   .ip_clk_frequency_Hz = 100000000U,
   .Sample_Freq_Hz = 5U,
   // channelgroup A
   .Configdata_A = {0U},
   .Configdata_A[0] = 0U,
   .Configdata_A[1] = SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k,
   .Configdata_A[2] = 0U,
   .Configdata_A[3] = SENSOR_TYPE__RTD_PT_100 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__100UA | RTD_STANDARD__EUROPEAN,
   .Configdata_A[4] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[5] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[6] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[7] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[8] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[9] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[10] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[11] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[12] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[13] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[14] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[15] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[16] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[17] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[18] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   .Configdata_A[19] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
   // channelgroup B
   .Configdata_B = {0U},
   // channelgroup C
   .Configdata_C = {0U}
   };

As can be seen, we now assigned configuration words for almost every of the 20 channels of ``ChannelGroup A``. Each configuration word is created by 
bit-wise OR of several ``#defines``. ``Ch2`` (array index 1) is configured for beeing connected to a 1kOhm sense resistor, that the LTC2983 uses for measuring its 
excitation current of the ``PT100`` RTD that is connected to ``Ch4`` (array index 3), and is excited with a ``100µA`` current. This ``PT100`` serves as the CJC measurement device for 
the Thermocouples. The 16 remaining channels ``Ch5`` to ``Ch20`` are configured for single-ended ``Type K`` thermocouples that refer to ``Ch4`` for internal CJC within the LTC2983.
With this, the user is able to simply read the temperature results in degrees celsius directly from the ``float temperature[20]`` variable in ``struct uz_temperaturecard_OneGroup`` as mentioned 
at the beginning of the driver section.

.. note:: 

   If fewer channels than 16 are sufficient for your application, set the not necessary channels in the ``config_temperature_card`` struct to ``0U``. 
   Since the LTC2983 updates all **configured** channels within one ChannelGroup one after another, fewer configured channels will lead to a faster 
   update rate of the measurements!  

PT100
-----
some example

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




PT100
-----
In this example the temperature card is used to read six winding temperatures from an electric machine which uses PT100 sensors.
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






Driver Reference
****************

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

.. doxygenfunction:: uz_TempCard_IF_MeasureTemps_cyclic

.. doxygenfunction:: uz_TempCard_IF_get_channel

.. doxygenfunction:: uz_TempCard_IF_average_temperature_for_valid

Designed by 
-----------------------
Robert Zipprich (Universität Kassel / EMA) // Michael Hoerner (TH Nürnberg) in 01/2023
