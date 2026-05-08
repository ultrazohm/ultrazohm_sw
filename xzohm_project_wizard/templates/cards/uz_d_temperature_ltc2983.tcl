# -----------------------------------------------------------------------------
# {{ slot }}: {{ card_name }}
# -----------------------------------------------------------------------------
{% for note in notes %}
# NOTE: {{ note }}
{% endfor %}

puts "Adding Temperature Card IP for slot {{ slot }}"

# The original script tcl_scripts/ip_uz_user_temp_ip_core.tcl was written for a
# fixed D4 flow. This template places the IP core and slot-specific pins in
# uz_digital_Adapter/{{ slot }}_adapter. AXI SmartConnect integration is
# intentionally left as a TODO for the next generator step.

set digital_adapter_hier uz_digital_Adapter
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
  if {[llength [get_bd_ports -quiet $port_name]] == 0} {
    create_bd_port -dir $direction $port_name
  } else {
    puts "Reusing existing port $port_name"
  }
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

connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MOSI_1_Dig01] [get_bd_pins ${temp_ip_path}/SPI_MOSI_1]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SCLK_1_Dig00] [get_bd_pins ${temp_ip_path}/SPI_SCLK_1]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SS_1_Dig03] [get_bd_pins ${temp_ip_path}/SPI_SS_1]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_resetn_1_Dig18] [get_bd_pins ${temp_ip_path}/LTC_resetn_1]

connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MOSI_2_Dig13] [get_bd_pins ${temp_ip_path}/SPI_MOSI_2]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SCLK_2_Dig12] [get_bd_pins ${temp_ip_path}/SPI_SCLK_2]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SS_2_Dig15] [get_bd_pins ${temp_ip_path}/SPI_SS_2]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_resetn_2_NC] [get_bd_pins ${temp_ip_path}/LTC_resetn_2]

connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MOSI_3_Dig07] [get_bd_pins ${temp_ip_path}/SPI_MOSI_3]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SCLK_3_Dig06] [get_bd_pins ${temp_ip_path}/SPI_SCLK_3]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SS_3_Dig09] [get_bd_pins ${temp_ip_path}/SPI_SS_3]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_resetn_3_NC] [get_bd_pins ${temp_ip_path}/LTC_resetn_3]

connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MISO_1_Dig02] [get_bd_pins ${temp_ip_path}/SPI_MISO_1]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MISO_2_Dig14] [get_bd_pins ${temp_ip_path}/SPI_MISO_2]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MISO_3_Dig08] [get_bd_pins ${temp_ip_path}/SPI_MISO_3]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_Interrupt_1_Dig04] [get_bd_pins ${temp_ip_path}/LTC_Interrupt_1]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_Interrupt_2_Dig16] [get_bd_pins ${temp_ip_path}/LTC_Interrupt_2]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_Interrupt_3_Dig10] [get_bd_pins ${temp_ip_path}/LTC_Interrupt_3]

connect_bd_net [get_bd_pins ${adapter_hier_path}/aclk] [get_bd_pins ${temp_ip_path}/s00_axi_aclk]
connect_bd_net [get_bd_pins ${adapter_hier_path}/aresetn] [get_bd_pins ${temp_ip_path}/s00_axi_aresetn]

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

connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SCLK_1_Dig00] [get_bd_ports Dig_00_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MOSI_1_Dig01] [get_bd_ports Dig_01_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MISO_1_Dig02] [get_bd_ports Dig_02_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SS_1_Dig03] [get_bd_ports Dig_03_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_Interrupt_1_Dig04] [get_bd_ports Dig_04_Ch{{ slot_index }}]

connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SCLK_3_Dig06] [get_bd_ports Dig_06_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MOSI_3_Dig07] [get_bd_ports Dig_07_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MISO_3_Dig08] [get_bd_ports Dig_08_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SS_3_Dig09] [get_bd_ports Dig_09_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_Interrupt_3_Dig10] [get_bd_ports Dig_10_Ch{{ slot_index }}]

connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SCLK_2_Dig12] [get_bd_ports Dig_12_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MOSI_2_Dig13] [get_bd_ports Dig_13_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_MISO_2_Dig14] [get_bd_ports Dig_14_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/SPI_SS_2_Dig15] [get_bd_ports Dig_15_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_Interrupt_2_Dig16] [get_bd_ports Dig_16_Ch{{ slot_index }}]
connect_bd_net [get_bd_pins ${adapter_hier_path}/LTC_resetn_1_Dig18] [get_bd_ports Dig_18_Ch{{ slot_index }}]

# TODO: Create/connect a shared AXI SmartConnect path for ${temp_ip_path}/s00_axi.
# TODO: Assign the AXI base address after the SmartConnect connection exists.

puts "Switching Temperature Card constraints for slot {{ slot }}"

set packed_constraint [get_files -quiet Digital_{{ slot }}_packed.xdc]
if {[llength $packed_constraint] > 0} {
  set_property is_enabled false $packed_constraint
} else {
  puts "WARNING: Could not find Digital_{{ slot }}_packed.xdc"
}

set unpacked_constraint [get_files -quiet Digital_AdapterBoard_{{ slot }}.xdc]
if {[llength $unpacked_constraint] > 0} {
  set_property is_enabled true $unpacked_constraint
} else {
  puts "WARNING: Could not find Digital_AdapterBoard_{{ slot }}.xdc"
}

{% if driver %}
# Vitis driver hook: {{ driver }}
{% endif %}
