.. _UltraZohmSetup:

===============
UltraZohm Setup
===============

.. toctree::
   :maxdepth: 2

Requirements
************

- Installed Xilinx toolchain (Vivado and Vitis)
- Installed Java 
- Vivado license
- Installed git
- Bitbucket account
- (Optional) Sourcetree

Aim
***

- Setup the physical connections of the UltraZohm
- :ref:`clone`
- Generate the bitstream with Vivado
- Generate the Vitis workspace
- Program the UltraZohm
- Debug the UltraZohm
- Connect the Javascope to the UltraZohm

.. _clone:

Clone the UltraZohm Repositories
********************************

- Create a folder ``ultrazohm``
- Use git bash / terminal to clone the repositories

::

   git clone https://bitbucket.org/ultrazohm/ultrazohm_sw.git


After executing the ``git clone`` commands, the following directory structure exists.

::

  ./ultrazohm/
      ultrazohm_sw


.. image:: ./img_setup/1_folder_setup_gitclone.png


.. _gen_bitstream:

Generate the bitstream with Vivado
**********************************

Open the block design
---------------------

To generate the bitstream in Vivado, open Vivado by double-clicking it.

- Open the project in ``File -> Project -> Open``
- Choose the file ``~/ultrazohm/ultrazohm_sw/vivado/project/ultrazohm.xpr``
- The project initializes
- Check if a valid Vivado license exists in ``Help -> Manage License -> View License Status``
- Click ``Open Block Design``
- The Block Design is opened (takes several minutes)

.. image:: ./img_open_block_design/1_open_project.png

.. image:: ./img_open_block_design/2_open_xpr.png

.. image:: ./img_open_block_design/3_init_project.png

.. image:: ./img_open_block_design/4_project_opened.png

.. image:: ./img_open_block_design/5_check_license.png

.. image:: ./img_open_block_design/6_license_manager.png

.. image:: ./img_open_block_design/7_open_block_design.png

.. image:: ./img_open_block_design/8_opened_block_design.png


Generate Bitstream
------------------

- Click on ``Generate Bitstream``
- Click ``Yes`` to launch synthesis and implementation
- Choose the number of CPU jobs/cores that should be used by Vivado (leave a few unused, e.g., for your OS etc.)
- Launch the run(s) by clicking ``Ok``
- The bitstream is generated. This takes **20 to 60 minutes**, depending on your PC!
- Open the implemented design after the bitstream generation is completed

.. note::

  More CPU jobs decrease the time Vivado needs to generate the bitstream. However, Vivado requires more RAM for a higher number of jobs. If you run out of RAM and your OS writes to the disk (paging file or swap), decrease the number of jobs!


.. image:: ./img_gen_bitstream/1_gen_bitstream.png

.. image:: ./img_gen_bitstream/2_impl_results.png

.. image:: ./img_gen_bitstream/3_launch_run.png

.. image:: ./img_gen_bitstream/4_starts.png

.. image:: ./img_gen_bitstream/5_generated.png

.. image:: ./img_gen_bitstream/6_open_design.png


Export Bitstream
----------------

- Export the bitstream in ``File -> Export -> Export Hardware``
- Choose ``Fixed``
- Choose ``Include bitstream``
- Choose the path to which the bitstream will be exported
- Path: ``~/ultrazohm/ultrazohm_sw/vitis/vivado_exported_xsa``
- Override the existing file
- Vivado exports the file


.. image:: ./img_exp_bit/1_export.png

.. image:: ./img_exp_bit/2_export_fixed.png

.. image:: ./img_exp_bit/3_inc_bitstream.png

.. image:: ./img_exp_bit/4_choose_path.png

.. image:: ./img_exp_bit/5_path.png

.. image:: ./img_exp_bit/6_next.png

.. image:: ./img_exp_bit/7_override.png

.. image:: ./img_exp_bit/8_finish.png

.. image:: ./img_exp_bit/9_load.png


Export Bitstream tcl-script
---------------------------

A TCL script can be added to the Vivado icons to automate the process of exporting the bitstream since it is a common task.

- ``Tools -> Custom Commands -> Customize Commands``
- Click on the `plus` and enter a name, e.g., export_xsa
- Click on ``Source Tcl file``
- Path: ``~/ultrazohm/ultrazohm_sw/tcl_scripts/vivado_export_xsa.tcl``
- Click ok

.. image:: https://images2.imgbox.com/20/97/ltbV6vKQ_o.gif


.. _genvitis:

Generate the Vitis workspace
****************************

- See pictures below for all steps!
- Navigate to ``~/ultrazohm/ultrazohm_sw/vitis/software/Baremetal/src/uz``
- Copy the file ``default_uz_global_configuration.h`` (same folder)
- Rename the file to ``uz_global_configuration.h``

.. warning:: Do not rename the file directly! Copy the file and rename the copy!

- Check that the configuration file matches your setup (see :ref:`global_configuration` for details)

.. important:: You probably have to adjust the UltraZohm version in uz_global_configuration.h by setting the define ``UZ_HARDWARE_VERSION`` to your version (e.g., ``2U``, ``3U``, ``4U``, ...)

- Open Vitis or launch Vitis from Vivado (``Tools -> Launch Vitis IDE``)
- Choose the workspace
- Path: ``~/ultrazohm_sw/vitis/workspace``
- Open the XSCT Console in Vitis: ``Windows -> Show view... -> XSCT Console``
- Type the following commands

::

   cd [getws]
   source {../../tcl_scripts/vitis_generate_UltraZohm_workspace.tcl}

- The script runs for several minutes
- The script displays `generate_UltraZohm_workspace.tcl script finished...`

.. image:: ./img_vitis_import/1_launch_vitis_vivado.png

.. image:: ./img_vitis_import/2_workspace.png

.. image:: ./img_vitis_import/4_xstc_console.png

.. note:: If the XSCT console is still not visible, press the *restore* button.

.. image:: ./img_vitis_import/5_build_workspace.png

.. image:: ./img_vitis_import/6_sucess.png


Physical Setup of the UltraZohm
*******************************

- Connect the UltraZohm to the grid
- Connect the Ethernet to your PC
- Connect the USB (JTAG) to your PC
- For UltraZohm :ref:`carrier_board_rev3`: Plug an external stop or the external stop dummy into the front panel
- For UltraZohm :ref:`carrier_board_rev4`: An external stop / dummy is not required
- Turn on the UltraZohm
- All four LEDs are turned on

.. image:: ./img_physical/physical_setup.png

Program (Debug)
***************

- Click on the red-marked windows to see the design perspective in Vitis
- Click the arrow next to the debug-icon and choose ``Debug Configurations``
- Choose ``Debug_FreeRTOS_Baremetal_FPGA``
- Click on ``Debug``
- After the first debug run, it is sufficient to click the debug-icon
- Start all processors (click on the play button)

.. image:: ./img_debug/1_vitis_show_design.png

.. image:: ./img_debug/2_debug.png

.. image:: ./img_debug/3_start_debug.png


Javascope
*********

- Setup the network settings of the Ethernet adapter, which is connected to the UltraZohm

::

   IP: 192.168.1.1
   Subnet-Mask: 255.255.255.0
   Gateway: 192.168.1.233

- See :ref:`gui`
- Go to the folder
- Start the Javascope

.. image:: https://images2.imgbox.com/99/98/KSNpOtWT_o.gif