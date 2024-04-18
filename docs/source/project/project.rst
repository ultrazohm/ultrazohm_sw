.. _SystemOverview:

===============
System Overview
===============

* UltraZohm is a powerful real-time computation unit
* The UltraZohm is used to control power electronics and electrical drives
* The UltraZohm is work in progress
* Funded by `BMBF-Project KI-Power <https://www.elektronikforschung.de/projekte/ki-power>`_

.. _UltraZohmFront:

.. figure:: front_lowres.png
   :width: 400px
   :align: center

   Front of the UltraZohm.

Requirements of the UltraZohm
*****************************

Development goals
-----------------

Computational power
 The use of more complex control algorithms based on model predictive control and/or artificial intelligence, as well as the increased use of wide-band gap power electronics, require a real-time computing unit with sufficient processing power.
 The necessary processing power is provided by the UltraZohm.
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
 Adapter cards are used as a flexible interface for analoge and digital signals such as ADC's and gate signals for power electronics.
 Software modularity is achieved by using encapsulated design patterns combined with IP-Cores on the FPGA.

Usability
 We aim to create a system with a high usability.
 The UltraZohm is **novice friendly** since there are a lot of different tutorials, existing IP-Cores and adapter cards that are used by the community.
 Therefore, a new user does not have to start from scratch.
 The UltraZohm is **expert friendly** since there are **no black boxes** in the system.
 Due to project being open source, every user can investigate every line of code, every IP-Core and the complete signal chain in the schematics.
 Furthermore, **everybody** is encouraged to :ref:`contribute <contribution>` to the UltraZohm and improve the system!

Requirements
------------

The following requirements are derived from the development goals of the UltraZohm.

.. csv-table:: table
    :file: requirements.csv
    :widths: 10 10 10 10
    :header-rows: 1


Overview of the project
***********************

The UltraZohm project is hosted on a bitbucket `repository <https://bitbucket.org/ultrazohm/ultrazohm_sw>`_.
The repository is structured in the following way, with some important files highlighted.
The source of this documentation is located in ``ultrazohm_sw/docs/source/``.
The online version (docs.ultrazohm.com) is always the documentation of the current state of the ``main`` branch.

::

    ultrazohm_sw/
    ├── docs/
    |   ├── source/ 
    |   ├── requirements.txt
    |   └── Makefile
    ├── ip_core/
    ├── javascope/
    ├── tcl_scripts/
    |   ├── vivado_export_xsa.tcl
    │   ├── vitis_generate_UltraZohm_workspace.tcl
    │   └── vitis_update_platform.tcl
    ├── vitis/
    |   ├── software/
    │   └── vivado_exported_xsa
    |      └── zusys_wrapper.xsa
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


.. toctree::
   :maxdepth: 3

   useCases/useCases
   project_structure/project_structure
   infrastructure/infrastructure
   how_to_guides/how_to_guides
   