# add resolver ip core to uz_user hierarchy
puts "Adding Resolver_Interface IPs for D5 to uz_user"
startgroup
create_bd_cell -type ip -vlnv ki_power:user:Resolver_Interface_v1_0:1.0 uz_user/Resolver_Interface_v_0
endgroup
startgroup
create_bd_cell -type ip -vlnv ki_power:user:Resolver_Interface_v1_0:1.0 uz_user/Resolver_Interface_v_1
endgroup

puts "Creating Ports in uz_user"
# create output ports in uz_user
create_bd_pin -dir O uz_user/N_SAMPLE_1_Dig_06
create_bd_pin -dir O uz_user/F_SYNC_1_Dig_08
create_bd_pin -dir O uz_user/SCLK_1_Dig_09
create_bd_pin -dir O uz_user/N_RESET_1_Dig_10
create_bd_pin -dir O uz_user/A1_1_Dig_11
create_bd_pin -dir O uz_user/A0_1_Dig_12
create_bd_pin -dir O uz_user/CS_1_Dig_13
create_bd_pin -dir O uz_user/SDO_1_Dig_07

create_bd_pin -dir O uz_user/N_SAMPLE_2_Dig_15
create_bd_pin -dir O uz_user/F_SYNC_2_Dig_17
create_bd_pin -dir O uz_user/SCLK_2_Dig_18
create_bd_pin -dir O uz_user/N_RESET_2_Dig_19
create_bd_pin -dir O uz_user/A1_2_Dig_20
create_bd_pin -dir O uz_user/A0_2_Dig_21
create_bd_pin -dir O uz_user/CS_2_Dig_22
create_bd_pin -dir O uz_user/SDO_2_Dig_16

# create input ports in uz_user
create_bd_pin -dir I uz_user/SDI_1_Dig_14
create_bd_pin -dir I uz_user/SDI_2_Dig_23

create_bd_pin -dir I uz_user/sample_trigger

puts "Connecting signals between uz_user ports and ip core"
# connect all signals exept the axi line between the ports and the ip core
# First Resolver IP
connect_bd_net [get_bd_pins uz_user/N_SAMPLE_1_Dig_06] [get_bd_pins uz_user/Resolver_Interface_v_0/AD2S1210_n_sample]
connect_bd_net [get_bd_pins uz_user/F_SYNC_1_Dig_08] [get_bd_pins uz_user/Resolver_Interface_v_0/AD2S1210_n_fsync]
connect_bd_net [get_bd_pins uz_user/SCLK_1_Dig_09] [get_bd_pins uz_user/Resolver_Interface_v_0/SPI_SCLK]
connect_bd_net [get_bd_pins uz_user/N_RESET_1_Dig_10] [get_bd_pins uz_user/Resolver_Interface_v_0/AD2S1210_n_reset]
connect_bd_net [get_bd_pins uz_user/A1_1_Dig_11] [get_bd_pins uz_user/Resolver_Interface_v_0/AD2S1210_mode_A1]
connect_bd_net [get_bd_pins uz_user/A0_1_Dig_12] [get_bd_pins uz_user/Resolver_Interface_v_0/AD2S1210_mode_A0]
connect_bd_net [get_bd_pins uz_user/CS_1_Dig_13] [get_bd_pins uz_user/Resolver_Interface_v_0/SPI_SS]
connect_bd_net [get_bd_pins uz_user/SDO_1_Dig_07] [get_bd_pins uz_user/Resolver_Interface_v_0/SPI_MOSI]

connect_bd_net [get_bd_pins uz_user/SDI_1_Dig_14] [get_bd_pins uz_user/Resolver_Interface_v_0/SPI_MISO]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/Resolver_Interface_v_0/s00_axi_aclk]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/Resolver_Interface_v_0/s00_axi_aresetn]

connect_bd_net [get_bd_pins uz_user/sample_trigger] [get_bd_pins uz_user/Resolver_Interface_v_0/sample_trigger]

