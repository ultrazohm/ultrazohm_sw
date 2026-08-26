# Project Wizard AI Handoff

This file captures project-specific knowledge for future AI/code-assistant sessions. Read it before making changes to the Project Wizard or the wizard-owned Vivado/Vitis flow.

## 1. Project Architecture

### Repository Context

- Main repo: UltraZohm software/Vivado/Vitis repository.
- Wizard path: `project_wizard/`.
- Main saved wizard config: `project_wizard/user_configurations/project_wizard_config.pw.json`.
- Vivado block design target: `vivado/project/zusys/zusys.bd`.
- Vitis bare-metal sources: `vitis/software/Baremetal/src/`.
- Neighbor reference repos used during development:
  - `../ultrazohm_sw_ZC_test_2`
  - `../ultrazohm_sw_pcim2024`

### Languages And Tools

- GUI: Python + PyQt.
- Hardware generation: Tcl templates emitted by Python.
- Software generation: C/H templates emitted by Python and marker-based patching.
- Data catalogs: JSON files in `project_wizard/data/`.
- Template engine: local `SimpleTemplateRenderer` in `project_wizard/template_renderer.py`.
- CPLD programming: Lattice Diamond Programmer `.xcf` generation and CLI execution.
- Vivado/Vitis: Xilinx Vivado 2022.2 style block design and Vitis bare-metal workspace.

### Important Wizard Files

- `project_wizard/views/main_window.py`
  - Main PyQt shell: menu, service wiring, navigation stack, and page registration.
- `project_wizard/views/mixins/`
  - Focused GUI page/workflow modules used by `MainWindow`.
- `project_wizard/data/adapter_cards.json`
  - Hardware/card catalog: compatible slots, Vivado templates, IP VLNVs, ports, AXI interfaces, constraints, default CPLD program.
- `project_wizard/data/software_drivers.json`
  - Software driver catalog: generated C/H templates and advanced driver config fields.
- `project_wizard/data/platforms.json`
  - Platform defaults, AXI defaults, revision choices.
- `project_wizard/tcl_generator.py`
  - High-level Tcl generation coordinator.
- `project_wizard/services/software_generator_service.py`
  - Model-based Vitis software integration generator.
- `project_wizard/services/software_analog.py`
  - Analog-card software contexts, ADC readout snippets, ADC packed-buffer offsets, and DAC wavegen helper logic.
- `project_wizard/services/software_models.py`
  - Software-generation plan dataclasses, marker definitions, and small shared constants.
- `project_wizard/services/software_driver_config.py`
  - Reusable driver-configuration value resolution for default/custom advanced driver options.
- `project_wizard/services/software_digital.py`
  - Digital-card software contexts and generated snippets for inverter, incremental encoder, absolute encoder, and resolver integrations.
- `project_wizard/services/software_patcher.py`
  - Marker-based Vitis file patching and generated software file writes.
- `project_wizard/services/software_pwm.py`
  - PWM software config fields, PWM init context, PWM runtime ISR lines, and PWM-owned RASV duty-cycle entries.
- `project_wizard/services/software_temperature_io.py`
  - Temperature-card software context, temperature readout snippets, AXI GPIO IO-card context, and generated Arduino-style IO wrapper files.
- `project_wizard/services/software_visualization.py`
  - Formatting of generated visualization fields, Javascope observable entries, and slow-data entries.
- `project_wizard/services/xparameters.py`
  - `xparameters.h` discovery and generated base-address/device-id macro selection.
- `project_wizard/services/visualization_catalog.py`
  - Shared visualization signal catalog plus IO-card direction/AXI helper functions.
- `project_wizard/services/cpld_programmer_service.py`
  - `.xcf` generation and Diamond Programmer CLI handling.
- `project_wizard/services/vivado_service.py`
  - Vivado TCL execution wrapper.
- `project_wizard/models.py` and `project_wizard/services/system_resolver.py`
  - Typed config/resolver boundary for wizard workflows.

### Current Data Model

Project configuration uses schema version 2 and is loaded through `SystemConfig`.
The saved `.pw.json` has typed top-level sections:

- `platform`: `{id, revision, cpld}`
- `slots`: per-slot `{card, options, cpld}`
- `software`: `{source_dir, modes, presets, visualization_routes, driver_config, extra}`
- `toolchain`
- `hardware`
- `cpld_programmer`
- `axi`

