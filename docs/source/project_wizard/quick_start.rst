.. _project_wizard_quick_start:

Quick Start
===========

This quick start describes the shortest path from a new wizard configuration to a matching Vivado block design and compiling Vitis software.
It intentionally avoids deep explanations; those are covered in the later reference pages.

Prerequisites
-------------

Before starting, make sure that:

* the UltraZohm repository is checked out locally;
* Vivado and Vitis are installed for the project version used by the repository;
* Lattice Diamond is installed if slot CPLDs should be programmed from the wizard;
* the base Vivado project exists under ``vivado/project/``;
* the Vitis bare-metal source folder exists under ``vitis/software/Baremetal/src/``.

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

Configure Hardware
------------------

1. Open **Platform**.
2. Select the platform and hardware revision.
3. Use the displayed nameplate hint to identify the correct UltraZohm revision.
4. Open **Hardware configuration -> General**.
5. Select the Vivado project file, usually ``vivado/project/ultrazohm.xpr``.
6. Confirm the block-design name, usually ``zusys``.
7. Open **PWM / Timing / Interrupts** and configure the global timing values.
8. Open **Adapter cards** and select the installed cards for each A and D slot.
9. For cards with additional options, configure the card detail view.
10. Open **ADC triggers** and keep the defaults unless the application needs different trigger wiring.

When removing a card from a slot, use **No adapter board** if wizard-owned slot content should be cleaned.
Use **Bypass** only if the slot must remain untouched.

Generate And Apply Vivado TCL
-----------------------------

1. Open **TCL generation**.
2. Select either **Local Vivado builds** or **Remote workstation builds**.
3. Press **Refresh TCL preview** and inspect warnings.
4. For local builds, optionally press **Clear local Vivado artifacts** after branch changes or stale Vivado errors.
5. Press **Execute TCL workflow** for a local run, or **Export TCL** for execution on another workstation.

For a first validation, use **Validate BD** and **Save BD**.
For a complete hardware build, enable **Generate bitstream** and optionally **Export .xsa after successful build**.

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

