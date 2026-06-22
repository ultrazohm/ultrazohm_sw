# -----------------------------------------------------------------------------
# AXI interconnect setup
# -----------------------------------------------------------------------------

set uz_pw_upstream_smartconnect {{ upstream_smartconnect }}
set uz_pw_axi_clock_pin {{ clock_pin }}
set uz_pw_axi_resetn_pin {{ resetn_pin }}
set uz_pw_axi_address_space {{ address_space }}

proc uz_pw_get_sc_mi_pin {smartconnect_path index} {
  if {$index < 10} {
    return "${smartconnect_path}/M0${index}_AXI"
  }
  return "${smartconnect_path}/M${index}_AXI"
}

proc uz_pw_parent_path {object_path} {
  set parts [split $object_path "/"]
  if {[llength $parts] <= 1} {
    return ""
  }
  return [join [lrange $parts 0 end-1] "/"]
}

proc uz_pw_leaf_name {object_path} {
  set parts [split $object_path "/"]
  return [lindex $parts end]
}

proc uz_pw_create_intf_pin_if_missing {mode pin_path} {
  if {[llength [get_bd_intf_pins -quiet $pin_path]] > 0} {
    puts "Reusing existing AXI interface pin $pin_path"
    return
  }

  set parent_path [uz_pw_parent_path $pin_path]
  set pin_name [uz_pw_leaf_name $pin_path]
  set old_instance [current_bd_instance .]
  if {$parent_path ne ""} {
    current_bd_instance [get_bd_cells $parent_path]
  }
  create_bd_intf_pin -mode $mode -vlnv xilinx.com:interface:aximm_rtl:1.0 $pin_name
  current_bd_instance $old_instance
}

proc uz_pw_find_peer_intf_pin {pin_path peer_pattern} {
  set pin [get_bd_intf_pins -quiet $pin_path]
  if {[llength $pin] == 0} {
    return ""
  }
  set nets [get_bd_intf_nets -quiet -of_objects $pin]
  foreach net $nets {
    foreach peer [get_bd_intf_pins -quiet -of_objects $net] {
      if {$peer eq $pin} {
        continue
      }
      if {[string match $peer_pattern $peer]} {
        return $peer
      }
    }
  }
  return ""
}

proc uz_pw_add_upstream_mi_pin {smartconnect_path} {
  set upstream_sc_cell [get_bd_cells -quiet $smartconnect_path]
  if {[llength $upstream_sc_cell] == 0} {
    return ""
  }
  set upstream_mi_count [expr {[get_property [list CONFIG.NUM_MI] $upstream_sc_cell] + 1}]
  uz_pw_set_property_dict_if_objects [list CONFIG.NUM_MI "$upstream_mi_count"] $upstream_sc_cell $smartconnect_path
  set upstream_mi_index [expr {$upstream_mi_count - 1}]
  return [uz_pw_get_sc_mi_pin $smartconnect_path $upstream_mi_index]
}

proc uz_pw_get_or_add_upstream_mi_pin {smartconnect_path} {
  set upstream_sc_cell [get_bd_cells -quiet $smartconnect_path]
  if {[llength $upstream_sc_cell] == 0} {
    return ""
  }

  set mi_count [get_property CONFIG.NUM_MI $upstream_sc_cell]
  for {set index 0} {$index < $mi_count} {incr index} {
    set mi_pin_path [uz_pw_get_sc_mi_pin $smartconnect_path $index]
    set mi_pin [get_bd_intf_pins -quiet $mi_pin_path]
    if {[llength $mi_pin] == 0} {
      continue
    }
    if {[llength [get_bd_intf_nets -quiet -of_objects $mi_pin]] == 0} {
      puts "Reusing unconnected upstream AXI master interface $mi_pin_path"
      return $mi_pin_path
    }
  }

  return [uz_pw_add_upstream_mi_pin $smartconnect_path]
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
  foreach source_net $source_nets {
    if {[lsearch -exact $sink_nets $source_net] >= 0} {
      puts "Reusing existing net on $sink_pin"
      return
    }
  }

  if {[llength $sink_nets] == 0} {
    connect_bd_net $source $sink
    return
  }

  # The sink may already drive a local sub-net, e.g. a hierarchy clock pin wired
  # to local IP pins before the upstream clock is attached. Preserve those loads
  # and merge them into the source net.
  set sink_net [lindex $sink_nets 0]
  set sink_net_pins [get_bd_pins -quiet -of_objects $sink_net]
  foreach sink_net_pin $sink_net_pins {
    catch {disconnect_bd_net $sink_net $sink_net_pin}
  }
  foreach sink_net_pin $sink_net_pins {
    if {[llength [get_bd_nets -quiet -of_objects $sink_net_pin]] == 0} {
      connect_bd_net $source $sink_net_pin
    }
  }

  if {[llength [get_bd_nets -quiet -of_objects $sink]] == 0} {
    connect_bd_net $source $sink
  } else {
    puts "Reusing existing net on $sink_pin"
  }
}

