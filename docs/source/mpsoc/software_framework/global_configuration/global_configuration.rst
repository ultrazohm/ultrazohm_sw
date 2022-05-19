.. _global_configuration:

====================
Global configuration
====================

The global configuration of the UltraZohm workspace regarding the R5 software is defined in the header file ``uz_global_configuration.h``.
Since the configuration of the system is specific for all users, this file does not exist in the repository and is not **not** tracked by git (listed in .gitignore).
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
