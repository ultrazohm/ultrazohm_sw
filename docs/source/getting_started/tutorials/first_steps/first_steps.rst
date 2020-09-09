==============================
First steps with the UltraZohm
==============================

Aim of the tutorial
***************

In this tutorial, the GUI (Javascope) is used to visualize the life check variable of the R5 of the UltraZohm. Furthermore, a sine wave calculation is added to the interrupt service routine (isr.c) of the R5. The Javascope is used to visualize the sine wave.

After this tutorial, you can:

- Make changes to the PS of the system
- Build the Vitis project to incorporate the changes
- Transfer the bitstream & software to the UltraZohm
- Start a debug session
- Use the Javascope to visualize variables of the R5

Requirements
************

The following tutorial requires:

- Complete Xilinx Toolchain (Vivado, Vitis) installation
- git installation
- Java installation
- Cloned all UltraZohm repositories from Bitbucket
- UltraZohm connected to your PC by Ethernet and USB (JTAG)


UltraZohm Setup
***************

The UltraZohm has to be connected to a PC by Ethernet and USB (JTAG-Programmer).

.. image:: ./img/physical_setup.jpg

Visualize the life check
**********************

The ISR's life check variable (f_ISRLifeCheck) has to be written to the Javascope struct js_ptr_arr to display it in the Javascope GUI. The following line achieves this.

.. code-block:: c

    js_ptr_arr[JSO_Sawtooth1] = &f_ISRLifeCheck;


.. image:: ./img/1_after_build.jpg