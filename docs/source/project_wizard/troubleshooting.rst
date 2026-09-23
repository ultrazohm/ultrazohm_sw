.. _project_wizard_troubleshooting:

Troubleshooting
===============

Missing Toolchain Path
----------------------

If an action requires Vivado or Diamond Programmer and the path is empty, the wizard shows a warning and navigates to the Toolchain page.

Fix:

* configure the missing executable path;
* rerun the action.

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

How to use the 26tx_w_enable CPLD programs on the D-slots
---------------------------------------------------------

.. warning:: In former block designs there was a hard coded wiring for using the output enable mechanism of the tx26_w_enable CPLD program. This has been removed from the block design. For creating the similar functionality via the project wizard, use the IO configuration shown below.

.. figure:: img/page_references/26tx_w_enable_io.png
   :width: 800
   :align: center

   26tx_w_enable IO configuration

The ``tx26_w_enable`` CPLD program is currently not selectable in the project wizard. If one needs to use it, it has to be manually 
deployed to the UltraZohm via Diamond Programmer.