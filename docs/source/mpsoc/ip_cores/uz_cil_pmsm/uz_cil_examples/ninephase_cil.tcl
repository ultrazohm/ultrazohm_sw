update_ip_catalog -rebuild
create_bd_cell -type hier ninephase_CIL



startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 ninephase_CIL/smartconnect_0
set_property -dict [list \
  CONFIG.NUM_MI {5} \
  CONFIG.NUM_SI {1} \
] [get_bd_cells ninephase_CIL/smartconnect_0]
create_bd_pin -dir I ninephase_CIL/aresetn
create_bd_pin -dir I ninephase_CIL/aclk
create_bd_pin -dir I ninephase_CIL/trigger_adc
create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ninephase_CIL/AXI
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/smartconnect_0/aclk]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/smartconnect_0/aresetn]
connect_bd_intf_net [get_bd_intf_pins ninephase_CIL/AXI] [get_bd_intf_pins ninephase_CIL/smartconnect_0/S00_AXI]
endgroup

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_pmsm_model_9ph_dq:1.0 ninephase_CIL/uz_pmsm_model_9ph_dq_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_ninephase_VSD_transformation:1.0 ninephase_CIL/uz_ninephase_VSD_tra_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 ninephase_CIL/uz_inverter_3ph_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 ninephase_CIL/uz_inverter_3ph_1
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 ninephase_CIL/uz_inverter_3ph_2
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_rs_flip_flop:1.0 ninephase_CIL/uz_rs_flip_flop_0
create_bd_pin -dir I ninephase_CIL/gate_sys1
create_bd_pin -dir I ninephase_CIL/gate_sys2
create_bd_pin -dir I ninephase_CIL/gate_sys3
endgroup

startgroup
connect_bd_intf_net [get_bd_intf_pins ninephase_CIL/uz_pmsm_model_9ph_dq_0/AXI4] [get_bd_intf_pins ninephase_CIL/smartconnect_0/M00_AXI]
connect_bd_intf_net [get_bd_intf_pins ninephase_CIL/uz_ninephase_VSD_tra_0/AXI4] [get_bd_intf_pins ninephase_CIL/smartconnect_0/M01_AXI]
connect_bd_intf_net [get_bd_intf_pins ninephase_CIL/uz_inverter_3ph_0/AXI4] [get_bd_intf_pins ninephase_CIL/smartconnect_0/M02_AXI]
connect_bd_intf_net [get_bd_intf_pins ninephase_CIL/uz_inverter_3ph_1/AXI4] [get_bd_intf_pins ninephase_CIL/smartconnect_0/M03_AXI]
connect_bd_intf_net [get_bd_intf_pins ninephase_CIL/uz_inverter_3ph_2/AXI4] [get_bd_intf_pins ninephase_CIL/smartconnect_0/M04_AXI]
endgroup

startgroup
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_ninephase_VSD_tra_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_ninephase_VSD_tra_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_rs_flip_flop_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_1/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_1/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_2/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_2/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_pmsm_model_9ph_dq_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aclk] [get_bd_pins uz_user/ninephase_CIL/uz_pmsm_model_9ph_dq_0/AXI4_ACLK]
endgroup

startgroup
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_ninephase_VSD_tra_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_ninephase_VSD_tra_0/AXI4_ARESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_rs_flip_flop_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_0/AXI4_ARESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_1/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_1/AXI4_ARESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_2/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_inverter_3ph_2/AXI4_ARESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_pmsm_model_9ph_dq_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/ninephase_CIL/aresetn] [get_bd_pins uz_user/ninephase_CIL/uz_pmsm_model_9ph_dq_0/AXI4_ARESETN]
endgroup

startgroup
connect_bd_net [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_out_dq_0] [get_bd_pins ninephase_CIL/uz_pmsm_model_9ph_dq_0/voltage_input_dq_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_pmsm_model_9ph_dq_0/currents_dq_out_0] [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_in_dq_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_pmsm_model_9ph_dq_0/theta_el_out] [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/theta_el]
connect_bd_net [get_bd_pins ninephase_CIL/uz_inverter_3ph_0/u_abc_pl_0] [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_abc1_ll_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_inverter_3ph_1/u_abc_pl_0] [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_abc2_ll_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_inverter_3ph_2/u_abc_pl_0] [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_abc3_ll_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_abc_1_0] [get_bd_pins ninephase_CIL/uz_inverter_3ph_0/i_abc_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_abc_2_0] [get_bd_pins ninephase_CIL/uz_inverter_3ph_1/i_abc_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/x_abc_3_0] [get_bd_pins ninephase_CIL/uz_inverter_3ph_2/i_abc_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/uz_rs_flip_flop_0/ff_out] [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/trigger_new_values]
connect_bd_net [get_bd_pins ninephase_CIL/uz_ninephase_VSD_tra_0/refresh_values] [get_bd_pins ninephase_CIL/uz_rs_flip_flop_0/ff_reset]
connect_bd_net [get_bd_pins ninephase_CIL/trigger_adc] [get_bd_pins ninephase_CIL/uz_rs_flip_flop_0/ff_set]
connect_bd_net [get_bd_pins ninephase_CIL/gate_sys1] [get_bd_pins ninephase_CIL/uz_inverter_3ph_0/gate_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/gate_sys2] [get_bd_pins ninephase_CIL/uz_inverter_3ph_1/gate_pl_0]
connect_bd_net [get_bd_pins ninephase_CIL/gate_sys3] [get_bd_pins ninephase_CIL/uz_inverter_3ph_2/gate_pl_0]
endgroup

regenerate_bd_layout -hierarchy [get_bd_cells ninephase_CIL]
