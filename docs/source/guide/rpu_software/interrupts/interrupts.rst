.. _r5_interrupts:

=============
R5 interrupts
=============

Software User Model
-------------------

The interrupt triggers the ``ISR_Control`` function (in ``isr.c``) and the ADC conversion in the PL.

User can set the interrupt source
Can choose every nth pwm event is a ISR event
Can delay between pwm event and adc trigger


Two defines in ``uz_global_configuration.h`` control how the **ISR** and the **ADC** conversion are triggered:

* ``INTERRUPT_ISR_SOURCE_USER_CHOICE`` selects the PWM counter event as the base trigger source.

The **ISR** has an additional trigger mode ``INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY``:

* ``0``: ISR triggers on the PWM event selected by ``INTERRUPT_ISR_SOURCE_USER_CHOICE``. This results in a race condition between ADC data transfer and ISR execution.
* ``1``: ISR triggers on ``axi2tcm_write_done``, i.e. after the ADC conversion is complete and the data has been transferred to TCM (~:math:`1.3 \mu s` delay after the PWM event). This eliminates the race condition between ADC data transfer and ISR execution.

The **ADC** trigger signal can be delayed relative to the original trigger signal by setting the ``ADC_TRIGGER_DELAY_IN_US`` define.

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

From an outside perspective, the interrupt gets six different sources for the interrupt and outputs the selected signal to the PS interrupt and to trigger_conversions for the ADC.


.. _pl_interrupt_module:

.. figure:: images_interrupt/pl_interrupt_module_top_view.png

  Top view of the PL module of the interrupt structure. Interrupt6 is the signal from axi2tcm_write_done.



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


ILA Timing Example
~~~~~~~~~~~~~~~~~~

The following timing diagram is generated directly from ``interrupt_ila_data.csv`` and therefore stays in sync with the captured hardware data.
It plots all recorded CSV signals over the full capture range in one figure, without selecting a subset of traces or creating zoomed views.

.. plot:: guide/rpu_software/interrupts/interrupts_ila_plot.py
  :caption: Timing diagram generated from ILA export in ``interrupt_ila_data.csv``. 

The following additional timing diagram is generated directly from ``iladata.vcd``.
It renders the same captured probes from the raw VCD waveform export, which is useful when only the VCD file is available.

.. plot:: guide/rpu_software/interrupts/interrupts_ila_vcd_plot.py
  :caption: Additional timing diagram generated from ILA export in ``iladata.vcd``. 


.. code-block:: c
  :caption: Settings of the timing diagram


   #define UZ_SOURCE_Interrupt_2L_max_min 0
   #define UZ_SOURCE_Interrupt_2L_max_min 1
   #define UZ_SOURCE_Interrupt_2L_max_min 2
   #define UZ_SOURCE_Interrupt_2L_max_min 3
   #define UZ_SOURCE_Interrupt_2L_max_min 4
   #define UZ_SOURCE_Interrupt_2L_max_min 5

   #define INTERRUPT_ISR_SOURCE_USER_CHOICE        0U

   #define INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY 0U // 0: ISR fires on selected PWM event. 1: ISR fires on axi2tcm_write_done (ADC data in TCM). See r5_interrupts in docs.
   #define INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE	10U
   #define ADC_TRIGGER_DELAY_IN_US                 0.01f // ADC trigger delay in us; applies in both ISR trigger modes. 10ns delay to keep default behvaior. See uz_mux_axi in docs.

