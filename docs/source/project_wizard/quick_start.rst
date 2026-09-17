.. _project_wizard_quick_start:

Quick Start
===========

This quick start describes the shortest path from a new wizard configuration to a matching Vivado block design and compiling Vitis software.
It intentionally avoids deep explanations; those are covered in the later reference pages.

Prerequisites
-------------

Before starting, make sure that:

* the UltraZohm repository ``ultrazohm_sw`` is checked out locally;
* Python is installed and available from the terminal (tested with Python 3.12);
* the Project Wizard Python dependencies, i.e., ``PyQT6``, are installed with ``pip install -r project_wizard/requirements.txt``;
* Vivado and Vitis are installed for the project version used by the repository;
* Lattice Diamond is installed if slot CPLDs should be programmed from the wizard;
* The ``cpld_lattice`` repository is checked out locally.

Start The Wizard
----------------

On Windows:

.. code-block:: powershell

   cd project_wizard
   .\run_project_wizard.bat

On Linux:

.. code-block:: bash

   cd project_wizard
   ./start_project_wizard.sh

Create Or Open A Configuration
------------------------------

| Use **File -> New** for a new wizard project.
| Use **File -> Open** to open an existing ``.pw.json`` file from ``project_wizard/user_configurations/``. 
| (Screenshots below will show the UltraZohm default configuration that is provided in the repository in ``project_wizard/user_configurations/project_wizard_config.pw.json``.)

Save the configuration early with **File -> Save As**.
The wizard configuration is user-owned project state and is not a generated output file.

Configure Toolchain and Platform
--------------------------------

1. After starting the Project Wizard the **Toolchain** page is already open. Press the **Detect Toolchain** button to let the Project Wizard automatically check for the paths to your local Vivado/Vitis and Diamond Programmer installation. The path to the CPLD repository **cpld_lattice** has to be provided manually in any case.

.. figure:: img/quickstart/toolchain.png
   :width: 800
   :align: center

   Toolchain page of the Project Wizard

2. Open **Platform** and select the platform and hardware revision. Use the displayed nameplate hint to identify the correct UltraZohm revision.

.. figure:: img/quickstart/platform.png
   :width: 800
   :align: center

   Platform page of the Project Wizard

Configure Hardware
------------------

3. Open **Hardware configuration -> General**. The Vivado project file, usually ``$yourrepopath$/vivado/project/ultrazohm.xpr`` should be already set automatically. Confirm **Block design name**, usually ``zusys``.

.. figure:: img/quickstart/hardware_general.png
   :width: 800
   :align: center

   Hardware configuration -> General page of the Project Wizard

4. Open **PWM / Timing / Interrupts** and configure the global timing values.

.. figure:: img/quickstart/pwm_timing_interrupts.png
   :width: 800
   :align: center

   Hardware configuration -> PWM / Timing / Interrupts page of the Project Wizard

5. Open **Adapter cards** and select the installed cards for each A and D slot. For cards with additional options, configure the card details view.

.. figure:: img/quickstart/adapter_cards.png
   :width: 800
   :align: center

   Hardware configuration -> Adapter Cards page of the Project Wizard

6.  Open **ADC triggers** and keep the defaults unless the application needs different trigger wiring.

.. figure:: img/quickstart/adc_triggers.png
   :width: 800
   :align: center

   Hardware configuration -> ADC triggers page of the Project Wizard

Generate And Apply Vivado TCL
-----------------------------

7. Open **TCL generation**. Select either **Local Vivado builds** or **Remote workstation builds**. Press **Refresh TCL preview** and inspect warnings. 
For local builds, optionally press **Clear local Vivado artifacts** after branch changes or stale Vivado errors. Press **Execute TCL workflow** for a local run, 
or **Export TCL** for execution on another workstation. For a first validation, use **Validate BD** and **Save BD**. For a complete hardware build, 
enable **Generate bitstream** and optionally **Export .xsa after successful build**.

.. figure:: img/quickstart/tcl_generation.png
   :width: 800
   :align: center

   Hardware configuration -> TCL generation page of the Project Wizard

