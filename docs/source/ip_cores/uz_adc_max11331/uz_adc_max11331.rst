.. _ipCore_adc_max11331:

================
ADC MAX11331 V1
================

Introduction
============

The IP core ADC_MAX11331 in version 1 is designed to read the ADCs which are located on the MAX adpater board and to further process the values obtained from the ADCs.
The IP core features an AXI4 Lite interface for settings and software control.
The conversion can be triggered by using the hardware port ``enable_measure`` for real-time control.
The IP core ADC_MAX11331 does not process the raw value further (offset and conversion factor) to an SI value, instead it only provides the RAW value ``raw_measured_data``.
The raw value from the ADC is a ``std_logic_vector`` at the hardware interface of the IP core.

Features
--------

- The MAX11331 ADC chip is able to read 16 single-ended or 8 differential channels.
- The IP-Core for the MAX11331 ADC is capable of processing up to 6 ADC chips, even if only one ADC chip is currently connected.

- The IP-Core does the following tasks:
    - Initialize the MAX11331 ADC chip(s)
    - Validate SPI communication to the ADC chip(s)
    - Send data to the ADC chip(s) in order to sample 16 single-ended channels (or alternatively 8 differential channels)
    - Read back the 16(8) ADC channels, which are sampled one after another. 
	
- Each ADC chip contains one inital message and afterwards:
    - In single-ended case: Each ADC contains 16 channels, which are sampled one after each other. Hence, 16 +1 SPI messages are required to sample and send the 16 channel values.
    - In differential case: Each ADC contains 8 channels, which are sampled one after each other. Hence, 8 +1 SPI messages are required to sample and send the 8 channel values. 
- The inital (extra) message is required since the first message tells the ADC which channel should be sampled. Afterwards, thus from the second message ongoing the data are send (first only the odd channel numbers and than the even channel numbers)
	
- The IP-Core needs the R5 processor to set the registers of the MAX11331 ADC chip for the following reasons:
    - Configure the SPI-Clock divider
    - Configure how many MAX11331 chips are connected (number of Masters). For now there is only one MAX11331 ADC chip, thus one Master, used.
    - The settings required by the registers in the ADC chip(s) are set in individual SPI messages with the name of the respective register, so it is easy to change the initialization using the data sheet if necessary.

- IP-Core clk frequency is typically 100MHz: 
    - The SPI-Clock is generated internally by logic of clock divider. You can change its value from the IP-core using the SPI-Clock divider.
    - Clock divider 0x1, set SPI-Clock to 50Mhz. 
    - Clock divider 0x2, set SPI-Clock to 25Mhz.
    - Clock divider 0x3, set SPI-Clock to divider 3 to 16.6Mhz and so on. 
    - The SPI SCK frequency will be given by: IP-Core clk frequency / (2^(clock divider))
    - The SPI SCK frequency of 16.67MHZ(= 0x3) is used in default.

- So far, the ADC can only be triggered by a PL signal, but not by the software driver:
    - There is an input pin to trigger the start sampling when it has the value ‘1’. 
    - Changing the trigger value meanwhile the sampling is being carried out does do nothing. 
    - The trigger pin is only read when there is no sampling active. 
    - If the trigger pin is fix to ‘1’, the IP-Core will continuously sample the 16(8) channels using the 17(9) messages explained before.
    - It is important to notice that the 16(8) channels of one ADC chip are sampled one after another, which must be known when the data are used in the control loop. 
    - The IP core updates all channel outputs as soon as the last channel has been sampled and read. Therefore you will not notice how the channels are actually sampled, but all 16(8) channels are updated simultaneously at the IP core output in the FPGA.
	
- Output is supplied to the PL-ports of the IP-Core as well as to the AXI4 over the TCM.

Table :ref:`ipCore_adc_max11331_interfaces` lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. _ipCore_adc_max11331_interfaces:

.. csv-table:: Interface of adc_max11331 IP-Core
   :file: adc_max11331_register_mapping.csv
   :widths: 50 50 50 50 50 50 200
   :header-rows: 1

Vitis
=====

Initialize one driver instance and write the two configurations:

.. code-block:: c

   static struct uz_adcMax11331_config_t config={
        .base_address = XPAR_MAX11_ADC_MAX11331_TOP_0_BASEADDR,
        .ip_clk_frequency_Hz = XPAR_A1_ADC_MAX11331_IP_CORE_FREQUENCY,
        .channel_config = {
            .conversion_factor = DEFAULT_MAX11331_CONVERSION_FACTOR,
            .conversion_factor_definition = {
                .is_signed = true,
                .integer_bits = DEFAULT_MAX11331_INTEGER_BITS,
                .fractional_bits = DEFAULT_MAX11331_FRACTIONAL_BITS},
            .offset = DEFAULT_MAX11331_OFFSET,
        },
        .trigger_mode=continuous_trigger,
        .cpol = 1U,
        .cpha = 1U,
        .master_select = UZ_ADCMAX11331_MASTER1,
        .channel_select = UZ_ADCMAX11331_CH1 | UZ_ADCMAX11331_CH2 | UZ_ADCMAX11331_CH3 | UZ_ADCMAX11331_CH4 | UZ_ADCMAX11331_CH5 | UZ_ADCMAX11331_CH6 | UZ_ADCMAX11331_CH7 | UZ_ADCMAX11331_CH8 | UZ_ADCMAX11331_CH9 | UZ_ADCMAX11331_CH10 | UZ_ADCMAX11331_CH11 | UZ_ADCMAX11331_CH12 | UZ_ADCMAX11331_CH13 | UZ_ADCMAX11331_CH14 | UZ_ADCMAX11331_CH15 | UZ_ADCMAX11331_CH16,
        .clk_div = UZ_ADCMAX11331_SPI_CLK_16_67MHZ
   };

   uz_adcMax11331_t *instance_1 = uz_adcMax11331_init(config);
   struct uz_dq_t currents = uz_dqIPcore_get_id_iq(test_instance);

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
-----------------------

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

Address offset: 0x08

Echoed bipolar 34 Register
**************************

Address offset: 0x0C

Echoed bipolar 56 Register
**************************

Address offset: 0x10

Echoed unibipolar 12 Register
*****************************

Address offset: 0x14

Echoed unibipolar 34 Register
*****************************

Address offset: 0x18

Echoed unibipolar 56 Register
*****************************

Address offset: 0x1C
  
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


Designed by 
-----------

Eyke Aufderheide (TUM), Sebastian Wendel (ZC) in 11/2024