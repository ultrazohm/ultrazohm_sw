.. _uz_mux_axi:

=============================
Mux Axi / ISR Trigger Control
=============================

- Selects the PWM counter event that triggers ADC and the interrupt of the R5 processor
- Selects ADC/ISR trigger ratio: trigger the ISR in the R5 every n-th ADC trigger event ``(n = 1,2,3,...)``


PWM counter events
==================

- The ``PWM and SS Control`` as well as the 3-level PWM ip core use an up-down counter
- At counter min and max those ip cores provide rising edge signals that are fed to the uz_mux_axi ip core
- Those trigger signals depend on the selected PWM frequency


Interrupt sources
=================

- The user selects the trigger source for ADC triggering via the ``#define`` ``INTERRUPT_ISR_SOURCE_USER_CHOICE`` in ``uz_global_configuration.h`` (see :ref:`global_configuration`)
- The selected trigger source also triggers the ISR in the R5 processor (see also :ref:`r5_interrupts`)
- Below, as well as in ``uz_global_configuration.h``, the user will find the valid interrupt source options:

.. code-block:: c

   /** ISR trigger source
    *
    * chose here which of the above interrupt trigger you want to use:
    * 0 for Interrupt_2L_max_min
    * 1 for Interrupt_2L_min
    * 2 for Interrupt_2L_max
    * 3 for Interrupt_3L_start_center
    * 4 for Interrupt_3L_start
    * 5 for Interrupt_3L_center
    * 6 for Interrupt_timer_fcc
   */

ADC/ISR trigger ratio
=====================

- If necessary, the user can choose an integer multiple ratio between ADC and ISR triggering
- This is done by setting the ``INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE`` ``#define`` in ``uz_global_configuration.h``

Example
=======

The user wants to have a PWM frequency of 100 kHz and an ISR frequency of 20 kHz:

- The user selects the PWM frequency of 100 kHz: the define ``UZ_PWM_FREQUENCY`` is set to ``100.0e3f`` in ``uz_global_configuration.h``
- The trigger source is ``Interrupt_2L_min``: the define ``INTERRUPT_ISR_SOURCE_USER_CHOICE`` is set to ``1U`` in ``uz_global_configuration.h``
- The trigger ratio is set to 5 (100 kHz/20 kHz = 5): the define ``INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE`` is set to ``5U`` in ``uz_global_configuration.h``

.. code-block:: c
   :caption: Settings in uz_global_configuration.h for the example

   #define INTERRUPT_ISR_SOURCE_USER_CHOICE        1U
   #define INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE  5U
   
   #define UZ_D5_INCREMENTAL_ENCODER_RESOLUTION    5000.0f
   #define UZ_D5_MOTOR_POLE_PAIR_NUMBER            4.0f
   #define UZ_PWM_FREQUENCY                        10.0e3f

These settings result in the behavior depicted in :numref:`example_trigger_picture` (ADC interrupt in the upper subplot, interrupt of R5 in the lower subplot):

.. _example_trigger_picture:

.. figure:: img/adc_to_isr_ratio.png
   :width: 800
   :align: center

   Resulting trigger ratio from the example above


.. warning::
   * Trigger ratios other than ``1`` were only tested with trigger source ``Interrupt_2L_min``
   * Especially when using trigger sources with two ADC trigger events (e.g. ``Interrupt_2L_max_min``), the user has to take care of the resulting ADC/ISR trigger ratio

IP-Core
=======

The IP-Core takes up to 8 different interrupt sources as inputs (external port ``interrupts_in``).
One of these inputs is selected by AXI configuration and routed directly routed to the ``interrupt_out_adc`` external port. 
Additionally, all interrupt sources of ``interrupts_in`` are coupled with an internal counter that routes the signal of ``interrupts_in`` to ``interrupt_out_isr`` every n-th time the ``interrupt_out_adc`` signal is high.
Table :ref:`ipCore_uz_mux_axi_interfaces` lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. _ipCore_uz_mux_axi_interfaces:

.. csv-table:: Interface of uz_mux_axi IP-Core
   :file: uz_mux_axi_register_mapping.csv
   :widths: 50 50 50 50 50 50 200
   :header-rows: 1

:numref:`ip_core_vivado_picture` of the IP-Core embedded in the block design:

.. _ip_core_vivado_picture:

.. figure:: img/ipcore.png
   :width: 800
   :align: center

   IP-Core in the default Vivado block design.


Software driver
===============

The software driver is initialized by default. The user just has to select the mux and the interrupt ratio ``#define`` in ``uz_global_configuration.h``
The IP-Core is initialized at the startup of the system. The software driver is not intended to change the settings at runtime.

Reference
=========

.. doxygentypedef:: uz_mux_axi_t

.. doxygenstruct:: uz_mux_axi_config_t
  :members:

.. doxygenfunction:: uz_mux_axi_init

.. doxygenfunction:: uz_mux_axi_enable

.. doxygenfunction:: uz_mux_axi_set_mux

.. doxygenfunction:: uz_mux_axi_set_n_th_interrupt

