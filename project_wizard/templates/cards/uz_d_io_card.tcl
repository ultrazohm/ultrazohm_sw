# -----------------------------------------------------------------------------
# {{ slot }}: {{ card_name }}
# -----------------------------------------------------------------------------
{% for note in notes %}
# NOTE: {{ note }}
{% endfor %}

puts "Adding {{ card_name }} for slot {{ slot }}"

set adapter_parent_hier {{ adapter_parent_hier }}
set adapter_hier_name {{ slot }}_adapter
set adapter_hier_path ${adapter_parent_hier}/${adapter_hier_name}

uz_pw_create_hier_if_missing ${adapter_parent_hier}
uz_pw_create_hier_if_missing ${adapter_hier_path}

# Remove known non-slot-prefixed pins from previous D-slot card templates.
# Do not bulk-delete hierarchy pins here because AXI interface scalar pins are
# represented as BD pins and cannot be removed individually.
uz_pw_delete_pin_if_exists ${adapter_hier_path}/Enable_Gate
uz_pw_delete_pin_if_exists ${adapter_hier_path}/Gate_Signals_2L
{% for pwm_source in pwm_sources %}
uz_pw_delete_pin_if_exists ${adapter_hier_path}/{{ pwm_source.boundary_name }}
{% endfor %}

proc uz_pw_io_create_slot_signal {direction adapter_parent_hier adapter_hier_path internal_name external_name {left ""} {right ""}} {
  uz_pw_create_bd_port_if_missing $direction $external_name "$left" "$right"
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier $direction $internal_name "$left" "$right"
  uz_pw_create_hier_pin_if_missing $adapter_hier_path $direction $internal_name "$left" "$right"

  if {$direction ne "O"} {
    uz_pw_connect_port_if_unconnected "${adapter_parent_hier}/${internal_name}" $external_name
    uz_pw_connect_pin_pair_if_unconnected "${adapter_parent_hier}/${internal_name}" "${adapter_hier_path}/${internal_name}"
  }
}

proc uz_pw_io_connect_slot_output {adapter_parent_hier adapter_hier_path internal_name external_name} {
  uz_pw_connect_pin_pair_if_unconnected "${adapter_hier_path}/${internal_name}" "${adapter_parent_hier}/${internal_name}"
  uz_pw_connect_port_if_unconnected "${adapter_parent_hier}/${internal_name}" $external_name
}

proc uz_pw_io_create_xlslice {cell_path din_width bit_index} {
  uz_pw_create_ip_cell_if_missing $cell_path xilinx.com:ip:xlslice
  uz_pw_set_property_dict_if_objects [list CONFIG.DIN_WIDTH $din_width CONFIG.DIN_FROM $bit_index CONFIG.DIN_TO $bit_index CONFIG.DOUT_WIDTH {1}] [get_bd_cells -quiet $cell_path] $cell_path
}

proc uz_pw_io_create_xlconstant {cell_path width value} {
  uz_pw_create_ip_cell_if_missing $cell_path xilinx.com:ip:xlconstant
  uz_pw_set_property_dict_if_objects [list CONFIG.CONST_WIDTH $width CONFIG.CONST_VAL $value] [get_bd_cells -quiet $cell_path] $cell_path
}

uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/{{ adapter_clock_pin }}
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/{{ adapter_resetn_pin }}

{% if has_axi_gpio %}
set io_gpio_path ${adapter_hier_path}/{{ axi_gpio_instance_name }}
uz_pw_create_ip_cell_if_missing $io_gpio_path xilinx.com:ip:axi_gpio
uz_pw_set_property_dict_if_objects [list CONFIG.C_GPIO_WIDTH 30 CONFIG.C_ALL_INPUTS {{ axi_gpio_all_inputs }} CONFIG.C_ALL_OUTPUTS {{ axi_gpio_all_outputs }} CONFIG.C_IS_DUAL 0] [get_bd_cells -quiet $io_gpio_path] $io_gpio_path
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ adapter_clock_pin }} ${io_gpio_path}/s_axi_aclk
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ adapter_resetn_pin }} ${io_gpio_path}/s_axi_aresetn
{% endif %}

{% if has_axi_input_concat %}
set io_gpio_i_concat_path ${adapter_hier_path}/{{ slot_lower }}_io_gpio_i_concat
uz_pw_create_ip_cell_if_missing $io_gpio_i_concat_path xilinx.com:ip:xlconcat
uz_pw_set_property_dict_if_objects [list CONFIG.NUM_PORTS 30] [get_bd_cells -quiet $io_gpio_i_concat_path] $io_gpio_i_concat_path
{% endif %}

{% if has_axi_input_zero %}
set io_gpio_zero_path ${adapter_hier_path}/{{ slot_lower }}_io_gpio_zero
uz_pw_io_create_xlconstant $io_gpio_zero_path 1 0
{% endif %}

{% for pwm_source in pwm_sources %}
set {{ pwm_source.variable_name }} "{{ pwm_source.source_path }}"
if {${{ pwm_source.variable_name }} eq "" || [llength [get_bd_pins -quiet ${{ pwm_source.variable_name }}]] == 0} {
  puts "WARNING: PWM vector source '${{ pwm_source.variable_name }}' not found for {{ slot }} IO card; using zero fallback."
  set {{ pwm_source.variable_name }}_zero_path "${adapter_hier_path}/{{ pwm_source.boundary_name }}_zero"
  uz_pw_io_create_xlconstant ${{ pwm_source.variable_name }}_zero_path 6 0x00
  set {{ pwm_source.variable_name }} "${{{ pwm_source.variable_name }}_zero_path}/dout"
} else {
  uz_pw_create_hier_pin_if_missing $adapter_parent_hier I {{ pwm_source.boundary_name }} 5 0
  uz_pw_create_hier_pin_if_missing $adapter_hier_path I {{ pwm_source.boundary_name }} 5 0
  uz_pw_connect_pin_pair_if_unconnected ${{ pwm_source.variable_name }} "${adapter_parent_hier}/{{ pwm_source.boundary_name }}"
  uz_pw_connect_upper_boundary_net_if_unconnected "${adapter_parent_hier}/{{ pwm_source.boundary_name }}" "${adapter_hier_path}/{{ pwm_source.boundary_name }}"
  set {{ pwm_source.variable_name }} "${adapter_hier_path}/{{ pwm_source.boundary_name }}"
}
{% endfor %}

