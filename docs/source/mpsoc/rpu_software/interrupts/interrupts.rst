.. _r5_interrupts:

=============
Interrupts R5
=============

Software User Model
-------------------

The interrupt triggers the ``ISR_Control`` function (in ``isr.c``) and the ADC conversion in the PL. 
The trigger can be synchronized with the PWM (two- and three-level) modules or a timer. 
The interrupt trigger is defined in ``uz_global_configuration.h``  by assigning a value to ``Interrupt_ISR_source_user_choice``.

.. code-block:: c 

    //chose here which of the above interrupt trigger you want to use:
    #define Interrupt_ISR_source_user_choice	0

    
.. csv-table:: Trigger sources for interrupt
   :header: "#","Define name", "Interrupt trigger"
   :widths: 10,20, 20
   
    "0","Interrupt_2L_max_min","Two-Level PWM Module at **minimum** and **maximum** value of the triangular carrier"
    "1","Interrupt_2L_min","Two-Level PWM Module at **minimum** value of the triangular carrier"
    "2","Interrupt_2L_max","Two-Level PWM Module at **maximum** value of the triangular carrier"
    "3","Interrupt_3L_start_center","Three-Level PWM Module at **minimum** and **maximum** value of the triangular carrier"
    "4","Interrupt_3L_start","Three-Level PWM Module at **minimum** value of the triangular carrier"
    "5","Interrupt_3L_center","Three-Level PWM Module at **maximum** value of the triangular carrier"
    "6","axi2tcm_write_done","Triggers when axi2tcm signals ``write_done`` and is configured in ``Initialize_Timer``"


Structure of the Interrupt
--------------------------

.. mermaid::
    :align: center
    :caption: Usage of ``Interrupt_ISR_source_user_choice`` in source code
    
    graph TD
      A[Interrupt_ISR_source_user_choice] -->|Sets interrupt source| B(Initialize_ISR)
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

    * ``mux_axi``: chose source of ADC conversion trigger 
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
At the moment this is done with a VIO (Virtual IO) in the Hardware Manager in Vivado.

