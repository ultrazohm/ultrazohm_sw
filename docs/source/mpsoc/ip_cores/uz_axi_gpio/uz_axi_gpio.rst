===========
uz_axi_gpio
===========

The AXI GPIO core is provided by AMD/Xilinx:

- https://www.xilinx.com/products/intellectual-property/axi_gpio.html
- https://docs.xilinx.com/v/u/en-US/pg144-axi-gpio
- https://docs.xilinx.com/v/u/1.01b-English/ds744_axi_gpio

A software wrapper for the vendor IP-core and driver is implemented to facilitate a consistent interface with custom IP-Cores.
Only a small subset of the capabilities is implemented in the wrapper.


Features:

- Variable number of pins
- Output or input (how to mix in one instance?)
- Only one channel (dual channel mode not supported)
- No interrupt support
- All input or all output is recommended for simplicity
- Static partitioning of pins using the pins ``gpio_oi_o`` for outputs and ``gpio_oi_i`` for inputs is possible
- Refer to AXI GPIO product guide if dynamic IO (i.e., changing inputs to outputs and vice versa during run-time) is required (i.e., correct handling of 3-state buffer)
- Number of pins is configurable between 1 and 32.
- If the bitmask functions accesses more pins than are available, the spare bits are ignored
- If the pin-wise function accesses more pins than are available, an assertion is triggered


Relevant files:

- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/src/xgpio.c
- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/src/xgpio.h
- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/gpio/examples/xgpio_example.c





