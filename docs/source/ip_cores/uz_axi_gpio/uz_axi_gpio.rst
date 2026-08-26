========
AXI GPIO
========

The AXI GPIO IP core connects processor software to individual input and
output signals in the PL. The UltraZohm driver wraps the vendor-provided
Xilinx AXI GPIO driver with the same static-allocation style used by other
UltraZohm IP-core drivers.

Vendor documentation:

- https://www.xilinx.com/products/intellectual-property/axi_gpio.html
- https://docs.xilinx.com/v/u/en-US/pg144-axi-gpio
- https://docs.xilinx.com/v/u/1.01b-English/ds744_axi_gpio

Scope and Assumptions
=====================

The wrapper intentionally implements a compact subset of the AXI GPIO feature
set:

- one AXI GPIO channel is supported; dual-channel mode is not supported
- 1 to 30 pins are supported, matching the available UltraZohm adapter-card digital pins
- pin numbering is zero-based, i.e., bit ``0`` is the first pin
- input/output direction is configured during initialization through a bitmask
- dynamic direction changes during runtime are not wrapped
- interrupt support is not wrapped

The direction bitmask follows the Xilinx convention:

- ``1`` configures a pin as input
- ``0`` configures a pin as output

Use ``UZ_AXI_GPIO_DIRECTION_ALL_INPUT`` or
``UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT`` if all pins use the same direction.
Mixed input/output GPIO instances are supported by setting individual bits in
``direction_of_pins``.

Pin helpers are provided in two forms:

- ``DIG_00`` ... ``DIG_29`` are zero-based pin numbers for pin-wise functions
- ``UZ_AXI_GPIO_PIN_00`` ... ``UZ_AXI_GPIO_PIN_29`` are bit masks for mask-wise functions

Use the ``LOW`` and ``HIGH`` enum values for readable pin state arguments.

Reading Inputs
==============

Input readout is direct. Use ``uz_axi_gpio_read_bitmask`` to read the complete
GPIO channel in one AXI transaction. Use ``uz_axi_gpio_read_pin_zero_based`` if
only one pin is needed and the convenience is more important than avoiding a
full-channel read.

Project Wizard IO-card input handling
=====================================

For adapter-card AXI GPIO instances, the Project Wizard reads the complete
input bitmask once per ISR cycle and slices AXI-backed input pins into
individual actual-value variables:

.. code-block:: c

   Global_Data.av.io_card_d1_state =
      uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_d1);

   Global_Data.av.io_card_d1_dig_14 =
      (Global_Data.av.io_card_d1_state >> DIG_14) & 0x1U;

User code can use the individual ``io_card_dx_dig_yy`` variables directly.
Generated Javascope and slow-data assignments for IO-card input pins also point
to these variables directly, so the bit slicing is not duplicated in the
visualization path.

Writing Outputs
===============

The recommended output path is shadow based. Shadow functions update a local
driver-side output bitmask and do not access AXI immediately. Call
``uz_axi_gpio_flush_outputs`` once after all output changes of the current
control step are collected. This performs one AXI4-Lite write for all output
pins and updates the physical GPIO outputs together.

Typical cyclic usage:

.. code-block:: c

   uz_axi_gpio_set_output_pin(gpio, DIG_04);
   uz_axi_gpio_clear_output_pin(gpio, DIG_07);
   uz_axi_gpio_set_output_bitmask(gpio, UZ_AXI_GPIO_PIN_12 | UZ_AXI_GPIO_PIN_13);

   uz_axi_gpio_flush_outputs(gpio);

This pattern is useful in an ISR or control loop because several logical pin
changes can be grouped into one AXI transaction. The output timing is therefore
defined by the flush point, not by the individual shadow update calls.

Immediate Writes
================

For time-critical cases where a pin or bitmask must be written immediately, the
driver keeps the existing immediate functions:

- ``uz_axi_gpio_write_pin_zero_based``
- ``uz_axi_gpio_write_bitmask``

Both functions update the internal output shadow before writing to hardware.
This keeps immediate writes coherent with later shadow updates and prevents a
later ``uz_axi_gpio_flush_outputs`` from restoring stale output states.

.. note::

   Prefer shadow updates plus ``uz_axi_gpio_flush_outputs`` for cyclic code with
   several output changes. Use immediate writes only when the immediate output
   edge is intentional.

Input-Pin Masking
=================

