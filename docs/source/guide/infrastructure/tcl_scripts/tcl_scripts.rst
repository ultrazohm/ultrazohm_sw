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

The Vivado scripts can be called from Vivado tcl console (``Window -> Tcl console`` in Vivado) or choose a Tcl script (``Tools -> Run Tcl script...``) as well as the command line in batch mode on linux:

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

Opens the ``ultrazohm.xpr`` Vivado project and runs to design flow to ``write_bitstream``.
Returns ``0`` if successful and ``1`` if not.

vivado\_
********

vivado_export_xsa.tcl
---------------------

Exports the Bitstream (``.xsa`` file) to the folder in which Vitis expects the current Bitstream (``ultrazohm_sw/vitis/vivado_exported_xsa``).
Usage:

Export Bitstream tcl-script
---------------------------

A TCL script can be added to the Vivado icons to automate the process of exporting the Bitstream since it is a common task.

- ``Tools -> Custom Commands -> Customize Commands``
- Click on the `plus` and ender a name, e.g., export_xsa
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
   source {../../tcl_scripts/vitis_generate_UltraZohm_workspace.tcl}