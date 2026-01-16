.. _vitis_programming_modes:

Vitis Programming Modes
=======================

Vitis (Eclipse) provides two buttons to start the programming procedure of the UltraZohm

- **Run** (green arrow) button ignoring all breakpoints.
- **Debug** (green bug) button fully supporting breakpoints.

The inteded use of the three launch configurations are as follows:

- ``Run_UltraZohm`` via the **Run** (green arrow) 
- ``Debug_UltraZohm`` via the  **Debug** (green bug) 
- ``Debug_UltraZohm_fast_restart_PL_reset`` (DEBUG_WARM_START) via the  **Debug** (green bug) 


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
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Default programming modes of the UltraZohm.

- Full system reset ``rst -system``
- Downloads bitstream to PL and executes PS initialization ``psu_init``
- Downloads the application ELF(s) and starts execution (``con``).


``Debug_UltraZohm_fast_restart_PL_reset``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Faster programming mode for rapid software iteration. 

- Skips PL programming and PS init if the FPGA is already programmed, otherwise same as above (full PL programming and PS init)
- Stops selected R5:0 and A53:0 cores to stop all AXI-transactions from PS to PL.
- Resets FPGA with ``psu_ps_pl_reset_config`` command (stopping all AXI-transactions PL to PS).
- Performs a core-level reset of proccesors, programs them with ELF-files and lets them run as usual. 
- If the system state is inconsistent (e.g., after PL changes), fall back to ``Run_UltraZohm`` or ``Debug_UltraZohm``.


Addtional notes
----------------

- The behavior is defined by TCL startup script ``tcl_scripts/vitis_debug_run_UltraZohm.tcl`` 
- The differentiation in ``Run_UltraZohm`` and ``Debug_UltraZohm`` ensures that the launch session is terminated when switching between them. 

.. figure:: images_vitis_programming_modes/launch_session_terminate.jpg
   :width: 70%
   When prompted, always choose ``Yes`` to terminate the existing launch session.

- To enable the ``Debug_UltraZohm_fast_restart_PL_reset`` mode, the interrupt initialization process had to be adjusted to catch the case that the processors are reset while actively handeling an interrupt. In that the case, the ``ACTIVE`` register of that interrupt is latched after reprogramming the processor, since the General Interrupt Controller (GIC) is a peripheral that is not reset during core-level resets. 
As a remedy, the  ``ACTIVE`` register is read during startup and maunally cleared if necessary.
This applies to both proccesors, R5:0 and A53:0.
See changes in #PR532 for details.