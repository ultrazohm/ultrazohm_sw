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

proc uz_pw_connect_net_if_unconnected {source_pin sink_pin} {
  if {[llength [get_bd_pins -quiet $source_pin]] == 0} {
    puts "WARNING: Source pin not found: $source_pin"
    return
  }
  if {[llength [get_bd_pins -quiet $sink_pin]] == 0} {
    puts "WARNING: Sink pin not found: $sink_pin"
    return
  }
  if {[llength [get_bd_nets -quiet -of_objects [get_bd_pins $sink_pin]]] == 0} {
    connect_bd_net [get_bd_pins $source_pin] [get_bd_pins $sink_pin]
  } else {
    puts "Reusing existing net on $sink_pin"
  }
}

proc uz_pw_connect_intf_if_unconnected {source_pin sink_pin} {
  if {[llength [get_bd_intf_pins -quiet $source_pin]] == 0} {
    puts "WARNING: Source AXI interface not found: $source_pin"
    return
  }
  if {[llength [get_bd_intf_pins -quiet $sink_pin]] == 0} {
    puts "WARNING: Sink AXI interface not found: $sink_pin"
    return
  }
  if {[llength [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins $sink_pin]]] == 0} {
    connect_bd_intf_net [get_bd_intf_pins $source_pin] [get_bd_intf_pins $sink_pin]
  } else {
    puts "Reusing existing AXI interface connection on $sink_pin"
  }
}

proc uz_pw_connect_intf_upper_if_unconnected {source_pin sink_pin} {
  if {[llength [get_bd_intf_pins -quiet $source_pin]] == 0} {
    puts "WARNING: Source AXI interface not found: $source_pin"
    return
  }
  if {[llength [get_bd_intf_pins -quiet $sink_pin]] == 0} {
    puts "WARNING: Sink AXI interface not found: $sink_pin"
    return
  }
  if {[llength [get_bd_intf_nets -quiet -of_objects [get_bd_intf_pins $sink_pin]]] == 0} {
    connect_bd_intf_net -boundary_type upper [get_bd_intf_pins $source_pin] [get_bd_intf_pins $sink_pin]
  } else {
    puts "Reusing existing AXI interface connection on $sink_pin"
  }
}

proc uz_pw_set_property_dict_if_objects {property_dict objects label} {
  if {[llength $objects] == 0} {
    puts "WARNING: Could not set properties on $label because no object was found"
    return
  }
  set_property -dict $property_dict $objects
}

{% if has_axi %}
if {[llength [get_bd_cells -quiet $uz_pw_upstream_smartconnect]] == 0} {
  error "Configured upstream AXI SmartConnect not found: $uz_pw_upstream_smartconnect"
}

if {[llength [get_bd_pins -quiet $uz_pw_axi_clock_pin]] == 0} {
  error "Configured AXI clock pin not found: $uz_pw_axi_clock_pin"
}

if {[llength [get_bd_pins -quiet $uz_pw_axi_resetn_pin]] == 0} {
  error "Configured AXI resetn pin not found: $uz_pw_axi_resetn_pin"
}

{% for slot in axi_slots %}
puts "Configuring local AXI SmartConnect for slot {{ slot.slot }}"

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
uz_pw_connect_net_if_unconnected $uz_pw_axi_clock_pin {{ slot.adapter_hier_path }}/aclk
uz_pw_connect_net_if_unconnected $uz_pw_axi_resetn_pin {{ slot.adapter_hier_path }}/aresetn

set upstream_hier_path [uz_pw_parent_path $uz_pw_upstream_smartconnect]
set digital_adapter_boundary_pin uz_digital_adapter/{{ slot.slot }}_AXI
set slot_boundary_pin {{ slot.adapter_hier_path }}/S00_AXI

set upstream_boundary_pin [uz_pw_find_peer_intf_pin $digital_adapter_boundary_pin "*${upstream_hier_path}/M*_AXI"]
if {$upstream_boundary_pin eq ""} {
  if {$upstream_hier_path eq ""} {
    set upstream_boundary_pin {{ slot.slot }}_AXI
  } else {
    set upstream_boundary_pin ${upstream_hier_path}/{{ slot.slot }}_AXI
  }
}

uz_pw_create_intf_pin_if_missing Master $upstream_boundary_pin
uz_pw_create_intf_pin_if_missing Slave $digital_adapter_boundary_pin
uz_pw_create_intf_pin_if_missing Slave $slot_boundary_pin

set upstream_mi_pin [uz_pw_find_peer_intf_pin $upstream_boundary_pin "*${uz_pw_upstream_smartconnect}/M*_AXI"]
if {$upstream_mi_pin eq ""} {
  set upstream_mi_pin [uz_pw_add_upstream_mi_pin $uz_pw_upstream_smartconnect]
}

uz_pw_connect_intf_if_unconnected $upstream_mi_pin $upstream_boundary_pin
uz_pw_connect_intf_upper_if_unconnected $upstream_boundary_pin $digital_adapter_boundary_pin
uz_pw_connect_intf_upper_if_unconnected $digital_adapter_boundary_pin $slot_boundary_pin
uz_pw_connect_intf_if_unconnected $slot_boundary_pin ${slot_sc}/S00_AXI

{% endfor %}

{% for interface in axi_connections %}
set slot_sc {{ interface.local_smartconnect_path }}
set slot_mi_pin [uz_pw_get_sc_mi_pin $slot_sc {{ interface.index }}]
uz_pw_connect_intf_if_unconnected $slot_mi_pin {{ interface.path }}
assign_bd_address -target_address_space {{ address_space }} [get_bd_addr_segs {{ interface.addr_seg }}] -force
{% endfor %}
{% endif %}
