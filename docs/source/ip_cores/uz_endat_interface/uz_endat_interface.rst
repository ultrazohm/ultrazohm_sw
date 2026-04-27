.. _uz_endat_interface:

===============
EnDat Interface
===============

The EnDat interface driver configures and accesses the EnDat IP-Core from the processor.
It writes the encoder configuration, PLL parameters, machine pole pair count and mechanical offset to the IP-Core.
After enabling the IP-Core, the driver provides separate getter functions for the raw position values, SI position values and speed values.

Interface Definition
====================

Table :ref:`ipCore_uz_endat_interface` lists all input and output ports (AXI and external port) that are present in the IP core.

.. _ipCore_uz_endat_interface:

.. csv-table:: Interface of uz_endat_interface IP core
   :file: uz_endat_interface_port_mapping.csv
   :widths: 50 50 50 70 60 300
   :header-rows: 1

Configuration
=============

The public configuration struct contains only user-relevant parameters.
The EnDat CRC width is fixed to 5 bits by the driver and is not part of the public configuration.

The single-turn and multi-turn bit widths are each limited to 31 bits.
This keeps all parameter transfers compatible with the 32-bit AXI interface and avoids undefined shift operations in the software driver.
The sum of single-turn and multi-turn bits is limited to 48 bits.
The complete EnDat frame length, including the fixed 5 CRC bits, must not exceed 64 bits.
The mechanical offset must be between ``-2*pi`` and ``2*pi`` rad and the converted offset in encoder ticks must fit into an ``int32_t``.
This can further reduce the valid offset range for encoders with very high single-turn bit widths.

The EnDat clock divider is calculated during initialization from ``ip_clk_frequency_Hz`` and ``endat_clk_frequency_Hz``.
The resulting divider must be between 3 and 500.

Example Usage
=============

The IP core is designed to be employed with the :ref:`uz_d_absolute_encoder` adapter board together with the CPLD program ``uz_d_abs_encoder``. The adapter board provides three encoder channels. 
The following step-by-step description shall guide the user in order to properly implement the IP core and the respective interface and software drivers.
It exemplifies the procedure for one instance that will be connected to slot ``D5`` - ``channel 1`` of the ``uz_d_absolute_encoder`` adapter board.

Block design
------------

.. figure:: endat_block_design.png
  :width: 700

  Example of connecting EnDat IP core to channel 1 of digital adapter card slot 5

First, the IP core has to be added to the block design in Vivado:

1. In the block design, add an EnDat interface IP core ``uz_endat_interface`` inside the ``uz_user`` hierarchy.
2. Create pins and connections in the hierarchy according to the figure above.
3. Additionally provide ``100 MHz`` clock and reset signals for the IP core and the AXI4_Lite interface.
4. Connect the AXI4_Lite interface to the ``AXI_SmartConnect`` block in the uz_user hierarchy
5. Outside of the uz_user hierarchy create the respective digital I/O ports  and connect them to the digital I/Os of the same name at the uz_user hierarchy.
6. Connect the ``trigger_endat`` pin to the ``trigger_conversions`` pin of the ``uz_system`` hierarchy.
7. It is highly recommended to also place a integrated logic analyzer block ``ILA`` and connect at least: ``trigger_endat_read``, ``endat_clk``, ``endat_data_in``, and ``endat_received_data_out_SH``, in order to debug the timing in case of high encoder clock frequencies or long encoder cables. See also :ref:`uz_endat_interface_delay_comp`.
8. Assign an AXI address, validate the design, save it and generate the bitstream. Perform export of the xsa file after successful generation of the bitstream.

If more than one EnDat interface is required, the table below shows the pin assignment for all three channels of the ``uz_d_absolute_encoder`` adapter board.

.. list-table:: D-slot pin mapping within the FPGA design
   :header-rows: 1
   :widths: 40 30 30 30

   * - EnDat IP-core signal
     - Channel 1
     - Channel 2
     - Channel 3
   * - endat_clk
     - Dig_15_Chx
     - Dig_14_Chx
     - Dig_22_Chx
   * - endat_mode_data_out
     - Dig_08_Chx
     - Dig_09_Chx
     - Dig_12_Chx
   * - RW_clk
     - Dig_17_Chx
     - Dig_16_Chx
     - Dig_23_Chx
   * - RW_data
     - Dig_11_Chx
     - Dig_10_Chx
     - Dig_20_Chx
   * - endat_data_in
     - Dig_07_Chx
     - Dig_06_Chx
     - Dig_18_Chx


