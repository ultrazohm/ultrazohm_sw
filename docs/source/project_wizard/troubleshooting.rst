.. _project_wizard_troubleshooting:

Troubleshooting
===============

Missing Toolchain Path
----------------------

If an action requires Vivado or Diamond Programmer and the path is empty, the wizard shows a warning and navigates to the Toolchain page.

Fix:

* configure the missing executable path;
* rerun the action.

Missing Software Source Folder
------------------------------

Software generation requires a folder containing ``globalData.h``.

Fix:

* open **Software configuration -> General**;
* select ``vitis/software/Baremetal/src`` or the matching source folder for the project.

No Visualization Signals Shown
------------------------------

Visualization signals are generated from the current hardware and software model.

Possible causes:

* the slot software mode is set to no software driver;
* the selected card has no generated software signal;
* a card channel is disabled;
* the relevant card option is not AXI/software-backed;
* the view has not been refreshed after a card change.

Fix:

* check slot software mode;
* check card details;
* refresh previews or reopen the configuration.

Vivado Reports Stale IP Or Interface Errors
-------------------------------------------

This often happens after switching branches or changing a base block design in the same local repository.

Fix:

* close Vivado;
* press **Clear local Vivado artifacts**;
* reopen or rerun the TCL workflow.

AXI Address Assignment Fails
----------------------------

Possible causes:

* stale AXI content in a slot;
* the slot was set to Bypass instead of No adapter board;
* manual block-design content conflicts with generated attachment points;
* the generated TCL was applied to a different base design than expected.

Fix:

* use **No adapter board** for slots that should be cleaned;
* rerun the generated TCL;
* inspect the local slot hierarchy and upstream SmartConnects in Vivado;
* rebuild/export hardware before regenerating software.

Software Builds With Wrong Base Address
---------------------------------------

The software generator uses macros from ``xparameters.h``.
If the Vitis platform is stale, generated software can compile but point to an old or wrong address.

Fix:

* rebuild or update the hardware platform after Vivado changes;
* regenerate software after the hardware platform is current.

Generate Software Files Overwrites My Code
------------------------------------------

Normal Project Wizard marker blocks are overwritten by design.
Only explicit Project Wizard user blocks are preserved.

Fix:

* keep application code outside normal wizard marker blocks;
* use preserved user blocks where provided;
* if a generated section needs permanent customization, add a wizard option or template change.

Bypass Did Not Clean A Slot
---------------------------

This is expected.
Bypass means leave the slot untouched.

Fix:

* select **No adapter board** if wizard-owned slot content should be removed.

CPLD CLI Programming Fails
--------------------------

Older CPLD workflows may be less reliable through the command-line interface.

Fix:

* generate the ``.xcf`` file;
* open it manually in Lattice Diamond Programmer;
* verify cable, port address, and selected device chain.

TCL Preview Contains Template Markers
-------------------------------------

Generated TCL must not contain template markers such as ``{%`` or ``{{``.
If these appear, the generator or template has a bug.

Fix:

* do not execute the TCL;
* report or fix the template/generator issue;
* run the golden scenario checks after the fix.

