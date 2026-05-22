# -----------------------------------------------------------------------------
# Shared block-design helper procedures for Project Wizard generated TCL.
# -----------------------------------------------------------------------------

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

proc uz_pw_connect_net_if_unconnected {source_pin sink_pin} {
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
    uz_pw_try_connect_bd_net $source $sink
    return
  }
  if {[llength $source_nets] > 0 && [llength $sink_nets] == 0} {
    set net_name [get_property NAME [lindex $source_nets 0]]
    uz_pw_try_connect_bd_net -net $net_name $sink
    return
  }
  if {[llength $source_nets] == 0 && [llength $sink_nets] > 0} {
    set net_name [get_property NAME [lindex $sink_nets 0]]
    uz_pw_try_connect_bd_net -net $net_name $source
    return
  }
  if {[lindex $source_nets 0] ne [lindex $sink_nets 0]} {
    puts "Refreshing stale net on $sink_pin"
    uz_pw_try_disconnect_bd_net [lindex $sink_nets 0] $sink
    set net_name [get_property NAME [lindex $source_nets 0]]
    uz_pw_try_connect_bd_net -net $net_name $sink
  }
}

proc uz_pw_connect_upper_boundary_net_if_unconnected {source_pin sink_pin} {
  set source [get_bd_pins -quiet $source_pin]
  set sink [get_bd_pins -quiet $sink_pin]
  if {[llength $source] == 0 || [llength $sink] == 0} {
    puts "WARNING: Could not connect upper boundary net from $source_pin to $sink_pin"
    return
  }
  uz_pw_try_connect_bd_net -boundary_type upper $source $sink
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

proc uz_pw_set_property_if_objects {property_name property_value objects label} {
  if {[llength $objects] == 0} {
    puts "WARNING: Could not set $property_name on $label because no object was found"
    return
  }
  set_property $property_name $property_value $objects
}

proc uz_pw_apply_slot_constraints {slot packed_constraint_name adapter_constraint_name} {
  puts "Switching adapter constraints for slot ${slot}"

  set packed_constraint [get_files -quiet $packed_constraint_name]
  if {[llength $packed_constraint] > 0} {
    uz_pw_set_property_if_objects is_enabled false $packed_constraint $packed_constraint_name
  } else {
    puts "WARNING: Could not find $packed_constraint_name"
  }

  set adapter_constraint [get_files -quiet $adapter_constraint_name]
  if {[llength $adapter_constraint] > 0} {
    uz_pw_set_property_if_objects is_enabled true $adapter_constraint $adapter_constraint_name
  } else {
    puts "WARNING: Could not find $adapter_constraint_name"
  }
}
