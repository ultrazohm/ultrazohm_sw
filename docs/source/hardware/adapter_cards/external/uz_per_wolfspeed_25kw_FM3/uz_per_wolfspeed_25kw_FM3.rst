.. _uz_per_wolfspeed_25kw_FM3:

uz_per_wolfspeed_25kw_FM3
===============================

Source
******

- `uz_per_wolfspeed_25kw_FM3 PCB repository <https://bitbucket.org/ultrazohm/uz_per_wolfspeed_25kw_fm3/src/main/>`_

General Description
*******************

This PCB is designed to interface the UltraZohm with the Wolfspeed `CRD25DA12N-FMC 25 kW Three-Phase Inverter <https://www.wolfspeed.com/products/power/reference-designs/crd25da12n-fmc/>`_. The PCB can be directly plugged into the Wolfspeed inverter in place of the Texas Instruments TMDSCNCD280039C control card and a RJ45 Ethernet connector is used to transfer analog, and digital optical transmitters/receivers used to transfer digital signals to and from UltraZohm.

.. _Interface_board_function:

.. figure:: InterfaceBoardLayout.png

   Functional areas of the uz per wolfspeed inverter interface pcb

Layout
******

The PCB is structured by functional areas as shown in :ref:`Interface_board_function`.

1. HFBR-1521Z/2521Z Digital optical transmitters and receivers
2. RJ45 ethernet port for analog signal transmission 
3. Digital signal circuitry 
4. TI THS4561 fully differential op-amp circuitry for differential signalling  
5. Power section - 3.3V output TI TPS7A20 LDO, 2.5V and 1.7V output TI REF35 voltage references 
6. Samtec HSEC8 120-pin edge card connector that plugs into the Wolfspeed inverter


Signal Description
******************

The interface board adapts all required signals between the Wolfspeed inverter and UltraZohm. These signals can be divided into two groups:


Analog Signals
**************

.. list-table::
   :header-rows: 1
   :widths: 25 20 35 20

   * - Signal
     - Source
     - Conditioning
     - Destination
   * - Phase Current U
     - Inverter Hall sensor → single-ended
     - THS4561 differential amplifier, gain 1.5
     - UltraZohm ADC (RJ45)
   * - Phase Current V
     - Inverter Hall sensor → single-ended
     - THS4561 differential amplifier, gain 1.5
     - UltraZohm ADC (RJ45)
   * - Phase Current W
     - Inverter Hall sensor → single-ended
     - THS4561 differential amplifier, gain 1.5
     - UltraZohm ADC (RJ45)
   * - DC-Link Voltage
     - Inverter voltage divider + buffer
     - THS4561 differential amplifier, gain 1.5
     - UltraZohm ADC (RJ45)


Digital Signals
***************

.. list-table::
   :header-rows: 1
   :widths: 30 15 25 30

   * - Signal
     - Direction
     - Conditioning
     - Notes
   * - 6× PWM Gate Signals (HS/LS per phase)
     - UltraZohm → Inverter
     - Optical Tx/Rx (HFBR-1521Z/2521Z)
     - Complementary, dead-time handled by UltraZohm
   * - Gate Driver Disable
     - UltraZohm → Inverter
     - Optical Tx/Rx
     - Global gate driver shutdown
   * - 6× Overcurrent Detection
     - Inverter → UltraZohm
     - AND-gates (SN74HCS08DR) → Optical Tx
     - Consolidated into single fault signal
   * - NTC Temperature
     - Inverter → UltraZohm
     - Optical Tx
     - Thermal feedback


Testing
*******

Tests were performed up to 10kW using an RL-load with a 14 Ohm braking resistor and 1mH inductor

.. _FinalSetup:

.. figure:: FinalSetup.png

   Integrated testing setup with RL-load

Stable three-phase sinusoidal currents measured using a Rohde &Schwarz MXO5series 100MHz 8-channel oscilloscope

.. _Testgraph:

.. figure:: Testgraph.png

   Oscilloscope measurements of the output phase voltage at a 100kHz switching frequency with a 999V/8.33A DC-link input


Notes for Future Revisions
**************************

A few considerations should be kept in mind for future iterations of the interface board:

- **Edge connector pinning**:  
  The HSEC8/HSEC9 120-pin edge card connector from Samtec uses a different numbering scheme
  than the TI control card. Care must be taken when mapping pins to avoid interface mismatches.

- **Mechanical stability**:  
  A 3D-printed support stand was added in the current design to keep the board mechanically sturdy
  when plugged into the inverter. The step file of the stand can be found on the Bitbucket repository.

.. _stand:

.. figure:: stand.jpg
   :width: 60%
   :align: center

   Interface board with 3D-printed stand for mechanical stability



Documents
*********

You can :download:`download the Bachelor thesis here <BachelorThesis_SP.pdf>`

For quick reference, view :download:`the final presentation <FinalPresentation.pdf>`

