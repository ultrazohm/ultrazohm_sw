.. _ipCore_LTC2311_v3:

==============
ADC LTC2311 V3
==============

Introduction
============

The IP core ADC_LVDS_LTC2311 in version 3 is designed to read the ADCs which are located on the :ref:`analog adapter board <Analog_LTC2311_16_v3>` and to further process the values obtained from the ADCs.
The IP core features an AXI4 Lite interface for settings and software control.
For real time control, the IP core can be triggered by using the hardware port ``TRIGGER_CONV``.
The IP-Core adds an offset value to the raw value and multiplies the result with a conversion factor, which in turn is avialable on the hardware port ``SI_VALUE``.
The raw value from the ADC and the processed value are ``std_logic_vectors`` at the hardware interface of the IP core.
For a thorough project description please refer to the project report which is available in the :ref:`Downloads section <downloads>`.

Features
--------

- Up to 32 independent Serial Peripheral Interface (SPI) Masters with each up to 32 synchronous channels.
  In total up to 1024 individual ADCs are theoretically possible with one IP-Core instance.
- Pipelined addition with an offset value and subsequent multiplication with a conversion factor with the following features:

  + Low resource footprint due to pipelined setup
  + Each individual SPI Master features one DSP48 block
  + The results from the synchronous SPI channels are piped through the DSP48 block.
    This leads to high throughput while maintaining a low resource footprint by not granting a single DSP48 block per ADC channel.

- Offset and conversion factor are configurable by software individually for each ADC
- Burst transfer of an adjustable number of samples
- Continuous and triggered operation modes
- Hardware trigger interface for real time requirements and software trigger interface via AXI4 Lite for convenient usage in case of non time-critical applications
- Software control:

  + Software trigger
  + Software reset

- CPHA CPOL and SCLK frequency of the SPI interface are configurable
  by software

  + The SCLK frequency scales with :math:`f_{SCLK} = \frac{ f_{SystemClock} }{2 \cdot (CLK\_DIV + 1)}`

- Read only SPI. Only a **unidirectional** communication from the ADC to FPGA is possible.
- Single ended and differential operation modes.
  In order to interact with the :ref:`analog adapter board <Analog_LTC2311_16_v3>`, the interface must be set to differential.
  In this case, an LVDS buffer is instantiated inside the IP core.


Software Driver
===============

The configuration of the IP-Core settings by software use the control register, the SPI-Master, and the channel selection to distribute the configuration values from one AXI register to the internal configuration registers in the IP-Core.
The control register is used to set the trigger mode, trigger the conversion, reset the IP-Core or determine to which register in the IP-Core the value in the ``Configuration Value Register`` AXI register should be written.
This control is facilitated by writing different bit patterns to the control register (see table :ref:`table_adc_cr`).

To write a config value to a specific ADC channel, the number of the SPI master and the desired channel has to be written to the Master Channel selection and ADC Channel selection AXI registers.
Furthermore, the control register has to be set to match the variable that is write to the ``Configuration Value Register``.
Effectively, the SPI Master and channel selection as well as the configuration value register act as a switch to route the values from the AXI registers to the ADC channels.


To write a specific conversion factor to one of the ADC channels, the following steps are performed:

1. read the current value from the configuration register
2. Reset all bits that encode what the ``Configuration Value Register`` holds (bit 4 to 6)
3. Set the bit pattern to ``001`` to indicate that the value is the conversion factor
4. Write the spi master and channel number to the AXI registers of the ADC channel that has to be changed
5. Write the conversion factor to ``Configuration Value Register``
6. Write the configuration to the configuration register
7. Call ``uz_adcLtc2311_cr_wait_for_value_acknowledgement`` which repeatedly reads the configuration register and waits for the acknowledgement of a successful data transfer


Configuration Procedure
-----------------------

The test bench function below displays an example of how to configure and use the IP core.
In this example the software trigger is used but instead the hardware trigger in the FPGA can be used as well.
The functions are further explained in the section :ref:`Representation in Software <uz_adcLtc2311_software_driver>`.

The following settings are set globally for each IP-Core instance:

- base_address
- ip_clk_frequency_Hz
- pre_delay
- post_delay
- clk_div
- cpha
- cpol
- max_attempts
- mode (either triggered or continuous sampling)

