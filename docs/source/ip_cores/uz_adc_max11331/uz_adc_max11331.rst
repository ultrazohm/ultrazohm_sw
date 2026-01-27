.. _ipCore_adc_max11331:

===============
ADC MAX11331 V1
===============

Introduction
============

- The IP core ADC_MAX11331 in version 1 is designed to read the ADCs which are located on the :ref:`analog adapter board <analog_max11331>` and to further process the values obtained from the ADCs.
- The IP core features an AXI4 Lite interface for settings and software control.
- The conversion can be triggered by using the hardware port ``enable_measure`` for real-time control.
- The IP core ADC_MAX11331 (in contrast to the :ref:`IP core LTC2311 <ipCore_LTC2311_v3>`) does not process (offset and conversion factor) the raw values further to an SI value, instead it only provides the RAW value ``raw_measured_data`` .
- The raw value from the ADC is a ``std_logic_vector`` at the hardware interface of the IP core.

Features
********

- Up to 6 independent Serial Peripheral Interface (SPI) Masters can communicate with up to 6 independent `MAX11331 ADC <https://www.analog.com/media/en/technical-documentation/data-sheets/MAX11329-MAX11332.pdf>`_ chips, each capable of sampling up to 16 synchronous channels.
  In total up to 96 individual ADC channels are theoretically possible with one IP-Core instance.
- Each SPI Master (ADC chip) is able to read 16 single-ended or 8 differential channels.
  In order to interact with the :ref:`analog adapter board <analog_max11331>`, the interface must be set to differential.
- The IP-Core does the following tasks:

  - Initialize the 1-6 MAX11331 ADC chip(s)
  - Validate SPI communication to the ADC chip(s)
  - Send data to the ADC chip(s) in order to sample 8 differential channels (or alternatively 16 single-ended channels)
  - Read back the 16(8) ADC channels, which are sampled one after another. 

Sampling 
--------

- Each ADC chip contains one initial message and afterwards:

  - In single-ended case: Each ADC contains 16 channels, which are sampled one after each other. Hence, 16 +1 SPI messages are required to sample and send the 16 channel values.
  - In differential case: Each ADC contains 8 channels, which are sampled one after each other. Hence, 8 +1 SPI messages are required to sample and send the 8 channel values. 
  
- The initial (extra) message is required since the first message tells the ADC which channel should be sampled. Afterwards, thus from the second message ongoing the data are send (first only the odd channel numbers and than the even channel numbers)

Configuration
-------------

- The IP-Core instance needs the processor to set the registers of the MAX11331 ADC chip for the following reasons:
  
  - Configure the SPI-Clock divider
  - Configure how many MAX11331 chips are connected (number of Masters). On :ref:`analog adapter board <analog_max11331>` are three MAX11331 ADC chips, thus three Masters, used.
  - The settings required by the registers in the ADC chip(s) are set in individual SPI messages with the name of the respective register, so it is easy to change the initialization using the data sheet if necessary.
  
- Offset and conversion factor are configurable by software individually for each ADC in ``main.c``
  
  - Offset is set to zero by default
  - Conversion factor is set to 10/6.65*3.3 = 4.96241 by default due to the gain of amplifier circuit described in the hardware section of :ref:`uz_a_max11331 adapter card <MAX11331_measurement_gains>` . 

SPI Interface
-------------

- A **bidirectional** communication from the ADC to FPGA is possible, i.e., read and write SPI.

  - ``CPHA``, ``CPOL``, ``clk_div`` and ``adc_delay_offset`` of the SPI interface are configurable by software
  - The ``SCLK`` frequency scales with :math:`f_{SCLK} = \frac{ f_{SystemClock} }{2 \cdot (CLK\_DIV + 1)}` 

- IP-Core clk frequency is typically 100MHz: 
  
  - The SPI-Clock is generated internally by logic of clock divider. You can change its value from the IP-core using the SPI-Clock divider.
  - Clock divider 0x1, set SPI-Clock to 50Mhz. 
  - Clock divider 0x2, set SPI-Clock to 25Mhz.
  - Clock divider 0x3, set SPI-Clock to 16.6Mhz and so on. 
  - The SPI SCK frequency will be given by: IP-Core clk frequency / (2^(clock divider))
  - The SPI SCK frequency of 16.67MHZ(= 0x3) is used in default.

ADC Trigger
-----------