Software driver
---------------

The EnDat interface driver configures and accesses the EnDat IP-Core from the processor.
It writes the encoder configuration, PLL parameters, machine pole pair count and mechanical offset to the IP-Core.
After enabling the IP-Core, the driver provides separate getter functions for the raw position values, SI position values and speed values.
For interacting with the IP core, the following step-by-step example shows a way of implementing one instance of the software driver.

1. In Vitis, in the Baremetal project under the folder ``hw_init`` create a new file ``uz_endat_interface_init.c``.
2. Include necessary files and create a ``config`` struct as well as an init function for one or more instances as shown below:

.. code-block:: c
  :caption: Example of uz_endat_interface_init.c

  #include "../include/uz_endat_interface_init.h"

  struct uz_endat_interface_config_t endat_d5_1_config = {
    .base_address = XPAR_UZ_USER_UZ_ENDAT_INTERFACE_0_BASEADDR,
	.ip_clk_frequency_Hz = 100000000U,
	.machine_polepairs = 2U,
	.endat_clk_frequency_Hz = 2500000U,
	.position_mech_offset_si_single_turn = -1.0f,
	.endat_encoder_bit_width_single_turn = 25U,
	.endat_encoder_bit_width_multi_turn = 12U,
	.kp_pll = 628.3185f,
	.ki_pll = 98696.0f,
	.sampling_interval_seconds = 0.0001f,
	.delay_sampling_in_clk_ticks = 0U
    };

  uz_endat_interface_t* endat_encoder_init_endat_d5_1(void) {
	return(uz_endat_interface_init(endat_d5_1_config));
  }

3. In the ``include`` folder, create a header file ``uz_endat_interface_init.h``.
4. Include necessary files and add the function prototype of your init routine:

.. code-block:: c
  :caption: Example of uz_endat_interface_init.h

  #pragma once 
  #include "../IP_Cores/uz_endat_interface/uz_endat_interface.h"
  #include "xparameters.h"

  uz_endat_interface_t* endat_encoder_init_endat_d5_1(void);

5. In the header file ``globalData.h``, include header file and add an object pointer of the respective type in the ``object_pointer_t`` struct as shown below:

.. code-block:: c
 :caption: Lines to add in globalData.h

 ... 
 #include "IP_Cores/uz_endat_interface/uz_endat_interface.h"
 ...

 typedef struct{
 ...
 uz_endat_interface_t* endat_encoder_d5_1;
 ...
 }object_pointers_t;

6. In ``main.c``, initialize an instance of the driver and assign it to the object pointer structure in the ``Global_Data`` struct inside the ``init_ip_cores`` case, set the ``mode command`` so that the encoder will send position information, and enable the IP core:

.. code-block:: c
 :caption: Example of init in main.c
 
 ...
 case init_ip_cores:
 ...
 Global_Data.objects.endat_encoder_d5_1 = endat_encoder_init_endat_d5_1();
 uz_endat_interface_set_mode_command(Global_Data.objects.endat_encoder_d5_1, uz_endat_interface_send_position);
 uz_endat_interface_enable_ip(Global_Data.objects.endat_encoder_d5_1, true);
 ...
 break;

7. In ``main.h``, include your init header file ``#include "include/uz_endat_interface_init.h"``.
8. In ``isr.c``, you can now read the AXI output registers of the IP core and use them e.g. for your control algorithm:

.. code-block:: c
 :caption: Example of reading IP core outputs in isr.c

 ...
 YourMechPosST = uz_endat_interface_get_position_mech_si_single_turn(Global_Data.objects.endat_encoder_d5_1);
 YourMechPosMT = uz_endat_interface_get_position_multi_turn(Global_Data.objects.endat_encoder_d5_1);
 YourElPosST = uz_endat_interface_get_position_el_si_single_turn(Global_Data.objects.endat_encoder_d5_1);
 YourMechSpeedRPM = uz_endat_interface_get_speed_mech_rpm(Global_Data.objects.endat_encoder_d5_1);
 ...

Notes
=====

Some implementation details might be worth knowing in order to use the EnDat interface correctly.

Aligned wrapping of single- and multi-turn position
---------------------------------------------------