The application boundary is:

```text
GUI widget state / saved JSON
  -> typed SystemConfig
  -> ResolvedSystemModel
  -> Tcl/Software/CPLD generators
```

Generator public APIs are model-based. Legacy-shaped dictionaries remain only as
private implementation details inside generators where they preserve proven
behavior.

Resolver-owned facts currently include:

- Resolved slots, card metadata, and selected option choices.
- Card-derived default CPLD programs and selected slot CPLD programs.
- Software-driver instance discovery for advanced driver configuration.
- Available visualization signal discovery for the GUI.
- Analog datamover streams, packed offsets, channel count, and data width.
- Slot-local AXI cleanup/attachment facts and AXI interface lists.
- Shared IO-card direction/AXI participation helpers through
  `services/visualization_catalog.py`.

The remaining high-risk area is dirty Vivado BD transition behavior around AXI
cleanup/attachment. The facts are resolver-owned and the Tcl is golden-tested,
but actual dirty-BD cleanup still needs manual Vivado testing when changed.

Current platform-scope note:

- Leave existing `uz_` hardcoded Tcl/software names as-is for now. The current generators intentionally target the UltraZohm Vivado/software architecture (`uz_system`, `uz_user`, `uz_analog_adapter`, `uz_digital_adapter`, `uz_pwm`, `uz_*` drivers, `UZ_*` defines). Platform combo entries for future platforms should not imply that this naming has already been abstracted. Future MicroZohm/Kria support will need a deliberate platform-naming/configuration abstraction.

## 2. Established Methods And Coding Rules

### General Coding Rules

- Prefer existing patterns and helpers over inventing new ones.
- Use `rg` for search.
- Use `apply_patch` for manual edits.
- Do not rewrite unrelated user changes.
- Keep generated and wizard-owned code visibly marked with `Project Wizard` comments where useful.
- Use ASCII for new source content unless the file already requires otherwise.
- Run at least:
  - `python -m json.tool project_wizard/data/adapter_cards.json`
  - `python -m json.tool project_wizard/data/software_drivers.json`
  - `python -m compileall project_wizard`
- Remove `__pycache__` folders after compile checks.

### Vivado Tcl Patterns

Use helpers from `project_wizard/templates/helpers/bd_helpers.tcl`. Do not hand-roll new variants unless a missing helper is genuinely needed.

Template rendering rule:

- Generated Tcl must never contain unresolved template syntax such as `{% if ... %}`, `{% endif %}`, `{% for ... %}`, `{% endfor %}`, or `{{ variable }}`.
- Vivado/Tcl reports these leaks as confusing runtime errors such as `invalid command name "% endif %"`.
- This has happened repeatedly during generator development. Always scan generated Tcl for `"{%"` and `"{{"` after changing templates or `SimpleTemplateRenderer`.
- The local `SimpleTemplateRenderer` is intentionally small. It now supports nested `{% if %}` blocks by reducing innermost `if` blocks first, but it is still not a full Jinja engine. Keep templates simple, and add renderer smoke tests when introducing new control-flow shapes.
- Especially check disabled-option paths such as PWM debug ILA unchecked, because these paths can expose leaked closing tags that are hidden when the option is enabled.

Proven signal-through-hierarchy pattern:

1. Create/reuse the parent hierarchy.
2. Create/reuse the child hierarchy.
3. Create boundary pins at every hierarchy level using `uz_pw_create_hier_pin_if_missing`.
4. Connect source to parent boundary with `uz_pw_connect_pin_pair_if_unconnected` or `uz_pw_connect_upper_boundary_net_if_unconnected` depending hierarchy level.
5. Connect parent boundary to child boundary with `uz_pw_connect_upper_boundary_net_if_unconnected`.
6. Connect child boundary to IP pin with `uz_pw_connect_pin_pair_if_unconnected`.
7. For top-level ports, use:
   - `uz_pw_create_bd_port_if_missing`
   - `uz_pw_connect_port_if_unconnected`

Important helpers:

- `uz_pw_connect_pin_pair_if_unconnected`
- `uz_pw_connect_net_if_unconnected`
- `uz_pw_connect_upper_boundary_net_if_unconnected`
- `uz_pw_connect_port_if_unconnected`
- `uz_pw_connect_intf_if_unconnected`
- `uz_pw_delete_child_cells_in_slot_hierarchy`
- `uz_pw_apply_slot_constraints`
- `uz_pw_disable_slot_constraints`

