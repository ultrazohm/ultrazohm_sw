.. _dig_incEncoderRev04:

=========================
Digital IncrEncoder Rev04
=========================

.. image:: incr_encoder_rev04/incr_encoder_rev04_pcb.jpg
   :height: 500

It is based on :ref:`Digital IncrEncoder Rev03 <dig_incEncoderRev03>` and introduces the changes listed below.

Changes from Rev03
------------------

* The LED issue present in Rev03 has been fixed.
* An EEPROM has been added.
* The ``Power_Load_LEDs10mA.SchDoc`` circuit adds a permanent 10 mA minimum load
  to the ``VIN`` rail. This makes ``RailnFAULT_1V8_DSLOT`` a valid supply-status
  signal; without the load, the monitoring circuit behaves similarly to an
  empty slot. See :ref:`VIN minimum load and rail-fault monitoring <dslot_vin_rail_fault>`
  for the load requirement and :ref:`A-slot and D-slot VIN supervision <carrier_board_rev05_s3c_dslot_vin>`
  for the interaction between the D-slot CPLD and S3C.

Connector pinout
----------------

The connector pinout is identical for all three encoder channels.
The FPGA signals shown below apply to operation in digital slot D5.

Encoder 1
"""""""""

=====  ========  ==========  =====================
Pin    D-Sub 9   FPGA        Kubrich Encoder
=====  ========  ==========  =====================
0+     3         Dig_11_Ch5  blue
0-     4                     red
A+     8         Dig_12_Ch5  green
A-     7                     yellow
B+     5         Dig_13_Ch5  grey
B-     9                     pink
Vcc    2                     brown
GND    1                     white
=====  ========  ==========  =====================

Encoder 2
"""""""""

=====  ========  ==========  =====================
Pin    D-Sub 9   FPGA        Kubrich Encoder
=====  ========  ==========  =====================
0+     3         Dig_14_Ch5  blue
0-     4                     red
A+     8         Dig_15_Ch5  green
A-     7                     yellow
B+     5         Dig_16_Ch5  grey
B-     9                     pink
Vcc    2                     brown
GND    1                     white
=====  ========  ==========  =====================

Encoder 3
"""""""""

=====  ========  ==========  =====================
Pin    D-Sub 9   FPGA        Kubrich Encoder
=====  ========  ==========  =====================
0+     3         Dig_17_Ch5  blue
0-     4                     red
A+     8         Dig_18_Ch5  green
A-     7                     yellow
B+     5         Dig_19_Ch5  grey
B-     9                     pink
Vcc    2                     brown
GND    1                     white
=====  ========  ==========  =====================

Pin configuration
-----------------

==============  ==========  ===========
Package pin D5  Port        Signal
==============  ==========  ===========
J15             Dig_19_Ch5  Encoder_3_B
A13             Dig_18_Ch5  Encoder_3_A
K15             Dig_17_Ch5  Encoder_3_I
B13             Dig_16_Ch5  Encoder_2_B
G14             Dig_15_Ch5  Encoder_2_A
A14             Dig_14_Ch5  Encoder_2_I
G15             Dig_13_Ch5  Encoder_1_B
B14             Dig_12_Ch5  Encoder_1_A
E15             Dig_11_Ch5  Encoder_1_I
==============  ==========  ===========

FPGA configuration
------------------

To use all three encoder channels, the Vivado block design has to contain three incremental-encoder IP-core instances connected to the selected digital slot.
The CPLDs have to be programmed as described in :ref:`label_cpld_programming`.

Compatibility
-------------

* Digital slots D1 to D5 can be used without limitations; D5 is recommended.
* The Vivado block design has to be adapted when all three encoder channels are used.

See also
--------

* :download:`Schematic Rev04 <incr_encoder_rev04/SCH_UZ_D_Incr_Encoder_Default_04.pdf>`
* :ref:`Digital Incremental Encoder <dig_incEncoder>`
* :ref:`Digital IncrEncoder Rev03 <dig_incEncoderRev03>`
* :ref:`label_cpld_programming`