The EnDat IP core provides the input of a mechanical encoder offset in the config struct in order 
to align the mechanical zero position of the encoder with the magnetic zero position of the machine (``.position_mech_offset_si_single_turn``). 
When using single-turn encoders, the offset value is added/substracted to the single-turn position. 
When using multi-turn encoders the offset value is computed in such a way that the multi-turn position value always 
wraps aligned to the offset shifted single-turn position. Thefigure below illustrates the behavior.

.. figure:: mt_aligned_wrap.png
  :width: 700

  Illustration of the wrapping behavior of the multi-turn position

The red signal ``CH1`` is the mechanical single-turn position already accounting for an offset value of ``-1.0f``. 
The blue signal ``CH3`` shows the raw multi-turn position, that now would still increment at the :math:`2\pi` wrap of the 
single-turn position without offset, i.e. at :math:`2\pi-1.0=5.2831...`. The green signal ``CH2`` ist the multi-turn position that accounts for the mechanical 
offset value in the config. Its full revolution position counter increments aligned with the red coloured single-turn position. 
Therefore, when dealing with multi-turn-encoders always use the ``position_multi_turn`` or ``position_multi_turn_AXI`` signal, in order 
to have the correct alignment of both single- and multi-turn position. This is exactly the differenze between the raw multi-turn value 
and the position_multi_turn value.

.. _uz_endat_interface_delay_comp:

Delay Compensation of ``endat_data_in``
---------------------------------------

At the clock frequencies of serial encoder interfaces (several 100 kHz up to 16 MHz) the delay of the electrical signals caused by the encoder cables matters.
If the timely delay is too large, the serial data is not sample correctly anymore by the interface IP core. The figure below shows 
an almost edge case, where the sampling will fail when either increasing the clock frequency or using a longer encoder cable. 
The figure shows the example for an EnDat encoder connected with a ``2m`` encoder cable and a set clock frequency of ``2.5MHz``. 

.. figure:: delay_comp.png
  :width: 700

  Sampling mechanism of the serial data from the encoder

With every rising edge of the clock the next data bit is provided by the encoder ``clock rising``. Due to the internal data transfer logic and the cable delay, 
this takes a certain amount of time until the bit is present on the data line in the IP core ``data_in``. In order to give enough time for the bit to show up, 
a common practice is to sample the bit at the falling edge of the clock ``sampling on falling edge``. In the figure it can be seen 
that only ``5 clock ticks`` before the falling edge the bit is present on the data_in. If we would increase the clock frequency further or use a longer 
encoder cable, this margin of 5 clock ticks will get smaller until the data bit won't show up on the data_in line before the falling clock edge occurs. 
In order to account for such a timing issue, the IP core driver provides a config value ``.delay_sampling_in_clk_ticks`` to set a certain number of clock ticks that the sampling should be delayed 
after the falling clock edge. So if you observe invalid behavior of the position values received from the encoder, check the timing of the serial transmission with an ``ILA`` in the FPGA block design. 
If possible, reduce the serial clock speed, use a shorter encoder cable or tune the ``.delay_sampling_in_clk_ticks`` value while observing the timing for compensation for the delay.

Reference
=========

.. doxygentypedef:: uz_endat_interface_t

.. doxygenenum:: uz_endat_interface_mode_command_t

.. doxygenstruct:: uz_endat_interface_config_t
   :members:

.. doxygenfunction:: uz_endat_interface_init

.. doxygenfunction:: uz_endat_interface_get_position_raw_single_turn

.. doxygenfunction:: uz_endat_interface_get_position_raw_multi_turn

.. doxygenfunction:: uz_endat_interface_get_position_multi_turn

.. doxygenfunction:: uz_endat_interface_get_position_mech_si_single_turn

.. doxygenfunction:: uz_endat_interface_get_position_el_si_single_turn

.. doxygenfunction:: uz_endat_interface_get_speed_mech_si

.. doxygenfunction:: uz_endat_interface_get_speed_el_si

.. doxygenfunction:: uz_endat_interface_get_speed_mech_rpm

.. doxygenfunction:: uz_endat_interface_enable_ip

.. doxygenfunction:: uz_endat_interface_set_mode_command

.. doxygenfunction:: uz_endat_interface_set_mechanical_offset_endat_single_turn

.. doxygenfunction:: uz_endat_interface_set_sampling_delay_clk_ticks