{% for pin in io_pins %}
{% if pin.is_tx %}
uz_pw_io_create_slot_signal O $adapter_parent_hier $adapter_hier_path {{ pin.pin_name }} {{ pin.pin_name }}
{% endif %}
{% if pin.is_rx %}
uz_pw_io_create_slot_signal I $adapter_parent_hier $adapter_hier_path {{ pin.pin_name }} {{ pin.pin_name }}
{% endif %}

{% if pin.is_axi_tx %}
set {{ pin.helper_name }}_slice_path ${adapter_hier_path}/{{ pin.helper_name }}_slice
uz_pw_io_create_xlslice ${{ pin.helper_name }}_slice_path 30 {{ pin.index }}
uz_pw_connect_pin_pair_if_unconnected ${io_gpio_path}/gpio_io_o ${{ pin.helper_name }}_slice_path/Din
uz_pw_connect_pin_pair_if_unconnected ${{ pin.helper_name }}_slice_path/Dout ${adapter_hier_path}/{{ pin.pin_name }}
{% endif %}
{% if pin.is_axi_rx %}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ pin.pin_name }} ${io_gpio_i_concat_path}/In{{ pin.index }}
{% endif %}
{% if pin.is_top_level_tx %}
uz_pw_create_bd_port_if_missing I {{ pin.user_port_name }}
uz_pw_create_hier_pin_if_missing $adapter_parent_hier I {{ pin.user_port_name }}
uz_pw_create_hier_pin_if_missing $adapter_hier_path I {{ pin.user_port_name }}
uz_pw_connect_port_to_pin_if_unconnected {{ pin.user_port_name }} ${adapter_parent_hier}/{{ pin.user_port_name }}
uz_pw_connect_upper_boundary_net_if_unconnected ${adapter_parent_hier}/{{ pin.user_port_name }} ${adapter_hier_path}/{{ pin.user_port_name }}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ pin.user_port_name }} ${adapter_hier_path}/{{ pin.pin_name }}
{% endif %}
{% if pin.is_top_level_rx %}
uz_pw_create_bd_port_if_missing O {{ pin.user_port_name }}
uz_pw_connect_pin_to_port_if_unconnected ${adapter_hier_path}/{{ pin.pin_name }} {{ pin.user_port_name }}
{% endif %}
{% if pin.is_pwm %}
set {{ pin.helper_name }}_pwm_slice_path ${adapter_hier_path}/{{ pin.helper_name }}_pwm_slice
uz_pw_io_create_xlslice ${{ pin.helper_name }}_pwm_slice_path 6 {{ pin.pwm_bit }}
uz_pw_connect_pin_pair_if_unconnected ${{ pin.pwm_source_variable }} ${{ pin.helper_name }}_pwm_slice_path/Din
uz_pw_connect_pin_pair_if_unconnected ${{ pin.helper_name }}_pwm_slice_path/Dout ${adapter_hier_path}/{{ pin.pin_name }}
{% endif %}
{% if pin.is_source_pin %}
uz_pw_create_hier_pin_if_missing $adapter_parent_hier I {{ pin.source_boundary_name }}
uz_pw_create_hier_pin_if_missing $adapter_hier_path I {{ pin.source_boundary_name }}
uz_pw_connect_pin_pair_if_unconnected {{ pin.source_path }} ${adapter_parent_hier}/{{ pin.source_boundary_name }}
uz_pw_connect_upper_boundary_net_if_unconnected ${adapter_parent_hier}/{{ pin.source_boundary_name }} ${adapter_hier_path}/{{ pin.source_boundary_name }}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ pin.source_boundary_name }} ${adapter_hier_path}/{{ pin.pin_name }}
{% endif %}
{% if pin.is_constant %}
set {{ pin.helper_name }}_const_path ${adapter_hier_path}/{{ pin.helper_name }}_const
uz_pw_io_create_xlconstant ${{ pin.helper_name }}_const_path 1 {{ pin.constant_value }}
uz_pw_connect_pin_pair_if_unconnected ${{ pin.helper_name }}_const_path/dout ${adapter_hier_path}/{{ pin.pin_name }}
{% endif %}
{% if pin.is_tx %}
uz_pw_io_connect_slot_output $adapter_parent_hier $adapter_hier_path {{ pin.pin_name }} {{ pin.pin_name }}
{% endif %}
{% endfor %}

{% for zero_input in axi_input_zero_indices %}
uz_pw_connect_pin_pair_if_unconnected ${io_gpio_zero_path}/dout ${io_gpio_i_concat_path}/In{{ zero_input.index }}
{% endfor %}

{% if has_axi_input_concat %}
uz_pw_connect_pin_pair_if_unconnected ${io_gpio_i_concat_path}/dout ${io_gpio_path}/gpio_io_i
{% endif %}

{% if has_constraints %}
uz_pw_apply_slot_constraints {{ slot }} [list {{ slot_constraint_names }}] [list {{ enable_constraint_names }}]
{% endif %}

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
