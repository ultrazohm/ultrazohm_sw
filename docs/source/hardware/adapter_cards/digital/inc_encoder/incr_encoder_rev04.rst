.. _dig_incEncoderRev04:

=========================
Digital IncrEncoder Rev04
=========================

The Digital IncrEncoder Rev04 adapter card connects up to three incremental encoders to the FPGA.
It is based on :ref:`Digital IncrEncoder Rev03 <dig_incEncoderRev03>` and introduces the changes listed below.

Functionality
-------------

* Connects three incremental encoders to the FPGA
* Provides an isolated 5 V supply to the encoders
* Reads the differential encoder signals

Changes from Rev03
------------------

* The LED issue present in Rev03 has been fixed.
* An EEPROM has been added.
* The ``Power_Load_LEDs10mA.SchDoc`` circuit has been added to provide a minimum load on the ``VIN`` rail.
  This load allows the carrier board's rail monitoring to operate as intended, making the active-low ``RailnFAULT_1V8_DSLOT`` signal usable by the D-slot CPLD.

VIN minimum load and rail-fault signal
--------------------------------------

The ``Power_Load_LEDs10mA.SchDoc`` schematic block provides a permanent minimum load on the ``VIN`` rail by means of the 10 mA LED load.
The load enables reliable operation of the rail-monitoring circuit on the carrier board even when the encoder card itself otherwise draws only a small current from that rail.

The encoder card neither generates nor directly uses the active-low ``RailnFAULT_1V8_DSLOT`` signal.
Instead, the additional load on the card allows the carrier board to generate a valid rail-fault indication, which is already routed to the D-slot CPLD as ``RailnFAULT_1V8_DSLOT``.
The card-specific CPLD firmware can evaluate this signal, for example to inhibit signal forwarding or to include a detected supply fault in the slot status reported to the carrier board.
Its exact effect depends on the CPLD implementation programmed for the selected D-slot.

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
