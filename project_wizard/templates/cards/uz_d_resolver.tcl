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

proc uz_pw_resolver_create_input_path {adapter_parent_hier adapter_hier_path internal_name external_name target_pin} {
  uz_pw_create_bd_port_if_missing I $external_name
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier I $internal_name
  uz_pw_create_hier_pin_if_missing $adapter_hier_path I $internal_name
  uz_pw_connect_port_if_unconnected "${adapter_parent_hier}/${internal_name}" $external_name
  uz_pw_connect_pin_pair_if_unconnected "${adapter_parent_hier}/${internal_name}" "${adapter_hier_path}/${internal_name}"
  uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${internal_name}" $target_pin
}

proc uz_pw_resolver_create_output_path {adapter_parent_hier adapter_hier_path internal_name external_name source_pin} {
  uz_pw_create_bd_port_if_missing O $external_name
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier O $internal_name
  uz_pw_create_hier_pin_if_missing $adapter_hier_path O $internal_name
  uz_pw_connect_pin_pair_if_unconnected $source_pin "${adapter_hier_path}/${internal_name}"
  uz_pw_connect_upper_boundary_net_if_unconnected "${adapter_hier_path}/${internal_name}" "${adapter_parent_hier}/${internal_name}"
  uz_pw_connect_port_if_unconnected "${adapter_parent_hier}/${internal_name}" $external_name
}

proc uz_pw_resolver_create_pl_output_path {adapter_parent_hier adapter_hier_path boundary_name source_pin left right} {
  uz_pw_create_hier_pin_if_missing $adapter_hier_path O $boundary_name $left $right
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier O $boundary_name $left $right
  uz_pw_connect_pin_pair_if_unconnected $source_pin "${adapter_hier_path}/${boundary_name}"
  uz_pw_connect_upper_boundary_net_if_unconnected "${adapter_hier_path}/${boundary_name}" "${adapter_parent_hier}/${boundary_name}"
}

proc uz_pw_resolver_create_xlconstant {cell_path width value} {
  uz_pw_create_ip_cell_if_missing $cell_path xilinx.com:ip:xlconstant
  uz_pw_set_property_dict_if_objects [list CONFIG.CONST_WIDTH $width CONFIG.CONST_VAL $value] [get_bd_cells -quiet $cell_path] $cell_path
}

{% for resolver in resolver_channels %}
set resolver_ip_{{ resolver.channel }}_path "${adapter_hier_path}/{{ resolver.resolver_instance_name }}"
uz_pw_create_ip_cell_if_missing $resolver_ip_{{ resolver.channel }}_path {{ resolver_ip.vlnv }}

uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_clock_pin}" "${resolver_ip_{{ resolver.channel }}_path}/s00_axi_aclk"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_resetn_pin}" "${resolver_ip_{{ resolver.channel }}_path}/s00_axi_aresetn"

uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.sample_internal_name }} {{ resolver.sample_pin }} "${resolver_ip_{{ resolver.channel }}_path}/AD2S1210_n_sample"
uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.sdo_internal_name }} {{ resolver.sdo_pin }} "${resolver_ip_{{ resolver.channel }}_path}/SPI_MOSI"
uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.fsync_internal_name }} {{ resolver.fsync_pin }} "${resolver_ip_{{ resolver.channel }}_path}/AD2S1210_n_fsync"
uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.sclk_internal_name }} {{ resolver.sclk_pin }} "${resolver_ip_{{ resolver.channel }}_path}/SPI_SCLK"
uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.reset_internal_name }} {{ resolver.reset_pin }} "${resolver_ip_{{ resolver.channel }}_path}/AD2S1210_n_reset"
uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.a1_internal_name }} {{ resolver.a1_pin }} "${resolver_ip_{{ resolver.channel }}_path}/AD2S1210_mode_A1"
uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.a0_internal_name }} {{ resolver.a0_pin }} "${resolver_ip_{{ resolver.channel }}_path}/AD2S1210_mode_A0"
uz_pw_resolver_create_output_path $adapter_parent_hier $adapter_hier_path {{ resolver.cs_internal_name }} {{ resolver.cs_pin }} "${resolver_ip_{{ resolver.channel }}_path}/SPI_SS"
uz_pw_resolver_create_input_path $adapter_parent_hier $adapter_hier_path {{ resolver.sdi_internal_name }} {{ resolver.sdi_pin }} "${resolver_ip_{{ resolver.channel }}_path}/SPI_MISO"

