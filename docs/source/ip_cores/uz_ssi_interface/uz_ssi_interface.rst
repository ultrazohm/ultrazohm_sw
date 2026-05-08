.. _uz_ssi_interface:

=============
SSI Interface
=============

The SSI interface IP core connects SSI absolute encoders to the UltraZohm.
It handles the serial communication with the encoder and provides raw position values, SI position values and speed values to the processor.
This page describes how to instantiate and connect the IP core in the FPGA design and how to set up the corresponding software driver.
After initialization, the driver configures the IP core and provides getter functions for position values from the encoder and speed values derived from the measured position.

Interface Definition
====================

Table :ref:`ipCore_uz_ssi_interface` lists all input and output ports (AXI and external port) that are present in the IP core.

.. _ipCore_uz_ssi_interface:

.. csv-table:: Interface of uz_ssi_interface IP core
   :file: uz_ssi_interface_port_mapping.csv
   :widths: 50 50 50 70 60 300
   :header-rows: 1

Configuration
=============

The public configuration struct contains only user-relevant parameters.
The SSI encoder data frame is configured by the bit widths of the single-turn position, multi-turn position and status bits.
The single-turn and multi-turn bit widths are each limited to 31 bits.
This keeps all parameter transfers compatible with the 32-bit AXI interface and avoids undefined shift operations in the software driver.
The number of status bits is limited to 32 bits.
The complete SSI frame length, i.e. the sum of single-turn, multi-turn and status bits, must not exceed 64 bits.
The mechanical offset must be between ``-2*pi`` and ``2*pi`` rad and the converted offset in encoder ticks must fit into an ``int32_t``.
This can further reduce the valid offset range for encoders with very high single-turn bit widths.
The position data can be configured as binary or gray-code encoded.

The SSI clock divider is calculated during initialization from ``ip_clk_frequency_Hz`` and ``ssi_clk_frequency_Hz``.
The resulting divider must be between 20 and 625.

.. warning::

   The raw single-turn and multi-turn position values are read from the encoder with the configured bit widths.
   However, the SI position and speed values generated inside the IP core use a fixed-point reciprocal to scale the raw single-turn position to radians.
   With the current reciprocal format, the reciprocal becomes zero for single-turn bit widths of 28 bit and higher.
   For these configurations, the IP core SI position values and the PLL-based speed values are invalid.
   For single-turn bit widths below 28 bit, the reciprocal remains nonzero, but its quantization increases with the encoder resolution.

   If a high-resolution encoder with 28 or more single-turn bits is used, read the raw position values from the driver and perform the position scaling and speed estimation in software or in a custom high-precision signal path.

Example Usage
=============

The IP core is designed to be employed with the :ref:`uz_d_absolute_encoder` adapter board together with the CPLD program ``uz_d_abs_encoder``, see :ref:`label_cpld_programming`.
The adapter board provides three encoder channels.
The following step-by-step description shows how to implement the IP core and the respective interface and software drivers.
It exemplifies the procedure for one instance that will be connected to slot ``D5`` - ``channel 1`` of the ``uz_d_absolute_encoder`` adapter board.

Block design
------------

.. figure:: ssi_block_design.png
   :width: 700

   Example of connecting SSI IP core to channel 1 of digital adapter card slot 5

First, the IP core has to be added to the block design in Vivado:

1. In the block design, add an SSI interface IP core ``uz_ssi_interface`` inside the ``uz_user`` hierarchy.
2. Create pins and connections in the hierarchy according to the figure above.
3. Additionally provide ``100 MHz`` clock and reset signals for the IP core and the AXI4_Lite interface.
4. Connect the AXI4_Lite interface to the ``AXI_SmartConnect`` block in the uz_user hierarchy.
5. Outside of the uz_user hierarchy create the respective digital I/O ports and connect them to the digital I/Os of the same name at the uz_user hierarchy.
6. Connect the ``trigger_ssi_read`` pin to the ``trigger_conversions`` pin of the ``uz_system`` hierarchy.
7. It is highly recommended to also place an integrated logic analyzer block ``ILA`` and connect at least: ``trigger_ssi_read``, ``ssi_clk``, ``ssi_data_in``, and ``ssi_data_out_SH``, in order to debug the timing in case of high encoder clock frequencies or long encoder cables. See also :ref:`uz_ssi_interface_delay_comp`.
8. Assign an AXI address, validate the design, save it and generate the bitstream. Perform export of the xsa file after successful generation of the bitstream.

