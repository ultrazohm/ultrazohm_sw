.. _ipCore_EnDat:

=======
EnDat22
=======

The EnDat22 IP-Core (``EnDat``) evaluates signals of an EnDat22 based absolute singleturn encoders and is compatible to :ref:`dig_encoder_v1`.
It features the positional and speed calculation. 

Position
  Positional information for the actual and the two values before is available. The actual position can also provide its age. The position is available in radiant inside the driver environment and in raw values in the FPGA environment. 

Time difference
  The time difference between two positional information is available in the FPGA and the SOC Part. It is used to calculate the rotational speed and useful to have an estimation of the frequency for new positional values.

Positional difference
  The raw positional difference is available solely inside the SOC Part and facilitates the calculation of rotational speed.

Rotational Speed
  The speed is calculated in the driver and can be output with RPM or RAD/s and ca n be filtered by a configurable filter. 


IP-Core Hardware
================

The IP-Core is generated using Matlab/Simulink HDL-Coder based on the model ``UZ_EnDat.slx`` (in ``ultrazohm_sw/ip_cores/uz_EnDat_IPCore/Simulink_Model/UZ_EnDat.slx``).


Vivado integration
------------------

.. figure:: uz_EnDat_vivado.png
  :align: center

  Vivado block design of EnDat22 IP-Core.

.. warning:: The IP-Core (IPCORE_CLK) has to be sourced by a clock with :math:`100 MHz`! The auxialliary clock (CLK50MHZ) has to be fed with a :math:`50 MHz` Signal


Table *Interfaces of the EnDat22 IP-Core* lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. csv-table:: Interfaces of the EnDat22 IP-Core
   :file: uz_EnDat_register_mapping.csv
   :widths: 50 50 50 50 200
   :header-rows: 1
   :align: center


Software driver
===============

The software driver for the IP-Core has multiple use cases - with the configuration and calculation being the most important ones. 

Init Functions
---------------
.. doxygentypedef:: uz_EnDat_t
.. doxygentypedef:: controlword


.. doxygenfunction:: uz_EnDat_IP_core_init

This function initializes a 25-Bit EnDat22 sensor with default settings. The IP-Core has to be named "uz_EnDat_0" in Vivado and have an operating frequency of 100 MHz.
Use this function to initialize the sensortype ECN125 without further adjustment necessary. Generally this method is not advised to be used due to its inflexibility.

.. doxygenfunction:: uz_EnDat_IP_core_custom_init

This function initializes a EnDat22 sensor using settings and supporting various sensor resolutions. The IP-Core has to be named "uz_Endat_0" in Vivado and have an operating frequency of 100 MHz.
For adjusting the configuration of the EnDat22 sensor, please edit the file ``uz_EnDat_IP_core_init.c``. Changes during runtime are prohibited.

.. doxygenfunction:: uz_EnDat_IP_core_expert_init

This function is the most flexible one when it comes to configuration of the IP-Core since every parameter is handed over by the call function. The name of the IP-Core the frequency are adjustable and multiple instances are possible.
You should not deviate from the 100 MHz Clock however. Keep in mind that using this Init-Method no default values are provided and one must carefully set every setting manually. 

Control Functions
-----------------

There are multiple functions and settings used to control the IP-Core. The most basic way of controlling the IP-Core is the controlword.

Table *Controlword* shows the content of the controlword to 



.. csv-table:: EnDat22 IP-Core controlword
  :file: ./uz_EnDat_controlword.csv
  :widths: 25 25 75 50
  :header-rows: 1
  :align: center

An exemplary control word would look like this: *0xB407* for an 25-Bit EnDat22 Sensor.

The sensor operating frequency is set by a divider variable, ``uz_EnDat_frequency`` with the alias ``uz_EnDat_frequency_selector``. The following operating frequencies are supported by this IP-Core:

.. doxygenenum:: uz_EnDat_frequency_selector
 
The divider value can be set manually or selecting a frequency enum which is then transferred by the following function to the proper divider.

.. doxygenfunction:: uz_EnDat_get_clk_frequency_divider_from_frequency

With both the control word and the divider setup you are good to go to start using that IP-Core in conjunction with the basic initialization functions: ``uz_EnDat_IP_core_init`` and ``uz_EnDat_IP_core_custom_init.c``.

Additionally there are multiple adjustment settings so called "factors" that you can adjust to establish a connection to the sensor.

