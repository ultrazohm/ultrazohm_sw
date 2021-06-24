.. _global_configuration:

====================
Global configuration
====================

The global configuration of the UltraZohm workspace regarding the R5 software is defined in the header file ``uz_global_configuration.h``.
Since the configuration of the system is sepcific for all users, this file does not exist in the repository and is not **not** tracked by git (listed in .gitignore).
To simplify the setup, a default configuration``default_uz_global_configuration.h`` is provided (tracked by git).

After cloning the repository, the user has to:

#. Create a copy of ``default_uz_global_configuration.h`` (``vitis/software/Baremetal/src/uz``)
#. Adjust the configuration to match your setup
#. Rename the copy to ``uz_global_configuration.h``
#. Software now can be compiled
#. Use the UltraZohm

Configuration
=============

The configuration is used for:

- :ref:`static_memory_allocation`
-  Set the hardware version specific settings (e.g., ``UZ_HARDWARE_VERSION`` for different front panels).
- Configure the interrupt source (:ref:`r5_interrupts`)

To change the default global configuration, make the changes to the local ``uz_global_configuration.h``, and make sure that all :ref:`unit_tests` work locally.
Then, copy the content of ``uz_global_configuration.h`` to ``default_uz_global_configuration.h`` and commit the change.

.. _default_vivado_project:

Default Vivado project
======================

Includes the following IP-Cores.

General purpose:

- :ref:`AXI_testIP` to use in :ref:`how_to_create_ipcore_driver` and to test AXI communication
- Interrupt module (see :ref:`r5_interrupts`)
- 64-bit counter for :ref:`systemTimeR5`

Analog adapter card intended to be used with :ref:`Analog_LTC2311_16_v2` (A1) and :ref:`Analog_LTC2311_16_v3` (A2 and A3):

- DataMover (PL to R5 by using the TCM)
- :ref:`ipCore_LTC23` (3 times)

For controlling a two-level inverter on D1:

- 2L PWM (:ref:`ipCore_pwm`)
- 2L interlock module(:ref:`uz_interlockDeadtime2L`)

For controlling a three-level inverter on D2:

- 3L PWM
- 3L interlock module

For usage with :ref:`dig_encoder_v1` on D5:

- :ref:`ipCore_incremental_encoder`
