=======
Encoder
=======

Aim of the tutorial
*******************

In this tutorial, the encoder card is used to measure a mechanical angle.

After this tutorial, you can:

- Read out the encoder

Requirements
************

The following tutorial requires:

- Complete UltraZohm Toolchain (Vivado, Vitis, ultrazohm_sw repository)
- UltraZohm connected to your PC by Ethernet and USB (JTAG)
- Encoder card in D5 (:ref:`dig_incEncoder`)
- Incremental Encoder (Kübler 8.5000.8344.2000 is used here)


.. UltraZohm Setup
.. ***************

.. The UltraZohm has to be connected to a PC by Ethernet and USB (JTAG-Programmer) and the optical adapter card is in D3.

.. .. image:: ./img/vio_physical_setup.png

Read out Encoder
****************

.. youtube:: n5EbyrPFRE0

Updated information
*******************

``js_ch_observable[JSO_Theta_el] = &data->av.theta_elec`` and ``js_ch_observable[JSO_theta_mech] = &data->av.theta_mech`` are now in the ``javascope.c`` instead of the ``isr.c``. The rest remains unchanged. 