- Continuous and hardware (PL) triggered operation mode can be chosen by ``trigger_mode``. Hardware (PL) triggered interface is designed for real-time requirements in time-critical applications:
  
  - There is an input pin to trigger the start sampling when it has the value ``1``. 
  - Changing the trigger value during sampling has no effect. 
  - The trigger pin is only read when there is no sampling active. 
  - If the trigger pin is fix to ``1``, the IP-Core will continuously sample the 16(8) channels using the 17(9) messages explained before.
  - It is important to note that the 16(8) channels of an ADC chip are sampled in sequence, which must be known if the data is to be used in the control loop.  
  - The IP core updates all channel outputs as soon as the last channel has been sampled and read. Therefore you will not notice how the channels are actually sampled, but all 16(8) channels are updated simultaneously at the IP core output in the FPGA.
	
- Output is supplied to the PL-ports of the IP-Core as well as to the AXI4 over the TCM.

AXI Interface
-------------

Table :ref:`ipCore_adc_max11331_interfaces` lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. _ipCore_adc_max11331_interfaces:

.. csv-table:: Interface of adc_max11331 IP-Core
   :file: adc_max11331_register_mapping.csv
   :widths: 50 50 50 50 50 50 200
   :header-rows: 1

Default Setups
**************

The MAX11331 can be configured in multiple ways as 

.. figure::  MAX11_measurement_variants.png
   :width: 800

   Analog input configurations and waveforms, see Table 8 in [MAX11331_data_sheet]_ 

.. figure::  MAX11_register_combinations_commented.png
   :width: 800

   Register configurations, see Table 9 in [MAX11331_data_sheet]_ 

Differential 
------------

In differential mode, the ip core configures all channels with the following register set, resulting in 8 differential inputs with an input range of ±Vref.

- ``UNIPOLAR = 0``
- ``BIPOLAR = 1``
- ``RANGE = 1``
- ``PDIFF_COM = 0``

This configuration is used in the uz_a_max11331 adapter card for :ref:`MAX11331_differential_measurement` .

Single-ended 
------------

In differential mode, the ip core configures all channels with the following register set, resulting in 16 single-ended inputs (referenced to ground of the UltraZohm) with an input range of 0..Vref.

- ``UNIPOLAR = 0``
- ``BIPOLAR = 0``
- ``RANGE = 1``
- ``PDIFF_COM = 0``
  
Note that the ``UNIPOLAR`` register takes precedence over the ``RANGE`` and ``BIPOLAR`` registers.

Software Driver
===============

Configuration Procedure
***********************

The test bench function below displays an example of how to configure and use the IP core.
In this example the hardware trigger in the FPGA is used but instead the continuous sampling can be used as well.

The following settings are set globally for each IP-Core instance and are valid for all three masters (all three ADC chips on one adapter board):

- base_address
- ip_clk_frequency_Hz
- trigger mode (either PL triggered or continuous sampling)
- cpha
- cpol
- adc_delay_offset
- clk_div

The following settings are set on a per channel basis within an IP-Core instance:

- conversion_factor
- offset

Example initialization of three IP-Core driver instances:

.. code-block:: c
  :caption: Initialization of IP-Core driver instances

   #define XPAR_A3_ADC_MAX11331_IP_CORE_FREQUENCY 100000000U
   #define DEFAULT_MAX11331_CONVERSION_FACTOR 1.0f
   #define DEFAULT_MAX11331_INTEGER_BITS 14
   #define DEFAULT_MAX11331_FRACTIONAL_BITS 4
   #define DEFAULT_MAX11331_OFFSET 0

   void uz_adcMax11331_ip_core_init(void)
   {
       //Parameter set for one MAX11331 chip, thus one master
       struct uz_adcMax11331_config_t default_configuration = {
           .base_address = XPAR_UZ_ANALOG_ADAPTER_A3_ADAPTER_ADC_MAX11331_A3_BASEADDR,
           .ip_clk_frequency_Hz = XPAR_A3_ADC_MAX11331_IP_CORE_FREQUENCY,
           .channel_config = {
               .conversion_factor = DEFAULT_MAX11331_CONVERSION_FACTOR,
               .conversion_factor_definition = {
                   .is_signed = true,
                   .integer_bits = DEFAULT_MAX11331_INTEGER_BITS,
                   .fractional_bits = DEFAULT_MAX11331_FRACTIONAL_BITS},
               .offset = DEFAULT_MAX11331_OFFSET,
           },
           .trigger_mode=pl_trigger,
           .cpol = 1U,
           .cpha = 1U,
           .master_select = UZ_ADCMAX11331_MASTER1 | UZ_ADCMAX11331_MASTER2  | UZ_ADCMAX11331_MASTER3,
           .adc_delay_offset = 0,
		   .clk_div = UZ_ADCMAX11331_SPI_CLK_16_67MHZ};

	   //1.) Create the instance of the first Max11331 adapter card with one or may several master = several physical Max11331 chips
       uz_adcMax11331_t *instance_1 = uz_adcMax11331_init(default_configuration);

       // Apply same configuration to all following instances, despite the base address of the FPGA IP Core
       //2.) Create the instance of the second Max11331 adapter board with one or may several master = several physical Max11331 chips
       default_configuration.base_address = XPAR_UZ_ANALOG_ADAPTER_A1_ADAPTER_A1_ADC_MAX11331_BASEADDR;
       uz_adcMax11331_t *instance_2 = uz_adcMax11331_init(default_configuration);
	   //3.) Create the instance of the third Max11331 adapter board with one or may several master = several physical Max11331 chips
       default_configuration.base_address = XPAR_UZ_ANALOG_ADAPTER_A2_ADAPTER_A2_ADC_MAX11331_BASEADDR;
       uz_adcMax11331_t *instance_3 = uz_adcMax11331_init(default_configuration);
   }