.. doxygenenum:: uz_EnDat_factors

The factors can be set by the following function with the factor enum as selector and the value you want to write.

.. doxygenfunction:: uz_EnDat_write_factor

Experimentally known-good values are to be found in the appendix of this documentation.

An extensive description can be found in the Thesis to the EnDat22 connector. 

A short description follows:


.. list-table:: Factor description
  :widths: 25 75 25
  :header-rows: 1
  :align: center

  * - Factor
    - Description
    - Default
  
  * - #1 - DATAFLOW
    - This factor changes the timing where the RS485 data line transceiver is set from Read to Write mode.
    - 100 - relative
  
  * - #2 - RECOVERYTIME
    - This factor changes the bus pause period after a telegram. Per default it is set to about 30 microseconds regardless of the operating frequency. By adjusting this value you can change the absolute time from 0 to about 415 micro seconds.
    - 100 - relative
    
  * - #3 - INITIALOFF
    - This factor shortens or adds to the time which is waited upon a full cold boot of the FPGA before attempting to communicate to the sensor. Default ist about 5 miliseconds. 
    - 100 - relative
  
  * - #4 - DATACLKSYNC
    - This factor changes the relative position of the DATA-TX to the CLK-TX line. With that you can granularly adjust the offset inbetween those related lines.
    - 100 - relative
    
  * - #5 - TELEGRAMLEN
    - This factor adjusts the total telegram length excluding the bus pause period. Default is about 48 clocks which is enough for a 25-bit sensor.
    - 100 - relative
  
  * - #6 - SYNCRESPONSE
    - This factor changes the relative position of the DATA - RX line to the internal clock. With that you can adjust the response if is on the edge of the internal clock leading to undefined states.
    - 0 - absolute unsigned
  
  * - #7 - EXTRASHIFT
    - This factor changes the internal alignment inside the FPGA to ensure that the right part of the answer is interpreted as the payload. Use this factor if you have n-cycles indicated whereas physically there was only one turn.
    - 0 - absolute signed

Fetching positional values
--------------------------

With the factors and the control function set the basic set-up is complete. Now there are two possibilities to fetch the positional information. One is the basic one just returning the position value:

.. doxygenfunction:: uz_EnDat_read_pos_and_return_radiant

You can also fetch an extended positional information which also incorporates the age of the position. With this function you can only fetch the most recent position. Its important to only call the function once with the update bit set to high.

.. doxygenfunction:: uz_EnDat_read_pos_t0_as_radiant_and_age_wrapper
  

Fetching rotational speed values
--------------------------------

For fetching the rotational speed the following function is most suited. It will return the revolution of the sensor in RPM.

.. doxygenfunction:: uz_EnDat_calc_revs_from_fpga_pos_dif_and_time

If RPMs are not suiting you - feel free to use this converter function to change it to rad/s.

.. doxygenfunction:: uz_EnDat_rpm_to_rad_per_second_converter


Filter function
---------------

To filter some noises from any signal you like (intended for speed though) you can use this function which will filter with a parameter.

.. doxygenfunction:: uz_EnDat_rpm_smoothening


Diagnose functions
------------------

There are multiple diagnostic functions that provide interesting insights.

This function will read the length of the actual response. It should never be lower then the total amount of bytes need to read in the answer (2 + 5 + Sensor precision)

.. doxygenfunction:: uz_EnDat_read_reponselength_and_convert_to_float

This factor is an indicator about the quality of the connection with values smaller then 99 indicating a faulty sync.

.. doxygenfunction:: uz_EnDat_calculate_sync_quality_indicator

This function updates the statusword (which is mostly a readback copy of the control word) and the errorbit provided by the sensor.

.. doxygenfunction:: uz_EnDat_fetch_statusword_and_errorbit_from_EnDat_object_and_write_to_object

Usage Examples
==============

The following examples provide a valid suggestion how to set up for usage of this IP-Core.

Init in Main
------------

.. code-block:: c

  Global_Data.objects.EnDat_master_pointer = uz_EnDat_IP_core_custom_init();

  //or.. if you are a true expert :o)

  Global_Data.objects.EnDat_master_pointer = uz_EnDat_IP_core_expert_init(XPAR_UZ_USER_UZ_ENDAT_0_BASEADDR, 100000000U, 100, 100, 100, 100, 100, 0, 0, uz_EnDat_set_output_enable_in_controlword(uz_EnDat_enable_config_evaluation_in_IP(uz_EnDat_set_sensor_precision_in_controlword( uz_EnDat_set_operation_mode(ENDAT_CONTROLWORD_DEFAULT, uz_EnDat_Encoder_send_position_values), uz_EnDat_25_bit))), 1);


