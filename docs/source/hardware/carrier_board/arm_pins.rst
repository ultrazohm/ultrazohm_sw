========================
Overview of the ARM Pins
========================

In the following table you will find an overview of the pin mapping of the SoC MIO pins (ARM pins of the SoCs' Processing System).
All accessible MIO pins through a connector are labeled with the appropriate carrier board schematic label in column **Schematic Connector Label** and the connector pin in column **CB-Pin** (CB --> Carrier Board).
The connectivity between MIO pin and the four user LEDs is shown by column **LED**.

.. csv-table:: Overview of the MIO Pins
  :file: interfaces/MIO_Pinout.csv
  :widths: 5 8 8 5 10 5 5
  :header-rows: 1



Interface description
---------------------

The following diagrams show the signal flow of all communication interfaces.

^^^^^^^^^^^^^^^^^^
I2C0
^^^^^^^^^^^^^^^^^^

	* I2C0 is shared over all Digital- and Analog-Adapter-Sockets --> this is in order to read out errors after the "Collective Fault" switched of in an error case!
	* I2C0 is also used to configure the PLL chip Si5345 during start-up, which sets up all clocks. See `the Trenz-Elektronik Wiki <https://wiki.trenz-electronic.de/display/PD/Si5345>`_
	  
.. mermaid::

	graph TD
		SoM[SoM]
		SoM --> |1.8 V| U4A(CPLD U4A)
		SoM --> |1.8 V| U4B(CPLD U4B)
		SoM --> |1.8 V| U4C(CPLD U4C)
		SoM --> |1.8 V| U4D(CPLD U4D)
		SoM --> |1.8 V| U4E(CPLD U4E)
		SoM --> |1.8 V| U30[Level Shifter U30]
		U30 --> |3.3 V| A1(A1)
		U30 --> |3.3 V| A2(A2)
		U30 --> |3.3 V| A3(A3)
		U30 --> |3.3 V| D1(D1)
		U30 --> |3.3 V| D2(D2)
		U30 --> |3.3 V| D3(D3)
		U30 --> |3.3 V| D4(D4)
		U30 --> |3.3 V| D5(D5)


^^^^^^^^^^^^^^^^^^
I2C1
^^^^^^^^^^^^^^^^^^

	* I2C1 is for free use but without isolated interface
	
.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U14[Level Shifter U14]
		U14 --> |3.3 V| X10


^^^^^^^^^^^^^^^^^^
UART0
^^^^^^^^^^^^^^^^^^

	* UART0 is available at the XMOD connector for the TE0790 module (JTAG interface)
	
.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| X8


^^^^^^^^^^^^^^^^^^
UART1
^^^^^^^^^^^^^^^^^^

	* UART_1 is for free use, but without isolated interface
	
.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U14(Level Shifter, U14)
		U14 --> |3.3 V| X10


^^^^^^^^^^^^^^^^^^
CAN0
^^^^^^^^^^^^^^^^^^

.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U6A(CAN PHY, U6A<br>Isolation)
		SoM --> |1.8 V| P1A(P1A)
		U6A --> |5.0 V| X7A


^^^^^^^^^^^^^^^^^^
CAN1
^^^^^^^^^^^^^^^^^^

.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U6B(CAN PHY, U6B<br>Isolation)
		SoM --> |1.8 V| P1B(P1B)
		U6B --> |5.0 V| X7B


^^^^^^^^^^^^^^^^^^
SPI0
^^^^^^^^^^^^^^^^^^

.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U14(Level Shifter, U14)
		U14 --> |3.3 V| X10


^^^^^^^^^^^^^^^^^^
SPI1
^^^^^^^^^^^^^^^^^^

.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U17(Level Shifter, U17)
		U17 --> |3.3 V| U18(Digital Isolator, U6A<br>Isolation)
		U18 --> |3.3 V| X12


^^^^^^^^^^^^^^^^^^
Ethernet
^^^^^^^^^^^^^^^^^^

.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U2(U2 <br> ETH PHY)
		U2 --> |3.3 V| X4(X4 <br> RJ45)


^^^^^^^^^^^^^^^^^^^
GPIO0, GPIO1, GPIO2
^^^^^^^^^^^^^^^^^^^

.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| U25(U25 <br> Level Shifter)
		U25 --> |3.3 V| U24(U24 <br> Digital Isolator)
		U25 --> |3.3 V| U26(U26 <br> Digital Isolator)
		U24 --> |3.3 V| IO_protection(I/O Protection <br> TVS, PTC Fuse)
		U26 --> |3.3 V| IO_protection
		IO_protection --> X13
		SoM --> |1.8 V| LEDs
		SoM --> |1.8 V| X11


^^^^^^^^^^^^^^^^^^
PJTAG
^^^^^^^^^^^^^^^^^^

.. mermaid::

	graph LR
		SoM[SoM]
		SoM --> |1.8 V| X9




Pin capabilities
----------------

For detailed information see the `Xilinx Technical Refrence Manual UG1085 (v2.2) for the Zynq UltraScale+ <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G30.498111>`_

The MIO interface description can be found on page under chapter 28 *Multiplexed I/O* (*Table 28-3: MIO Interfaces*).