Do not create partial interface paths in one place and complete paths in another. AXI interface connections through hierarchies should be made consistently using the established AXI helper flow.

Slot-boundary pin naming rule:

- Every generated hierarchy pin or boundary pin must carry the slot prefix, e.g. `D3_...`, unless it is a fixed external adapter port such as `Dig_00_Ch3`.
- Do not derive intermediate boundary pin names from generic source leaf names such as `Gate_Signals_2L_0` or `Enable_Gate`. Slot changes rely on cleanup patterns like `*D3*`; generic names become stale pins under `uz_digital_adapter`.
- Before inventing a new signal-routing strategy, compare against the already-tested templates, especially inverter, incremental encoder, and resolver. Reuse their helper pattern unless there is a concrete technical reason not to.
- For PWM/gate routing, prefer the proven vector-through-hierarchy approach: route `uz_pwm/Gate_Signals_2L_x` into the slot hierarchy as a slot-prefixed vector boundary pin and slice locally if scalar pins are needed.

### Wizard Ownership Rule

The wizard owns:

- `uz_analog_adapter/Ax_adapter` contents for selected A slots.
- `uz_digital_adapter/Dx_adapter` contents for selected D slots.
- `uz_pwm` hierarchy and its `pwm_2L` / `pwm_3L` subhierarchies.
- Generated marker blocks in Vitis C/H files.
- Slot-specific adapter init sections in `*_adapter_init.c/.h`.

The wizard assumes these top-level hierarchies already exist:

- `uz_analog_adapter`
- `uz_digital_adapter`
- `uz_pwm` after PWM generation, or created by the PWM template.
- `uz_system`
- `uz_user`

Legacy pins under top-level adapter hierarchies can cause confusion. If a pin belongs to stale, non-wizard logic, remove it manually or extend cleanup intentionally.

### AXI Rules

- Prefer automatic Vivado address assignment for AXI4-Lite IPs.
- Do not keep fixed address offsets unless there is a proven system-level reason.
- Software must read final base address macros from `xparameters.h`.
- Fallback base address macros are only fallback/warning paths; a real exported Vitis workspace should provide the actual macro.
- Local SmartConnects are used per slot or per subsystem where appropriate:
  - A slots have their own A-slot attachment flow.
  - D slots use D-slot attachment.
  - PWM has `pwm_2L` and `pwm_3L` SmartConnects.

### Constraint Rules

- A-slot constraints are card-specific:
  - LTC2311 uses `Analog_Ax_packed.xdc`.
  - MAX11331 uses `Analog_Ax_ADC_MAX11331.xdc`.
  - DAC8831 uses DAC-specific constraints.
- Digital slots:
  - Packed constraints are used for packed/generic adapters.
  - Inverter and incremental encoder use `Digital_AdapterBoard_Dx.xdc` and disable `Digital_Dx_packed.xdc`.
- Wizard Tcl must explicitly enable/disable constraints so the wizard setting wins.
- The TE0803 constraint path is untested; TE0808 is the main proven path.

### Vivado Checkpoint Workaround

Vivado 2022.2 sometimes crashes while writing DCP/checkpoints with the inverter-adapter setup. The reliable workaround was to set BD synth checkpoint mode to none for `zusys.bd`.

- This is exposed as a checkbox in the hardware/general UI.
- The Tcl must set both enabled and disabled states explicitly where possible.
- The working behavior was achieved by applying the property after BD construction and before validation/build reset. Avoid moving this casually.

### Vitis Software Generation Rules

- Existing driver code is usually already written in `vitis/software/Baremetal/src/IP_Cores/...`.
- The wizard integrates drivers; it should not rewrite driver internals except for small compatibility fixes.
- Slot files:
  - `include/a1_adapter_init.h` ... `include/d5_adapter_init.h`
  - `hw_init/a1_adapter_init.c` ... `hw_init/d5_adapter_init.c`
- Marker-patched files include:
  - `globalData.h`
  - `main.c`
  - `sw/isr.c`
  - `include/javascope.h`
  - `sw/javascope.c`
  - `uz/uz_global_configuration.h`
  - `IP_Cores/uz_dataMover/uz_dataMover.c`
- Instance count defines in `uz_global_configuration.h` must match selected wizard drivers.
- If `MAX_INSTANCES` can be `0U`, the driver must compile with `0U`. We already fixed this for the LTC2311 private utilities.