proc uz_pw_delete_intf_nets_on_pin {pin label} {
  foreach intf_net [get_bd_intf_nets -quiet -of_objects $pin] {
    puts "Deleting stale AXI interface net on $label: $intf_net"
    catch {delete_bd_objs $intf_net}
  }
}

proc uz_pw_connect_intf_pair {source_pin sink_pin {boundary_type ""} {preserve_source_nets 0}} {
  set source [get_bd_intf_pins -quiet $source_pin]
  set sink [get_bd_intf_pins -quiet $sink_pin]

  if {[llength $source] == 0} {
    puts "WARNING: Source AXI interface not found: $source_pin"
    return
  }
  if {[llength $sink] == 0} {
    puts "WARNING: Sink AXI interface not found: $sink_pin"
    return
  }

  set source_nets [get_bd_intf_nets -quiet -of_objects $source]
  set sink_nets [get_bd_intf_nets -quiet -of_objects $sink]
  foreach source_net $source_nets {
    if {[lsearch -exact $sink_nets $source_net] >= 0} {
      puts "Reusing existing AXI interface connection between $source_pin and $sink_pin"
      return
    }
  }

  if {!$preserve_source_nets && [llength $source_nets] > 0} {
    uz_pw_delete_intf_nets_on_pin $source $source_pin
  }
  if {[llength [get_bd_intf_pins -quiet $sink_pin]] > 0 && [llength [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins $sink_pin]]] > 0} {
    uz_pw_delete_intf_nets_on_pin [get_bd_intf_pins $sink_pin] $sink_pin
  }

  set source [get_bd_intf_pins -quiet $source_pin]
  set sink [get_bd_intf_pins -quiet $sink_pin]
  if {[llength $source] == 0 || [llength $sink] == 0} {
    puts "WARNING: Could not reconnect AXI interface because a pin disappeared: $source_pin -> $sink_pin"
    return
  }

  if {$boundary_type eq "upper"} {
    connect_bd_intf_net -boundary_type upper $source $sink
  } else {
    connect_bd_intf_net $source $sink
  }
}

proc uz_pw_connect_intf_if_unconnected {source_pin sink_pin} {
  uz_pw_connect_intf_pair $source_pin $sink_pin
}

proc uz_pw_connect_intf_preserve_source_if_unconnected {source_pin sink_pin} {
  uz_pw_connect_intf_pair $source_pin $sink_pin "" 1
}

proc uz_pw_connect_intf_upper_if_unconnected {source_pin sink_pin} {
  uz_pw_connect_intf_pair $source_pin $sink_pin upper 1
}

proc uz_pw_set_property_dict_if_objects {property_dict objects label} {
  if {[llength $objects] == 0} {
    puts "WARNING: Could not set properties on $label because no object was found"
    return
  }
  set_property -dict $property_dict $objects
}

proc uz_pw_delete_intf_pin_and_net_if_present {pin_path} {
  set pin [get_bd_intf_pins -quiet $pin_path]
  if {[llength $pin] == 0} {
    return
  }

  foreach intf_net [get_bd_intf_nets -quiet -of_objects $pin] {
    puts "Deleting AXI interface net connected to $pin_path: $intf_net"
    catch {delete_bd_objs $intf_net}
  }

  if {[llength [get_bd_intf_pins -quiet $pin_path]] > 0} {
    puts "Deleting AXI interface pin $pin_path"
    catch {delete_bd_objs [get_bd_intf_pins -quiet $pin_path]}
  }
}