# Second Resolver IP
connect_bd_net [get_bd_pins uz_user/N_SAMPLE_2_Dig_15] [get_bd_pins uz_user/Resolver_Interface_v_1/AD2S1210_n_sample]
connect_bd_net [get_bd_pins uz_user/F_SYNC_2_Dig_17] [get_bd_pins uz_user/Resolver_Interface_v_1/AD2S1210_n_fsync]
connect_bd_net [get_bd_pins uz_user/SCLK_2_Dig_18] [get_bd_pins uz_user/Resolver_Interface_v_1/SPI_SCLK]
connect_bd_net [get_bd_pins uz_user/N_RESET_2_Dig_19] [get_bd_pins uz_user/Resolver_Interface_v_1/AD2S1210_n_reset]
connect_bd_net [get_bd_pins uz_user/A1_2_Dig_20] [get_bd_pins uz_user/Resolver_Interface_v_1/AD2S1210_mode_A1]
connect_bd_net [get_bd_pins uz_user/A0_2_Dig_21] [get_bd_pins uz_user/Resolver_Interface_v_1/AD2S1210_mode_A0]
connect_bd_net [get_bd_pins uz_user/CS_2_Dig_22] [get_bd_pins uz_user/Resolver_Interface_v_1/SPI_SS]
connect_bd_net [get_bd_pins uz_user/SDO_2_Dig_16] [get_bd_pins uz_user/Resolver_Interface_v_1/SPI_MOSI]

connect_bd_net [get_bd_pins uz_user/SDI_2_Dig_23] [get_bd_pins uz_user/Resolver_Interface_v_1/SPI_MISO]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/Resolver_Interface_v_1/s00_axi_aclk]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/Resolver_Interface_v_1/s00_axi_aresetn]

connect_bd_net [get_bd_pins uz_user/sample_trigger] [get_bd_pins uz_user/Resolver_Interface_v_1/sample_trigger]

# check number of axi channels at smartconnect_1 and add another channel
set num [expr {[get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] + 1}]
set_property -dict [list CONFIG.NUM_MI "$num"] [get_bd_cells uz_user/smartconnect_1]
# connect first ipcore AXI port to the above created AXI port at smartconnect_1
set num [expr [get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] - 1]
if {$num < 10} {
connect_bd_intf_net [get_bd_intf_pins uz_user/Resolver_Interface_v_0/s00_axi] [get_bd_intf_pins uz_user/smartconnect_1/M0${num}_AXI]
} else {
connect_bd_intf_net [get_bd_intf_pins uz_user/Resolver_Interface_v_0/s00_axi] [get_bd_intf_pins uz_user/smartconnect_1/M${num}_AXI]
}

# check number of axi channels at smartconnect_1 and add another channel
set num [expr {[get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] + 1}]
set_property -dict [list CONFIG.NUM_MI "$num"] [get_bd_cells uz_user/smartconnect_1]
# connect second ipcore AXI port to the above created AXI port at smartconnect_1
set num [expr [get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] - 1]
if {$num < 10} {
connect_bd_intf_net [get_bd_intf_pins uz_user/Resolver_Interface_v_1/s00_axi] [get_bd_intf_pins uz_user/smartconnect_1/M0${num}_AXI]
} else {
connect_bd_intf_net [get_bd_intf_pins uz_user/Resolver_Interface_v_1/s00_axi] [get_bd_intf_pins uz_user/smartconnect_1/M${num}_AXI]
}

# assign base address to first IP core
assign_bd_address -target_address_space /zynq_ultra_ps_e_0/Data [get_bd_addr_segs uz_user/Resolver_Interface_v_0/s00_axi/reg0] -force
# assign base address to second IP core
assign_bd_address -target_address_space /zynq_ultra_ps_e_0/Data [get_bd_addr_segs uz_user/Resolver_Interface_v_1/s00_axi/reg0] -force