### Visualization Rules

- Visualization supports both:
  - fast Javascope observable path
  - slow-data path
- Current UI uses independent checkboxes so a signal can be routed to no path, one path, or both paths.
- Non-float signals are converted through generated `project_wizard_visualization_data` fields.
- Boolean values become `1.0f` / `0.0f`; integer values are cast to float.

### Naming Conventions

- Wizard name: `Project Wizard`.
- Do not reintroduce `xz`, `xZohm`, or `xz_project_wizard` naming.
- Generated helper names use `project_wizard_...`.
- A-slot IP names are slot-specific, e.g. `A1_ADC_LTC2311`.
- D-slot IP names should be slot-specific where practical, e.g. `incremental_encoder_d1`.
- Source fields should use explicit block-design pin paths, e.g. `uz_system/trigger_conversions`.

## 3. Present Project State

### Stable/Tested Milestones

#### CPLD Programming

- `.xcf` generation works.
- Diamond Programmer CLI flashing works on the user's machine.
- USB ID can be left empty; Port address matters.
- Cable recovery/import flow exists.
- Log highlighting exists.
- Rev04 ispMACH workflow exists but is not fully tested.
- MachXO2 Rev05+ workflow is the main target.

#### A-Slot Cards

All currently known A-slot cards are implemented:

- `Analog LTC2311-16`
- `Analog MAX11331`
- `Analog DAC8831`

Tested:

- A1/A2/A3 LTC2311 generated bitstream and real hardware ADC readout.
- Edge case A1 empty, A2/A3 LTC2311 worked in hardware.
- No A-slot ADC case handled by fallback AXI2TCM trigger/zero input logic.
- A1/A3 LTC2311 + A2 DAC8831 built and worked on hardware.
- A1 LTC2311 + A2 DAC8831 + A3 MAX11331 built and had first successful readouts.
- MAX11331 valid trigger changed from `meas_done` to `new_data`.

Important A-slot architecture:

- ADC data streams are packed into AXI2TCM via concat.
- LTC2311 contributes 8 channels x 16 bit.
- MAX11331 contributes 24 channels x 16 bit.
- AXI2TCM minimum safe channel count is 2.
- If no ADC source exists, a zero constant feeds AXI2TCM.
- Trigger source defaults to an available RAW_Valid signal or direct conversion trigger fallback.

#### DAC Runtime

- DAC8831 output can be constant or generated through wavegen functions.
- Wavegen architecture was updated to instance-based objects.
- Wavegen instance pointers are stored in `Global_Data.objects` for future runtime/Javascope access.
- Runtime Javascope edit of wavegen parameters was discussed but intentionally deferred.

#### D-Slot Inverter Adapter

- `UZ_D 3-phase inverter` is implemented for D slots.
- The original mapping IP was avoided/replaced with direct slice/concat logic because IP metadata caused Vivado issues.
- Gate source and PWM enable source are configurable.
- Default gate source uses `uz_pwm/Gate_Signals_2L_0`.
- Gate input is fixed to 6 signals; do not reintroduce configurable slice-from/to fields.
- Top-level ports use `Digital_AdapterBoard_Dx.xdc` style names.
- `Dig_16` was restored/aligned in D-slot constraints as part of cleanup.
- Inverter PWM enable is generated in platform-state ISR logic:
  - disabled in idle/error
  - enabled in running
  - no explicit control-state change
- Inverter visualization signals are available.
- Hardware bitstream with inverter on D3 built successfully using the checkpoint workaround.
- Real inverter hardware was not available for full functional validation, but software build/flash worked.

#### PWM Migration

- Historical PWM content was moved out of D1/D2 into wizard-owned `uz_pwm`.
- `uz_pwm/pwm_2L` and `uz_pwm/pwm_3L` are generated.
- 2L PWM supports 1..10 instances.
- 3L PWM supports one instance for now.
- PWM outputs are exposed per instance:
  - `Gate_Signals_2L_0`, `Gate_Signals_2L_1`, ...
  - `Gate_Signals_3L_0`
- `Interrupt_Start`, `Interrupt_Center`, and `Interrupt_Start_Center` are connected to `uz_system` in the legacy order.
- D1/D2 can be set to `No adapter board` after migration.
- Vitis builds with wizard-owned PWM init.
- Real PWM output was tested for at least 2L output 0 with three-phase wavegen and behaved like before.

