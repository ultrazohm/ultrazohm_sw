.. _r5_interrupts:

=============
R5 interrupts
=============

Software User Model
-------------------

The interrupt triggers the ``ISR_Control`` function (in ``isr.c``) and the ADC conversion in the PL.
The trigger can be synchronized with the PWM (two- and three-level) modules or the ``axi2tcm`` data mover.
The interrupt trigger is defined in ``uz_global_configuration.h`` by assigning a value to ``INTERRUPT_ISR_SOURCE_USER_CHOICE``.

.. code-block:: c 

    // choose here which of the above interrupt triggers you want to use:
    #define INTERRUPT_ISR_SOURCE_USER_CHOICE  0U

    
.. csv-table:: Trigger sources for interrupt
   :header: "#","Define name", "Interrupt trigger"
   :widths: 10,20, 20
   
    "0","Interrupt_2L_max_min","Two-Level PWM Module at **minimum** and **maximum** value of the triangular carrier"
    "1","Interrupt_2L_min","Two-Level PWM Module at **minimum** value of the triangular carrier"
    "2","Interrupt_2L_max","Two-Level PWM Module at **maximum** value of the triangular carrier"
    "3","Interrupt_3L_start_center","Three-Level PWM Module at **minimum** and **maximum** value of the triangular carrier"
    "4","Interrupt_3L_start","Three-Level PWM Module at **minimum** value of the triangular carrier"
    "5","Interrupt_3L_center","Three-Level PWM Module at **maximum** value of the triangular carrier"
    "6","axi2tcm_write_done","Triggers when axi2tcm data mover signals ``write_done``"

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
    :caption: Usage of ``INTERRUPT_ISR_SOURCE_USER_CHOICE`` in source code
    
    graph TD
      A[INTERRUPT_ISR_SOURCE_USER_CHOICE] -->|Sets interrupt source| B(Initialize_ISR)
      B -->|Mux for ADC trigger source| D[Trigger source of ADC in PL]
      B -->|Rpu_GicInit| E[Trigger source of ISR_Control]
		
.. mermaid::
    :align: center
    :caption: Signal flow in PL of interrupt and trigger ADC

    graph LR
        PWM2L --> Interrupt
        PWM3L --> Interrupt
        Interrupt --> Concat_interrupts
        Concat_interrupts --> mux_axi
        mux_axi --> ADC_trigger_conversion
        Concat_interrupts --> R5_Interrupt

Structure in the PL
-------------------

The Interrupt module consists of:

* ``mux_axi``: choose source of ADC conversion trigger
* ``delay_trigger``: adds delay to the ADC conversion trigger
* ``vio_interrupt``: manually trigger delay by Vivado hardware manager for debugging
* ``adc_delay``: vio to set delay of ``delay_trigger``

.. _pl_interrupt_module:

.. figure:: images_interrupt/pl_interrupt_module.png

  PL module of the interrupt structure.


In Vivado, the signals connected to ``pl_ps_irq0`` are assigned an interrupt ID starting at ``XPS_FPGA0_INT_ID`` for bit 0 and increasing with each additional signal. 
In our project, the ``Interrupt_vector`` is directly connected to ``pl_ps_irq0``. 
With this logic, the interrupt IDs are assigned in ``isr.h``.
Note that ``XPS_FPGAx_INT_ID`` is defined in ``xparameters_ps.h``.


Trigger of ADC Conversion
-------------------------
In some applications, the ADC conversion needs to be delayed relative to the trigger from the PWM module. 
This can be the case if you are using an IGBT, where the delay introduced by the driver and the IGBT itself are not negligible. 
To ensure that the ADC sampling does not occur while switching, the delay can be added in PL. 
At the moment this is done with a VIO (Virtual I/O) in the Hardware Manager in Vivado.

