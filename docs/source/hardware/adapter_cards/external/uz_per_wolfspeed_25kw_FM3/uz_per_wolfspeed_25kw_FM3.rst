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

   Functional areas of the uz per wolfspeed inverter interface pcb

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
**************

.. list-table::
   :header-rows: 1
   :widths: 25 20 35 20

   * - Signal
     - Source
     - Conditioning
     - Destination
   * - Phase Current U, V, W
     - Inverter Hall sensor → single-ended
     - fully diff. OpAmp, gain 1.5, total sensing gain in ?? V/A, bandwidth?
     - UltraZohm ADC Channels 1,2,3 ??
   * - DC-Link Voltage
     - Inverter voltage divider + buffer
     - fully diff. OpAmp, gain 1.5, total sensing gain in ?? Vsec/Vprim, bandwidth?
     - UltraZohm ADC Channel ??


Digital Signals
***************

.. list-table::
   :header-rows: 1
   :widths: 30 15 25 30

   * - Signal
     - Direction
     - Conditioning
     - Notes
   * - 6x PWM Gate Signals 
     - UltraZohm → Inverter
     - Optical Tx/Rx (HFBR-1521Z/2521Z)
     - High- and Low-Side for 3 phases, dead-time generated in UZ
   * - Gate Driver Disable
     - UltraZohm → Inverter
     - Optical Tx/Rx
     - Global gate driver shutdown
   * - 6x Overcurrent Detection
     - Inverter → UltraZohm
     - AND-gates (SN74HCS08DR) → Optical Tx
     - Consolidated into single fault signal (active Level ??) light on -> fault or no fault?
   * - NTC Temperature
     - Inverter → UltraZohm
     - Optical Tx
     - Thermal feedback


Testing
*******

Tests were performed up to 10kW using an RL-load with a 14Ohm braking resistor and 1mH inductor


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
  We used the ``feature/wolfspeed_inverter_adapterboard`` branch of the `ultrazohm_sw <https://bitbucket.org/ultrazohm/ultrazohm_sw/src/>`_ repository to test the inverter. View the branch directly `here <https://bitbucket.org/ultrazohm/ultrazohm_sw/src/feature/wolfspeed_inverter_adapterboard/>`_.

Documents and Links
*******************

- Bachelor thesis :download:`download here <Thesis_Park_BA_UltraZohm_Wolfspeed_2L_Inverter_compressed.pdf>`
- Final presentation :download:`download here <FinalPresentation.pdf>`
- Schematic Rev03 :download:`download here <SCH_uz_per_wolfspeed_25kw_FM3_jlc_Rev03.pdf>`
- Poster KI-Power Symposium :download:`download here <Poster_UZandWolfspeedInterface.pptx>`
- Altium Files `git Repo uz_per_wolfspeed_25kw_FM3 <https://bitbucket.org/ultrazohm/uz_per_wolfspeed_25kw_fm3/src/main/>`_
- Wolfspeed 25 kW Three-Phase Inverter `CRD25DA12N-FMC <https://www.wolfspeed.com/products/power/reference-designs/crd25da12n-fmc/>`_. 
- TI E2E `Thread on HSEC8 pinout <https://e2e.ti.com/support/microcontrollers/arm-based-microcontrollers-group/arm-based-microcontrollers/f/arm-based-microcontrollers-forum/1486750/tmdshsecdock-edge-connector-hsec8-160-wrong-orientation-and-position-of-pin-1/>`_