If more than one SSI interface is required, the table below shows the pin assignment for all three channels of the ``uz_d_absolute_encoder`` adapter board.

.. list-table:: D-slot pin mapping within the FPGA design
   :header-rows: 1
   :widths: 40 30 30 30

   * - SSI IP core signal
     - Channel 1
     - Channel 2
     - Channel 3
   * - ssi_clk
     - Dig_15_Chx
     - Dig_14_Chx
     - Dig_22_Chx
   * - RW_clk
     - Dig_17_Chx
     - Dig_16_Chx
     - Dig_23_Chx
   * - RW_data
     - Dig_11_Chx
     - Dig_10_Chx
     - Dig_20_Chx
   * - ssi_data_in
     - Dig_07_Chx
     - Dig_06_Chx
     - Dig_18_Chx


Software driver
---------------

The SSI interface driver configures and accesses the SSI IP core from the processor.
It writes the encoder configuration, PLL parameters, machine pole pair count and mechanical offset to the IP core.
After enabling the IP core, the driver provides separate getter functions for the raw position values, SI position values and speed values.
For interacting with the IP core, the following step-by-step example shows a way of implementing one instance of the software driver.

1. In Vitis, in the Baremetal project under the folder ``hw_init`` create a new file ``uz_ssi_interface_init.c``.
2. Include necessary files and create a ``config`` struct as well as an init function for one or more instances as shown below:

.. code-block:: c
   :caption: Example of uz_ssi_interface_init.c

   #include "../include/uz_ssi_interface_init.h"

   struct uz_ssi_interface_config_t ssi_d5_1_config = {
       .base_address = XPAR_UZ_USER_UZ_SSI_INTERFACE_0_BASEADDR,
       .ip_clk_frequency_Hz = 100000000U,
       .machine_polepairs = 2U,
       .ssi_clk_frequency_Hz = 1000000U,
       .position_encoding = uz_ssi_interface_binary,
       .position_mech_offset_si_single_turn = 0.0f,
       .ssi_encoder_bit_width_single_turn = 19U,
       .ssi_encoder_bit_width_multi_turn = 0U,
       .ssi_encoder_number_of_status_bits = 0U,
       .kp_pll = 628.3185f,
       .ki_pll = 98696.0f,
       .sampling_interval_seconds = 0.0001f,
       .sampling_delay_clk_ticks = 0U
   };

   uz_ssi_interface_t* ssi_encoder_init_d5_1(void) {
       return(uz_ssi_interface_init(ssi_d5_1_config));
   }

.. important::

   The value of ``.sampling_interval_seconds`` must match the period of the ``trigger_ssi_read`` signal that triggers the encoder communication.
   In the example above, ``0.0001f`` corresponds to a trigger period of ``100 us``.
   The speed PLL uses this value as its integration step time; wrong values directly lead to wrong speed estimates.

.. hint::

   The values for ``.kp_pll`` and ``.ki_pll`` can be calculated as described in :ref:`pos_to_speed_pll`.
   The PLL inside the SSI IP core is based on the same implementation, but uses fixed-point math instead of floating-point math.
   This can reduce the PLL performance, especially at low speeds.
   If maximum PLL performance is required, use the SI position signals from the SSI IP core and calculate the speed with the software implementation of the Position to Speed PLL instead.

.. note::

   The base address is generated by Vivado when the AXI address is assigned in the block design.
   After exporting the XSA and updating the Vitis hardware platform, the address macro is available in ``xparameters.h``.
   In the example above this macro is ``XPAR_UZ_USER_UZ_SSI_INTERFACE_0_BASEADDR``.

3. In the ``include`` folder, create a header file ``uz_ssi_interface_init.h``.
4. Include necessary files and add the function prototype of your init routine:

.. code-block:: c
   :caption: Example of uz_ssi_interface_init.h

   #pragma once
   #include "../IP_Cores/uz_ssi_interface/uz_ssi_interface.h"
   #include "xparameters.h"

   uz_ssi_interface_t* ssi_encoder_init_d5_1(void);

