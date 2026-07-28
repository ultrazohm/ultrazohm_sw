.. _uz_per_wolfspeed_25kw_FM3_rev04:

===========================================
Wolfspeed Inverter 2L 25 kW Interface Rev04
===========================================

Rev04 is the second productive revision of the ``uz_per_wolfspeed_25kw_FM3`` interface PCB.
Rev04 keeps the analog measurement concept of Rev03 and adds several digital functions for commissioning and inverter operation.

.. figure:: rev04_pcb_overview_numbered.png
   :width: 60%

   Functional areas of the Rev04 interface PCB.

The PCB is structured by functional areas as shown in :ref:`uz_per_wolfspeed_rev03_function` with:

1. HFBR-1521Z/2521Z digital optical transmitters and receivers
2. RJ45 port for analog signal transmission
3. Driver stages for the optical links
4. TI THS4561 fully differential amplifier stages
5. Power supply with TPS7A20 3.3 V LDO and REF35 voltage references
6. Samtec HSEC8 120-pin edge-card connector mating with the Wolfspeed inverter
7. Window comparators, AND gates, and flip-flop for overcurrent detection and latch
8. LTC6992 analog NTC temperature to PWM conversion 

Changes Compared to Rev03
=========================

* Added ``GateAndFanControl.SchDoc``: ``Gate_Driver_Enable`` is converted to the inverter ``GD_DIS`` polarity and also drives the fan-control output.
* Added ``OvercurrentDetectionLogic.SchDoc``: the six overcurrent comparator outputs are combined, latched, reset by gate enable, and routed to the optical ``OC`` output.
* Added ``TempSenseConditioning.SchDoc``: the analog isolated NTC signal is converted to a PWM signal before the optical transmitter.
* Added fan outputs ``FAN1_OUT`` and ``FAN2_OUT`` on the inverter connector.
* Added a red overcurrent latch indicator LED.
* Added a 2x3 jumper header in the overcurrent section for testing overcurrent events.

Analog Signals
==============

Rev04 keeps the Rev03 analog measurement structure.
The inverter-side phase-current and DC-link voltage measurements are converted from single-ended signals to fully differential signals for the UltraZohm ADC board.

.. list-table::
   :header-rows: 1
   :widths: 25 25 30 20

   * - Signal
     - Source
     - Total measurement gain
     - UltraZohm ADC channel
   * - Phase current U
     - LEM LAH 50-P
     - 0.03993 V/A, bandwidth about 50 kHz
     - ``I_U`` / Ch1
   * - Phase current V
     - LEM LAH 50-P
     - 0.03993 V/A, bandwidth about 50 kHz
     - ``I_V`` / Ch2
   * - Phase current W
     - LEM LAH 50-P
     - 0.03993 V/A, bandwidth about 50 kHz
     - ``I_W`` / Ch3
   * - DC-link voltage
     - Non-isolated voltage divider
     - 0.003744 Vsec/Vprim, bandwidth about 7 kHz
     - ``V_DC`` / Ch4

Digital Signals
===============

.. list-table::
   :header-rows: 1
   :widths: 30 20 25 25

   * - Signal
     - Direction
     - Conditioning
     - Notes
   * - ``U_HS_PWM``, ``U_LS_PWM``, ``V_HS_PWM``, ``V_LS_PWM``, ``W_HS_PWM``, ``W_LS_PWM``
     - UltraZohm to inverter
     - Optical receivers
     - High-side and low-side PWM for three phases; dead time is generated in the UltraZohm.
   * - ``Gate_Driver_Enable`` (GD_DIS label on PCB port!)
     - UltraZohm to interface
     - Optical receiver, then inverter logic
     - High enables the gate drivers and arms overcurrent protection.
   * - ``FAN1_OUT``, ``FAN2_OUT``
     - Interface to inverter
     - Derived from ``Gate_Driver_Enable``
     - Fans are on when ``Gate_Driver_Enable`` is high and off when it is low.
   * - ``OC``
     - Interface to UltraZohm
     - SN74HCS08DR logic, SN74LVC1G74 latch, optical transmitter
     - Combined and latched overcurrent feedback. The latch clears when ``Gate_Driver_Enable`` is low.
   * - ``Temp_PWM``
     - Interface to UltraZohm
     - LTC6992CS6-2 PWM generator and optical transmitter
     - PWM representation of the isolated NTC voltage.

.. warning::
   The printed label on the PCB called ``GD_DIS`` for the optical receiver is wrong. 
   Actually this is ``Gate_Driver_Enable``, a high-active enable signal.


Gate Enable and Fan Control
===========================

Rev04 separates the UltraZohm-side gate-enable command from the inverter-side disable polarity.
The schematic states the following behavior:

.. list-table::
   :header-rows: 1
   :widths: 30 30 40

   * - ``Gate_Driver_Enable``
     - Resulting output
     - Function
   * - High
     - ``GD_DIS`` low, ``FANx_OUT`` high
     - Gate drivers enabled, fans on, overcurrent protection armed.
   * - Low
     - ``GD_DIS`` high, ``FANx_OUT`` low
     - Gate drivers disabled, fans off, overcurrent latch cleared.

Overcurrent Detection
=====================

The Rev04 overcurrent (OC) detection uses TLV3502 comparators for the three phase-leg overcurrent signals:
``U_HI_OC``, ``U_LO_OC``, ``V_HI_OC``, ``V_LO_OC``, ``W_HI_OC`` and ``W_LO_OC``.
The comparator outputs are combined with SN74HCS08DR logic.
The result is latched with an SN74LVC1G74 flip-flop and routed to the ``OC`` optical transmitter.
When the gates are enabled, protection is armed.
When the gates are disabled, the latch is cleared.

