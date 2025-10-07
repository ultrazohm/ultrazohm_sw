.. _first_steps:

==============================
First steps with the UltraZohm
==============================

Aim of the tutorial
*******************

In this tutorial, the initial steps needed to get the UltraZohm running after cloning the repository are shown.

Requirements
************

The following tutorial requires:

- :ref:`Complete Xilinx Toolchain (Vivado, Vitis) installation <XilinxToolchain>`
- :ref:`Git installation <Git>`
- :ref:`Java installation <install_java>`
- :ref:`Cloned UltraZohm repositories from Bitbucket <clone>`
- :ref:`Generated Vitis workspace <genvitis>`
- UltraZohm connected to your PC by Ethernet and USB (JTAG)


UltraZohm Setup
***************

The UltraZohm has to be connected to a PC by Ethernet and USB (JTAG programmer).

.. image:: ./img/physical_setup.jpg

Initial steps
*************

#. Open the Git terminal inside the cloned UltraZohm repository, or alternatively do the following steps via your git client (e.g., :ref:`Sourcetree`).
#. Change your active branch from ``main`` to ``develop`` by using the **checkout** keyword (e.g., ``git checkout develop``).

   * The ``develop`` branch is the current development branch with the latest merged changes made to the UltraZohm repository. Every new feature branch will be created from this point.
   * The ``main`` branch is the latest stable version. 
   * For further information, see :ref:`contribution`. 

#. Create a new local branch with an appropriate name (e.g., *name_tutorial*) on which the changes made throughout the tutorial will be made.

   .. warning:: 

      This branch is only used locally for the tutorials. Do not push any changes to the remote repository.

#. Start **Vitis** and open up the workspace folder (``ultrazohm_sw/vitis/workspace``) of the UltraZohm repository.

   * Vitis is used to change the code for the Processor (PS). E.g., if you want to run a control algorithm on the ARM-Cortex processors of the UltraZohm, you have to make changes in Vitis.
   * Vivado is used to change the programmable logic (PL), i.e., the FPGA of the Zynq UltraScale. 

#. Review the contents of ``uz_global_configuration.h`` before building the source code

   * This file is the configuration file for the UltraZohm and has to be adjusted to your specific needs. 
   * Change the ``UZ_HARDWARE_VERSION`` to the version of *your* UltraZohm.
   * Note that on hardware version 5 or newer, potential mismatches between the define and the actual hardware version are handled by the software.
   * See :ref:`global_configuration` for further details.

#. Build the project by clicking on the red highlighted hammer visible in :numref:`build_workspace`.

   * Whenever changes have been made to the code base, this button has to be pressed.
   * If this button is not pressed after changes have been made, these changes can't be flashed onto the UltraZohm, and the previously built binary is programmed (without the changes!).

   ..  _build_workspace:
   ..  figure:: ./img/build_workspace.png
       :align: center

       Building the workspace

#. The build can fail, leading to errors as exemplarily depicted below.

   * Whenever you make changes to the codebase and the build leads to errors, they have to be fixed, otherwise, the UltraZohm cannot be flashed properly. This is because the errors stop the compiler from compiling the entire workspace.
   * While Warnings do not prohibit the UltraZohm from working, they should be fixed nonetheless.

   ..  _workspace_error:
   ..  figure:: ./img/workspace_error.png
       :align: center

       Errors after building the workspace

#. Our build is successful.
#. Flash the UltraZohm by either pressing the run icon in the green highlighted area in :numref:`debug_config` and select *Debug Configurations...*. Vitis will remember the last selection, which means that for a future flashing operation, the last debug config is already preselected. 
#. Use the ``Run_UltraZohm`` configuration for the debug/run selection.

   ..  _debug_config:
   ..  figure:: ./img/debug_config.png
       :align: center

       Debug configuration in Vitis.

#. If the flashing was successful, the **Ready LED** will blink slowly.
#. Make sure that you have configured your Ethernet-to-USB adapter according to :ref:`this guide <GUI_network>`.
#. Start the **uz_GUI** in the folder ``ultrazohm_sw/javascope`` by double-clicking on the ``UZ_GUI.jar`` file or executing the ``javascope_run.bat`` file.

#. Press the **Connect** button in the GUI. Now the GUI should be up and running. 

   * If the connection was successful, the field to the left of the IP address is moving. 
   * If nothing happens, check out the :ref:`known issues section <GUI_network>`.

#. Five default channels are visible in the scope after pressing the *sendSelectData (all)* button. 

   * To get the signals into the scope view, adjust the scaling of the first three channels.
   * Adjust the time base of the scope via the *setTime* button and the dropdown menu to ``x10``.
   * FYI, the values for the channels *theta_mech* and *ua* are, in the default case, 0.

   ..  _GUI_connected:
   ..  figure:: ./img/GUI_connected.png
       :align: center

       Visible signals after GUI has been connected.

#. Get yourself familiar with the GUI by trying different things in the GUI. For further information, read the :ref:`sections about the Setup Scope Page, Control Page, and Logging Panel <JavaScope>`.
#. In the next tutorial, changes will be made to the codebase, and the GUI will be customized.
