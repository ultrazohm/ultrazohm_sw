============
ADC Loopback
============

Aim of the tutorial
*******************

In this tutorial, the digital voltage adapter board is used to generate a PWM signal at D3.
You can use a scope to measure the gate Signal.
In the video, an RC-circuit is used as a low-pass.
Furthermore, this signal is looped back to the ADC of the UltraZohm and read out.


After this tutorial, you can:

 - Use the PWM-module
 - Test the optical adapter board
 - Use the ADC adapter card
 - read out ADC

Requirements
************

The following tutorial requires:

- Complete UltraZohm Toolchain (Vivado, Vitis, ultrazohm_sw repository)
- UltraZohm connected to your PC by USB (JTAG)
- Digital voltage card in slot D1 (:ref:`digitalVoltage`)
- Analog adapter card ADC :ref:`analog_tcl` in slot D1 (:ref:`digitalVoltage`)

.. UltraZohm Setup
.. ***************

.. The UltraZohm has to be connected to a PC by Ethernet and USB (JTAG-Programmer) and the optical adapter card is in D3.

.. .. image:: ./img/vio_physical_setup.png

ADC usage
*********

.. youtube:: omQ-nHE6q4w