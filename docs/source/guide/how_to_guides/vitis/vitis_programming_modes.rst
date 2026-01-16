.. _vitis_programming_modes:

Vitis Programming Modes
=======================

Vitis (Eclipse) provides two launch buttons to program and start the UltraZohm target:

- **Run** (green arrow) button ignoring all breakpoints.
- **Debug** (green bug) button fully supporting breakpoints.

The intended use of the three UltraZohm launch configurations is:

- ``Run_UltraZohm`` via **Run** (green arrow)
- ``Debug_UltraZohm`` via **Debug** (bug)
- ``Debug_UltraZohm_fast_restart_PL_reset`` (DEBUG_WARM_START) via **Debug** (bug)

.. figure:: images_vitis_programming_modes/vitis_launch_modes_run.jpg
   :width: 70%
    Vitis **Run** dropdown for launch configurations ``Run_UltraZohm`` 

.. figure:: images_vitis_programming_modes/vitis_launch_modes_debug.jpg
   :width: 70%
   Vitis **Debug** dropdown for launch configurations ``Debug_UltraZohm`` and ``Debug_UltraZohm_fast_restart_PL_reset``


Modes
-----

In all modes, variables can be inspected via the Expressions view in Vitis and the proccesors can be suspended and resumed.
Breakpoints are only supported when the **Debug** (green bug) button is used to start the programming procedure.


``Run_UltraZohm`` and ``Debug_UltraZohm``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Default programming modes for UltraZohm.

- Full system reset ``rst -system``
- Downloads bitstream to PL and executes PS initialization ``psu_init``
- Downloads the application ELF(s) and starts execution (``con``).


``Debug_UltraZohm_fast_restart_PL_reset``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Faster programming mode for rapid software iteration. 

- Skips PL programming and PS initialization if the FPGA is already configured; otherwise behaves like the
  default modes (full PL programming and ``psu_init``).
- Stops the cores R5:0 and A53:0 to quiesce software-driven AXI activity from PS to PL.
- Issues a PL reset via ``psu_ps_pl_reset_config`` (resets PL logic to initial state similar to reprogramming it with the same bitstream).
- Performs a core-level reset of the processors, downloads the ELF files, and starts execution.
- If the system state is inconsistent (e.g., after PL or platform changes), fall back to
  ``Run_UltraZohm`` or ``Debug_UltraZohm``.

Additional notes
----------------

- After initially building the Vitis workspace via ``vitis_generate_UltraZohm_workspace.tcl``, the launch
  configurations may only appear after restarting Vitis once.
- The programming sequence is defined by the TCL startup script
  ``tcl_scripts/vitis_debug_run_UltraZohm.tcl``.
- Using separate launch configurations for ``Run_UltraZohm`` and ``Debug_UltraZohm`` ensures the active launch
  session is terminated when switching between them.

.. figure:: images_vitis_programming_modes/launch_session_terminate.jpg
   :width: 70%

   When prompted, choose ``Yes`` to terminate the existing launch session.

- To enable ``Debug_UltraZohm_fast_restart_PL_reset``, the interrupt initialization was adjusted to handle the
  case where a processor is reset while an interrupt is active. 
  In this case, the interrupt **ACTIVE** state can remain latched across a core-level reset because the GIC is not reset by a core reset.
  As a remedy, the **ACTIVE** register is checked during startup and maunally cleared by the EOIR (End-of-Interrupt-Register). 
  This applies to both processors, R5:0 and A53:0. See PR532 for details.