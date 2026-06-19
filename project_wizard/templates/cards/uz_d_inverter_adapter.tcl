# -----------------------------------------------------------------------------
# {{ slot }}: {{ card_name }}
# -----------------------------------------------------------------------------
{% for note in notes %}
# NOTE: {{ note }}
{% endfor %}

set adapter_parent_hier {{ adapter_parent_hier }}
set adapter_hier_name {{ slot }}_adapter
set adapter_hier_path "${adapter_parent_hier}/${adapter_hier_name}"
set adapter_clock_pin {{ adapter_clock_pin }}
set adapter_resetn_pin {{ adapter_resetn_pin }}

# Recreate the selected slot content so the wizard configuration wins over stale IP.
uz_pw_delete_child_cells_in_slot_hierarchy $adapter_hier_path
uz_pw_create_hier_if_missing $adapter_parent_hier
uz_pw_create_hier_if_missing $adapter_hier_path

uz_pw_delete_pin_if_exists "${adapter_hier_path}/aclk"
uz_pw_delete_pin_if_exists "${adapter_hier_path}/aresetn"
uz_pw_create_hier_pin_if_missing $adapter_hier_path I $adapter_clock_pin
uz_pw_create_hier_pin_if_missing $adapter_hier_path I $adapter_resetn_pin

set inverter_driver_path "${adapter_hier_path}/{{ ip.instance_name }}"
uz_pw_create_ip_cell_if_missing $inverter_driver_path {{ ip.vlnv }}
{% if ip.has_properties %}
uz_pw_set_property_dict_if_objects [list {{ ip.property_dict }}] [get_bd_cells -quiet $inverter_driver_path] $inverter_driver_path
{% endif %}

uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_clock_pin}" "${inverter_driver_path}/IPCORE_CLK"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_clock_pin}" "${inverter_driver_path}/AXI4_Lite_ACLK"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_resetn_pin}" "${inverter_driver_path}/IPCORE_RESETN"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_resetn_pin}" "${inverter_driver_path}/AXI4_Lite_ARESETN"

proc uz_pw_inverter_create_slot_signal {direction adapter_parent_hier adapter_hier_path internal_name external_name {left ""} {right ""}} {
  uz_pw_create_bd_port_if_missing $direction $external_name "$left" "$right"
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier $direction $external_name "$left" "$right"
  uz_pw_create_hier_pin_if_missing $adapter_hier_path $direction $internal_name "$left" "$right"

  if {$direction ne "O"} {
    uz_pw_connect_port_if_unconnected "${adapter_parent_hier}/${external_name}" $external_name
    uz_pw_connect_pin_pair_if_unconnected "${adapter_parent_hier}/${external_name}" "${adapter_hier_path}/${internal_name}"
  }
}

proc uz_pw_inverter_connect_slot_output {adapter_parent_hier adapter_hier_path internal_name external_name} {
  uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${internal_name}" "${adapter_parent_hier}/${external_name}"
  uz_pw_connect_port_if_unconnected "${adapter_parent_hier}/${external_name}" $external_name
}

proc uz_pw_inverter_create_xlslice {cell_path bit_index} {
  uz_pw_create_ip_cell_if_missing $cell_path xilinx.com:ip:xlslice
  uz_pw_set_property_dict_if_objects [list CONFIG.DIN_WIDTH {6} CONFIG.DIN_FROM $bit_index CONFIG.DIN_TO $bit_index CONFIG.DOUT_WIDTH {1}] [get_bd_cells -quiet $cell_path] $cell_path
}

proc uz_pw_inverter_create_xlconcat {cell_path port_count} {
  uz_pw_create_ip_cell_if_missing $cell_path xilinx.com:ip:xlconcat
  uz_pw_set_property_dict_if_objects [list CONFIG.NUM_PORTS $port_count] [get_bd_cells -quiet $cell_path] $cell_path
}

# Future wizard option: Gates[5:0] source. For now this boundary pin is left unconnected by design.
uz_pw_create_hier_pin_if_missing $adapter_hier_path I Gates 5 0
uz_pw_create_hier_pin_if_missing $adapter_parent_hier I {{ slot }}_Gates 5 0
uz_pw_connect_pin_pair_if_unconnected "${adapter_parent_hier}/{{ slot }}_Gates" "${adapter_hier_path}/Gates"

# Future wizard option: PWM_UZ_Enable source. For now this boundary pin is left unconnected by design.
uz_pw_create_hier_pin_if_missing $adapter_hier_path I PWM_UZ_Enable
uz_pw_create_hier_pin_if_missing $adapter_parent_hier I {{ slot }}_PWM_UZ_Enable
uz_pw_connect_pin_pair_if_unconnected "${adapter_parent_hier}/{{ slot }}_PWM_UZ_Enable" "${adapter_hier_path}/PWM_UZ_Enable"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/PWM_UZ_Enable" "${inverter_driver_path}/PWM_UZ_Enable"

# Dig_16_Ch{{ slot_index }} is unused by the adapter mapping but present on the adapter board connector.
uz_pw_inverter_create_slot_signal I $adapter_parent_hier $adapter_hier_path {{ slot }}_DIG_IO_17 Dig_16_Ch{{ slot_index }}

