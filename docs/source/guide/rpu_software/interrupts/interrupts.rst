.. _r5_interrupts:

=============
R5 interrupts
=============

Software User Model
-------------------

The interrupt triggers the ``ISR_Control`` function (in ``isr.c``) and the ADC conversion in the PL.
Two defines in ``uz_global_configuration.h`` control how the ISR is triggered:

* ``INTERRUPT_ISR_SOURCE_USER_CHOICE`` — selects which PWM counter event is used as the base trigger source.
* ``INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY`` — selects the trigger mode:

  * ``0``: ISR fires directly on the PWM event selected by ``INTERRUPT_ISR_SOURCE_USER_CHOICE``.
  * ``1``: ISR fires on ``axi2tcm_write_done``, i.e. after the ADC conversion is complete and the data has been transferred to TCM (~1.3 µs delay after the PWM event). This eliminates the race condition between ADC data transfer and ISR execution.

An additional delay for the ADC trigger path can be configured with ``ADC_TRIGGER_DELAY_IN_US``.

.. code-block:: c

    // Select the PWM counter event used as the base trigger source:
    #define INTERRUPT_ISR_SOURCE_USER_CHOICE        0U
    // Trigger the ISR on axi2tcm_write_done instead of directly on the PWM event:
    #define INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY 1U


.. csv-table:: PWM trigger sources for ``INTERRUPT_ISR_SOURCE_USER_CHOICE``
   :header: "#","Define name", "Interrupt trigger"
   :widths: 10,20, 20

    "0","Interrupt_2L_max_min","Two-Level PWM Module at **minimum** and **maximum** value of the triangular carrier"
    "1","Interrupt_2L_min","Two-Level PWM Module at **minimum** value of the triangular carrier"
    "2","Interrupt_2L_max","Two-Level PWM Module at **maximum** value of the triangular carrier"
    "3","Interrupt_3L_start_center","Three-Level PWM Module at **minimum** and **maximum** value of the triangular carrier"
    "4","Interrupt_3L_start","Three-Level PWM Module at **minimum** value of the triangular carrier"
    "5","Interrupt_3L_center","Three-Level PWM Module at **maximum** value of the triangular carrier"

.. note::
   When one of the two-level PWM sources is selected, update
   ``uz_PWM_SS_2L_config_t.trigger_source`` in the PWM driver at the same time:

   * ``Interrupt_2L_min`` with ``trigger_at_MIN``
   * ``Interrupt_2L_max`` with ``trigger_at_MAX``
   * ``Interrupt_2L_max_min`` with ``trigger_at_EITHER``

   This keeps PWM register updates, ADC triggering, and ``ISR_Control``
   synchronized to the same carrier event.


Structure of the Interrupt
--------------------------

.. mermaid::
    :align: center
    :caption: Usage of interrupt configuration defines in source code

    graph TD
      A[INTERRUPT_ISR_SOURCE_USER_CHOICE] -->|Sets ADC trigger source| B(Initialize_ISR)
      C[INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY] -->|Sets ISR trigger source| B
      B -->|Mux for ADC trigger source| D[ADC trigger in PL]
      B -->|Rpu_GicInit| E[Trigger source of ISR_Control]

.. mermaid::
    :align: center
    :caption: Signal flow in PL for ADC trigger and ISR trigger

    graph LR
        PWM2L --> Concat_interrupts
        PWM3L --> Concat_interrupts
        Concat_interrupts --> mux_axi
        mux_axi -->|"interrupt_out_adc (selected PWM source)"| delay_trigger
        delay_trigger --> ADC_conversion
        ADC_conversion -->|axi2tcm_write_done| Concat_interrupts
        Concat_interrupts -->|"selected interrupt ID → R5 GIC"| R5_Interrupt

Structure in the PL
-------------------

The Interrupt module consists of:

* ``mux_axi``: chooses the ADC conversion trigger source, the ADC-to-ISR ratio, and configures the ADC trigger delay
* ``delay_trigger``: adds the configured delay to the ADC conversion trigger
* ``vio_interrupt``: manually injects an interrupt trigger via Vivado hardware manager for debugging

.. _pl_interrupt_module:

.. figure:: images_interrupt/pl_interrupt_module.png

  PL module of the interrupt structure.


In Vivado, the signals connected to ``pl_ps_irq0`` are assigned an interrupt ID starting at ``XPS_FPGA0_INT_ID`` for bit 0 and increasing with each additional signal. 
In our project, the ``Interrupt_vector`` is directly connected to ``pl_ps_irq0``. 
With this logic, the interrupt IDs are assigned in ``isr.h``.
Note that ``XPS_FPGAx_INT_ID`` is defined in ``xparameters_ps.h``.


Trigger of ADC Conversion
-------------------------
The ADC conversion is always triggered by the PWM source selected via ``INTERRUPT_ISR_SOURCE_USER_CHOICE``, regardless of the ISR trigger mode set by ``INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY``.

In some applications, the ADC conversion needs to be delayed relative to the PWM trigger — for example when using IGBTs, where the switching transient must settle before sampling.
To prevent ADC sampling during a switching event, this delay can be added in PL via ``ADC_TRIGGER_DELAY_IN_US`` in ``uz_global_configuration.h``.
The software driver converts the configured value in microseconds to clock cycles and rounds up to the next achievable step.
This delay applies in both ISR trigger modes: when ``INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY = 1``, the ISR fires after the (already delayed) ADC conversion completes and the data has been transferred to TCM.
For more details on the register and driver interface, see :ref:`uz_mux_axi`.

.. _delay_trigger_block:

Delay Trigger Block
~~~~~~~~~~~~~~~~~~~

The PL delay is implemented by ``delay_trigger.vhd`` in ``ip_cores/Delay_signal``.
The block behavior is:

* ``delay_cycles = 0`` routes ``a_in`` directly to ``a_out``
* ``delay_cycles = 1..1023`` emits a delayed output pulse after the configured number of ``clk`` cycles
* the output pulse width is fixed locally in the VHDL source via ``pulse_width_cycles_c``
* changing ``delay_cycles`` clears any pending delayed trigger
* a second rising edge while a delayed pulse is pending or active is ignored
* ``pulse_pending`` indicates that a delayed trigger is pending or currently being emitted

With the default 100 MHz clock used in the interrupt path, the achievable delay range is ``0`` to ``10.23 us`` in ``10 ns`` steps.

