.. _dig_incEncoderRev02:

==============================
Digital IncrEncoder Rev02
==============================


.. image:: incr_encoder_rev02/incr_encoder_rev02_pcb.jpg
   :height: 500

Functionality
-----------------------
* Connects three incremental encoder FPGA
* Provides isolated 5V supply to encoder
* Reads differential signals from encoder


Pinout (exemplary for Encoder 1)
"""""""""""""""""""""""""""""""""
=====  ========  ==========  =====================
Pin    D-Sub 9     FPGA        Kubrich Encoder 
=====  ========  ==========  =====================
0+      3        Dig_14_Ch5    blue
0-      4                      red
A+      8        Dig_13_Ch5    green
A-      7                      yellow
B+      5        Dig_12_Ch5    grey
B-      9                      pink
Vcc     2                      brown
GND     1                      white
=====  ========  ==========  =====================


* Program CPLDs with firmware, see :ref:`label_cpld_programming` for details

Known issues
-----------------------
* Rev 02: Twisted labels for Encoder signals. Constraint file Digital_AdapterBoard_D5 in vivado project has to be changed.

Pin configuration
"""""""""""""""""""""""""""

===============  ==========  ============
Package PIN D5   Port        Signal
===============  ==========  ============
E14              Dig_20_Ch5   Encoder_3_I
J15              Dig_19_Ch5   Encoder_3_A
A13              Dig_18_Ch5   Encoder_3_B
K15              Dig_17_Ch5   Encoder_2_I
B13              Dig_16_Ch5   Encoder_2_A
G14              Dig_15_Ch5   Encoder_2_B
A14              Dig_14_Ch5   Encoder_1_I
G15              Dig_13_Ch5   Encoder_1_A
B14              Dig_12_Ch5   Encoder_1_B
===============  ==========  ============

* :download:`Example constraint file for te0808<incr_encoder_rev2/Digital_AdapterBoard_D5.xdc>`


Vivado block design with three IP-Cores on D5
--------------------------------------------------
.. image:: incr_encoder_rev02/vivado_block.jpg
   :height: 500

Compatibility 
----------------------
* Slots D1 to D5 can be used without limitations, D5 is suggested. 
* Block design in vivado has to be adapted with three IP-Cores for reading out.


See also
"""""""""""""""
* :download:`Schematic V02 <incr_encoder_rev02/SCH_UZ_D_Incr_Encoder_Default_Rev02.pdf>`
* :ref:`label_cpld_programming`


Designed by 
"""""""""""""""
Michaela Hlatky (THN) in 02/2022
