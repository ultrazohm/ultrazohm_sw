.. _global_configuration:

====================
Global configuration
====================

The global configuration of the UltraZohm workspace regarding the R5 software is defined in the header file ``uz_global_configuration.h``.
The configuration of the system is specific for all users and must be adjusted to the specific setup.

After cloning the repository, the user has to:

#. Navigate to ``uz_global_configuration.h`` in ``vitis/software/Baremetal/src/uz``
#. Adjust the configuration to match your setup
#. Compile the software
#. Use the UltraZohm

Configuration
=============

The configuration is used for:

- :ref:`static_memory_allocation`
- Set the hardware version specific settings (e.g., ``UZ_HARDWARE_VERSION`` for different front panels).
- Configure the use of an external stop button, depending on the hardware revision (:ref:`external_stop`)

Timing-related defines
======================

The following defines in ``uz_global_configuration.h`` are commonly adjusted together. This section only lists the fields and points to the detailed documentation.

.. list-table:: Timing-related global configuration defines
   :widths: 35 65
   :header-rows: 1

   * - Define
     - Description
   * - ``INTERRUPT_ISR_SOURCE_USER_CHOICE``
     - Selects the PWM counter event used as the base trigger source. See :ref:`r5_interrupts` and :ref:`uz_mux_axi`.
   * - ``INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY``
     - Trigger mode: ``0`` fires the ISR directly on the PWM event; ``1`` fires on ``axi2tcm_write_done`` (ADC data ready in TCM). See :ref:`r5_interrupts`.
   * - ``INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE``
     - Sets the ADC-to-ISR trigger ratio. See :ref:`uz_mux_axi`.
   * - ``ADC_TRIGGER_DELAY_IN_US``
     - Sets the additional ADC trigger delay. See :ref:`uz_mux_axi`.
   * - ``UZ_PWM_DEADTIME_IN_US``
     - Sets the initial deadtime of the 2-level interlock/deadtime blocks. See :ref:`uz_interlockDeadtime2L`.
   * - ``UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US``
     - Sets the initial minimum pulse width used by the 2-level PWM driver. See :ref:`uz_pwm_ss_2l`.
