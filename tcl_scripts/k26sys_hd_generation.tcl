

################################################################
# Hierarchy Design Automation Flow
################################################################

cd [ get_property DIRECTORY [current_project] ]
create_bd_cell -type hier uzblocksys
source ../tcl_scripts/kria_vivado_block_uz_user.tcl
create_hier_cell_uz_user uzblocksys uz_user
source ../tcl_scripts/kria_vivado_block_uz_system.tcl
create_hier_cell_uz_system uzblocksys uz_system
source ../tcl_scripts/kria_vivado_block_digital_adapter.tcl
create_hier_cell_uz_digital_adapter uzblocksys uz_digital_adapter
ungroup_bd_cells [get_bd_cells uzblocksys]
regenerate_bd_layout

connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/S00_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM0_LPD]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_1
endgroup

delete_bd_objs [get_bd_intf_nets uz_digital_adapter/AXI4_Lite_3] [get_bd_nets uz_digital_adapter/Gates_3L_Gate_Signals_3L] [get_bd_nets uz_digital_adapter/xlslice_Enable_Inverter_Dout] [get_bd_nets uz_digital_adapter/Gates_3L_Interrupt_Center] [get_bd_nets uz_digital_adapter/Gates_3L_Interrupt_Start] [get_bd_nets uz_digital_adapter/Gates_3L_Interrupt_Start_Center] [get_bd_cells uz_digital_adapter/D2_adapter]
delete_bd_objs [get_bd_intf_nets uz_digital_adapter/AXI4_Lite_2] [get_bd_nets uz_digital_adapter/zynq_ultra_ps_e_0_pl_clk3] [get_bd_nets uz_digital_adapter/proc_sys_reset_50MHz_peripheral_aresetn] [get_bd_nets uz_digital_adapter/I_1] [get_bd_nets uz_digital_adapter/A_1] [get_bd_nets uz_digital_adapter/B_1] [get_bd_nets uz_digital_adapter/Interrupt_muxed] [get_bd_cells uz_digital_adapter/D5_adapter]
delete_bd_objs [get_bd_nets uz_digital_adapter/vio_D2_test_probe_out0] [get_bd_cells uz_digital_adapter/D3_adapter]
delete_bd_objs [get_bd_intf_pins uz_digital_adapter/AXI4_Lite3]
delete_bd_objs [get_bd_intf_pins uz_digital_adapter/AXI4_Lite]
delete_bd_objs [get_bd_pins uz_digital_adapter/D2_OUT]
delete_bd_objs [get_bd_pins uz_digital_adapter/D3_OUT]
delete_bd_objs [get_bd_pins uz_digital_adapter/Interrupt_Center]
delete_bd_objs [get_bd_pins uz_digital_adapter/Interrupt_Start]
delete_bd_objs [get_bd_pins uz_digital_adapter/Interrupt_Start_Center]
delete_bd_objs [get_bd_pins uz_digital_adapter/Dig_11_Ch5]
delete_bd_objs [get_bd_pins uz_digital_adapter/Dig_12_Ch5]
delete_bd_objs [get_bd_pins uz_digital_adapter/Dig_13_Ch5]
delete_bd_objs [get_bd_pins uz_digital_adapter/Enable_Gate]
delete_bd_objs [get_bd_pins uz_digital_adapter/AXI4_Lite_ACLK]
delete_bd_objs [get_bd_pins uz_digital_adapter/AXI4_Lite_ARESETN1]
delete_bd_objs [get_bd_pins uz_digital_adapter/probe5]
delete_bd_objs [get_bd_intf_nets uz_system_M00_AXI1]
delete_bd_objs [get_bd_intf_pins uz_system/M01_AXI]
delete_bd_objs [get_bd_intf_nets uz_system/Conn4] [get_bd_intf_pins uz_system/M00_AXI1]
delete_bd_objs [get_bd_intf_nets uz_system/Conn6] [get_bd_intf_nets uz_system_M01_AXI]
delete_bd_objs [get_bd_intf_nets uz_system/Conn5] [get_bd_intf_pins uz_system/M02_AXI]
delete_bd_objs [get_bd_intf_nets uz_system/Conn2] [get_bd_intf_pins uz_system/M10_AXI]
delete_bd_objs [get_bd_intf_nets uz_system/Conn12] [get_bd_intf_pins uz_system/M12_AXI]

set_property CONFIG.CONST_WIDTH {128} [get_bd_cells xlconstant_1]
connect_bd_net [get_bd_pins uz_system/ADC_A1] [get_bd_pins xlconstant_1/dout]
connect_bd_net [get_bd_pins uz_system/ADC_A2] [get_bd_pins xlconstant_1/dout]
connect_bd_net [get_bd_pins uz_system/ADC_A3] [get_bd_pins xlconstant_1/dout]
connect_bd_net [get_bd_pins uz_system/Interrupt0] [get_bd_pins uz_digital_adapter/Carrier_triangular_max_min] -boundary_type upper
connect_bd_net [get_bd_pins uz_system/Interrupt1] [get_bd_pins uz_digital_adapter/Carrier_triangular_min] -boundary_type upper
connect_bd_net [get_bd_pins uz_system/Interrupt2] [get_bd_pins uz_digital_adapter/Carrier_triangular_max] -boundary_type upper
connect_bd_net [get_bd_pins uz_system/Interrupt3] [get_bd_pins xlconstant_0/dout]
connect_bd_net [get_bd_pins uz_system/Interrupt4] [get_bd_pins xlconstant_0/dout]
connect_bd_net [get_bd_pins uz_system/Interrupt5] [get_bd_pins xlconstant_0/dout]
connect_bd_net [get_bd_pins uz_system/trigger_converesions] [get_bd_pins uz_system/Trigger_AXI2TCM] -boundary_type upper
connect_bd_net [get_bd_pins uz_system/clk] [get_bd_pins zynq_ultra_ps_e_0/pl_clk0]
connect_bd_net [get_bd_pins uz_system/resetn] [get_bd_pins zynq_ultra_ps_e_0/pl_resetn0]

connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_Lite_PWM_0] [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_0]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_Lite_PWM_1] [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_1]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_Lite_PWM_2] [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_2]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_Lite_PWM_3] [get_bd_intf_pins uz_digital_adapter/AXI4_Lite_PWM_3]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_interlock_0] [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_0]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_interlock_1] [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_1]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_interlock_2] [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_2]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/AXI4_interlock_3] [get_bd_intf_pins uz_digital_adapter/AXI4_interlock_3]
connect_bd_intf_net [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_LPD] -boundary_type upper [get_bd_intf_pins uz_system/M00_AXI]
connect_bd_intf_net -boundary_type upper [get_bd_intf_pins uz_system/M09_AXI] [get_bd_intf_pins uz_user/S00_AXI]
connect_bd_net [get_bd_pins uz_system/D4_OUT] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
connect_bd_net [get_bd_pins uz_digital_adapter/RESETN] [get_bd_pins uz_system/peripheral_aresetn] -boundary_type upper
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq1] [get_bd_pins uz_system/wdt_interrupt]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_system/peripheral_aresetn] -boundary_type upper
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins uz_user/aclk]
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins uz_digital_adapter/clk]


regenerate_bd_layout

