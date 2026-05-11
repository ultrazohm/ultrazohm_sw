# {{ option_label }}: {{ choice_label }}
set digital_adapter_hier uz_digital_adapter
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

proc uz_pw_create_bd_port_if_missing {direction port_name} {
  set old_instance [current_bd_instance .]
  current_bd_instance [get_bd_cells /]
  if {[llength [get_bd_ports -quiet $port_name]] == 0} {
    create_bd_port -dir $direction $port_name
  } else {
    puts "Reusing existing port $port_name"
  }
  current_bd_instance $old_instance
}

proc uz_pw_connect_net_if_unconnected {source_pin sink_pin} {
  uz_pw_connect_net_if_unconnected_with_args $source_pin $sink_pin [list]
}

proc uz_pw_connect_upper_boundary_net_if_unconnected {source_pin sink_pin} {
  uz_pw_connect_net_if_unconnected_with_args $source_pin $sink_pin [list -boundary_type upper]
}

proc uz_pw_connect_net_in_hierarchy_if_unconnected {hier_path source_pin sink_pin} {
  set hier [get_bd_cells -quiet $hier_path]
  if {[llength $hier] == 0} {
    puts "WARNING: Hierarchy not found: $hier_path"
    return
  }

  set old_instance [current_bd_instance .]
  current_bd_instance $hier
  uz_pw_connect_net_if_unconnected $source_pin $sink_pin
  current_bd_instance $old_instance
}

proc uz_pw_connect_pin_pair_if_unconnected {source_pin sink_pin} {
  set source [get_bd_pins -quiet $source_pin]
  set sink [get_bd_pins -quiet $sink_pin]
  if {[llength $source] == 0} {
    puts "WARNING: Source pin not found: $source_pin"
    return
  }
  if {[llength $sink] == 0} {
    puts "WARNING: Sink pin not found: $sink_pin"
    return
  }

  set source_nets [get_bd_nets -quiet -of_objects $source]
  set sink_nets [get_bd_nets -quiet -of_objects $sink]
  foreach source_net $source_nets {
    if {[lsearch -exact $sink_nets $source_net] >= 0} {
      return
    }
  }

  foreach sink_net $sink_nets {
    uz_pw_try_disconnect_bd_net $sink_net $sink
  }

  uz_pw_try_connect_bd_net $source $sink
}

proc uz_pw_connect_net_if_unconnected_with_args {source_pin sink_pin connect_args} {
  set source [get_bd_pins -quiet $source_pin]
  set sink [get_bd_pins -quiet $sink_pin]
  if {[llength $source] == 0} {
    puts "WARNING: Source pin not found: $source_pin"
    return
  }
  if {[llength $sink] == 0} {
    puts "WARNING: Sink pin not found: $sink_pin"
    return
  }
  set source_nets [get_bd_nets -quiet -of_objects $source]
  set sink_nets [get_bd_nets -quiet -of_objects $sink]
  if {[llength $source_nets] == 0 && [llength $sink_nets] == 0} {
    uz_pw_try_connect_bd_net {*}$connect_args $source $sink
    return
  }
  if {[llength $source_nets] > 0 && [llength $sink_nets] == 0} {
    set net_name [get_property NAME [lindex $source_nets 0]]
    uz_pw_try_connect_bd_net {*}$connect_args -net $net_name $sink
    return
  }
  if {[llength $source_nets] == 0 && [llength $sink_nets] > 0} {
    set net_name [get_property NAME [lindex $sink_nets 0]]
    uz_pw_try_connect_bd_net {*}$connect_args -net $net_name $source
    return
  }
  if {[lindex $source_nets 0] ne [lindex $sink_nets 0]} {
    puts "Refreshing stale net on $sink_pin"
    uz_pw_try_disconnect_bd_net [lindex $sink_nets 0] $sink
    set net_name [get_property NAME [lindex $source_nets 0]]
    uz_pw_try_connect_bd_net {*}$connect_args -net $net_name $sink
  }
}

proc uz_pw_connect_port_if_unconnected {source_pin port_name} {
  set source [get_bd_pins -quiet $source_pin]
  if {[llength $source] == 0} {
    puts "WARNING: Source pin not found: $source_pin"
    return
  }
  set old_instance [current_bd_instance .]
  current_bd_instance [get_bd_cells /]
  set port [get_bd_ports -quiet $port_name]
  current_bd_instance $old_instance
  if {[llength $port] == 0} {
    puts "WARNING: Port not found: $port_name"
    return
  }
  set source_nets [get_bd_nets -quiet -of_objects $source]
  set port_nets [get_bd_nets -quiet -of_objects $port]
  if {[llength $source_nets] == 0 && [llength $port_nets] == 0} {
    uz_pw_try_connect_bd_net $source $port
    return
  }
  if {[llength $source_nets] > 0 && [llength $port_nets] == 0} {
    set net_name [get_property NAME [lindex $source_nets 0]]
    uz_pw_try_connect_bd_net -net $net_name $port
    return
  }
  if {[llength $source_nets] == 0 && [llength $port_nets] > 0} {
    set net_name [get_property NAME [lindex $port_nets 0]]
    uz_pw_try_connect_bd_net -net $net_name $source
    return
  }
  if {[lindex $source_nets 0] ne [lindex $port_nets 0]} {
    puts "Refreshing stale net on port $port_name"
    uz_pw_try_disconnect_bd_net [lindex $port_nets 0] $port
    set net_name [get_property NAME [lindex $source_nets 0]]
    uz_pw_try_connect_bd_net -net $net_name $port
  }
}

