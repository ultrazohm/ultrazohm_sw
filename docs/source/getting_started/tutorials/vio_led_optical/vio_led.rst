==========================
Virtual Input Output (VIO) 
==========================

Aim of the tutorial
*******************

In this tutorial, the Virtual Input Output (VIO) IP-Core is used to light up LEDs on the optical adapter board.

After this tutorial, you can:

- Connect to the programmed FPGA with Vivado
- Use the VIO
- Test the optical adapter board

Requirements
************

The following tutorial requires:

- Complete UltraZohm Toolchain (Vivado, Vitis, ultrazohm_sw repository)
- UltraZohm connected to your PC by Ethernet and USB (JTAG)
- Optical adapter card in slot D3 (:ref:`dig_optical`)


UltraZohm Setup
***************

The UltraZohm has to be connected to a PC by Ethernet and USB (JTAG-Programmer) and the optical adapter card is in D3.

.. image:: ./img/vio_physical_setup.png

VIO usage
*********

Updated information
-------------------

- With optical adapter card **2v02** one must set Output 19 to high, since this is the **ENABLE** signal of the optical card
- VIO IP-Core name at `1:02 <https://youtu.be/jtIzec7ymQA?t=62>`_ has changed to *vio_D34_test*
- The output ports are now labeled **D3_OUT[25:0]** instead of **Dig_Ch4[25:0]**
- The selection for the **hw_vio** channel at `1:25 <https://youtu.be/jtIzec7ymQA?t=85>`_ changed: It is now **hw_vio_6** instead of **hw_vio_5**.

.. figure:: ./img/Block_Design.png
   :align: center

   Current location and name of vio IP-Core for testing D3


.. youtube:: jtIzec7ymQA

.. figure:: https://images2.imgbox.com/d3/5a/JaM3wGSv_o.gif
   :align: center

