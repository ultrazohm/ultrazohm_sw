.. _ipCore_incremental_encoder:

===================
Incremental Encoder
===================

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

The IP-Core is generated using Matlab/Simulink HDL-Coder based on the model ``inc_enc_v26.slx`` (in ``ultrazohm_sw/ip-cores/IncreEncoder_V26_ip/Simulation/``).

Vivado integration
------------------

.. figure:: increEncoder_vivado.png

  Vivado block design of incremental encoder IP-Core.

.. warning:: The IP-Core (IPCORE_CLK) has to be sourced by a clock with :math:`100 MHz`! For lower frequencies the accuracy of the encoder result is not tested.



Configuration registers (AXI)
-----------------------------

The following configuration registers are available for the IP-Core.
The software driver writes to the registers based on the configuration that is provided to the initialization function.


PI2_Inc_AXI
  Scales the output theta_el to :math:`0..2\pi`.
  Is calculated in the processor and written to the IP-Core.
  Calculation: :math:`\frac{2 \cdot \pi}{IncPerTurn \cdot QudratureFactor} \cdot PolePair` with ``PolePair`` being the pole pairs of the drive. 

Timer_FPGA_ms
  Scales the timer, that is used to calculate the rotational speed, from FPGA clock ticks to seconds w.r.t. the number of increments and :math:`2\pi`.
  Default is :math:`\frac{IncPerTurn}{f_{IP-Core}} \cdot \frac{1}{2\pi}=7.958e-06` with :math:`f_{IP-Core}=100 MHz` and :math:`IncPerTurn=5000`.

IncPerTurn_mech
  Configures the number of lines per mechanical revolution.

IncPerTurn_elec
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
  Used to reset the counter that is used to calculate the rotational speed, which is output at ``countPerPeriod_AXI``.
  Not recommended, use calculation based on time measurement based on counting edges of the A-lane instead (``omega_AXI``).

TimeoutValue
  Used to set the timeout value in milliseconds for the ``omega_out`` port. If a timeout occurs, the ``omega_out`` port will be set to zero after the configured value has passed.

PositionOffset
  Sets the mechanical offset for the :math:`\theta_{mech}`. :math:`\theta_{mech}` can only be used in the PL.

ElectricalOffset
  Sets the electrical offset for the :math:`\theta_{el}`. This changes the :math:`\theta_{el}` in software and the PL.

CountingDirection
  Sets the counting direction of the angle and rotation. Can be configured via an enum. Default is clock_wise.


Table *Interfaces of the incremental encoder IP-Core* lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. csv-table:: Interfaces of the incremental encoder IP-Core
   :file: incrementalEncoder_register_mapping.csv
   :widths: 50 50 50 50 200
   :header-rows: 1

Software driver
===============

The software driver for the IP-Core handles the configuration of the aforementioned registers.

.. code-block:: c
  :caption: Initialization of an encoder

  struct uz_incrementalEncoder_config encoder_D5_config={
		.base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_0_BASEADDR,
		.ip_core_frequency_Hz=100000000U,
		.line_number_per_turn_mech=5000U,
		.OmegaPerOverSample_in_rpm=500.0f,
		.drive_pole_pair=4U,
		.Encoder_elec_Offset = 0U,
		.counting_direction = clock_wise,
		.Speed_Timeout_ms = 10U //10ms
  };
  uz_incrementalEncoder_t* test_instance=uz_incrementalEncoder_init(testconfig);

.. code-block:: c
  :caption: Read position and speed

  float omega=uz_incrementalEncoder_get_omega_mech(test_instance);
  float theta_el=uz_incrementalEncoder_get_theta_el(test_instance);
  uint32_t position=uz_incrementalEncoder_get_position(test_instance);


Driver reference
----------------

.. doxygentypedef:: uz_incrementalEncoder_t

.. doxygenenum:: uz_incrementalEncoder_counting_direction

.. doxygenstruct:: uz_incrementalEncoder_config
  :members:

.. doxygenfunction:: uz_incrementalEncoder_init

.. doxygenfunction:: uz_incrementalEncoder_get_omega_mech

.. doxygenfunction:: uz_incrementalEncoder_get_theta_el

.. doxygenfunction:: uz_incrementalEncoder_get_position
