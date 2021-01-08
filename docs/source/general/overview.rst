===============
System Overview
===============

* UltraZohm is a powerful real-time computation unit
* The UltraZohm is used to control power electronics and electrical drives
* The UltraZohm is work in progress
* Funded by `BMBF-Project KI-Power <https://www.elektronikforschung.de/projekte/ki-power>`_

Requirements of the UltraZohm
*****************************

Development goals
-----------------

Computation power
 The usage of more complex control algorithms based on model predictive control and/or artificial intelligence as well as the increased useage of wide-band gap power electronics require a real-time computation unit with sufficient computational power.
 This computational power is be provided by the UltraZohm.
 A heterogenous SoC is used due to the diverse requirements of different applications and control algorithms.
 The UltraZohm project uses the `Xilinx Zynq UltraScale+ MPSoC <https://www.xilinx.com/products/silicon-devices/soc/zynq-ultrascale-mpsoc.html>`_ on a SoM by `Trenz Electronics <https://shop.trenz-electronic.de/de/Produkte/Trenz-Electronic/TE08XX-Zynq-UltraScale/TE0808-Zynq-UltraScale/>`_.

Hard real-time
 *Fast* calculations are not sufficient for the control of power electronics which require hard real-time, i.e. the system must meet the real-time at all times.
 Missing the real-time results in malfunction, undefined behavior or failure of the system.
 The UltraZohm is designed to meet these hard real-time requirements.
 Control algorithms for power electronics and electrical drives typically require a control time of :math:`5 \mu s` to :math:`100 \mu s`. 

Modularity
 The UltraZohm is modular in terms of software and hardware.
 The system can be used with different devices within the UltraScale MPSoC family.
 Adaptercards are used as a flexible interface for analoge and digital signals such as ADC's and gate signals for power electronics.
 Software modularity is achieved by using encapsulated design patterns combined with IP-Cores on the FPGA.

Requirements
------------

The following requirements are derived from the development goals of the UltraZohm.

.. csv-table:: table
    :file: requirements.csv
    :widths: 10 10 10 10 10
    :header-rows: 1


Overview of the project
***********************

The UltraZohm project is hosted on a bitbucket `repository <https://bitbucket.org/ultrazohm/ultrazohm_sw>`_.
The repository is structured in the following way, which some important files highlighted.
The source of this documentation is located in ``ultrazohm_sw/docs/source/``.
The online version (docs.ultrazohm.com) is always the documentation of the current state of the ``main`` branch.

::

    ultrazohm_sw/
    ├── docs/
    |   ├── source/ 
    |   ├── requirements.txt
    |   └── Makefile
    ├── ip_core/
    ├── tcl_scripts/
    |   ├── vivado_export_xsa.tcl
    │   ├── vitis_generate_UltraZohm_workspace.tcl
    │   └── vitis_update_platform.tcl
    ├── vitis/
    |   ├── export/
    │   ├── vivado_exported_xsa
    |   |   └── zusys_wrapper.xsa
    │   └── vitis_update_platform.tcl
    └── vivado/
        └── project/
            └── ultrazohm.xpr

Simple block diagram of UltraZohm
---------------------------------

.. raw:: html
    :file: block_diagram_simple.svg


Components of UltraZohm
-----------------------

.. mermaid::

  graph TD
  UltraZohm --> Cabinet
  UltraZohm --> Carrier-Board
  UltraZohm --> Adapter
  UltraZohm --> SoM

Interfaces of Carrier-Board
---------------------------

.. mermaid::

  graph TD
  Carrier-Board --> Power("Power Supply")
  Power --> p_in("Power Input")
  Power --> p_out("Power Output")
  Carrier-Board --> SoM("SoM")
  Carrier-Board --> analog("Analog (A1..A3)")
  Carrier-Board --> dig("Digital (D1..D5)")
  Carrier-Board --> JTAG
  JTAG --> CPLD
  JTAG --> MPSoC
  Carrier-Board --> SD-Card
  Carrier-Board --> PS_GPIO("PS GPIO")
  Carrier-Board --> Communication
  Communication --> SPI
  Communication --> Serial
  Communication --> Ethernet
  Communication --> CAN


Interfaces of Cabinet
---------------------

.. mermaid::

  graph TD
  Cabinet --> Rack
  Cabinet --> Power-Supply
  Power-Supply --> Line-Voltage-Plug
  Cabinet --> Front-Plane
  Front-Plane --> Communication
  Front-Plane --> Power-ON
  Front-Plane --> Button
  Front-Plane --> LED
  LED --> LED1
  LED --> LED2
  LED --> LED3
  LED --> LED4
  Button --> SW1
  Button --> SW2
  Button --> SW3
  Button --> External-Stop
  Communication --> Ethernet
  Communication --> CAN
  Communication --> JTAG
