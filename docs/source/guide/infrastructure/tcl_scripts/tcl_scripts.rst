.. _tcl_scripts:

===========
Tcl Scripts
===========

Xilinx uses Tcl to control vivado and vitis by script.
See Xilinx `UG835 <https://www.xilinx.com/support/documentation/sw_manuals/xilinx2020_1/ug835-vivado-tcl-commands.pdf>`_, `UG1416 <https://www.xilinx.com/html_docs/xilinx2020_1/vitis_doc/upu1569395223804.html>`_ and `UG1400 <https://www.xilinx.com/support/documentation/sw_manuals/xilinx2019_2/ug1400-vitis-embedded.pdf>`_ for reference.
All Tcl scripts of the UltraZohm Community are located in the ``ultrazohm_sw`` repository in the folder ``tcl_scripts``.
The three different kinds of Tcl scripts are differentiated by prefix:

* ci\_ marks scripts that are used for continuous integration
* vivado\_ marks scripts for Vivado
* vitis\_ marks scripts for Vitis

The Vivado scripts can be called from Vivado Tcl console (``Window -> Tcl console`` in Vivado) or choose a Tcl script (``Tools -> Run Tcl script...``) as well as the command line in batch mode on linux:

::

  vivado -nolog -nojournal -mode batch -source $NAME.tcl

The ``settings64.sh`` might need to be executed if vivado is not on path after a boot of the system.
The path depends on your install location (e.g. ``/opt/`` instead of ``/tools/``).

::

  source /tools/Xilinx/Vivado/2020.1/settings64.sh

The Vitis scripts can be called from the XSCT console from Vitis (see :ref:`vitis_gen_workspace_tcl`) or from the command line:

::

  xsct $NAME.tcl

The ``settings64.sh`` might need to be executed if Vitis is not on path after a boot of the system.
The path depends on your install location (e.g. ``/opt/`` instead of ``/tools/``).

::

  source /tools/Xilinx/Vivado/2020.1/settings64.sh

ci\_
****

The CI scripts draw from `this tutorial <https://vhdlwhiz.com/jenkins-for-fpga#vivado-gui-projects-in-batch-mode>`_.

ci_generate_bitstream.tcl
-------------------------

Opens the ``ultrazohm.xpr`` Vivado project and runs the design flow to ``write_bitstream``.
Returns ``0`` if successful and ``1`` if not.

vivado\_
********

.. _vivado_export_xsa_tcl:

vivado_export_xsa.tcl
---------------------

Exports the Bitstream (``.xsa`` file) to the folder in which Vitis expects the current Bitstream (``ultrazohm_sw/vitis/vivado_exported_xsa``).
Usage:

Export Bitstream Tcl script
---------------------------

A Tcl script can be added to the Vivado icons to automate the process of exporting the Bitstream since it is a common task.

- ``Tools -> Custom Commands -> Customize Commands``
- Click on the `plus` and enter a name, e.g., export_xsa
- Click on ``Source Tcl file``
- Path: ``~/ultrazohm/ultrazohm_sw/tcl_scripts/vivado_export_xsa.tcl``
- Click ok

.. image:: https://images2.imgbox.com/20/97/ltbV6vKQ_o.gif

vitis\_
*******

vitis_update_platform.tcl
-------------------------

Updates the Vitis workspace after the platform, i.e., the bitstream and the ``.xsa`` file have changed.
Usage:

- Open Vitis or launch Vitis from Vivado (``Tools -> Launch Vitis IDE``)
- Choose the workspace
- Path: ``~/ultrazohm/ultrazohm_sw/vitis/workspace``
- Open the XSCT Console in Vitis: ``Windows -> Show view... -> XSCT Console``
- Type the following commands

::

   cd [getws]

::

   source {../../tcl_scripts/vitis_update_platform.tcl}

.. _vitis_gen_workspace_tcl:

vitis_generate_UltraZohm_workspace.tcl
--------------------------------------

Generates the Vitis Platform workspace for the UltraZohm.
Usage:

- Open Vitis or launch Vitis from Vivado (``Tools -> Launch Vitis IDE``)
- Choose the workspace
- Path: ``~/ultrazohm/ultrazohm_sw/vitis/workspace``
- Open the XSCT Console in Vitis: ``Windows -> Show view... -> XSCT Console``
- Type the following commands

