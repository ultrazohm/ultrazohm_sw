# -----------------------------------------------------------------------------
# {{ slot }}: No adapter board
# -----------------------------------------------------------------------------

puts "Removing adapter slot {{ slot }} because no adapter board is selected"

set slot "{{ slot }}"
set adapter_hier_name "{{ slot }}_adapter"
set slot_cleanup_patterns [list {{ cleanup_patterns }}]

# Run the slot cleanup once more here so this destructive mode stays isolated
# from normal adapter-card templates.
uz_pw_delete_external_ports_for_slot $slot $slot_cleanup_patterns

foreach adapter_parent_hier [list uz_digital_adapter uz_analog_adapter] {
  set adapter_hier_path ${adapter_parent_hier}/${adapter_hier_name}

  if {[llength [get_bd_cells -quiet $adapter_hier_path]] == 0} {
    puts "No existing adapter hierarchy found at $adapter_hier_path"
    continue
  }

  puts "Deleting existing adapter hierarchy $adapter_hier_path"

  foreach intf_pin [get_bd_intf_pins -quiet ${adapter_hier_path}/*] {
    uz_pw_disconnect_intf_pin_from_all_nets $intf_pin
  }

  foreach pin [get_bd_pins -quiet ${adapter_hier_path}/*] {
    uz_pw_disconnect_pin_from_all_nets $pin
  }

  catch {delete_bd_objs [get_bd_cells $adapter_hier_path]}
}

foreach adapter_parent_hier [list uz_digital_adapter uz_analog_adapter] {
  uz_pw_disconnect_matching_pins_in_hierarchy $adapter_parent_hier $slot_cleanup_patterns
  uz_pw_delete_matching_nets_in_hierarchy $adapter_parent_hier $slot_cleanup_patterns
  uz_pw_delete_matching_intf_pins_in_hierarchy $adapter_parent_hier $slot_cleanup_patterns
  uz_pw_delete_matching_pins_in_hierarchy $adapter_parent_hier $slot_cleanup_patterns
}
