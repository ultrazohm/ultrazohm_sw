.. _r5_statemachine:

================
R5 state machine
================

The state of the UltraZohm is controlled by a state machine in the R5.
After the initialization, there are four states:

- Idle
- Running
- Control
- Error

The different states are indicated by  the status of the LEDs on the front panel.
The main difference between the states is that no output signals are routed througth the CPLD (*gate signals* are off) if the system is not in the state *Running* or *Control*.
Likewise, the control algorithm in the ISR is not executed, if the system is not in the state *Control*.

For simplification, the different steps of the initialization procedure are not shown in the state table.
They are just executed one after the other.
Note that the sequence matters, i.e., the state *Initialize Interrupt* has to be the last init state.
The implicit state *assertion* is not shown.
If in any state an execution is  triggered, the error state is executed once and the system is on hold and can only be used after a restart (power cycle).


Table:

.. csv-table:: State table
    :file: r5_statemachine_table.csv
    :widths: 10 10 10 10 10 10 10 10 10 10 10 10
    :header-rows: 1


.. mermaid::

    stateDiagram-v2
        [*] --> Setup
        Setup --> Init_platform
        Init_platform --> Init_ip
        Init_ip --> Init_isr
        Init_isr --> Idle
        Idle --> Running: Enable System
        Running --> Control: Enable Control
        Control --> Error: Error
        Running --> Error: Error
        Idle --> Error: Error
        Error --> Idle: Reset Error
        Running --> Idle: Stop
        Control --> Idle: Stop
        state "Idle" as Idle: uz_interlockDeadtime2L_set_enable_output <br> Blink ready LED
        state "Running" as Running: Slowly blink running LED <br> uz_axigpio_enable_pwm_and_power_electronics
        state "Control" as Control: Blink running LED <br> Enable control algorithm
        state "Error" as Error: Disable power electronics
        state "Setup assertions" as Setup: Xil_AssertSetCallback <br> uz_printf("Welcome")
        state "Initialize platform" as Init_platform: Initialize_AXI_GPIO <br> uz_frontplane_button_and_led_init <br> Initialize_Timer <br> uz_SystemTime_init <br> JavaScope_initalize <br>
        state "Initialize IP-Cores" as Init_ip: uz_adcLtc2311_ip_core_init <br> uz_interlockDeadtime2L_staticAllocator_slotD1 <br> initialize_pwm_2l_on_D1 <br> PWM_3L_Initialize <br> initialize_incremental_encoder_ipcore_on_D5 <br> 
        state "Initialize Interrupt" as Init_isr: Initialize_ISR <br> AXI2TCM_on


