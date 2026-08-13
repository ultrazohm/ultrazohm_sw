# Generic Adapter Card Metadata

The generic Vivado generator uses `templates/cards/generic_adapter_card.tcl`.
New cards should describe their hardware in `adapter_cards.json` instead of
adding a card-specific TCL template.

Two system entries are intentionally special:

- `empty` is shown as `Bypass` in the GUI and emits no TCL for the slot.
- `no_adapter_board` emits `templates/cards/no_adapter_board.tcl` and removes
  generated slot content. Its AXI boundary cleanup is handled by the shared
  AXI interconnect template because it needs the configured project-level
  SmartConnect.

Cards normally use `slot_cpld` for their default slot CPLD program. Rare cards
with slot-specific CPLD images can additionally define `slot_cpld_by_slot`;
the GUI uses this map to prefill the Slot CPLDs view while still allowing the
user to override every slot manually.

```json
{
  "slot_cpld": "uz_d_resolver_d1_to_d4",
  "slot_cpld_by_slot": {
    "D1": "uz_d_resolver_d1_to_d4",
    "D2": "uz_d_resolver_d1_to_d4",
    "D3": "uz_d_resolver_d1_to_d4",
    "D4": "uz_d_resolver_d1_to_d4",
    "D5": "uz_d_resolver_d5"
  }
}
```

Minimum `vivado` shape:

```json
{
  "template": "cards/generic_adapter_card.tcl",
  "adapter_parent_hier": "uz_digital_adapter or uz_analog_adapter",
  "adapter_clock_pin": "aclk",
  "adapter_resetn_pin": "aresetn",
  "ip_cores": [
    {
      "instance_name": "OptionalFixedInstanceName",
      "instance_prefix": "used_if_instance_name_is_missing",
      "module": "IP module name",
      "vlnv": "vendor:library:name",
      "cell_type": "ip or module",
      "reference": "module_name_for_module_ref_cells",
      "clock_pins": ["s00_axi_aclk"],
      "reset_pins": ["s00_axi_aresetn"],
      "properties": {
        "CONFIG.PARAMETER_NAME": "value"
      }
    }
  ],
  "ports": [
    {
      "signal": "logical_signal_name",
      "ip_core": "OptionalInstanceNameIfNotPrimaryIp",
      "ip_pin": "ip_pin_name_if_different",
      "direction": "in or out",
      "pin": "Dig_00_Ch{slot_index}",
      "pins": ["first_parallel_external_port", "second_parallel_external_port"],
      "left": 15,
      "right": 0
    }
  ],
  "signals": [
    {
      "signal": "hierarchy_only_signal_name",
      "ip_pin": "ip_pin_name_if_different",
      "direction": "in or out",
      "external_port": false
    }
  ],
  "pin_connections": [
    {
      "source_ip_core": "source_instance_name",
      "source_pin": "source_pin",
      "sink_ip_core": "sink_instance_name",
      "sink_pin": "sink_pin"
    }
  ],
  "outputs": [
    "optional_ip_output_exposed_to_uz_digital_adapter"
  ],
  "trigger_inputs": [
    {
      "signal": "trigger_ip_pin"
    }
  ],
  "axi_interfaces": [
    {
      "name": "AXI4_Lite",
      "path_template": "uz_digital_adapter/{slot}_adapter/ip_instance/AXI4_Lite",
      "addr_seg_template": "uz_digital_adapter/{slot}_adapter/ip_instance/AXI4_Lite/reg0"
    }
  ],
  "constraints": {
    "disable": "Digital_{slot}_packed.xdc",
    "enable": "Digital_AdapterBoard_{slot}.xdc"
  }
}
```

For option-based cards, put the same `vivado` shape inside each selectable
choice. The GUI stores configurable trigger sources as
`<option_id>_trigger_source`; if the value has no slash, the generator prefixes
it with `uz_system/`.

AXI interfaces are connected and assigned by the generated TCL with Vivado's
automatic address assignment. Card definitions provide the interface pin path in
`path_template` and the address segment in `addr_seg_template`; they do not
define fixed address offsets or ranges. Software drivers use the generated
`xparameters.h` macros to pick up the final addresses.

Generated signal path for an external pin:

```text
IP pin -> slot adapter boundary -> adapter parent hierarchy boundary -> top-level port
```

Generated signal path for a configurable trigger input:

```text
configured source -> uz_digital_adapter boundary -> Dx_adapter boundary -> IP pin
```
