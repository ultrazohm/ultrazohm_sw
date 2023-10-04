# add uz_resolver_pl_interface ip core to uz_user hierarchy
puts "Adding uz_resolver_pl_interface IPs for D5 to uz_user"
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_resolver_pl_interface:1.0 uz_user/uz_resolver_pl_inter_0
endgroup
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_resolver_pl_interface:1.0 uz_user/uz_resolver_pl_inter_1
endgroup

puts "Connecting signals between uz_user ports and ip core"
# connect all signals exept the axi line between the ports and the ip core
# First resolver_pl_interface IP
connect_bd_net [get_bd_pins uz_user/uz_resolver_pl_inter_0/position_raw] [get_bd_pins uz_user/Resolver_Interface_v_0/position_out_m]
connect_bd_net [get_bd_pins uz_user/uz_resolver_pl_inter_0/velocity_raw] [get_bd_pins uz_user/Resolver_Interface_v_0/velocity_out_m]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_resolver_pl_inter_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_resolver_pl_inter_0/AXI4_Lite_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_resolver_pl_inter_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_resolver_pl_inter_0/AXI4_Lite_ARESETN]

connect_bd_net [get_bd_pins uz_user/sample_trigger] [get_bd_pins uz_user/uz_resolver_pl_inter_0/trigger]
# Second resolver_pl_interface IP
connect_bd_net [get_bd_pins uz_user/uz_resolver_pl_inter_1/position_raw] [get_bd_pins uz_user/Resolver_Interface_v_1/position_out_m]
connect_bd_net [get_bd_pins uz_user/uz_resolver_pl_inter_1/velocity_raw] [get_bd_pins uz_user/Resolver_Interface_v_1/velocity_out_m]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_resolver_pl_inter_1/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_resolver_pl_inter_1/AXI4_Lite_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_resolver_pl_inter_1/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_resolver_pl_inter_1/AXI4_Lite_ARESETN]

connect_bd_net [get_bd_pins uz_user/sample_trigger] [get_bd_pins uz_user/uz_resolver_pl_inter_1/trigger]

# check number of axi channels at smartconnect_1 and add another channel
set num [expr {[get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] + 1}]
set_property -dict [list CONFIG.NUM_MI "$num"] [get_bd_cells uz_user/smartconnect_1]
# connect first ipcore AXI port to the above created AXI port at smartconnect_1
set num [expr [get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] - 1]
if {$num < 10} {
connect_bd_intf_net [get_bd_intf_pins uz_user/uz_resolver_pl_inter_0/AXI4_Lite] [get_bd_intf_pins uz_user/smartconnect_1/M0${num}_AXI]
} else {
connect_bd_intf_net [get_bd_intf_pins uz_user/uz_resolver_pl_inter_0/AXI4_Lite] [get_bd_intf_pins uz_user/smartconnect_1/M${num}_AXI]
}

# check number of axi channels at smartconnect_1 and add another channel
set num [expr {[get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] + 1}]
set_property -dict [list CONFIG.NUM_MI "$num"] [get_bd_cells uz_user/smartconnect_1]
# connect second ipcore AXI port to the above created AXI port at smartconnect_1
set num [expr [get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] - 1]
if {$num < 10} {
connect_bd_intf_net [get_bd_intf_pins uz_user/uz_resolver_pl_inter_1/AXI4_Lite] [get_bd_intf_pins uz_user/smartconnect_1/M0${num}_AXI]
} else {
connect_bd_intf_net [get_bd_intf_pins uz_user/uz_resolver_pl_inter_1/AXI4_Lite] [get_bd_intf_pins uz_user/smartconnect_1/M${num}_AXI]
}

# assign base address to first IP core
assign_bd_address -target_address_space /zynq_ultra_ps_e_0/Data [get_bd_addr_segs uz_user/uz_resolver_pl_inter_0/AXI4_Lite/reg0] -force
# assign base address to second IP core
assign_bd_address -target_address_space /zynq_ultra_ps_e_0/Data [get_bd_addr_segs uz_user/uz_resolver_pl_inter_1/AXI4_Lite/reg0] -force