proc uz_pw_compact_upstream_mi_connections {smartconnect_path} {
  set smartconnect_cell [get_bd_cells -quiet $smartconnect_path]
  if {[llength $smartconnect_cell] == 0} {
    puts "WARNING: Cannot compact AXI master interfaces because SmartConnect was not found: $smartconnect_path"
    return
  }

  set mi_count [get_property CONFIG.NUM_MI $smartconnect_cell]
  set connected_peers {}

  for {set index 0} {$index < $mi_count} {incr index} {
    set mi_pin_path [uz_pw_get_sc_mi_pin $smartconnect_path $index]
    set mi_pin [get_bd_intf_pins -quiet $mi_pin_path]
    if {[llength $mi_pin] == 0} {
      continue
    }

    foreach intf_net [get_bd_intf_nets -quiet -of_objects $mi_pin] {
      set peer_pin ""
      foreach peer [get_bd_intf_pins -quiet -of_objects $intf_net] {
        if {$peer ne $mi_pin} {
          set peer_pin $peer
          break
        }
      }
      if {$peer_pin ne "" && [lsearch -exact $connected_peers $peer_pin] < 0} {
        lappend connected_peers $peer_pin
      }
      catch {delete_bd_objs $intf_net}
    }
  }

  set new_mi_count [llength $connected_peers]
  if {$new_mi_count < 1} {
    set new_mi_count 1
  }
  puts "Compacting $smartconnect_path to $new_mi_count AXI master interface(s)"
  uz_pw_set_property_dict_if_objects [list CONFIG.NUM_MI "$new_mi_count"] $smartconnect_cell $smartconnect_path

  for {set index 0} {$index < [llength $connected_peers]} {incr index} {
    set mi_pin_path [uz_pw_get_sc_mi_pin $smartconnect_path $index]
    set peer_pin [lindex $connected_peers $index]
    if {[llength [get_bd_intf_pins -quiet $mi_pin_path]] == 0} {
      puts "WARNING: Could not reconnect AXI peer $peer_pin because $mi_pin_path does not exist"
      continue
    }
    if {[llength [get_bd_intf_pins -quiet $peer_pin]] == 0} {
      puts "WARNING: Could not reconnect AXI peer because it no longer exists: $peer_pin"
      continue
    }
    puts "Reconnecting $mi_pin_path to $peer_pin"
    connect_bd_intf_net [get_bd_intf_pins $mi_pin_path] [get_bd_intf_pins $peer_pin]
  }
}

proc uz_pw_remove_slot_axi_attachment {slot adapter_root_hier} {
  set upstream_hier_path [uz_pw_parent_path $::uz_pw_upstream_smartconnect]
  set candidate_pins {}
  set upstream_boundary_pin ""

  if {$upstream_hier_path eq ""} {
    set upstream_boundary_pin ${slot}_AXI
  } else {
    set upstream_boundary_pin ${upstream_hier_path}/${slot}_AXI
  }
  lappend candidate_pins $upstream_boundary_pin
  lappend candidate_pins ${adapter_root_hier}/${slot}_AXI
  lappend candidate_pins ${adapter_root_hier}/${slot}_adapter/S00_AXI

  foreach pin [get_bd_intf_pins -quiet */${slot}_AXI] {
    if {[lsearch -exact $candidate_pins $pin] < 0} {
      lappend candidate_pins $pin
    }
  }

  foreach pin_path $candidate_pins {
    uz_pw_delete_intf_pin_and_net_if_present $pin_path
  }

  uz_pw_compact_upstream_mi_connections $::uz_pw_upstream_smartconnect
}

{% if has_no_adapter_slots %}
{% for slot in no_adapter_slots %}
set uz_pw_upstream_smartconnect {{ slot.upstream_smartconnect }}
if {$uz_pw_upstream_smartconnect eq "" || [llength [get_bd_cells -quiet $uz_pw_upstream_smartconnect]] == 0} {
  puts "WARNING: Upstream AXI SmartConnect not found; skipping AXI attachment cleanup for {{ slot.slot }}."
} else {
  uz_pw_remove_slot_axi_attachment {{ slot.slot }} {{ slot.adapter_root_hier }}
}
{% endfor %}

{% endif %}

{% if has_axi %}
{% for slot in axi_slots %}
set uz_pw_upstream_smartconnect {{ slot.upstream_smartconnect }}
set uz_pw_axi_clock_pin {{ slot.clock_pin }}
set uz_pw_axi_resetn_pin {{ slot.resetn_pin }}
set uz_pw_axi_address_space {{ slot.address_space }}

if {[llength [get_bd_cells -quiet $uz_pw_upstream_smartconnect]] == 0} {
  error "Configured upstream AXI SmartConnect not found: $uz_pw_upstream_smartconnect"
}

if {[llength [get_bd_pins -quiet $uz_pw_axi_clock_pin]] == 0} {
  error "Configured AXI clock pin not found: $uz_pw_axi_clock_pin"
}

if {[llength [get_bd_pins -quiet $uz_pw_axi_resetn_pin]] == 0} {
  error "Configured AXI resetn pin not found: $uz_pw_axi_resetn_pin"
}

