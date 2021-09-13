.. _ipCore_incremental_encoder:

===================
Incremental Encoder
===================

The incremental encoder IP-Core (``IncreEncoder_V24``) evaluates signals of an incremental encoder and is compatible to :ref:`dig_encoder_v1`.
It features multiple possibilities to calculate the rotor position and the rotational speed of the encoder.

Position
  Calculates the rotational position of the encoder based on counting rising and falling edges on the A and B-lane of the encoder.
  Resets to zero based on the I-lane.

Position (electrical)
  Calculates the rotational position of the encoder and transforms the position to the *electrical* position of electric drives (e.g., permanent magnet synchronous machines).
  Uses the number of pole pairs to divide one mechanical turn of the encoder to (multiple) turns of the electrical system.
  *Can only be used if the number of pole paris is an integer multiple of the number of increments!*

Rotational speed
  Calculates the rotational speed of the drive by counting rising edges of the A-lane in combination with a oversampling mechanism and subsequent filtering of the speed signal in the IP-Core.

Direction of rotation
  Determines the direction of the rotation (clockwise / counterclockwise)

Configuration
=============

Hardware
--------

PI2_Inc_AXI
  Scales the output theta_el to :math:`0..2\pi`.
  Is calculated in the processor and written to the IP-Core.
  Calculation: :math:`\frac{2 \cdot \pi}{IncPerTurn \cdot QudratureFactor} \cdot PolePair` with ``PolePair`` being the pole paris of the drive. 

Timer_FPGA_ms
  Scales the timer, that is used to calculate the rotational speed, from FPGA clock ticks to seconds w.r.t. the number of increments and :math:`2\pi`.
  Default is :math:`\frac{1}{f_{IP-Core} \cdot IncPerTurn} \cdot \frac{1}{2\pi}=1.5915e-05` with :math:`f_{IP-Core}=50 MHz`.

IncPerTurn_mech
  Configures the number of lines per mechanical revolution.

IncPerTurn_elek
  Configures the number of lines per electrical revolution, i.e., w.r.t. to the pole pairs of a electrical machine.
  Set to ``IncPerTurn_mech`` divided by pole pairs of the electrical machine.

OverSamplingFactor
  Calculation of the rotational speed omega is based on measuring the time between rising edges of the A-lane.
  If ``OverSampleFactor=1``, every rising edge is used.
  For ``OverSampleFactor=n``, every n-th rising ege is used.
  Based on the setting, the IP-Core adapts the OverSampleFactor over the operating range of the drive.
  The ``OverSamplingFactor`` is set by ``OmegaPerOverSampl_AXI4`` in ``rad/s``.
  Default value is :math:`500 \frac{1}{min} \cdot \frac{2\pi}{60 s}=52.3599 s^{-1}`.

PeriodEnd
  Used to reset the counter that is used to calculate the rotational speed which is output at ``countPerPeriod_AXI``.
  Not recommended, use calculation based on time measurement based on counting edges of the A-lane instead (``omega_AXI``).

Software
--------

QuadratureFactor
  Specifies the number of edges based on the number of increments per turn. For regular incremental encoders with A and B-lane, this factor is four (4).



Vivado
======

.. warning:: The IP-Core (IPCORE_CLK) has to be sourced by a clock with :math:`50 MHz`! For higher frequencies the timing does not close (negative slack time), for lower frequencies the accuracy of the encoder result is not tested.

.. figure:: increEncoder_vivado.png

  Vivado block design of incremental encoder IP-Core.


.. csv-table:: Interfaces of the incremental encoder IP-Core
   :file: incrementalEncoder_register_mapping.csv
   :widths: 50 50 50 50 200
   :header-rows: 1