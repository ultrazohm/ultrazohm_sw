# {{ option_label }}: {{ choice_label }}
{% if enabled %}
set digital_adapter_hier uz_digital_Adapter
set adapter_hier_name {{ slot }}_adapter
set adapter_hier_path ${digital_adapter_hier}/${adapter_hier_name}

proc uz_pw_create_hier_if_missing {hier_path} {
  if {[llength [get_bd_cells -quiet $hier_path]] == 0} {
    create_bd_cell -type hier $hier_path
  } else {
    puts "Reusing existing hierarchy $hier_path"
  }
}

proc uz_pw_create_bd_pin_if_missing {direction pin_path} {
  if {[llength [get_bd_pins -quiet $pin_path]] == 0} {
    create_bd_pin -dir $direction $pin_path
  } else {
    puts "Reusing existing pin $pin_path"
  }
}

uz_pw_create_hier_if_missing ${digital_adapter_hier}
uz_pw_create_hier_if_missing ${adapter_hier_path}
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aclk
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aresetn

{% for ip in ip_cores %}
set ip_path ${adapter_hier_path}/{{ ip.instance_name }}
if {[llength [get_bd_cells -quiet $ip_path]] == 0} {
  set {{ ip.instance_name }} [create_bd_cell -type ip -vlnv {{ ip.vlnv }} $ip_path]
} else {
  puts "Reusing existing IP $ip_path"
}
# Module: {{ ip.module }}
connect_bd_net [get_bd_pins ${adapter_hier_path}/aclk] [get_bd_pins ${ip_path}/AXI4_Lite_ACLK]
connect_bd_net [get_bd_pins ${adapter_hier_path}/aresetn] [get_bd_pins ${ip_path}/AXI4_Lite_ARESETN]
{% endfor %}
{% for port in ports %}
# {{ port.signal }} ({{ port.direction }}) -> {{ port.pin }}
{% endfor %}
{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
{% endif %}