puts "Refreshing AXI attachment for slot {{ slot.slot }}"
uz_pw_remove_slot_axi_attachment {{ slot.slot }} {{ slot.adapter_root_hier }}

puts "Configuring local AXI SmartConnect for slot {{ slot.slot }}"

# Remove legacy slot-local AXI boundary names before creating the canonical
# wizard boundary. Older designs used IP-specific names such as AXI4_Lite here;
# the wizard uses S00_AXI consistently between Dx/Ax_adapter and the local
# SmartConnect.
foreach legacy_slot_axi_pin [list \
  {{ slot.adapter_hier_path }}/AXI4_Lite \
  {{ slot.adapter_hier_path }}/s00_axi \
  {{ slot.adapter_hier_path }}/s_axi_lite \
] {
  uz_pw_delete_intf_pin_and_net_if_present $legacy_slot_axi_pin
}

set slot_sc {{ slot.local_smartconnect_path }}
if {[llength [get_bd_cells -quiet $slot_sc]] == 0} {
  create_bd_cell -type ip -vlnv {{ local_smartconnect_vlnv }} $slot_sc
} else {
  puts "Reusing existing local SmartConnect $slot_sc"
}

set slot_sc_cell [get_bd_cells -quiet $slot_sc]
uz_pw_set_property_dict_if_objects [list CONFIG.NUM_SI 1 CONFIG.NUM_MI {{ slot.interface_count }}] $slot_sc_cell $slot_sc

uz_pw_connect_net_if_unconnected $uz_pw_axi_clock_pin ${slot_sc}/aclk
uz_pw_connect_net_if_unconnected $uz_pw_axi_resetn_pin ${slot_sc}/aresetn
uz_pw_connect_net_if_unconnected $uz_pw_axi_clock_pin {{ slot.adapter_hier_path }}/{{ slot.adapter_clock_pin }}
uz_pw_connect_net_if_unconnected $uz_pw_axi_resetn_pin {{ slot.adapter_hier_path }}/{{ slot.adapter_resetn_pin }}

set upstream_hier_path [uz_pw_parent_path $uz_pw_upstream_smartconnect]
set adapter_root_boundary_pin {{ slot.adapter_root_hier }}/{{ slot.slot }}_AXI
set slot_boundary_pin {{ slot.adapter_hier_path }}/S00_AXI

set upstream_boundary_pin [uz_pw_find_peer_intf_pin $adapter_root_boundary_pin "*${upstream_hier_path}/M*_AXI"]
if {$upstream_boundary_pin eq ""} {
  if {$upstream_hier_path eq ""} {
    set upstream_boundary_pin {{ slot.slot }}_AXI
  } else {
    set upstream_boundary_pin ${upstream_hier_path}/{{ slot.slot }}_AXI
  }
}

uz_pw_create_intf_pin_if_missing Master $upstream_boundary_pin
uz_pw_create_intf_pin_if_missing Slave $adapter_root_boundary_pin
uz_pw_create_intf_pin_if_missing Slave $slot_boundary_pin

set upstream_mi_pin [uz_pw_find_peer_intf_pin $upstream_boundary_pin "*${uz_pw_upstream_smartconnect}/M*_AXI"]
if {$upstream_mi_pin eq ""} {
  set upstream_mi_pin [uz_pw_get_or_add_upstream_mi_pin $uz_pw_upstream_smartconnect]
}

uz_pw_connect_intf_if_unconnected $upstream_mi_pin $upstream_boundary_pin
uz_pw_connect_intf_upper_if_unconnected $upstream_boundary_pin $adapter_root_boundary_pin
uz_pw_connect_intf_upper_if_unconnected $adapter_root_boundary_pin $slot_boundary_pin
uz_pw_connect_intf_preserve_source_if_unconnected $slot_boundary_pin ${slot_sc}/S00_AXI

{% endfor %}

{% for interface in axi_connections %}
set slot_sc {{ interface.local_smartconnect_path }}
set slot_mi_pin [uz_pw_get_sc_mi_pin $slot_sc {{ interface.index }}]
uz_pw_connect_intf_if_unconnected $slot_mi_pin {{ interface.path }}
{{ interface.address_assignment_command }}
{% endfor %}
{% endif %}

{% if has_upstream_smartconnects %}
puts "Final compaction of project-level AXI SmartConnect master interfaces"
{% for smartconnect in upstream_smartconnects %}
uz_pw_compact_upstream_mi_connections {{ smartconnect.path }}
{% endfor %}
{% endif %}