set sample_trigger_source_pin_{{ resolver.channel }} "{{ resolver.trigger_source }}"
if {$sample_trigger_source_pin_{{ resolver.channel }} eq "" || [llength [get_bd_pins -quiet $sample_trigger_source_pin_{{ resolver.channel }}]] == 0} {
  puts "WARNING: sample_trigger source '$sample_trigger_source_pin_{{ resolver.channel }}' not found for {{ slot }} resolver channel {{ resolver.channel }}; using zero fallback."
  set sample_trigger_default_path_{{ resolver.channel }} "${adapter_hier_path}/{{ slot }}_resolver_sample_trigger_{{ resolver.channel }}_default_zero"
  uz_pw_resolver_create_xlconstant $sample_trigger_default_path_{{ resolver.channel }} 1 0
  set sample_trigger_source_pin_{{ resolver.channel }} "${sample_trigger_default_path_{{ resolver.channel }}}/dout"
}

set sample_trigger_parent_pin "{{ slot }}_resolver_sample_trigger_{{ resolver.channel }}"
uz_pw_create_hier_pin_if_missing $adapter_parent_hier I $sample_trigger_parent_pin
uz_pw_create_hier_pin_if_missing $adapter_hier_path I $sample_trigger_parent_pin
uz_pw_connect_pin_pair_if_unconnected $sample_trigger_source_pin_{{ resolver.channel }} "${adapter_parent_hier}/${sample_trigger_parent_pin}"
uz_pw_connect_upper_boundary_net_if_unconnected "${adapter_parent_hier}/${sample_trigger_parent_pin}" "${adapter_hier_path}/${sample_trigger_parent_pin}"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${sample_trigger_parent_pin}" "${resolver_ip_{{ resolver.channel }}_path}/sample_trigger"

{% if resolver.pl_enabled %}
set resolver_pl_{{ resolver.channel }}_path "${adapter_hier_path}/{{ resolver.pl_instance_name }}"
uz_pw_create_ip_cell_if_missing $resolver_pl_{{ resolver.channel }}_path {{ resolver_pl_ip.vlnv }}

uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_clock_pin}" "${resolver_pl_{{ resolver.channel }}_path}/IPCORE_CLK"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_clock_pin}" "${resolver_pl_{{ resolver.channel }}_path}/AXI4_Lite_ACLK"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_resetn_pin}" "${resolver_pl_{{ resolver.channel }}_path}/IPCORE_RESETN"
uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${adapter_resetn_pin}" "${resolver_pl_{{ resolver.channel }}_path}/AXI4_Lite_ARESETN"
uz_pw_connect_pin_pair_if_unconnected "${resolver_ip_{{ resolver.channel }}_path}/position_out_m" "${resolver_pl_{{ resolver.channel }}_path}/position_raw"
uz_pw_connect_pin_pair_if_unconnected "${resolver_ip_{{ resolver.channel }}_path}/velocity_out_m" "${resolver_pl_{{ resolver.channel }}_path}/velocity_raw"
uz_pw_connect_pin_pair_if_unconnected "${resolver_ip_{{ resolver.channel }}_path}/valid_m" "${resolver_pl_{{ resolver.channel }}_path}/trigger"
{% endif %}
{% endfor %}

{% for output in resolver_pl_output_paths %}
uz_pw_resolver_create_pl_output_path $adapter_parent_hier $adapter_hier_path {{ output.boundary_name }} "{{ output.source_pin }}" {{ output.left }} {{ output.right }}
{% endfor %}

uz_pw_apply_slot_constraints {{ slot }} [list {{ slot_constraint_names }}] [list "Digital_AdapterBoard_{{ slot }}.xdc"]

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
