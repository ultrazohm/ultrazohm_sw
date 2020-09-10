===============
System Overview
===============

* Overview over the complete system
* Block diagram of the system


Documentation
=============

.. mermaid::

  graph TD
  A[UltraZohm documentation]
  A --> B[What kind of documentation am I looking for?]
  B -->|Reference| D[docs]
  B -->|Processes| E[Nextcloud]
  B -->|Source| F[Bitbucket]

Simple block diagram of UltraZohm
=================================

.. raw:: html
    :file: block_diagram_simple.svg


Components of UltraZohm
=======================

.. mermaid::

  graph TD
  UltraZohm --> Cabinet
  UltraZohm --> Carrier-Board
  UltraZohm --> Adapter
  UltraZohm --> SoM

Interfaces of Carrier-Board
===========================

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
=====================

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
