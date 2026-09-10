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

Use **File -> New** for a new wizard project.
Use **File -> Open** to open an existing ``.pw.json`` file from ``project_wizard/user_configurations/``.

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

Generate CPLD Programmer Files
------------------------------

1. Open **Slot CPLDs**.
2. Check that the proposed CPLD programs match the selected digital adapter cards.
3. Generate the programmer project file.
4. Execute it from the wizard or open it in Lattice Diamond Programmer.

For older CPLD families, the graphical Diamond Programmer workflow may be more reliable than the command-line workflow.

Configure Software
------------------

1. Open **Software configuration -> General**.
2. Select the source folder that contains ``globalData.h``, usually ``vitis/software/Baremetal/src``.
3. Choose whether each slot follows the hardware selection or should generate no software driver.
4. Open **IP core drivers setup**.
5. Keep driver options on **Default** unless the application needs custom configuration values.
6. Open **Data visualization**.
7. Select signals for Javascope, slow data, or both.

Generate Software
-----------------

1. Press **Generate software files**.
2. Confirm the warning dialog.
3. Inspect the software generation output.
4. Rebuild the Vitis workspace.

The Vitis workspace must match the current bitstream.
The generated software uses base-address macros from ``xparameters.h``; stale exported hardware can therefore result in wrong software integration.

Expected Result
---------------

After a successful quick-start flow:

* the Vivado block design validates;
* the bitstream builds if bitstream generation was selected;
* the Vitis software compiles;
* selected visualization signals are available in the configured Javascope and slow-data paths;
* saved wizard configuration can be reopened and regenerated.
