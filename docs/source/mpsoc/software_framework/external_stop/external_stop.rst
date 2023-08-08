.. _external_stop:

=============
External Stop
=============

Description
===========

| Since hardware revision 3, the UltraZohm owns a connector for an external stop button.
| **This external stop functionality is explicitly not an emergency stop!**
| It simply reflects the ``STOP`` button functionality from the ``front panel``, as well as in the ``JavaGUI``.
| Therefore, when using this feature as described below, pressing the external stop button simply sets the :ref:`r5_statemachine` 
| into ``Idle`` state. Additional behavior like e.g. bringing connected power electronics into a safe state has to be ensured by the user.
| Using the external stop button has to be configured in the global configuration file, see :ref:`global_configuration`.

Usage
=====

.. warning:: Pay attention to the dependency on the hardware revision of the UltraZohm

* ``UZ_HARDWARE_VERSION`` is ``3``: **nothing to configure**, works out of the box.
* ``UZ_HARDWARE_VERSION`` is ``4`` and higher: set ``UZ_USE_EXTERNAL_STOP_ON_V4`` to ``1U`` as shown below.

.. code-block:: c
  :emphasize-lines: 2,6
  :caption: Configuration of global_configuration.h for usage of external stop with hardware version 4 and higher. 

    // Hardware version of the UltraZohm
    #define UZ_HARDWARE_VERSION 4U

    // If Hardware version is v4 and the external STOP should be used, this define has to be set to 1. Otherwise, the external stop does nothing.
    // For Version 3, the external STOP always works, but the hardware loopback is required if no external stop is used.
    #define UZ_USE_EXTERNAL_STOP_ON_V4 1U

    #if (UZ_HARDWARE_VERSION != 4U) && (UZ_USE_EXTERNAL_STOP_ON_V4 == 1U)
    #error The UZ_USE_EXTERNAL_STOP_ON_V4 flag must not be used on hardware version 3. For hardware version 3, external stop can be used without the flag, prior versions to 3 do not have this feature.
    #endif