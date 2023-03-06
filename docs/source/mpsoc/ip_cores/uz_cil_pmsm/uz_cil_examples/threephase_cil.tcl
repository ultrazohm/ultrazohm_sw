update_ip_catalog -rebuild


delete_bd_objs [get_bd_intf_nets uz_user/smartconnect_1_M00_AXI] [get_bd_cells uz_user/uz_axi_testIP_0]

startgroup
set_property -dict [list CONFIG.NUM_MI {4}] [get_bd_cells uz_user/smartconnect_1]
endgroup

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_pmsm_model_3ph_dq:1.0 uz_user/uz_pmsm_model_3ph_dq_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_threephase_VSD_transformation:1.0 uz_user/uz_threephase_VSD_tr_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_inverter_3ph:1.0 uz_user/uz_inverter_3ph_0
create_bd_cell -type ip -vlnv xilinx.com:ip:PWM_and_SS_control_V4_ip:4.1 uz_user/PWM_and_SS_control_V_0
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 uz_user/xlconcat_0
create_bd_cell -type ip -vlnv xilinx.com:ip:uz_rs_flip_flop:1.0 uz_user/uz_rs_flip_flop_0
endgroup



set_property -dict [list CONFIG.NUM_PORTS {6}] [get_bd_cells uz_user/xlconcat_0]



connect_bd_intf_net [get_bd_intf_pins uz_user/uz_pmsm_model_3ph_dq_0/AXI4] [get_bd_intf_pins uz_user/smartconnect_1/M00_AXI]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_pmsm_model_3ph_dq_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_pmsm_model_3ph_dq_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_pmsm_model_3ph_dq_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_pmsm_model_3ph_dq_0/AXI4_ARESETN]

connect_bd_intf_net [get_bd_intf_pins uz_user/uz_threephase_VSD_tr_0/AXI4] [get_bd_intf_pins uz_user/smartconnect_1/M01_AXI]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/AXI4_ARESETN]

connect_bd_intf_net [get_bd_intf_pins uz_user/uz_inverter_3ph_0/AXI4] [get_bd_intf_pins uz_user/smartconnect_1/M02_AXI]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_inverter_3ph_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_inverter_3ph_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_inverter_3ph_0/AXI4_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_inverter_3ph_0/AXI4_ARESETN]

connect_bd_intf_net [get_bd_intf_pins uz_user/PWM_and_SS_control_V_0/AXI4_Lite] [get_bd_intf_pins uz_user/smartconnect_1/M03_AXI]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/PWM_and_SS_control_V_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/PWM_and_SS_control_V_0/IPCORE_RESETN]
connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/PWM_and_SS_control_V_0/AXI4_Lite_ACLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/PWM_and_SS_control_V_0/AXI4_Lite_ARESETN]

connect_bd_net [get_bd_pins uz_user/aclk] [get_bd_pins uz_user/uz_rs_flip_flop_0/IPCORE_CLK]
connect_bd_net [get_bd_pins uz_user/aresetn] [get_bd_pins uz_user/uz_rs_flip_flop_0/IPCORE_RESETN]


connect_bd_net [get_bd_pins uz_user/uz_rs_flip_flop_0/ff_out] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/trigger_new_values]
connect_bd_net [get_bd_pins uz_user/uz_threephase_VSD_tr_0/refresh_values] [get_bd_pins uz_user/uz_rs_flip_flop_0/ff_reset]
connect_bd_net [get_bd_pins uz_user/uz_threephase_VSD_tr_0/x_abc_0] [get_bd_pins uz_user/uz_inverter_3ph_0/i_abc_pl_0]
connect_bd_net [get_bd_pins uz_user/uz_inverter_3ph_0/u_abc_pl_0] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/x_abc1_ll_pl_0]
connect_bd_net [get_bd_pins uz_user/uz_threephase_VSD_tr_0/x_out_dq_0] [get_bd_pins uz_user/uz_pmsm_model_3ph_dq_0/voltage_input_dq_0]
connect_bd_net [get_bd_pins uz_user/uz_pmsm_model_3ph_dq_0/currents_dq_out_0] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/x_in_dq_0]
connect_bd_net [get_bd_pins uz_user/uz_pmsm_model_3ph_dq_0/theta_el_out] [get_bd_pins uz_user/uz_threephase_VSD_tr_0/theta_el]
connect_bd_net [get_bd_pins uz_user/uz_inverter_3ph_0/gate_pl_0] [get_bd_pins uz_user/xlconcat_0/dout]
connect_bd_net [get_bd_pins uz_user/xlconcat_0/In0] [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS0_OUT]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS1_OUT] [get_bd_pins uz_user/xlconcat_0/In1]
connect_bd_net [get_bd_pins uz_user/xlconcat_0/In2] [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS2_OUT]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS3_OUT] [get_bd_pins uz_user/xlconcat_0/In3]
connect_bd_net [get_bd_pins uz_user/xlconcat_0/In4] [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS4_OUT]
connect_bd_net [get_bd_pins uz_user/PWM_and_SS_control_V_0/SS5_OUT] [get_bd_pins uz_user/xlconcat_0/In5]

connect_bd_net [get_bd_pins uz_system/trigger_converesions] [get_bd_pins uz_user/uz_rs_flip_flop_0/ff_set]
connect_bd_net [get_bd_pins uz_digital_adapter/D1_adapter/Gates/PWM_and_SS_control_V_0/triangle_out] [get_bd_pins uz_user/PWM_and_SS_control_V_0/triangle_in]
regenerate_bd_layout -hierarchy [get_bd_cells uz_user]
