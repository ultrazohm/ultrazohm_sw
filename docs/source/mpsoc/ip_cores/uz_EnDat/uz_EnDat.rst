.. _ipCore_EnDat:

=======
EnDat22
=======

The EnDat22 IP-Core (``EnDat``) evaluates signals of an EnDat22 based absolute singleturn encoders and is compatible to :ref:`dig_encoder_v1`.
It features the positional and speed calculation. 

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


IP-Core Hardware
================

The IP-Core is generated using Matlab/Simulink HDL-Coder based on the model ``UZ_EnDat.slx`` (in ``ultrazohm_sw/ip_cores/uz_EnDat_IPCore/Simulink_Model/UZ_EnDat.slx``).


Vivado integration
------------------

.. figure:: uz_EnDat_vivado.png
  :align: center

  Vivado block design of EnDat22 IP-Core.

.. warning:: The IP-Core (IPCORE_CLK) has to be sourced by a clock with :math:`100 MHz`! The auxialliary clock (CLK50MHZ) has to be fed with a :math:`50 MHz` Signal


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
  Default is :math:`\frac{f_{IP-Core}}{IncPerTurn} \cdot \frac{1}{2\pi}=1.5915e-05` with :math:`f_{IP-Core}=50 MHz` and :math:`IncPerTurn=5000`.

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


Table *Interfaces of the EnDat22 IP-Core* lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. csv-table:: Interfaces of the EnDat22 IP-Core
   :file: uz_EnDat_register_mapping.csv
   :widths: 50 50 50 50 200
   :header-rows: 1


Software driver
===============

The software driver for the IP-Core has multiple use cases - with the configuration and calculation beeing the most important ones. 

Init Functions
----------------
.. doxygentypedef:: uz_EnDat_t
.. doxygentypedef:: controlword
.. c:type:: uint8_t

.. doxygenfunction:: uz_EnDat_IP_core_init

This function initializes a 25-Bit EnDat22 sensor with default settings. The IP-Core has to be named "uz_EnDat_0" in Vivado and have an operating frequency of 100 MHz.
Use this function to initialize the sensortype ECN125 without further adjustment necessary. Generally this method is not advised to be used due to its inflexibility.

.. doxygenfunction:: uz_EnDat_IP_core_custom_init

This function initializes a EnDat22 sensor using settings and supporting various sensor resolutions. The IP-Core has to be named "uz_Endat_0" in Vivado and have an operating frequency of 100 MHz.
For adjusting the configuration of the EnDat22 sensor, please edit the file ``uz_EnDat_IP_core_init.c``. Changes during runtime are prohibited.

.. doxygenfunction:: uz_EnDat_IP_core_expert_init

This function is the most flexible one when it comes to configuration of the IP-Core since every parameter is handed over by the call function. 
Diese Funktion lasst dem Anwender maximale Flexibilit ¨ at. Sowohl der Name des IP-Cores ¨
in Vivado, die Betriebsfrequenz als auch die multiple Initialisierung sind hiermit moglich. ¨
Es wird jedoch ausdrucklich davon abgeraten, eine von 100 MHz abweichende Betriebs- ¨
frequenz zu verwenden. Bei dieser Initialisierung muss die Basisadresse des IP-Cores auf
dem AXI4-Bus bekannt sein. Ferner ist jede einzelne Einstellung manuell zwingend vorzu￾nehmen. Zur Initialisierung muss diese Funktion mit allen fur den Betrieb notwendigen ¨
Parametern aufgerufen werden, es werden hierbei keine Standardeinstellungen an den
IP-Core ubergeben. 


  


