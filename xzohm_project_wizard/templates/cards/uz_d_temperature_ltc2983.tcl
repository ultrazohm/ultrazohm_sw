# -----------------------------------------------------------------------------
# {{ slot }}: {{ card_name }}
# -----------------------------------------------------------------------------
{% for note in notes %}
# NOTE: {{ note }}
{% endfor %}

puts "Adding Temperature Card IP for slot {{ slot }}"

# The original script tcl_scripts/ip_uz_user_temp_ip_core.tcl was written for a
# fixed D4 flow. This template places the IP core and slot-specific pins in
# uz_digital_adapter/{{ slot }}_adapter. AXI SmartConnect integration is
# intentionally left as a TODO for the next generator step.

set digital_adapter_hier uz_digital_adapter
set adapter_hier_name {{ slot }}_adapter
set adapter_hier_path ${digital_adapter_hier}/${adapter_hier_name}
set temp_ip_path ${adapter_hier_path}/Temperature_Card_Int_0

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

if {[llength [get_bd_cells -quiet ${temp_ip_path}]] == 0} {
  startgroup
  create_bd_cell -type ip -vlnv xilinx.com:user:Temperature_Card_Interface_v1_0:1.1 ${temp_ip_path}
  endgroup
} else {
  puts "Reusing existing IP ${temp_ip_path}"
}

puts "Creating pins in ${adapter_hier_path}"

uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_MOSI_1_Dig01
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_SCLK_1_Dig00
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_SS_1_Dig03
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/LTC_resetn_1_Dig18

uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_MOSI_2_Dig13
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_SCLK_2_Dig12
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_SS_2_Dig15
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/LTC_resetn_2_NC

uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_MOSI_3_Dig07
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_SCLK_3_Dig06
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/SPI_SS_3_Dig09
uz_pw_create_bd_pin_if_missing O ${adapter_hier_path}/LTC_resetn_3_NC

uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/SPI_MISO_1_Dig02
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/SPI_MISO_2_Dig14
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/SPI_MISO_3_Dig08
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/LTC_Interrupt_1_Dig04
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/LTC_Interrupt_2_Dig16
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/LTC_Interrupt_3_Dig10

uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aclk
uz_pw_create_bd_pin_if_missing I ${adapter_hier_path}/aresetn

puts "Connecting Temperature Card IP pins in ${adapter_hier_path}"

uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_MOSI_1_Dig01 ${temp_ip_path}/SPI_MOSI_1
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_SCLK_1_Dig00 ${temp_ip_path}/SPI_SCLK_1
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_SS_1_Dig03 ${temp_ip_path}/SPI_SS_1
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/LTC_resetn_1_Dig18 ${temp_ip_path}/LTC_resetn_1

uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_MOSI_2_Dig13 ${temp_ip_path}/SPI_MOSI_2
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_SCLK_2_Dig12 ${temp_ip_path}/SPI_SCLK_2
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_SS_2_Dig15 ${temp_ip_path}/SPI_SS_2
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/LTC_resetn_2_NC ${temp_ip_path}/LTC_resetn_2

uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_MOSI_3_Dig07 ${temp_ip_path}/SPI_MOSI_3
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_SCLK_3_Dig06 ${temp_ip_path}/SPI_SCLK_3
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_SS_3_Dig09 ${temp_ip_path}/SPI_SS_3
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/LTC_resetn_3_NC ${temp_ip_path}/LTC_resetn_3

uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_MISO_1_Dig02 ${temp_ip_path}/SPI_MISO_1
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_MISO_2_Dig14 ${temp_ip_path}/SPI_MISO_2
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/SPI_MISO_3_Dig08 ${temp_ip_path}/SPI_MISO_3
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/LTC_Interrupt_1_Dig04 ${temp_ip_path}/LTC_Interrupt_1
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/LTC_Interrupt_2_Dig16 ${temp_ip_path}/LTC_Interrupt_2
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/LTC_Interrupt_3_Dig10 ${temp_ip_path}/LTC_Interrupt_3

uz_pw_connect_net_if_unconnected ${adapter_hier_path}/aclk ${temp_ip_path}/s00_axi_aclk
uz_pw_connect_net_if_unconnected ${adapter_hier_path}/aresetn ${temp_ip_path}/s00_axi_aresetn

puts "Creating external ports for Temperature Card slot {{ slot }}"

uz_pw_create_bd_port_if_missing O Dig_00_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_01_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing I Dig_02_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_03_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing I Dig_04_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_06_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_07_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing I Dig_08_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_09_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing I Dig_10_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_12_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_13_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing I Dig_14_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_15_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing I Dig_16_Ch{{ slot_index }}
uz_pw_create_bd_port_if_missing O Dig_18_Ch{{ slot_index }}

uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_SCLK_1_Dig00 Dig_00_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_MOSI_1_Dig01 Dig_01_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_MISO_1_Dig02 Dig_02_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_SS_1_Dig03 Dig_03_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/LTC_Interrupt_1_Dig04 Dig_04_Ch{{ slot_index }}

uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_SCLK_3_Dig06 Dig_06_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_MOSI_3_Dig07 Dig_07_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_MISO_3_Dig08 Dig_08_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_SS_3_Dig09 Dig_09_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/LTC_Interrupt_3_Dig10 Dig_10_Ch{{ slot_index }}

uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_SCLK_2_Dig12 Dig_12_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_MOSI_2_Dig13 Dig_13_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_MISO_2_Dig14 Dig_14_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/SPI_SS_2_Dig15 Dig_15_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/LTC_Interrupt_2_Dig16 Dig_16_Ch{{ slot_index }}
uz_pw_connect_port_if_unconnected ${adapter_hier_path}/LTC_resetn_1_Dig18 Dig_18_Ch{{ slot_index }}

# TODO: Create/connect a shared AXI SmartConnect path for ${temp_ip_path}/s00_axi.
# TODO: Assign the AXI base address after the SmartConnect connection exists.

puts "Switching Temperature Card constraints for slot {{ slot }}"

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

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