The following settings are set on a per master basis within one IP-Core instance:

- sleeping_spi_masters
- napping_spi_masters
- error_code
- samples
- sample_time

The following settings are set on a per channel basis of one SPI master within an IP-Core instance:

- conversion_factor
- offset

Additionally, the trigger as well as the software trigger affects all ADC channels of one SPI master.


.. code-block:: c
  :caption: Content of the file ``uz_adcLtc2311_testbench.c``

  #include "../include/uz_adcLtc2311_testbench.h"
  #include "../uz/uz_HAL.h"
  #include "../IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
  #include "xparameters.h"
  #include <stdint.h>

  void uz_adcLtc2311_testbench(void)
  {
      int32_t conversion_factor = 153;
      uint32_t samples = 4;
      int32_t offset = 0;
      uint32_t sample_time = 6;
      uint32_t cpol = 1;
      uint32_t cpha = 0;
      uint32_t pre_delay = 0;
      uint32_t post_delay = 0;
      uint32_t clk_div = 0;
      uint32_t master = UZ_ADCLTC2311_MASTER1;
      uint32_t channel = UZ_ADCLTC2311_CH1 | UZ_ADCLTC2311_CH2 | UZ_ADCLTC2311_CH3 | UZ_ADCLTC2311_CH4 | UZ_ADCLTC2311_CH5 | UZ_ADCLTC2311_CH6 | UZ_ADCLTC2311_CH7 | UZ_ADCLTC2311_CH8;
      // set max_attempts to non zero if you want to prevent that the IP core potentially tries to update
      // operation parameters infinitely
      uint32_t max_attempts = 10;

      struct uz_adcLtc2311_config_t default_configuration = {
          .base_address=XPAR_A1_ADC_LTC2311_S00_AXI_BASEADDR,
          .ip_clk_frequency_Hz=100000000U,
          .conversion_factor = conversion_factor,
          .samples = samples,
          .cpol = cpol,
          .cpha = cpha,
          .offset = offset,
          .napping_spi_masters=0,
          .sleeping_spi_masters=0,
          .master_select = master,
          .channel_select = channel,
          .sample_time = sample_time,
          .pre_delay = pre_delay,
          .post_delay = post_delay,
          .clk_div = clk_div,
          .max_attempts = max_attempts
      };

      // Apply the same configurations to all instances
      uz_adcLtc2311_t* test_instance = uz_adcLtc2311_init(default_configuration);
      default_configuration.base_address = XPAR_A2_ADC_LTC2311_S00_AXI_BASEADDR;
      uz_adcLtc2311_t* test_instance_2 = uz_adcLtc2311_init(default_configuration);
      default_configuration.base_address = XPAR_A3_ADC_LTC2311_S00_AXI_BASEADDR;
      uz_adcLtc2311_t* test_instance_3 = uz_adcLtc2311_init(default_configuration);

      // Adjust operation parameters
      // 1: Select which channels you want to update
      uz_adcLtc2311_set_master_select(test_instance, UZ_ADCLTC2311_MASTER1);
      uz_adcLtc2311_set_channel_select(test_instance, UZ_ADCLTC2311_CH4);

      // 2: Adjust the parameters in the software representation
      // These parameters are channel specific
      uz_adcLtc2311_set_conversion_factor(test_instance, 160);
      uz_adcLtc2311_set_offset(test_instance, 10);

      // These parameters are specific for a master but not channel specific
      // Take 5 samples per trigger event
      uz_adcLtc2311_set_samples(test_instance, 5);
      // Wait at least 20 system clock cycles from the rising edge of SS_N to the next falling edge of SS_N
      uz_adcLtc2311_set_sample_time(test_instance, 20);

      // 3: Call the update functions to write the values to the hardware and check their return values
      // Since these functions are potentially called during operation they do not stop the application
      // by raising an exception if the action fails. The user has to take care about this case!!!
      int32_t return_value = uz_adcLtc2311_update_conversion_factor(test_instance);
      uz_assert(return_value == UZ_SUCCESS);
      return_value = uz_adcLtc2311_update_offset(test_instance);
      uz_assert(return_value == UZ_SUCCESS);
      return_value = uz_adcLtc2311_update_samples(test_instance);
      uz_assert(return_value == UZ_SUCCESS);
      return_value = uz_adcLtc2311_update_sample_time(test_instance);
      uz_assert(return_value == UZ_SUCCESS);

      // Operation
      while(1)
      {
        // Software trigger with explicitely chosen SPI master
        uz_adcLtc2311_software_trigger(test_instance, UZ_ADCLTC2311_MASTER1);
        // When setting the choice to 0 the SPI masters from
        // test_instance->config.master_select are chosen for the trigger
        uz_adcLtc2311_software_trigger(test_instance_2, 0);
        uz_adcLtc2311_software_trigger(test_instance_3, 0);

        // Nap and sleep mode:
        uz_adcLtc2311_enter_nap_mode(test_instance);
        // This trigger event will not trigger any conversions
        // because the masters are in nap mode
        uz_adcLtc2311_software_trigger(test_instance, 0);
        uz_adcLtc2311_leave_nap_mode(test_instance);
        // The trigger works again
        uz_adcLtc2311_software_trigger(test_instance, 0);
        uz_adcLtc2311_enter_sleep_mode(test_instance);
        // This trigger event will not trigger any conversions
        // because the masters are in sleep mode
        uz_adcLtc2311_software_trigger(test_instance, 0);
        uz_adcLtc2311_leave_sleep_mode(test_instance);

        // After enabling continuous mode the ADC is triggered at maximum sampling frequency
        uz_adcLtc2311_set_continuous_mode(test_instance);
        // Execute some samples
        uz_sleep_useconds(5);
        // After enabling the triggered mode the current conversion is executed until the end
        // end the triggered mode is entered
        uz_adcLtc2311_set_triggered_mode(test_instance);
        uz_adcLtc2311_software_trigger(test_instance, 0);
      }
  }


