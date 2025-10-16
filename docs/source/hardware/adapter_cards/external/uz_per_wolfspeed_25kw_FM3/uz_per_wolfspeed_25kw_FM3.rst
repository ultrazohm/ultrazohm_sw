.. _uz_per_wolfspeed_25kw_FM3:

Wolfspeed Inverter 2L 25kW Interface
====================================

Source
******

- `PCB repository uz_per_wolfspeed_25kw_FM3 <https://bitbucket.org/ultrazohm/uz_per_wolfspeed_25kw_fm3/src/main/>`_

General Description
*******************

This PCB is designed to interface the UltraZohm with the Wolfspeed `CRD25DA12N-FMC 25 kW Three-Phase Inverter <https://www.wolfspeed.com/products/power/reference-designs/crd25da12n-fmc/>`_. 
It plugs directly into the Wolfspeed inverter in place of the Texas Instruments TMDSCNCD280039C control card.

Analog measurement signals are routed via an RJ45 connector to the UltraZohm ADC board using fully differential signaling. 
Digital control and status signals are transmitted over optical links using HFBR transmitters/receivers.

.. _Interface_board_function:

.. figure:: InterfaceBoardLayout.png

   Functional areas of the uz_per_wolfspeed inverter interface pcb

Layout
******

The PCB is structured by functional areas as shown in :ref:`Interface_board_function`.

1. HFBR-1521Z/2521Z Digital optical transmitters and receivers
2. RJ45 port for analog signal transmission 
3. Driver stages for the optical links
4. TI THS4561 fully differential amplifier stages for differential signaling
5. Power section: TPS7A20 (3.3V LDO), REF35 (2.5V and 1.7V references)
6. Samtec HSEC8 120-pin edge-card connector mating with the Wolfspeed inverter



Signal Description
******************

The interface board adapts all required signals between the Wolfspeed inverter and UltraZohm. 
Signals are grouped as analog and digital.


Analog Signals
--------------

The signals on the inverter side are single-ended and converted to fully differential signals for noise-robust transmission to the UltraZohm ADC board.
The adapter cards scales the single-ended signals by factor 1.5038 (10/6.65) to match the analog range of the Wolfspeed inverter (3.3V) to the 5V analog input range of the UltraZohm ADC board.
The reported total sensing gain is measured experimentally, see attached thesis for details. 
It includes the gain of the measurement device (e.g. current sensor) and the gain of the interface board.
The bandwidth is determined theoretically based on an LTSpice simulation and the resulting -3dB point.

.. list-table::
   :header-rows: 1
   :widths: 20 20 30 30

   * - Signal
     - Source
     - Total Measurement Gain
     - UltraZohm ADC Channel
   * - Phase Currents U, V, W
     - LEM LAH 50-P
     - total sensing gain 0.02417 in V/A, bandwidth ~50kHz
     - I_U (Ch1), I_V (Ch2), I_W (Ch3)
   * - DC-Link Voltage
     - voltage divider, non-isolated
     - total sensing gain in 0.003744 Vsec/Vprim, bandwidth ~7kHz
     - V_DC on Ch4 (RJ45 Pair 1-2)


Digital Signals
---------------


The overcurrent detection signal is active LOW, meaning that when an overcurrent condition is detected, the signal goes LOW and, therefore, the LED of the transmitter is OFF.
The overcurrent limits are by default set to +-79A and can be adjusted by varying the reference resistors, as detailed in the Wolfspeed documentation.

The NTC output is converted to a 50 kHz PWM signal with varying duty cycle. 


.. list-table::
   :header-rows: 1
   :widths: 25 20 20 35

   * - Signal
     - Direction
     - Conditioning
     - Notes
   * - 6x PWM Gate Signals 
     - UZ → Inverter
     - Optical Rx
     - High- and Low-Side for 3 phases, dead-time generated in UZ
   * - Gate Driver Disable
     - UZ → Inverter
     - Optical Rx
     - Global gate driver shutdown
   * - 6x Overcurrent Detection
     - Inverter → UZ
     - AND-gates (SN74HCS08DR) + Optical Tx
     - Consolidated into single fault signal (active-LOW)
   * - NTC Temperature
     - Inverter → UZ
     - Optical Tx
     - PWM modulated signal at 50kHz


Testing
*******

Tests were performed up to 10kW using an RL-load with a 14Ohm resistor and 1mH inductor


.. figure:: FinalSetup.png

   Integrated testing setup with RL-load

Stable three-phase sinusoidal currents measured using a Rohde & Schwarz MXO 5 series oscilloscope (2GHz, 8 channels)


.. figure:: Testgraph.png

   Oscilloscope measurements of the output phase voltage at a 100kHz switching frequency with a 999V/8.33A DC-link input


Notes for Future Revisions
**************************

A few considerations should be kept in mind for future iterations of the interface board:

- **Edge connector pinning**:  
  The HSEC8 120-pin edge card connector from Samtec uses a different numbering scheme
  than the TI control card. Care must be taken when mapping pins to avoid interface mismatches. 
  Details in `TI E2E Forum <https://e2e.ti.com/support/microcontrollers/arm-based-microcontrollers-group/arm-based-microcontrollers/f/arm-based-microcontrollers-forum/1486750/tmdshsecdock-edge-connector-hsec8-160-wrong-orientation-and-position-of-pin-1/>`_
  

- **Mechanical stability**:  
  A 3D-printed support stand was added in the current design to keep the board mechanically sturdy
  when plugged into the inverter. The step file of the stand can be found on the Bitbucket repository.

.. figure:: stand.jpg
   :width: 60%
   :align: center

   Interface board with 3D-printed stand for mechanical stability

- **Software Branch**
  We used the ``feature/wolfspeed_inverter_adapterboard`` branch of the `ultrazohm_sw <https://bitbucket.org/ultrazohm/ultrazohm_sw/src/>`_ repository to test the inverter. 
  View the branch diff directly `here <https://bitbucket.org/ultrazohm/ultrazohm_sw/branches/compare/feature%2Fwolfspeed_inverter_adapterboard%0Ddevelop#diff>`_.

Documents and Links
*******************

- Bachelor thesis :download:`download here <Thesis_Park_BA_UltraZohm_Wolfspeed_2L_Inverter_compressed.pdf>`
- Final presentation :download:`download here <FinalPresentation.pdf>`
- Schematic Rev03 :download:`download here <SCH_uz_per_wolfspeed_25kw_FM3_jlc_Rev03.pdf>`
- Poster KI-Power Symposium :download:`download here <Poster_UZandWolfspeedInterface.pptx>`
- Altium Files `git Repo uz_per_wolfspeed_25kw_FM3 <https://bitbucket.org/ultrazohm/uz_per_wolfspeed_25kw_fm3/src/main/>`_
- Wolfspeed 25 kW Three-Phase Inverter `CRD25DA12N-FMC <https://www.wolfspeed.com/products/power/reference-designs/crd25da12n-fmc/>`_. 
- TI E2E `Thread on HSEC8 pinout <https://e2e.ti.com/support/microcontrollers/arm-based-microcontrollers-group/arm-based-microcontrollers/f/arm-based-microcontrollers-forum/1486750/tmdshsecdock-edge-connector-hsec8-160-wrong-orientation-and-position-of-pin-1/>`_
