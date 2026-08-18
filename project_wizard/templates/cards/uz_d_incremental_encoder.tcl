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

proc uz_pw_incremental_encoder_create_input_path {adapter_parent_hier adapter_hier_path internal_name external_name target_pin} {
  uz_pw_create_bd_port_if_missing I $external_name
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier I $internal_name
  uz_pw_create_hier_pin_if_missing $adapter_hier_path I $internal_name
  uz_pw_connect_port_if_unconnected "${adapter_parent_hier}/${internal_name}" $external_name
  uz_pw_connect_pin_pair_if_unconnected "${adapter_parent_hier}/${internal_name}" "${adapter_hier_path}/${internal_name}"
  uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${internal_name}" $target_pin
}

proc uz_pw_incremental_encoder_create_xlconstant {cell_path width value} {
  uz_pw_create_ip_cell_if_missing $cell_path xilinx.com:ip:xlconstant
  uz_pw_set_property_dict_if_objects [list CONFIG.CONST_WIDTH $width CONFIG.CONST_VAL $value] [get_bd_cells -quiet $cell_path] $cell_path
}

proc uz_pw_incremental_encoder_create_output_path {adapter_parent_hier adapter_hier_path boundary_name source_pin left right} {
  uz_pw_create_hier_pin_if_missing $adapter_hier_path O $boundary_name $left $right
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier O $boundary_name $left $right
  uz_pw_connect_pin_pair_if_unconnected $source_pin "${adapter_hier_path}/${boundary_name}"
  uz_pw_connect_upper_boundary_net_if_unconnected "${adapter_hier_path}/${boundary_name}" "${adapter_parent_hier}/${boundary_name}"
}

set period_end_source_pin "{{ incremental_encoder_period_end_source }}"
if {$period_end_source_pin eq "" || [llength [get_bd_pins -quiet $period_end_source_pin]] == 0} {
  puts "WARNING: PeriodEnd source '$period_end_source_pin' not found for {{ slot }} incremental encoder; using zero fallback."
  set period_end_default_path "${adapter_hier_path}/{{ slot }}_period_end_default_zero"
  uz_pw_incremental_encoder_create_xlconstant $period_end_default_path 1 0
  set period_end_source_pin "${period_end_default_path}/dout"
}

{% for encoder in incremental_encoder_channels %}
set incremental_encoder_{{ encoder.channel }}_path "${adapter_hier_path}/{{ encoder.instance_name }}"
uz_pw_create_ip_cell_if_missing $incremental_encoder_{{ encoder.channel }}_path {{ ip.vlnv }}
{% if ip.has_properties %}
uz_pw_set_property_dict_if_objects [list {{ ip.property_dict }}] [get_bd_cells -quiet $incremental_encoder_{{ encoder.channel }}_path] $incremental_encoder_{{ encoder.channel }}_path
{% endif %}

uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_clock_pin}" "${incremental_encoder_{{ encoder.channel }}_path}/IPCORE_CLK"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_clock_pin}" "${incremental_encoder_{{ encoder.channel }}_path}/AXI4_Lite_ACLK"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_resetn_pin}" "${incremental_encoder_{{ encoder.channel }}_path}/IPCORE_RESETN"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_resetn_pin}" "${incremental_encoder_{{ encoder.channel }}_path}/AXI4_Lite_ARESETN"

uz_pw_incremental_encoder_create_input_path $adapter_parent_hier $adapter_hier_path {{ encoder.index_internal_name }} {{ encoder.index_pin }} "${incremental_encoder_{{ encoder.channel }}_path}/I"
uz_pw_incremental_encoder_create_input_path $adapter_parent_hier $adapter_hier_path {{ encoder.a_internal_name }} {{ encoder.a_pin }} "${incremental_encoder_{{ encoder.channel }}_path}/A"
uz_pw_incremental_encoder_create_input_path $adapter_parent_hier $adapter_hier_path {{ encoder.b_internal_name }} {{ encoder.b_pin }} "${incremental_encoder_{{ encoder.channel }}_path}/B"

set period_end_parent_pin "{{ slot }}_PeriodEnd_{{ encoder.channel }}"
uz_pw_create_hier_pin_if_missing $adapter_parent_hier I $period_end_parent_pin
uz_pw_create_hier_pin_if_missing $adapter_hier_path I $period_end_parent_pin
uz_pw_connect_pin_pair_if_unconnected $period_end_source_pin "${adapter_parent_hier}/${period_end_parent_pin}"
uz_pw_connect_upper_boundary_net_if_unconnected "${adapter_parent_hier}/${period_end_parent_pin}" "${adapter_hier_path}/${period_end_parent_pin}"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${period_end_parent_pin}" "${incremental_encoder_{{ encoder.channel }}_path}/PeriodEnd"
{% endfor %}

{% for output in incremental_encoder_output_paths %}
uz_pw_incremental_encoder_create_output_path $adapter_parent_hier $adapter_hier_path {{ output.boundary_name }} "{{ output.source_pin }}" {{ output.left }} {{ output.right }}
{% endfor %}

uz_pw_apply_slot_constraints {{ slot }} [list {{ slot_constraint_names }}] [list "Digital_AdapterBoard_{{ slot }}.xdc"]

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