#### PWM Software

- `hw_init/pwm_init.c` and `include/pwm_init.h` are wizard-owned.
- Legacy fixed-flow PWM files are removed; wizard-owned PWM init lives in `hw_init/pwm_init.c` and `include/pwm_init.h`.
- Advanced driver config exists for:
  - 2L PWM
  - 2L deadtime
  - 3L PWM
- Enum fields are dropdowns.
- Boolean fields are dropdowns with `true`/`false`.
- PWM frequency/deadtime/min pulse width defines are written to `uz_global_configuration.h`.
- ISR platform-state logic exists for idle/running/control/error.
- 2L idle/error behavior is configurable:
  - set duty cycles only
  - set tristate enable plus duty cycles

#### Visualization

- Data visualization page has adapter-board tabs.
- Signals can be routed independently to fast Javascope and/or slow-data path.
- DAC outputs, inverter outputs/status, ADC values, temperature values, SSI/EnDat values, and incremental encoder values can be made available as signals depending selected hardware/software.

### Current Work In Progress

#### Incremental Encoder Adapter

Recently added and hardware-smoke-tested implementation:

- Adapter card id: `uz_d_incremental_encoder`.
- Default CPLD program: `rx30`.
- Vivado template: `project_wizard/templates/cards/uz_d_incremental_encoder.tcl`.
- IP VLNV: `xilinx.com:ip:Incremental_Encoder_v26`.
- Instance naming for enabled channels: `incremental_encoder_{slot_lower}_1`, `_2`, `_3`.
- Adapter revision dropdown exists in the adapter-card detail view:
  - default: Rev04
  - Rev03 and Rev04 share the same pinout.
  - Rev02 uses the older documented pinout.
- Channel 1/2/3 dropdowns exist below the revision selector:
  - default: `Incremental encoder`
  - alternative: `Not used`
  - disabled channels are omitted from Vivado IP generation, AXI attachment, software driver generation, instance counts, and visualization signals.
- Physical pins by revision:
  - Rev03/Rev04:
    - channel 1 I/A/B: `Dig_11_Chx`, `Dig_12_Chx`, `Dig_13_Chx`
    - channel 2 I/A/B: `Dig_14_Chx`, `Dig_15_Chx`, `Dig_16_Chx`
    - channel 3 I/A/B: `Dig_17_Chx`, `Dig_18_Chx`, `Dig_19_Chx`
  - Rev02:
    - channel 1 I/A/B: `Dig_14_Chx`, `Dig_13_Chx`, `Dig_12_Chx`
    - channel 2 I/A/B: `Dig_17_Chx`, `Dig_16_Chx`, `Dig_15_Chx`
    - channel 3 I/A/B: `Dig_20_Chx`, `Dig_19_Chx`, `Dig_18_Chx`
- Generated output hierarchy pins are exposed at `uz_digital_adapter` and `Dx_adapter`:
  - `Dx_incr_encoder_{channel}_omega`
  - `Dx_incr_encoder_{channel}_theta_el`
  - `Dx_incr_encoder_{channel}_position`
  - `Dx_incr_encoder_{channel}_omega_MA_N4`
- PeriodEnd source:
  - GUI source field id: `period_end_source`
  - default: `uz_system/trigger_conversions`
  - if missing, Tcl warns and ties PeriodEnd to zero.
- No ILA is generated.
- Uses `Digital_AdapterBoard_Dx.xdc` and disables packed D-slot constraint.
- AXI path:
  - `uz_digital_adapter/{slot}_adapter/incremental_encoder_{slot_lower}_{channel}/AXI4_Lite`
  - address segment `.../AXI4_Lite/reg0`
- Software driver id: `uz_incrementalEncoder`.
- Generated templates:
  - `templates/software/incremental_encoder.h.tpl`
  - `templates/software/incremental_encoder.c.tpl`
- Advanced config fields:
  - `ip_core_frequency_Hz`
  - `line_number_per_turn_mech`
  - `OmegaPerOverSample_in_rpm`
  - `drive_pole_pair`
  - `Encoder_mech_Offset`
  - `Encoder_elec_Offset`
  - `counting_direction` dropdown
  - `Speed_Timeout_ms`
