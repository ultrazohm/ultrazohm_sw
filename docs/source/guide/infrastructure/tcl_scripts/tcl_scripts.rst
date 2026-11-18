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


Command-line workspace operations
---------------------------------

``vitis_headless.tcl`` is the shared XSCT entry point for workspace generation,
building, and JTAG programming. The Makefile and Windows batch wrappers in
``vitis/`` delegate to it. It resolves the workspace relative to its own location, so callers
can use an absolute script path from any working directory.

With Vitis 2022.2's ``xsct`` on ``PATH``, run from the repository root:

.. code-block:: text

   xsct -nodisp tcl_scripts/vitis_headless.tcl generate
   xsct -nodisp tcl_scripts/vitis_headless.tcl build
   xsct -nodisp tcl_scripts/vitis_headless.tcl flash Run_UltraZohm
   xsct -nodisp tcl_scripts/vitis_headless.tcl open

On Windows, use ``xsct.bat`` if required by the command shell. No Bash or Make
installation is needed for direct XSCT invocation. Native Windows build and
hardware programming still require validation.

Windows convenience wrappers are also available. From the repository root in
Command Prompt:

.. code-block:: bat

   vitis\run_generate_workspace.bat
   vitis\open_workspace.bat
   vitis\build_and_flash.bat

The first creates/builds an empty workspace and opens Vitis (``generate-open``).
The second opens an existing workspace. The third incrementally builds, then
programs and runs over JTAG (``flash``), defaulting to ``Run_UltraZohm``; this
profile can also be passed explicitly. Close Vitis before building/flashing.
The wrappers locate the Tcl script relative to themselves, forward its exit
status, and require ``xsct.bat`` on ``PATH``. Set the ``XSCT`` environment
variable to an alternative launcher path if needed. In PowerShell, prefix the
commands with ``.\``.

``generate`` creates and builds an empty workspace; only the placeholder file
``create_Vitis_workspace_here.txt`` may already exist. ``generate-open`` also
starts the GUI after successful generation. ``open`` launches the GUI for an
existing workspace. Both GUI actions require ``vitis`` on ``PATH`` and return
after launching it.

``flash`` (also accepted as ``run``) incrementally builds first, then programs
and runs through JTAG using the existing ``Run_UltraZohm`` profile. It does not
write persistent flash storage. Debug profiles require the Vitis GUI. Build or
programming failures return a nonzero status. Programming requires the vendor
environment (including ``XILINX_VITIS``), JTAG drivers, and a local hardware
server at ``127.0.0.1:3121``.

Ubuntu users can use the convenience Makefile:

.. code-block:: bash

   make -C vitis generate
   make -C vitis build
   make -C vitis flash
   make -C vitis open

``generate-open``, ``run``, and ``build-run`` are also available. ``XSCT`` can
select another executable and ``PROFILE`` defaults to ``Run_UltraZohm``.
Close Vitis before modifying the workspace and do not run separate workspace
operations concurrently.