.. _uz_adcLtc2311_software_driver:

Driver reference
----------------



Representation in software
**************************

.. _config_typedef:

.. doxygentypedef:: uz_adcLtc2311_t

.. _config_struct:

.. doxygenstruct:: uz_adcLtc2311_config_t
   :members:

Operation
*********

.. doxygenfunction:: uz_adcLtc2311_init

.. doxygenfunction:: uz_adcLtc2311_update_conversion_factor

.. doxygenfunction:: uz_adcLtc2311_update_offset

.. doxygenfunction:: uz_adcLtc2311_update_samples

.. doxygenfunction:: uz_adcLtc2311_update_sample_time

.. doxygenfunction:: uz_adcLtc2311_update_spi

.. doxygenfunction:: uz_adcLtc2311_set_triggered_mode

.. doxygenfunction:: uz_adcLtc2311_set_continuous_mode

.. doxygenfunction:: uz_adcLtc2311_software_trigger

.. doxygenfunction:: uz_adcLtc2311_software_reset

Nap and Sleep Mode
******************

.. doxygenfunction:: uz_adcLtc2311_enter_nap_mode

.. doxygenfunction:: uz_adcLtc2311_leave_nap_mode

.. doxygenfunction:: uz_adcLtc2311_enter_sleep_mode

.. doxygenfunction:: uz_adcLtc2311_leave_sleep_mode


Parameter Adjustment
--------------------

Every parameter in :ref:`configuration struct <config_struct>` has a get and set function by default.
If a get or set function is not available it is mentioned explicitly.
The ``self`` parameter is always a pointer to the :ref:`instance representing the IP core in software <config_typedef>`.
The get function always asserts that self is not NULL and that the instance is ready and then it returns the demanded value.

If the set function is not further explained below, the value is not examined for validity.
Otherwise, the performed asserts are mentioned below.

.. doxygenfunction:: uz_adcLtc2311_set_samples

.. doxygenfunction:: uz_adcLtc2311_set_sample_time

.. doxygenfunction:: uz_adcLtc2311_set_pre_delay

.. doxygenfunction:: uz_adcLtc2311_set_post_delay

.. doxygenfunction:: uz_adcLtc2311_set_clk_div

.. doxygenfunction:: uz_adcLtc2311_set_cpha

.. doxygenfunction:: uz_adcLtc2311_set_cpol


Functional Description
======================

Architecture
------------

The IP core is hierarchically organized.
The figure below shows the components of the IP core.
Every component is a single VHDL file.
The functionality, which is assigned to the component is also mentioned in the figure.

