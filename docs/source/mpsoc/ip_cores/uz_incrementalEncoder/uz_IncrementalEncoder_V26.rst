.. _ipCore_incremental_encoder_V26:

=======================
Incremental Encoder V26
=======================

The incremental encoder IP-Core (``IncreEncoder_V26``) evaluates signals of an incremental encoder and is compatible to :ref:`dig_encoder_v1`.
It features multiple possibilities to calculate the rotor position and the rotational speed of the encoder.

Position
  Calculates the rotational position of the encoder based on counting rising and falling edges on the A and B-lane of the encoder.
  Resets to zero based on the I-lane (once per mechanical revolution).

Position (electrical)
  Calculates the rotational position of the encoder and transforms the position to the *electrical* position of electric drive (e.g., permanent magnet synchronous machines).
  Uses the number of pole pairs to divide one mechanical turn of the encoder to (multiple) turns of the electrical system.
  Can only be used if the number of increments is an integer multiple of the number of pole pairs!
  The value of ``drive_pole_pair`` in the driver configuration has to be an integer multiple of the increments per turn or set to zero.
  If ``drive_pole_pair`` is an integer multiple of increments per turn, the electrical angle can be used and read by calling ``uz_incrementalEncoder_get_theta_el``.
  If ``drive_pole_pair`` is set to ``0``, the function can not be called (assertion fires if it is called).
  If ``drive_pole_pair`` is not ``0`` and not an integer multiple of increments per turn, the initialization of the driver fails with an assertion.
  Note that the FPGA output port of the IP-Core outputs the (potentially false!) electrical position regardless of this setting!

Rotational speed
  Calculates the rotational speed of the drive by counting the time between two consecutive rising edges of the A-lane in combination with an speed-dependent oversampling mechanism and subsequent filtering of the speed signal in the IP-Core.
  The oversampling mechanism allows to skip edges to improve the measurement at higher speeds.

Direction of rotation
  Determines the direction of the rotation (clockwise / counterclockwise)

Configuration
=============



Hardware filter of rotational speed
===================================



IP-Core Hardware
================


Vivado integration
------------------




Configuration registers (AXI)
-----------------------------




Software driver
===============


Driver reference
----------------
