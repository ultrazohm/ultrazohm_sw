# -----------------------------------------------------------------------------
# {{ slot }}: {{ card_name }}
# -----------------------------------------------------------------------------
{% for note in notes %}
# NOTE: {{ note }}
{% endfor %}

puts "Adding {{ card_name }} for slot {{ slot }}"

set digital_adapter_hier uz_digital_adapter
set adapter_hier_name {{ slot }}_adapter
set adapter_hier_path ${digital_adapter_hier}/${adapter_hier_name}

uz_pw_create_hier_if_missing ${digital_adapter_hier}
uz_pw_create_hier_if_missing ${adapter_hier_path}

uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aclk
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aresetn

{% for ip in ip_cores %}
set {{ ip.instance_name }}_path ${adapter_hier_path}/{{ ip.instance_name }}
if {[llength [get_bd_cells -quiet ${{ ip.instance_name }}_path]] == 0} {
  set {{ ip.instance_name }} [create_bd_cell -type ip -vlnv {{ ip.vlnv }} ${{ ip.instance_name }}_path]
} else {
  puts "Reusing existing IP ${{ ip.instance_name }}_path"
}
# Module: {{ ip.module }}
{% endfor %}

{% for clock in clock_connections %}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/aclk {{ clock.ip_pin_path }}
{% endfor %}
{% for reset in reset_connections %}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/aresetn {{ reset.ip_pin_path }}
{% endfor %}

{% for signal in signals %}
uz_pw_create_bd_pin_if_missing {{ signal.direction }} ${adapter_hier_path}/{{ signal.adapter_pin_name }}
{% if signal.has_boundary %}
uz_pw_create_bd_pin_if_missing {{ signal.direction }} ${digital_adapter_hier}/{{ signal.boundary_name }}
{% endif %}
{% if signal.has_external_port %}
uz_pw_create_bd_port_if_missing {{ signal.direction }} {{ signal.external_port }}
{% endif %}
{% if signal.connects_to_ip %}
uz_pw_connect_pin_pair_if_unconnected {{ signal.core_source }} {{ signal.core_sink }}
{% endif %}
{% if signal.has_boundary %}
uz_pw_connect_pin_pair_if_unconnected {{ signal.boundary_source }} {{ signal.boundary_sink }}
{% endif %}
{% if signal.has_external_port %}
uz_pw_connect_port_if_unconnected ${digital_adapter_hier}/{{ signal.boundary_name }} {{ signal.external_port }}
{% endif %}
{% endfor %}

{% for trigger in trigger_inputs %}
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/{{ trigger.adapter_pin_name }}
uz_pw_create_bd_pin_if_missing I ${digital_adapter_hier}/{{ trigger.boundary_name }}
uz_pw_connect_upper_boundary_net_if_unconnected {{ trigger.source_path }} ${digital_adapter_hier}/{{ trigger.boundary_name }}
uz_pw_connect_pin_pair_if_unconnected ${digital_adapter_hier}/{{ trigger.boundary_name }} ${adapter_hier_path}/{{ trigger.adapter_pin_name }}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ trigger.adapter_pin_name }} {{ trigger.ip_pin_path }}
{% endfor %}

{% if has_constraints %}
uz_pw_apply_slot_constraints {{ slot }} {{ packed_constraint }} {{ adapter_constraint }}
{% endif %}

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
