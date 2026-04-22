.. _uz_endat_interface:

===============
EnDat Interface
===============

The EnDat interface driver configures and accesses the EnDat IP-Core from the processor.
It writes the encoder configuration, PLL parameters, machine pole pair count and mechanical offset to the IP-Core.
After enabling the IP-Core, the driver provides separate getter functions for the raw position values, SI position values and speed values.

The getter functions intentionally read one value per call.
Each getter maps to one AXI read in the hardware driver.
This keeps the caller in control of the number of bus transactions, which is especially relevant when values are read from an ISR.

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

Example
=======

.. code-block:: c

   #include "IP_Cores/uz_endat_interface/uz_endat_interface.h"

   static struct uz_endat_interface_config_t endat_config = {
       .base_address = XPAR_UZ_USER_UZ_ENDAT_INTERFACE_0_BASEADDR,
       .ip_clk_frequency_Hz = 100000000U,
       .endat_clk_frequency_Hz = 2500000U,
       .endat_encoder_bit_width_single_turn = 19U,
       .endat_encoder_bit_width_multi_turn = 12U,
       .machine_polepairs = 4U,
       .sampling_interval_seconds = 0.0001f,
       .kp_pll = 628.0f,
       .ki_pll = 98696.0f,
       .position_mech_offset_si_single_turn = 0.0f
   };

   static uz_endat_interface_t *endat_instance = NULL;

   void init_endat(void) {
       endat_instance = uz_endat_interface_init(endat_config);
       uz_endat_interface_set_mode_command(endat_instance, uz_endat_interface_send_position);
       uz_endat_interface_enable_ip(endat_instance, true);
   }

   void read_endat_values(void) {
       float position_el = uz_endat_interface_get_position_el_si_single_turn(endat_instance);
       float speed_mech = uz_endat_interface_get_speed_mech_si(endat_instance);

       (void)position_el;
       (void)speed_mech;
   }

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