# Gate outputs to the adapter board.
# Former mapping IP order: Gates[0..5] -> PWM_H1, PWM_L1, PWM_H2, PWM_L2, PWM_H3, PWM_L3.
{% for gate in inverter_gate_outputs %}
set {{ gate.port }}_slice_path "${adapter_hier_path}/{{ slot }}_{{ gate.port }}_slice"
uz_pw_inverter_create_xlslice ${{ gate.port }}_slice_path {{ gate.bit }}
uz_pw_inverter_create_slot_signal O $adapter_parent_hier $adapter_hier_path {{ slot }}_{{ gate.port }} {{ gate.external_port }}
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/Gates" "${{{ gate.port }}_slice_path}/Din"
uz_pw_connect_pin_pair_if_unconnected "${{{ gate.port }}_slice_path}/Dout" "${adapter_hier_path}/{{ slot }}_{{ gate.port }}"
uz_pw_inverter_connect_slot_output $adapter_parent_hier $adapter_hier_path {{ slot }}_{{ gate.port }} {{ gate.external_port }}
{% endfor %}

# PWM enable output from the driver IP to the adapter board.
uz_pw_inverter_create_slot_signal O $adapter_parent_hier $adapter_hier_path {{ slot }}_pwm_en Dig_14_Ch{{ slot_index }}
uz_pw_connect_pin_pair_if_unconnected "${inverter_driver_path}/PWM_EN" "${adapter_hier_path}/{{ slot }}_pwm_en"
uz_pw_inverter_connect_slot_output $adapter_parent_hier $adapter_hier_path {{ slot }}_pwm_en Dig_14_Ch{{ slot_index }}

# Status and diagnostic inputs from the adapter board.
{% for input in inverter_input_ports %}
uz_pw_inverter_create_slot_signal I $adapter_parent_hier $adapter_hier_path {{ slot }}_{{ input.name }} {{ input.external_port }}
{% endfor %}

uz_pw_inverter_create_xlconcat "${adapter_hier_path}/{{ slot }}_i_diag_concat" 4
# Former mapping IP order: I_DIAG = {I3_DIAG, I2_DIAG, I1_DIAG, I_DIAG}.
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_i_diag" "${adapter_hier_path}/{{ slot }}_i_diag_concat/In0"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_i1_diag" "${adapter_hier_path}/{{ slot }}_i_diag_concat/In1"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_i2_diag" "${adapter_hier_path}/{{ slot }}_i_diag_concat/In2"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_i3_diag" "${adapter_hier_path}/{{ slot }}_i_diag_concat/In3"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_i_diag_concat/dout" "${inverter_driver_path}/I_DIAG"

uz_pw_inverter_create_xlconcat "${adapter_hier_path}/{{ slot }}_temp_concat" 6
# Former mapping IP order: Temp = {L3_Temp, H3_Temp, L2_Temp, H2_Temp, L1_Temp, H1_Temp}.
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h1_temp" "${adapter_hier_path}/{{ slot }}_temp_concat/In0"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l1_temp" "${adapter_hier_path}/{{ slot }}_temp_concat/In1"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h2_temp" "${adapter_hier_path}/{{ slot }}_temp_concat/In2"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l2_temp" "${adapter_hier_path}/{{ slot }}_temp_concat/In3"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h3_temp" "${adapter_hier_path}/{{ slot }}_temp_concat/In4"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l3_temp" "${adapter_hier_path}/{{ slot }}_temp_concat/In5"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_temp_concat/dout" "${inverter_driver_path}/Temp"

uz_pw_inverter_create_xlconcat "${adapter_hier_path}/{{ slot }}_oc_concat" 6
# Former mapping IP order: OC = {L3_OC, H3_OC, L2_OC, H2_OC, L1_OC, H1_OC}.
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h1_oc" "${adapter_hier_path}/{{ slot }}_oc_concat/In0"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l1_oc" "${adapter_hier_path}/{{ slot }}_oc_concat/In1"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h2_oc" "${adapter_hier_path}/{{ slot }}_oc_concat/In2"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l2_oc" "${adapter_hier_path}/{{ slot }}_oc_concat/In3"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h3_oc" "${adapter_hier_path}/{{ slot }}_oc_concat/In4"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l3_oc" "${adapter_hier_path}/{{ slot }}_oc_concat/In5"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_oc_concat/dout" "${inverter_driver_path}/OC"

uz_pw_inverter_create_xlconcat "${adapter_hier_path}/{{ slot }}_fault_concat" 6
# Former mapping IP order: FAULT = {H3_FAULT, L3_FAULT, L2_FAULT, H2_FAULT, L1_FAULT, H1_FAULT}.
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h1_fault" "${adapter_hier_path}/{{ slot }}_fault_concat/In0"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l1_fault" "${adapter_hier_path}/{{ slot }}_fault_concat/In1"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h2_fault" "${adapter_hier_path}/{{ slot }}_fault_concat/In2"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l2_fault" "${adapter_hier_path}/{{ slot }}_fault_concat/In3"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_l3_fault" "${adapter_hier_path}/{{ slot }}_fault_concat/In4"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_h3_fault" "${adapter_hier_path}/{{ slot }}_fault_concat/In5"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/{{ slot }}_fault_concat/dout" "${inverter_driver_path}/FAULT"

uz_pw_apply_slot_constraints {{ slot }} [list {{ slot_constraint_names }}] [list "Digital_AdapterBoard_{{ slot }}.xdc"]

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