.. _uz_adcLtc2311_architecture:

.. figure:: ./adc_v3/images/architecture.svg
   :width: 800
   :align: center

   Architecture of the ADC IP core.


Configuration Registers
-----------------------

Control Register
****************

Address offset: 0x0

Software control register of the IP core.


.. _table_adc_cr:
.. csv-table:: ADC_CR
  :file: ./adc_v3/tables/adc_cr.csv
  :widths: 5 10 5 10 40 40
  :header-rows: 1

By setting the bits 4 to 6 the meaning of the value in the ``ADC_VALUE`` register is determined. Bit 4 to 6 are interpreted as an unsigned integer.

.. _table_adc_cr_2:
.. csv-table::
  :file: ./adc_v3/tables/adc_cr_2.csv
  :widths: 2 2 2 10 40 20
  :header-rows: 1


SPI Control Register
********************

Address offset: 0x4

The SPI interfaces can be controlled manually with this register in order to use sleep and nap modes of the ADC.
The signal ``SS_N`` and ``SCLK`` only can be controlled manually if the selected master channels are not busy.
Check :ref:`table_adc_master_busy` as a status indicator.

Furthermore, the clock polarity and the sample phase are set with this register.
This setting applies globally to all SPI masters instantiated.

.. _table_adc_spi_cr:
.. csv-table:: ADC_SPI_CR
  :file: ./adc_v3/tables/adc_spi_cr.csv
  :widths: 5 10 5 10 40 40
  :header-rows: 1


SPI Configuration Register
**************************

Address offset: 0x8

Setting for

- DCNVSCKL (a.k.a PRE_WAIT)
- DSCKLCNVH (a.k.a POST_WAIT)
- Number of system clock cycles per half SCLK cycle - 1 (a.k.a
  CLK_DIV)

See figure 21 in `the datasheet of the LTC2311 <https://www.analog.com/media/en/technical-documentation/data-sheets/231116fa.pdf>`_ for illustration.

The values given indicate the number of system clock cycles for the time described.

.. _table_adc_spi_cfgr:
.. csv-table:: ADC_SPI_CFGR
  :file: ./adc_v3/tables/adc_spi_cfgr.csv
  :widths: 10 10 5 10 40 30
  :header-rows: 1

Master Channel selection
************************

Address offset: 0xC

Encoding: :ref:`One-Hot <adc_one_hot>`

This register is used for two different functions:

1. Update of the configuration values such as offset, conversion factor and number of samples per trigger.
   In order to specify which individual ADC channels shall be updated, the SPI master as well as the ADC which is controlled by the selected SPI master channel must be selected.
   The individual channel selection is done in :ref:`table_adc_channel`.
2. Channel selection for software trigger: When setting the software trigger bit in the :ref:`table_adc_cr` all channels selected in :ref:`table_adc_master_channel` are triggered by software.
   When using hardware trigger the content of this register is ignored.

.. _table_adc_master_channel:
.. csv-table:: ADC_MASTER_CHANNEL
  :file: ./adc_v3/tables/adc_master_channel.csv
  :widths: 8 30 3 10 30 30
  :header-rows: 1

ADC Channel selection
*********************

Address offset: 0x10

Encoding: :ref:`One-Hot <adc_one_hot>`

When updating the offset and conversion factor select the channel on the SPI masters selected in :ref:`table_adc_master_channel` that shall be updated.

.. _table_adc_channel:
.. csv-table:: ADC_CHANNEL
  :file: ./adc_v3/tables/adc_channel.csv
  :widths: 8 30 3 10 30 30
  :header-rows: 1

Transmission ended register
***************************

Address offset: 0x14

Encoding: :ref:`One-Hot <adc_one_hot>`

This register indicates that an SPI master unit finished with the transmission of the raw value from the SPI master i.e. the value on the hardware port ``RAW_VALUE`` is valid for the indicated channels.

.. _table_adc_master_finish:
.. csv-table:: ADC_MASTER_FINISH
  :file: ./adc_v3/tables/adc_master_finish.csv
  :widths: 7 25 3 10 30 30
  :header-rows: 1

Addition and Multiplication ended register
******************************************

Address offset: 0x18

Encoding: :ref:`One-Hot <adc_one_hot>`

