.. _global_configuration:

====================
Global configuration
====================

The global configuration of the UltraZohm workspace regarding the R5 software is defined in the header file ``uz_global_configuration.h``.
The configuration of the system is specific for all users and must be adjusted to the specific setup.

After cloning the repository, the user has to:

#. Navigate to``uz_global_configuration.h`` in ``vitis/software/Baremetal/src/uz``
#. Adjust the configuration to match your setup
#. Compile the software
#. Use the UltraZohm

Configuration
=============

The configuration is used for:

- :ref:`static_memory_allocation`
-  Set the hardware version specific settings (e.g., ``UZ_HARDWARE_VERSION`` for different front panels).
- Configure the interrupt source (:ref:`r5_interrupts`)
- Configure the use of an external stop button, depending on the hardware revision (:ref:`external_stop`)