- ISR readout generated:
  - `theta_el`
  - `omega_mech`
  - `omega_mech_ma_n4`
  - `position`
  - `position_w_offset`
  - `index_found`
- The wizard passes `drive_pole_pair` through to the driver and always uses the normal electrical-angle getter in generated ISR code. Invalid or unsupported pole-pair configurations should be handled by the driver, not hidden in wizard-generated ISR code.
- Instance count define handled:
  - `UZ_INCREMENTALENCODER_MAX_INSTANCES`.

Smoke checks passed:

- JSON parse.
- `python -m compileall project_wizard`.
- Tcl/software preview for D5 incremental encoder.
- Rev02/Rev04 Tcl generation checks for pinout selection and generated output hierarchy pins.

User built the workspace and confirmed all three encoder interfaces are working with attached hardware.

#### Resolver Adapter

Resolver implementation added and hardware-smoke-tested by the user:

- Adapter card id: `uz_d_resolver`.
- Slot CPLD programs:
  - D1-D4: `uz_d_resolver_d1_to_d4`
  - D5: `uz_d_resolver_d5`
- Vivado template: `project_wizard/templates/cards/uz_d_resolver.tcl`.
- Base resolver IP:
  - VLNV: `ki_power:user:Resolver_Interface_v1_0:1.0`
  - instance naming: `resolver_ip_{slot_lower}_{channel}`
  - D1-D4 generate 3 channels.
  - D5 generates 2 channels.
- Optional resolver PL interface:
  - per-channel checkboxes in adapter-card detail view: `enable_pl_interface_ch1`, `enable_pl_interface_ch2`, `enable_pl_interface_ch3`
  - default: enabled
  - VLNV: `xilinx.com:ip:uz_resolver_pl_interface:1.0`
  - instance naming: `resolver_pl_interface_{slot_lower}_{channel}`
  - hard-wired connections:
    - `resolver_ip_*/position_out_m` -> `resolver_pl_interface_*/position_raw`
    - `resolver_ip_*/velocity_out_m` -> `resolver_pl_interface_*/velocity_raw`
    - `resolver_ip_*/valid_m` -> `resolver_pl_interface_*/trigger`
- Sample trigger source:
  - GUI source field ids: `sample_trigger_source_ch1`, `sample_trigger_source_ch2`, `sample_trigger_source_ch3`
  - default: `uz_system/trigger_conversions`
  - D1-D4 show channel 1-3 trigger fields; D5 shows only channel 1-2 trigger fields.
  - if a selected channel trigger source is missing, Tcl warns and ties that channel sample trigger to zero.
- PL-interface outputs are exposed at `uz_digital_adapter` and `Dx_adapter`:
  - `Dx_resolver_pl_{channel}_position_mech_raw`
  - `Dx_resolver_pl_{channel}_position_mech_2pi`
  - `Dx_resolver_pl_{channel}_position_el_2pi`
  - `Dx_resolver_pl_{channel}_omega_mech_rad_s`
  - `Dx_resolver_pl_{channel}_n_mech_rpm`
  - `Dx_resolver_pl_{channel}_done`
- Software driver ids:
  - `uz_resolverIP`
  - `uz_resolver_pl_interface`
- Generated templates:
  - `templates/software/resolver_ip.h.tpl`
  - `templates/software/resolver_ip.c.tpl`
  - `templates/software/resolver_pl_interface.h.tpl`
  - `templates/software/resolver_pl_interface.c.tpl`
- Resolver IP advanced config fields:
  - `ip_clk_frequency_Hz`
  - `resolution`
  - `freq_clockin`
  - `zero_position_mechanical`
  - `pole_pairs_machine`
  - `pole_pairs_resolver`
  - `mode_after_init` dropdown, default `POSITION_VELOCITY_MODE`
- Resolver PL-interface advanced config fields:
  - `ip_clk_frequency_Hz`
  - `resolver_polepairs`
  - `machine_polepairs`
  - `position_intmax`
  - `bitToRPS_factor`
  - `theta_m_offset_rad`
- ISR readout generated for PL-interface enabled channels from `uz_resolver_pl_interface_get_outputs()`:
  - `position_mech_2pi`
  - `position_el_2pi`
  - `omega_mech_rad_s`
  - `n_mech_rpm`
  - `omega_el_rad_s` calculated as mechanical rad/s times resolver IP machine pole pairs
  - `revolution_counter`