The driver masks output writes with the configured direction bitmask. Bits
configured as inputs are ignored when the output shadow is written to hardware.
They can still be read through ``uz_axi_gpio_read_bitmask`` or
``uz_axi_gpio_read_pin_zero_based``.

Reference
=========

.. doxygentypedef:: uz_axi_gpio_t

.. doxygenenum:: uz_axi_gpio_pin_state_t

.. doxygenenum:: uz_axi_gpio_digital_pin_t

.. doxygendefine:: UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT

.. doxygendefine:: UZ_AXI_GPIO_DIRECTION_ALL_INPUT

.. doxygendefine:: UZ_AXI_GPIO_PIN_00

.. doxygendefine:: UZ_AXI_GPIO_PIN_29

.. doxygenstruct:: uz_axi_gpio_config_t
    :members:

.. doxygenfunction:: uz_axi_gpio_init

.. doxygenfunction:: uz_axi_gpio_read_bitmask

.. doxygenfunction:: uz_axi_gpio_read_pin_zero_based

.. doxygenfunction:: uz_axi_gpio_set_output_pin

.. doxygenfunction:: uz_axi_gpio_clear_output_pin

.. doxygenfunction:: uz_axi_gpio_set_output_pin_to

.. doxygenfunction:: uz_axi_gpio_set_output_bitmask

.. doxygenfunction:: uz_axi_gpio_clear_output_bitmask

.. doxygenfunction:: uz_axi_gpio_set_output_shadow

.. doxygenfunction:: uz_axi_gpio_get_output_shadow

.. doxygenfunction:: uz_axi_gpio_flush_outputs

.. doxygenfunction:: uz_axi_gpio_write_bitmask

.. doxygenfunction:: uz_axi_gpio_write_pin_zero_based

Example
=======

The loopback example uses two AXI GPIO instances: one output instance and one
input instance. The output pins are connected to the input pins in the block
design, optionally with an ILA for inspection.

.. _uz_axi_gpio_loopback:

.. figure:: uz_axi_gpio_testsetup.png

  Two AXI GPIO instances and one system ILA in loopback configuration.

Configuration:

.. code-block:: c
   :linenos:
   :caption: Configuration structs for two AXI GPIO instances.

   #include "xparameters.h"
   #include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

   struct uz_axi_gpio_config_t output_config = {
      .base_address = XPAR_UZ_USER_AXI_GPIO_0_BASEADDR,
      .device_id = XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID,
      .number_of_pins = 16,
      .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT
   };

   struct uz_axi_gpio_config_t input_config = {
      .base_address = XPAR_UZ_USER_AXI_GPIO_1_BASEADDR,
      .device_id = XPAR_UZ_USER_AXI_GPIO_1_DEVICE_ID,
      .number_of_pins = 30,
      .direction_of_pins = UZ_AXI_GPIO_DIRECTION_ALL_INPUT
   };

Shadow-based output update:

.. code-block:: c
   :linenos:
   :caption: Collect several output changes and write them with one flush.

   uz_axi_gpio_t *output_gpio = uz_axi_gpio_init(output_config);
   uz_axi_gpio_t *input_gpio = uz_axi_gpio_init(input_config);

   uz_axi_gpio_set_output_shadow(output_gpio, 0x00005050U);
   uz_axi_gpio_set_output_pin(output_gpio, 0U);
   uz_axi_gpio_clear_output_bitmask(output_gpio, UZ_AXI_GPIO_PIN_04 | UZ_AXI_GPIO_PIN_05);
   uz_axi_gpio_flush_outputs(output_gpio);

   uint32_t input_bitmask = uz_axi_gpio_read_bitmask(input_gpio);

Immediate output update:

.. code-block:: c
   :linenos:
   :caption: Write a pin immediately when the output edge must happen at this point.

   uz_axi_gpio_write_pin_zero_based(output_gpio, 0U, false);

Driver and Test Implementation
==============================

The software driver is a wrapper around the vendor-provided driver.
Relevant vendor files:

- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/src/xgpio.c
- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/src/xgpio.h
- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/examples/xgpio_example.c

Mocked versions of the vendor interfaces are used by the tests in
``vitis/software/Baremetal/test``. The ``Device id`` is defined in
``xparameters.h`` alongside the base address and identifies the AXI GPIO
instance used by the Xilinx driver initialization.
