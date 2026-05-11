# Generic Adapter Card Metadata

The generic Vivado generator uses `templates/cards/generic_adapter_card.tcl`.
New cards should describe their hardware in `adapter_cards.json` instead of
adding a card-specific TCL template.

Minimum `vivado` shape:

```json
{
  "template": "cards/generic_adapter_card.tcl",
  "ip_cores": [
    {
      "instance_name": "OptionalFixedInstanceName",
      "instance_prefix": "used_if_instance_name_is_missing",
      "module": "IP module name",
      "vlnv": "vendor:library:name:version",
      "clock_pins": ["s00_axi_aclk"],
      "reset_pins": ["s00_axi_aresetn"]
    }
  ],
  "ports": [
    {
      "signal": "logical_signal_name",
      "ip_pin": "ip_pin_name_if_different",
      "direction": "in or out",
      "pin": "Dig_00_Ch{slot_index}"
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

Generated signal path for an external pin:

```text
IP pin -> Dx_adapter boundary -> uz_digital_adapter boundary -> top-level port
```

Generated signal path for a configurable trigger input:

```text
configured source -> uz_digital_adapter boundary -> Dx_adapter boundary -> IP pin
```