5. In the header file ``globalData.h``, include header file and add an object pointer of the respective type in the ``object_pointer_t`` struct as shown below:

.. code-block:: c
   :caption: Lines to add in globalData.h

   ...
   #include "IP_Cores/uz_ssi_interface/uz_ssi_interface.h"
   ...

   typedef struct{
       ...
       uz_ssi_interface_t* ssi_encoder_d5_1;
       ...
   }object_pointers_t;

6. In ``main.c``, initialize an instance of the driver and assign it to the object pointer structure in the ``Global_Data`` struct inside the ``init_ip_cores`` case and enable the IP core:

.. code-block:: c
   :caption: Example of init in main.c

   ...
   case init_ip_cores:
   ...
   Global_Data.objects.ssi_encoder_d5_1 = ssi_encoder_init_d5_1();
   uz_ssi_interface_enable_ip(Global_Data.objects.ssi_encoder_d5_1, true);
   ...
   break;

7. In ``main.h``, include your init header file ``#include "include/uz_ssi_interface_init.h"``.
8. In ``isr.c``, you can now read the AXI output registers of the IP core and use them e.g. for your control algorithm:

.. code-block:: c
   :caption: Example of reading IP core outputs in isr.c

   ...
   YourMechPosST = uz_ssi_interface_get_position_mech_si_single_turn(Global_Data.objects.ssi_encoder_d5_1);
   YourMechPosMT = uz_ssi_interface_get_position_multi_turn(Global_Data.objects.ssi_encoder_d5_1);
   YourElPosST = uz_ssi_interface_get_position_el_si_single_turn(Global_Data.objects.ssi_encoder_d5_1);
   YourMechSpeedRPM = uz_ssi_interface_get_speed_mech_rpm(Global_Data.objects.ssi_encoder_d5_1);
   ...

Notes
=====

Some implementation details might be worth knowing in order to use the SSI interface correctly.

Aligned wrapping of single- and multi-turn position
---------------------------------------------------

The SSI IP core provides the input of a mechanical encoder offset in the config struct in order
to align the mechanical zero position of the encoder with the magnetic zero position of the machine (``.position_mech_offset_si_single_turn``).
When using single-turn encoders, the offset value is added to or subtracted from the single-turn position.
When using multi-turn encoders the offset value is computed in such a way that the multi-turn position value always
wraps aligned to the offset shifted single-turn position. The figure below illustrates the behavior.

.. figure:: mt_aligned_wrap.png
   :width: 700

   Illustration of the wrapping behavior of the multi-turn position

The red signal ``CH1`` is the mechanical single-turn position already accounting for an offset value of ``-1.0f``.
The blue signal ``CH3`` shows the raw multi-turn position, that now would still increment at the :math:`2\pi` wrap of the
single-turn position without offset, i.e. at :math:`2\pi-1.0=5.2831...`. The green signal ``CH2`` is the multi-turn position that accounts for the mechanical
offset value in the config. Its full revolution position counter increments aligned with the red coloured single-turn position.
``position_multi_turn`` is an offset-corrected multi-turn revolution counter which increments aligned with the full revolution wrap of the single-turn position.
It does not contain the single-turn position ticks.
Therefore, when dealing with multi-turn encoders always use the ``position_multi_turn`` or ``position_multi_turn_AXI`` signal, in order
to have the correct alignment of both single- and multi-turn position. This is exactly the difference between the raw multi-turn value
and the position_multi_turn value.

Validity of position and speed values
-------------------------------------

The signal ``trigger_ssi_read`` starts one SSI transaction and writes the results of the previous SSI transaction into the output registers.
For example, if ``trigger_ssi_read`` is connected to ``trigger_conversions``, the position and speed values are updated once per control cycle.
The software getter functions therefore always read the values of the previous control cycle from the AXI output registers.
This delay has to be accounted for in software if it is critical for control purposes.
``ssi_transaction_done`` only indicates that an SSI transaction is finished and does not indicate validity of the output values.

.. _uz_ssi_interface_delay_comp:

Delay Compensation of ``ssi_data_in``
--------------------------------------