- ISR readout generated for channels without PL interface from the base resolver IP driver:
  - calls `uz_resolverIP_readMechanicalPositionAndVelocity()` for mechanical position/speed
  - calls `uz_resolverIP_readElectricalPositionAndVelocity()` for electrical position/speed
  - stores `resolver_ip_{slot_lower}_{channel}_position_mech_2pi`
  - stores `position_el_2pi`, `omega_mech_rad_s`, `n_mech_rpm`, and `omega_el_rad_s`
  - visualization signals are generated for those base-IP values instead of PL-interface values
- Instance count defines handled:
  - `UZ_RESOLVERIP_MAX_INSTANCES`
  - `UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES`

Resolver smoke checks passed:

- JSON parse for adapter cards and software drivers.
- `python -m compileall project_wizard`.
- Focused Tcl generation check for D4 with PL interface enabled.
- Focused Tcl generation check for D5 with PL interface disabled.
- Focused software plan check for D5 with PL interface enabled, including instance counts and generated init/readout content.
- Resolver PL-interface selection is now per channel:
  - Adapter-card view shows channel 1-3 checkboxes for D1-D4.
  - Adapter-card view shows only channel 1-2 checkboxes for D5.
  - Tcl, AXI attachment, and PL-interface software driver generation are generated only for checked PL-interface channels.
  - Unchecked channels still generate base resolver IP software readout and visualization.
  - Toggling PL-interface channel checkboxes refreshes advanced driver options, software preview, and visualization options immediately.
- User confirmed D2 hardware readout and visualization for all three resolver channels, including a mixed case with channel 2 using base resolver IP readout and channels 1/3 using PL interface.
- User confirmed D5 bitstream/software/GUI visualization with two resolver channels using PL interfaces.

### Files Touched Along The Way

High-level list of important touched areas:

- `project_wizard/data/adapter_cards.json`
- `project_wizard/data/software_drivers.json`
- `project_wizard/templates/cards/*.tcl`
- `project_wizard/templates/helpers/bd_helpers.tcl`
- `project_wizard/templates/software/*.tpl`
- `project_wizard/tcl_generator.py`
- `project_wizard/models.py`
- `project_wizard/golden_scenarios.py`
- `project_wizard/services/software_generator_service.py`
- `project_wizard/services/system_resolver.py`
- `project_wizard/services/visualization_catalog.py`
- `project_wizard/services/cpld_programmer_service.py`
- `project_wizard/services/vivado_service.py`
- `project_wizard/views/main_window.py`
- `project_wizard/views/mixins/*.py`
- `project_wizard/theme.py`
- `project_wizard/assets/checkmark.svg`
- `vitis/software/Baremetal/src/globalData.h`
- `vitis/software/Baremetal/src/main.c`
- `vitis/software/Baremetal/src/sw/isr.c`
- `vitis/software/Baremetal/src/include/javascope.h`
- `vitis/software/Baremetal/src/sw/javascope.c`
- `vitis/software/Baremetal/src/uz/uz_global_configuration.h`
- `vitis/software/Baremetal/src/IP_Cores/uz_dataMover/uz_dataMover.c`
- Digital and analog XDC files under `vivado/constraints/te0808/`

## 4. Next Concrete Steps

Immediate start for a new assistant session:

1. Read this file and `project_wizard/README.md`.
2. Inspect the current working tree before editing. User test files and generated
   output may be present.
3. Run the standard wizard checks before and after structural changes:
   - `python -m json.tool project_wizard/data/adapter_cards.json`
   - `python -m json.tool project_wizard/data/software_drivers.json`
   - `python -m compileall project_wizard`
   - `python -m project_wizard.golden_scenarios --check`
4. For changes touching TCL behavior, also scan generated TCL for leaked template
   markers such as `{%` and `{{`.

Current roadmap:

- Keep the public wizard boundary model-first: GUI state and saved JSON become
  `SystemConfig`, then `ResolvedSystemModel`, then generator/service calls.
- Keep the Adapter Card Database page read-only for v1. Do not wire the draft
  `CardEditorDialog` back into the GUI without a deliberate schema-complete
  editor redesign.
- Continue field testing with Vivado/hardware configurations, especially slot
  transition cleanup and local Vivado workflow combinations.
- Add new adapter cards through JSON/templates/docs and golden scenario checks.

## 5. Known Caveats And Watch Points