- **Local Vivado builds:** When using your local machine be aware that this might take up to ``over 1 hour`` for a complete bitstream generation. 
  When pressing ``Execute TCL workflow`` a save dialog appears within the folder ``/generated/vivado_bd_config/``. Here, the TCL file ``project_wizard_config.tcl`` 
  will be saved that handles the block design modifications. After saving it the local Vivado build starts. 
  The TCL console outputs are displayed in the ``TCL preview warnings and workflow output`` section. In the lower left corner of the window 
  ``Running Vivado TCL workflow...`` will be shown during the execution. After successful execution a message box will appear ``Vivado finished successfully.``.
  If ``Run Vivado in GUI mode`` is selected, the success message will only appear after you manually close Vivado.

- **Remote workstation builds:** When using a workstation or any kind of remote computer, this workflow only exports the TCL file without 
  calling your local Vivado instance. When pressing ``Export TCL`` a save dialog appears within the folder ``/generated/vivado_bd_config/``. 
  Here, the TCL file ``project_wizard_config.tcl`` will be saved that handles the block design modifications. After saving you will have to 
  copy that TCL file to your remote computer. There, open Vivado and the UltraZohm project ``ultrazohm_sw/vivado/project/ultrazohm.xpr``. 
  Open the block design. Execute the TCL script ``project_wizard_config.tcl`` via ``Tools -> Run TCL script...``.

  **After the TCL script finished you will need to manually validate the block design, start bitstream generation, and export the resulting .xsa file.**

Generate CPLD Programmer Files
------------------------------

8. Open **Slot CPLDs**. Check that the proposed CPLD programs match the selected digital adapter cards.
Generate the programmer project file. Execute Diamond Programmer Command-Line Interface (CLI) from the wizard or open the project file in Lattice Diamond Programmer. 
Be aware that the CLI workflow is only tested with MACHXO2 CPLDs that are used from UltraZohm Rev05 and higher.

.. figure:: img/quickstart/slot_cplds.png
   :width: 800
   :align: center

   Hardware configuration -> Slot CPLDs page of the Project Wizard

Configure Software
------------------

9. Open **Software configuration -> General**. Check if the source folder that contains ``globalData.h``, usually ``vitis/software/Baremetal/src``, is already selected.

.. figure:: img/quickstart/sw_general.png
   :width: 800
   :align: center

   Software configuration -> General page of the Project Wizard

10. Open **Software configuration -> IP core driver setup**. Choose whether each slot follows the hardware selection or should generate no software driver. Keep Mode options on **Follow hardware selection** and Presets on **Default** unless the application needs differently.

.. figure:: img/quickstart/ip_core_driver_setup.png
   :width: 800
   :align: center

   Software configuration -> IP core driver setup page of the Project Wizard

11. Open **Software configuration -> Advanced driver configuration**. Check the config parameters for each adapter card driver. Select Config mode **Custom** if you need to set specific parameters.

.. figure:: img/quickstart/advanced_driver_config.png
   :width: 800
   :align: center

   Software configuration -> Advanced driver configuration page of the Project Wizard

12. Open **Software configuration -> Data visualization**. Select signals for Javascope, slow data, or both. 

.. figure:: img/quickstart/data_visualization.png
   :width: 800
   :align: center

   Software configuration -> Data visualization page of the Project Wizard

Generate Software
-----------------

1. Press **Generate software files**.
2. Confirm the warning dialog if present.
3. Inspect the software generation output.
4. Rebuild the Vitis workspace.

The Vitis workspace must match the current bitstream.
The generated software uses base-address macros from ``xparameters.h``; stale exported bitstream can therefore result in wrong software integration.
However, fallback base-addresses are used, that usually match wizard placed IP-Cores, if the Vitis workspace has not been updated with the recently generated bitstream. 

Expected Result
---------------

After a successful quick-start flow:

* the Vivado block design validates;
* the bitstream builds if bitstream generation was selected;
* the Vitis software compiles;
* selected visualization signals are available in the configured Javascope and slow-data paths;
* saved wizard configuration can be reopened and regenerated.
