# Project Wizard AI Handoff

This file captures project-specific knowledge for future AI/code-assistant sessions. Read it before making changes to the Project Wizard or the wizard-owned Vivado/Vitis flow.

## 1. Project Architecture

### Repository Context

- Main repo: UltraZohm software/Vivado/Vitis repository.
- Wizard path: `project_wizard/`.
- Main generated config: `project_wizard/generated/project_wizard_config.pw.json`.
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
  - Main PyQt UI. Large, but many workflows are still wired here.
- `project_wizard/data/adapter_cards.json`
  - Hardware/card catalog: compatible slots, Vivado templates, IP VLNVs, ports, AXI interfaces, constraints, default CPLD program.
- `project_wizard/data/software_drivers.json`
  - Software driver catalog: generated C/H templates and advanced driver config fields.
- `project_wizard/data/platforms.json`
  - Platform defaults, AXI defaults, revision choices.
- `project_wizard/tcl_generator.py`
  - High-level Tcl generation coordinator.
- `project_wizard/services/software_generator_service.py`
  - Vitis source generation and marker patching.
- `project_wizard/services/cpld_programmer_service.py`
  - `.xcf` generation and Diamond Programmer CLI handling.
- `project_wizard/services/vivado_service.py`
  - Vivado TCL execution wrapper.
- `project_wizard/models.py` and `project_wizard/services/system_resolver.py`
  - First step toward typed config/resolver architecture. Not yet the single source for all generation.

### Current Data Model

The saved `.pw.json` config is still mostly user-facing, with dictionaries for:

- `slots`
- `slot_options`
- `slot_cplds`
- `axi`
- `software`
- `visualization`
- `hardware_config`

There is an early model/resolver layer, but generators still directly consume much of the raw config. Future refactoring should move toward:

```text
raw config JSON
  -> typed SystemConfig
  -> ResolvedSystemModel
  -> ValidationService
  -> Tcl/Software/CPLD generators
```

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
- Legacy `pwm_3L_driver.c` was removed.
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
- Instance naming: `incremental_encoder_{slot_lower}_1`, `_2`, `_3`.
- Adapter revision dropdown exists in the adapter-card detail view:
  - default: Rev04
  - Rev03 and Rev04 share the same pinout.
  - Rev02 uses the older documented pinout.
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

First-pass implementation added, not yet Vivado/hardware validated by the user:

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
  - checkbox in adapter-card detail view: `enable_pl_interface`
  - default: enabled
  - VLNV: `xilinx.com:ip:uz_resolver_pl_interface:1.0`
  - instance naming: `resolver_pl_interface_{slot_lower}_{channel}`
  - hard-wired connections:
    - `resolver_ip_*/position_out_m` -> `resolver_pl_interface_*/position_raw`
    - `resolver_ip_*/velocity_out_m` -> `resolver_pl_interface_*/velocity_raw`
    - `resolver_ip_*/valid_m` -> `resolver_pl_interface_*/trigger`
- Sample trigger source:
  - GUI source field id: `sample_trigger_source`
  - default: `uz_system/trigger_conversions`
  - if missing, Tcl warns and ties sample trigger to zero.
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
- ISR readout generated for PL-interface enabled channels:
  - `position_mech_2pi`
  - `position_el_2pi`
  - `omega_mech_rad_s`
  - `n_mech_rpm`
  - `omega_el_rad_s` calculated as mechanical rad/s times resolver IP machine pole pairs
  - `revolution_counter`
- Instance count defines handled:
  - `UZ_RESOLVERIP_MAX_INSTANCES`
  - `UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES`

Resolver smoke checks passed:

- JSON parse for adapter cards and software drivers.
- `python -m compileall project_wizard`.
- Focused Tcl generation check for D4 with PL interface enabled.
- Focused Tcl generation check for D5 with PL interface disabled.
- Focused software plan check for D5 with PL interface enabled, including instance counts and generated init/readout content.

### Files Touched Along The Way

High-level list of important touched areas:

- `project_wizard/data/adapter_cards.json`
- `project_wizard/data/software_drivers.json`
- `project_wizard/templates/cards/*.tcl`
- `project_wizard/templates/helpers/bd_helpers.tcl`
- `project_wizard/templates/software/*.tpl`
- `project_wizard/tcl_generator.py`
- `project_wizard/services/software_generator_service.py`
- `project_wizard/services/cpld_programmer_service.py`
- `project_wizard/services/vivado_service.py`
- `project_wizard/views/main_window.py`
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

Immediate next task in the new chat:

1. Start by reading this file.
2. Validate the resolver implementation:
   - Open the wizard.
   - Select `UZ_D Resolver` in D4 first, then D5.
   - Confirm default CPLD becomes `uz_d_resolver_d1_to_d4` for D1-D4 and `uz_d_resolver_d5` for D5.
   - Confirm the resolver PL interface checkbox is enabled by default.
   - Confirm sample trigger source defaults to `uz_system/trigger_conversions`.
   - Generate Tcl.
   - Apply Tcl in Vivado GUI.
   - Check BD:
     - D1-D4 create 3 `resolver_ip_*` instances and 3 `resolver_pl_interface_*` instances when enabled.
     - D5 creates 2 `resolver_ip_*` instances and 2 `resolver_pl_interface_*` instances when enabled.
     - `valid_m` connects to PL-interface `trigger`.
     - resolver sample trigger connects from configured source to each resolver IP.
     - PL-interface outputs are exposed through the D-slot adapter hierarchy.
     - No ILA exists for this card.
     - AXI4-Lite is connected through the D-slot AXI flow.
     - `Digital_AdapterBoard_Dx.xdc` enabled, `Digital_Dx_packed.xdc` disabled.
   - Validate BD.
   - Build bitstream.
   - Export hardware and regenerate Vitis workspace.
   - Generate software from wizard.
   - Build Vitis.
   - If hardware is available, test resolver position/speed readout and PL-interface output signals.

Likely follow-up tasks:

- If sample trigger source name differs in the live BD, adjust the default source field.
- If xparameters macro names differ from fallbacks, confirm `resolve_base_address_macro` finds resolver IP and PL-interface macros without warning after workspace regeneration.
- Decide whether resolver readout should optionally map to legacy motor variables (`theta_elec`, `mechanicalRotorSpeed`) or remain purely slot-local.
- Add docs or GUI hint for resolver pin mapping and PL-interface checkbox behavior.
- Continue with voltage and optical IO cards after resolver is validated.

## 5. Known Caveats And Watch Points

- Generated files in `project_wizard/generated/` are often user/local state. Be careful before editing or reverting.
- The working tree may be dirty from user tests. Never revert unrelated files.
- `compileall` creates `__pycache__`; remove those before finalizing.
- The UI may remain open while files are edited; Python source changes require restarting the wizard. JSON/templates are generally read when workflows run, but restart is still safest.
- The Vivado GUI flow and generated Tcl flow should behave the same. Avoid special cases that only work when Tcl is pasted manually.
- If Vivado address assignment fails randomly, rerun generation after ensuring stale AXI pins/legacy hierarchies are cleaned.
- Legacy uncontrolled BD content can cause confusing build errors. The long-term goal is a cleaner, fully wizard-owned script path, but current strategy is still piecewise migration.
- Do not reintroduce fixed AXI addresses.
- Do not reintroduce old `xz` naming.
