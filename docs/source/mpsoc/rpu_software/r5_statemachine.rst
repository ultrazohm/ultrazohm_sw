.. _r5_statemachine:

================
R5 state machine
================

The state of the UltraZohm is controlled by a state machine in the R5 (``uz_platform_state_machine.c``).
The initialization of the system is not part of the state machine and is done in ``main.c`` of the R5.

.. _state_machine_figure:

.. mermaid::

    stateDiagram-v2
        [*] --> Idle
        Idle --> Running: Enable System
        Running --> Control: Enable Control
        Control --> Error: Error
        Running --> Error: Error
        Idle --> Error: Error
        Error --> Idle: Stop
        Running --> Idle: Stop
        Control --> Idle: Stop
        state "Idle" as Idle: Slowly blink ready LED
        state "Running" as Running: Blink ready LED <br> Enable FPGA outputs
        state "Control" as Control: Blink ready LED <br> Turn on running LED <br> Enable control algorithm
        state "Error" as Error: Disable FPGA outputs <br> Turn on error LED

The figure above shows the four state of the UltraZohm:

- Idle
- Running
- Control
- Error

The implicit state *assertion* is not shown (see :ref:`assertions`).
If in any state an execution is triggered, the error state is executed once, the system is hold and can only be used after a restart (power cycle).
The state machine has the following input variables:

- Enable system
- Enable control
- Stop
- Error

The inputs are set using the set functions (e.g., ``ultrazohm_state_machine_set_enable_system``).
For all UltraZohm versions >2, enable system, enable control, and stop are available as buttons on the frontpanel.
Additionally, the signals can be set using the :ref:`JavaScope`.
The input ``Error`` is only set from software functions.

The different states are indicated by the status of the LEDs on the front panel.
The main difference between the states is that no output signals are routed through the CPLD (*gate signals* are off) if the system is not in the state *Running* or *Control*.
Likewise, the control algorithm in the ISR is not executed, if the system is not in the state *Control*.

The following table shows the complete state table.

.. csv-table:: State table with inputs and outputs of the UltraZohm
    :file: r5_statemachine_table.csv
    :widths: 10 10 10 10 10 10 10 10 10 10 10 10
    :header-rows: 3




Software reference
==================

.. doxygenfunction:: ultrazohm_state_machine_step

.. doxygenfunction:: ultrazohm_state_machine_set_enable_system

.. doxygenfunction:: ultrazohm_state_machine_set_enable_control

.. doxygenfunction:: ultrazohm_state_machine_set_stop

.. doxygenfunction:: ultrazohm_state_machine_set_error

.. doxygenfunction:: ultrazohm_state_machine_get_enable_system

.. doxygenfunction:: ultrazohm_state_machine_get_enable_control

.. doxygenfunction:: ultrazohm_state_machine_is_control_state