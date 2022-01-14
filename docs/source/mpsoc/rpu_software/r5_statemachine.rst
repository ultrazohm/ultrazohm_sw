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
        [*] --> Idle
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

