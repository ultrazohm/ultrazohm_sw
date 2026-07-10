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

uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/{{ adapter_clock_pin }}
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/{{ adapter_resetn_pin }}

{% for ip in ip_cores %}
set {{ ip.instance_name }}_path ${adapter_hier_path}/{{ ip.instance_name }}
if {[llength [get_bd_cells -quiet ${{ ip.instance_name }}_path]] == 0} {
{% if ip.is_module_ref %}
  set {{ ip.instance_name }} [create_bd_cell -type module -reference {{ ip.reference }} ${{ ip.instance_name }}_path]
{% endif %}
{% if ip.is_ip %}
  set {{ ip.instance_name }} [create_bd_cell -type ip -vlnv {{ ip.vlnv }} ${{ ip.instance_name }}_path]
{% endif %}
} else {
  puts "Reusing existing IP ${{ ip.instance_name }}_path"
}
# Module: {{ ip.module }}
{% if ip.has_properties %}
uz_pw_set_property_dict_if_objects [list {{ ip.property_dict }}] [get_bd_cells -quiet ${{ ip.instance_name }}_path] ${{ ip.instance_name }}_path
{% endif %}
{% endfor %}

{% for clock in clock_connections %}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ adapter_clock_pin }} {{ clock.ip_pin_path }}
{% endfor %}
{% for reset in reset_connections %}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ adapter_resetn_pin }} {{ reset.ip_pin_path }}
{% endfor %}

{% for connection in pin_connections %}
uz_pw_connect_pin_pair_if_unconnected {{ connection.source_path }} {{ connection.sink_path }}
{% endfor %}

{% for signal in signals %}
uz_pw_create_bd_pin_if_missing {{ signal.direction }} ${adapter_hier_path}/{{ signal.adapter_pin_name }} "{{ signal.left }}" "{{ signal.right }}"
{% if signal.has_boundary %}
uz_pw_create_bd_pin_if_missing {{ signal.direction }} ${adapter_parent_hier}/{{ signal.boundary_name }} "{{ signal.left }}" "{{ signal.right }}"
{% endif %}
{% if signal.has_external_port %}
{{ signal.external_port_creation_commands }}
{% endif %}
{% if signal.connects_to_ip %}
uz_pw_connect_pin_pair_if_unconnected {{ signal.core_source }} {{ signal.core_sink }}
{% endif %}
{% if signal.has_boundary %}
uz_pw_connect_pin_pair_if_unconnected {{ signal.boundary_source }} {{ signal.boundary_sink }}
{% endif %}
{% if signal.has_external_port %}
{{ signal.external_port_connection_commands }}
{% endif %}
{% endfor %}

{% for trigger in trigger_inputs %}
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/{{ trigger.adapter_pin_name }}
uz_pw_create_bd_pin_if_missing I ${adapter_parent_hier}/{{ trigger.boundary_name }}
uz_pw_connect_upper_boundary_net_if_unconnected {{ trigger.source_path }} ${adapter_parent_hier}/{{ trigger.boundary_name }}
uz_pw_connect_pin_pair_if_unconnected ${adapter_parent_hier}/{{ trigger.boundary_name }} ${adapter_hier_path}/{{ trigger.adapter_pin_name }}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ trigger.adapter_pin_name }} {{ trigger.ip_pin_path }}
{% endfor %}

{% if has_constraints %}
uz_pw_apply_slot_constraints {{ slot }} [list {{ slot_constraint_names }}] [list {{ enable_constraint_names }}]
{% endif %}

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