This register indicates that an SPI master unit finished with the addition and the multiplication of the raw value  i.e. the value on the hardware port ``SI_VALUE`` is valid for the indicated channels.

.. _table_adc_si_finish:
.. csv-table:: ADC_MASTER_SI_FINISH
  :file: ./adc_v3/tables/adc_master_si_finish.csv
  :widths: 8 30 3 10 30 30
  :header-rows: 1

Conversion ongoing indicator
****************************

Address offset: 0x1C

Encoding: :ref:`One-Hot <adc_one_hot>`

The indicated master channels are currently busy i.e. a transmission or a multiplication is ongoing.

.. _table_adc_master_busy:
.. csv-table:: ADC_MASTER_BUSY
  :file: ./adc_v3/tables/adc_master_busy.csv
  :widths: 8 30 3 10 30 30
  :header-rows: 1

Configuration Value register
****************************

Address offset: 0x20

Encoding: Depending on the value

The value for the offset and the conversion factor is given in this register.
The distinction between the offset and the conversion factor is done in :ref:`table_adc_cr`.

.. _table_adc_off_conv:
.. csv-table:: ADC_VALUE
  :file: ./adc_v3/tables/adc_conv_value.csv
  :widths: 10 10 5 10 30 30
  :header-rows: 1

ADC Available indicator
***********************

Address offset: 0x24

Encoding: :ref:`One-Hot <adc_one_hot>`

The indicated master channels are currently not available because they are either in sleep mode or in nap mode.
This register is set by software and used by the hardware in order to prohibit a trigger when an ADC is not available.

.. _table_adc_available:
.. csv-table:: ADC_AVAILABLE
  :file: ./adc_v3/tables/adc_available.csv
  :widths: 8 30 3 10 30 30
  :header-rows: 1


Design Parameters
-----------------

.. _table_adc_generics:
.. csv-table:: Generics
  :file: ./adc_v3/tables/generics.csv
  :widths: 10 30 5 5 30
  :header-rows: 1

I/O Signals (Interface)
=======================

Clock and Reset
---------------

The IP core is globally clocked with the signal ``s00_axi_aclk``.
The global reset signal apart from the software reset is ``s00_axi_aresetn``.
The reset is synchronous and low activ. Keep this signal high for normal operation.

The IP core has been tested with a system clock frequency of up to 100MHz.
The if the IP core is operated with a higher frequency, the PRE_DELAY and the POST_DELAY of the SPI must be adjusted according to `the datasheet of the LTC2311 <https://www.analog.com/media/en/technical-documentation/data-sheets/231116fa.pdf>`_.
Besides that, the minimum sample time should be adjusted to a value, that meets the hardware requirements of the LTC2311 and suits the driving strength of the captured analog signal.

AXI Signals
-----------

All signals with the prefix ``s00_axi`` belong to the AXI4 Lite interface.
See the Xilinx AXI signal description for details.

Other I/O Signals
-----------------

.. _table_adc_io_interface:
.. csv-table:: I/O Interface
  :file: ./adc_v3/tables/io_signals.csv
  :widths: 10 5 40 5 30
  :header-rows: 1


.. _adcltc_vivado_picture:

.. figure:: ltc_v3_vivado.png
   :width: 400px
   :align: center

   ADC LTC2311 IP-Core.

Terminology
===========

.. _adc_one_hot:

One-Hot Encoding
----------------

One-Hot encoding means that every bit in a register controls a channel of the IP core.
This channel can be either an SPI master instance with a DSP48 block or a channel (a.k.a. individual ADC) of that instance which is synchronously controlled with the other channels assigned to the SPI master instance.
This distinction is done in the description of the individual register.


.. _downloads:

Downloads
=========

:download:`Detailed project description <./adc_v3/report_2_wendt.pdf>` 

:download:`Sample waveforms captured with Vivado ILA <./adc_v3/sample_waveform_from_vivado_ila.zip>` 


Designed by
-----------

`Thilo Wendt <mailto:business@thilo-wendt.de>`_, `Institut ELSYS
<https://www.th-nuernberg.de/einrichtungen-gesamt/in-institute/institut-fuer-leistungselektronische-systeme-elsys/>`_
@ `Technische Hochschule Nürnberg <https://www.th-nuernberg.de>`_, 04/2021