proc uz_pw_try_disconnect_bd_net {net endpoint} {
  if {![catch {disconnect_bd_net $net $endpoint}]} {
    return
  }
  if {![catch {disconnect_bd_net $endpoint}]} {
    return
  }
  set net_name [get_property NAME $net]
  if {![catch {disconnect_bd_net -net $net_name $endpoint}]} {
    return
  }
  puts "WARNING: disconnect_bd_net failed for $endpoint"
}

proc uz_pw_try_connect_bd_net {args} {
  if {[catch {uplevel 1 [linsert $args 0 connect_bd_net]} result]} {
    if {[string match "*already connected*" $result] || [string match "*all ports/pins are already connected*" $result]} {
      return
    }
    puts "WARNING: connect_bd_net failed: $result"
  }
}

proc uz_pw_set_property_if_objects {property_name property_value objects label} {
  if {[llength $objects] == 0} {
    puts "WARNING: Could not set $property_name on $label because no object was found"
    return
  }
  set_property $property_name $property_value $objects
}

uz_pw_create_hier_if_missing ${digital_adapter_hier}
uz_pw_create_hier_if_missing ${adapter_hier_path}
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aclk
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aresetn

set ip_path ${adapter_hier_path}/{{ ip.instance_name }}
if {[llength [get_bd_cells -quiet $ip_path]] == 0} {
  set {{ ip.instance_name }} [create_bd_cell -type ip -vlnv {{ ip.vlnv }} $ip_path]
} else {
  puts "Reusing existing IP $ip_path"
}
# Module: {{ ip.module }}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/aclk ${ip_path}/AXI4_Lite_ACLK
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/aresetn ${ip_path}/AXI4_Lite_ARESETN
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/aclk ${ip_path}/IPCORE_CLK
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/aresetn ${ip_path}/IPCORE_RESETN

{% for port in ports %}
uz_pw_create_bd_pin_if_missing {{ port.direction }} ${adapter_hier_path}/{{ port.adapter_pin_name }}
uz_pw_create_bd_pin_if_missing {{ port.direction }} ${digital_adapter_hier}/{{ port.boundary_name }}
uz_pw_create_bd_port_if_missing {{ port.direction }} {{ port.pin }}
uz_pw_connect_net_if_unconnected {{ port.core_source }} {{ port.core_sink }}
uz_pw_connect_net_if_unconnected {{ port.boundary_source }} {{ port.boundary_sink }}
uz_pw_connect_port_if_unconnected ${digital_adapter_hier}/{{ port.boundary_name }} {{ port.pin }}
{% endfor %}

{% for trigger in trigger_inputs %}
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/{{ trigger.adapter_pin_name }}
uz_pw_create_bd_pin_if_missing I ${digital_adapter_hier}/{{ trigger.boundary_name }}
uz_pw_connect_upper_boundary_net_if_unconnected {{ trigger.source_path }} ${digital_adapter_hier}/{{ trigger.boundary_name }}
uz_pw_connect_pin_pair_if_unconnected ${digital_adapter_hier}/{{ trigger.boundary_name }} ${adapter_hier_path}/{{ trigger.adapter_pin_name }}
uz_pw_connect_pin_pair_if_unconnected ${adapter_hier_path}/{{ trigger.adapter_pin_name }} ${ip_path}/{{ trigger.signal }}
{% endfor %}

{% for output in exposed_outputs %}
uz_pw_create_bd_pin_if_missing O ${digital_adapter_hier}/{{ output.boundary_name }}
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/{{ output.adapter_pin_name }}
uz_pw_connect_net_if_unconnected ${ip_path}/{{ output.signal }} ${adapter_hier_path}/{{ output.adapter_pin_name }}
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/{{ output.adapter_pin_name }} ${digital_adapter_hier}/{{ output.boundary_name }}
{% endfor %}

puts "Switching absolute encoder constraints for slot {{ slot }}"

set packed_constraint [get_files -quiet Digital_{{ slot }}_packed.xdc]
if {[llength $packed_constraint] > 0} {
  uz_pw_set_property_if_objects is_enabled false $packed_constraint Digital_{{ slot }}_packed.xdc
} else {
  puts "WARNING: Could not find Digital_{{ slot }}_packed.xdc"
}

set unpacked_constraint [get_files -quiet Digital_AdapterBoard_{{ slot }}.xdc]
if {[llength $unpacked_constraint] > 0} {
  uz_pw_set_property_if_objects is_enabled true $unpacked_constraint Digital_AdapterBoard_{{ slot }}.xdc
} else {
  puts "WARNING: Could not find Digital_AdapterBoard_{{ slot }}.xdc"
}

# Vitis driver hook: {{ driver }}
