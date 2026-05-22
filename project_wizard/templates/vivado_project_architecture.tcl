# -----------------------------------------------------------------------------
# Project Wizard architecture setup
# -----------------------------------------------------------------------------
# Platform: {{ platform_name }}
# Platform ID: {{ platform_id }}
# Platform revision: {{ platform_revision }}

set project_wizard_origin [pwd]
set project_wizard_platform {{ platform_id }}
set project_wizard_platform_name "{{ platform_name }}"
set project_wizard_platform_revision "{{ platform_revision }}"

puts "Project Wizard: applying adapter card configuration"
puts "Target platform: {{ platform_name }} {{ platform_revision }}"

# TODO: Check that a Vivado project and block design are open.
# Example direction:
#   if {[current_project -quiet] eq ""} { error "No Vivado project open" }
#   if {[current_bd_design -quiet] eq ""} { error "No block design open" }

# TODO: Remove or reuse previously generated Project Wizard hierarchies.
# This should eventually be guarded by generated object names or a user choice.

proc uz_pw_delete_external_ports_for_slot {slot cleanup_patterns} {
  set ports_to_delete {}
  foreach pattern $cleanup_patterns {
    foreach port [get_bd_ports -quiet $pattern] {
      if {[lsearch -exact $ports_to_delete $port] < 0} {
        lappend ports_to_delete $port
      }
    }
  }

  if {[llength $ports_to_delete] > 0} {
    puts "Deleting existing external ports for slot ${slot}: $ports_to_delete"
    delete_bd_objs $ports_to_delete
  } else {
    puts "No existing external ports found for slot ${slot}"
  }
}

proc uz_pw_object_matches_patterns {object cleanup_patterns} {
  set object_name [get_property NAME $object]
  foreach pattern $cleanup_patterns {
    if {[string match $pattern $object_name]} {
      return 1
    }
  }
  return 0
}

proc uz_pw_is_axi_scalar {object} {
  set object_name [get_property NAME $object]
  expr {[string match "D*_AXI*" $object_name] || [string match "S*_AXI*" $object_name] || [string match "M*_AXI*" $object_name]}
}

proc uz_pw_is_axi_interface_pin {object} {
  set object_name [get_property NAME $object]
  expr {[string match "*_AXI" $object_name] || [string match "S*_AXI" $object_name] || [string match "M*_AXI" $object_name]}
}

proc uz_pw_disconnect_pin_from_all_nets {pin} {
  foreach net [get_bd_nets -quiet -of_objects $pin] {
    puts "Disconnecting ${pin} from ${net}"
    if {![catch {disconnect_bd_net $net $pin}]} {
      continue
    }
    if {![catch {disconnect_bd_net $pin}]} {
      continue
    }
    set net_name [get_property NAME $net]
    if {![catch {disconnect_bd_net -net $net_name $pin}]} {
      continue
    }
    puts "WARNING: disconnect_bd_net failed for ${pin}"
  }
}

proc uz_pw_disconnect_intf_pin_from_all_nets {intf_pin} {
  foreach intf_net [get_bd_intf_nets -quiet -of_objects $intf_pin] {
    puts "Deleting interface net connected to ${intf_pin}: ${intf_net}"
    catch {delete_bd_objs $intf_net}
  }
}