- Files in `project_wizard/generated/` and `project_wizard/user_configurations/` are often user/local state. Be careful before editing or reverting.
- The working tree may be dirty from user tests. Never revert unrelated files.
- `compileall` creates `__pycache__`; remove those before finalizing.
- The UI may remain open while files are edited; Python source changes require restarting the wizard. JSON/templates are generally read when workflows run, but restart is still safest.
- The Vivado GUI flow and generated Tcl flow should behave the same. Avoid special cases that only work when Tcl is pasted manually.
- If Vivado address assignment fails randomly, rerun generation after ensuring stale AXI pins/legacy hierarchies are cleaned.
- Legacy uncontrolled BD content can cause confusing build errors. The long-term goal is a cleaner, fully wizard-owned script path, but current strategy is still piecewise migration.
- Tcl template safety was smoke-tested at generator level across bypass, no-adapter, checkpoint on/off, every card in every compatible slot, selectable option choices, all-option-`none` paths, and IO-card no-AXI paths. This catches template/rendering errors but does not replace Vivado execution tests.
- Project configuration uses schema version 2. The saved JSON now has typed sections:
  - `platform`: `{id, revision, cpld}`
  - `slots`: per-slot `{card, options, cpld}`
  - `software`: `{source_dir, modes, presets, visualization_routes, driver_config, extra}`
  - top-level `toolchain`, `hardware`, `cpld_programmer`, and `axi`.
- `project_wizard/models.py` owns the typed config dataclasses. `SystemConfig` no longer exposes ambiguous old-style public properties such as `slots`, `slot_options`, or flat `software`. Private generator internals that still preserve proven historical rendering behavior receive those shapes through the explicit `SystemConfig.legacy_generator_values()` bridge.
- GUI preview/export/generate paths should go through `MainWindow.resolved_system_model()` and model-based generator APIs such as `TclGenerator.generate()` and `SoftwareGenerator.build_plan()`.
- `SystemResolver` owns card-derived CPLD defaults, software driver instance discovery, visualization signal discovery, and analog datamover facts. Do not reintroduce duplicate public GUI/generator discovery logic for those domains.
- `SystemResolver` owns slot-local AXI cleanup/attachment facts and AXI interface lists. `tcl_generator.py` should render those facts, not rediscover them from card JSON.
- `services/visualization_catalog.py` is the shared owner for visualization signal helpers and IO-card direction/AXI helper functions. Use it from resolver/generators instead of copying IO-card rules.
- Golden scenario baselines live in `project_wizard/generated/golden_scenarios/`. Run `python -m project_wizard.golden_scenarios --check` after config/resolver/generator changes; it compares representative scenarios against TCL and software-summary baselines.
- The Adapter Card Database page is intentionally read-only for v1. `adapter_cards.json` remains the source of truth. The old draft `CardEditorDialog` exists in the source tree but is not wired into the GUI because it is not schema-complete and can break the wizard catalog if used casually. New cards should be added by editing JSON/templates through the developer workflow and running golden checks.
- Vivado-live Tcl transition tests after the resolver refactor were run by the user with the complex golden scenario:
  - D5 absolute encoder -> `No adapter board`: BD validated OK.
  - D4 resolver -> 3V3/5V card with PWM/constant pins and no AXI GPIO pins selected: BD validated OK.
  - Dirty D1 slot with manually added AXI GPIO -> selected absolute encoder card with one EnDat instance: BD validated OK.
  - D1 set to `Bypass`: slot internals were correctly untouched. Vivado validation reported a dangling external input warning for `D1_to_pwm_source_2l_0` on `uz_d_adapter`; keep this edge case in mind when evaluating bypass behavior. Bypass intentionally does not clean or repair slot-local contents, but external wizard-owned wiring can still interact with an untouched slot.
- Open local Vivado workflow matrix tests to run manually with Vivado or by test users:
  - Batch mode with `Validate BD` only.
  - Batch mode with `Validate BD` + `Save BD`.
  - GUI mode with validate/save enabled.
  - `Generate bitstream` enabled.
  - `Generate bitstream` + `Export .xsa after successful build` enabled.
  - Confirm workflow output autoscrolls and contains enough error context for failed Vivado runs.
  - Confirm `Clear local Vivado artifacts` reliably fixes stale cache/IP issues before rerunning.
- Do not reintroduce fixed AXI addresses.
- Do not reintroduce old `xz` naming.
