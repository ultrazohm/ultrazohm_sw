========
XCP Introduction
========

.. _xcp_intro:


XCP (Universal Measurement and Calibration Protocol)
----------------------------------------------------

The **Universal Measurement and Calibration Protocol (XCP)** is an **ASAM** standardized communication protocol for measurement, calibration, and parameterization of embedded systems. It provides standardized access to internal variables and parameters of an application without requiring application-specific communication interfaces. Instead, memory objects are described by an A2L file and accessed based on their memory addresses.

A key feature of XCP is the separation of the protocol layer from the transport layer. This allows the same XCP protocol stack to operate over different communication interfaces, including CAN, Ethernet (UDP/TCP), USB, and SPI. XCP follows a master-slave architecture, where a measurement and calibration tool (master) communicates with the target device (slave).

The UltraZohm integrates the open-source implementation **XCPlite** (reference: https://github.com/vectorgrp/XCPlite), which provides an XCP-over-Ethernet server for high-performance measurement and calibration. XCPlite enables external XCP master tools to access measurement variables, calibrate parameters, and exchange data with the running application.

There are several XCP master tools available:

- CANape (Vector) - industry standard
- INCA (ETAS)
- ControlDesk (dSPACE)
- PCAN-Explorer (PEAK-System)
- OpenXCP / pyXCP (Open Source)
- MATLAB / Simulink (MathWorks)

More documentation about the XCP protocol layer can be found in the free available reference book "XCP – The Standard Protocol for ECU Development" (PDF) from Vector:

https://www.vector.com/int/en/download/reference-book-xcp-the-standard-protocol-for-ecu-development-pdf/
