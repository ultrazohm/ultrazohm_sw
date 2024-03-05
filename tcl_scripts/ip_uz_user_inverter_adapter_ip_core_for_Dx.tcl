# set number of the instance (valid: 0...4)
set instance 1


set instance_dig_interface [expr {$instance + 1}]
puts "Instance Number: $instance"
puts "Interface Port Name: D$instance_dig_interface"
puts "Adding uz_d_inverter_adapter IP for D1 to uz_user"

# add uz_resolver_pl_interface ip core to uz_user hierarchy
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_d_inverter_adapter:1.0 uz_user/uz_d_inverter_adapter_${instance}
endgroup
startgroup
create_bd_cell -type ip -vlnv xilinx.com:user:uz_inverter_adapter_mapping:1.0 uz_user/uz_inverter_adapter_${instance}
endgroup

puts "Creating Interface Port"
create_bd_intf_pin -mode Master -vlnv th-nuernberg.de:user:uz_inverter_adapter_rtl:1.0 uz_user/D${instance_dig_interface}

puts "Connecting signals between uz_user ports and ip core"
# connect all signals exept the axi line between the ports and the ip core
connect_bd_net [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/PWM_EN] [get_bd_pins uz_user/uz_inverter_adapter_${instance}/PWM_ENABLE]
connect_bd_net [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/Temp] [get_bd_pins uz_user/uz_inverter_adapter_${instance}/Temp]
connect_bd_net [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/FAULT] [get_bd_pins uz_user/uz_inverter_adapter_${instance}/FAULT]
connect_bd_net [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/OC] [get_bd_pins uz_user/uz_inverter_adapter_${instance}/OC]
connect_bd_net [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/I_DIAG] [get_bd_pins uz_user/uz_inverter_adapter_${instance}/I_DIAG]

connect_bd_intf_net [get_bd_intf_pins uz_user/D${instance_dig_interface}] [get_bd_intf_pins uz_user/uz_inverter_adapter_${instance}/uz_inverter_adapter]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/AXI4_Lite_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/AXI4_Lite_ARESETN]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_d_inverter_adapter_${instance}/IPCORE_RESETN]

# check number of axi channels at smartconnect_1 and add another channel
set num [expr {[get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] + 1}]
set_property -dict [list CONFIG.NUM_MI "$num"] [get_bd_cells uz_user/smartconnect_1]
# connect ipcore AXI port to the above created AXI port at smartconnect_1
set num [expr [get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] - 1]
if {$num < 10} {
connect_bd_intf_net [get_bd_intf_pins uz_user/uz_d_inverter_adapter_${instance}/AXI4_Lite] [get_bd_intf_pins uz_user/smartconnect_1/M0${num}_AXI]
} else {
connect_bd_intf_net [get_bd_intf_pins uz_user/uz_d_inverter_adapter_${instance}/AXI4_Lite] [get_bd_intf_pins uz_user/smartconnect_1/M${num}_AXI]
}

# assign base address to IP core
assign_bd_address -target_address_space /zynq_ultra_ps_e_0/Data [get_bd_addr_segs uz_user/uz_d_inverter_adapter_${instance}/AXI4_Lite/reg0] -force

# copy constraint file to the project
file copy -force ../../ip_cores/uz_d_inverter_adapter/constraint_files/Digital_D${instance_dig_interface}_packed.xdc ../../vivado/constraints/te0808/Digital_D${instance_dig_interface}_packed.xdc