The optical ``OC`` signal is high when an overcurrent event has been detected, which latches the signal.
The inverter gates are disabled until the ``OC`` latch is reset via a low signal on ``Gate_Driver_Enable``.
Disabling the gate signals is independents of an active ``Gate_Driver_Enable`` signal.
The OC trips at ``+/-49 A``.

.. note::
   Rev04 includes a 2x3 jumper header in the overcurrent section for testing overcurrent events.
   For normal operation, i.e., an active overcurrent detection, place the jumpers as stated in the explanatory figure, connecting left and right pins of each row.

.. figure:: rev04_oc_test_jumpers.png
   :width: 60%

   Jumper setup for overcurrent comparators.

Inverter Temperature Measurement
================================

Rev04 converts the isolated NTC voltage to an optical PWM signal.
The ``NTC_ISO`` from the inverter PCB is expected to be in the range of ``0 V`` to ``2 V`` and a voltage divider on the Rev04 PCB reduces this to ``0 V`` to ``1 V`` for matching the input range of the PWM generator (LTC6992CS6-2).

The LTC6992CS6-2 is configured with:

* ``R_SET = 68 kOhm``, resulting in approximately ``46 kHz`` PWM frequency.
* ``DIVCODE = 2`` / ``N_DIV = 16`` from the ``182 kOhm`` and ``976 kOhm`` divider.
* ``POL = 1`` so rising NTC temperature results in increasing duty cycle.

Temperature from PWM Duty Cycle
===============================

.. warning::
   The following approximation is calculated from assumptions based on the inverter schematics. 
   The duty cycle to temperature function has not been validated on real hardware.

The module temperature is approximated from the measured PWM duty cycle using the following linear relationship:

.. math::

   T(D) = 1.55 \cdot D + 13.639

where:

* :math:`D` is the PWM duty cycle in percent.
* :math:`T` is the estimated temperature in degrees Celsius.

For example, a duty cycle of ``25 %`` gives:

.. math::

   T(25) = 1.55 \cdot 25 + 13.639 = 52.389\ ^\circ\mathrm{C}


Temperature-over-Duty-Cycle Graph
---------------------------------

.. plot::
   :caption: Estimated module temperature as a function of PWM duty cycle.
   :align: center
   :include-source: false

   import matplotlib.pyplot as plt
   import numpy as np

   # Duty-cycle points derived from the NTC model.
   duty_points = np.array([
       5.7,
       8.8,
       15.7,
       23.4,
       31.5,
       43.6,
       60.8,
       72.9,
       80.7,
   ])

   # Temperatures calculated using the linear regression.
   temperature_points = 1.55 * duty_points + 13.639

   # Continuous regression line.
   duty = np.linspace(5.0, 95.0, 500)
   temperature = 1.55 * duty + 13.639

   plt.figure(figsize=(8, 5))

   plt.plot(
       duty,
       temperature,
       label=r"$T = 1.55D + 13.639$",
   )

   plt.scatter(
       duty_points,
       temperature_points,
       label="Calculated data points",
       zorder=3,
   )

   for duty_value, temperature_value in zip(
       duty_points,
       temperature_points,
   ):
       plt.annotate(
           f"{temperature_value:.1f} °C",
           (duty_value, temperature_value),
           xytext=(5, 5),
           textcoords="offset points",
           fontsize=8,
       )

   plt.xlabel("PWM duty cycle (%)")
   plt.ylabel("Estimated temperature (°C)")
   plt.title("Estimated Temperature from PWM Duty Cycle")
   plt.xlim(0, 100)
   plt.grid(True)
   plt.legend()
   plt.tight_layout()


Reference Data
--------------

The following table contains the previously estimated NTC-model data and
the corresponding result from the linear regression.

.. list-table:: Duty-cycle and temperature reference values
   :header-rows: 1
   :widths: 25 35 40
   :align: center

   * - Duty cycle
     - NTC-model estimate
     - Linear-regression result
   * - 5.7 %
     - 25.0 °C
     - 22.5 °C
   * - 8.8 %
     - 30.1 °C
     - 27.3 °C
   * - 15.7 %
     - 40.0 °C
     - 38.0 °C
   * - 23.4 %
     - 50.0 °C
     - 49.9 °C
   * - 31.5 %
     - 60.0 °C
     - 62.5 °C
   * - 43.6 %
     - 75.0 °C
     - 81.2 °C
   * - 60.8 %
     - 100.0 °C
     - 107.9 °C
   * - 72.9 %
     - 124.9 °C
     - 126.6 °C
   * - 80.7 %
     - 149.9 °C
     - 138.7 °C

Commissioning Notes
===================

Before first operation:

* Mount the interface PCB with the two mentioned 3d-printed clamps tightly to the inverter. The .STL parts are available in the `PCB-repository <https://bitbucket.org/ultrazohm/uz_per_wolfspeed_25kw_fm3/src/main/Altium/step/stl/>`_.
* Check fan behavior before applying high DC-link voltage.
* Verify the temperature PWM duty-cycle interpretation in the software or FPGA logic.
* Check the overcurrent test jumper setting. Three jumpers need to be placed in order to set the OC detection active.

.. figure:: rev04_opt_connections.png
   :width: 90%

   Commissioning of the interface PCB with optical signal connections, mechanical mounting, and active OC circuitry

Known issues
============

* The printed label on the PCB called ``GD_DIS`` for the optical receiver is wrong. Actually this is ``Gate_Driver_Enable``, a high-active enable signal.

Documents
=========

* :download:`Schematic Rev04 <../SCH_uz_per_wolfspeed_25kw_FM3_jlc_Rev04.pdf>`
* `PCB repository uz_per_wolfspeed_25kw_FM3 <https://bitbucket.org/ultrazohm/uz_per_wolfspeed_25kw_fm3/src/main/>`_
