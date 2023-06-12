========
AXI GPIO
========

This IP-Core and software driver enables the PS to control individual input/output signals inside the PL.
The core functionality of the AXI GPIO IP-Core is vendor provided:

- https://www.xilinx.com/products/intellectual-property/axi_gpio.html
- https://docs.xilinx.com/v/u/en-US/pg144-axi-gpio
- https://docs.xilinx.com/v/u/1.01b-English/ds744_axi_gpio

A software wrapper for the vendor IP-core and driver is implemented to facilitate a consistent interface with other UltraZohm IP-Cores.
Only a small subset of the capabilities is implemented in the wrapper to simplify the usage and focus on common use cases.

Features:

- Variable number of I/O between 1 and 32
- I/O numbering is zero-based (first signal is bit ``0`` / LSB)
- All input or all output is recommended for simplicity
- Output or input configurable on a per-pin basis is supported
- Only one channel (dual channel mode of the IP-Core is not supported)
- No interrupt support
- Static partitioning of pins using the pins ``gpio_oi_o`` for outputs and ``gpio_oi_i`` for inputs is possible
- Refer to AXI GPIO product guide if dynamic IO (i.e., changing inputs to outputs and vice versa during run-time) is required (i.e., correct handling of 3-state buffer)
- The number of pins is configurable 
- If the bitmask functions access more pins than are available, the spare bits are ignored
- If the pin-wise function accesses more pins than are available, an assertion is triggered

Reference
=========

.. note:: Using the Pin-wise functions requires one AXI4-lite read/write (takes approx. :math:`1\,\mu s`) per function call. If multiple pins have to be set, using the bitmask-based functions improves speed significantly (one AXI4-lite read/write for all 32 pins)


.. doxygentypedef:: uz_axi_gpio_t

.. doxygendefine:: UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT

.. doxygendefine:: UZ_AXI_GPIO_DIRECTION_ALL_INPUT

.. doxygenstruct:: uz_axi_gpio_config_t
    :members:

.. doxygenfunction:: uz_axi_gpio_init

.. doxygenfunction:: uz_axi_gpio_write_pin_zero_based

.. doxygenfunction:: uz_axi_gpio_read_pin_zero_based

.. doxygenfunction:: uz_axi_gpio_write_bitmask

.. doxygenfunction:: uz_axi_gpio_read_bitmask


Example
=======

Example using two AXI GPIO in a loopback example, i.e., one AXI GPIO is configured as an output which are fed to the other AXI GPIO instance which is configured as an input.
The example loops and flips all bits in each iteration by reading the input AXI GPIO and feeding back the flipped bitmask to the output AXI GPIO.
Additionally, the bit 0 is flipped in each iteration.


.. _uz_axi_gpio_loopback:

.. figure:: uz_axi_gpio_testsetup.png

  Two AXI GPIO instances and one system ILA in loopback configuration.

.. code-block:: c
   :linenos:
   :caption: Code for configuration structs of AXI GPIO. Add to, e.g., top of main.c for testing.

    #include "xparameters.h"
    // Base addresses and device ID are from xparameters:
    // XPAR_UZ_USER_AXI_GPIO_0_BASEADDR
    // XPAR_UZ_USER_AXI_GPIO_1_BASEADDR
    //
    #include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

    struct uz_axi_gpio_config_t output_config={
    		.base_address=XPAR_UZ_USER_AXI_GPIO_0_BASEADDR,
    		.device_id=XPAR_UZ_USER_AXI_GPIO_0_DEVICE_ID,
    		.number_of_pins=16,
    		.direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_OUTPUT
    };

    struct uz_axi_gpio_config_t input_config={
    		.base_address=XPAR_UZ_USER_AXI_GPIO_1_BASEADDR,
    		.device_id=XPAR_UZ_USER_AXI_GPIO_1_DEVICE_ID,
    		.number_of_pins=32,
    		.direction_of_pins=UZ_AXI_GPIO_DIRECTION_ALL_INPUT
    };

    uint32_t output_bitmask=0xaaaa5050U;


.. code-block:: c
   :linenos:
   :caption: Code for init and bit-flipping of AXI GPIO. Add to, e.g., main state machine after initialization but before interrupt initialization.

    uz_axi_gpio_t* output_gpio=uz_axi_gpio_init(output_config);
    uz_axi_gpio_t* input_gpio=uz_axi_gpio_init(input_config);

    while(1){
        uz_axi_gpio_write_bitmask(output_gpio,~output_bitmask);
        output_bitmask=uz_axi_gpio_read_bitmask(input_gpio);
        uz_axi_gpio_write_pin_zero_based(output_gpio, 0U, false);
        output_bitmask=uz_axi_gpio_read_bitmask(input_gpio);
    }


Driver and test implementation
==============================

The software driver is a wrapper around the vendor-provided driver.
Relevant files:

- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/src/xgpio.c
- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/src/xgpio.h
- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/examples/xgpio_example.c

These files are added to be mocked to the test directory ``vitis/software/Baremetal/test/support``.
Specifically, ``xgpio.h`` is added from the ``embeddedsw`` repository and modified.
The include ``#include "xgpio_l.h"`` inside ``xgpio.h`` is deleted to break the dependency of ``xgpio.h`` to other vendor provided modules.
This works since ``xgpio.h`` is never used directly but only mocked.

In addition to the commonly used ``base address`` in the software driver that directs the driver to the memory address of the AXI interface of the IP-Core, the ``Device id`` is required.
The ``Device id`` is defined in ``xparameters.h`` alongside the ``base address`` and numbers the different instances of the AXI GPIO IP-Core.




