========================
Overview of the ARM Pins
========================

In the following table you will find an overview of the pin mapping of the hard wired ARM processors.

.. csv-table:: Overview of the hardwired ARM-Pins
   :header: "MIO", "Xilinx", "Function", "Voltage Level [V]", "Schematic", "ISO & PTC", "Schematic Shifted", "LED"
   :widths: 8, 15, 15, 15, 10, 10, 15, 8

   0, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   1, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   2, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   3, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   4, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   5, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   6, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   7, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   8, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   9, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   10, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   11, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   12, :bg-seagreen:`QSPI (for memory)`, , 1.8, , ,
   13, :bg-red:`GPIO`, :bg-red:`IO[13]`, 1.8, :bg-red:`PS_GPIO1`, yes, :bg-red:`EXT_GPIO1 (3.3V)`, :bg-red:`LED1`
   14, :bg-green:`I2C_0`, :bg-green:`SCL`, 1.8, , ,
   15, :bg-green:`I2C_0`, :bg-green:`SDA`, 1.8, , ,
   16, :bg-green:`I2C_1`, :bg-green:`SCL`, 1.8, , ,
   17, :bg-green:`I2C_1`, :bg-green:`SDA`, 1.8, , ,
   18, :bg-green:`UART0 (@JTAG-Con)`, :bg-green:`Rx`, 1.8, , ,
   19, :bg-green:`UART0 (@JTAG-Con)`, :bg-green:`Tx`, 1.8, , ,
   20, :bg-green:`UART1`, :bg-green:`Tx`, 1.8, , ,
   21, :bg-green:`UART1`, :bg-green:`Rx`, 1.8, , ,
   22, :bg-green:`CAN_0`, :bg-green:`Rx`, 1.8, , ,
   23, :bg-green:`CAN_0`, :bg-green:`Tx`, 1.8, , ,
   24, :bg-green:`CAN_1`, :bg-green:`Tx`, 1.8, , ,
   25, :bg-green:`CAN_1`, :bg-green:`Rx`, 1.8, , ,
   26, :bg-purple:`PS_JTAG`, :bg-purple:`TCK`, 1.8, , ,
   27, , :bg-purple:`TDI`, 1.8, , ,
   28, , :bg-purple:`TDO`, 1.8, , ,
   29, , :bg-purple:`TMS`, 1.8, , ,
   30, , IO[4], 1.8, :bg-red:`PS_DIG_GPIO_01_1.8V`, ,
   31, :bg-red:`GPIO1`, :bg-red:`IO[5]`, 1.8, :bg-red:`PS_DIG_GPIO_02_1V8`, , :bg-red:`PS_DIG_GPIO_02_3V3`,
   32, :bg-yellow:`SPI_1`, :bg-yellow:`SCLK`, 1.8,
   33, :bg-red:`GPIO1`, :bg-red:`IO[7]`, 1.8, :bg-red:`PS_GPIO2 (1V8)`, yes, :bg-red:`EXT_GPIO2 (3V3)`, LED2
   34, :bg-red:`GPIO1`, :bg-red:`IO[8]`, 1.8, :bg-red:`PS_GPIO3 (1V8)`, yes, :bg-red:`EXT_GPIO3 (3V3)`, LED3
   35, :bg-yellow:`SPI_1`, :bg-yellow:`n_ss_out[0]`, 1.8,
   36, :bg-yellow:`SPI_1`, :bg-yellow:`MISO`, 1.8,
   37, :bg-yellow:`SPI_1`, :bg-yellow:`MOSI`, 1.8,
   38, :bg-yellow:`SPI_0`, :bg-yellow:`SCLK`, 1.8,
   39, :bg-red:`GPIO1`, :bg-red:`IO[13]`, 1.8, :bg-red:`PS_DIG_GPIO4 (1V8)`, yes, :bg-red:`EXT_GPIO4 (3V3)`, LED4
   40, :bg-red:`GPIO1`, :bg-red:`IO[14]`, 1.8, :bg-red:`PS_DIG_GPIO5 (1V8)`, yes, :bg-red:`EXT_GPIO5 (3V3)`
   41, :bg-yellow:`SPI_0`, :bg-yellow:`n_ss_out[0]`, 1.8,
   42, :bg-yellow:`SPI_0`, :bg-yellow:`MISO`, 1.8,
   43, :bg-yellow:`SPI_0`, :bg-yellow:`MOSI`, 1.8,
   44, :bg-red:`GPIO1`, :bg-red:`IO[18]`, 1.8, :bg-red:`PS_ANL_GPIO_01_1V8`, , :bg-red:`PS_ANL_GPIO_01_3V3`
   45, :bg-red:`GPIO1`, :bg-red:`IO[19]`, 1.8, :bg-red:`PS_ANL_GPIO_02_1V8`, , :bg-red:`PS_ANL_GPIO_02_3V3`
   46, :bg-gray:`SD-Card1`, :bg-gray:`DO0`, 1.8,
   47, , :bg-gray:`DO1`, 1.8,
   48, , :bg-gray:`DO2`, 1.8,
   49, , :bg-gray:`DO3`, 1.8,
   50, , :bg-gray:`CMD`, 1.8,
   51, , :bg-gray:`CLK`, 1.8,
   52, :bg-bisque:`USB_0`, :bg-bisque:`CLK`, 1.8, :bg-red:`PS_GPIO7 (1V8)`, yes, :bg-red:`PS_GPIO7 (3V3)`
   53, :bg-bisque:`USB_0`, :bg-bisque:`DIR`, 1.8, :bg-red:`PS_GPIO6 (1V8)`, yes, :bg-red:`PS_GPIO6 (3V3)`
   54, :bg-bisque:`USB_0`, :bg-bisque:`Tx2`, 1.8,
   55, :bg-bisque:`USB_0`, :bg-bisque:`NXT`, 1.8, :bg-red:`PS_GPIO8 (1V8)`, yes, :bg-red:`PS_GPIO8 (3V3)`
   56, :bg-bisque:`USB_0`, :bg-bisque:`Tx0`, 1.8,
   57, :bg-bisque:`USB_0`, :bg-bisque:`Tx1`, 1.8,
   58, :bg-bisque:`USB_0`, :bg-bisque:`STP`, 1.8,
   59, :bg-bisque:`USB_0`, :bg-bisque:`Tx3`, 1.8,
   60, :bg-bisque:`USB_0`, :bg-bisque:`Tx4`, 1.8,
   61, :bg-bisque:`USB_0`, :bg-bisque:`Tx5`, 1.8,
   62, :bg-bisque:`USB_0`, :bg-bisque:`Tx6`, 1.8,
   63, :bg-bisque:`USB_0`, :bg-bisque:`Tx7`, 1.8,
   64, :bg-brown:`Ethernet`, :bg-brown:`Tx_clk`, 1.8,
   65, :bg-brown:`Ethernet`, :bg-brown:`Tx0`, 1.8,
   66, :bg-brown:`Ethernet`, :bg-brown:`Tx1`, 1.8,
   67, :bg-brown:`Ethernet`, :bg-brown:`Tx2`, 1.8,
   68, :bg-brown:`Ethernet`, :bg-brown:`Tx3`, 1.8,
   69, :bg-brown:`Ethernet`, :bg-brown:`Tx_CTL`, 1.8,
   70, :bg-brown:`Ethernet`, :bg-brown:`Rx_CLK`, 1.8,
   71, :bg-brown:`Ethernet`, :bg-brown:`Rx0`, 1.8,
   72, :bg-brown:`Ethernet`, :bg-brown:`Rx1`, 1.8,
   73, :bg-brown:`Ethernet`, :bg-brown:`Rx2`, 1.8,
   74, :bg-brown:`Ethernet`, :bg-brown:`Rx3`, 1.8,
   75, :bg-brown:`Ethernet`, :bg-brown:`Rx_CTL`, 1.8,
   76, :bg-brown:`Ethernet`, :bg-brown:`MDC`, 1.8,
   77, :bg-brown:`Ethernet`, :bg-brown:`MDIO`, 1.8,


