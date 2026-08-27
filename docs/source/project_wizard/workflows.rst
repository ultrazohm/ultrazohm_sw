.. _project_wizard_workflows:

Workflows
=========

This page collects common task-oriented workflows.

Create A New Configuration
--------------------------

1. Use **File -> New**.
2. Select platform and revision.
3. Select Vivado project and block-design name.
4. Configure hardware pages.
5. Save the configuration as ``.pw.json``.
6. Generate and apply TCL.
7. Generate software.

Change An Adapter Card
----------------------

1. Open **Adapter cards**.
2. Change the slot selection.
3. Configure card-specific details.
4. Refresh TCL preview.
5. Execute or export TCL.
6. Rebuild the bitstream.
7. Regenerate software.
8. Rebuild Vitis.

Remove A Card From A Slot
-------------------------

Use **No adapter board** when the slot should be cleaned.
Then regenerate and execute TCL.

Use **Bypass** only when the slot should remain untouched.
Bypass is useful for manual experiments, but it can leave stale generated or manual content in the block design.

Run A Local Vivado Validation
-----------------------------

1. Open **TCL generation**.
2. Select **Local Vivado builds**.
3. Enable **Validate BD**.
4. Enable or disable **Save BD** depending on whether the validated design should be written.
5. Press **Execute TCL workflow**.

The workflow output shows the Vivado command output and autoscrolls to the newest messages.

Clear Stale Vivado Artifacts
----------------------------

Use **Clear local Vivado artifacts** after:

* switching branches;
* changing the base block design;
* seeing stale IP/interface errors;
* seeing unexpected address-assignment errors after previously valid designs.

The action removes common local Vivado cache/build folders.
It does not remove source-controlled design files.

Export TCL For A Workstation
----------------------------

1. Open **TCL generation**.
2. Select **Remote workstation builds**.
3. Configure remote-relevant options.
4. Press **Export TCL**.
5. Copy or execute the TCL on the workstation with Vivado.

After the workstation build, make sure the resulting hardware export is used by the Vitis workspace before regenerating software.

Generate Software After Bitstream Build
---------------------------------------

1. Make sure the Vitis platform matches the current Vivado hardware.
2. Open **Software configuration -> General**.
3. Select the source folder containing ``globalData.h``.
4. Refresh the software preview.
5. Configure driver options and visualization.
6. Press **Generate software files**.
7. Build the Vitis workspace.

Add Visualization Signals
-------------------------

1. Select the relevant hardware and software driver.
2. Open **Data visualization**.
3. Select Javascope, slow data, or both for each desired signal.
4. Generate software files.
5. Rebuild the Vitis workspace.

Program Slot CPLDs
------------------

1. Configure the Toolchain page with the Diamond Programmer executable.
2. Select adapter cards and verify CPLD program defaults.
3. Open **Slot CPLDs**.
4. Generate an ``.xcf`` programmer project file.
5. Execute from the wizard or open the ``.xcf`` in Diamond Programmer.