::

   cd [getws]

::

   source {../../tcl_scripts/vitis_generate_UltraZohm_workspace.tcl}

.. _vitis_patch_freertos_bsp_tcl:

vitis_patch_UltraZohm_freertos_bsp.tcl
--------------------------------------

The FreeRTOS port of Vitis 2022.2 for the A53 lacks ``portMEMORY_BARRIER``, and without it the A53 can freeze under network load.
The same bug on the MicroBlaze port is described in `this FreeRTOS forum thread <https://forums.freertos.org/t/should-the-microblaze-freertos-port-define-portmemory-barrier/16704>`_ and fixed in `FreeRTOS-Kernel #621 <https://github.com/FreeRTOS/FreeRTOS-Kernel/pull/621>`_: without the barrier, the compiler may optimize ``xTaskResumeAll`` so that it loops forever.
This script adds the define to the FreeRTOS BSP.
You do not need to run it yourself: ``vitis_generate_UltraZohm_workspace.tcl`` and ``vitis_update_platform.tcl`` use it.

Regenerating the BSP removes the define again, e.g. after changing the BSP settings in the Vitis GUI.
You then get one of these errors:

- The FreeRTOS application does not compile: ``FreeRTOS BSP without portMEMORY_BARRIER``.
- The launch (``vitis_debug_run_UltraZohm.tcl``) stops before programming the UltraZohm, because ``FreeRTOS.elf`` is built without the define.

Workspaces generated with an older version of the scripts show the same error once.
To fix it, run ``vitis_update_platform.tcl``, or type in the XSCT console:

::

   cd [getws]
   source {../../tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl}
   platform active UltraZohm
   uz_vitis_generate_platform [getws]
   uz_vitis_build_app [getws] FreeRTOS

To start the UltraZohm anyway, create an empty file ``uz_start_without_memory_barrier.txt`` in ``ultrazohm_sw/vitis/workspace``.
The launch then only warns, and the A53 can freeze.
Delete the file once the workspace is fixed.


Startup scripts
---------------

For Ubuntu, helper scripts are available in ``ultrazohm_sw/vitis`` to simplify creating and opening the Vitis workspace.
They assume that ``xsct`` and ``vitis`` are available on ``PATH``.

run_generate_workspace.sh
^^^^^^^^^^^^^^^^^^^^^^^^^

Creates the Vitis workspace in ``ultrazohm_sw/vitis/workspace`` by running ``vitis_generate_UltraZohm_workspace.tcl`` via XSCT.
The script refuses to run if the workspace folder is not empty, except for ``create_Vitis_workspace_here.txt``.
After the workspace has been generated, it starts ``open_vitis.sh``.

Usage:

::

  cd ~/ultrazohm/ultrazohm_sw
  ./vitis/run_generate_workspace.sh

open_vitis.sh
^^^^^^^^^^^^^

Opens Vitis with the workspace preset to ``ultrazohm_sw/vitis/workspace``.
This is useful after the workspace has already been created once.

Usage:

::

  cd ~/ultrazohm/ultrazohm_sw
  ./vitis/open_vitis.sh

run_generate_workspace.bat
^^^^^^^^^^^^^^^^^^^^^^^^^^

Creates the Vitis workspace in ``ultrazohm_sw\vitis\workspace`` by running ``vitis_generate_UltraZohm_workspace.tcl`` via XSCT on Windows.
The script checks the configured Xilinx installation path, writes a log file in ``ultrazohm_sw\vitis\logs``, and refuses to run if the workspace folder is not empty except for ``create_Vitis_workspace_here.txt``.
After the workspace has been generated, it starts ``open_workspace.bat`` in a new command window.

Usage:

::

  cd C:\path\to\ultrazohm_sw
  vitis\run_generate_workspace.bat

open_workspace.bat
^^^^^^^^^^^^^^^^^^

Opens Vitis on Windows with the workspace preset to ``ultrazohm_sw\vitis\workspace``.
The script expects the configured Vitis installation to exist and can be used after the workspace has already been created.

Usage:

::

  cd C:\path\to\ultrazohm_sw
  vitis\open_workspace.bat