Interface description
---------------------

It has to be noted that one SPI is for the CPLD communication and the QSPI is for the memory.
So we have free interfaces for our use:

* 2x UART:

	* 1x UART (UART_1) is for free use, but without isolated interface (chip = U14)
	* 1x UART (UART_0) is at the XMOD for the JTAG interface without isolated interface

* 2x I2C:

	* 1x I2C (I2C1) is for free use but without isolated interface (chip = U14) -> available at an external connector
	* 1x I2C (I2C0) is shared over all Digital- and Analogue-Adapter-Boards without isolated interface ->
	  this is in order to read out errors after the "Collective Fault" switched of in an error case!
	* More important, this "I2C_0" is used to configure the PLL chip Si5345 during start-up, which sets up all clocks.
	  See `the Trenz-Elektronik Wiki <https://wiki.trenz-electronic.de/display/PD/Si5345>`_

* 2x CAN:

	* Both are for free use over an isolated interface (chip = U6)

* 1x JTAG
* 2x SPI:

	* 1x SPI (SPI1) is for free use over an isolated interface (chip = U17)
	* 1x SPI (SPI0) is for free use but without isolated interface (chip = U14) -> we should use this as interface to the Digital-Adapterboard-Connector!?
	* Note, there is an extra SPI interface from the FPGA (PL) shared for the Analogue-Adapter-Board without isolated interface in order for the Slow-ADC-Adapter-boards!
	* Missing SPI: SPI to Configure the potentiometer for the ADC threshold-voltage -> Chilean colleagues want to have this. Or is the shared I2C enough?

* 1x SD-Card:

	* SD Card 1 is used (SD Card 0 is not used and not implemented)

* 1x USB
* 1x Ethernet
* 9x GPIOs ( + Dual use Pins if you don’t use SD-Card or USB or whatever)


Pin capabilities
----------------

For detailed information see the `Xilinx Technical Refrence Manual UG1085 for the Zynq UltraScale+ <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf>`_

The MIO interface description can be found on page 782 to 787. See especially the tables on pages 789 and 790.
