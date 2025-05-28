set proj_path [get_property DIRECTORY [current_project]]
set bd_path "$proj_path/zusys/zusys.bd"


if { [current_bd_design -quiet] eq "" } {
        open_bd_design $bd_path
}



delete_bd_objs [get_bd_intf_nets uz_user/smartconnect_1_M00_AXI]
delete_bd_objs [get_bd_cells uz_user/uz_axi_testIP_0]
delete_bd_objs [get_bd_nets uz_user/zynq_ultra_ps_e_0_pl_clk1] 
delete_bd_objs [get_bd_nets uz_user/proc_sys_reset_1_peripheral_aresetn] 
delete_bd_objs [get_bd_intf_nets uz_user/smartconnect_0_M10_AXI] 
delete_bd_objs [get_bd_cells uz_user/smartconnect_1]
delete_bd_objs [get_bd_nets uz_system_wdt_interrupt]

create_bd_cell -type ip -vlnv fau.de:hsa:board_design_graybox:1.0 uz_user/board_design_graybox_0
create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 uz_user/DATA_AXI00
create_bd_pin -dir O uz_user/IRQ
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0

set_property CONFIG.PSU__USE__S_AXI_GP2 {1} [get_bd_cells zynq_ultra_ps_e_0]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/board_design_graybox_0/CMD_AXI_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/board_design_graybox_0/CORE_CLK]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/board_design_graybox_0/DATA_AXI_CLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/board_design_graybox_0/DATA_AXI_RSTN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/board_design_graybox_0/CORE_RSTN]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/board_design_graybox_0/CMD_AXI_RSTN]
connect_bd_intf_net [get_bd_intf_pins uz_user/S00_AXI] [get_bd_intf_pins uz_user/board_design_graybox_0/CMD_AXI]
connect_bd_intf_net [get_bd_intf_pins uz_user/DATA_AXI00] [get_bd_intf_pins uz_user/board_design_graybox_0/DATA_AXI00]
connect_bd_net [get_bd_pins uz_user/IRQ] [get_bd_pins uz_user/board_design_graybox_0/HOST_PP_IRQ]

connect_bd_net [get_bd_pins xlconcat_0/In0] [get_bd_pins uz_system/wdt_interrupt]
connect_bd_net [get_bd_pins uz_user/IRQ] [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq1]
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/saxihp0_fpd_aclk] [get_bd_pins zynq_ultra_ps_e_0/pl_clk0]
connect_bd_intf_net [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HP0_FPD] -boundary_type upper [get_bd_intf_pins uz_user/DATA_AXI00]

assign_bd_address -target_address_space /uz_user/board_design_graybox_0/DATA_AXI00 [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP2/HP0_DDR_LOW] -force
assign_bd_address -target_address_space /uz_user/board_design_graybox_0/DATA_AXI00 [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP2/HP0_LPS_OCM] -force
assign_bd_address -target_address_space /uz_user/board_design_graybox_0/DATA_AXI00 [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP2/HP0_DDR_HIGH] -force
assign_bd_address -target_address_space /uz_user/board_design_graybox_0/DATA_AXI00 [get_bd_addr_segs zynq_ultra_ps_e_0/SAXIGP2/HP0_QSPI] -force
assign_bd_address -offset 0x80120000 -range 64K [get_bd_addr_segs uz_user/board_design_graybox_0/CMD_AXI/reg0]

validate_bd_design

set_property synth_checkpoint_mode None [get_files $bd_path]

add_files -fileset constrs_1 "$proj_path/../../ip_cores/fau_cs3_graybox/fau_cs3_graybox.xdc"
set_property USED_IN {synthesis implementation} [get_files fau_cs3_graybox.xdc]

generate_target all [get_files $bd_path]

save_bd_design

make_wrapper -files [get_files $bd_path] -top



