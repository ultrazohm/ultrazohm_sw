# create hierarchy and put temperature card ip core in it
puts "Adding Temperature Card IP to uz_user"
create_bd_cell -type hier uz_user/temp_card_interface
startgroup
create_bd_cell -type ip -vlnv xilinx.com:user:Temperature_Card_Interface_v1_0:1.1 uz_user/temp_card_interface/Temperature_Card_Int_0
endgroup

puts "Creating Ports in uz_user"
# create output ports in uz_user
create_bd_pin -dir O uz_user/SPI_MOSI_1_Dig01
create_bd_pin -dir O uz_user/SPI_SCLK_1_Dig00
create_bd_pin -dir O uz_user/SPI_SS_1_Dig03
create_bd_pin -dir O uz_user/LTC_resetn_1_Dig18

create_bd_pin -dir O uz_user/SPI_MOSI_2_Dig13
create_bd_pin -dir O uz_user/SPI_SCLK_2_Dig12
create_bd_pin -dir O uz_user/SPI_SS_2_Dig15
create_bd_pin -dir O uz_user/LTC_resetn_2_NC

create_bd_pin -dir O uz_user/SPI_MOSI_3_Dig07
create_bd_pin -dir O uz_user/SPI_SCLK_3_Dig06
create_bd_pin -dir O uz_user/SPI_SS_3_Dig09
create_bd_pin -dir O uz_user/LTC_resetn_3_NC

# create input ports in uz_user
create_bd_pin -dir I uz_user/SPI_MISO_1_Dig02
create_bd_pin -dir I uz_user/SPI_MISO_2_Dig14
create_bd_pin -dir I uz_user/SPI_MISO_3_Dig08
create_bd_pin -dir I uz_user/LTC_Interrupt_1_Dig04
create_bd_pin -dir I uz_user/LTC_Interrupt_2_Dig16
create_bd_pin -dir I uz_user/LTC_Interrupt_3_Dig10

puts "Connecting signals between uz_user ports and ip core"
# connect all signals exept the axi line between the ports and the ip core
connect_bd_net [get_bd_pins uz_user/SPI_MOSI_1_Dig01] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_MOSI_1]
connect_bd_net [get_bd_pins uz_user/SPI_SCLK_1_Dig00] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_SCLK_1]
connect_bd_net [get_bd_pins uz_user/SPI_SS_1_Dig03] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_SS_1]
connect_bd_net [get_bd_pins uz_user/LTC_resetn_1_Dig18] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/LTC_resetn_1]

connect_bd_net [get_bd_pins uz_user/SPI_MOSI_2_Dig13] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_MOSI_2]
connect_bd_net [get_bd_pins uz_user/SPI_SCLK_2_Dig12] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_SCLK_2]
connect_bd_net [get_bd_pins uz_user/SPI_SS_2_Dig15] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_SS_2]
connect_bd_net [get_bd_pins uz_user/LTC_resetn_2_NC] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/LTC_resetn_2]

connect_bd_net [get_bd_pins uz_user/SPI_MOSI_3_Dig07] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_MOSI_3]
connect_bd_net [get_bd_pins uz_user/SPI_SCLK_3_Dig06] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_SCLK_3]
connect_bd_net [get_bd_pins uz_user/SPI_SS_3_Dig09] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_SS_3]
connect_bd_net [get_bd_pins uz_user/LTC_resetn_3_NC] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/LTC_resetn_3]

connect_bd_net [get_bd_pins uz_user/SPI_MISO_1_Dig02] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_MISO_1]
connect_bd_net [get_bd_pins uz_user/SPI_MISO_2_Dig14] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_MISO_2]
connect_bd_net [get_bd_pins uz_user/SPI_MISO_3_Dig08] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/SPI_MISO_3]
connect_bd_net [get_bd_pins uz_user/LTC_Interrupt_1_Dig04] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/LTC_Interrupt_1]
connect_bd_net [get_bd_pins uz_user/LTC_Interrupt_2_Dig16] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/LTC_Interrupt_2]
connect_bd_net [get_bd_pins uz_user/LTC_Interrupt_3_Dig10] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/LTC_Interrupt_3]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/s00_axi_aclk]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/temp_card_interface/Temperature_Card_Int_0/s00_axi_aresetn]

# check number of axi channels at smartconnect_1 and add another channel
set num [expr {[get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] + 1}]
set_property -dict [list CONFIG.NUM_MI "$num"] [get_bd_cells uz_user/smartconnect_1]

# connect ipcore AXI port to the above created AXI port at smartconnect_1
set num [expr [get_property [list CONFIG.NUM_MI] [get_bd_cells uz_user/smartconnect_1]] - 1]
if {$num < 10} {
connect_bd_intf_net [get_bd_intf_pins uz_user/temp_card_interface/Temperature_Card_Int_0/s00_axi] [get_bd_intf_pins uz_user/smartconnect_1/M0${num}_AXI]
} else {
connect_bd_intf_net [get_bd_intf_pins uz_user/temp_card_interface/Temperature_Card_Int_0/s00_axi] [get_bd_intf_pins uz_user/smartconnect_1/M${num}_AXI]
}

# assign base address
assign_bd_address -target_address_space /zynq_ultra_ps_e_0/Data [get_bd_addr_segs uz_user/temp_card_interface/Temperature_Card_Int_0/s00_axi/reg0] -force

# disable the packed constraint file for D4
set_property is_enabled false [get_files  Digital_D4_packed.xdc]

# enable the "unpacked" constraint file for D4
set_property is_enabled true [get_files  Digital_AdapterBoard_D4.xdc]