.. warning:: The software driver has no way to read the trigger ADC signal ``enable_measure`` nor the output valid signal ``new_data``! Thus, the user has to be sure that a ADC conversion took place and is finished. This means that the driver can mostly be used for debugging control algorithms that are fully implemented in the PL!


Driver reference
****************

.. doxygentypedef:: uz_adcMax11331_t

.. doxygenstruct:: uz_adcMax11331_config_t
   :members:

.. doxygenfunction:: uz_adcMax11331_init

.. doxygenfunction:: uz_adcMax11331_set_clk_div

.. doxygenfunction:: uz_adcMax11331_check_echo_of_master



Configuration Registers
=======================

Status Register
***************

Address offset: 0x0

Software status register of the IP core.

.. _table_adc_status:
.. csv-table:: ADC_STATUS
  :file: ./tables/adc_status.csv
  :widths: 10 20 10 20 50
  :header-rows: 1

Error Counter Register
**********************

Address offset: 0x04

Echoed bipolar 12 Register
**************************

- Address offset: 0x08
- Read: Data sent by ADC connected to MISO, corresponding to echo of bipolar register value 1 and 2

Echoed bipolar 34 Register
**************************

- Address offset: 0x0C
- Read: Data sent by ADC connected to MISO, corresponding to echo of bipolar register value 3 and 4

Echoed bipolar 56 Register
**************************

- Address offset: 0x10
- Read: Data sent by ADC connected to MISO, corresponding to echo of bipolar register value 5 and 6

Echoed unibipolar 12 Register
*****************************

- Address offset: 0x14
- Read: Data sent by ADC connected to MISO, corresponding to echo of unipolar register value 1 and 2

Echoed unibipolar 34 Register
*****************************

- Address offset: 0x18
- Read: Data sent by ADC connected to MISO, corresponding to echo of unipolar register value 3 and 4

Echoed unibipolar 56 Register
*****************************

- Address offset: 0x1C
- Read: Data sent by ADC connected to MISO, corresponding to echo of unipolar register value 5 and 6
  
ADC Selector ForceInit Register
*******************************

Address offset: 0x20

Software ADC selector and force init register of the IP core.

.. _table_adc_selector:
.. csv-table:: ADC_SELECTOR_FORCEINIT
  :file: ./tables/adc_selector.csv
  :widths: 10 20 10 20 50
  :header-rows: 1
  
CLK Division Register
*********************

Address offset: 0x24

Software CLK division register of the IP core.

.. _table_adc_clk_division:
.. csv-table:: ADC_CLK_DIVISION
  :file: ./tables/adc_clk_division.csv
  :widths: 10 20 10 20 50
  :header-rows: 1 

Vivado
======

.. figure:: max11331_ipcore.png

The only tested clock frequency for ``clk`` and ``s_axi_lite_aclk`` is 100 Mhz.

.. csv-table:: Vivado block design interfaces of MAX11331 IP-Core
   :file: ./max11331_VivadoInterface.csv
   :widths: 50 50 50
   :header-rows: 1

Further information 
===================

- The state machine inside the IP-Core does not have a graph, however is easy to follow reading the VHDL code of the IP-Core. 


References
**********

* MAX11331 Adapter Card :ref:`Analog_MAX11331`
* .. [MAX11331_data_sheet] `Data sheet ADC MAX11331 <https://www.analog.com/media/en/technical-documentation/data-sheets/MAX11329-MAX11332.pdf>`_


Designed by 
***********

Eyke Aufderheide (TUM), Sebastian Wendel (ZC) in 11/2024
