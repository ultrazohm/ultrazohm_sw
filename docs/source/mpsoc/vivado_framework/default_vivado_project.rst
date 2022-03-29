.. _default_vivado_project:

Default Vivado project
======================

Includes the following IP-Cores.

General purpose:

- :ref:`AXI_testIP` to use in :ref:`how_to_create_ipcore_driver` and to test AXI communication
- Interrupt module (see :ref:`r5_interrupts`)
- 64-bit counter for :ref:`systemTimeR5`

Analog adapter card intended to be used with :ref:`Analog_LTC2311_16_v3` (A1, A2, and A3):

- :ref:`uz_dataMover` (PL to R5 by using the TCM)
- :ref:`ipCore_LTC2311_v3` (3 times)

For controlling a two-level inverter on D1:

- 2L PWM (:ref:`ipCore_pwm`)
- 2L interlock module(:ref:`uz_interlockDeadtime2L`)

For controlling a three-level inverter on D2:

- 3L PWM
- 3L interlock module

For usage with :ref:`dig_encoder_v1` on D5:

- :ref:`ipCore_incremental_encoder`