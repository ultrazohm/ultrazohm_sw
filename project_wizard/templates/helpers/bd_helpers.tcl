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

proc uz_pw_create_bd_pin_if_missing {direction pin_path {left ""} {right ""}} {
  if {[llength [get_bd_pins -quiet $pin_path]] == 0} {
    if {$left ne "" && $right ne ""} {
      create_bd_pin -dir $direction -from $left -to $right $pin_path
    } else {
      create_bd_pin -dir $direction $pin_path
    }
  } else {
    puts "Reusing existing pin $pin_path"
  }
}

proc uz_pw_create_bd_port_if_missing {direction port_name {left ""} {right ""}} {
  set old_instance [current_bd_instance .]
  current_bd_instance [get_bd_cells /]
  if {[llength [get_bd_ports -quiet $port_name]] == 0} {
    if {$left ne "" && $right ne ""} {
      create_bd_port -dir $direction -from $left -to $right $port_name
    } else {
      create_bd_port -dir $direction $port_name
    }
  } else {
    puts "Reusing existing port $port_name"
  }
  current_bd_instance $old_instance
}

proc uz_pw_create_hier_pin_if_missing {hier_path direction pin_name {left ""} {right ""}} {
  set old_instance [current_bd_instance .]
  current_bd_instance [get_bd_cells $hier_path]
  set pin_path "${hier_path}/${pin_name}"
  if {[llength [get_bd_pins -quiet $pin_path]] == 0} {
    if {$left ne "" && $right ne ""} {
      create_bd_pin -dir $direction -from $left -to $right $pin_name
    } else {
      create_bd_pin -dir $direction $pin_name
    }
  } else {
    puts "Reusing existing pin $pin_path"
  }
  current_bd_instance $old_instance
}

proc uz_pw_disconnect_pin_path_from_all_nets {pin_path} {
  foreach pin [get_bd_pins -quiet $pin_path] {
    foreach net [get_bd_nets -quiet -of_objects $pin] {
      uz_pw_try_disconnect_bd_net $net $pin
    }
  }
}

proc uz_pw_delete_pin_if_exists {pin_path} {
  set pins [get_bd_pins -quiet $pin_path]
  if {[llength $pins] == 0} {
    return
  }
  foreach pin $pins {
    foreach net [get_bd_nets -quiet -of_objects $pin] {
      uz_pw_try_disconnect_bd_net $net $pin
    }
  }
  delete_bd_objs $pins
}

proc uz_pw_create_ip_cell_if_missing {cell_path vlnv} {
  if {[llength [get_bd_cells -quiet $cell_path]] == 0} {
    set old_instance [current_bd_instance .]
    set path_parts [split $cell_path "/"]
    set cell_name [lindex $path_parts end]
    set parent_path [join [lrange $path_parts 0 end-1] "/"]
    if {$parent_path eq ""} {
      set parent_path "/"
    }
    current_bd_instance [get_bd_cells $parent_path]
    create_bd_cell -type ip -vlnv $vlnv $cell_name
    current_bd_instance $old_instance
  } else {
    puts "Reusing existing cell $cell_path"
  }
}

proc uz_pw_delete_cell_if_exists {cell_path} {
  set cells [get_bd_cells -quiet $cell_path]
  if {[llength $cells] == 0} {
    return
  }
  foreach pin [get_bd_pins -quiet ${cell_path}/*] {
    foreach net [get_bd_nets -quiet -of_objects $pin] {
      uz_pw_try_disconnect_bd_net $net $pin
    }
  }
  foreach intf_pin [get_bd_intf_pins -quiet ${cell_path}/*] {
    foreach intf_net [get_bd_intf_nets -quiet -of_objects $intf_pin] {
      catch {delete_bd_objs $intf_net}
    }
  }
  delete_bd_objs $cells
}

proc uz_pw_set_property_dict_if_objects {property_dict objects label} {
  if {[llength $objects] == 0} {
    puts "WARNING: Could not set properties on $label because no object was found"
    return
  }
  set_property -dict $property_dict $objects
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

proc uz_pw_connect_pins_to_shared_net {pin_paths} {
  set pins {}
  foreach pin_path $pin_paths {
    set pin [get_bd_pins -quiet $pin_path]
    if {[llength $pin] == 0} {
      puts "WARNING: Shared-net pin not found: $pin_path"
      continue
    }
    lappend pins $pin
  }
  if {[llength $pins] < 2} {
    return
  }

  set selected_net ""
  foreach pin $pins {
    set nets [get_bd_nets -quiet -of_objects $pin]
    if {[llength $nets] > 0} {
      set selected_net [lindex $nets 0]
      break
    }
  }

  if {$selected_net eq ""} {
    uz_pw_try_connect_bd_net {*}$pins
    return
  }

  set net_name [get_property NAME $selected_net]
  foreach pin $pins {
    set already_connected 0
    foreach net [get_bd_nets -quiet -of_objects $pin] {
      if {$net eq $selected_net} {
        set already_connected 1
      }
    }
    if {!$already_connected} {
      uz_pw_try_connect_bd_net -net $net_name $pin
    }
  }
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
  if {[llength $adapter_constraint] == 0 && [llength $packed_constraint] > 0} {
    set packed_path [lindex $packed_constraint 0]
    set candidate_path [file normalize [file join [file dirname $packed_path] $adapter_constraint_name]]
    if {[file exists $candidate_path]} {
      puts "Adding adapter constraint file $candidate_path"
      add_files -fileset constrs_1 $candidate_path
      set adapter_constraint [get_files -quiet $adapter_constraint_name]
    }
  }
  if {[llength $adapter_constraint] > 0} {
    uz_pw_set_property_if_objects is_enabled true $adapter_constraint $adapter_constraint_name
  } else {
    puts "WARNING: Could not find $adapter_constraint_name"
  }
}