At the clock frequencies of serial encoder interfaces (80 kHz up to 2.5 MHz) the delay of the electrical signals caused by the encoder cables matters.
If the time delay is too large, the serial data is no longer sampled correctly by the interface IP core.

Symptom
^^^^^^^

The figure below shows an almost edge case, where the sampling will fail when either increasing the clock frequency or using a longer encoder cable.
The figure shows the example for an SSI encoder connected with a ``2 m`` encoder cable and a set clock frequency of ``2.5 MHz``.

.. figure:: delay_comp.png
   :width: 700

   Sampling mechanism of the serial data from the encoder

With every rising edge of the clock the next data bit is provided by the encoder ``clock rising``. Due to the internal data transfer logic and the cable delay,
this takes a certain amount of time until the bit is present on the data line in the IP core ``data_in``. In order to give enough time for the bit to show up,
a common practice is to sample the bit at the falling edge of the clock ``sampling on falling edge``. In the figure it can be seen
that only ``5 clock ticks`` before the falling edge the bit is present on the data_in. If we would increase the clock frequency further or use a longer
encoder cable, this margin of 5 clock ticks will get smaller until the data bit won't show up on the data_in line before the falling clock edge occurs.

Debug with ILA
^^^^^^^^^^^^^^

If you observe invalid behavior of the position values received from the encoder, check the timing of the serial transmission with an ``ILA`` in the FPGA block design.
Useful signals are ``trigger_ssi_read``, ``ssi_clk``, ``ssi_data_in``, and ``ssi_data_out_SH``.

Countermeasures
^^^^^^^^^^^^^^^

If possible, reduce the serial clock speed or use a shorter encoder cable.
The IP core driver also provides the config value ``.sampling_delay_clk_ticks`` to delay sampling by a certain number of clock ticks after the falling clock edge.
Tune this value while observing the timing with an ``ILA`` to compensate for the delay.

Debugging the IP core's ``pos_to_speed_pll``
--------------------------------------------

The SSI IP core contains a debug input for the internal ``pos_to_speed_pll``.
This debug path can be used to feed a user-defined mechanical position directly into the speed PLL instead of the mechanical position calculated from the encoder data.
It is useful for checking the PLL parametrization, debugging the speed calculation and separating PLL behavior from encoder communication issues.

The debug path is controlled by the software driver.
Use ``uz_ssi_interface_set_pll_debug_position`` to write the mechanical debug position in rad.
Allowed values are between ``0`` and ``2*pi``.
Use ``uz_ssi_interface_enable_pll_debug_mode`` to switch the PLL input between the encoder-derived position and the debug position.

.. warning::

   If the PLL debug mode is enabled, the speed values no longer correspond to the connected encoder position.
   Disable the debug mode for normal encoder operation and for closed-loop control with real position feedback.
   By default, the debug mode is disabled.

Reference
=========

.. doxygentypedef:: uz_ssi_interface_t

.. doxygenenum:: uz_ssi_interface_position_encoding_t

.. doxygenstruct:: uz_ssi_interface_config_t
   :members:

.. doxygenfunction:: uz_ssi_interface_init

.. doxygenfunction:: uz_ssi_interface_get_position_raw_single_turn

.. doxygenfunction:: uz_ssi_interface_get_position_raw_multi_turn

.. doxygenfunction:: uz_ssi_interface_get_position_multi_turn

.. doxygenfunction:: uz_ssi_interface_get_position_mech_si_single_turn

.. doxygenfunction:: uz_ssi_interface_get_position_el_si_single_turn

.. doxygenfunction:: uz_ssi_interface_get_speed_mech_si

.. doxygenfunction:: uz_ssi_interface_get_speed_el_si

.. doxygenfunction:: uz_ssi_interface_get_speed_mech_rpm

.. doxygenfunction:: uz_ssi_interface_get_encoder_status

.. doxygenfunction:: uz_ssi_interface_enable_ip

.. doxygenfunction:: uz_ssi_interface_set_mechanical_offset_ssi_single_turn

.. doxygenfunction:: uz_ssi_interface_set_sampling_delay_clk_ticks

.. doxygenfunction:: uz_ssi_interface_enable_pll_debug_mode

.. doxygenfunction:: uz_ssi_interface_set_pll_debug_position