proc uz_pw_delete_matching_nets_in_hierarchy {hier_path cleanup_patterns} {
  if {[llength [get_bd_cells -quiet $hier_path]] == 0} {
    return
  }

  set nets_to_delete {}
  foreach net [get_bd_nets -quiet ${hier_path}/*] {
    if {[uz_pw_is_axi_scalar $net]} {
      continue
    }
    if {[uz_pw_object_matches_patterns $net $cleanup_patterns] && [lsearch -exact $nets_to_delete $net] < 0} {
      lappend nets_to_delete $net
    }
  }

  if {[llength $nets_to_delete] > 0} {
    puts "Deleting existing generated nets in ${hier_path}: $nets_to_delete"
    delete_bd_objs $nets_to_delete
  }
}

proc uz_pw_disconnect_matching_pins_in_hierarchy {hier_path cleanup_patterns} {
  if {[llength [get_bd_cells -quiet $hier_path]] == 0} {
    return
  }

  foreach pin [get_bd_pins -quiet ${hier_path}/*] {
    if {[uz_pw_is_axi_scalar $pin]} {
      continue
    }
    if {![uz_pw_object_matches_patterns $pin $cleanup_patterns]} {
      continue
    }

    uz_pw_disconnect_pin_from_all_nets $pin
  }
}

proc uz_pw_delete_matching_pins_in_hierarchy {hier_path cleanup_patterns} {
  if {[llength [get_bd_cells -quiet $hier_path]] == 0} {
    return
  }

  set pins_to_delete {}
  foreach pin [get_bd_pins -quiet ${hier_path}/*] {
    if {[uz_pw_is_axi_scalar $pin]} {
      continue
    }
    if {[uz_pw_object_matches_patterns $pin $cleanup_patterns] && [lsearch -exact $pins_to_delete $pin] < 0} {
      lappend pins_to_delete $pin
    }
  }

  if {[llength $pins_to_delete] > 0} {
    puts "Deleting existing generated pins in ${hier_path}: $pins_to_delete"
    delete_bd_objs $pins_to_delete
  }
}

proc uz_pw_delete_matching_intf_pins_in_hierarchy {hier_path cleanup_patterns} {
  if {[llength [get_bd_cells -quiet $hier_path]] == 0} {
    return
  }

  set intf_pins_to_delete {}
  foreach intf_pin [get_bd_intf_pins -quiet ${hier_path}/*] {
    if {[uz_pw_is_axi_interface_pin $intf_pin]} {
      continue
    }
    if {[uz_pw_object_matches_patterns $intf_pin $cleanup_patterns] && [lsearch -exact $intf_pins_to_delete $intf_pin] < 0} {
      lappend intf_pins_to_delete $intf_pin
    }
  }

  foreach intf_pin $intf_pins_to_delete {
    uz_pw_disconnect_intf_pin_from_all_nets $intf_pin
  }

  if {[llength $intf_pins_to_delete] > 0} {
    puts "Deleting existing generated interface pins in ${hier_path}: $intf_pins_to_delete"
    delete_bd_objs $intf_pins_to_delete
  }
}

{% for slot in configured_slots %}
# TODO: Create or refresh hierarchy for adapter slot {{ slot.slot }}.
# Suggested hierarchy path: uz_digital_adapter/{{ slot.slot }}_adapter or uz_analog_adapter/{{ slot.slot }}_adapter
uz_pw_delete_external_ports_for_slot {{ slot.slot }} [list {{ slot.cleanup_patterns }}]
uz_pw_disconnect_matching_pins_in_hierarchy uz_digital_adapter/{{ slot.slot }}_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_disconnect_matching_pins_in_hierarchy uz_digital_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_disconnect_matching_pins_in_hierarchy uz_analog_adapter/{{ slot.slot }}_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_disconnect_matching_pins_in_hierarchy uz_analog_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_nets_in_hierarchy uz_digital_adapter/{{ slot.slot }}_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_nets_in_hierarchy uz_digital_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_nets_in_hierarchy uz_analog_adapter/{{ slot.slot }}_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_nets_in_hierarchy uz_analog_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_intf_pins_in_hierarchy uz_digital_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_intf_pins_in_hierarchy uz_analog_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_pins_in_hierarchy uz_digital_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_pins_in_hierarchy uz_digital_adapter/{{ slot.slot }}_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_pins_in_hierarchy uz_analog_adapter [list {{ slot.cleanup_patterns }}]
uz_pw_delete_matching_pins_in_hierarchy uz_analog_adapter/{{ slot.slot }}_adapter [list {{ slot.cleanup_patterns }}]
{% endfor %}

{% for cpld in slot_cplds %}
# Slot CPLD {{ cpld.slot }}: {{ cpld.program_name }} ({{ cpld.program_id }})
{% endfor %}
