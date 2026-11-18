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

Inserts ``portMEMORY_BARRIER`` into the generated ``FreeRTOSConfig.h`` of the FreeRTOS BSP.
The FreeRTOS port of Vitis 2022.2 for the A53 does not define it, and without it the A53 can freeze under network load.
``vitis_generate_UltraZohm_workspace.tcl`` and ``vitis_update_platform.tcl`` call the script after regenerating the BSP and again right before building the platform.
After the platform build, both scripts check that the FreeRTOS kernel library and the exported headers were built with the define, and stop with an error otherwise.

Every regeneration of the BSP removes the define again, also a change of the BSP settings in the Vitis GUI.
The FreeRTOS application therefore does not compile against a BSP without the define and stops with the message ``FreeRTOS BSP without portMEMORY_BARRIER``.
Before the UltraZohm is programmed, ``vitis_debug_run_UltraZohm.tcl`` checks that the kernel in ``FreeRTOS.elf`` is built with the define, and stops without touching the UltraZohm otherwise.
This also catches an outdated ``FreeRTOS.elf``, e.g. if the last build of the FreeRTOS application failed.

The checks read the compiled files, not their dates, so they do not report errors for files that are only older than others.
For this, the patch adds one byte in the section ``.uz_freertos_memory_barrier`` to every kernel object file.
The section is not loaded to the UltraZohm, and the kernel code is the same as with the define alone.
A workspace patched by an older version of the script has the define without this section, and the checks report it until the fix below has been applied once.

To fix it, type the following commands in the XSCT console (or run ``vitis_update_platform.tcl``, then clean and build the FreeRTOS application):

::

   cd [getws]
   source {../../tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl}
   platform active UltraZohm
   uz_vitis_patch_freertos_bsp [getws]
   platform generate
   uz_vitis_verify_freertos_bsp [getws]
   app clean -name FreeRTOS
   app build -name FreeRTOS

The FreeRTOS application is cleaned before it is built, because it is not linked again if only the kernel library has changed.


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

