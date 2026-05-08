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

set_property -dict [list CONFIG.NUM_SI 1 CONFIG.NUM_MI {{ slot.interface_count }}] [get_bd_cells $slot_sc]

uz_pw_connect_net_if_unconnected $uz_pw_axi_clock_pin ${slot_sc}/aclk
uz_pw_connect_net_if_unconnected $uz_pw_axi_resetn_pin ${slot_sc}/aresetn
uz_pw_connect_net_if_unconnected $uz_pw_axi_clock_pin {{ slot.adapter_hier_path }}/aclk
uz_pw_connect_net_if_unconnected $uz_pw_axi_resetn_pin {{ slot.adapter_hier_path }}/aresetn

set upstream_mi_count [expr {[get_property [list CONFIG.NUM_MI] [get_bd_cells $uz_pw_upstream_smartconnect]] + 1}]
set_property -dict [list CONFIG.NUM_MI "$upstream_mi_count"] [get_bd_cells $uz_pw_upstream_smartconnect]
set upstream_mi_index [expr {$upstream_mi_count - 1}]
set upstream_mi_pin [uz_pw_get_sc_mi_pin $uz_pw_upstream_smartconnect $upstream_mi_index]
uz_pw_connect_intf_if_unconnected ${slot_sc}/S00_AXI $upstream_mi_pin

{% endfor %}

{% for interface in axi_connections %}
set slot_sc {{ interface.local_smartconnect_path }}
set slot_mi_pin [uz_pw_get_sc_mi_pin $slot_sc {{ interface.index }}]
uz_pw_connect_intf_if_unconnected $slot_mi_pin {{ interface.path }}
assign_bd_address -target_address_space {{ address_space }} [get_bd_addr_segs {{ interface.addr_seg }}] -force
{% endfor %}
{% endif %}
