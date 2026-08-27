.. _project_wizard_generated_outputs:

Generated Outputs And Ownership
===============================

The wizard deliberately separates saved user configuration from generated output.
Understanding this distinction prevents accidental overwrites and confusing Vivado or Vitis states.

Saved Configuration
-------------------

Saved configuration files are stored in:

``project_wizard/user_configurations/``
   User-owned ``.pw.json`` files.

These files describe the intended setup.
They are not generated output and should be treated like project configuration files.

Generated Wizard Files
----------------------

Generated files are stored below:

``project_wizard/generated/``
   Root folder for wizard-generated helper files.

Important subfolders:

``vivado_bd_config/``
   Generated block-design TCL.

``vivado_run_scripts/``
   Local Vivado wrapper scripts.

``cpld_config/``
   Generated Lattice Diamond Programmer ``.xcf`` files.

``logs/``
   Local workflow logs.

``golden_scenarios/``
   Developer regression baselines.

Vivado Ownership
----------------

The wizard owns selected block-design regions.
Manual edits inside those regions may be overwritten or removed when the wizard regenerates the design.

Wizard-owned regions:

* selected A-slot hierarchies below ``uz_analog_adapter``;
* selected D-slot hierarchies below ``uz_digital_adapter``;
* generated slot-local AXI integration for wizard-controlled slots;
* the generated ``uz_pwm`` hierarchy.

The wizard assumes these surrounding base-design hierarchies already exist:

* ``uz_system``;
* ``uz_user``;
* ``uz_analog_adapter``;
* ``uz_digital_adapter``.

Manual content outside the wizard-owned regions can coexist with wizard-generated content.
However, manual legacy content can still influence validation or address assignment if it connects to the same interfaces.

Vitis Ownership
---------------

The software generator writes slot-specific files and patches shared files inside explicit marker blocks.

Generated slot files:

* ``include/a1_adapter_init.h`` to ``include/a3_adapter_init.h``;
* ``include/d1_adapter_init.h`` to ``include/d5_adapter_init.h``;
* ``hw_init/a1_adapter_init.c`` to ``hw_init/a3_adapter_init.c``;
* ``hw_init/d1_adapter_init.c`` to ``hw_init/d5_adapter_init.c``.

Shared marker-patched files include:

* ``globalData.h``;
* ``main.c``;
* ``sw/isr.c``;
* ``include/javascope.h``;
* ``sw/javascope.c``;
* ``uz/uz_global_configuration.h``;
* ``IP_Cores/uz_dataMover/uz_dataMover.c``.

Marker blocks look like:

.. code-block:: c

   /* Project Wizard BEGIN: example */
   /* generated content */
   /* Project Wizard END: example */

Normal Project Wizard marker blocks are overwritten on regeneration.

Preserved User Blocks
---------------------

Some generated software sections are inserted as user-owned blocks.
These are generated once and preserved on later regeneration.

Example:

.. code-block:: c

   /* Project Wizard USER BEGIN: D1 axi_gpio_outputs */
   static void update_axi_gpio_d1_outputs(void)
   {
       uz_axi_gpio_set_output_pin_to(Global_Data.objects.axi_gpio_d1, DIG_24, LOW);
   }
   /* Project Wizard USER END: D1 axi_gpio_outputs */

User code inside these blocks is preserved.
The wizard may recreate a missing user block, but it does not intentionally overwrite existing user code inside such blocks.

Safe Manual Edits
-----------------

Safe places for manual edits:

* application code outside Project Wizard marker blocks;
* code inside Project Wizard user blocks;
* manual Vivado content outside wizard-owned slot and PWM regions;
* saved wizard configuration files.

Unsafe places for manual edits:

* normal Project Wizard marker blocks;
* generated slot init files when the slot is still wizard-controlled;
* wizard-owned Vivado slot hierarchies;
* generated TCL files that will be overwritten by a later export.

If manual changes are needed permanently, prefer adding the option to the wizard configuration, card catalog, or template.