Readout Sensor in fast cycle (e.g. ISR)
---------------------------------------

Fetching positional information with age:

.. code-block:: c

    Global_Data.av.theta_mech = uz_EnDat_read_pos_t0_as_radiant_and_age_wrapper(Global_Data.objects.EnDat_master_pointer, -1, false, true);
    Global_Data.av.EnDat_pos_age = uz_EnDat_read_pos_t0_as_radiant_and_age_wrapper(Global_Data.objects.EnDat_master_pointer, 0, true, false);

Fetching positional information simple way:

.. code-block:: c
  
    Global_Data.av.theta_mech = uz_EnDat_read_pos_and_return_radiant(Global_Data.objects.EnDat_master_pointer,uz_EnDat_pos_t0); 


Fetch status in slow cycle (e.g. slow ISR)
------------------------------------------

.. code-block:: c

    Global_Data.av.EnDat_value_calc_time = uz_EnDat_time_elapsed_ns_to_s_converter(uz_EnDat_read_time_elapsed(Global_Data.objects.EnDat_master_pointer, uz_EnDat_elapsed_t0_t1));
    Global_Data.av.EnDat_value_response_length = uz_EnDat_read_reponselength_and_convert_to_float(Global_Data.objects.EnDat_master_pointer);
    Global_Data.av.EnDat_sync_quality = uz_EnDat_calculate_sync_quality_indicator(Global_Data.objects.EnDat_master_pointer, Global_Data.av.EnDat_value_calc_time);
    uz_EnDat_fetch_statusword_and_errorbit_from_EnDat_object_and_write_to_object(Global_Data.objects.EnDat_master_pointer);





Appendix
=========

known-good values
-----------------

.. csv-table:: EnDat22 known-good settings
  :file: ./uz_EnDat_known_good_settings.csv
  :widths: 25 25 25 25 25 25 25 25 25 25
  :header-rows: 1
  :align: center


proposed slow async clock function
----------------------------------

If not implemented by the time you read the documentation, feel free to add this function. Call then "async_slow_clk_cycle_100ms();" inside "case infinite_loop:".

.. doxygenfile:: slow_cycle.h


.. code-block:: c

  #include <stdint.h>
  #include <stdbool.h>
  #include "../globalData.h"
  #include "../IP_Cores/uz_EnDat/uz_EnDat.h"
  #include "../uz/uz_global_configuration.h"
  #include "../uz/uz_SystemTime/uz_SystemTime.h"

  void async_slow_clk_cycle_100ms(void);
  void async_slow_clk_cycle_100ms_wrapper(void);



.. code-block:: c

  #include "../include/slow_cycle.h"

  extern DS_Data Global_Data;

  void async_slow_clk_cycle_100ms(void) {
    unsigned long int act;
    static unsigned long int old;
    static bool skip = false;
    act = uz_SystemTime_GetUptimeInMs();

    if (!skip && (act % (100) < 50)) {
        async_slow_clk_cycle_100ms_wrapper();
        skip = true;
        Global_Data.av.slow_cycle_period_ms = (float)(act - old);
        old = act;
    }
    if (((old + 99) < act) || (act < old)) {
        skip = false; 
    }
  }

  void async_slow_clk_cycle_100ms_wrapper(void) {
    //EXECUTE HERE
    Global_Data.av.EnDat_value_calc_time = uz_EnDat_time_elapsed_ns_to_s_converter(uz_EnDat_read_time_elapsed(Global_Data.objects.EnDat_master_pointer, uz_EnDat_elapsed_t0_t1));
    Global_Data.av.EnDat_value_response_length = uz_EnDat_read_reponselength_and_convert_to_float(Global_Data.objects.EnDat_master_pointer);
    Global_Data.av.EnDat_sync_quality = uz_EnDat_calculate_sync_quality_indicator(Global_Data.objects.EnDat_master_pointer, Global_Data.av.EnDat_value_calc_time);
    uz_EnDat_fetch_statusword_and_errorbit_from_EnDat_object_and_write_to_object(Global_Data.objects.EnDat_master_pointer);
  }

