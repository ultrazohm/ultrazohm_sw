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

The figure above shows the four states of the UltraZohm:

- Idle
- Running
- Control
- Error

The implicit state *assertion* is not shown (see :ref:`assertions`).
If an assertion is triggered in any state, the state machine enters the error state.
From error state, the system returns to idle when a stop input is present.
The state machine has the following input variables:

- Enable system
- Enable control
- Stop
- Error

For all UltraZohm versions >2, enable system, enable control, and stop are available as buttons on the front panel.
Additionally, these signals can be set using the :ref:`JavaScope` setter functions (e.g., ``ultrazohm_state_machine_set_enable_system``).
The effective state machine inputs are updated in every ``ultrazohm_state_machine_step`` by merging both sources:

- Enable system = front-panel button ``OR`` JavaScope request
- Enable control = front-panel button ``OR`` JavaScope request (only considered in running state)
- Stop = front-panel stop ``OR`` JavaScope request (plus optional external stop, if enabled at compile time)

This merged handling avoids race conditions where asynchronous JavaScope commands could otherwise be overwritten by button polling.
The input ``Error`` is only set from software functions.

The different states are indicated by the status of the LEDs on the front panel.
The main difference between the states is that no output signals are routed through the CPLD (*gate signals* are off) if the system is not in the state *Running* or *Control*.
Likewise, the control algorithm in the ISR is not executed, if the system is not in the state *Control*.

The following table shows the complete state table.
In this table, ``Enable System``, ``Enable Control``, and ``Stop`` refer to the merged effective inputs described above.

.. csv-table:: State table with inputs and outputs of the UltraZohm
    :file: r5_statemachine_table.csv
    :widths: 10 10 10 10 10 10 10 10 10 10 10 10
    :header-rows: 3




Software reference
==================

.. doxygenenum:: platform_state_t

.. doxygenfunction:: ultrazohm_state_machine_get_state

.. doxygenfunction:: ultrazohm_state_machine_step

.. doxygenfunction:: ultrazohm_state_machine_set_enable_system

.. doxygenfunction:: ultrazohm_state_machine_set_enable_control

.. doxygenfunction:: ultrazohm_state_machine_set_stop

.. doxygenfunction:: ultrazohm_state_machine_set_error

.. doxygenfunction:: ultrazohm_state_machine_get_enable_system

.. doxygenfunction:: ultrazohm_state_machine_get_enable_control

.. doxygenfunction:: ultrazohm_state_machine_is_control_state

.. doxygenfunction:: ultrazohm_state_get_led_running

.. doxygenfunction:: ultrazohm_state_get_led_ready

.. doxygenfunction:: ultrazohm_state_get_led_error
